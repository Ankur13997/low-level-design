#pragma once
#include<string>
using namespace std;

class Player
{
private:
	string name;
	int currentPosition;
	char symbol;
public:
	Player(string name, char symbol): symbol(symbol), name(name)
	{
		currentPosition = -1;
	}
	char getSymbol()
	{
		return symbol;
	}
	string getName()
	{
		return name;
	}
	void setPosition(int index)
	{
		currentPosition = index;
	}
	int getPosition()
	{
		return currentPosition;
	}

};