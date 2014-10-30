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