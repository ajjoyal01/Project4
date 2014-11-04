#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

#include "PlayDeck.h"
#include "vmath.h"

using vmath::mat4;

class Player
{

public:

	Player();
	~Player();

	void setDeck(vector<Card*>);
	void printDeck();
	void recycleDiscard();
	int getDeckSize();
	void draw(Shader);
	void placeDeck();
	void placeDiscard();

	void setDeckLocation();
	void setDiscardLocation();

	void scale(float);
	void translate(float, float, float);
	void rotate(float, vmath::vec3);
	void updateCenter();

	void transformDecks(vmath::mat4);

	PlayDeck deck;
	PlayDeck discard;

	vec4 center;
	vec4 deckLocation;
	vec4 discardLocation;

private:

	

	
	mat4 transform;
	
};

