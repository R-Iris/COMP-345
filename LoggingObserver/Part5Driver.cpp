#include <iostream>
#include <vector>


#include "../Game Engine/GameEngine.h"
#include "../Map/Map.h"
#include "../CommandProcessor/CommandProcessor.h"
#include "../Orders/Orders.h"

int main()
{
    Observer* _obs = new LogObserver();
    /*CommandProcessor* _command_processor = new CommandProcessor(_obs);*/
	// GameEngine* _game = new GameEngine(_obs);

    // Instantiate Observer object
    //Observer* _game_observer = new LogObserver();
    // Instantiate GameEngine object
    //GameEngine* game = new GameEngine(_game_observer);
    GameEngine* game = new GameEngine(_obs);
    // Create a map from file and assign to this game instance
    string fileName = "C:/Other/Desk/Conc/COMP_345/Assignments/1/COMP-345/Game Engine/test.map";
    Map* map = MapLoader::createMapfromFile(fileName);
    //map->validate();
    //game->setMap(map);

    // Initializing states
    State* start = game->newState("start");
    State* map_loaded = game->newState("map_loaded");
    State* map_validated = game->newState("map_validated");
    State* players_added = game->newState("players_added");
    State* assign_reinforcement = game->newState("assign_reinforcement");
    State* issue_orders = game->newState("issue_orders");
    State* execute_orders = game->newState("execute_orders");
    State* win = game->newState("win");

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

    cout << "Adding new players..." << endl;
    // Add new players
    Player* p1 = new Player("P1", new Hand(), game);
    Player* p2 = new Player("P2", new Hand(), game);

    cout << "Adding territory..." << endl;
    auto* territory1 = new Territory();
    auto* territory2 = new Territory();


    p1->addOwnedTerritory(territory1);
    p2->addOwnedTerritory(territory2);
    territory1->setNumberOfArmies(20);



    cout << "Adding deploy order..." << endl;
    auto* deploy = new Deploy(p1, 10, territory1, game);
    auto* advance = new Advance(p1, 20, territory1, territory2, game);

    cout << "Adding deploy to orderList..." << endl;
    p1->getOrdersList()->addOrders(deploy);
    p1->getOrdersList()->addOrders(advance);

    cout << "Executing order..." << endl;
    deploy->execute();    

    cout << "Showing orderList.." << endl;
    cout << *p1->getOrdersList() << endl;

    

    cout << "Setting game players..." << endl;
    // Add players to game list
    game->players = {p1, p2};

    cout << "Changing current state..." << endl;
    // Initializing currentState
    game->currentState = players_added;
    // Announce current state
    cout << *game->currentState;

    // Execute start phase
    // game->startupPhase();
    game->changeState("gamestart");



    // call end() which deletes game and prints a message
    game->end();
    // delete game
    game = nullptr;
    // fix dangling pointer
    //game = nullptr;
    // deallocate observer object
    //delete _game_observer;
    // fix dangling pointer
    //_game_observer = nullptr;
    return 0;

	//string answer;
	//string fileName;

	//cout << "Do you wish to accept commands from the console or read them from a file? " << '\n';

	//cin >> answer;

	//if (answer == "console") {
	//	cout << "\nPlease enter a command" << '\n';

	//	while (!(_command_processor->getExitProgram())) {
	//		_command_processor->getCommand(_game, _command_processor);
	//	}

	//	cout << "\n\nAll commands: " << _command_processor->getCommandList();
	//	cout << "\nValid commands: " << _command_processor->getValidCommandList();

	//	delete _command_processor;
	//	_command_processor = NULL;
	//}
	//else if (answer == "file") {
	//	cout << "\nWhich file do you wish to open? " << '\n';

	//	cin >> fileName;

	//	FileLineReader* fileReader = new FileLineReader();
	//	fileReader->readLineFromFile("../CommandProcessor/" + fileName + ".txt"); // Problem finding files?

	//	FileCommandProcessorAdapter* filecmd = new FileCommandProcessorAdapter(fileReader, _obs);
	//	//filecmd->readCommand();

	//	while (!(_command_processor->getExitProgram())) {
	//		_command_processor->getCommand(_game, filecmd);
	//	}

	//	cout << "\n\nAll commands: " << _command_processor->getCommandList();
	//	cout << "\nValid commands: " << _command_processor->getValidCommandList();

	//	delete filecmd;
	//	delete fileReader;
	//	filecmd = NULL;
	//	fileReader = NULL;

	//}

	//delete _game;
    /*delete _command_processor;*/
    delete _obs;
	//_game = nullptr;
    /*_command_processor = nullptr;*/
    _obs = nullptr;
    return 0;
}