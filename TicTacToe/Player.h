#pragma once
#include<string>
#include "PlayerSymbol.h"
using namespace std;

class Player
{
private:
	string playerName;
	PlayerSymbol symbol;
public:
	Player(string playerName, PlayerSymbol symbol):
		playerName(playerName), symbol(symbol) {}

	PlayerSymbol getSymbol()
	{
		return symbol;
	}
	string getPlayerName()
	{
		return playerName;
	}

};