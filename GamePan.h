#pragma once
#include "Library.h"
class Player;
class Card;
class Account;
class GamePan
{
private:
	Account* account;
	ofstream OutPut;
public:
	void Init();
	void PlayerTurn(Player* (&player), Card* (&card),
		int myturn, int& peoplegamemoney, int& cardposx,
		int maxhumans, int userplayer);
	void AITurn(Player* (&player), Card* (&card),
		int myturn, int& peoplegamemoney, int& cardposx, int carddecknum);
	void Comparison(Player* (&player), Card* (&card), int& peoplegamemoney,
		int battingMoney, int myturn, int cardposx);
	void KeyDownEvent();
	void Release();
};

