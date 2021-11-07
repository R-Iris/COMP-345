#include "Orders.h"

int main(){
    cout << "Part 4: Order Execution Implementation\n" << endl;

    auto* gameEngine = new GameEngine();

    Hand* hand = new Hand(1);

    auto* p1 = new Player("Player 1", nullptr);
    auto* p2 = new Player("Player 2", hand);
    auto* p3 = new Player("Player 3", nullptr);
    auto* p4 = new Player("Player 4", nullptr);

    vector<Player*> players = {p1,p2,p3,p4};

    Deck* deck = new Deck(10);

    gameEngine->players = players;
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

    auto* deploy = new Deploy(p1,10,t1);
    //Attack between p1 and p2 -- P2 should win and t1 ownership should be transferred to p2
    auto* advance = new Advance(p2,30,t2,t1,deck);
    //Should be invalid
    auto* airlift = new Airlift(p3,10,t1,t3);
    auto* bomb = new Bomb(p4,t1);
    //Number of armies of t4 should be doubled and ownership of t4 should be transferred to neutral player
    //Since there is no neutral player, another player should be created when this order executes
    auto* blockade = new Blockade(p4,t4,gameEngine);
    //No attacks should be valid between p3 and p4 till the remainder of the turn
    auto* negotiate = new Negotiate(p3,p4);
    //Used to test the negotiate method above
    auto* advance1 = new Advance(p3,10,t3,t4,deck);


    p1->issueOrder(*deploy);
    p2->issueOrder(*advance);
    p3->issueOrder(*airlift);
    p4->issueOrder(*bomb);
    p4->issueOrder(*blockade);
    p3->issueOrder(*negotiate);
    p3->issueOrder(*advance1);


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

    cout << "Owner of t4 territory is now " << t4->getOwner()->getName() << endl;

    cout << "\nEND" << endl;

    gameEngine->end();


    delete p1,delete p2,delete p3,delete p4;
    delete t1,delete t2,delete t3,delete t4;
    delete deploy,delete advance,delete airlift,delete blockade,delete negotiate,delete advance1;
    delete gameEngine,delete deck;
    delete hand;
}