#pragma once

#include "Card.h"

class Deck
{

public:

	Deck();
	~Deck();

	Card* getCard();
	void setCards(vector<Card*>);
	void shuffle();		// shuffle the deck to get random order
	int getSize();

	vector<Card*> getCards();
	void print();
	void add(Card*);
	void clear();
	void draw();
	void stack();	// stack deck vertically once in place
	void place(float,float,float);	// put deck in base spot on a player's field

	vector<Card*> cards;

protected:

	

};

