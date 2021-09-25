#include "Orders.h"

using namespace std;

int main(){
    OrdersList* ol = new OrdersList();
    cout << "Inserting a few Orders into the Orders list" <<endl;
    ol->insert(*new Advance());
    ol->insert(*new Deploy());
    ol->insert(*new Blockade());
    ol->insert(*new Airlift());
    ol->insert(*new Negotiate());
    ol->insert(*new Bomb());
    ol->print();
}
