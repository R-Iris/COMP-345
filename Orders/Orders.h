#pragma once
#include <vector>
#include <string>

using namespace std;

//Fake classes
class Territory{
public:
    vector<Territory> neighbours;
    bool isNeighbour(Territory* t);
};

class Player{
private:
    vector<Territory> territories;
public:
    Player();
    Player(vector<Territory> territories);
    //void attack(Territory t);
    bool ownsTerritory(Territory *t);
};
//End of Fake classes

class Orders{

public:
    //Default constructor
    Orders();

    //Copy constructor

    //toString function containing the description of the order
    virtual string toString();

    //Virtual validate method
    //virtual bool validate();

    //Virtual execute method;
    //virtual void execute();

};

class Deploy : public Orders{
public:
    //Default constructor
    Deploy();
    //Parametrized Constructor.

    //Copy constructor

    //toString function containing description of the Deploy Order
    string toString();

    //Validate method
    bool validate(Player p, Territory* t);

    //Execute method
    void execute(Player p,Territory* t);

};

class Advance : public Orders{
public:
    //Default constructor
    Advance();
    //Parametrized Constructor.

    //Copy constructor

    //toString function containing description of the Advance Order
    string toString();

    //Validate method
    bool validate(Player p,Territory* source, Territory* target);

    //Execute method
    void execute(Player p,Territory* source, Territory* target);

};

class Bomb : public Orders{
public:
    //Default constructor
    Bomb();
    //Parametrized Constructor.

    //Copy constructor

    //toString function containing description of the Bomb Order
    string toString();

    //Validate method
    bool validate(Player p,Territory* target);

    //Execute method
    void execute(Player p,Territory* target);

};

class Blockade : public Orders{
public:
    //Default constructor
    Blockade();
    //Parametrized Constructor.

    //Copy constructor

    //toString function containing description of the Blockade Order
    string toString();

    //Validate method
    bool validate(Player p, Territory* target);

    //Execute method
    void execute(Player p, Territory* target);

};

class Airlift : public Orders{
public:
    //Default constructor
    Airlift();
    //Parametrized Constructor.

    //Copy constructor

    //toString function containing description of the Airlift Order
    string toString();

    //Validate method
    bool validate(Player p, Territory *source, Territory *target);

    //Execute method
    void execute(Player p, Territory* source, Territory* target);

};

class Negotiate : public Orders{
public:
    //Default constructor
    Negotiate();
    //Parametrized Constructor.

    //Copy constructor

    //toString function containing description of the Negotiate Order
    string toString();

    //Validate method
    bool validate(Player p1, Player p2);

    //Execute method
    void execute(Player p1,Player p2);

};

