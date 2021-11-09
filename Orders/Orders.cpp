#include "Orders.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Orders& o){
    return strm << "Order has been called";
}

Orders::Orders() = default;

bool Orders::getExecuted() const {
    return executed;
}
void Orders::setExecuted(bool exec) {
    this->executed = exec;
}

string Orders::getEffect() {
    return this->effect;
}
string Orders::stringToLog()
{
    return "Order: " + getName() + ", Effect: " + getEffect();
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


//------------------Deploy class--------------------

Deploy::Deploy(Player* orderOwner,int noOfArmies, Territory* target, GameEngine* game) {
    this->game = game;
    this->Attach(game->_observer);
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
    this->game = deploy.game;
    this->Attach(deploy.game->_observer);
    this->orderOwner = deploy.orderOwner;
    this->noOfArmies = deploy.noOfArmies;
    this->target = deploy.target;
    return *this;
}

//Validate method checking if orderOwner owns target territory and number of armies is valid
bool Deploy::validate() {
    if(getExecuted()){
        cout << "Order already executed" << endl;
        return false;
    }
    //If the target territory does not belong to the player that issued the order, the order is invalid
    if(orderOwner->ownsTerritory(getTarget()) && getNoOfArmies() > 0) {
        cout << "Deploy order is valid" << endl;
        return true;
    }
    cout << "Deploy order is invalid since " + orderOwner->getName() + " does not own " + target->getName() + " territory" <<endl;
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
        setEffect(orderOwner->getName() + " has deployed " + to_string(getNoOfArmies()) +
        " armies to territory " + target->getName() + ". New army count = " + to_string(getTarget()->getNumberOfArmies())
         + "\n");
        cout << getEffect();
        setExecuted(true);
    }
    else {
        setEffect("The deploy call failed to execute\n");
        cout << getEffect();
    }
    Notify(this);
}
//Copy constructor
Deploy::Deploy(const Deploy &deploy) {
    //Intentionally shallow copying data members of deploy class since no new members are being created
    this->game = deploy.game;
    this->Attach(deploy.game->_observer);
    this->orderOwner = deploy.orderOwner;
    this->target = deploy.target;
    this->noOfArmies = deploy.noOfArmies;
}

//Destructor is default since no new data members being created in the class
Deploy::~Deploy() { 
    game = nullptr;
    this->Detach();
};

//------------------------------Advance class---------------------

