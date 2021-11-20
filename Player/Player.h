#pragma once // Should be included in all header files to avoid redundant inclusions. Dealt by preprocessor
#include <iostream> // Used for cout and stream insertion operator
#include <vector> // Used for lists instead of arrays
#include <algorithm> // Used for binary search
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"

using namespace std;

// Forward declaration
class Hand;
class Territory;
class Orders;
class OrdersList;
class PlayerStrategy;

// The player class contains a Hand (of cards), a list of owned territories, and a list of issued orders

class Player {
public:
	Player(Hand*, GameEngine*); // Default constructor requires at least a hand
    Player(string name, Hand*, GameEngine*); // Constructor with name, hand, and engine
	Player(const Player &player); // Copy constructor
	~Player(); // Destructor
	Player& operator =(const Player& player); // Assignment operator
	void addOwnedTerritory(Territory*);
    void removeOwnedTerritory(Territory*);
	vector<Territory*> toDefend();	// Returns a list of territories that are to be defended (owned territories)
	vector<Territory*> toAttack();	// Returns a list of territories that are to be attacked
	void issueOrder();
	bool ownsTerritory(Territory* t); // Whether player owns a territory in defend list
	bool ownsTerritory(int index);
	string getName(); // Name getter
	Hand* getHand(); // Hand pointer getter
	OrdersList* getOrdersList();
	int getReinforcementPool();
	void setReinforcementPool(int);
	void setGameEngine(GameEngine* game);
	GameEngine* getGameEngine();
	friend ostream& operator<<(ostream& out, const Player& player); // Stream insertion operator
    vector<Player*> cannotAttack; //Vector of players which cannot be attacked
    void setOwnedTerritories(vector<Territory*>&);
    bool receivedCardThisTurn = false;
	PlayerStrategy* getPlayerStrategy();
	void setPlayerStrategy(PlayerStrategy*);
private:
	string name;
    GameEngine* gameEngine;
	Hand* hand; // Pointer to hand of cards
	vector<Territory*> territoriesOwned; // List of owned territories
	OrdersList* ordersList;
	int reinforcementPool; // Number of armies in the reinforcement pool
	PlayerStrategy* ps;
};