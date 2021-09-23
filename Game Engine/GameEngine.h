#pragma once         // Makes sure that the GameEngine.h file is only called once
#include <string>    // Allows for the use of strings
#include <iostream>  // Allows for the use of input and output streams
using namespace std; // Imports the standard library for cout/cin..etc..

// Keeps track of the current state of the game, takes in input from command and checks if it's valid
class State
{
public:
    // Default Constructor
    State();
    // Copy Constructor
    State(State &state);
    // Equals operator copy constructor
    State &operator=(const State &state);
    // Insertion operator conversion
    friend ostream &operator<<(ostream &out, const State &state);
    // Prints out the current state to the console
    void showState();
    // Retrieves the name of the current state
    string getState();
    // Checks validity of the command before executing
    bool isValid(string command);
    // Executes the command to change the state
    bool changeState(string nextState);

private:
    // Array states that contains all the names for each state
    string states[8];
    // The current state
    string currentState;
    // Position in the array of the current state
    int currentStatePosition;
};

// Starts the game and sets up state machine
void playGame();
// Ends the game without memory leaks
void end(State *game);