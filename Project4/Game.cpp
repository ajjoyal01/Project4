#include "Game.h"

Game::Game()
{
	winner = 0;
}

Game::~Game()
{
}

void Game::init()
{
	master.init();
	master.cards.at(0)->calculateDimentions();
	initPlayers();
}

void Game::initPlayers()
{
	master.shuffle();

	vector<Card*> temp1 = master.getCards();
	temp1.erase(temp1.begin() + 26, temp1.end());
	
	vector<Card*> temp2 = master.getCards();
	temp2.erase(temp2.begin(), temp2.begin() + 26);
	
	player1.setDeck(temp1);
	player2.setDeck(temp2);

	player1.setDeckLocation(vec3(1, 0, 0));
	player2.setDeckLocation(vec3(1, 0, 0));

	//player1.translate(0, 0, 1);
	player2.rotate(180, vmath::vec3(0, 1, 0));
	//player2.translate(0, 0, -1);
	
	//player1.deck.rotate(180, vmath::vec3(0, 1, 0));

	player1.placeDeck();
	player2.placeDeck();
}

void Game::playTurn()
{
	int handWinner = 0;

	cout << "Hand:\n";
	do
	{
		flipCards();

		handWinner = getHandWinner();

		if (handWinner == 0)
		{
			war();
		}

		checkReshuffle();

	} while (handWinner == 0 && winner == 0);

	takePile(handWinner);

	checkReshuffle();

	outputStats();

	checkWinner();

	if (winner == 1)
	{
		cout << "Player 1 Wins!!\n";
	}
	else if(winner == 2)
	{
		cout << "Player 2 Wins!!\n";
	}
}

void Game::flipCards()
{
	// push player 1's card onto the pile
	pile.push_back(player1.deck.cards.back());
	pile.back()->print();
	player1.deck.cards.pop_back();

	// push player 2's card onto the pile
	pile.push_back(player2.deck.cards.back());
	pile.back()->print();
	player2.deck.cards.pop_back();

	// *****animate card flips*****
}

int Game::getHandWinner()
{
	if (pile.at(pile.size() - 1)->getValue() < pile.at(pile.size() - 2)->getValue())
	{
		cout << "Hand Winner: 1\n";
		return 1;
	}
	else if (pile.at(pile.size() - 1)->getValue() > pile.at(pile.size() - 2)->getValue())
	{
		cout << "Hand Winner: 2\n";
		return 2;
	}

	return 0;
}

void Game::war()
{
	cout << "WAR!!!\n";
	int warSize;

	checkWinner();

	if (winner == 0)
	{
		if (player1.deck.cards.size() + player1.discard.cards.size() > player2.deck.cards.size() + player2.discard.cards.size())
		{
			warSize = player2.deck.cards.size() + player2.discard.cards.size() - 1;
		}
		else
		{
			warSize = player1.deck.cards.size() + player1.discard.cards.size() - 1;
		}
	
		for (int i = 0; i < 3 && i < warSize; i++)
		{
			checkReshuffle();
			burn();
			
		}
	}
}

void Game::burn()
{
	cout << "Burn\n";
	// push player 1's card onto the pile
	pile.push_back(player1.deck.cards.back());
	player1.deck.cards.pop_back();

	// push player 2's card onto the pile
	pile.push_back(player2.deck.cards.back());
	player2.deck.cards.pop_back();

	// *****animate card burns*****
}

void Game::takePile(int player)
{
	if (player == 1)
	{
		player1.discard.cards.insert(player1.discard.cards.end(), pile.begin(), pile.end());

		// *****animate discard pile move*****
	}
	else
	{
		player2.discard.cards.insert(player2.discard.cards.end(), pile.begin(), pile.end());

		// *****animate discard pile move*****
	}

	pile.clear();

	
}

void Game::checkReshuffle()
{
	if (player1.getDeckSize() == 0)
	{
		player1.recycleDiscard();
	}
	if (player2.getDeckSize() == 0)
	{
		player2.recycleDiscard();
	}
}

void Game::outputStats()
{
	cout << "-----------------------------------------------\n"
		<< "Player\tDeck\tDiscard\n"
		<< "-----------------------------------------------\n"
		<< "1\t" << player1.deck.cards.size() << "\t" << player1.discard.cards.size()
		<< "\n2\t" << player2.deck.cards.size() << "\t" << player2.discard.cards.size()
		<< "\n-----------------------------------------------\n" << endl;
}

void Game::checkWinner()
{
	if (player1.deck.cards.size() + player1.discard.cards.size() == 0)
	{
		winner = 2;
	}
	else if (player2.deck.cards.size() + player2.discard.cards.size() == 0)
	{
		winner = 1;
	}
}

int Game::getWinner()
{
	return winner;
}

void Game::draw(Shader shader)
{
	
	player1.draw(shader);
	player2.draw(shader);

	for (int i = 0; i < pile.size(); i++)
	{
		pile.at(i)->draw(shader);
	}

	//master.cards.at(0)->draw(shader);
}