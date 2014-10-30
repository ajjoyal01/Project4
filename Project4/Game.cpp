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
	//master.shuffle();

	vector<Card*> temp1 = master.getCards();
	temp1.erase(temp1.begin() + 26, temp1.end());
	
	vector<Card*> temp2 = master.getCards();
	temp2.erase(temp2.begin(), temp2.begin() + 26);
	
	player1.setDeck(temp1);
	player2.setDeck(temp2);

	//player1.printDeck();

	cout << endl;

	//player2.printDeck();

	player1.recycleDiscard();

}