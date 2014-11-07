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
	
	initPlayers();

	origTarget1 = vmath::vec3(.5, 0, .5);
	origTarget2 = vmath::vec3(-.5, 0, -.5);

	tempTarget1 = origTarget1;
	tempTarget2 = origTarget2;
	
}

void Game::initPlayers()
{
	master.shuffle();

	// split the deck in half
	vector<Card*> temp1 = master.getCards();
	temp1.erase(temp1.begin() + 26, temp1.end());
	
	vector<Card*> temp2 = master.getCards();
	temp2.erase(temp2.begin(), temp2.begin() + 26);

	/*
	vector<Card*> ordered1;
	vector<Card*> ordered2;
	for (int i = 0;i < master.cards.size(); i++)
	{
		if (i % 2 == 0)
			ordered1.push_back(master.cards.at(i));
		else
			ordered2.push_back(master.cards.at(i));
	}*/
	
	// give each player half the deck
	player1.setDeck(temp1);
	player2.setDeck(temp2);

	player1.deck.translate(1.4, 0, 0);
	player2.deck.translate(1.4, 0, 0);
	player1.discard.translate(-1.4, 0, 0);
	player2.discard.translate(-1.4, 0, 0);

	player1.translate(0, 0, 1.4);
	player2.translate(0, 0, -1.4);
	
	player2.rotate((float)180, vmath::vec3(0, 1, 0));
	player1.deck.rotate(90, vmath::vec3(0, 1, 0));
	player2.deck.rotate(90, vmath::vec3(0, 1, 0));

	// once player sides are setup, lock in deck location value as the current center
	player1.setDeckLocation();
	player2.setDeckLocation();
	player1.setDiscardLocation();
	player2.setDiscardLocation();
	
	// place the decks at the designated start positions
	player1.placeDeck();
	player2.placeDeck();

	player1.deck.flip();
	player2.deck.flip();
}

void Game::playTurn1()
{
	handWinner = 0;

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

}
	
void Game::playTurn2()
{
	takePile(handWinner);

	tempTarget1 = origTarget1;
	tempTarget2 = origTarget2;

	checkReshuffle();

	outputStats();

	checkWinner();

	if (winner == 1)
	{
		cout << "Player 1 Wins!!\n";
	}
	else if (winner == 2)
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
	animateCardFlip();
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

	tempTarget1[0] += pile.at(0)->getWidth() * 1.2;
	tempTarget2[0] -= pile.at(0)->getWidth() * 1.2;

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
			tempTarget1[1] += master.cards.at(0)->getDepth();
			tempTarget2[1] += master.cards.at(0)->getDepth();
			tempTarget1[0] += master.cards.at(0)->getWidth() / 5;
			tempTarget2[0] -= master.cards.at(0)->getWidth() / 5;
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
	animateBurn();
}

