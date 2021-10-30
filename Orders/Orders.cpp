#include "Orders.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Orders& o){
    return strm << "Order has been called";
}

Orders::Orders()= default;

bool Orders::getExecuted() const {
    return executed;
}
void Orders::setExecuted(bool exec) {
    this->executed = exec;
}

string Orders::getEffect() {
    return this->effect;
}
void Orders::setEffect(string eff) {
    effect = eff;
}

//Implemented in other child classes -- Virtual function
bool Orders::validate() {
    return false;
}

//Implemented in order child classes -- Virtual function
void Orders::execute() {}

string Orders::getName() {return {};}

Orders::Orders(const Orders &o) = default; //Copy constructor
Orders::~Orders() = default; //Destructor
Orders& Orders::operator= (const Orders& orders)= default; //Assignment operator overload

/*
//*********************
// method from ILoggable
ostream& Orders::stringToLog(ostream& os)
{
    os << this;
    return os;
}
*/

//------------------Deploy class--------------------

Deploy::Deploy(Player* orderOwner,int noOfArmies, Territory* target) {
    this->orderOwner = orderOwner;
    this->noOfArmies = noOfArmies;
    this->target = target;
}

void Deploy::setNoOfArmies(int army){
    this->noOfArmies = army;
}

int Deploy::getNoOfArmies() const{
    return this->noOfArmies;
}

void Deploy::setTarget(Territory* t){
    this->target = t;
}

Territory* Deploy::getTarget(){
    return this->target;
}

string Deploy::getName() {return name;}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Deploy& deploy){
    string s1 = "Deploy order\n";
    if(deploy.getExecuted()){
        return strm << s1 + deploy.getEffect();
    }
    else return strm << s1;
}

//Assignment operator overload
Deploy& Deploy::operator = (const Deploy& deploy){
    //Intentionally shallow copying data members of deploy class since no new members are being created
    this->orderOwner = deploy.orderOwner;
    this->noOfArmies = deploy.noOfArmies;
    this->target = deploy.target;
    return *this;
}

//Validate method checking if orderOwner owns target territory and number of armies is valid
bool Deploy::validate() {
    //If the target territory does not belong to the player that issued the order, the order is invalid
    if(orderOwner->ownsTerritory(getTarget()) && getNoOfArmies() > 0) {
        cout << "Deploy order is valid" << endl;
        return true;
    }
    cout << "Deploy order is invalid since player " + orderOwner->getName() + " does not own " + target->getName() + " territory" <<endl;
    return false;
}

//Executing method if valid -- Only printing strings for now
void Deploy::execute() {
    if (validate()) {
        cout << "Executing the deploy order" << endl;
        //Moving armies
        int newNoOfArmies = getTarget()->getNumberOfArmies() + noOfArmies;
        getTarget()->setNumberOfArmies(newNoOfArmies);
        //Printing message
        setEffect("Player " + orderOwner->getName() + " has deployed " + to_string(getNoOfArmies()) +
        " armies to territory " + target->getName() + ". New army count = " + to_string(getTarget()->getNumberOfArmies())
         + "\n");
        cout << getEffect();
        setExecuted(true);
    }
    else {
        cout << "The deploy call failed to execute" << endl;
    }
}
//Copy constructor
Deploy::Deploy(const Deploy &deploy) {
    //Intentionally shallow copying data members of deploy class since no new members are being created
    this->orderOwner = deploy.orderOwner;
    this->target = deploy.target;
    this->noOfArmies = deploy.noOfArmies;
}

//Destructor is default since no new data members being created in the class
Deploy::~Deploy()= default;

//------------------------------Advance class---------------------

Advance::Advance(Player* orderOwner,int n, Territory *s, Territory *t) {
    this->orderOwner = orderOwner;
    this->noOfArmies = n;
    this->source = s;
    this->target = t;
}

int Advance::getNoOfArmies() const {
    return noOfArmies;
}

void Advance::setNoOfArmies(int n) {
    this->noOfArmies = n;
}

Territory* Advance::getTarget() {
    return target;
}

void Advance::setTarget(Territory *t) {
    target = t;
}

