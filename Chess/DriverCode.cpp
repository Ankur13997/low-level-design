// chess.cpp
// Compile: g++ -std=c++17 chess.cpp -o chess

/*
    Strategy pattern for piece movement
    Factory pattern for piece creation
    singleton pattern for board
    observer pattern for notification
*/
#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <optional>
#include <cassert>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::array;
using std::optional;
using std::nullopt;
using std::weak_ptr;
using std::string;

enum class Color { WHITE, BLACK };
enum class PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

struct Position {
    int r; // 0..7
    int c; // 0..7
    Position(int rr, int cc): r(rr), c(cc) {}
    bool operator==(Position const& o) const { return r==o.r && c==o.c; }
};

inline bool inBounds(const Position& p) {
    return p.r >= 0 && p.r < 8 && p.c >= 0 && p.c < 8;
}

// Forward declaration
struct Board;

// Movement strategy interface
struct MovementStrategy {
    virtual ~MovementStrategy() = default;
    // Return vector of legal positions this piece could move to ignoring check rules.
    virtual vector<Position> getMoves(const Board& board, const Position& from) const = 0;
};

// Piece interface
struct Piece {
    Color color;
    PieceType type;
    std::shared_ptr<MovementStrategy> strategy;

    Piece(Color c, PieceType t, std::shared_ptr<MovementStrategy> s)
        : color(c), type(t), strategy(s) {}

    virtual ~Piece() = default;
};

// Board singleton
struct Board {
private:
    array<array<shared_ptr<Piece>, 8>, 8> grid;

    Board() {
        for (int r=0;r<8;++r) for (int c=0;c<8;++c) grid[r][c] = nullptr;
    }

public:
    Board(Board const&) = delete;
    Board& operator=(Board const&) = delete;

    static Board& getInstance() {
        static Board instance;
        return instance;
    }

    shared_ptr<Piece> getPiece(const Position& p) const {
        if (!inBounds(p)) return nullptr;
        return grid[p.r][p.c];
    }

    void setPiece(const Position& p, shared_ptr<Piece> piece) {
        assert(inBounds(p));
        grid[p.r][p.c] = piece;
    }

    void removePiece(const Position& p) {
        assert(inBounds(p));
        grid[p.r][p.c] = nullptr;
    }

    bool isEmpty(const Position& p) const {
        return getPiece(p) == nullptr;
    }

    // Move piece if the move is allowed by the piece's movement strategy (doesn't check "check" state).
    // Returns true if move executed.
    bool movePiece(const Position& from, const Position& to) {
        if (!inBounds(from) || !inBounds(to)) return false;
        auto piece = getPiece(from);
        if (!piece) return false;

        // Compute allowed moves from strategy
        auto moves = piece->strategy->getMoves(*this, from);
        bool allowed = false;
        for (auto &m : moves) if (m == to) { allowed = true; break; }

        if (!allowed) return false;

        // If destination has same-color piece, illegal
        auto destPiece = getPiece(to);
        if (destPiece && destPiece->color == piece->color) return false;

        // Execute move (simple capture if dest occupied)
        setPiece(to, piece);
        removePiece(from);
        return true;
    }

    // Utility: print board (simple ASCII)
    void print() const {
        for (int r=7;r>=0;--r) {
            cout << r+1 << " ";
            for (int c=0;c<8;++c) {
                auto p = grid[r][c];
                if (!p) cout << ". ";
                else {
                    char ch = '?';
                    switch (p->type) {
                        case PieceType::KING: ch='K'; break;
                        case PieceType::QUEEN: ch='Q'; break;
                        case PieceType::ROOK: ch='R'; break;
                        case PieceType::BISHOP: ch='B'; break;
                        case PieceType::KNIGHT: ch='N'; break;
                        case PieceType::PAWN: ch='P'; break;
                    }
                    if (p->color == Color::BLACK) ch = std::tolower(ch);
                    cout << ch << " ";
                }
            }
            cout << endl;
        }
        cout << "  a b c d e f g h\n";
    }
};

// Helper for direction sliding moves
static vector<Position> slideMoves(const Board& board, const Position& from, const vector<std::pair<int,int>>& dirs, Color myColor) {
    vector<Position> res;
    for (auto [dr, dc] : dirs) {
        int r = from.r + dr;
        int c = from.c + dc;
        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            Position p(r,c);
            auto piece = board.getPiece(p);
            if (!piece) {
                res.push_back(p);
            } else {
                if (piece->color != myColor) res.push_back(p); // capture
                break; // blocked
            }
            r += dr; c += dc;
        }
    }
    return res;
}

// Concrete movement strategies

struct KingStrategy : MovementStrategy {
    vector<Position> getMoves(const Board& board, const Position& from) const override {
        vector<Position> res;
        for (int dr=-1; dr<=1; ++dr)
            for (int dc=-1; dc<=1; ++dc) {
                if (dr==0 && dc==0) continue;
                Position p(from.r+dr, from.c+dc);
                if (!inBounds(p)) continue;
                auto dest = board.getPiece(p);
                if (!dest || dest->color != board.getPiece(from)->color) res.push_back(p);
            }
        // TODO: check/checkmate/castling handled externally
        return res;
    }
};

struct KnightStrategy : MovementStrategy {
    vector<Position> getMoves(const Board& board, const Position& from) const override {
        vector<Position> res;
        static const int moves[8][2] = {
            {2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}
        };
        auto me = board.getPiece(from);
        for (auto &m : moves) {
            Position p(from.r + m[0], from.c + m[1]);
            if (!inBounds(p)) continue;
            auto dest = board.getPiece(p);
            if (!dest || dest->color != me->color) res.push_back(p);
        }
        return res;
    }
};

