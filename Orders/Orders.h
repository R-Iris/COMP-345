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
    //Parameterised constructor

    Player(string name, vector<Territory*> territories);

    //Copy constructor

    //Getters and setters

    void setTerritories(vector<Territory *> v);
    vector<Territory *> getTerritories();
    string getName();
    void setName(string n);

    //void attack(Territory t);

    bool ownsTerritory(Territory *t);
};

//--------------End of Fake classes-------------------

class Orders{

public:
    //Default constructor
    Orders();

    //Copy constructor

    //Assignment operator

    //Stream insertion operator

    //toString function containing the description of the order
    virtual string toString();

    //Virtual validate method
    //virtual bool validate();

    //Virtual execute method;
    //virtual void execute();

};

//---------Deploy class-------------------
class Deploy : public Orders{
private:
    int noOfArmies;
    Territory* target;
public:
    //Parametrized Constructor.
    Deploy(int noOfArmies,Territory* target);
    //Copy constructor

    //Assignment operator

    //Stream insertion operator

    //Setters and Getters
    void setNoOfArmies(int noOfArmies);

    int getNoOfArmies() const;

    void setTarget(Territory *target);

    Territory *getTarget();

    //toString function containing description of the Deploy Order
    string toString();

    //Validate method
    bool validate(Player p);

    //Execute method
    void execute(Player p);
};


//------Advance class--------------------------
class Advance : public Orders{
private:
    int noOfArmies;
    Territory* source;
    Territory* target;
public:
    //Parametrized Constructor.
    Advance(int noOfArmies, Territory* source, Territory* target);
    //Copy constructor

    //Assignment operator

    //Stream insertion operator

    //Setters and Getters
    void setNoOfArmies(int noOfArmies);

    int getNoOfArmies() const;

    void setSource(Territory* source);

    Territory* getSource();

    void setTarget(Territory *target);

    Territory *getTarget();

    //toString function containing description of the Deploy Order
    string toString();

    //Validate method
    bool validate(Player p);

    //Execute method
    void execute(Player p);

};

//--------------Bomb class---------------------

class Bomb : public Orders{
private:
    Territory* target;
public:
    //Parametrized Constructor.
    explicit Bomb(Territory* target);
    //Copy constructor

    //Assignment operator

    //Stream insertion operator

    //Setters and Getters
    void setTarget(Territory *target);

    Territory *getTarget();

    //toString function containing description of the Deploy Order
    string toString();

    //Validate method
    bool validate(Player p);

    //Execute method
    void execute(Player p);

};

//--------------Blockade class---------------------

class Blockade : public Orders{
private:
    int noOfArmies;
    Territory* target;
public:
    //Parametrized Constructor.
    Blockade(int noOfArmies,Territory* target);
    //Copy constructor

    //Assignment operator

    //Stream insertion operator

    //Setters and Getters
    void setNoOfArmies(int noOfArmies);

    int getNoOfArmies() const;

    void setTarget(Territory *target);

    Territory *getTarget();

    //toString function containing description of the Deploy Order
    string toString();

    //Validate method
    bool validate(Player p);

    //Execute method
    void execute(Player p);

};

//--------------Airlift class---------------------

class Airlift : public Orders{
private:
    int noOfArmies;
    Territory* source;
    Territory* target;
public:
    //Parametrized Constructor.
    Airlift(int noOfArmies, Territory* source, Territory* target);
    //Copy constructor

    //Assignment operator

    //Stream insertion operator

    //Setters and Getters
    void setNoOfArmies(int noOfArmies);

    int getNoOfArmies() const;

    void setSource(Territory* source);

    Territory* getSource();

    void setTarget(Territory *target);

    Territory *getTarget();

    //toString function containing description of the Deploy Order
    string toString();

    //Validate method
    bool validate(Player p);

    //Execute method
    void execute(Player p);
};

//--------------Negotiate class---------------------

class Negotiate : public Orders{
public:
    //Default constructor
    Negotiate();
    //Parametrized Constructor.

    //Copy constructor

    //Assignment operator

    //Stream insertion operator

    //toString function containing description of the Negotiate Order
    string toString();

    //Validate method
    bool validate(Player p1, Player p2);

    //Execute method
    void execute(Player p1,Player p2);

};
