#include "Card.h"


Card::Card()
{
}


Card::~Card()
{
}

void Card::print()
{
	cout << value << " of " + suit << endl;
}

void Card::setValue(int inVal)
{
	value = inVal;
}

int Card::getValue()
{
	return value;
}

void Card::setSuit(string inSuit)
{
	suit = inSuit;
}