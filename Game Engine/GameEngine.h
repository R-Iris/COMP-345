#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Keeps track of the state's name as well as next available state
class State
{
public:
    // State's name
    string stateName;
    // Pointer to the next state
    State *nextState;

    // Default constructor
    State();
    // Destructor
    ~State();
    // Parametrized constructor
    State(string name, State *nextState);
    // Parametrized constructor
    State(string name);
    // Copy constructor
    State(const State *state);
    // = operator copy constructor
    State &operator=(const State *state);
    // << ostream conversion
    friend ostream &operator<<(ostream &out, const State &state);
};

// Transitions between states and contains the ruleset for the game engine
class Transition
{
public:
    // States
    State *start;
    State *map_loaded;
    State *map_validated;
    State *players_added;
    State *assign_reinforcement;
    State *issue_orders;
    State *execute_orders;
    State *win;
    // Vector of pointers to states
    vector<State *> states;
    // Current State
    State *currentState;
    // Default Constructor
    Transition();
    // Destructor
    ~Transition();
    // Copy constructor
    Transition(const Transition *transition);
    // = operator copy constructor
    Transition &operator=(const Transition *transition);
    // << ostream conversion
    friend ostream &operator<<(ostream &out, const Transition *transition);
    // Checks and Changes the states
    bool changeState(string command);
};

// Ends the game and deletes game object
void end(Transition *game);

// Starts and plays the game
void playGame();
