#pragma once
#include "library.h"

class Player
{
private:
	CardInfo cardinfo[2];
	int Money;
	int MyTurn;
	string Name;
	int LandMoney;
	int LandNum;
	int Dice{ 0 };
public:
	Player();
	void setCardInfoShape(string shape, int arrnum);
	void setCardInfoNumber(int number, int arrnum);
	CardInfo getCardInfo1();
	CardInfo getCardInfo2();
	void SetMoney(int money);
	int getMoney();
	void setMyturn(int num);
	int getMyturn();
	void setName(string name);
	string getName();
	void SetDice(int dice);
	int getDice();
	void setLandMoney(int landmoney);
	int getLandMoney();
	void setLandNum(int landnum);
	int getLandNum();
	~Player();
};

