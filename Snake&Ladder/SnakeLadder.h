#pragma once
#include "Dice.h"
#include "Player.h"
#include "Board.h"
#include <deque>
#include<iostream>
class SnakeLadder
{
private:
	deque<Player*>listPlayer;
	Board *board;
	Dice *dice;
	int boardSize;
public:
	SnakeLadder(deque<Player*>listPlayer, int boardSize, int diceCount): listPlayer(listPlayer), boardSize(boardSize)
	{

		board = new Board(boardSize );
		dice = new Dice(diceCount);
	}

	Board *getBoard()
	{
		return board;
	}
	Player *getCurrentPlayer()
	{
		return listPlayer.front();
	}

	void switchTurn()
	{
		Player *currentPlayer = getCurrentPlayer();
		listPlayer.pop_front();
		listPlayer.push_back(currentPlayer);
	}
	void startGame()
	{
		bool isGameOn = true;

		while (isGameOn)
		{
			board->Display(listPlayer);
			Player *currentPlayer = getCurrentPlayer();
			int rollDice = dice->rollDice();
			cout << currentPlayer->getName() << " " << currentPlayer->getSymbol() << "'s turn: " << rollDice;
			int currentPosition = currentPlayer->getPosition();
			currentPosition += rollDice;
			if (currentPosition >= boardSize)
				currentPosition = boardSize;

			Cell *currentCell = board->getCellAtPostion(currentPosition);
			Jump *jump = currentCell->getJump();

			if (jump->getStartJump() != -1)
			{
				cout << " " << ((jump->getJumpType() == Snake) ? "Snake" : "Ladder" );
				currentPosition = jump->getEndJump();
			}
			cout << ". CurrentPosition: " << currentPosition << endl;
			currentPlayer->setPosition(currentPosition);
			if (isWin(currentPlayer))
			{
				cout << currentPlayer->getName() << " Win!!!" << endl;
				return;
			}
			switchTurn();

		}
	}

	bool isWin(Player *currentPlayer)
	{
		if (currentPlayer->getPosition() >= boardSize - 1)return true;
		return false;
	}
	~SnakeLadder()
	{
		delete board;
		delete dice;
	}


};