#include "Game.h"

Game::Game()
{
}


Game::~Game()
{
}

void Game::init()
{
	initPlayers();
}

void Game::initPlayers()
{
	master.shuffle();

	vector<Card*> temp1 = master.getCards();
	temp1.erase(temp1.begin(), temp1.begin() + 26);
	vector<Card*> temp2 = master.getCards();
	temp2.erase(temp2.begin() + 26, temp2.end());
	
	player1.setDeck(temp1);
	player2.setDeck(temp2);

	player1.printDeck();
	player2.printDeck();

}