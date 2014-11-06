#pragma once

#include "Card.h"
#include "vmath.h"

#define CARD_WIDTH .7
#define CARD_HEIGHT .45
#define CARD_DEPTH .002

using vmath::mat4;

class Deck
{

public:

	Deck();
	~Deck();

	Card* getCard();
	void setCards(vector<Card*>);
	void shuffle();		// shuffle the deck to get random order
	int getSize();

	vector<Card*> getCards();
	void print();
	void add(Card*);
	void clear();
	void draw(Shader);
	void stack();	// stack deck vertically once in place
	void place(float,float,float);	// put deck in base spot on a player's field
	void flip();

	void scale(float);
	void translate(float, float, float);
	void rotate(float, vmath::vec3);
	void updateCenter();

	void transformCards(vmath::mat4);
	void updateTransform(vmath::mat4);

	vector<Card*> cards;

	vec4 center;
	mat4 transform;

protected:

	

};

