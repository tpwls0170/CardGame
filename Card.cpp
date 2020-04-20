#include "Card.h"

void Card::setCardInfoShape(string shape)
{
	cardinfo.Shape = shape;
}

void Card::setCardInfoNumber(int number)
{
	cardinfo.Number = number;
}

CardInfo Card::getCardInfo()
{
	return cardinfo;
}

