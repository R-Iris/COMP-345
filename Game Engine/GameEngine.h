#pragma once
#include <string>
using std::string;

// Keeps track of the current state of the game, takes in input from command and checks if it's valid
class State
{
public:
    bool *isValid;
    State();
    void showState();
    string getState();
    bool changeState(string &nextState);
    void del();

private:
    /*friend*/ bool *transition;
    string *currentState;
    string states[8];
};

// Transition between startup and play, as well as winning and playing again
class Transition
{
public:
    Transition(string &issuedCommand);
};

class Command
{
public:
    Command();
    Command(string &issedCommand);
    //void issueCommand();

private:
};

void playGame();
void end(State game);