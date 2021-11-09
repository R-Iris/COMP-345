#include <iostream>
#include <vector>


#include "../Game Engine/GameEngine.h"
#include "../Map/Map.h"
#include "../CommandProcessor/CommandProcessor.h"
#include "../Orders/Orders.h"

int main()
{
    Observer* _obs = new LogObserver();
    CommandProcessor* _command_processor = new CommandProcessor(_obs);
	GameEngine* _game = new GameEngine(_obs);

	State* start = _game->newState("start");
	State* map_loaded = _game->newState("map_loaded");
	State* map_validated = _game->newState("map_validated");
	State* players_added = _game->newState("players_added");
	State* assign_reinforcement = _game->newState("assign_reinforcement");
	State* win = _game->newState("win");
	State* end_game = _game->newState("end_game");


	_game->newTransition(start, map_loaded, "loadmap");
	_game->newTransition(map_loaded, map_loaded, "loadmap");
	_game->newTransition(map_loaded, map_validated, "validatemap");
	_game->newTransition(map_validated, players_added, "addplayer");
	_game->newTransition(players_added, players_added, "addplayer");
	_game->newTransition(players_added, assign_reinforcement, "gamestart");
	_game->newTransition(assign_reinforcement, win, "gameend");	//For testing purposes
	_game->newTransition(win, start, "replay");
	_game->newTransition(win, end_game, "quit");


	string answer;
	string fileName;

	cout << "Do you wish to accept commands from the console or read them from a file? " << '\n';

	cin >> answer;

	if (answer == "console") {
		cout << "\nPlease enter a command" << '\n';

		while (!(_command_processor->getExitProgram())) {
			_command_processor->getCommand(_game, _command_processor);
		}

		cout << "\n\nAll commands: " << _command_processor->getCommandList();
		cout << "\nValid commands: " << _command_processor->getValidCommandList();

		delete _command_processor;
		_command_processor = NULL;
	}
	else if (answer == "file") {
		cout << "\nWhich file do you wish to open? " << '\n';

		cin >> fileName;

		FileLineReader* fileReader = new FileLineReader();
		fileReader->readLineFromFile("../CommandProcessor/" + fileName + ".txt"); // Problem finding files?

		FileCommandProcessorAdapter* filecmd = new FileCommandProcessorAdapter(fileReader, _obs);
		//filecmd->readCommand();

		while (!(_command_processor->getExitProgram())) {
			_command_processor->getCommand(_game, filecmd);
		}

		cout << "\n\nAll commands: " << _command_processor->getCommandList();
		cout << "\nValid commands: " << _command_processor->getValidCommandList();

		delete filecmd;
		delete fileReader;
		filecmd = NULL;
		fileReader = NULL;

	}

	delete _game;
    delete _command_processor;
    delete _obs;
	_game = nullptr;
    _command_processor = nullptr;
    _obs = nullptr;
    return 0;
}