void Game::takePile(int player)
{
	if (player == 1)
	{
		player1.discard.cards.insert(player1.discard.cards.end(), pile.begin(), pile.end());

		// *****animate discard pile move*****
		animateDiscard(1);
	}
	else
	{
		player2.discard.cards.insert(player2.discard.cards.end(), pile.begin(), pile.end());

		// *****animate discard pile move*****
		animateDiscard(2);
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

//****** ANIMATE MOVEMENTS*****

void Game::animateCardFlip()
{
	// translate
	pile.at(pile.size() - 2)->translate(tempTarget1[0] - pile.at(pile.size() - 2)->center.x,
		tempTarget1[1] - pile.at(pile.size() - 2)->center.y,
		tempTarget1[2] - pile.at(pile.size() - 2)->center.z);

	pile.at(pile.size() - 1)->translate(tempTarget2[0] - pile.at(pile.size() - 1)->center.x,
		tempTarget2[1] - pile.at(pile.size() - 1)->center.y,
		tempTarget2[2] - pile.at(pile.size() - 1)->center.z);

	pile.at(pile.size() - 2)->rotate((flip_factor)* 180, vmath::vec3(0, 0, 1));
	pile.at(pile.size() - 1)->rotate((flip_factor)* 180, vmath::vec3(0, 0, 1));
	//-----------------------------------------------

	//-----------------------------------------------
	// ** Last Step of Animation (Animation Complete) **
	//-----------------------------------------------
	if (animate_amount >= 100)
	{
		//animate_flip = false;
		animate_amount = 0;
		pile.at(pile.size() - 2)->flip();
		pile.at(pile.size() - 1)->flip();
	}

	pile.at(pile.size() - 2)->flip();
	pile.at(pile.size() - 1)->flip();

	
}

void Game::animateBurn()
{
	if (!animate_flip)
	{
		// translate

		// if beginning of action
		if (animate_amount == 0)
		{
			// push player 1's card onto the pile
			pile.push_back(player1.deck.cards.back());
			player1.deck.cards.pop_back();

			// push player 2's card onto the pile
			pile.push_back(player2.deck.cards.back());
			player2.deck.cards.pop_back();

			//tempTarget1[1] += master.cards.at(0)->getDepth();
			//tempTarget2[1] += master.cards.at(0)->getDepth();
			//tempTarget1[0] += master.cards.at(0)->getWidth() / 5;
			//tempTarget2[0] -= master.cards.at(0)->getWidth() / 5;

			dist_x_1 = (flip_factor)* (tempTarget1[0] - pile.at(pile.size() - 2)->center.x);
			dist_y_1 = (flip_factor)* (tempTarget1[1] - pile.at(pile.size() - 2)->center.y);
			dist_z_1 = (flip_factor)* (tempTarget1[2] - pile.at(pile.size() - 2)->center.z);
			dist_x_2 = (flip_factor)* (tempTarget2[0] - pile.at(pile.size() - 1)->center.x);
			dist_y_2 = (flip_factor)* (tempTarget2[1] - pile.at(pile.size() - 1)->center.y);
			dist_z_2 = (flip_factor)* (tempTarget2[2] - pile.at(pile.size() - 1)->center.z);

		}

		if (animate_amount < 50)
		{
			pile.at(pile.size() - 2)->translate(dist_x_1, dist_y_1 + .01, dist_z_1);
			pile.at(pile.size() - 1)->translate(dist_x_2, dist_y_2 + .01, dist_z_2);
		}
		else
		{
			pile.at(pile.size() - 2)->translate(dist_x_1, dist_y_1 - .01, dist_z_1);
			pile.at(pile.size() - 1)->translate(dist_x_2, dist_y_2 - .01, dist_z_2);
		}

		animate_amount++;

		if (animate_amount >= 100)
		{
			animate_burn = false;
			animate_amount = 0;

			tempTarget1[1] += master.cards.at(0)->getDepth();
			tempTarget2[1] += master.cards.at(0)->getDepth();
			tempTarget1[0] += master.cards.at(0)->getWidth() / 5;
			tempTarget2[0] -= master.cards.at(0)->getWidth() / 5;

			actionQueue.pop();
		}

		glutPostRedisplay();
	}
}

void Game::animateDiscard(int player)
{
	if (player == 1)
	{
		for (int i = 0; i < pile.size(); i++)
		{
			if (!pile.at(i)->isFaceUp())
			{
				pile.at(i)->rotate(180, vmath::vec3(0, 0, 1));
				pile.at(i)->flip();
			}

			if (!pile.at(pile.size() - 1)->isFaceUp())
			{
				pile.at(pile.size() - 1)->rotate(flip_factor * 180, vmath::vec3(0, 0, 1));
			}

			pile.at(pile.size() - 1)->translate(dist_x_1, dist_y_1, dist_z_1);

			animate_amount++;

			if (animate_amount >= 100)
			{
				animate_amount = 0;

				if (!pile.at(pile.size() - 1)->isFaceUp())
				{
					pile.at(pile.size() - 1)->flip();
				}

				discardTarget1[1] += pile.at(pile.size() - 1)->getDepth();
				pile.pop_back();
			}

			glutPostRedisplay();
		}

		player1.discard.stack();
	}
	else
	{
		for (int i = 0; i < pile.size(); i++)
		{
			if (!pile.at(i)->isFaceUp())
			{
				pile.at(i)->rotate(180, vmath::vec3(0, 0, 1));
				pile.at(i)->flip();
			}

			pile.at(i)->translate(player2.discardLocation.x - pile.at(i)->center.x,
				player2.discardLocation.y - pile.at(i)->center.y,
				player2.discardLocation.z - pile.at(i)->center.z);
		}

	// on completion of animation
	if (pile.size() == 0)
	{
		//animate_discard = false;
		animate_complete = true;
		actionQueue.pop();

		tempTarget1 = origTarget1;
		tempTarget2 = origTarget2;

		checkReshuffle();

		outputStats();

		checkWinner();

		if (winner == 1)
		{
			cout << "Player 1 Wins!!\n";
		}
		else if (winner == 2)
		{
			cout << "Player 2 Wins!!\n";
		}
	}
}

void Game::animateDeckReset(int player)
{
	for (int i = 0; i < player1.discard.cards.size(); i++)
	{

	}
}