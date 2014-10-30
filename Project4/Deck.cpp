#include "Deck.h"


Deck::Deck()
{
}


Deck::~Deck()
{
}


Card* Deck::getCard(int index)
{
	return cards[index];
}

// shuffles cards
void Deck::shuffle()
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

vector<Card*> Deck::getCards()
{
	return cards;
}

int Deck::getSize()
{
	return cards.size();
}

void Deck::setCards(vector<Card*> inCards)
{
	cards = inCards;
}

void Deck::print()
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards[i]->print();
	}
}

void Deck::add(Card* newCard)
{
	cards.push_back(newCard);
}

void Deck::clear()
{
	cards.clear();
}