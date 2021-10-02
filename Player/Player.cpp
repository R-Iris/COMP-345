#include "Player.h" // Including the appropriate header file

// Default constructor requires a hand
Player::Player(Hand* hand) : name("Unnamed"), hand(hand) {}

// Constructor with player name and hand
Player::Player(string name, Hand* hand) : name(name), hand(hand){}

// Copy constructor
Player::Player(const Player& player)
{
	name = player.name;
	this->hand = new Hand(*(player.hand));
	territoriesDefend = player.territoriesDefend;
	territoriesAttack = player.territoriesAttack;
	orders = player.orders;
}

// Destructor
Player::~Player()
{
	delete hand; // Delete pointer to hand

	// All cleared vectors need their content deleted, depending on how they are initialized (see driver)
	territoriesDefend.clear();
	territoriesAttack.clear();
	orders.clear();
}

// Assignment operator
Player& Player::operator=(const Player& player)
{
	name = player.name;
	this->hand = new Hand(*(player.hand)); // Deep copy of hand is made by calling new
	territoriesDefend = player.territoriesDefend;
	territoriesAttack = player.territoriesAttack;
	orders = player.orders;
	return *this;
}

// Add territory to defend to vector
void Player::addTerritoryDefend(Territory* territory)
{
	territoriesDefend.push_back(territory);
}

// Add territory to attack to vector
void Player::addTerritoryAttack(Territory* territory)
{
	territoriesAttack.push_back(territory);
}

// Return a list of owned territories
vector<class Territory*> Player::toDefend() // Returns a list of territories that are to be defended
{
	return territoriesDefend;
}

// PLACEHOLDER: return a list of territories to attack
vector<class Territory*> Player::toAttack() // Returns a list of territories that are to be attacked
{
	return territoriesAttack;
}

// PLACEHOLDER : Create a new order and add to order list
void Player::issueOrder(string order) // Creates an Order object and puts it in the player’s list of orders
{
	orders.push_back(new Order(order));
}

// Getters
string Player::getName() {return name;}
Hand* Player::getHand() {return hand;}
vector<class Order*> Player::getOrders(){return orders;}

// Stream insertion operator, returns player's name
ostream& operator<<(ostream& out, const Player& player) {
	return out << player.name;
}

/* ----------------------------------------------------------- */

/*
The Hand, Territory, and Order classes are placeholders with similar functionality.
*/

// Hand
Hand::Hand() : name("Empty Hand") {}
Hand::Hand(string name) : name(name) {}
Hand::Hand(const Hand& hand) {name = hand.name;}
Hand& Hand::operator=(const Hand& hand)
{
	name = hand.name;
	return *this;
}
string Hand::getName() {return name;}
void Hand::setName(string name) {name = name;}
ostream& operator<<(ostream& out, const Hand& hand) {
	return out << hand.name;
}

/* ----------------------------------------------------------- */

// Territory
Territory::Territory() : name("Undiscovered") {}
Territory::Territory(string name) : name(name) {}
Territory::Territory(const Territory& territory) {name = territory.name;}
Territory& Territory::operator=(const Territory& territory)
{
	name = territory.name;
	return *this;
}
string Territory::getName() {return name;}
void Territory::setName(string name) {name = name;}
ostream& operator<<(ostream& out, const Territory& territory) {
	return out << territory.name;
}

/* ----------------------------------------------------------- */

// Order
Order::Order() : orderString("Unknown") {}
Order::Order(string orderString) : orderString(orderString) {}
Order::Order(const Order& order) {orderString = order.orderString;}
Order& Order::operator=(const Order& order)
{
	orderString = order.orderString;
	return *this;
}
string Order::getOrder() {return orderString;}
void Order::setOrder(string orderString) {orderString = orderString;}
ostream& operator<<(ostream& out, const Order& order) {
	return out << order.orderString;
}