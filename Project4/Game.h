#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>

#include "vmath.h"

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
	void playTurn1();
	void playTurn2();
	void flipCards();
	int getHandWinner();
	void war();
	void burn();
	void takePile(int);
	void checkReshuffle();
	void outputStats();
	void checkWinner();
	int getWinner();
	void draw(Shader);

	void animateCardFlip();
	void animateBurn();
	void animateDiscard(int);
	void animateDeckReset(int);
	
private:

	StandardDeck master;
	Player player1;
	Player player2;

	vector<Card*> pile;

	void initPlayers();

	vmath::vec3 origTarget1;
	vmath::vec3 origTarget2;

	vmath::vec3 tempTarget1;
	vmath::vec3 tempTarget2;

	int winner;
	int handWinner;
};

