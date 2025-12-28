// chess_full.cpp
// Compile: g++ -std=c++17 chess_full.cpp -o chess_full
/*
Full check detection and legal-move validation by simulating moves.

Checkmate detection (simple: no legal moves while in check).

Castling (both kingside and queenside) with rules: king/rook unmoved, path empty, squares not under attack, king not currently in check.

En-passant capture handling.

Pawn promotion (automatic to Queen for simplicity).

The same Factory, Strategy, and Singleton Board structure as before; pieces have a hasMoved flag required for castling/en-passant.
*/
#include <bits/stdc++.h>
using namespace std;

enum class Color { WHITE, BLACK };
enum class PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

struct Position {
    int r; // 0..7
    int c; // 0..7
    Position() : r(0), c(0) {}
    Position(int rr, int cc): r(rr), c(cc) {}
    bool operator==(Position const& o) const { return r==o.r && c==o.c; }
    bool operator!=(Position const& o) const { return !(*this == o); }
};

inline bool inBounds(const Position& p) {
    return p.r >= 0 && p.r < 8 && p.c >= 0 && p.c < 8;
}

// forward
struct Board;

// Movement strategy interface
struct MovementStrategy {
    virtual ~MovementStrategy() = default;
    // Return vector of pseudo-legal positions this piece could move to ignoring checks.
    virtual vector<Position> getMoves(const Board& board, const Position& from) const = 0;
};

// Piece struct (contains hasMoved flag)
struct Piece {
    Color color;
    PieceType type;
    shared_ptr<MovementStrategy> strategy;
    bool hasMoved;

    Piece(Color c, PieceType t, shared_ptr<MovementStrategy> s)
        : color(c), type(t), strategy(s), hasMoved(false) {}

    // clone helper
    shared_ptr<Piece> clone() const {
        auto p = make_shared<Piece>(color, type, strategy);
        p->hasMoved = hasMoved;
        return p;
    }
};

// Move record for history & en-passant
struct MoveRecord {
    Position from;
    Position to;
    PieceType pieceType;
    bool wasCapture;
    // If pawn double-step, useful for en-passant detection
    bool pawnDoubleStep;
};

// Board singleton with clone ability
struct Board {
private:
    array<array<shared_ptr<Piece>, 8>, 8> grid;
    // history: last move is at back()
    vector<MoveRecord> history;

    Board() {
        for (int r=0;r<8;++r) for (int c=0;c<8;++c) grid[r][c] = nullptr;
    }

public:
    //Board(Board const&) = delete;
    //Board& operator=(Board const&) = delete;

    static Board& getInstance() {
        static Board instance;
        return instance;
    }