Territory* Advance::getSource() {
    return source;
}
void Advance::setSource(Territory *s) {
    source = s;
}

string Advance::getName() {return name;}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Advance& advance){
    string s1 = "Advance order\n";
    if(advance.getExecuted()){
        return strm << s1 + advance.getEffect();
    }
    else return strm << s1;
}

//Advance order valid only if target is neighbour of source
bool Advance::validate() {
    //If the source territory does not belong to the player that issued the order, the order is invalid.
    if(!orderOwner->ownsTerritory(source)){
        cout << "Deploy order not valid" << endl;
        cout << "Source territory does not belong to player " + orderOwner->getName() << endl;
        return false;
    }
    //If the target territory is not adjacent to the source territory, the order is invalid.
    bool targetAdj = false;
    for(auto it: getTarget()->getAdjacentTerritories()){
        if(it == source){
            targetAdj = true;
        }
    }
    if(!targetAdj){
        cout << "Deploy order not valid" << endl;
        cout << "Target territory( " + getTarget()->getName() + ") not adjacent to source territory(" + source->getName() + ")" << endl;
        return false;
    }
    cout << "Advance order valid" << endl;
    return true;
}
//If valid, checking if target is owner territory or enemy territory before executing
void Advance::execute() {
    if(validate()){
        //If the source and target territory both belong to the player that issued the order, the army units are moved
        //from the source to the target territory.
        if(orderOwner->ownsTerritory(target)){
            cout << "Executing advance order" << endl;
            //Moving armies from source to target territory
            int initialSourceArmy = source->getNumberOfArmies();
            int initialTargetArmy = target->getNumberOfArmies();
            target->setNumberOfArmies(initialTargetArmy + noOfArmies);
            source->setNumberOfArmies(initialSourceArmy - noOfArmies);
            setEffect("Player " + orderOwner->getName() + " has moved " + to_string(getNoOfArmies()) + " armies from " + source->getName()
            + " territory to " + target->getName() + " territory \n");
            cout << getEffect();
        }
        //If the target territory belongs to another player than the player that issued the advance order, an attack is
        //simulated when the order is executed. An attack is simulated by the following battle simulation
        //mechanism:
        //1.Each attacking army unit involved has 60% chances of killing one defending army. At the same time,
        //each defending army unit has 70% chances of killing one attacking army unit.
        //2.If all the defender's armies are eliminated, the attacker captures the territory. The attacking army units
        //that survived the battle then occupy the conquered territory.
        //3.A player receives a card at the end of his turn if they successfully conquered at least one territory
        //during their turn.
        else{
            cout << "Executing advance order" << endl;
            //Random int from 1 to 10
            int randNumber = rand() % 10 + 1;
            //Reducing source army
            source->setNumberOfArmies(source->getNumberOfArmies() - noOfArmies);
            int attackingArmy = noOfArmies;
            int defendingArmy = target->getNumberOfArmies();
            for(int i = 0;i <noOfArmies;i++){
                if(randNumber <= 6){
                    defendingArmy--;
                }
                if(randNumber <=7){
                    attackingArmy--;
                }
                if(defendingArmy == 0){
                    //Attacker captures territory
                    target->setOwner(orderOwner);
                    target->setNumberOfArmies(attackingArmy);
                    //A player receives a card at the end of his turn if
                    //they successfully conquered at least one territory during their turn.

                }
                else if(attackingArmy == 0){
                    //Nothing happens-- Battle lost
                }
            }
            setEffect("Player " + orderOwner->getName() + " attacking " + target->getName() + " territory\n");
            cout << getEffect();
        }
        setExecuted(true);
    }
    else{
        cout << "The advance call was not executed since it was invalid" << endl;
    }
}
//Assignment operator overload
//Intentionally shallow copying data members of deploy class since no new members are being created
Advance &Advance::operator=(const Advance &advance) {
    this->orderOwner = advance.orderOwner;
    this->target = advance.target;
    this->source = advance.source;
    this->noOfArmies = advance.noOfArmies;
    return *this;
}

//Intentionally shallow copying data members of deploy class since no new members are being created
Advance::Advance(const Advance &advance) {
    this->orderOwner = advance.orderOwner;
    this->target = advance.target;
    this->source = advance.source;
    this->noOfArmies = advance.noOfArmies;
}

