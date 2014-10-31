#pragma once

#include "Card.h"

class Deck
{

public:

	Deck();
	~Deck();

	Card* getCard();
	void setCards(vector<Card*>);
	void shuffle();
	int getSize();

	vector<Card*> getCards();
	void print();
	void add(Card*);
	void clear();




	vector<Card*> cards;

protected:

	

};

