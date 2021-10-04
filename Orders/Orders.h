#pragma once
#include <vector>
#include <string>

using namespace std;

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
public:
    Player(string name, vector<Territory*> territories);
    void setTerritories(vector<Territory *> v);
    vector<Territory *> getTerritories();
    string getName();
    void setName(string n);
    bool ownsTerritory(Territory *t);
};

//--------------End of Fake classes-------------------



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
    friend ostream& operator << (ostream &strm, Orders* o); //Stream insertion operator
    virtual string toString();
    void setExecuted(bool exec);
    bool getExecuted() const;
    void setEffect(string eff);
    string getEffect();
};

//---------Deploy class-------------------
class Deploy : public Orders{
private:
    int noOfArmies;
    Territory* target;
public:
    Deploy(int noOfArmies,Territory* target); //Parametrized Constructor.
    Deploy(const Deploy& deploy); //Copy constructor
    Deploy& operator = (const Deploy& deploy); //Assignment operator
    ~Deploy(); //Destructor
    void setNoOfArmies(int noOfArmies);
    int getNoOfArmies() const;
    void setTarget(Territory *target);
    Territory *getTarget();
    string toString() override;
    bool validate(Player p);
    void execute(Player p);
};

//------Advance class--------------------------

class Advance : public Orders{
private:
    int noOfArmies;
    Territory* source;
    Territory* target;
public:
    Advance(int noOfArmies, Territory* source, Territory* target); //Parametrized Constructor.
    //Copy constructor
    Advance(const Advance& advance);
    Advance& operator = (const Advance& advance); //Assignment operator
    ~Advance(); //Destructor
    void setNoOfArmies(int noOfArmies);
    int getNoOfArmies() const;
    void setSource(Territory* source);
    Territory* getSource();
    void setTarget(Territory *target);
    Territory *getTarget();
    string toString() override;
    bool validate(Player p);
    void execute(Player p);
};

//--------------Bomb class---------------------

class Bomb : public Orders{
private:
    Territory* target;
public:
    explicit Bomb(Territory* target);
    //Copy constructor
    Bomb(const Bomb& bomb);
    ~Bomb();
    Bomb& operator = (const Bomb& bomb);
    void setTarget(Territory *target);
    Territory *getTarget();
    string toString() override;
    bool validate(Player p);
    void execute(Player p);
};

//--------------Blockade class---------------------

class Blockade : public Orders{
private:
    int noOfArmies;
    Territory* target;
public:
    Blockade(int noOfArmies,Territory* target);
    //Copy constructor
    Blockade(const Blockade& blockade);
    ~Blockade();
    Blockade& operator = (const Blockade& blockade);
    void setNoOfArmies(int noOfArmies);
    int getNoOfArmies() const;
    void setTarget(Territory *target);
    Territory *getTarget();
    string toString() override;
    bool validate(Player p);
    void execute(Player p);
};

//--------------Airlift class---------------------

class Airlift : public Orders{
private:
    int noOfArmies;
    Territory* source;
    Territory* target;
public:
    Airlift(int noOfArmies, Territory* source, Territory* target);
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
    string toString() override;
    bool validate(Player p);
    void execute(Player p);
};

//--------------Negotiate class---------------------

class Negotiate : public Orders{
public:
    Negotiate();
    //Copy constructor
    Negotiate(const Negotiate& negotiate);
    ~Negotiate();
    Negotiate& operator= (const Negotiate& negotiate);
    string toString() override;
    bool validate(Player p1, Player p2);
    void execute(Player p1,Player p2);
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
    void print();
};

//---------------------End-------------------------------
