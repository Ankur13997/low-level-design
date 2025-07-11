#pragma once

class Dice
{
private:
	int diceCount;
public:
	Dice(int diceCount): diceCount(diceCount)
	{
		srand(time(0));
	}

	int rollDice()
	{

		int totalSum = 0;
		for (int count = 0; count < diceCount; count++)
		{
			totalSum += 1 + rand() % 6;
		}
		return totalSum;
	}
};