//Destructor is default since no new data members being created in the class
Advance::~Advance() = default;

//------------------------------Bomb class---------------------

Bomb::Bomb(Player* orderOwner, Territory *target) {
    this->orderOwner = orderOwner;
    this->target = target;
}

Territory* Bomb::getTarget() {
    return target;
}

void Bomb::setTarget(Territory *t) {
    target = t;
}

string Bomb::getName() {return name;}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Bomb& bomb){
    string s1 = "Bomb order\n";
    if(bomb.getExecuted()){
        return strm << s1 + bomb.getEffect();
    }
    else return strm << s1;
}

bool Bomb::validate() {
    //If the target belongs to the player that issued the order, the order is invalid.
    if(orderOwner->ownsTerritory(target)) {
        cout << "Target belongs to order owner. Cannot bomb it" << endl;
        return false;
    }
    //If the target territory is not adjacent to one of the territory owned by the player issuing the order, then the
    //order is invalid
    bool targetAdj = false;
    for(auto it: target->getAdjacentTerritories()){
        if(orderOwner->ownsTerritory(it)) targetAdj = true;
    }
    if(!targetAdj){
        cout << "Bomb order invalid --> No territory owned adjacent to target territory " << endl;
    }
    cout << "Bomb order valid" << endl;
    return true;

}
//If valid, checking if target territory is owned by player before executing
void Bomb::execute() {
    if(validate()){
            cout << "Executing bomb order" << endl;
            //Reducing enemy army by half
            target->setNumberOfArmies(target->getNumberOfArmies()/2);
            setEffect("Successfully bombed " + target->getName() + " territory\n");
            cout << getEffect();
            setExecuted(true);
    }
    else{
        cout << "The bomb order was not executed since it was invalid" << endl;
    }
}
//Assignment operator overload
//Intentionally shallow copying data members of deploy class since no new members are being created
Bomb &Bomb::operator=(const Bomb &bomb) {
    this->orderOwner = bomb.orderOwner;
    this->target = bomb.target;
    return *this;
}

//Intentionally shallow copying data members of deploy class since no new members are being created
Bomb::Bomb(const Bomb &bomb) {
    this->orderOwner = bomb.orderOwner;
    this->target = bomb.target;
}

//Destructor is default since no new data members being created in the class
Bomb::~Bomb() = default;

//------------------------------Blockade class---------------------

Blockade::Blockade(Player* orderOwner,int noOfArmies, Territory *target) {
    this->orderOwner = orderOwner;
    this->noOfArmies = noOfArmies;
    this->target = target;
}

void Blockade::setTarget(Territory *t) {
    target= t;
}

Territory* Blockade::getTarget() {
    return target;
}

int Blockade::getNoOfArmies() const {
    return noOfArmies;
}

void Blockade::setNoOfArmies(int n) {
    noOfArmies = n;
}

string Blockade::getName() {return name;}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Blockade& blockade){
    string s1 = "Blockade order\n";
    if(blockade.getExecuted()){
        return strm << s1 + blockade.getEffect();
    }
    else return strm << s1;
}

//The blockade order can only be created by playing the blockade card
bool Blockade::validate() {
    //If the target territory belongs to an enemy player, the order is declared invalid.
    if(!orderOwner->ownsTerritory(target)){
        cout << "Order invalid -- Target territory belongs to enemy player" << endl;
    }
    return false; // TO CHANGE TO CHANGE TO CHANGE
}

//Executing order if valid -- Only printing strings
void Blockade::execute() {
    if(validate()){
        cout << "Executing blockade order" << endl;
        //Doubling number of armies and transferring ownership
        target->setNumberOfArmies(target->getNumberOfArmies() * 2);
        //Ownership of the territory is transferred to the Neutral player, which must be created if it
        //does not already exist.
        target->setOwner(nullptr);
        setEffect("Successfully tripled the number of armies in " + target->getName() + " territory\n");
        cout << getEffect();
        setExecuted(true);
    }
    else{
        cout << "The blockade order was not executed" << endl;
    }
}

