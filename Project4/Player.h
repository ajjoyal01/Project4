#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

#include "PlayDeck.h"

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
	vec3 getDeckLocation();
	vec3 getDiscardLocation();

	PlayDeck deck;
	PlayDeck discard;

private:

	vec3 deckLocation;
	vec3 discardLocation;
	
};

