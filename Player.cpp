#include "Player.h"

Player::Player() { cout << "Player생성자 호출" << endl; }

void Player::setCardInfoShape(string shape, int arrnum)
{
	cardinfo[arrnum].Shape = shape;
}

void Player::setCardInfoNumber(int number, int arrnum)
{
	cardinfo[arrnum].Number = number;
}

CardInfo Player::getCardInfo1()
{
	return cardinfo[0];
}

CardInfo Player::getCardInfo2()
{
	return cardinfo[1];
}

void Player::SetMoney(int money) { Money = money; }
int Player::getMoney() { return Money; }

void Player::setMyturn(int num) { MyTurn = num; }
int Player::getMyturn() { return MyTurn; }

void Player::setName(string name) { Name = name; }
string Player::getName() { return Name; }

void Player::SetDice(int dice) { Dice = dice; }
int Player::getDice(){ return Dice; }

void Player::setLandMoney(int landmoney) { LandMoney = landmoney; }

int Player::getLandMoney()
{
	return LandMoney;
}

void Player::setLandNum(int landnum)
{
	LandNum = landnum;
}

int Player::getLandNum()
{
	return LandNum;
}

Player::~Player() { cout << "Player소멸자 호출" << endl; }
