#pragma once // Should be included in all header files to avoid redundant inclusions. Dealt by preprocessor
#include <iostream>
#include <vector>
using namespace std;

class Player {
public:
	Player(class Hand*);
	Player(string name, class Hand*);
	Player(const Player &player);
	~Player();
	Player& operator =(const Player& player);
	void addTerritoryDefend(class Territory*);
	void addTerritoryAttack(class Territory*);
	vector<class Territory*> toDefend();	// return a list of territories that are to be defended (owned territories)
	vector<class Territory*> toAttack();	// returns a list of territories that are to be attacked
	void issueOrder(string);	// creates an Order object and puts it in the player’s list of orders
	string getName();
	class Hand* getHand();
	vector<class Order*> getOrders();
	friend ostream& operator<<(ostream& out, const Player& player);

private:
	string name;
	class Hand* hand;
	vector<class Territory*> territoriesDefend; // List of owned territories
	vector<class Territory*> territoriesAttack; // List of territories to attack
	vector<class Order*> orders;
};

class Territory {
public:
	Territory();
	Territory(string);
	Territory(const Territory& territory);
	Territory& operator =(const Territory& territory);
	string getName();
	void setName(string);
	friend ostream& operator<<(ostream& out, const Territory& territory);
private:
	string name;
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