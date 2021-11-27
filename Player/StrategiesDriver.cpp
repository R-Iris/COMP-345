#include "PlayerStrategies.h";

/*
Driver:
(1) different players can be assigned different strategies that lead to different behavior using the Strategy design pattern
(2) the strategy adopted by a player can be changed dynamically during play
(3) the human player makes decisions according to user interaction, and computer
players make decisions automatically, which are both implemented using the strategy pattern.
*/

int main() {
    GameEngine* game = new GameEngine();
    // Add new players
    Player* p1 = new Player("P1", new Hand(), game);
    Player* p2 = new Player("P2", new Hand(), game);
    p2->setPlayerStrategy(new NeutralPlayerStrategy(p2));

    // Adding territories
    vector<Territory*> territories1;
    auto* territory1 = new Territory();
    territories1.push_back(territory1);
    vector<Territory*> territories2;
    auto* territory2 = new Territory();
    territories2.push_back(territory2);

    // Associating territories and armies to players
    p1->addOwnedTerritory(territory1);
    p2->addOwnedTerritory(territory2);
    territory1->setNumberOfArmies(20);
    territory2->setNumberOfArmies(20);

    territory1->setAdjacentTerritories(territories2);
    territory2->setAdjacentTerritories(territories1);

    // Testing Order instantiation
    cout << "Testing order instantiation..." << endl;
    auto* deploy = new Deploy(p1, 10, territory1, game);
    auto* advance = new Advance(p1, 20, territory1, territory2, game);
    auto* bomb = new Bomb(p1, territory2, game);
    auto* blockade = new Blockade(p2, territory1, game);
    auto* negotiate = new Negotiate(p1, p2, game);
    auto* airlift = new Airlift(p1, 20, territory1, territory2, game);

    // Testing order execute() Notify()
    cout << "Testing orders execute Notify()..." << endl;
    deploy->execute();
    advance->execute();
    bomb->execute();
    blockade->execute();
    negotiate->execute();
    airlift->execute();

	return 0;
}