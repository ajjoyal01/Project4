#include "Deck.h"


Deck::Deck()
{
}


Deck::~Deck()
{
}


Card* Deck::getCard()
{
	return cards.back();
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

void Deck::draw()
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->draw();
	}
}

void Deck::stack()
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->translate(0, .012 * i, 0);
		int angle = rand() % 3;
		int sign = rand() % 3 - 1;
		cards.at(i)->rotate(angle * sign, vmath::vec3(0, 1, 0));
	}
}

void Deck::place(float x,float y,float z)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->translate(cards.at(i)->center.x - x, cards.at(i)->center.y - y, cards.at(i)->center.z - z);
	}
}