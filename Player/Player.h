#pragma once // Should be included in all header files to avoid redundant inclusions. Dealt by preprocessor
#include <iostream>
using namespace std;

class Player {
public:
	void toDefend();	// return a list of territories that are to be defended
	void toAttack();	// returns a list of territories that are to be attacked
	void issueOrder();	// creates an Order object and puts it in the player’s list of orders
	//Hand* hand;
};

class Territory {
public:
	string name;
};

class Hand {};

class Order {
public:
	string order;
};