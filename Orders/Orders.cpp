#include "Orders.h"
#include <iostream>

using namespace std;

ostream& operator <<(std::ostream &strm, Orders* o){
    return strm << o->toString();
}

Orders::Orders()= default;
//bool Orders::validate(){return false;}
//void Orders::execute(){}
string Orders::toString() {
    return {};
}

//Orders::Orders(const Orders &orders) = default;

//Orders& Orders::operator=(const Orders &orders) = default;

//------------------Deploy class--------------------

Deploy::Deploy(int noOfArmies, Territory *target) {
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

string Deploy:: toString(){
    return "Placing some armies on one of the current player’s territories. \n";
}

bool Deploy::validate(Player p) {
    if(p.ownsTerritory(getTarget()) && getNoOfArmies() > 0) {
        cout << "Deploy order is valid" << endl;
        return true;
    }
    cout << "Deploy order is invalid since player " + p.getName() + " does not own " + target->getName() + " territory" <<endl;
    return false;
}

void Deploy::execute(Player p) {
    if(validate(p)){
        cout << "Executing the deploy order" << endl;
        //Only printing the message, armies have not been moved
        cout << "Player " + p.getName() +" has deployed " << getNoOfArmies() << " armies to territory " + target->getName()  << endl;
    }
    else{
        cout << "The deploy call was not executed" << endl;
    }
}


//------------------------------Advance class---------------------

Advance::Advance(int n, Territory *s, Territory *t) {
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

string Advance::toString(){
    return "Moving some armies from one of the current player’s territories (source) to an adjacent territory (target)\n";
}

bool Advance::validate(Player p) {
    //Checking if target is a neighbour of source
    if(source->isNeighbour(target) && p.ownsTerritory(source)){
        cout << "Advance order is valid" << endl;
        return true;
    }
    cout << "Cannot advance to that territory since Player " + p.getName() + "does not have any owned neighbour territories" << endl;
    return false;
}
void Advance::execute(Player p) {
    if(validate(p)){
        if(p.ownsTerritory(target)){
            cout << "Executing advance order" << endl;
            //Only printing the message, armies have not been moved
            cout << "Player " + p.getName() + " has moved " << getNoOfArmies() <<
            " armies from " + source->getName() + " territory to " + target->getName() + " territory" << endl;
        }
        else{
            cout << "Executing advance order" << endl;
            //Only printing the message, not attacking the territory
            cout << "Player " + p.getName() + " attacking " + target->getName() + " territory" << endl;
        }
    }
    else{
        cout << "The advance call was not executed" << endl;
    }
}

//------------------------------Bomb class---------------------

Bomb::Bomb(Territory *target) {
    this->target = target;
}

Territory* Bomb::getTarget() {
    return target;
}

void Bomb::setTarget(Territory *t) {
    target = t;
}

string Bomb::toString(){
    return "Destroying half of the armies located on an opponent’s territory that is adjacent to one of the current "
           "player’s territories. \n";
}
bool Bomb::validate(Player p) {
    //Checking if one of the neighbours of target is owned by p or if the target itself is owned by p
    auto it = target->neighbours.begin();
    for(;it!=target->neighbours.end();it++){
        if(p.ownsTerritory(*it) || p.ownsTerritory(target)){
            return true;
        }
    }
    cout << "Cannot bomb that territory since player " + p.getName() +" does not have any owned neighbour territories" << endl;
    return false;
}
void Bomb::execute(Player p) {
    if(validate(p)){
        if(p.ownsTerritory(target)){
            cout << "Order not executed, since you cannot bomb your own territories" << endl;
        }
        else{
            cout << "Executing bomb order" << endl;
            //Only printing the message, not bombing the territory
            cout << "Sucessfully bombed " + target->getName() + " territory" << endl;
        }
    }
    else{
        cout << "The bomb order was not executed" << endl;
    }
}

//------------------------------Blockade class---------------------

Blockade::Blockade(int noOfArmies, Territory *target) {
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

string Blockade::toString(){
    return "Tripling the number of armies on one of the current player’s territories and making it a neutral territory\n";
}
bool Blockade::validate(Player p) {
    if(p.ownsTerritory(target)){
        return true;
    }
    cout << "You do not own " + target->getName() + "territory" << endl;
    return false;
}
void Blockade::execute(Player p) {
    if(validate(p)){
        cout << "Executing blockade order" << endl;
        //Only printing the message, not tripling the armies
        cout << "Successfully triples the number of armies in " + target->getName() + " territory" << endl;
    }
    else{
        cout << "The blockade order was not executed" << endl;
    }
}


//------------------------------Airlift class---------------------

Airlift::Airlift(int n, Territory *s, Territory *t) {
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

string Airlift::toString(){
    return "Advancing some armies from one of the current player’s territories to any another territory.\n";
}
bool Airlift::validate(Player p) {
    if(p.ownsTerritory(source)){
        return true;
    }
    cout << "You do not own " + source->getName() + " territory" << endl;
    return false;
}
void Airlift::execute(Player p) {
    if(validate(p)){
        cout << "Executing Airlift order" << endl;
        //Only printing the message, no armies have been moved
        cout << "Successfully moved " << getNoOfArmies() << " armies from " + source->getName() +" to " + target->getName() + "territory via airlift" << endl;
    }
    else{
        cout << "Airlift order has not been executed";
    }
}

//--------------------------Negotiate class------------------

Negotiate::Negotiate() = default;
string Negotiate::toString(){
    return "A negotiate order has been called\n";
}

//Not sure how to validate or execute this order
bool Negotiate::validate(Player p1,Player p2) {
    return false;
}
void Negotiate::execute(Player p1,Player p2) {
}


//--------Fake methods to test if everything works later---------------

Player::Player(string name,vector<Territory*> territories) {
    this->name = name;
    this->territories = territories;
}

void Player::setName(string n){
    this->name = n;
}

string Player::getName(){
    return this->name;
}

vector<Territory*> Player::getTerritories(){
    return this->territories;
}

void Player::setTerritories(vector<Territory*> v){
    this->territories = v;
}

bool Player::ownsTerritory(Territory *t) {
    auto it = territories.begin();
    for(;it!=territories.end();it++){
        if(t == *it) return true;
    }
    return false;
}

Territory::Territory(string n) {
    this->name = n;
}
void Territory::setName(string n){
    this->name = n;
}
string Territory::getName(){
    return name;
}
bool Territory::isNeighbour(Territory *t) {
    auto it = neighbours.begin();
    for(;it!=neighbours.end();it++){
        if(t == * it) return true;
    }
    return false;
}

//-------------------End of fake methods--------------------------


//Start of OrdersList class implementation

//End of OrdersList class implementation