Advance::Advance(Player* orderOwner,int n, Territory *s, Territory *t, GameEngine* game) {
    this->game = game;
    this->Attach(game->_observer);
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
    if(getExecuted()){
        cout << "Order already executed" << endl;
        return false;
    }
    //If the source territory does not belong to the player that issued the order, the order is invalid.
    if(!orderOwner->ownsTerritory(source)){
        cout << "Advance order not valid" << endl;
        cout << "Source territory does not belong to " + orderOwner->getName() << endl;
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
        cout << "Target territory (" + getTarget()->getName() + ") not adjacent to source territory(" + source->getName() + ")" << endl;
        return false;
    }
    //If source territory does not have enough armies
    if(source->getNumberOfArmies() < getNoOfArmies()){
        cout << "Advance order invalid" << endl;
        cout << "Not enough armies from source to advance to target territory" << endl;
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
            setEffect(orderOwner->getName() + " has moved " + to_string(getNoOfArmies()) + " armies from " + source->getName()
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
            Player* enemy = target->getOwner();
            for(auto it: enemy->cannotAttack){
                if(it == orderOwner){
                    cout << "You cannot attack this player's territory for the remainder of this turn" << endl;
                    return;
                }
            }
            cout << "Executing advance order" << endl;

            cout << "Attack between " + orderOwner->getName() + " and " + enemy->getName() + " initiated" << endl;

            //Random int from 1 to 10
            int randNumber = rand() % 10 + 1;
            //Reducing source army
            if(source->getNumberOfArmies() - noOfArmies < 0){
                //If not enough army is in source territory , use only army in source territory
                source->setNumberOfArmies(0);
                noOfArmies = source->getNumberOfArmies();
            }
            else source->setNumberOfArmies(source->getNumberOfArmies() - noOfArmies);
            int attackingArmy = noOfArmies;
            int defendingArmy = target->getNumberOfArmies();
            for(int i = 0;;i++){
                if(randNumber <= 6){
                    defendingArmy--;
                }
                if(randNumber <=7){
                    attackingArmy--;
                }
                if(defendingArmy == 0){
                    cout << orderOwner->getName() + " won the battle and has captured territory " + target->getName()
                    << " successfully" << endl;
                    cout << "Number of armies on defeated target territory is now " << attackingArmy <<endl;
                    //Attacker captures territory
                    target->setNumberOfArmies(attackingArmy);
                    orderOwner->addOwnedTerritory(target);
                    //A player receives a card at the end of his turn if
                    //they successfully conquered at least one territory during their turn.
                    orderOwner->getHand()->addHand(game->deck->draw());
                    setEffect(orderOwner->getName() + " won battle against "
                    + enemy->getName() + "and takes " + target->getName() + " territory\n");
                    break;
                }
                if(attackingArmy == 0){
                    //Nothing happens-- Battle lost
                    cout << orderOwner->getName() + " lost the battle" << endl;
                    cout << "Remaining number of armies on enemy territory is " << target->getNumberOfArmies() << endl;
                    setEffect(orderOwner->getName() + " attacks " + enemy->getName() + " territory " +
                    target->getName() + " and lost.");
                    break;
                }
                randNumber = rand() % 10 + 1;
            }
        }
        setExecuted(true);
    }
    else{
        setEffect("The advance call was not executed since it was invalid\n");
        cout << getEffect() << endl;
    }
    Notify(this);
}
//Assignment operator overload
//Intentionally shallow copying data members of deploy class since no new members are being created
Advance &Advance::operator=(const Advance &advance) {
    this->game = advance.game;
    this->Attach(advance.game->_observer);
    this->orderOwner = advance.orderOwner;
    this->target = advance.target;
    this->source = advance.source;
    this->noOfArmies = advance.noOfArmies;
    return *this;
}

//Intentionally shallow copying data members of deploy class since no new members are being created
Advance::Advance(const Advance &advance){
    this->game = advance.game;
    this->Attach(advance.game->_observer);
    this->orderOwner = advance.orderOwner;
    this->target = advance.target;
    this->source = advance.source;
    this->noOfArmies = advance.noOfArmies;
}

//Destructor is default since no new data members being created in the class
Advance::~Advance() {
    game = nullptr;
    this->Detach();
};

//------------------------------Bomb class---------------------

Bomb::Bomb(Player* orderOwner, Territory *target, GameEngine* game) {
    this->game = game;
    this->Attach(game->_observer);
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
    if(getExecuted()){
        cout << "Order already executed" << endl;
        return false;
    }
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
        return false;
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
        setEffect("The bomb order was not executed since it was invalid\n");
        cout << getEffect() << endl;
    }
    Notify(this);
}
//Assignment operator overload
//Intentionally shallow copying data members of deploy class since no new members are being created
Bomb &Bomb::operator=(const Bomb &bomb) {
    this->game = bomb.game;
    this->Attach(bomb.game->_observer);
    this->orderOwner = bomb.orderOwner;
    this->target = bomb.target;
    return *this;
}

//Intentionally shallow copying data members of deploy class since no new members are being created
Bomb::Bomb(const Bomb &bomb) {
    this->game = bomb.game;
    this->Attach(bomb.game->_observer);
    this->orderOwner = bomb.orderOwner;
    this->target = bomb.target;
}

//Destructor is default since no new data members being created in the class
Bomb::~Bomb() {
    game = nullptr;
    this->Detach();
};

//------------------------------Blockade class---------------------

