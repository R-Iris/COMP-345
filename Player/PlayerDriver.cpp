#include "Player.h" // Including the appropriate header file

/*
All classes must implement a correct copy constructor, assignment operator,and stream insertion operator.
Memory leaks must be avoided.
Code must be documented using comments
*/

int main() {
	cout << "Driver for the player class." << endl;

	Player *p1 = new Player("P1", new Hand()), * p2 = new Player("P2", new Hand());
	Territory *t1 = new Territory("T1"), *t2 = new Territory("T2"), *t3 = new Territory("T3"), *t4 = new Territory("T4"), *t5 = new Territory();
	Order* o1 = new Order("O1"), * o2 = new Order("O2"), * o3 = new Order("O3"), * o4 = new Order("O4"), * o5 = new Order();

	

	return 0;
}