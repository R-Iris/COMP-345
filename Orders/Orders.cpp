#include "Orders.h"
#include <iostream>
#include <algorithm>

using namespace std;

//Stream insertion operator overload
ostream& operator <<(ostream &strm, Orders* o){
    return strm << o->toString();
}

Orders::Orders()= default;

string Orders::toString() {
    return {};
}

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

Orders::Orders(const Orders &o) = default; //Copy constructor
Orders::~Orders() = default; //Destructor
Orders& Orders::operator= (const Orders& orders)= default; //Assignment operator overload

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
    //string s1 = "Placing some armies on one of the current player’s territories. \n";
    string s1 = "This is the deploy order\n";
    if(this->getExecuted()){
        return s1 + getEffect();
    }
    else return s1;
}
//Assignment operator overload
Deploy& Deploy::operator = (const Deploy& deploy){
    this->noOfArmies = deploy.noOfArmies;
    this->target = deploy.target;
    return *this;
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
    if (validate(p)) {
        cout << "Executing the deploy order" << endl;
        //Only printing the message, armies have not been moved
        setEffect("Player " + p.getName() + " has deployed " + to_string(getNoOfArmies()) +
        " armies to territory " + target->getName() + "\n");
        cout << getEffect();
        setExecuted(true);
    }
    else {
        cout << "The deploy call was not executed" << endl;
    }
}

Deploy::Deploy(const Deploy &deploy) {
    this->target = deploy.target;
    this->noOfArmies = deploy.noOfArmies;
}

Deploy::~Deploy()= default;

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
    //string s1 = "Moving some armies from one of the current player’s territories (source) to an adjacent territory (target)\n";
    string s1 = "This is the advance order\n";
    if(this->getExecuted()){
        return s1 + getEffect();
    }
    else return s1;
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
            setEffect("Player " + p.getName() + " has moved " + to_string(getNoOfArmies()) + " armies from " + source->getName()
            + " territory to " + target->getName() + " territory \n");
            cout << getEffect();
        }
        else{
            cout << "Executing advance order" << endl;
            //Only printing the message, not attacking the territory
            setEffect("Player " + p.getName() + " attacking " + target->getName() + " territory\n");
            cout << getEffect();
        }
        setExecuted(true);
    }
    else{
        cout << "The advance call was not executed" << endl;
    }
}
//Assignment operator overload
Advance &Advance::operator=(const Advance &advance) {
    this->target = advance.target;
    this->source = advance.source;
    this->noOfArmies = advance.noOfArmies;
    return *this;
}

Advance::Advance(const Advance &advance) {
    this->target = advance.target;
    this->source = advance.source;
    this->noOfArmies = advance.noOfArmies;
}

Advance::~Advance() = default;

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
    //string s1 = "Destroying half of the armies located on an opponent’s territory that is adjacent to one of the current "
           //"player’s territories. \n";
    string s1 = "This is the bomb order\n";
    if(getExecuted()){
        return s1 + getEffect();
    }
    else return s1;
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
            setEffect("Successfully bombed " + target->getName() + " territory\n");
            cout << getEffect();
            setExecuted(true);
        }
    }
    else{
        cout << "The bomb order was not executed" << endl;
    }
}
//Assignment operator overload
Bomb &Bomb::operator=(const Bomb &bomb) {
    this->target = bomb.target;
    return *this;
}

Bomb::Bomb(const Bomb &bomb) {
    this->target = bomb.target;
}

Bomb::~Bomb() = default;

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
    //string s1 = "Tripling the number of armies on one of the current player’s territories and making it a neutral territory\n";
    string s1 = "This is the blockade order\n";
    if(getExecuted()){
        return s1 + getEffect();
    }
    else return s1;
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
        setEffect("Successfully tripled the number of armies in " + target->getName() + " territory\n");
        cout << getEffect();
        setExecuted(true);
    }
    else{
        cout << "The blockade order was not executed" << endl;
    }
}
//Assignment operator overload
Blockade &Blockade::operator=(const Blockade &blockade) {
    this->target = blockade.target;
    this->noOfArmies = blockade.noOfArmies;
    return *this;
}

Blockade::Blockade(const Blockade &blockade) {
    this->target = blockade.target;
    this->noOfArmies = blockade.noOfArmies;
}

Blockade::~Blockade() = default;


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
    //string s1 = "Advancing some armies from one of the current player’s territories to any another territory.\n";
    string s1 = "This is the airlift order\n";
    if(this->getExecuted()){
        return s1 + getEffect();
    }
    else return s1;
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
Airlift &Airlift::operator=(const Airlift &airlift) {
    this->source = airlift.source;
    this->target = airlift.target;
    this->noOfArmies = airlift.noOfArmies;
    return *this;
}

Airlift::Airlift(const Airlift &airlift) {
    this->source = airlift.source;
    this->target = airlift.target;
    this->noOfArmies = airlift.noOfArmies;
}

Airlift::~Airlift() = default;

//--------------------------Negotiate class------------------

Negotiate::Negotiate() = default;
string Negotiate::toString(){
    string s1 = "This is the negotiate order\n";
    if(getExecuted()){
        return s1 + getEffect();
    }
    else return s1;
}

//Not sure how to validate or execute this order
bool Negotiate::validate(Player p1,Player p2) {
    return true;
}
void Negotiate::execute(Player p1,Player p2) {
    if(validate(p1,p2)){
        cout << "Executing Negotiate order" << endl;
        //Only printing message
        setEffect("Attacking between " + p1.getName() + " and " + p2.getName() + " have been prevented until the end of the turn\n");
        cout << getEffect();
        setExecuted(true);
    }
    else{
        cout << "Airlift order has not been executed" << endl;
    }
}

Negotiate::Negotiate(const Negotiate &negotiate) = default;

Negotiate::~Negotiate() = default;

Negotiate &Negotiate::operator=(const Negotiate &negotiate) = default;

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

OrdersList::OrdersList(vector<Orders *> ordersList) {
    this->ordersList = ordersList;
}

void OrdersList::setOrdersList(vector<Orders*> ordersList) {
    this->ordersList = ordersList;
}

vector<Orders*>  OrdersList::getOrdersList() {
    return this->ordersList;
}

bool OrdersList::remove(int index) {
    cout << "Trying to remove an order from the list" << endl;
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

bool OrdersList::move(int i, int j) {
    cout << "Trying to move an order from position " << i << " to position " << j <<  " in the list " << endl;
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

void OrdersList::print(){
    for(auto & it : ordersList){
        cout << it;
    }
}

OrdersList::~OrdersList() {
    for(auto & it : ordersList){
        delete it;
    }
    ordersList.clear();
}

OrdersList::OrdersList(const OrdersList& ol){
    vector<Orders*> newOrdersList;
    for(auto& it: ordersList){
        newOrdersList.push_back(it);
    }
    this->ordersList = newOrdersList;
}

//End of OrdersList class implementation
