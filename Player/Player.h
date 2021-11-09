#pragma once // Should be included in all header files to avoid redundant inclusions. Dealt by preprocessor
#include <iostream> // Used for cout and stream insertion operator
#include <vector> // Used for lists instead of arrays
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"

using namespace std;

// Forward declaration
class Hand;
class Territory;
class Orders;
class OrdersList;

// TO DO : ToDefend and ToAttack

// The player class contains a Hand (of cards), a list of owned territories, and a list of issued orders

class Player {
public:
	Player(Hand*); // Default constructor requires at least a hand
	Player(string name, Hand*); // Constructor with player name and hand
    Player(string name,Hand*,GameEngine*);									//Please let me know if i shouldnt add this --Abhay
	Player(const Player &player); // Copy constructor
	~Player(); // Destructor
	Player& operator =(const Player& player); // Assignment operator
	void addOwnedTerritory(Territory*);
    void removeOwnedTerritory(Territory*);
	vector<Territory*> toDefend();	// Returns a list of territories that are to be defended (owned territories)
	vector<Territory*> toAttack();	// Returns a list of territories that are to be attacked
	void issueOrder(Orders*);	// Creates an Order object and puts it in the player's list of orders
	bool ownsTerritory(Territory* t); // Whether player owns a territory in defend list
	bool ownsTerritory(int index);
	string getName(); // Name getter
	Hand* getHand(); // Hand pointer getter
	OrdersList* getOrdersList();
	int getReinforcementPool();
	void setReinforcementPool(int);
	friend ostream& operator<<(ostream& out, const Player& player); // Stream insertion operator
    vector<Player*> cannotAttack; //Vector of players which cannot be attacked
    void setOwnedTerritories(vector<Territory*>&);
private:
	string name;
    GameEngine* gameEngine;
	Hand* hand; // Pointer to hand of cards
	vector<Territory*> territoriesOwned; // List of owned territories
	OrdersList* ordersList;
	int reinforcementPool; // Number of armies in the reinforcement pool
};