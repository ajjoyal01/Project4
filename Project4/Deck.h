#pragma once

#include "Card.h"

class Deck
{

public:

	Deck();
	~Deck();

	Card* getCard(int);
	void shuffle();
	int getSize();

	vector<Card*> getCards();

protected:

	vector<Card*> cards;

};

