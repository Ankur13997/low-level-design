#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include "Game.h"
using namespace std;

int main()
{
	Player player1("ABC", X);
	Player player2("CDE", Y);
	deque<Player*>listPlayer;
	listPlayer.push_back(&player1);
	listPlayer.push_back(&player2);
	Game TicTacToe(3, listPlayer);
	TicTacToe.startGame();
	return 0;
}