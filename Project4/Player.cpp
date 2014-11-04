#include "Player.h"


Player::Player()
{
	transform = mat4::identity();
	center = vec4(0, 0, 0, 1);
}

Player::~Player()
{
}

void Player::setDeck(vector<Card*> inCards)
{
	deck.setCards(inCards);
}

void Player::printDeck()
{
	deck.print();
}

void Player::recycleDiscard()
{
	deck = discard;
	discard.clear();
	deck.shuffle();

	for (int i = 0; i < deck.cards.size(); i++)
	{
		if (!deck.cards.at(i)->isFaceUp())
		{
			deck.cards.at(i)->rotate(180, vmath::vec3(0, 0, 1));
			deck.cards.at(i)->flip();
		}
	}
	placeDeck();
}

void Player::placeDeck()
{
	deck.translate(deckLocation.x - deck.center.x, deckLocation.y - deck.center.y, deckLocation.z - deck.center.z);
	deck.stack();
}

void Player::placeDiscard()
{
	discard.translate(discardLocation.x - deck.center.x, discardLocation.y - deck.center.y, discardLocation.z - deck.center.z);
	discard.stack();
}

int Player::getDeckSize()
{
	return deck.getSize();
}

void Player::draw(Shader shader)
{
	deck.draw(shader);
	discard.draw(shader);
}

void Player::setDeckLocation()
{
	deckLocation = deck.center;
}

void Player::setDiscardLocation()
{
	discardLocation = discard.center;
}

// Transformation Stuff
void Player::scale(float scaleFactor)
{
	// Translate to center
	vmath::mat4 translate1 = vmath::translate(0 - center.x, 0 - center.y, 0 - center.z);
	vmath::mat4 scale = vmath::scale(scaleFactor);
	vmath::mat4 translate2 = vmath::translate(center.x, center.y, center.z);

	scale = (translate2 * scale * translate1);
	transform = scale * transform;
	updateCenter();

	transformDecks(scale);
}

void Player::translate(float x, float y, float z)
{
	vmath::mat4 translate = vmath::translate(x, y, z);
	transform = translate * transform;

	updateCenter();

	transformDecks(translate);
}

void Player::rotate(float angle, vmath::vec3 inAxis)
{
	// Translate to center
	vmath::mat4 translate1 = vmath::translate(0 - center.x, 0 - center.y, 0 - center.z);
	vmath::mat4 rotate = vmath::rotate(angle, inAxis);
	vmath::mat4 translate2 = vmath::translate(center.x, center.y, center.z);

	rotate = (translate2 * rotate * translate1);
	transform = rotate * transform;
	updateCenter();

	transformDecks(rotate);
}

void Player::updateCenter()
{
	center.x = transform[3][0];
	center.y = transform[3][1];
	center.z = transform[3][2];
}

void Player::transformDecks(vmath::mat4 inTransform)
{
	deck.updateTransform(inTransform);
	discard.updateTransform(inTransform);
}