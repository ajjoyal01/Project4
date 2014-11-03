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

	void setDeckLocation(vec3);
	void setDiscardLocation(vec3);

	void scale(float);
	void translate(float, float, float);
	void rotate(float, vmath::vec3);
	void updateCenter();

	void transformDecks();

	PlayDeck deck;
	PlayDeck discard;

private:

	vec3 deckLocation;
	vec3 discardLocation;

	vec4 center;
	mat4 transform;
	
};