Blockade::Blockade(Player* orderOwner, Territory *target,GameEngine* gameEngine1) {
    this->game = gameEngine1;
    this->Attach(gameEngine1->_observer);
    this->orderOwner = orderOwner;
    this->target = target;

}

void Blockade::setTarget(Territory *t) {
    target= t;
}

Territory* Blockade::getTarget() {
    return target;
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
//A blockade order targets a territory that belongs to the player issuing the order. Its effect is to
//double the number of armies on the territory and to transfer the ownership of the territory to the Neutral player.
//The blockade order can only be created by playing the blockade card.
bool Blockade::validate() {
    if(getExecuted()){
        cout << "Order already executed" << endl;
        return false;
    }
    //If the target territory belongs to an enemy player, the order is declared invalid.
    if(!orderOwner->ownsTerritory(target)){
        cout << "Order invalid -- Target territory belongs to enemy player" << endl;
        return false;
    }
    return true;
}

//Executing order if valid
void Blockade::execute() {
    if(validate()){
        cout << "Executing blockade order" << endl;
        //Doubling number of armies and transferring ownership
        target->setNumberOfArmies(target->getNumberOfArmies() * 2);
        //Ownership of the territory is transferred to the Neutral player, which must be created if it
        //does not already exist.
        target->setOwner(game->getNeutralPlayer());
        orderOwner->removeOwnedTerritory(target);
        setEffect("Successfully doubled the number of armies in " + target->getName() + " territory" +
        " and ownership changed to neutral player\n");
        cout << getEffect();
        setExecuted(true);
    }
    else{
        setEffect("The blockade order was not executed\n");
        cout << getEffect() << endl;
    }
    Notify(this);
}

//Assignment operator overload
//Intentionally shallow copying data members of deploy class since no new members are being created
Blockade &Blockade::operator=(const Blockade &blockade) {
    this->game = blockade.game;
    this->Attach(blockade.game->_observer);
    this->orderOwner = blockade.orderOwner;
    this->target = blockade.target;
    return *this;
}

//Intentionally shallow copying data members of deploy class since no new members are being created
Blockade::Blockade(const Blockade &blockade) {
    this->game = blockade.game;
    this->Attach(blockade.game->_observer);
    this->orderOwner = blockade.orderOwner;
    this->target = blockade.target;
}

//Destructor is default since no new data members being created in the class
Blockade::~Blockade() {
    game = nullptr;
    this->Detach();
};


//------------------------------Airlift class---------------------

Airlift::Airlift(Player* orderOwner,int n, Territory *s, Territory *t, GameEngine* game) {
    this->game = game;
    this->Attach(game->_observer);
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
    if(getExecuted()){
        cout << "Order already executed" << endl;
        return false;
    }
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
        setEffect("Airlift order has not been executed\n");
        cout << getEffect() << endl;
    }
    Notify(this);
}

//Assignment operator overload
//Intentionally shallow copying data members of deploy class since no new members are being created
Airlift &Airlift::operator=(const Airlift &airlift) {
    this->game = airlift.game;
    this->Attach(airlift.game->_observer);
    this->orderOwner = airlift.orderOwner;
    this->source = airlift.source;
    this->target = airlift.target;
    this->noOfArmies = airlift.noOfArmies;
    return *this;
}

//Intentionally shallow copying data members of deploy class since no new members are being created
Airlift::Airlift(const Airlift &airlift) {
    this->game = game;
    this->Attach(airlift.game->_observer);
    this->orderOwner = airlift.orderOwner;
    this->source = airlift.source;
    this->target = airlift.target;
    this->noOfArmies = airlift.noOfArmies;
}

//Destructor is default since no new data members being created in the class
Airlift::~Airlift() {
    game = nullptr;
    this->Detach();
};

//--------------------------Negotiate class------------------

