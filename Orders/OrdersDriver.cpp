/*
#include "Orders.h"
#include <iostream>
using namespace std;

int main(){

   Territory* t1 = new Territory("Asia");
   Territory* t2 = new Territory("Europe");
   Territory* t3 = new Territory("Africa");
   Territory* t4 = new Territory("Australia");
   Territory* t5 = new Territory("North America");
   Territory* t6 = new Territory("South America");

   t1->neighbours = {t2};
   t2->neighbours = {t5,t1,t3};
   t3->neighbours = {t2};
   t4->neighbours = {t1};
   t5->neighbours = {t2,t6};
   t6->neighbours = {t5};

   Player* p1 = new Player("P1",{t1,t2},new OrdersList(*new vector<Orders*>));
   Player* p2 = new Player("P2",{t3,t4},new OrdersList(*new vector<Orders*>));
   Player* p3 = new Player("P3",{t5,t6},new OrdersList(*new vector<Orders*>));

   //Orders of any subclass can be created by the player and placed sequentially in the list of orders

   p1->getOrdersList()->addOrders( new Deploy(p1,10,t3));
   p2->getOrdersList()->addOrders(new Advance(p2,10,t3,t5));
   p3->getOrdersList()->addOrders(new Bomb(p3,t1));
   p1->getOrdersList()->addOrders(new Blockade(p1,10,t1));
   p2->getOrdersList()->addOrders(new Airlift(p1,10,t1,t4));
   p3->getOrdersList()->addOrders(new Negotiate(p3));

   //Printing each player's orderList

   cout << "Printing ordersList of player p1" << endl << *(p1->getOrdersList()) << endl;
   cout << "Printing ordersList of player p2" << endl << *(p2->getOrdersList()) << endl;
   cout << "Printing ordersList of player p3" << endl << *(p3->getOrdersList()) << endl;

   //Moving some orders

   cout << "Trying to move orders of p1" << endl;

   p1->getOrdersList()->move(0,1);

   cout << "Printing ordersList of player p1" << endl << *(p1->getOrdersList()) << endl;

   //Removing some orders

   cout << "Trying to remove 1 order of p2" << endl;

   p2->getOrdersList()->remove(1);

   cout << endl << "Printing ordersList of player p2" << endl << *(p2->getOrdersList()) << endl;

   //Executing some orders

   cout << endl << "Executing some orders" << endl << endl;

   Deploy* deploy = new Deploy(p1,10,t3);

   deploy->execute();

   cout << endl;

   Airlift* airlift = new Airlift(p3,10,t3,t4);

   airlift->execute();

   cout << endl;

   Bomb* bomb = new Bomb(p3,t2);

   bomb->execute();


   cout << endl << "Testing some stream insertion operators" << endl;

   cout << *deploy << *airlift << *bomb;

    delete p1;delete p2;delete p3;delete t1;delete t2;delete t3; delete t4; delete t5; delete t6;
    delete p1->getOrdersList(); delete p2->getOrdersList(); delete p3->getOrdersList();
    delete deploy,delete airlift, delete bomb;
}

*/

#include "Orders.h"
