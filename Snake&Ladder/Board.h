#pragma once
#include<vector>
#include <iomanip>
#include "Cell.h"
#include "Player.h"
using namespace std;

class Board
{
private:
	int boardSize;
	vector<Cell*>grid;
public:
	Board(int boardSize): boardSize(boardSize)
	{
		grid.resize(boardSize + 1);
		for (int ind = 0; ind <= boardSize; ind++)
		{
			grid[ind] = new Cell();
		}
	}

	Cell* getCellAtPostion(int index)
	{
		return grid[index];
	}

	void Display(deque<Player*>& players)
	{
		// int rows = boardSize / 10;
		// int start = boardSize ;
		// bool reverseRow = false;

		// for (int r = 0; r < rows; ++r)
		// {
		// 	for (int c = 0; c < 10; ++c)
		// 	{
		// 		int index = reverseRow ? (start - (9 - c)) : (start - c);
		// 		std::cout << std::setw(4) << index;
		// 	}
		// 	std::cout << std::endl;
		// 	reverseRow = !reverseRow;
		// 	start -= 10;
		// }
		int rows = boardSize / 10;
		int start = boardSize - 1;
		bool reverseRow = false;

		// Create a map of position to player symbols
		vector<string> cellSymbols(boardSize, "");  // index 0 to boardSize-1

		for (Player* player : players)
		{
			int pos = player->getPosition();
			if (pos >= 0 && pos < boardSize)
			{
				cellSymbols[pos] += player->getSymbol();  // append symbol if multiple players at same cell
			}
		}

		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < 10; ++c)
			{
				int index = reverseRow ? (start - (9 - c)) : (start - c);
				string cell = to_string(index);

				// Append player symbol if present
				if (!cellSymbols[index].empty())
				{	cout << setw(6) << cellSymbols[index];
					cell += cellSymbols[index];
				}
				else
				{
					cout << setw(6) << "_";
				}


			}
			cout << endl;
			reverseRow = !reverseRow;
			start -= 10;
		}
	}

	~Board()
	{
		for (Cell *cell : grid)delete cell;
	}

};