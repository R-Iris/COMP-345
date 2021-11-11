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

	//State* start = game->newState("start");
	//State* map_loaded = game->newState("map_loaded");
	//State* map_validated = game->newState("map_validated");
	//State* players_added = game->newState("players_added");
	//State* assign_reinforcement = game->newState("assign_reinforcement");
	//State* win = game->newState("win");
	//State* end_game = game->newState("end_game");


	//game->newTransition(start, map_loaded, "loadmap");
	//game->newTransition(map_loaded, map_loaded, "loadmap");
	//game->newTransition(map_loaded, map_validated, "validatemap");
	//game->newTransition(map_validated, players_added, "addplayer");
	//game->newTransition(players_added, players_added, "addplayer");
	//game->newTransition(players_added, assign_reinforcement, "gamestart");
	//game->newTransition(assign_reinforcement, win, "gameend");	//For testing purposes
	//game->newTransition(win, start, "replay");
	//game->newTransition(win, end_game, "quit");

		// Initializing states
	State* start = game->newState("start");
	State* map_loaded = game->newState("map_loaded");
	State* map_validated = game->newState("map_validated");
	State* players_added = game->newState("players_added");
	State* assign_reinforcement = game->newState("assign_reinforcement");
	State* issue_orders = game->newState("issue_orders");
	State* execute_orders = game->newState("execute_orders");
	State* win = game->newState("win");
	State* end_game = game->newState("end_game");

	// Connecting states together
	game->newTransition(start, map_loaded, "loadmap");
	game->newTransition(map_loaded, map_loaded, "loadmap");
	game->newTransition(map_loaded, map_validated, "validatemap");
	game->newTransition(map_validated, players_added, "addplayer");
	game->newTransition(players_added, players_added, "addplayer");
	game->newTransition(players_added, assign_reinforcement, "gamestart");
	game->newTransition(assign_reinforcement, issue_orders, "issueorder");
	game->newTransition(issue_orders, issue_orders, "issueorder");
	game->newTransition(issue_orders, execute_orders, "issueordersend");
	game->newTransition(execute_orders, execute_orders, "execorder");
	game->newTransition(execute_orders, assign_reinforcement, "endexecorders");
	game->newTransition(execute_orders, win, "win");
	game->newTransition(win, start, "replay");
	game->newTransition(win, end_game, "quit");

	game->cmd_currentState = start;
	game->currentState = start;


	string answer;
	string secondAnswer;
	string fileName;

	cout << "Do you wish to accept commands from the console or read them from a file? " << '\n';

	cin >> answer;

	if (answer == "console") {
		cout << "\nPlease enter a command" << '\n';

		// While the user has not entered "quit", while the game has not started and while the game is ended
			//  && !(commandprocessor->getGameStart()) && !(commandprocessor->getGameEnd())
		while (!(commandprocessor->getExitProgram())) {
			if (commandprocessor->getGameStart()) {
				cout << "\nFor testing purposes, the game has started but is not shown. Please end the game manually.\n";
				cin >> secondAnswer;
				while (!(secondAnswer == "win")) {
					cin >> secondAnswer;
				}
			}
			commandprocessor->getCommand(game, commandprocessor);
		}

		cout << "\n\nAll commands: " << commandprocessor->getCommandList();
		cout << "\nValid commands: " << commandprocessor->getValidCommandList();

		delete commandprocessor;
		commandprocessor = NULL;
	}
	else if (answer == "file") {
		cout << "\nWhich file do you wish to open? " << '\n';

		cin >> fileName;

		FileLineReader* fileReader = new FileLineReader();
		fileReader->readLineFromFile(fileName);

		FileCommandProcessorAdapter* filecmd = new FileCommandProcessorAdapter(fileReader, _observer);
		//filecmd->readCommand();
		
		while (!(commandprocessor->getExitProgram())) {
			commandprocessor->getCommand(game, filecmd);
		}

		cout << "\n\nAll commands: " << commandprocessor->getCommandList();
		cout << "\nValid commands: " << commandprocessor->getValidCommandList();

		delete filecmd;
		delete fileReader;
		filecmd = NULL;
		fileReader = NULL;
		
	}

	/// /////////////////
	// delete game;
	delete _observer;
	// game = NULL;
	_observer = NULL;
	/// /////////////////

	return 0;
}

 