#include "Player.h" // Including the appropriate header file

Player::Player(Hand* hand) : name("Unnamed"), hand(hand) {}
Player::Player(string name, Hand* hand) : name(name), hand(hand){}
Player::Player(const Player& player)
{
	name = player.name;
	this->hand = new Hand(*(player.hand));
	territoriesDefend = player.territoriesDefend;
	territoriesAttack = player.territoriesAttack;
	orders = player.orders;
}

Player::~Player()
{
	delete hand;
	territoriesDefend.clear();
	territoriesAttack.clear();
	orders.clear();
}

Player& Player::operator=(const Player& player)
{
	name = player.name;
	this->hand = new Hand(*(player.hand));
	territoriesDefend = player.territoriesDefend;
	territoriesAttack = player.territoriesAttack;
	orders = player.orders;
	return *this;
}

void Player::addTerritoryDefend(Territory* territory)
{
	territoriesDefend.push_back(territory);
}

void Player::addTerritoryAttack(Territory* territory)
{
	territoriesAttack.push_back(territory);
}

vector<class Territory*> Player::toDefend() // Returns a list of territories that are to be defended
{
	return territoriesDefend;
}

vector<class Territory*> Player::toAttack() // Returns a list of territories that are to be attacked
{
	return territoriesAttack;
}

void Player::issueOrder(string order) // Creates an Order object and puts it in the player’s list of orders
{
	orders.push_back(new Order(order));
}

string Player::getName() {return name;}
Hand* Player::getHand() {return hand;}

vector<class Order*> Player::getOrders()
{
	return orders;
}
ostream& operator<<(ostream& out, const Player& player) {
	return out << "This player's name: " << player.name;
}

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