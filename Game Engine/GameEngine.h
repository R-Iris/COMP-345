#pragma once
#include <string>
using std::string;

// Keeps track of the current state of the game, takes in input from command and checks if it's valid
class State
{
public:
    State();
    void showState();
    string getState();
    bool isValid(string command);
    bool changeState(string nextState);
    void del();

private:
    string states[8];
    string currentState;
    int currentStatePosition;
};

void playGame();
void end(State *game);