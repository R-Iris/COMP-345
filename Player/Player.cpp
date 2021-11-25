#include "Player.h" // Including the appropriate header file

// Default constructor with hand, and game
Player::Player(Hand* hand, GameEngine* game) : name("Unnamed"), hand(hand), reinforcementPool(0), gameEngine(game) {
	this->ordersList = new OrdersList(this,*new vector<Orders*>);
	ps = new HumanPlayerStrategy(this);
}

// Constructor with name, hand, and game
Player::Player(string name, Hand* hand, GameEngine* game) : name(name), hand(hand), reinforcementPool(0), gameEngine(game) {
	this->ordersList = new OrdersList(this, *new vector<Orders*>);
	ps = new HumanPlayerStrategy(this);
}

Player::Player(string name, Hand* hand, GameEngine* game, PlayerStrategy* strategy) : name(name), hand(hand), reinforcementPool(0), gameEngine(game), ps(strategy)
{
	this->ordersList = new OrdersList(this, *new vector<Orders*>);
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
	ps = player.ps;
}

// Destructor
Player::~Player()
{
	delete hand; // Delete pointer to hand
    delete getOrdersList(); //Delete allocated ordersList in constructor
	//delete ordersList; // Delete pointer to ordersList
	this->ordersList = nullptr;
	// All cleared vectors need their content deleted, depending on how they are initialized (see driver)
	territoriesOwned.clear();
	gameEngine = nullptr;
	delete ps; // Delete player strategy on player deletion
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
	ps = player.ps;
	return *this;
}

// Add territory to own
void Player::addOwnedTerritory(Territory* territory) {
	territoriesOwned.push_back(territory);
    territory->setOwner(this);
}

// Return a list of owned territories (to be defended)
vector<Territory*> Player::toDefend()
{
	ps->toDefend();
}

// Return a list of territories to attack
vector<Territory*> Player::toAttack()
{
	ps->toAttack();
}

// Create a new order and add to order list
void Player::issueOrder()
{
	ps->issueOrder();
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

void Player::setGameEngine(GameEngine* game)
{
	this->gameEngine = game;
}

GameEngine* Player::getGameEngine()
{
	return gameEngine;
}

// Stream insertion operator, returns player's name
ostream& operator<<(ostream& out, const Player& player) {
	return out << player.name;
}

void Player::removeOwnedTerritory(Territory * territory) {
	territoriesOwned.erase(remove(territoriesOwned.begin(), territoriesOwned.end(), territory), territoriesOwned.end());
}

vector<Territory*> Player::getOwnedTerritories()
{
	return territoriesOwned;
}

void Player::setOwnedTerritories(vector<Territory *> & newVector) {
    territoriesOwned = newVector;
}

PlayerStrategy* Player::getPlayerStrategy()
{
	return ps;
}

void Player::setPlayerStrategy(PlayerStrategy* strategy)
{
	delete ps;
	ps = strategy;
}
