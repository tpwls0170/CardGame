#pragma 
#include "Library.h"

class Card
{
private:
	CardInfo cardinfo;
	string Shape;
	int Number;
public:
	void setCardInfoShape(string shape);
	void setCardInfoNumber(int number);
	CardInfo getCardInfo();
};