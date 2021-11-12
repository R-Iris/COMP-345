/**
 * COMP 345: Advanced Program Design with C++
 * @file Part2Driver.cpp
 * @author Jason Patel
 * @version 12/11/2021
 */

#include <iostream>
#include <istream>
#include "../CommandProcessor/CommandProcessor.h"
#include "GameEngine.h"

using namespace std;

int main() {
	const int CARDS_IN_DECK = 52;

	// Instantiate Observer object
	Observer* _observer = new LogObserver();

	CommandProcessor* commandprocessor = new CommandProcessor(_observer);

	GameEngine* game = new GameEngine(_observer);
	game->setDeck(new Deck(CARDS_IN_DECK));

	State* start = game->newState("start");
	State* map_loaded = game->newState("map_loaded");
	State* map_validated = game->newState("map_validated");
	State* players_added = game->newState("players_added");
	State* assign_reinforcement = game->newState("assign_reinforcement");
	State* win = game->newState("win");
	State* end_game = game->newState("end_game");


	game->newTransition(start, map_loaded, "loadmap");
	game->newTransition(map_loaded, map_loaded, "loadmap");
	game->newTransition(map_loaded, map_validated, "validatemap");
	game->newTransition(map_validated, players_added, "addplayer");
	game->newTransition(players_added, players_added, "addplayer");
	game->newTransition(players_added, assign_reinforcement, "gamestart");
	game->newTransition(assign_reinforcement, win, "gameend");	//For testing purposes
	game->newTransition(win, start, "replay");
	game->newTransition(win, end_game, "quit");

	game->cmd_currentState = start;
	game->currentState = start;

	string answer;
	string file;

	cout << "Here, we read the commands that will be executed by startupPhase()" << endl;
	cout << "==================================================================" << endl << endl;
	cout << "Do you wish to accept commands from the console or read them from a file? " << '\n';

	cin >> answer;

	if (answer == "console") {
		cout << "Please enter a command" << '\n';
		while (!(commandprocessor->getExitProgram())) {
			commandprocessor->getCommand(game, commandprocessor);
		}
	}
	else if (answer == "file") {
		cout << "Which file do you wish to open? " << '\n';
		cin >> file;
	}

	// TESTING OF PART 2 BEGINS HERE
	game->startupPhase(commandprocessor);

	// Show effect of 'gamestart' command
	// Show turn order
	cout << endl;
	cout << "TURN ORDER (Shows that 'gamestart' command randomizes the turn order of players and the effect of the 'addplayer' command)" << endl;
	cout << "==========================================================================================================================" << endl;

	int i = 0;
	for (Player* p : game->players) {
		if (p->getName() != game->getNeutralPlayer()->getName()) {
			i++;
			cout << i << ") " << p->getName() << endl;
		}
	}

	// Show distribution of territories
	cout << endl;
	cout << "TERRITORY DISTRIBUTION" << endl;
	cout << "======================" << endl;

	for (Territory* t : game->map->getTerritories()) {
		if (game->getNeutralPlayer()->ownsTerritory(t)) {
			cout << "Territory " << t->getIndex() << " is neutral (no player owns it)." << endl;
		}

		else {
			for (Player* p : game->players) {
				if (p->ownsTerritory(t)) {
					cout << "Territory " << t->getIndex() << " is owned by player " << p->getName() << endl;
				}
			}
		}
	}

	cout << endl;

	// Show number of cards and armies for each player
	cout << "This next section shows that each player gets 50 armies and 2 cards from the deck." << endl;
	cout << "==================================================================================" << endl;

	for (Player* p : game->players) {
		if (p->getName() != game->getNeutralPlayer()->getName()) {
			cout << endl;
			cout << "Player " << p->getName() << " has " << p->getHand()->getCardsInHand().size() << " cards in their hand and " << p->getReinforcementPool() << " armies" << endl;
			cout << p->getName() << "'s cards are: " << endl;
			for (Card* c : p->getHand()->getCardsInHand()) {
				cout << "* " << c->getCardTypeName() << endl;
			}
		}
	}

	cout << endl;

	cout << "At the end of the startup phase, the game switches to first state in the play phase: assign_reinforcements." << endl;
	cout << "===========================================================================================================" << endl;
	cout << "Current state: " << game->currentState->stateName << endl;

	/// /////////////////
	delete game;
	delete commandprocessor;
	delete _observer;
	game = NULL;
	commandprocessor = NULL;
	_observer = NULL;
	/// /////////////////

	return 0;
}