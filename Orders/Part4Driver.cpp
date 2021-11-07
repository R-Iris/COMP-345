#include "Orders.h"

int main(){
    cout << "Part 4: Order Execution Implementation\n" << endl;

    auto* gameEngine = new GameEngine();

    auto* p1 = new Player("Player 1", nullptr);
    auto* p2 = new Player("Player 2", nullptr);
    auto* p3 = new Player("Player 3", nullptr);
    auto* p4 = new Player("Player 4", nullptr);

    vector<Player*> players = {p1,p2,p3,p4};

    Deck* deck = new Deck();

    gameEngine->players = players;
    gameEngine->deck = deck;

    auto* t1 = new Territory();
    t1->setName("T1");
    p1->addOwnedTerritory(t1);
    auto* t2 = new Territory();
    t2->setName("T2");
    p2->addOwnedTerritory(t2);
    auto* t3 = new Territory();
    t3->setName("T3");
    p3->addOwnedTerritory(t3);
    auto* t4 = new Territory();
    t4->setName("T4");
    p4->addOwnedTerritory(t4);


    auto* deploy = new Deploy(p1,10,t1);
    //Attack between p1 and p2 -- P2 should win and t1 ownership should be transferred to p2
    auto* advance = new Advance(p2,20,t2,t1,deck);
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
    p3->issueOrder(*advance1);



    cout << *(p1->getOrdersList()) << endl;
    cout << *(p2->getOrdersList()) << endl;
    cout << *(p3->getOrdersList()) << endl;
    cout << *(p4->getOrdersList()) << endl;

    cout << "Executing each player's order one by one\n" << endl;

    for(auto it:p1->getOrdersList()->ordersList){
        it->execute();
    }




    cout << "END" << endl;

    gameEngine->end();


    delete p1,delete p2,delete p3,delete p4;
    delete t1,delete t2,delete t3,delete t4;
    delete deploy,delete advance,delete airlift,delete blockade,delete negotiate,delete advance1;
    delete gameEngine,delete deck;
}