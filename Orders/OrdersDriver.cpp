
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

   Player* p1 = new Player("P1",{t1,t2});
   Player* p2 = new Player("P2",{t3,t4});
   Player* p3 = new Player("P3",{t5,t6});

   cout << endl;

   Deploy* d1 = new Deploy(1,t6);
   d1->execute(*p1);
   cout << endl;

   Advance* a1 = new Advance(2,t2,t3);
   a1->execute(*p1);
   cout << endl;

   Bomb* b1 = new Bomb(t3);
   b1->execute(*p2);
   cout << endl;

   Blockade* bl1 = new Blockade(4,t5);
   bl1->execute(*p3);
   cout << endl;

   Airlift* ai1 = new Airlift(3,t5,t1);
   ai1->execute(*p3);
   cout << endl;

   /*
    *Negotiate* n1 = new Negotiate();
    *n1->execute();
    *cout << endl;
   */

   return 0;
}
