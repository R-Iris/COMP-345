#include "PlayerStrategies.h";

/*
Driver:
(1) different players can be assigned different strategies that lead to different behavior using the Strategy design pattern
(2) the strategy adopted by a player can be changed dynamically during play
(3) the human player makes decisions according to user interaction, and computer
players make decisions automatically, which are both implemented using the strategy pattern.
*/
int main()
{

    // Random initializer
    srand((int)time(nullptr));

    GameEngine* game = new GameEngine();

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
    game->newTransition(assign_reinforcement, win, "win"); // Used for demonstration
    game->newTransition(issue_orders, issue_orders, "issueorder");
    game->newTransition(issue_orders, execute_orders, "issueordersend");
    game->newTransition(execute_orders, execute_orders, "execorder");
    game->newTransition(execute_orders, assign_reinforcement, "endexecorders");
    game->newTransition(execute_orders, win, "win");
    game->newTransition(win, start, "replay");

    // Initializing currentState
    game->currentState = players_added;
    game->cmd_currentState = players_added;
    // Announce current state
    cout << *game->currentState;

    // Create a map from file and assign to this game instance
    string fileName = "test.map";
    Map* map = MapLoader::createMapfromFile(fileName);
    map->validate();
    game->setMap(map);

    vector<Territory*> territories = map->getTerritories();

    // Add new players
    Player* p1 = new Player("P1", new Hand(), game);
    Player* p2 = new Player("P2", new Hand(), game);
    Player* p3 = new Player("P3", new Hand(), game);
    Player* p4 = new Player("P4", new Hand(), game);

    /// To test:
    /// 
    /// 
    /// 

    p2->setPlayerStrategy(new NeutralPlayerStrategy(p2));
    p3->setPlayerStrategy(new CheaterPlayerStrategy(p3));
    p4->setPlayerStrategy(new BenevolentPlayerStrategy(p4));


    // Add players to game list
    game->addPlayer(p1); game->addPlayer(p2);

    // Accept input for startup scenario
    cout << "Scenario 0: P1/P2 have 1 territory, no cards" << endl;
    cout << "Scenario 1: P1 has a continent (+20), P2 has 1 territory, no cards" << endl;
    cout << "Scenario 2: P1/P2 have 2 territories, 2 cards each" << endl;
    cout << "Scenario 3: P1 wins with all 4 territories, no cards" << endl;
    cout << "Scenario 4: P1/P2 have 2 territories, no cards" << endl;
    cout << "Scenario 5: P1 has 2 territories, P2/P3 have 1, no cards" << endl;
    cout << "Scenario 6: P1/P2/P3/P4 have 1 territory, no cards" << endl;
    cout << "Pick a scenario:" << endl;
    int scenario = 0;
    cin >> scenario;
    cout << endl;

    switch (scenario) {
    case 0:
        // Add territories to players
        p1->addOwnedTerritory(territories.at(0));
        p2->addOwnedTerritory(territories.at(1));

        // Set player's reinforcement pools to 50
        p1->setReinforcementPool(50);
        p2->setReinforcementPool(50);

        game->changeState("gamestart");

        // Execute main game loop
        game->mainGameLoop();
        break;
    case 1:
        // Add territories to players
        p1->addOwnedTerritory(territories.at(0)); p1->addOwnedTerritory(territories.at(1)); p1->addOwnedTerritory(territories.at(2));
        p2->addOwnedTerritory(territories.at(3));

        // Set player's reinforcement pools to 50
        p1->setReinforcementPool(50);
        p2->setReinforcementPool(5);

        game->changeState("gamestart");

        // Execute main game loop
        game->mainGameLoop();
        break;
    case 2:
        // Add territories to players
        p1->addOwnedTerritory(territories.at(0)); p1->addOwnedTerritory(territories.at(2));
        p2->addOwnedTerritory(territories.at(1)); p2->addOwnedTerritory(territories.at(3));

        // Set player's reinforcement pools to 50
        p1->setReinforcementPool(50);
        p2->setReinforcementPool(50);

        // Draw 2 cards for each player
        p1->getHand()->addHand(game->getDeck()->draw());
        p1->getHand()->addHand(game->getDeck()->draw());
        p2->getHand()->addHand(game->getDeck()->draw());
        p2->getHand()->addHand(game->getDeck()->draw());

        game->changeState("gamestart");

        // Execute main game loop
        game->mainGameLoop();
        break;
    case 3:
        // Add territories to players
        p1->addOwnedTerritory(territories.at(0)); p1->addOwnedTerritory(territories.at(1));
        p1->addOwnedTerritory(territories.at(2)); p1->addOwnedTerritory(territories.at(3));

        // Set player's reinforcement pools to 50
        p1->setReinforcementPool(50);
        p2->setReinforcementPool(50);

        game->changeState("gamestart");

        // Execute main game loop
        game->mainGameLoop();
        break;
    case 4:
        // Add territories to players
        p1->addOwnedTerritory(territories.at(0)); p1->addOwnedTerritory(territories.at(2));
        p2->addOwnedTerritory(territories.at(1)); p2->addOwnedTerritory(territories.at(3));

        // Set player's reinforcement pools to 50
        p1->setReinforcementPool(50);
        p2->setReinforcementPool(50);

        game->changeState("gamestart");

        // Execute main game loop
        game->mainGameLoop();
        break;
    case 5:
        // Add territories to players
        game->addPlayer(p3);
        p1->addOwnedTerritory(territories.at(0)); p1->addOwnedTerritory(territories.at(1));
        p2->addOwnedTerritory(territories.at(2));
        p3->addOwnedTerritory(territories.at(3));

        // Set player's reinforcement pools to 50
        p1->setReinforcementPool(50);
        p2->setReinforcementPool(5);
        p3->setReinforcementPool(5);

        game->changeState("gamestart");

        // Execute main game loop
        game->mainGameLoop();
        break;
    case 6:
        // Add territories to players
        game->addPlayer(p3); game->addPlayer(p4);
        p1->addOwnedTerritory(territories.at(0)); 
        p2->addOwnedTerritory(territories.at(1));
        p3->addOwnedTerritory(territories.at(2));
        p4->addOwnedTerritory(territories.at(3));

        // Set player's reinforcement pools to 50
        p1->setReinforcementPool(50);
        p2->setReinforcementPool(50);
        p3->setReinforcementPool(50);
        p4->setReinforcementPool(50);

        game->changeState("gamestart");

        // Execute main game loop
        game->mainGameLoop();
        break;
    }

    // Delete players
    delete p1; delete p2; delete p3, delete p4;
    p1, p2, p3, p4 = nullptr;

    // Call end() which deletes game and prints a message
    game->end();
    // Delete dangling pointer
    game = nullptr;

    return 0;
}