#pragma once

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

private:

	int value;
	string suit;
};

