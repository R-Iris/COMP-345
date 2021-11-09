#include <iostream>
#include <vector>

#include "GameEngine.h"
#include "../Map/Map.h"

int main()
{
    // Instantiate Observer object
    //Observer* _game_observer = new LogObserver();
    // Instantiate GameEngine object
    //GameEngine* game = new GameEngine(_game_observer);
    GameEngine * game = new GameEngine();
    // Create a map from file and assign to this game instance
    string fileName = "C:/Users/Karim-480GB-SSD/Desktop/C++ VS/COMP-345/Map/Assets/test.map";
    Map* map = MapLoader::createMapfromFile(fileName);
    //map->validate();
    game->setMap(map);

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

    // Add new players
    Player* p1 = new Player("P1", new Hand(), game);
    Player* p2 = new Player("P2", new Hand(), game);

    // Add players to game list
    game->addPlayer(p1); game->addPlayer(p2);

    // Initializing currentState
    game->currentState = players_added;
    // Announce current state
    cout << *game->currentState;

    // Execute start phase
    // game->startupPhase();
    game->changeState("gamestart");

    vector<Territory*> territories = map->getTerritories();

    /*
    for (Territory* t : territories) {
        cout << t << endl;
    }
    */

    p1->addOwnedTerritory(territories.at(0));
    p2->addOwnedTerritory(territories.at(1));

    // Execute main game loop
    game->mainGameLoop();

    cout << "P1's territories owned:" << endl;
    for (Territory* t : p1->toDefend()) {
        cout << t->getName() << endl;
    }
    cout << "P2's territories owned:" << endl;
    for (Territory* t : p2->toDefend()) {
        cout << t->getName() << endl;
    }

    cout << "P1's reinforcement pool:" << p1->getReinforcementPool() << endl;
    cout << "Adding territory C to P1" << endl;
    p1->addOwnedTerritory(territories.at(2));
    cout << "P1's territories owned:" << endl;
    for (Territory* t : p1->toDefend()) {
        cout << t->getName() << endl;
    }
    game->mainGameLoop();
    cout << "P1's reinforcement pool:" << p1->getReinforcementPool() << endl;

    /*
    game->removePlayer(p2);
    cout << "List of players:" << endl;
    for (Player* p : game->players) {
        cout << p->getName() << endl;
    }
    */


    // call end() which deletes game and prints a message
    game->end();
    // fix dangling pointer
    game = nullptr;
    // deallocate observer object
    //delete _game_observer;
    // fix dangling pointer
    //_game_observer = nullptr;
    return 0;
}