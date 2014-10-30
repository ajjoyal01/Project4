#pragma once

#include <iostream>
#include "Object.h"

class Card : public Object
{

public:

	Card();
	~Card();

	void print();

private:

	int value;
	string suit;
};

