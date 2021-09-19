#pragma once
#include <string>
using std::string;

class State
{
public:
    State();
    void showState();

private:
    string *currentState;
    string states[];
};

class Transition
{
public:
private:
    void changeState();
};

class Command
{
public:
    Command();
    Command(string &issedCommand);
    //void issueCommand();

private:
};