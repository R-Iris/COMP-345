#include "Player.h" // Including the appropriate header file

int main() {
	cout << "Driver for the player class." << endl;

	// Create new player, territory, order, and hand objects
	// Using pointers as they are user-created classes
	Player *p1 = new Player("P1", new Hand()), * p2 = new Player("P2", new Hand());
	Territory *t1 = new Territory("T1"), *t2 = new Territory("T2"), *t3 = new Territory("T3"), *t4 = new Territory("T4"), *t5 = new Territory();
	Order* o1 = new Order("O1"), * o2 = new Order("O2"), * o3 = new Order("O3"), * o4 = new Order("O4"), * o5 = new Order();

	// Add territories to defend and attack for Player 1
	p1->addTerritoryDefend(t1); p1->addTerritoryDefend(t2);
	p1->addTerritoryAttack(t3); p1->addTerritoryAttack(t4); p1->addTerritoryAttack(t5);
	
	// Printing out the territories to defend for Player 1
	cout << endl << "Territories to defend:" << endl;
	for (Territory* t : p1->toDefend()) {
		cout << *t << endl;
	}

	// Printing out the territories to attack for Player 1
	cout << endl << "Territories to attack:" << endl;
	for (Territory* t : p1->toAttack()) {
		cout << *t << endl;
	}

	// Issuing and printing out orders given to Player 1
	p1->issueOrder("Issued Order");
	p1->issueOrder("Second Issued Order");
	cout << endl << "Player 1's orders:" << endl;
	for (Order* o : p1->getOrders()) {
		cout << *o << endl;
	}

	// Printing the name of player 1's hand
	cout << endl << "Name of the hand of cards Player 1 stores: " << *(p1->getHand()) << endl;

	// Printing the list of player 1's owned territories
	cout << endl << "Player 1's owned territories:" << endl;
	for (Territory* t : p1->toDefend()) {
		cout << *t << endl;
	}
	
	// Delete all pointers that a "new" assignment on the right-hand side
	delete p1; delete p2;
	delete t1; delete t2; delete t3; delete t4; delete t5;
	delete o1; delete o2; delete o3; delete o4; delete o5;	
	
	// Avoid dangling pointers by assigning NULL to deleted pointers
	p1 = NULL; p2 = NULL;
	t1 = NULL; t2 = NULL; t3 = NULL; t4 = NULL; t5 = NULL;
	o1 = NULL; o2 = NULL; o3 = NULL; o4 = NULL; o5 = NULL;

	return 0;
}