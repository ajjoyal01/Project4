#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <time.h>
#include <queue>

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
	void getHandWinner();
	void war();
	void burn();
	void takePile();
	void checkReshuffle();
	void outputStats();
	void checkWinner();
	int getWinner();
	void draw(Shader);

	void animateCardFlip();
	void animateBurn();
	void animateDiscard();
	void animateDeckReset(int);

	void animateTurn();
	void setAnimateFlip();
	bool isAnimationComplete();
	void setAnimationComplete(bool);
	bool isFlipComplete();

	StandardDeck master;

private:

	Player player1;
	Player player2;

	vector<Card*> pile;

	void initPlayers();

	vmath::vec3 origTarget1;
	vmath::vec3 origTarget2;

	vmath::vec3 tempTarget1;
	vmath::vec3 tempTarget2;

	vmath::vec3 discardTarget1;
	vmath::vec3 discardTarget2;

	int winner;
	int handWinner;


	int animate_amount;		// used to track amount cards have been rotated (flipped)
	//float flip_time;		// used to modify speed of animation
	float flip_factor;		// used to adjust speed of animation
	bool animate_complete;		// determines that we should animate

	bool animate_flip;
	bool done_flip;
	bool animate_burn;
	bool animate_discard;

	float dist_x_1;
	float dist_y_1;
	float dist_z_1;
	float dist_x_2;
	float dist_y_2;
	float dist_z_2;

	queue<int> actionQueue;

	enum{ FLIP, BURN, DISCARD };
};

