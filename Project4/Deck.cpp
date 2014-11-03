#include "Deck.h"


Deck::Deck()
{
	transform = mat4::identity();
	center = vec3(0, 0, 0);
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

void Deck::draw(Shader shader)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->draw(shader);
	}
}

void Deck::stack()
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->translate(0, CARD_DEPTH * i, 0);
		int angle = rand() % 5;
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

// Transformation Stuff
void Deck::scale(float scaleFactor)
{
	// Translate to center
	vmath::mat4 translate1 = vmath::translate(0 - center.x, 0 - center.y, 0 - center.z);
	vmath::mat4 scale = vmath::scale(scaleFactor);
	vmath::mat4 translate2 = vmath::translate(center.x, center.y, center.z);

	transform = (translate2 * scale * translate1) * transform;
	updateCenter();

	transformCards();
}

void Deck::translate(float x, float y, float z)
{
	vmath::mat4 translate = vmath::translate(x, y, z);
	transform = translate * transform;

	updateCenter();

	transformCards();
}

void Deck::rotate(float angle, vmath::vec3 inAxis)
{
	// Translate to center
	vmath::mat4 translate1 = vmath::translate(0 - center.x, 0 - center.y, 0 - center.z);
	vmath::mat4 rotate = vmath::rotate(angle, inAxis);
	vmath::mat4 translate2 = vmath::translate(center.x, center.y, center.z);

	transform = (translate2 * rotate * translate1) * transform;
	updateCenter();

	transformCards();
}

void Deck::updateCenter()
{
	center.x = transform[3][0];
	center.y = transform[3][1];
	center.z = transform[3][2];
}

void Deck::transformCards()
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->updateTransform(transform);
	}
}

void Deck::updateTransform(vmath::mat4 inTransform)
{
	transform = inTransform * transform;

	updateCenter();
	transformCards();
}