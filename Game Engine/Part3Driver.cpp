#include <iostream>
#include <vector>

#include "GameEngine.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../Map/Map.h"

int main()
{
    // Instantiate GameEngine object
    GameEngine* game = new GameEngine();
    //Observer* logger = new LogObserver();
    //game->Attach(logger); // attaching to observer
    // Create a map from file and assign to this game instance
    string fileName = "test.map";
    Map* map = MapLoader::createMapfromFile(fileName);
    map->validate();
    game->setMap(map);

    // Add new players
    Player* p1 = new Player("P1", new Hand());
    Player* p2 = new Player("P2", new Hand());

    // Add players to game list
    game->addPlayer(p1); game->addPlayer(p2);

    // Execute start phase
    // game->startupPhase();

    vector<Territory*> territories = map->getTerritories();

    for (Territory* t : territories) {
        cout << t << endl;
    }

    //p1->addOwnedTerritory(territories.at(0));
    //p2->addOwnedTerritory(territories.at(2));

    // Execute main game loop
    game->mainGameLoop();

    cout << "P1's territories owned:" << endl;
    for (Territory* t : p1->toDefend()) {
        cout << t << endl;
    }
    cout << "P2's territories owned:" << endl;
    for (Territory* t : p2->toDefend()) {
        cout << t << endl;
    }

    /*
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
    game->newTransition(players_added, assign_reinforcement, "assigncountries");
    game->newTransition(assign_reinforcement, issue_orders, "issueorder");
    game->newTransition(issue_orders, issue_orders, "issueorder");
    game->newTransition(issue_orders, execute_orders, "endissueorders");
    game->newTransition(execute_orders, execute_orders, "execorder");
    game->newTransition(execute_orders, assign_reinforcement, "endexecorders");
    game->newTransition(execute_orders, win, "win");
    game->newTransition(win, start, "play");
    ///////////////////////////////////////////
    game->newTransition(start, win, "test"); // Used for demonstration purposes

    // Initializing currentState
    game->currentState = start;
    // Announce current state
    cout << *game->currentState;

    string command = "";

    // Confirming ruleset
    while (game->currentState->stateName != "win" || command != "end")
    {
        cout << "Please enter command: ";
        cin >> command;
        while (!game->changeState(command))
        {
            cout << "Command invalid, please try again: ";
            cin >> command;
        }
    }
    */

    game->end();
    game = NULL;
    //delete logger;
    //logger = NULL;
    //game->Detach(); problematic for some reason
    return 0;
}