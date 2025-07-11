#include<bits/stdc++.h>
#include "SnakeLadder.h"
using namespace std;

int main()
{

	Player player1("ABC", 'X');
	Player player2("DEF", 'Y');
	deque<Player*>listPlayer = {&player1, &player2};
	SnakeLadder snake_and_ladder(listPlayer, 100, 1);
	// Add sample ladders
	Jump* ladder1 = new Jump();
	ladder1->setJump(3, 22, Ladder);  // From cell 3 to 22
	snake_and_ladder.getBoard()->getCellAtPostion(3)->setJump(ladder1);

	Jump* ladder2 = new Jump();
	ladder2->setJump(5, 8, Ladder);
	snake_and_ladder.getBoard()->getCellAtPostion(5)->setJump(ladder2);

	// Add sample snakes
	// Jump* snake1 = new Jump();
	// snake1->setJump(97, 12, Snake);
	// snake_and_ladder.getBoard()->getCellAtPostion(97)->setJump(snake1);

	Jump* snake2 = new Jump();
	snake2->setJump(99, 21, Snake);
	snake_and_ladder.getBoard()->getCellAtPostion(99)->setJump(snake2);


	snake_and_ladder.startGame();

	return 0;
}