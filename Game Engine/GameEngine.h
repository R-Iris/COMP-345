#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// A State holds a string
class State
{
public:
    // State's name
    string stateName;
    // Default constructor
    State();
    // Parametrized constructor
    State(string name);
    // Copy constructor
    State(const State &state);
    // = assignment operator
    State &operator=(const State &state);
    // << ostream conversion
    friend ostream &operator<<(ostream &out, const State &state);
};

// Contains pointers from one state to another as well as its required command
class Transition
{
public:
    // current state
    State* current;
    // next state
    State* next;
    // Required command to perform transition
    string command;
    // Default Constructor
    Transition();
    // Parametrized Constructor
    Transition(State *current, State *next, string command);
    // Copy constructor
    Transition(const Transition &transition);
    // = assignment operator
    Transition &operator=(const Transition &transition);
    // << ostream conversion
    friend ostream &operator<<(ostream &out, const Transition &transition);
};

// The ruleset for the game using transitions and states
class GameEngine
{
public:
    // Vector of pointers to transitions
    vector<Transition*> transitions;
    // Vector of pointers to states
    vector<State*> states;
    // Current State
    State* currentState;
    // Default Constructor
    GameEngine();
    // Destructor
    ~GameEngine();
    // Copy constructor
    GameEngine(const GameEngine &gameEngine);
    // = assignment operator
    GameEngine& operator=(const GameEngine& gameEngine);
    // << ostream conversion
    friend ostream& operator<<(ostream& out, const GameEngine& gameEngine);
    // Checks and Changes the states
    bool changeState(string command);
    // Creates a new state
    State* newState(string state);
    // Creates a new Transition
    void newTransition(State* current, State* next, string command);
    // Ends the game and deletes game object
    void end();
};