struct BishopStrategy : MovementStrategy {
    vector<Position> getMoves(const Board& board, const Position& from) const override {
        auto me = board.getPiece(from);
        vector<std::pair<int,int>> dirs = {{1,1},{1,-1},{-1,1},{-1,-1}};
        return slideMoves(board, from, dirs, me->color);
    }
};

struct RookStrategy : MovementStrategy {
    vector<Position> getMoves(const Board& board, const Position& from) const override {
        auto me = board.getPiece(from);
        vector<std::pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
        return slideMoves(board, from, dirs, me->color);
    }
};

struct QueenStrategy : MovementStrategy {
    vector<Position> getMoves(const Board& board, const Position& from) const override {
        auto me = board.getPiece(from);
        vector<std::pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
        return slideMoves(board, from, dirs, me->color);
    }
};

struct PawnStrategy : MovementStrategy {
    vector<Position> getMoves(const Board& board, const Position& from) const override {
        vector<Position> res;
        auto me = board.getPiece(from);
        Color color = me->color;
        int dir = (color == Color::WHITE) ? 1 : -1;
        // single step
        Position one(from.r + dir, from.c);
        if (inBounds(one) && board.isEmpty(one)) res.push_back(one);
        // double step from starting rank
        int startRow = (color == Color::WHITE) ? 1 : 6;
        Position two(from.r + 2*dir, from.c);
        if (from.r == startRow && inBounds(two) && board.isEmpty(one) && board.isEmpty(two)) res.push_back(two);
        // captures
        for (int dc : {-1, 1}) {
            Position cap(from.r + dir, from.c + dc);
            if (inBounds(cap)) {
                auto p = board.getPiece(cap);
                if (p && p->color != color) res.push_back(cap);
            }
        }
        // TODO: en-passant, promotion
        return res;
    }
};

// Factory for creating pieces
struct PieceFactory {
    static shared_ptr<Piece> createPiece(PieceType type, Color color) {
        switch (type) {
            case PieceType::KING:
                return make_shared<Piece>(color, type, make_shared<KingStrategy>());
            case PieceType::QUEEN:
                return make_shared<Piece>(color, type, make_shared<QueenStrategy>());
            case PieceType::ROOK:
                return make_shared<Piece>(color, type, make_shared<RookStrategy>());
            case PieceType::BISHOP:
                return make_shared<Piece>(color, type, make_shared<BishopStrategy>());
            case PieceType::KNIGHT:
                return make_shared<Piece>(color, type, make_shared<KnightStrategy>());
            case PieceType::PAWN:
                return make_shared<Piece>(color, type, make_shared<PawnStrategy>());
            default:
                return nullptr;
        }
    }
};

// Helper: parse algebraic (like "e2") to Position
optional<Position> parsePos(const string& s) {
    if (s.size() != 2) return nullopt;
    char file = s[0];
    char rank = s[1];
    if (file < 'a' || file > 'h') return nullopt;
    if (rank < '1' || rank > '8') return nullopt;
    int c = file - 'a';
    int r = rank - '1';
    return Position(r,c);
}

// Example usage: setup board and do moves
int main() {
    Board& board = Board::getInstance();

    // Place some pieces using factory: a tiny setup for demonstration
    // White: King on e1, Queen on d1, pawn on e2
    board.setPiece(Position(0,4), PieceFactory::createPiece(PieceType::KING, Color::WHITE)); // e1
    board.setPiece(Position(0,3), PieceFactory::createPiece(PieceType::QUEEN, Color::WHITE)); // d1
    board.setPiece(Position(1,4), PieceFactory::createPiece(PieceType::PAWN, Color::WHITE)); // e2
    board.setPiece(Position(0,1), PieceFactory::createPiece(PieceType::KNIGHT, Color::WHITE)); // b1

    // Black: King e8, pawn e7, rook a8
    board.setPiece(Position(7,4), PieceFactory::createPiece(PieceType::KING, Color::BLACK)); // e8
    board.setPiece(Position(6,4), PieceFactory::createPiece(PieceType::PAWN, Color::BLACK)); // e7
    board.setPiece(Position(7,0), PieceFactory::createPiece(PieceType::ROOK, Color::BLACK)); // a8

    cout << "Initial board:\n";
    board.print();

    // Try moves
    auto pFrom = parsePos("e2").value();
    auto pTo = parsePos("e4").value();
    cout << "\nMoving white pawn e2->e4: ";
    if (board.movePiece(pFrom, pTo)) cout << "OK\n";
    else cout << "Illegal\n";
    board.print();

    cout << "\nTrying illegal move: white queen d1->d3 (blocked by pawn originally)\n";
    if (board.movePiece(parsePos("d1").value(), parsePos("d3").value())) cout << "OK\n"; else cout << "Illegal\n";
    board.print();

    cout << "\nMove black pawn e7->e5\n";
    if (board.movePiece(parsePos("e7").value(), parsePos("e5").value())) cout << "OK\n"; else cout << "Illegal\n";
    board.print();

    cout << "\nWhite queen attempts d1->h5 (diagonal): ";
    if (board.movePiece(parsePos("d1").value(), parsePos("h5").value())) cout << "OK\n"; else cout << "Illegal\n";
    board.print();

    return 0;
}
