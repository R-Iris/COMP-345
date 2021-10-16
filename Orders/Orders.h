#pragma once
#include <vector>
#include <string>

using namespace std;

//----------------------Orders class------------------
class Orders{
private:
    bool executed = false;
    string effect;
public:
    Orders();
    //Copy constructor
    Orders(const Orders& o);
    ~Orders(); //Destructor
    Orders& operator = (const Orders& orders); //Assignment operator
    friend ostream& operator << (ostream &strm, Orders& o); //Stream insertion operator
    virtual bool validate();
    virtual void execute();
    virtual string getName();
    void setExecuted(bool exec);
    bool getExecuted() const;
    void setEffect(string eff);
    string getEffect();
};

// ------------OrdersList class-----------------------
class OrdersList{
private:
    vector<Orders*> ordersList;
public:
    explicit OrdersList(vector<Orders*> ordersList); //Parameterised constructor
    OrdersList(const OrdersList& ol);
    ~OrdersList();
    void setOrdersList(vector<Orders*> ordersList);
    vector<Orders*> getOrdersList();
    bool remove(int index);
    bool move(int i,int j);
    friend ostream& operator << (ostream & strm, OrdersList& ordersList);
    void addOrders(Orders* o);
};

/*

//-------------Fake classes :To remove in other assignments------------

class Territory{
private:
    string name;
public:
    explicit Territory(string name);
    vector<Territory*> neighbours;
    bool isNeighbour(Territory* t);
    void setName(string n);
    string getName();
};

class Player{
private:
    string name;
    vector<Territory*> territories;
    OrdersList* ordersList;
public:
    Player(string name, vector<Territory*> territories,OrdersList* ol);
    void setTerritories(vector<Territory *> v);
    void setOrdersList(OrdersList* ol);
    OrdersList* getOrdersList();
    vector<Territory *> getTerritories();
    string getName();
    void setName(string n);
    bool ownsTerritory(Territory *t);
};

//--------------End of Fake classes-------------------

*/

//---------Deploy class-------------------
class Deploy : public Orders{
private:
    Player* orderOwner;
    string name = "Deploy";
    int noOfArmies;
    Territory* target;
public:
    Deploy(Player* orderOwner,int noOfArmies,Territory* target); //Parametrized Constructor.
    Deploy(const Deploy& deploy); //Copy constructor
    Deploy& operator = (const Deploy& deploy); //Assignment operator
    ~Deploy(); //Destructor
    void setNoOfArmies(int noOfArmies);
    int getNoOfArmies() const;
    string getName() override;
    void setTarget(Territory *target);
    Territory *getTarget();
    friend ostream& operator << (ostream & strm, Deploy& deploy);
    bool validate();
    void execute();
};

//------Advance class--------------------------

class Advance : public Orders{
private:
    Player* orderOwner;
    string name = "Advance";
    int noOfArmies;
    Territory* source;
    Territory* target;
public:
    Advance(Player* orderOwner,int noOfArmies, Territory* source, Territory* target); //Parametrized Constructor.
    //Copy constructor
    Advance(const Advance& advance);
    Advance& operator = (const Advance& advance); //Assignment operator
    ~Advance(); //Destructor
    void setNoOfArmies(int noOfArmies);
    string getName() override;
    int getNoOfArmies() const;
    void setSource(Territory* source);
    Territory* getSource();
    void setTarget(Territory *target);
    Territory *getTarget();
    friend ostream& operator << (ostream & strm, Advance& advance);
    bool validate();
    void execute();
};

//--------------Bomb class---------------------

class Bomb : public Orders{
private:
    Player* orderOwner;
    string name = "Bomb";
    Territory* target;
public:
    explicit Bomb(Player* orderOwner,Territory* target);
    //Copy constructor
    Bomb(const Bomb& bomb);
    ~Bomb();
    Bomb& operator = (const Bomb& bomb);
    void setTarget(Territory *target);
    string getName() override;
    Territory *getTarget();
    friend ostream& operator << (ostream & strm, Bomb& bomb);
    bool validate();
    void execute();
};

//--------------Blockade class---------------------

class Blockade : public Orders{
private:
    Player* orderOwner;
    string name = "Blockade";
    int noOfArmies;
    Territory* target;
public:
    Blockade(Player* orderOwner,int noOfArmies,Territory* target);
    //Copy constructor
    Blockade(const Blockade& blockade);
    ~Blockade();
    Blockade& operator = (const Blockade& blockade);
    void setNoOfArmies(int noOfArmies);
    int getNoOfArmies() const;
    string getName() override;
    void setTarget(Territory *target);
    Territory *getTarget();
    friend ostream& operator << (ostream & strm, Blockade& blockade);
    bool validate();
    void execute();
};

//--------------Airlift class---------------------

class Airlift : public Orders{
private:
    Player* orderOwner;
    string name = "Airlift";
    int noOfArmies;
    Territory* source;
    Territory* target;
public:
    Airlift(Player* orderOwner,int noOfArmies, Territory* source, Territory* target);
    //Copy constructor
    Airlift(const Airlift& airlift);
    ~Airlift();
    Airlift& operator = (const Airlift& airlift);
    void setNoOfArmies(int noOfArmies);
    int getNoOfArmies() const;
    void setSource(Territory* source);
    Territory* getSource();
    void setTarget(Territory *target);
    Territory *getTarget();
    string getName() override;
    friend ostream& operator << (ostream & strm, Airlift& airlift);
    bool validate();
    void execute();
};

//--------------Negotiate class---------------------

class Negotiate : public Orders{
private:
    Player* orderOwner;
    string name = "Negotiate";
public:
    Negotiate(Player* orderOwner);
    //Copy constructor
    Negotiate(const Negotiate& negotiate);
    ~Negotiate();
    Negotiate& operator= (const Negotiate& negotiate);
    string getName() override;
    friend ostream& operator << (ostream & strm, Negotiate& negotiate);
    bool validate(Player* otherPlayer);
    void execute(Player* otherPlayer);
};
//---------------------End-------------------------------