//Assignment operator overload
//Intentionally shallow copying data members of deploy class since no new members are being created
Blockade &Blockade::operator=(const Blockade &blockade) {
    this->orderOwner = blockade.orderOwner;
    this->target = blockade.target;
    this->noOfArmies = blockade.noOfArmies;
    return *this;
}

//Intentionally shallow copying data members of deploy class since no new members are being created
Blockade::Blockade(const Blockade &blockade) {
    this->orderOwner = blockade.orderOwner;
    this->target = blockade.target;
    this->noOfArmies = blockade.noOfArmies;
}

//Destructor is default since no new data members being created in the class
Blockade::~Blockade() = default;


//------------------------------Airlift class---------------------

Airlift::Airlift(Player* orderOwner,int n, Territory *s, Territory *t) {
    this->orderOwner = orderOwner;
    this->noOfArmies = n;
    this->source = s;
    this->target = t;
}

int Airlift::getNoOfArmies() const {
    return noOfArmies;
}

void Airlift::setNoOfArmies(int n) {
    this->noOfArmies = n;
}

Territory* Airlift::getTarget() {
    return target;
}

void Airlift::setTarget(Territory *t) {
    target = t;
}

Territory* Airlift::getSource() {
    return source;
}
void Airlift::setSource(Territory *s) {
    source = s;
}

string Airlift::getName() {return name;}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Airlift& airlift){
    string s1 = "Airlift order\n";
    if(airlift.getExecuted()){
        return strm << s1 + airlift.getEffect();
    }
    else return strm << s1;
}
//Airlift order valid if source territory is owned by OrderOwner
bool Airlift::validate() {
    if(!orderOwner->ownsTerritory(source)){
        cout << "Airlift order not valid -- " + orderOwner->getName() +
        " does not own " + source->getName() + "(source) territory" << endl;
        return false;
    }
    else if(!orderOwner->ownsTerritory(target)){
        cout << "Airlift order not valid -- " + orderOwner->getName() +
        " does not own " + target->getName() + "(target) territory" << endl;
        return false;
    }
    cout << "Airlift order valid" << endl;
    return true;
}

//Airlift order is executed if valid
void Airlift::execute() {
    if(validate()){
        cout << "Executing Airlift order" << endl;
        //Moving armies
        target->setNumberOfArmies(target->getNumberOfArmies() + noOfArmies);
        source->setNumberOfArmies(source->getNumberOfArmies() - noOfArmies);
        setEffect("Successfully moved " + to_string(getNoOfArmies()) + " armies from " +
        source->getName() + " to " + target->getName() + " territory via airlift\n");
        cout << getEffect();
        setExecuted(true);
    }
    else{
        cout << "Airlift order has not been executed" <<endl;
    }
}

//Assignment operator overload
//Intentionally shallow copying data members of deploy class since no new members are being created
Airlift &Airlift::operator=(const Airlift &airlift) {
    this->orderOwner = airlift.orderOwner;
    this->source = airlift.source;
    this->target = airlift.target;
    this->noOfArmies = airlift.noOfArmies;
    return *this;
}

//Intentionally shallow copying data members of deploy class since no new members are being created
Airlift::Airlift(const Airlift &airlift) {
    this->orderOwner = airlift.orderOwner;
    this->source = airlift.source;
    this->target = airlift.target;
    this->noOfArmies = airlift.noOfArmies;
}

//Destructor is default since no new data members being created in the class
Airlift::~Airlift() = default;

//--------------------------Negotiate class------------------

Negotiate::Negotiate(Player* orderOwner){
    this->orderOwner = orderOwner;
}

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Negotiate& negotiate){
    string s1 = "Negotiate order\n";
    if(negotiate.getExecuted()){
        return strm << s1 + negotiate.getEffect();
    }
    else return strm << s1;
}

//A negotiate order targets an enemy player. It results in the target player and the player issuing
//the order to not be able to successfully attack each others’ territories for the remainder of the turn. The negotiate
//order can only be created by playing the diplomacy card.
bool Negotiate::validate(Player* otherPlayer) {
    //If the target is the player issuing the order, then the order is invalid.
    if(orderOwner == otherPlayer){
        cout << "You cannot negotiate with yourself" << endl;
        return false;
    }
    cout << "Negotiate order valid" << endl;
    return true;
}

