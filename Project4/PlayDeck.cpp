#include "PlayDeck.h"


PlayDeck::PlayDeck()
{
	cards.clear();
}


PlayDeck::~PlayDeck()
{

}

// shuffles cards
void PlayDeck::shuffle()
{
	// temporary new set of cards
	vector<Card*> temp;

	// while there are still cards in the deck "cards"
	while (cards.size() > 0)
	{
		// get a random number between 0 and cards.size
		int random = rand() % cards.size();

		// add the random card to temp
		temp.push_back(cards.at(random));

		// erase the card from cards
		cards.erase(cards.begin() + random);
	}

	// set cards to temp, the shuffled set of cards
	cards = temp;
}

// gets size of the deck
int PlayDeck::getSize()
{
	return cards.size();
}