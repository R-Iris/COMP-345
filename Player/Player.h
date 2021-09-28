#pragma once // Should be included in all header files to avoid redundant inclusions. Dealt by preprocessor
#include <iostream>
#include <vector>
using namespace std;

class Player {
public:
	Player();
	Player(string name, class Hand*);
	void toDefend();	// return a list of territories that are to be defended
	void toAttack();	// returns a list of territories that are to be attacked
	void issueOrder(string);	// creates an Order object and puts it in the player’s list of orders
	string getName();
	class Hand* getHand();

private:
	string name;
	class Hand* hand;
	vector<class Territory*> territories;
	vector<class Order*> orders;
};

class Territory {
public:
	Territory();
	Territory(string);
	string getName();
	void setName(string);
private:
	string name;
};

class Hand {
public:
	Hand();
	Hand(string);
	string getName();
	void setName(string);
private:
	string name;
};

class Order {
public:
	Order();
	Order(string);
	string getOrder();
	void setOrder(string);
private:
	string order;
};