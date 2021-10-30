#pragma once // Should be included in all header files to avoid redundant inclusions. Dealt by preprocessor
#include <iostream> // Used for cout and stream insertion operator
#include <vector> // Used for lists instead of arrays
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"

using namespace std;
using namespace MapSpace;

// TO DO : ToDefend and ToAttack

// The player class contains a Hand (of cards), a list of owned territories, and a list of issued orders

class Player {
public:
	Player(Hand*); // Default constructor requires at least a hand
	Player(string name, class Hand*); // Constructor with player name and hand
	Player(const Player &player); // Copy constructor
	~Player(); // Destructor
	Player& operator =(const Player& player); // Assignment operator
	void addOwnedTerritory(Territory*);
	vector<Territory*> toDefend();	// Returns a list of territories that are to be defended (owned territories)
	vector<Territory*> toAttack();	// Returns a list of territories that are to be attacked
	void issueOrder(Orders*);	// Creates an Order object and puts it in the player�s list of orders
	bool ownsTerritory(Territory* t); // Whether player owns a territory in defend list
	string getName(); // Name getter
	class Hand* getHand(); // Hand pointer getter
	OrdersList* getOrdersList();
	friend ostream& operator<<(ostream& out, const Player& player); // Stream insertion operator

private:
	string name;
	Hand* hand; // Pointer to hand of cards
	vector<Territory*> territoriesOwned; // List of owned territories
	OrdersList* ordersList;
};

// Territory, Hand, and Order classes are placeholders and all similar in functionality
// Comments made in Territory are similar for Hand and Order

/*

class Territory {
public:
	Territory(); // Default constructor
	Territory(string); // Constructor to initialize string
	Territory(const Territory& territory); // Copy constructor
	Territory& operator =(const Territory& territory); // Assignment operator
	string getName(); // String getter
	void setName(string); // String setter 
	friend ostream& operator<<(ostream& out, const Territory& territory); // Stream insertion operator
private:
	string name; // Placeholder string
};

class Hand {
public:
	Hand();
	Hand(string);
	Hand(const Hand& hand);
	Hand& operator =(const Hand& hand);
	string getName();
	void setName(string);
	friend ostream& operator<<(ostream& out, const Hand& hand);
private:
	string name;
};

class Order {
public:
	Order();
	Order(string);
	Order(const Order& order);
	Order& operator =(const Order& order);
	string getOrder();
	void setOrder(string);
	friend ostream& operator<<(ostream& out, const Order& order);
private:
	string orderString;
};

*/