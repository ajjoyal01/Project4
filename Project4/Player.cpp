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

int Player::getDeckSize()
{
	return deck.getSize();
}
