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
    // Default constructor
    State();
    // Parametrized constructor
    State(string name);
    // Copy constructor
    State(const State &state);
    // = operator copy constructor
    State &operator=(const State &state);
    // << ostream conversion
    friend ostream &operator<<(ostream &out, const State &state);
};

// Transitions between states and contains the ruleset for the game engine
class Transition
{
public:
    State* current;
    State* next;
    string command;
    // Default Constructor
    Transition();
    // Parametrized Constructor
    Transition(State *current, State *next, string command);
    // Destructor
    ~Transition();
    // Copy constructor
    Transition(const Transition &transition);
    // = operator copy constructor
    Transition &operator=(const Transition &transition);
    // << ostream conversion
    friend ostream &operator<<(ostream &out, const Transition &transition);
};

class GameEngine
{
public:
    // Vector of pointers to states
    vector<Transition*> transitions;
    vector<State*> states;
    // Current State
    State* currentState;
    // Default Constructor
    GameEngine();
    // Destructor
    ~GameEngine();
    // Copy constructor
    GameEngine(const GameEngine &gameEngine);
    // = operator copy constructor
    GameEngine& operator=(const GameEngine& gameEngine);
    // << ostream conversion
    friend ostream& operator<<(ostream& out, const GameEngine& gameEngine);
    // Checks and Changes the states
    bool changeState(string command);
};

// Ends the game and deletes game object
void end(GameEngine *game);

// Starts and plays the game
void playGame();
