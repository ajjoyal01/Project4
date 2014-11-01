#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

#include "Deck.h"
#include "Card.h"

#define NUM_CARDS 52

class StandardDeck : public Deck
{

public:

	StandardDeck();
	~StandardDeck();
	void init();

	Card* getCard(int);

private:

	
};

