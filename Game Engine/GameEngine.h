#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../LoggingObserver/LoggingObserver.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../CommandProcessor/CommandProcessor.h"
#include "../Cards/Cards.h"
using namespace std;

// Forward declaration
class Player;
class Map;
class Deck;
class CommandProcessor;
class Observer;
class ILoggable;
class Subject;

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
	State(const State& state);
	// = assignment operator
	State& operator=(const State& state);
	// << ostream conversion
	friend ostream& operator<<(ostream& out, const State& state);
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
	Transition(State* current, State* next, string command);
	// Copy constructor
	Transition(const Transition& transition);
	// = assignment operator
	Transition& operator=(const Transition& transition);
	// << ostream conversion
	friend ostream& operator<<(ostream& out, const Transition& transition);
};

// The ruleset for the game using transitions and states
class GameEngine : public ILoggable, public Subject
{
public:
	// Vector of pointers to transitions
	vector<Transition*> transitions;
	// Vector of pointers to states
	vector<State*> states;
	// Current State
	State* currentState;

	// Vector of pointers to players
	vector<Player*> players; // 2 - 6 Players
	// Pointer to the current map
	Map* map;
	// Deck pointer
	Deck* deck;

	// Default Constructor
	GameEngine();
	// Observer pattern constructor
	GameEngine(Observer* _obs);
	// Destructor
	~GameEngine();
	// Copy constructor
	GameEngine(const GameEngine& gameEngine);
	// = assignment operator
	GameEngine& operator=(const GameEngine& gameEngine);
	// << ostream conversion
	friend ostream& operator<<(ostream& out, const GameEngine& gameEngine);
	// Getter for map
	Map* getMap();
	// Sets the map
	void setMap(Map*);
	// Getter for deck
	Deck* getDeck();
	// Setter for deck
	void setDeck(Deck*);
	// Adds players to player list
	void addPlayer(Player*);
	// Remove a player from the player list
	void removePlayer(Player*);
	// STRICTLY Checks the states
	bool checkState(string command);
	// Checks and Changes the states
	bool changeState(string command);
	// Creates a new state
	State* newState(string state);
	// Creates a new Transition
	void newTransition(State* current, State* next, string command);
	// Ends the game and deletes game object
	void end();

	// Startup Phase
	void startupPhase(CommandProcessor* cp);

	// Main Game Loop
	void mainGameLoop();

	// Reinforcement Phase
	void reinforcementPhase();

	// Issue Orders Phase
	void issueOrdersPhase();

	// Execute Orders Phase
	void executeOrdersPhase();

	
	//******************
	// stringToLog Implementation for ILoggable
	string stringToLog();

    //checking for a neutral player among the list of players and if there isnt one , a pointer to one will be created
    //and added to the list of players

    Player* getNeutralPlayer();
};
