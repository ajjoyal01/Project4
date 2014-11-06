#include "StandardDeck.h"


StandardDeck::StandardDeck()
{
}

void StandardDeck::init()
{
	// setup 52 cards
	string filename = "Models/cardFileNames.txt";

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
		card->init("Models/" + line);
		card->parseData();
		cards.push_back(card);
	}


	/*
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2; j < 15; j++)
		{
			Card* card = new Card();
			card->init("cardTest.obj");
			card->setValue(j);

			switch (i)
			{
			case 0:
				card->setSuit("Hearts");
				break;
			case 1:
				card->setSuit("Diamonds");
				break;
			case 2:
				card->setSuit("Spades");
				break;
			case 3:
				card->setSuit("Clubs");
				break;
			default:
				cout << "ERROR\n";
				break;
			}
			
			cards.push_back(card);
		}
	}*/
}

void StandardDeck::setTexture(Texture* tex)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->setTexture(tex);
	}
}

StandardDeck::~StandardDeck()
{
}
