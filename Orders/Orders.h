#pragma once
#include <vector>
#include <string>

#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../Game Engine/GameEngine.h"
#include "../Player/Player.h"
#include "../LoggingObserver/LoggingObserver.h"

using namespace std;

// Forward declaration
class Territory;
class Deck;
class GameEngine;

//----------------------Orders class------------------
class Orders : public ILoggable, public Subject{
private:
	bool executed = false;
	string effect;
public:

	Orders();
	//Copy constructor
	Orders(const Orders& o);
	~Orders(); //Destructor
	Orders& operator = (const Orders& orders); //Assignment operator
	friend ostream& operator << (ostream& strm, Orders& o); //Stream insertion operator
	virtual bool validate();
	virtual void execute();
	virtual string getName();
	void setExecuted(bool exec);
	bool getExecuted() const;
	void setEffect(string eff);
	string getEffect();
	
	//****************** Should this be implemented in each individual order class instead??
	// stringToLog Implementation for ILoggable
	string stringToLog();
	
};

// ------------OrdersList class-----------------------
class OrdersList : public ILoggable, public Subject {
private:

    Player* ordersListOwner;
public:
	explicit OrdersList(Player* ordersListOwner,vector<Orders*>& ordersList); //Parameterised constructor
	OrdersList(const OrdersList& ol);
	~OrdersList();
	void setOrdersList(vector<Orders*>& ordersList);
    vector<Orders*> ordersList;
	bool removeOrder(int index);
	bool move(int i, int j);
	friend ostream& operator << (ostream& strm, OrdersList& ordersList);
	void addOrders(Orders* o);
    void removeOrder(Orders* o);
	
	//******************
	// stringToLog Implementation for ILoggable
	string stringToLog();
	
};

//---------Deploy class-------------------
class Deploy : public Orders {
private:
	GameEngine* game;
	Player* orderOwner;
	string name = "Deploy";
	int noOfArmies;
	Territory* target;
public:
	Deploy(Player* orderOwner, int noOfArmies, Territory* target, GameEngine* game); //Parametrized Constructor.
	Deploy(const Deploy& deploy); //Copy constructor
	Deploy& operator = (const Deploy& deploy); //Assignment operator
	~Deploy(); //Destructor
	void setNoOfArmies(int noOfArmies);
	int getNoOfArmies() const;
	string getName();
	void setTarget(Territory* target);
	Territory* getTarget();
	friend ostream& operator << (ostream& strm, Deploy& deploy);
	bool validate();
	void execute();
};

//------Advance class--------------------------

class Advance : public Orders {
private:
	GameEngine* game;
	Player* orderOwner;
	string name = "Advance";
	int noOfArmies;
	Territory* source;
	Territory* target;
public:
	Advance(Player* orderOwner, int noOfArmies, Territory* source, Territory* target, GameEngine* game); //Parametrized Constructor.
	//Copy constructor
	Advance(const Advance& advance);
	Advance& operator = (const Advance& advance); //Assignment operator
	~Advance(); //Destructor
	void setNoOfArmies(int noOfArmies);
	string getName();
	int getNoOfArmies() const;
	void setSource(Territory* source);
	Territory* getSource();
	void setTarget(Territory* target);
	Territory* getTarget();
	friend ostream& operator << (ostream& strm, Advance& advance);
    bool cannotBeAttacked = false;
	bool validate();
	void execute();
};

//--------------Bomb class---------------------

class Bomb : public Orders {
private:
	GameEngine* game;
	Player* orderOwner;
	string name = "Bomb";
	Territory* target;
public:
	explicit Bomb(Player* orderOwner, Territory* target, GameEngine* game);
	//Copy constructor
	Bomb(const Bomb& bomb);
	~Bomb();
	Bomb& operator = (const Bomb& bomb);
	void setTarget(Territory* target);
	string getName();
	Territory* getTarget();
	friend ostream& operator << (ostream& strm, Bomb& bomb);
	bool validate();
	void execute();
};

//--------------Blockade class---------------------

class Blockade : public Orders {
private:
	GameEngine* game;
	Player* orderOwner;
	string name = "Blockade";
	Territory* target;
public:
	Blockade(Player* orderOwner,Territory* target,GameEngine* gameEngine1);
	//Copy constructor
	Blockade(const Blockade& blockade);
	~Blockade();
	Blockade& operator = (const Blockade& blockade);
	string getName();
	void setTarget(Territory* target);
	Territory* getTarget();
	friend ostream& operator << (ostream& strm, Blockade& blockade);
	bool validate();
	void execute();
};

//--------------Airlift class---------------------

class Airlift : public Orders {
private:
	GameEngine* game;
	Player* orderOwner;
	string name = "Airlift";
	int noOfArmies;
	Territory* source;
	Territory* target;
public:
	Airlift(Player* orderOwner, int noOfArmies, Territory* source, Territory* target, GameEngine* game);
	//Copy constructor
	Airlift(const Airlift& airlift);
	~Airlift();
	Airlift& operator = (const Airlift& airlift);
	void setNoOfArmies(int noOfArmies);
	int getNoOfArmies() const;
	void setSource(Territory* source);
	Territory* getSource();
	void setTarget(Territory* target);
	Territory* getTarget();
	string getName();
	friend ostream& operator << (ostream& strm, Airlift& airlift);
	bool validate();
	void execute();
};

//--------------Negotiate class---------------------

class Negotiate : public Orders {
private:
	GameEngine* game;
	Player* orderOwner;
    Player* otherPlayer;
	string name = "Negotiate";
public:
	Negotiate(Player* orderOwner,Player* otherPlayer, GameEngine* game);
	//Copy constructor
	Negotiate(const Negotiate& negotiate);
	~Negotiate();
	Negotiate& operator= (const Negotiate& negotiate);
	string getName();
	friend ostream& operator << (ostream& strm, Negotiate& negotiate);
	bool validate();
	void execute();
};
//---------------------End-------------------------------
