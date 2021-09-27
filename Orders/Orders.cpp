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


Deploy::Deploy() = default;
string Deploy:: toString(){
    return "A deploy order has been called\n";
}
bool Deploy::validate(Player p,Territory* t) {
    if(p.ownsTerritory(t)) {
        cout << "Deploy order is valid" << endl;
        return true;
    }
    return false;
}
void Deploy::execute(Player p, Territory* t) {
    if(validate(p,t)){
        cout << "Executing the deploy order" << endl;
        //Only printing the message, armies have not been moved
        cout << "Player p has deployed some armies to territory t" << endl;
    }
    else{
        cout << "The deploy call was not executed" << endl;
    }
}


Advance::Advance() = default;
string Advance::toString(){
    return "An advance order has been called\n";
}
bool Advance::validate(Player p,Territory* source, Territory* target) {
    //Checking if target is a neighbour of source
    if(source->isNeighbour(target) && p.ownsTerritory(source)){
        cout << "Advance order is valid" << endl;
        return true;
    }
    cout << "Cannot advance to that territory since player p does not have any owned neighbour territories" << endl;
    return false;
}
void Advance::execute(Player p,Territory* source, Territory* target) {
    if(validate(p,source,target)){
        if(p.ownsTerritory(target)){
            cout << "Executing advance order" << endl;
            //Only printing the message, armies have not been moved
            cout << "Player p has moved some armies from source territory to target territory" <<endl;
        }
        else{
            cout << "Executing advance order" << endl;
            //Only printing the message, not attacking the territory
            cout << "Player p attacking target territory" << endl;
        }
    }
    else{
        cout << "The advance call was not executed" << endl;
    }
}


Bomb::Bomb() = default;
string Bomb::toString(){
    return "Bomb order has been called\n";
}
bool Bomb::validate(Player p,Territory* target) {
    //Checking if one of the neighbours of target is owned by p
    auto it = target->neighbours.begin();
    for(;it!=target->neighbours.end();it++){
        if(p.ownsTerritory(it.base())){
            return true;
        }
    }
    cout << "Cannot bomb that territory since player p does not have any owned neighbour territories" << endl;
    return false;
}
void Bomb::execute(Player p,Territory* target) {
    if(validate(p,target)){
        if(p.ownsTerritory(target)){
            cout << "Order not executed, since you cannot bomb your own territories" << endl;
        }
        else{
            cout << "Executing bomb order" << endl;
            //Only printing the message, not bombing the territory
            cout << "Sucessfully bombed target territory" << endl;
        }
    }
    else{
        cout << "The bomb order was not executed" << endl;
    }
}


Blockade::Blockade() = default;
string Blockade::toString(){
    return "A blockade order has been called\n";
}
bool Blockade::validate(Player p,Territory* target) {
    if(p.ownsTerritory(target)){
        return true;
    }
    cout << "You do not own target territory" << endl;
    return false;
}
void Blockade::execute(Player p, Territory* target) {
    if(validate(p,target)){
        cout << "Executing blockade order" << endl;
        //Only printing the message, not tripling the armies
        cout << "Successfully triples the number of armies in the target territory" << endl;
    }
    else{
        cout << "The blockade order was not executed" << endl;
    }
}


Airlift::Airlift() = default;
string Airlift::toString(){
    return "An airlift order has been called\n";
}
bool Airlift::validate(Player p, Territory* source, Territory* target) {
    if(p.ownsTerritory(source)){
        return true;
    }
    cout << "You do not own source territory" << endl;
    return false;
}
void Airlift::execute(Player p, Territory* source, Territory* target) {
    if(validate(p,source,target)){
        cout << "Executing Airlift order" << endl;
        //Only printing the message, no armies have been moved
        cout << "Successfully moved some armies from source to target territory via airlift" << endl;
    }
    else{
        cout << "Airlift order has not been executed";
    }
}


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

//Fake methods to test if everything works later

Player::Player() = default;

Player::Player(vector<Territory> territories) {
    this->territories = territories;
}

bool Territory::isNeighbour(Territory *t) {
    auto it = this->neighbours.begin();
    for(;it!= this->neighbours.end();it++){
        if(t == it.base()){
            return true;
        }
    }
    return false;
}

//End of fake methods
