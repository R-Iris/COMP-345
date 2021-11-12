#include "Orders.h"

int main(){

    srand((int)time(nullptr));

    cout << "Part 4: Order Execution Implementation\n" << endl;

    Observer* _obs = new LogObserver();
    auto* gameEngine = new GameEngine(_obs);

    Card* card = new Card(Card::cardType::Blockade);

    Hand* hand = new Hand(1);

    hand->addHand(card);

    auto* p1 = new Player("Player 1", nullptr, gameEngine);
    auto* p2 = new Player("Player 2", hand, gameEngine);
    auto* p3 = new Player("Player 3", nullptr, gameEngine);
    auto* p4 = new Player("Player 4", nullptr, gameEngine);

    Deck* deck = new Deck(10);

    cout << "Adding players to the game engine" << endl;

    gameEngine->players = {p1,p2,p3,p4};

    cout << "\nPrinting the names of the players at the start of the game" << endl;

    for(auto it : gameEngine->players){
        cout << it->getName() << "-->";
    }

    cout << "END\n" << endl;

    gameEngine->deck = deck;

    auto* t1 = new Territory();
    t1->setName("T1");
    t1->setNumberOfArmies(5);
    p1->addOwnedTerritory(t1);
    auto* t2 = new Territory();
    t2->setNumberOfArmies(30);
    t2->setName("T2");
    p2->addOwnedTerritory(t2);
    auto* t3 = new Territory();
    t3->setName("T3");
    p3->addOwnedTerritory(t3);
    t3->setNumberOfArmies(50);
    auto* t4 = new Territory();
    t4->setName("T4");
    p4->addOwnedTerritory(t4);
    auto* t5 = new Territory();
    t5->setName("T5");
    p4->addOwnedTerritory(t5);

    t1->setAdjacentTerritories({t2});
    t2->setAdjacentTerritories({t1});
    t3->setAdjacentTerritories({t4});
    t4->setAdjacentTerritories({t3});

    auto* deploy = new Deploy(p1,10,t1, gameEngine);
    
    //Attack between p1 and p2 -- P2 should win and t1 ownership should be transferred to p2
    auto* advance = new Advance(p2,30,t2,t1, gameEngine);
    //Should be invalid
    auto* airlift = new Airlift(p3,10,t1,t3, gameEngine);
    auto* bomb = new Bomb(p4,t1, gameEngine);
    //Number of armies of t4 should be doubled and ownership of t4 should be transferred to neutral player
    //Since there is no neutral player, another player should be created when this order executes
    auto* blockade = new Blockade(p4,t4,gameEngine);
    //No attacks should be valid between p3 and p4 till the remainder of the turn
    auto* negotiate = new Negotiate(p3,p4, gameEngine);
    //Used to test the negotiate method above
    auto* advance1 = new Advance(p3,10,t3,t4,gameEngine);


    p1->getOrdersList()->addOrders(deploy);
    p2->getOrdersList()->addOrders(advance);
    p3->getOrdersList()->addOrders(airlift);
    p4->getOrdersList()->addOrders(bomb);
    p4->getOrdersList()->addOrders(blockade);
    p3->getOrdersList()->addOrders(negotiate);
    p3->getOrdersList()->addOrders(advance1);


    cout << *(p1->getOrdersList()) << endl;
    cout << *(p2->getOrdersList()) << endl;
    cout << *(p3->getOrdersList()) << endl;
    cout << *(p4->getOrdersList()) << endl;

    cout << "Executing each player's order one by one\n" << endl;

    cout << "Executing " + p1->getName() + "'s ordersList\n" << endl;

    for(auto it:p1->getOrdersList()->ordersList){
        it->execute();
    }

    cout << "\nExecuting " + p2->getName() + "'s ordersList\n" << endl;

    cout << "Initial p2's hand : " <<  *p2->getHand() << endl;

    for(auto it:p2->getOrdersList()->ordersList){
        it->execute();
    }

    cout << "P2's hand after battle : " << *p2->getHand() << endl;

    cout << "Testing if change of ownership was successful" << endl;

    cout << "t1 now belongs to " << t1->getOwner()->getName() << endl;

    cout << "\nExecuting " + p3->getName() + "'s ordersList while at the same time testing if negotiate order works\n" << endl;

    for(auto it:p3->getOrdersList()->ordersList){
        it->execute();
        cout << endl;
    }

    cout << "As seen above, negotiate order works as expected preventing any attack between "
    << "p3 and p4 for the remainder of the turn\n" << endl;


    cout << "List of territories owned by p4 before blockade order: ";

    for(auto it: p4->toDefend()){
        cout << it->getName() << " ";
    }


    cout << "\nNow executing " + p4->getName() + "'s ordersList while testing blockade order\n" << endl;

    for(auto it:p4->getOrdersList()->ordersList){
        it->execute();
        cout << endl;
    }

    cout << "List of territories owned by p4 after blockade order: ";

    for(auto it: p4->toDefend()){
        cout << it->getName() << " ";
    }

    cout << "\nAs seen above, p4 no longer owns t4 after blockade order is executed" << endl;

    cout << "\nNow testing transfer of ownership to neutral player" << endl;

    cout << "Owner of t4 territory is now " << t4->getOwner()->getName() << endl << endl;

    cout << "Printing the new list of player's in the game (after blockade order is executed)\n" << endl;

    for(auto it : gameEngine->players){
        cout << it->getName() << "-->";
    }

    cout << "END" << endl;

    cout << "\nEnd of Part 4 Driver" << endl;

    gameEngine->end();


    delete p1,delete p2,delete p3,delete p4;
    delete t1,delete t2,delete t3,delete t4;
}