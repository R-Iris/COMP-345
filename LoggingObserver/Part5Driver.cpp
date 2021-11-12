#include <iostream>


#include "../Game Engine/GameEngine.h"
#include "../Map/Map.h"
#include "../CommandProcessor/CommandProcessor.h"
#include "../Orders/Orders.h"

int main()
{
    // Instantiate Observer object
    Observer* _obs = new LogObserver();
    // Instatiate CommandProcessor object
    CommandProcessor* commandprocessor = new CommandProcessor(_obs);
    // Instantiate GameEngine object
    GameEngine* game = new GameEngine(_obs);
    // Create a map from file and assign to this game instance
    string fileName = "COMP-345/Map/Assets/test.map";

    // Instantiating states in the GameEngine
    State* start = game->newState("start");
    State* map_loaded = game->newState("map_loaded");
    State* map_validated = game->newState("map_validated");
    State* players_added = game->newState("players_added");
    State* assign_reinforcement = game->newState("assign_reinforcement");
    State* win = game->newState("win");
    State* end_game = game->newState("end_game");

    // Instantiating transitions in the GameEngine
    game->newTransition(start, map_loaded, "loadmap");
    game->newTransition(map_loaded, map_loaded, "loadmap");
    game->newTransition(map_loaded, map_validated, "validatemap");
    game->newTransition(map_validated, players_added, "addplayer");
    game->newTransition(players_added, players_added, "addplayer");
    game->newTransition(players_added, assign_reinforcement, "gamestart");
    game->newTransition(assign_reinforcement, win, "gameend");	//For testing purposes
    game->newTransition(win, start, "replay");
    game->newTransition(win, end_game, "quit");

    // Initializing currentState and cmd_currentState in gameEngine
    game->currentState = start;
    game->cmd_currentState = start;

    string answer;
    string cmd_fileName;

    // Testing the CommandProcessor ILoggable/Subject implementation
    cout << "\nTesting CommandProcessor ILoggable/Subject implementation.." << endl << "***************************************************" << endl;
    cout << "Do you wish to accept commands from the console or read them from a file? " << '\n';

    cin >> answer; // answer for file or console

    // if / else if for user input
    if (answer == "console") {
        cout << "\nPlease enter a command: " << '\n';

        // Testing Notify in commandprocessor
        cout << "Testing command and commandprocessor Notify()..." << endl;
        while (!(commandprocessor->getExitProgram())) {
            commandprocessor->getCommand(game, commandprocessor);
        }
        
        // getting commandList
        cout << "\n\nAll commands: " << commandprocessor->getCommandList();
        cout << "\nValid commands: " << commandprocessor->getValidCommandList();

        // preventing memory leaks
        delete commandprocessor;
        commandprocessor = NULL;
    }
    else if (answer == "file") {
        cout << "\nWhich file do you wish to open? " << '\n';

        // user in for filename
        cin >> cmd_fileName;

        // read from the file
        FileLineReader* fileReader = new FileLineReader();
        fileReader->readLineFromFile(cmd_fileName);

        // command processor now reads from the file
        FileCommandProcessorAdapter* filecmd = new FileCommandProcessorAdapter(fileReader, _obs);
        
        // Testing command and commandprocessor Notify()
        cout << "Testing command and commandprocessor Notify()..." << endl;
        while (!(commandprocessor->getExitProgram())) {
            commandprocessor->getCommand(game, filecmd);
        }

        // getting commandList
        cout << "\n\nAll commands: " << commandprocessor->getCommandList();
        cout << "\nValid commands: " << commandprocessor->getValidCommandList();

        // preventing memory leaks
        delete filecmd;
        delete fileReader;
        filecmd = NULL;
        fileReader = NULL;

    }

    // Testing Orders ILoggable/Subject implementation
    cout << "\nTesting Orders ILoggable/Subject implementation..." << endl << "***************************************************" << endl;
    // Add new players
    Player* p1 = new Player("P1", new Hand(), game);
    Player* p2 = new Player("P2", new Hand(), game);

    // Adding territories
    auto* territory1 = new Territory();
    auto* territory2 = new Territory();

    // Associating territories and armies to players
    p1->addOwnedTerritory(territory1);
    p2->addOwnedTerritory(territory2);
    territory1->setNumberOfArmies(20);
    territory2->setNumberOfArmies(20);

    // Testing Order instantiation
    cout << "Testing order instantiation..." << endl;
    auto* deploy = new Deploy(p1, 10, territory1, game);
    auto* advance = new Advance(p1, 20, territory1, territory2, game);
    auto* bomb = new Bomb(p2, territory2, game);
    auto* blockade = new Blockade(p2, territory1, game);
    auto* negotiate = new Negotiate(p1, p2, game);
    auto* airlift = new Airlift(p1, 20, territory1, territory2, game);


    // Testing orderList Notify()
    cout << "Testing orderList Notify()..." << endl;
    p1->getOrdersList()->addOrders(deploy);
    p1->getOrdersList()->addOrders(advance);
    p2->getOrdersList()->addOrders(bomb);
    p2->getOrdersList()->addOrders(blockade);
    p2->getOrdersList()->addOrders(negotiate);
    p2->getOrdersList()->addOrders(airlift);
    
    // Testing order execute() Notify()
    cout << "Testing orders execute Notify()..." << endl;
    deploy->execute();    
    advance->execute();
    bomb->execute();
    blockade->execute();
    negotiate->execute();
    airlift->execute();    

    // GameEngine ILoggable/Subject implementation
    cout << "\nTesting GameEngine ILoggable/Subject implementation..." << endl << "***************************************************" << endl;

    // replaying the game
    game->changeState("replay");

    cout << "Artificially changing game states to show Notify()/stringToLog() output.." << endl;
    // artificially changing game states
    // changing state to loadmap
    game->changeState("loadmap");
    // changing state to validatemap
    game->changeState("validatemap");
    // changing state to addplayer
    game->changeState("addplayer");


    // preventing memory leaks
    // end() delete the GameEngine (game) object
    game->end();
    game = nullptr;

    delete commandprocessor;
    commandprocessor = nullptr;

    delete _obs;
    _obs = nullptr;

    delete p1, p2;
    delete territory1, territory2;
    p1, p2, territory1, territory2 = nullptr;

    return 0;
}