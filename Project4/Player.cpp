#include "Player.h"


Player::Player()
{
	transform = mat4::identity();
	center = vec3(0, 0, 0);
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
}

void Player::placeDeck()
{
	deck.translate((center.x + deckLocation.x), (center.y + deckLocation.y), (center.z + deckLocation.z));
	deck.stack();
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

void Player::setDeckLocation(vec3 inLocation)
{
	deck.translate(inLocation.x, inLocation.y, inLocation.z);
}

void Player::setDiscardLocation(vec3 inLocation)
{
	discard.translate(inLocation.x - discard.center.x, inLocation.y - discard.center.y, inLocation.z - discard.center.z);
}

// Transformation Stuff
void Player::scale(float scaleFactor)
{
	// Translate to center
	vmath::mat4 translate1 = vmath::translate(0 - center.x, 0 - center.y, 0 - center.z);
	vmath::mat4 scale = vmath::scale(scaleFactor);
	vmath::mat4 translate2 = vmath::translate(center.x, center.y, center.z);

	transform = (translate2 * scale * translate1) * transform;
	updateCenter();

	transformDecks();
}

void Player::translate(float x, float y, float z)
{
	vmath::mat4 translate = vmath::translate(x, y, z);
	transform = translate * transform;

	updateCenter();

	transformDecks();
}

void Player::rotate(float angle, vmath::vec3 inAxis)
{
	// Translate to center
	vmath::mat4 translate1 = vmath::translate(0 - center.x, 0 - center.y, 0 - center.z);
	vmath::mat4 rotate = vmath::rotate(angle, inAxis);
	vmath::mat4 translate2 = vmath::translate(center.x, center.y, center.z);

	transform = (translate2 * rotate * translate1) * transform;
	updateCenter();

	transformDecks();
}

void Player::updateCenter()
{
	center.x = transform[3][0];
	center.y = transform[3][1];
	center.z = transform[3][2];
}

void Player::transformDecks()
{
	deck.updateTransform(transform);
	discard.updateTransform(transform);
}