//Negotiate method always being exected since validate method not yet implemented.
void Negotiate::execute(Player* otherPlayer) {
    //If the target is an enemy player, then the effect is that any attack that may be declared between territories
    //of the player issuing the negotiate order and the target player will result in an invalid order.
    if(validate(otherPlayer)){
        cout << "Executing Negotiate order" << endl;

        setEffect("Attacking between " + orderOwner->getName() + " and " + otherPlayer->getName() + " have been prevented until the end of the turn\n");
        cout << getEffect();
        setExecuted(true);
    }
    else{
        cout << "Airlift order has not been executed" << endl;
    }
}
//Intentionally shallow copying data members of deploy class since no new members are being created
Negotiate::Negotiate(const Negotiate &negotiate) {
    this->orderOwner = negotiate.orderOwner;
}

//Destructor is default since no new data members being created in the class
Negotiate::~Negotiate() = default;

//Intentionally shallow copying data members of deploy class since no new members are being created
Negotiate &Negotiate::operator=(const Negotiate &negotiate) {
    this->orderOwner = negotiate.orderOwner;
    return *this;
}

string Negotiate::getName() {return name;}

//Start of OrdersList class implementation

OrdersList::OrdersList(vector<Orders *> ordersList) {
    this->ordersList = ordersList;
}

void OrdersList::setOrdersList(vector<Orders*> orderList) {
    this->ordersList = orderList;
}

vector<Orders*>  OrdersList::getOrdersList() {
    return this->ordersList;
}

//Removing order by index --> invalid indexes checked
bool OrdersList::remove(int index) {
    cout << "Trying to remove order " + ordersList.at(index)->getName() + " from the list" << endl;
    if(index < 0 || index >= ordersList.size()){
        cout << "Index specified not in range of vector size" << endl;
        return false;
    }
    //If last element has to be removed
    else if(index +1 == ordersList.size()){
        ordersList.pop_back();
        cout << "Last order in list removed" << endl;
        return true;
    }
    else{
        ordersList.erase(ordersList.begin()+index);
        cout << "Order successfully removed" << endl;
        return true;
    }
}


//Moving orders from one index to another using the rotate algorithm
bool OrdersList::move(int i, int j) {
    cout << "Trying to move order " << ordersList.at(i)->getName() << " from position " << i << " to position " << j <<  " in the list " << endl;
    if(i < 0 || i >= ordersList.size() || j < 0 || j >= ordersList.size()) {
        cout << "Indexes specified not in range of vector size" << endl;
        return false;
    }
    else{
        if(i > j){
            rotate(ordersList.rend() - i - 1, ordersList.rend() - i, ordersList.rend() - j);
        }
        else{
            rotate(ordersList.begin() + i, ordersList.begin() + 1, ordersList.begin() + j + 1);
        }
        cout << "Order position successfully switched" << endl << endl;
        return true;
    }
}

//Destructor for ordersList, deleting each order pointer before clearing the vector
OrdersList::~OrdersList() {
    for(auto & it : ordersList){
        delete it;
    }
    ordersList.clear();
}
//New order is created and put in the list but the data members of the order are still a shallow copy since no new members needed to be created
OrdersList::OrdersList(const OrdersList& ol){
    vector<Orders*> newOrdersList;
    for(auto& it: ordersList){
        Orders* newOrder = new Orders(*it);
        newOrdersList.push_back(newOrder);
    }
    this->ordersList = newOrdersList;
}

//Stream insertion operator overload --> Printing all orders(name only)
ostream &operator<<(ostream &strm, OrdersList &ordersList) {
    cout << "Printing out the ordersList" << endl;
    for(auto& it : ordersList.ordersList){
        cout << it->getName() + " -> ";
    }
    return strm << "END" << endl;
}

void OrdersList::addOrders(Orders *o) {
    ordersList.push_back(o);
}


/*
//*********************
// method from ILoggable
ostream& OrdersList::stringToLog(ostream& os)
{
    os << this;
    return os;
}
*/

//End of OrdersList class implementation
