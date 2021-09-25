#pragma once
#include <bits/stdc++.h>

using namespace std;

class Orders {
public:
    Orders();

    virtual bool validate();

    virtual void execute();

    virtual string toString();
};

class Deploy : public Orders{
public:
    Deploy();
    bool validate() override;

    void execute() override;

    string toString() override;
};

class Advance: public Orders{
public:
    Advance();
    bool validate() override;

    void execute() override;

    string toString() override;
};

class Bomb: public Orders{
public:
    Bomb();
    bool validate() override;

    string toString() override;
};

class Blockade: public Orders{
public:
    Blockade();
    bool validate() override;

    void execute() override;

    string toString() override;
};

class Airlift: public Orders{
public:
    Airlift();
    bool validate() override;

    void execute() override;

    string toString() override;
};

class Negotiate: public Orders{
public:
    Negotiate();
    bool validate() override;

    void execute() override;

    string toString() override;
};

class OrdersList{
private:
    list<Orders>* list1;
public:
    OrdersList();
    void remove();
    void move();

    void insert(Orders &o);

    void print();
};

