#include "Player.h" // Including the appropriate header file

// Default constructor requires a hand
Player::Player(Hand* hand) : name("Unnamed"), hand(hand), reinforcementPool(0) {
    this->ordersList = new OrdersList(this,*new vector<Orders*>);
}

// Constructor with player name and hand
Player::Player(string name, Hand* hand) : name(name), hand(hand), reinforcementPool(0) {
    this->ordersList = new OrdersList(this,*new vector<Orders*>);
}


// Copy constructor
Player::Player(const Player& player)
{
	name = player.name;
	this->hand = new Hand(*(player.hand));
	territoriesOwned = player.territoriesOwned;
	ordersList = new OrdersList(*(player.ordersList));
	reinforcementPool = player.reinforcementPool;
    gameEngine = player.gameEngine; // Cannot create new map
}

// Destructor
Player::~Player()
{
	delete hand; // Delete pointer to hand
    delete getOrdersList(); //Delete allocated ordersList in constructor
	delete ordersList; // Delete pointer to ordersList
	// All cleared vectors need their content deleted, depending on how they are initialized (see driver)
	territoriesOwned.clear();
}

// Assignment operator
Player& Player::operator=(const Player& player)
{
	name = player.name;
	this->hand = new Hand(*(player.hand)); // Deep copy of hand is made by calling new
	territoriesOwned = player.territoriesOwned;
	ordersList = new OrdersList(*(player.ordersList));
	reinforcementPool = player.reinforcementPool;
    gameEngine = player.gameEngine;
	return *this;
}

// Add territory to own
void Player::addOwnedTerritory(Territory* territory) {
	territoriesOwned.push_back(territory);
    territory->setOwner(this);
}

// Return a list of owned territories
vector<Territory*> Player::toDefend() // Returns a list of territories that are to be defended
{
	return territoriesOwned;
}

// Return a list of territories to attack
vector<Territory*> Player::toAttack() // Returns a list of territories that are to be attacked
{
	vector<Territory*> adjacentTerritories;
	for (Territory* t : territoriesOwned) {
		for (Territory* a : t->getAdjacentTerritories()) {
			adjacentTerritories.push_back(a);
			// Doesn't take care of copies/repeats in territories
		}
	}
	return adjacentTerritories;
}

// Create a new order and add to order list
void Player::issueOrder(Orders* order) // Creates an Order object and puts it in the player�s list of orders
{
	ordersList->addOrders(order);
}

bool Player::ownsTerritory(Territory* territory) {
	for (Territory* t : territoriesOwned) {
		if (t == territory) {return true;}
	}
	return false;
}

bool Player::ownsTerritory(int index) {
    for (Territory* t : territoriesOwned) {
        if (t->getIndex() == index) {return true;}
    }
    return false;
}

// Getters
string Player::getName() {return name;}
Hand* Player::getHand() {return hand;}
OrdersList* Player::getOrdersList() {return ordersList;}

int Player::getReinforcementPool()
{
	return reinforcementPool;
}

void Player::setReinforcementPool(int rP)
{
	reinforcementPool = rP;
}

// Stream insertion operator, returns player's name
ostream& operator<<(ostream& out, const Player& player) {
	return out << player.name;
}

void Player::removeOwnedTerritory(Territory * territory) {
    auto newOwnedTerritory = new vector<Territory*>();
    for(auto it: territoriesOwned){
        if(it == territory){}
        else{
            newOwnedTerritory->push_back(it);
        }
    }
    setOwnedTerritories(*newOwnedTerritory);

}

void Player::setOwnedTerritories(vector<Territory *> & newVector) {
    territoriesOwned = newVector;
}

Player::Player(string name, Hand * hand, GameEngine* gameEngine) {
    this->name = name;
    this->hand = hand;
    this->gameEngine = gameEngine;
}
