#include <iostream>
#include <istream>
#include "CommandProcessor.h"
#include "../Game Engine/GameEngine.h"

using namespace std;

int main() {
	// Instantiate Observer object
	Observer* _observer = new LogObserver();

	CommandProcessor* commandprocessor = new CommandProcessor(_observer);

	GameEngine* game = new GameEngine(_observer);

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

	game->currentState = start;

	cout << "Please enter a command" << '\n';
	while (!(commandprocessor->getExitProgram())) {
		commandprocessor->getCommand(game);
	}

	cout << "\nAll commands: " << commandprocessor->getCommandList();
	cout << "\nValid commands: " << commandprocessor->getValidCommandList();

	/// /////////////////
	// delete game;
	delete commandprocessor;
	delete _observer;
	// game = NULL;
	commandprocessor = NULL;
	_observer = NULL;
	/// /////////////////

	return 0;
}