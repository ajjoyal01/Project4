#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>

#include "Card.h"
#include "Player.h"
#include "StandardDeck.h"

using namespace std;

class Game
{

public:

	Game();
	~Game();

	void init();
	
	

private:

	StandardDeck master;
	Player player1;
	Player player2;

	void initPlayers();
};

