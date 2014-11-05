#include "Card.h"


Card::Card()
{
	faceUp = false;
	totalRotate = 0;
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

void Card::parseData()
{
	// parses data of format 2_of_hearts.obj or queen_of_spades2.obj
	int lastSlash = name.find_last_of("/");

	if (lastSlash != -1)
		name.erase(name.begin(), name.begin() + lastSlash + 1);

	value = name.at(0) - '0';

	switch (name.at(0))
	{
	case '1':
		value = 10;
		break;
	case 'j':
		value = 11;
		break;
	case 'q':
		value = 12;
		break;
	case 'k':
		value = 13;
		break;
	case 'a':
		value = 14;
		break;
	default:
		break;
	}

	if (name.find("hearts") != -1)
		suit = "hearts";
	else if (name.find("diamonds") != -1)
		suit = "diamonds";
	else if (name.find("clubs") != -1)
		suit = "clubs";
	else if (name.find("spades") != -1)
		suit = "spades";
}

bool Card::isFaceUp()
{
	return faceUp;
}

void Card::flip()
{
	faceUp = !faceUp;
}