    // Create a deep copy of the board (for simulation)
    Board clone() const {
        Board b;
        for (int r=0;r<8;++r)
            for (int c=0;c<8;++c)
                if (grid[r][c]) b.grid[r][c] = grid[r][c]->clone();
                else b.grid[r][c] = nullptr;
        b.history = history;
        return b;
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

    // get last move if any
    optional<MoveRecord> lastMove() const {
        if (history.empty()) return nullopt;
        return history.back();
    }

    // low-level execute move (assumes move already validated). Handles turn-agnostic execution + special moves:
    // - capture
    // - en-passant capture
    // - castling rook movement
    // - pawn promotion (auto to queen)
    void executeMove(const Position& from, const Position& to) {
        auto piece = getPiece(from);
        assert(piece);
        bool wasCapture = false;
        bool pawnDouble = false;

        // En-passant capture detection: when pawn moves diagonally into empty square capturing opponent pawn that did a double step last turn
        if (piece->type == PieceType::PAWN && from.c != to.c && isEmpty(to)) {
            // en-passant capture; captured pawn is behind destination (opposite color)
            Position capPos(from.r, to.c);
            auto capPiece = getPiece(capPos);
            if (capPiece && capPiece->type == PieceType::PAWN && capPiece->color != piece->color) {
                removePiece(capPos);
                wasCapture = true;
            }
        } else {
            if (getPiece(to)) {
                wasCapture = true;
            }
        }

        // Castling rook movement: detect king move two squares horizontally
        if (piece->type == PieceType::KING && abs(to.c - from.c) == 2) {
            // kingside or queenside
            if (to.c == 6) { // kingside: rook from h -> f
                Position rookFrom(from.r, 7);
                Position rookTo(from.r, 5);
                auto rook = getPiece(rookFrom);
                setPiece(rookTo, rook);
                if (rook) rook->hasMoved = true;
                removePiece(rookFrom);
            } else if (to.c == 2) { // queenside: rook from a -> d
                Position rookFrom(from.r, 0);
                Position rookTo(from.r, 3);
                auto rook = getPiece(rookFrom);
                setPiece(rookTo, rook);
                if (rook) rook->hasMoved = true;
                removePiece(rookFrom);
            }
        }

        // Move piece
        setPiece(to, piece);
        removePiece(from);

        // Pawn double-step detection (for en-passant)
        if (piece->type == PieceType::PAWN && abs(to.r - from.r) == 2) pawnDouble = true;

        // mark hasMoved
        piece->hasMoved = true;

        // Pawn promotion (auto to Queen)
        if (piece->type == PieceType::PAWN) {
            if ((piece->color == Color::WHITE && to.r == 7) || (piece->color == Color::BLACK && to.r == 0)) {
                // promote to queen
                piece->type = PieceType::QUEEN;
                piece->strategy = make_shared<struct QueenStrategy>();
            }
        }

        // push history
        MoveRecord mr { from, to, piece->type, wasCapture, pawnDouble };
        history.push_back(mr);
    }

    // Validate and perform a move (per color turn isn't enforced by this function; caller should enforce turn).
    // This checks that 'to' is in the pseudo-legal moves of the piece (including special-case castling/en-passant),
    // and that after the move own king is not in check. Returns true if executed.
    bool movePieceIfLegal(const Position& from, const Position& to) {
        if (!inBounds(from) || !inBounds(to)) return false;
        auto piece = getPiece(from);
        if (!piece) return false;

        // compute pseudo-legal moves
        vector<Position> candidates = pseudoLegalMoves(from);

        bool allowed = false;
        for (auto &m : candidates) if (m == to) { allowed = true; break; }
        if (!allowed) return false;

        // simulate
        Board copy = this->clone();
        copy.executeMove(from, to);

        // is own king in check after this move?
        if (copy.isInCheck(piece->color)) return false;

        // commit
        executeMove(from, to);
        return true;
    }

    // Build pseudo-legal moves for a piece at 'from' including special moves (castling, en-passant) but ignoring check.
    vector<Position> pseudoLegalMoves(const Position& from) const {
        vector<Position> res;
        auto piece = getPiece(from);
        if (!piece) return res;

        // basic moves via strategy
        auto baseMoves = piece->strategy->getMoves(*this, from);
        for (auto &m : baseMoves) res.push_back(m);

        // Castling (king only)
        if (piece->type == PieceType::KING && !piece->hasMoved) {
            // cannot castle out of check; that check will be applied later by simulation, but also require path empty and rook unmoved
            // kingside
            Position f = from;
            // kingside squares f,g (c indices 5 and 6)
            bool canKS = true;
            if (getPiece(Position(f.r,5)) || getPiece(Position(f.r,6))) canKS = false;
            auto rookKS = getPiece(Position(f.r,7));
            if (!rookKS || rookKS->type != PieceType::ROOK || rookKS->color != piece->color || rookKS->hasMoved) canKS = false;
            if (canKS) {
                // also cannot castle if squares are under attack or king currently in check
                if (!isSquareAttacked(f, oppositeColor(piece->color)) &&
                    !isSquareAttacked(Position(f.r,5), oppositeColor(piece->color)) &&
                    !isSquareAttacked(Position(f.r,6), oppositeColor(piece->color))) {
                    res.push_back(Position(f.r,6));
                }
            }
            // queenside
            bool canQS = true;
            if (getPiece(Position(f.r,1)) || getPiece(Position(f.r,2)) || getPiece(Position(f.r,3))) canQS = false;
            auto rookQS = getPiece(Position(f.r,0));
            if (!rookQS || rookQS->type != PieceType::ROOK || rookQS->color != piece->color || rookQS->hasMoved) canQS = false;
            if (canQS) {
                if (!isSquareAttacked(f, oppositeColor(piece->color)) &&
                    !isSquareAttacked(Position(f.r,3), oppositeColor(piece->color)) &&
                    !isSquareAttacked(Position(f.r,2), oppositeColor(piece->color))) {
                    res.push_back(Position(f.r,2));
                }
            }
        }

        // En-passant (pawn only): if last move was opponent pawn double-step and adjacent
        if (piece->type == PieceType::PAWN) {
            auto lm = lastMove();
            if (lm.has_value() && lm->pawnDoubleStep && lm->pieceType == PieceType::PAWN && lm->to.r == from.r) {
                // last move landed an enemy pawn adjacent in same rank
                int dc = lm->to.c - from.c;
                if (abs(dc) == 1) {
                    // capture square is one step forward-diagonal to last-moved pawn's file
                    int dir = (piece->color == Color::WHITE) ? 1 : -1;
                    Position capPos(from.r + dir, lm->to.c);
                    // en-passant capture is only allowed onto capPos if empty (destination is empty except for en-passant)
                    if (inBounds(capPos) && isEmpty(capPos)) res.push_back(capPos);
                }
            }
        }

        // remove moves that capture same-color pieces
        vector<Position> filtered;
        for (auto &m : res) {
            auto dest = getPiece(m);
            if (!dest || dest->color != piece->color) filtered.push_back(m);
        }
        // remove duplicates
        sort(filtered.begin(), filtered.end(), [](const Position&a,const Position&b){
            if (a.r!=b.r) return a.r<b.r; return a.c<b.c;
        });
        filtered.erase(unique(filtered.begin(), filtered.end(), [](const Position&a,const Position&b){return a==b;}), filtered.end());
        return filtered;
    }

    // get opposite color
    static Color oppositeColor(Color c) { return (c==Color::WHITE)?Color::BLACK:Color::WHITE; }

    // is a square attacked by any piece of 'byColor'?
    bool isSquareAttacked(const Position& sq, Color byColor) const {
        // iterate all pieces of byColor and see if they attack sq
        for (int r=0;r<8;++r) for (int c=0;c<8;++c) {
            auto p = grid[r][c];
            if (!p || p->color != byColor) continue;
            Position from(r,c);
            // special-case by type for efficiency and correctness (pawns attack diagonally even if destination empty)
            switch (p->type) {
                case PieceType::PAWN: {
                    int dir = (byColor == Color::WHITE) ? 1 : -1;
                    Position a(from.r + dir, from.c - 1), b(from.r + dir, from.c + 1);
                    if (inBounds(a) && a == sq) return true;
                    if (inBounds(b) && b == sq) return true;
                    break;
                }
                case PieceType::KNIGHT: {
                    static const int moves[8][2] = {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
                    for (auto &m : moves) {
                        Position p2(from.r + m[0], from.c + m[1]);
                        if (inBounds(p2) && p2 == sq) return true;
                    }
                    break;
                }
                case PieceType::KING: {
                    for (int dr=-1; dr<=1; ++dr) for (int dc=-1; dc<=1; ++dc) {
                        if (dr==0 && dc==0) continue;
                        Position p2(from.r+dr, from.c+dc);
                        if (inBounds(p2) && p2 == sq) return true;
                    }
                    break;
                }
                case PieceType::BISHOP: {
                    static const vector<pair<int,int>> dirs = {{1,1},{1,-1},{-1,1},{-1,-1}};
                    for (auto [dr,dc] : dirs) {
                        int rr = from.r + dr, cc = from.c + dc;
                        while (rr>=0 && rr<8 && cc>=0 && cc<8) {
                            Position p2(rr,cc);
                            if (p2 == sq) return true;
                            if (grid[rr][cc]) break;
                            rr += dr; cc += dc;
                        }
                    }
                    break;
                }
                case PieceType::ROOK: {
                    static const vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
                    for (auto [dr,dc] : dirs) {
                        int rr = from.r + dr, cc = from.c + dc;
                        while (rr>=0 && rr<8 && cc>=0 && cc<8) {
                            Position p2(rr,cc);
                            if (p2 == sq) return true;
                            if (grid[rr][cc]) break;
                            rr += dr; cc += dc;
                        }
                    }
                    break;
                }
                case PieceType::QUEEN: {
                    static const vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
                    for (auto [dr,dc] : dirs) {
                        int rr = from.r + dr, cc = from.c + dc;
                        while (rr>=0 && rr<8 && cc>=0 && cc<8) {
                            Position p2(rr,cc);
                            if (p2 == sq) return true;
                            if (grid[rr][cc]) break;
                            rr += dr; cc += dc;
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
        return false;
    }

    // Is color in check?
    bool isInCheck(Color color) const {
        // find king
        Position kingPos(-1,-1);
        for (int r=0;r<8;++r) for (int c=0;c<8;++c) {
            auto p = grid[r][c];
            if (p && p->type == PieceType::KING && p->color == color) {
                kingPos = Position(r,c);
                break;
            }
        }
        if (!inBounds(kingPos)) return false; // no king? treat as not in check (shouldn't happen)
        return isSquareAttacked(kingPos, oppositeColor(color));
    }

    // has any legal move for color? used for checkmate/stalemate detection.
    bool hasAnyLegalMove(Color color) const {
        for (int r=0;r<8;++r) for (int c=0;c<8;++c) {
            auto p = grid[r][c];
            if (!p || p->color != color) continue;
            Position from(r,c);
            auto moves = pseudoLegalMoves(from);
            for (auto &to : moves) {
                // simulate
                Board copy = this->clone();
                copy.executeMove(from, to);
                if (!copy.isInCheck(color)) return true;
            }
        }
        return false;
    }

    // print ASCII board
    void print() const {
        for (int r=7;r>=0;--r) {
            cout << r+1 << " ";
            for (int c=0;c<8;++c) {
                auto p = grid[r][c];
                if (!p) cout << ". ";
                else {
                    char ch='?';
                    switch (p->type) {
                        case PieceType::KING: ch='K'; break;
                        case PieceType::QUEEN: ch='Q'; break;
                        case PieceType::ROOK: ch='R'; break;
                        case PieceType::BISHOP: ch='B'; break;
                        case PieceType::KNIGHT: ch='N'; break;
                        case PieceType::PAWN: ch='P'; break;
                    }
                    if (p->color == Color::BLACK) ch = tolower(ch);
                    cout << ch << " ";
                }
            }
            cout << endl;
        }
        cout << "  a b c d e f g h\n";
    }

    // helper to set history (for testing)
    void clearHistory() { history.clear(); }
};

// Helper for slide moves shared among strategies
static vector<Position> slideMoves(const Board& board, const Position& from, const vector<pair<int,int>>& dirs, Color myColor) {
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
                if (piece->color != myColor) res.push_back(p);
                break;
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
        // Castling handled at Board::pseudoLegalMoves
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
        vector<pair<int,int>> dirs = {{1,1},{1,-1},{-1,1},{-1,-1}};
        return slideMoves(board, from, dirs, me->color);
    }
};

struct RookStrategy : MovementStrategy {
    vector<Position> getMoves(const Board& board, const Position& from) const override {
        auto me = board.getPiece(from);
        vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
        return slideMoves(board, from, dirs, me->color);
    }
};

struct QueenStrategy : MovementStrategy {
    vector<Position> getMoves(const Board& board, const Position& from) const override {
        auto me = board.getPiece(from);
        vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
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
        // en-passant is handled at Board::pseudoLegalMoves (requires history)
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

// Example usage & tests
int main() {
    Board& board = Board::getInstance();

    // Setup standard initial positions (for demonstration minimal pieces + some special scenarios)
    // We'll populate a full initial chess setup to allow castling, en-passant tests, etc.
    // White back rank
    board.setPiece(Position(0,0), PieceFactory::createPiece(PieceType::ROOK, Color::WHITE));
    board.setPiece(Position(0,1), PieceFactory::createPiece(PieceType::KNIGHT, Color::WHITE));
    board.setPiece(Position(0,2), PieceFactory::createPiece(PieceType::BISHOP, Color::WHITE));
    board.setPiece(Position(0,3), PieceFactory::createPiece(PieceType::QUEEN, Color::WHITE));
    board.setPiece(Position(0,4), PieceFactory::createPiece(PieceType::KING, Color::WHITE));
    board.setPiece(Position(0,5), PieceFactory::createPiece(PieceType::BISHOP, Color::WHITE));
    board.setPiece(Position(0,6), PieceFactory::createPiece(PieceType::KNIGHT, Color::WHITE));
    board.setPiece(Position(0,7), PieceFactory::createPiece(PieceType::ROOK, Color::WHITE));
    for (int c=0;c<8;++c) board.setPiece(Position(1,c), PieceFactory::createPiece(PieceType::PAWN, Color::WHITE));

    // Black back rank
    board.setPiece(Position(7,0), PieceFactory::createPiece(PieceType::ROOK, Color::BLACK));
    board.setPiece(Position(7,1), PieceFactory::createPiece(PieceType::KNIGHT, Color::BLACK));
    board.setPiece(Position(7,2), PieceFactory::createPiece(PieceType::BISHOP, Color::BLACK));
    board.setPiece(Position(7,3), PieceFactory::createPiece(PieceType::QUEEN, Color::BLACK));
    board.setPiece(Position(7,4), PieceFactory::createPiece(PieceType::KING, Color::BLACK));
    board.setPiece(Position(7,5), PieceFactory::createPiece(PieceType::BISHOP, Color::BLACK));
    board.setPiece(Position(7,6), PieceFactory::createPiece(PieceType::KNIGHT, Color::BLACK));
    board.setPiece(Position(7,7), PieceFactory::createPiece(PieceType::ROOK, Color::BLACK));
    for (int c=0;c<8;++c) board.setPiece(Position(6,c), PieceFactory::createPiece(PieceType::PAWN, Color::BLACK));

    cout << "Initial board:\n";
    board.print();

    // Example: play moves to demonstrate en-passant and castling & promotion
    // 1. e2-e4
    board.movePieceIfLegal(parsePos("e2").value(), parsePos("e4").value());
    cout << "\nAfter e2-e4:\n"; board.print();

    // 1... d7-d5
    board.movePieceIfLegal(parsePos("d7").value(), parsePos("d5").value());
    cout << "\nAfter d7-d5:\n"; board.print();

    // 2. e4xd5 en-passant capture is NOT available here because the pawn moved one? Actually d7-d5 is double-step so e4 can capture d5 normally as a capture on d5.
    // Let's show en-passant scenario properly: reset small scenario:
    Board test = board.clone(); // start from current
    // Clear board for focused en-passant demo:
    Board& b2 = board; // reuse main board: construct custom scenario
    // Clear all
    board = Board::getInstance(); // singleton reference
    // Just set pawns
    board.clearHistory();
    // White pawn at e5 (r=4,c=4)
    board.setPiece(Position(4,4), PieceFactory::createPiece(PieceType::PAWN, Color::WHITE));
    // Black pawn at d7 (6,3)
    board.setPiece(Position(6,3), PieceFactory::createPiece(PieceType::PAWN, Color::BLACK));
    cout << "\nSetup for en-passant demo:\n"; board.print();

    // Black plays d7-d5 (double step)
    board.movePieceIfLegal(parsePos("d7").value(), parsePos("d5").value());
    cout << "\nAfter d7-d5 (black double-step):\n"; board.print();

    // White may capture en-passant e5xd6
    bool okEP = board.movePieceIfLegal(parsePos("e5").value(), parsePos("d6").value());
    cout << "\nWhite e5xd6 en-passant result: " << (okEP ? "OK" : "Illegal") << "\n";
    board.print();

    // Reset to starting position again for castling demo
    board = Board::getInstance().clone(); // get current instance? easier to clear manual
    // Clear and re-place standard king/rook for castling test
    board = Board::getInstance(); // reset reference
    // clear board
    for (int r=0;r<8;++r) for (int c=0;c<8;++c) board.removePiece(Position(r,c));
    board.clearHistory();
    // Place white king and rooks
    board.setPiece(Position(0,4), PieceFactory::createPiece(PieceType::KING, Color::WHITE));
    board.setPiece(Position(0,0), PieceFactory::createPiece(PieceType::ROOK, Color::WHITE));
    board.setPiece(Position(0,7), PieceFactory::createPiece(PieceType::ROOK, Color::WHITE));
    cout << "\nSetup for castling demo:\n"; board.print();

    // Ensure squares between king and rook empty (they are), ensure not in check: try kingside castle
    bool okCastleKS = board.movePieceIfLegal(parsePos("e1").value(), parsePos("g1").value());
    cout << "\nWhite kingside castle e1->g1: " << (okCastleKS ? "OK" : "Illegal") << "\n";
    board.print();

    // Reset and try queenside
    for (int r=0;r<8;++r) for (int c=0;c<8;++c) board.removePiece(Position(r,c));
    board.clearHistory();
    board.setPiece(Position(0,4), PieceFactory::createPiece(PieceType::KING, Color::WHITE));
    board.setPiece(Position(0,0), PieceFactory::createPiece(PieceType::ROOK, Color::WHITE));
    board.setPiece(Position(0,7), PieceFactory::createPiece(PieceType::ROOK, Color::WHITE));
    bool okCastleQS = board.movePieceIfLegal(parsePos("e1").value(), parsePos("c1").value());
    cout << "\nWhite queenside castle e1->c1: " << (okCastleQS ? "OK" : "Illegal") << "\n";
    board.print();

    // Promotion demo: pawn to last rank
    for (int r=0;r<8;++r) for (int c=0;c<8;++c) board.removePiece(Position(r,c));
    board.clearHistory();
    // white pawn at g7 (6,6) move to g8 to promote
    board.setPiece(Position(6,6), PieceFactory::createPiece(PieceType::PAWN, Color::WHITE));
    cout << "\nPromotion setup:\n"; board.print();
    bool okPromo = board.movePieceIfLegal(parsePos("g7").value(), parsePos("g8").value());
    cout << "\ng7->g8 promotion result: " << (okPromo ? "OK" : "Illegal") << "\n";
    board.print();

    // Check/checkmate demo (simple): Fool's mate example
    for (int r=0;r<8;++r) for (int c=0;c<8;++c) board.removePiece(Position(r,c));
    board.clearHistory();
    // Standard starting minimal pieces to reach quick mate
    // White: king e1, pawn f2, pawn g2
    board.setPiece(Position(0,4), PieceFactory::createPiece(PieceType::KING, Color::WHITE));
    board.setPiece(Position(1,5), PieceFactory::createPiece(PieceType::PAWN, Color::WHITE)); // f2
    board.setPiece(Position(1,6), PieceFactory::createPiece(PieceType::PAWN, Color::WHITE)); // g2
    // Black: king e8, queen d8, bishop c8
    board.setPiece(Position(7,4), PieceFactory::createPiece(PieceType::KING, Color::BLACK));
    board.setPiece(Position(7,3), PieceFactory::createPiece(PieceType::QUEEN, Color::BLACK));
    board.setPiece(Position(7,2), PieceFactory::createPiece(PieceType::BISHOP, Color::BLACK));
    cout << "\nFool's mate demo start (simplified):\n"; board.print();
    // White plays f2-f3
    board.movePieceIfLegal(parsePos("f2").value(), parsePos("f3").value());
    // Black plays e7-e5 (we'll simulate bishop/queen lines instead)
    // Black plays queen d8-h4 giving mate quickly (we don't have full pawns so just demonstrate checkmate detection)
    board.movePieceIfLegal(parsePos("d8").value(), parsePos("h4").value());
    cout << "\nAfter Black Qd8-h4, is White in check? " << (board.isInCheck(Color::WHITE) ? "Yes" : "No") << "\n";
    cout << "Does White have any legal move? " << (board.hasAnyLegalMove(Color::WHITE) ? "Yes" : "No") << "\n";
    if (board.isInCheck(Color::WHITE) && !board.hasAnyLegalMove(Color::WHITE)) cout << "White is checkmated!\n";
    else cout << "Not checkmate (demo simplified).\n";

    return 0;
}
