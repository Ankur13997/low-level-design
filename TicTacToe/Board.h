#pragma once
#include "Player.h"
#include <string>
using namespace std;

class Board
{
private:
	int boardSize;
	vector<vector<char>>grid;
public:
	Board(int boardSize): boardSize(boardSize)
	{
		grid = vector<vector<char>>(boardSize, vector<char>(boardSize, '-'));
	}
	int getBoardSize()
	{
		return boardSize;
	}
	void DisplayBoard()
	{
		for (auto row : grid)
		{
			for (auto col : row)
				cout << col;
			cout << endl;
		}
	}
	bool isFull()
	{
		for (auto row : grid)
		{
			for (auto col : row)
			{
				if (col == '-')
					return false;
			}

		}
		return true;
	}

	bool isCellEmpty(int row, int col)
	{
		return grid[row][col] == '-';
	}
	void setCell(int row, int col, PlayerSymbol symbol)
	{
		if (isCellEmpty(row, col))
		{
			grid[row][col] = (symbol == X ) ? 'X' : 'Y';
		}

		return;
	}

	bool isWin(PlayerSymbol symbo)
	{
		char sym = (symbo == X) ? 'X' : 'Y';

		//row
		for (auto row : grid)
		{
			bool flag = true;

			for (auto col : row)
			{
				if (col != sym)
				{
					flag = false;
					break;
				}
			}
			if (flag)return true;
		}
		//col
		for (int col = 0; col < boardSize; col++)
		{
			bool flag = true;
			for (int row = 0; row < boardSize; row++)
			{
				if (grid[row][col] != sym)
				{
					flag = false;
					break;
				}
			}
			if (flag)return true;
		}

		//up diagonal
		bool flag = true;
		int r = 0, c = 0;
		while (r < boardSize && c < boardSize)
		{
			if (grid[r][c] != sym)
			{
				flag = false;
				break;
			}
			r++;
			c++;
		}
		if (flag)return true;

		//down diagonal
		flag = true;
		r = 0, c = boardSize - 1;
		while (r < boardSize && c >= 0)
		{
			if (grid[r][c] != sym)
			{
				flag = false;
				break;
			}
			r++;
			c--;
		}
		if (flag)return true;

		return false;
	}

};