Negotiate::Negotiate(Player *orderOwner,Player* otherPlayer, GameEngine* game){
    this->game = game;
    this->Attach(game->_observer);
    this->orderOwner = orderOwner;
    this->otherPlayer = otherPlayer;
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
bool Negotiate::validate() {
    if(getExecuted()){
        cout << "Order already executed" << endl;
        return false;
    }
    //If the target is the player issuing the order, then the order is invalid.
    if(orderOwner == otherPlayer){
        cout << "You cannot negotiate with yourself" << endl;
        return false;
    }
    cout << "Negotiate order valid" << endl;
    return true;
}

//A negotiate order targets an enemy player. It results in the target player and the player issuing
//the order to not be able to successfully attack each others’ territories for the remainder of the turn. The negotiate
//order can only be created by playing the diplomacy card.
void Negotiate::execute() {
    //If the target is an enemy player, then the effect is that any attack that may be declared between territories
    //of the player issuing the negotiate order and the target player will result in an invalid order.
    if(validate()){
        cout << "Executing Negotiate order" << endl;
        orderOwner->cannotAttack.push_back(otherPlayer);
        otherPlayer->cannotAttack.push_back(orderOwner);

        setEffect("Attacking between " + orderOwner->getName() + " and " + otherPlayer->getName() + " has been prevented until the end of the turn\n");
        cout << getEffect();
        setExecuted(true);
    }
    else{
        setEffect("Airlift order has not been executed\n");
        cout << getEffect() << endl;
    }
    Notify(this);
}
//Intentionally shallow copying data members of deploy class since no new members are being created
Negotiate::Negotiate(const Negotiate &negotiate){
    this->game = negotiate.game;
    this->Attach(negotiate.game->_observer);
    this->orderOwner = negotiate.orderOwner;
    this->otherPlayer = negotiate.otherPlayer;
}

//Destructor is default since no new data members being created in the class
Negotiate::~Negotiate() {
    game = nullptr;
    this->Detach();
};

//Intentionally shallow copying data members of deploy class since no new members are being created
Negotiate &Negotiate::operator=(const Negotiate &negotiate) {
    this->game = negotiate.game;
    this->Attach(negotiate.game->_observer);
    this->orderOwner = negotiate.orderOwner;
    this->otherPlayer = negotiate.otherPlayer;
    return *this;
}

string Negotiate::getName() {return name;}



//Start of OrdersList class implementation

OrdersList::OrdersList(Player* ordersListOwner,vector<Orders *> ordersList) {
    this->ordersListOwner = ordersListOwner;
    this->ordersList = ordersList;
    this->Attach(ordersListOwner->getGameEngine()->_observer);
}

void OrdersList::setOrdersList(vector<Orders*> orderList) {
    this->ordersList = orderList;
}

//Removing order by index --> invalid indexes checked
bool OrdersList::removeOrder(int index) {
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
    this->Detach();
}
//New order is created and put in the list but the data members of the order are still a shallow copy since no new members needed to be created
OrdersList::OrdersList(const OrdersList& ol){
    vector<Orders*> newOrdersList;
    for(auto& it: ordersList){
        auto* newOrder = new Orders(*it);
        newOrdersList.push_back(newOrder);
    }
    this->ordersList = newOrdersList;
    this->Attach(ol.ordersListOwner->getGameEngine()->_observer);
}

//Stream insertion operator overload --> Printing all orders(name only)
ostream &operator<<(ostream &strm, OrdersList &ordersList) {
    cout << "Printing out the ordersList of " + ordersList.ordersListOwner->getName() << endl;
    for(auto& it : ordersList.ordersList){
        cout << it->getName() + " -> ";
    }
    return strm << "END" << endl;
}

void OrdersList::addOrders(Orders* o) {
    this->ordersList.push_back(o);
    Notify(this);
}

void OrdersList::removeOrder(Orders* o) {
    ordersList.erase(remove(ordersList.begin(),ordersList.end(),o),ordersList.end());
}


//*********************
// method from ILoggable
string OrdersList::stringToLog()
{
    string out = "Inserted ";
    Orders* o = ordersList.back();
    out += "Order: " + o->getName() + "";
    out += " into the list.";
    return out;
}
//End of OrdersList class implementation

/*Neutral player pointer return method*/

