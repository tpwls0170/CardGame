#pragma once
#include "Library.h"
class Player;
class Account
{
private:
public:
	void Choice(Player* (&player),int MaxHumans,int userplayer,ofstream& output);
	void MoneyLend(Player* (&player), int select,
		int userplayer,int moneyselect, ofstream& output);
};

