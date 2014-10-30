#pragma once

#include "Card.h"

class Deck
{

public:

	Deck();
	~Deck();

	Card* getCard(int);
	void setCards(vector<Card*>);
	void shuffle();
	int getSize();

	vector<Card*> getCards();
	void print();
	void add(Card*);
	void clear();

protected:

	vector<Card*> cards;

};

