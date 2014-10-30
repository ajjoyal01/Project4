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

private:

	PlayDeck deck;
	PlayDeck discard;
};

