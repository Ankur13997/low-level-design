#pragma once
#include "Board.h"
#include<deque>
#include <iostream>
using namespace std;

class Game
{
private:
	Board *board;
	deque<Player*>listPlayer;
public:
	Game(int boardSize, deque<Player*>&listPlayer): listPlayer(listPlayer)
	{
		board = new Board(boardSize);
	}

	Player* getCurrentPlayer()
	{
		return listPlayer.front();
	}
	void switchTurn()
	{

		Player* currentPlayer = getCurrentPlayer();
		listPlayer.pop_front();
		listPlayer.push_back(currentPlayer);
	}

	bool isValid(int row, int col)
	{
		if ( row >= 0 && row < board->getBoardSize() && col >= 0 && col < board->getBoardSize() && board->isCellEmpty(row, col) )
		{
			return true;
		}
		cout << "Invalid move. Try again !!!" << endl;
		return false;
	}

	void startGame()
	{
		board->DisplayBoard();
		while (!board->isFull())
		{
			int row, col;
			Player *currentPlayer = getCurrentPlayer();
			cout << currentPlayer->getPlayerName() << " (" << currentPlayer->getSymbol() << "): Give Input row and col (r,c)" << endl;
			cin >> row >> col;
			if (isValid(row, col))
			{
				board->setCell(row, col, currentPlayer->getSymbol());
			}
			else
				continue;
			board->DisplayBoard();
			if (board->isWin(currentPlayer->getSymbol()))
			{
				cout << currentPlayer->getPlayerName() << " Wins !!!" << endl;
				return;
			}
			switchTurn();

		}
		cout << "Game Tie !!!" << endl;
		return;

	}
};