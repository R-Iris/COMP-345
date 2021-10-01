#include "Player.h" // Including the appropriate header file

int main() {
	cout << "Driver for the player class." << endl;

	Player *p1 = new Player("P1", new Hand()), * p2 = new Player("P2", new Hand());
	Territory *t1 = new Territory("T1"), *t2 = new Territory("T2"), *t3 = new Territory("T3"), *t4 = new Territory("T4"), *t5 = new Territory();
	Order* o1 = new Order("O1"), * o2 = new Order("O2"), * o3 = new Order("O3"), * o4 = new Order("O4"), * o5 = new Order();

	p1->addTerritoryDefend(t1); p1->addTerritoryDefend(t2);
	p1->addTerritoryAttack(t3); p1->addTerritoryAttack(t4); p1->addTerritoryAttack(t5);
	
	cout << endl << "Territories to defend:" << endl;
	for (Territory* t : p1->toDefend()) {
		cout << *t << endl;
	}

	cout << endl << "Territories to attack:" << endl;
	for (Territory* t : p1->toAttack()) {
		cout << *t << endl;
	}

	p1->issueOrder("Issued Order");
	p1->issueOrder("Second Issued Order");
	cout << endl << "Player 1's orders:" << endl;
	for (Order* o : p1->getOrders()) {
		cout << *o << endl;
	}

	cout << endl << "Name of the hand of cards Player 1 stores: " << *(p1->getHand()) << endl;

	cout << endl << "Player 1's owned territories:" << endl;
	for (Territory* t : p1->toDefend()) {
		cout << *t << endl;
	}

	delete p1; delete p2;
	delete t1; delete t2; delete t3; delete t4; delete t5;
	delete o1; delete o2; delete o3; delete o4; delete o5;	
	
	return 0;
}