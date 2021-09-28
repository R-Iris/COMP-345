#include "Player.h" // Including the appropriate header file

Player::Player() {
	
}

Player::Player(string name, Hand* hand) : name(name), hand(hand)
{
}

void Player::toDefend() // return a list of territories that are to be defended
{

}

void Player::toAttack() // returns a list of territories that are to be attacked
{

}

void Player::issueOrder(string order) // creates an Order object and puts it in the player’s list of orders
{

}

string Player::getName() {return string();}
Hand* Player::getHand() {return hand;}

Hand::Hand() : name("Empty Hand") {}
Hand::Hand(string name) : name(name) {}
string Hand::getName() {return string();}
void Hand::setName(string name) {name = name;}

Territory::Territory() : name("Undiscovered") {}
Territory::Territory(string name) : name(name) {}
string Territory::getName() {return string();}
void Territory::setName(string name) {name = name;}

Order::Order() : order("Unknown") {}
Order::Order(string order) : order(order) {}
string Order::getOrder() {return string();}
void Order::setOrder(string order) {order = order;}