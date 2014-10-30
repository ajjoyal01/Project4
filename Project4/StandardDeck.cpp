#include "StandardDeck.h"


StandardDeck::StandardDeck()
{
	// setup 52 cards
	string filename = "cardObjectFiles.txt";

	ifstream in(filename, ios::in);

	if (!in)
	{
		cerr << "Cannot open " << filename << endl;
		exit(1);
	}

	string line;

	while (getline(in, line) && cards.size() < NUM_CARDS)
	{
		Card* card = new Card();
		card->init(line);
		cards.push_back(card);
	}
	
}


StandardDeck::~StandardDeck()
{
}
