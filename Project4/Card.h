#pragma once

#include "vmath.h"

#include <iostream>
#include "Model.h"

class Card : public Model
{

public:

	Card();
	~Card();

	void print();

	void setValue(int);
	int getValue();
	void setSuit(string);
	void parseData();
	bool isFaceUp();
	void flip();

private:

	int value;
	string suit;

	bool faceUp;

	vmath::mat4 totalRotate;
};

