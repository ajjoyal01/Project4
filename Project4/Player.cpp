#include "Player.h"


Player::Player()
{
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
	deck.place(deckLocation.x,deckLocation.y,deckLocation.z);
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
	deckLocation = inLocation;
}

void Player::setDiscardLocation(vec3 inLocation)
{
	discardLocation = inLocation;
}

vec3 Player::getDeckLocation()
{
	return deckLocation;
}

vec3 Player::getDiscardLocation()
{
	return discardLocation;
}