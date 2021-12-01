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
    Player* p5 = new Player("P5", new Hand(), game);

    p2->setPlayerStrategy(new NeutralPlayerStrategy(p2));
    p3->setPlayerStrategy(new CheaterPlayerStrategy(p3));
    p4->setPlayerStrategy(new BenevolentPlayerStrategy(p4));
    p5->setPlayerStrategy(new AggressivePlayerStrategy(p5));

    // Add players to game list
    game->addPlayer(p1); game->addPlayer(p2);

    // Accept input for startup scenario
    cout << "Scenario 0: P1/P2 have 2 territories, 2 cards each -- Human (1), Neutral (2)" << endl;
    cout << "\t\t Show neutral player changing to aggressive player when attacked" << endl;
    cout << "Scenario 1: P3/P4 have 1 territory, no cards -- Cheater (3), Benevolent (4)" << endl;
    cout << "\t\t Show cheater player absorbing other territories" << endl;
    cout << "Scenario 2: P1/P5 each have 2 territories, no cards -- Neutral (2), Aggressive (5)" << endl;
    cout << "\t\t Test toAttack() and toDefend() vectors that have two different sorting strategies" << endl;
    cout << "\nPick a scenario:" << endl;
    int scenario = 0;
    cin >> scenario;
    cout << endl;

    switch (scenario) {
    case 0:
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
    case 1:
        game->removePlayer(p1); game->removePlayer(p2);
        // Add territories to players
        game->addPlayer(p3); game->addPlayer(p4);
        p3->addOwnedTerritory(territories.at(0)); 
        p4->addOwnedTerritory(territories.at(1));
        p3->addOwnedTerritory(territories.at(2));
        p4->addOwnedTerritory(territories.at(3));

        // Set player's reinforcement pools to 50
        p3->setReinforcementPool(50);
        p4->setReinforcementPool(50);

        game->changeState("gamestart");

        // Execute main game loop
        game->mainGameLoop();
        break;
    case 2:
        p2->addOwnedTerritory(territories.at(0)); p2->addOwnedTerritory(territories.at(2));
        p5->addOwnedTerritory(territories.at(1)); p5->addOwnedTerritory(territories.at(3));
        p2->setReinforcementPool(50);
        p5->setReinforcementPool(50);
        territories.at(0)->setNumberOfArmies(50);
        cout << "Territory 1 #armies: " << territories.at(0)->getNumberOfArmies() << endl;
        territories.at(1)->setNumberOfArmies(25);
        cout << "Territory 2 #armies: " << territories.at(1)->getNumberOfArmies() << endl;
        territories.at(2)->setNumberOfArmies(60);
        cout << "Territory 3 #armies: " << territories.at(2)->getNumberOfArmies() << endl;
        territories.at(3)->setNumberOfArmies(75);
        cout << "Territory 4 #armies: " << territories.at(3)->getNumberOfArmies() << endl;
        cout << endl;

        cout << "Neutral Player:" << endl;
        cout << "/------------------------/" << endl << endl;
        // Player 2 (Neutral)
        cout << "Neutral player sorts by most vulnerable territories (least armies)" << endl;
        cout << "ownedTerritories: Sorted.." << endl;
        for (Territory* t : p2->toDefend())
        {
            cout << *t << endl;
        }

        cout << "Neutral player has no toAttack" << endl;
        cout << "attackableTerritories: Sorted.." << endl;
        for (Territory* t : p2->toAttack())
        {
            cout << *t << endl;
        }
        cout << endl;
        cout << "Aggressive Player:" << endl;
        cout << "/------------------------/" << endl << endl;
        // Player 5 (Aggressive)
        cout << "Aggressive player sorts by most strong territories (most armies)" << endl;
        cout << "ownedTerritories: Sorted.." << endl;
        for (Territory* t : p5->toDefend())
        {
            cout << *t << endl;
        }

        cout << "Aggressive player sorts attackable territories by weakest (least armies)" << endl;
        cout << "attackableTerritories: Sorted.." << endl;
        for (Territory* t : p5->toAttack())
        {
            cout << *t << endl;
        }
        break;
    }
    

    // Delete players
    delete p1; delete p2; delete p3, delete p4, delete p5;
    p1, p2, p3, p4, p5 = nullptr;

    // Call end() which deletes game and prints a message
    game->end();
    // Delete dangling pointer
    game = nullptr;

    return 0;
}