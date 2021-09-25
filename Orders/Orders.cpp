
#include <iostream>
#include <string>
#include "Orders.h"


using namespace std;


std::ostream& operator<<(std::ostream& os, Orders order)
{
    os << order.toString();
    // write order to stream
    return os;
}


Orders::Orders()= default;

bool Orders::validate(){
    return false;
}

void Orders::execute(){

}

string Orders::toString() {
    return {};
}

Deploy::Deploy() = default;

string Deploy::toString(){
    return "A deploy order has been called\n";
}

bool Deploy::validate() {
    return false;
}

void Deploy::execute() {

}
Advance::Advance() = default;

string Advance::toString(){
    return "An advance order has been called\n";
}

bool Advance::validate() {
    return false;
}
void Advance::execute() {

}

Bomb::Bomb() = default;

string Bomb::toString(){
    return "Bomb order has been called\n";
}

bool Bomb::validate() {
    return false;
}

Blockade::Blockade() = default;

string Blockade::toString(){
    return "A blockade order has been called\n";
}

bool Blockade::validate() {
    return false;
}
void Blockade::execute() {

}

Airlift::Airlift() = default;

string Airlift::toString(){
    return "An airlift order has been called\n";
}
bool Airlift::validate() {
    return false;
}
void Airlift::execute() {

}
Negotiate::Negotiate() = default;

string Negotiate::toString(){
    return "A negotiate order has been called\n";
}
bool Negotiate::validate() {
    return false;
}

void Negotiate::execute() {

}

OrdersList::OrdersList() {

}

void OrdersList::move() {

}

void OrdersList::remove() {

}

void OrdersList::insert(Orders& o){
    list1->push_front(o);
}

void OrdersList::print(){
    cout<<"Printing contents of ordersList"<<endl;
    list<Orders>::iterator it;
    for(it = list1->begin();it!=list1->end();it++){
        cout << *it;
    }
}

