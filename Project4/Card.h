#pragma once

#include <iostream>
#include "Object.h"

class Card : public Object
{

public:

	Card();
	~Card();

	void print();

	void setValue(int);
	int getValue();
	void setSuit(string);
	void parseData();

private:

	int value;
	string suit;
};

