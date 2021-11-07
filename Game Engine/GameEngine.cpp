#include "GameEngine.h"
#include "../CommandProcessor/CommandProcessor.h"
#include <regex>
#include <math.h>
// Members of State Class

State::State() : stateName("none") {}
State::State(string name) : stateName(name) {}
State::State(const State& state) : stateName(state.stateName) {}

State& State::operator=(const State& state)
{
	this->stateName = state.stateName;
	return *this;
}

ostream& operator<<(ostream& out, const State& state)
{
	out << "Current State: " << state.stateName << endl;
	return out;
}

// Members of Transition Class

Transition::Transition() : current(nullptr), next(nullptr), command("none") {}
Transition::Transition(State* current, State* next, string command) : current(current), next(next), command(command) {}
Transition::Transition(const Transition& transition) : current(transition.current), next(transition.next), command(transition.command) {}

Transition& Transition::operator=(const Transition& transition)
{
	// Intentionally making shallow copies to refer to the same states
	this->current = transition.current;
	this->next = transition.next;
	this->command = transition.command;
	return *this;
}

ostream& operator<<(ostream& out, const Transition& transition)
{
	out << "(From: " << transition.current->stateName << ", To: " << transition.next->stateName << ")" << endl;
	return out;
}

// Members of GameEngine class

GameEngine::GameEngine() : currentState(nullptr), deck(new Deck()) {}
GameEngine::~GameEngine()
{
	// use for loop first to delete pointer contents inside of vector
	for (int i = 0; i < transitions.size(); i++)
	{
		delete transitions.at(i);
		transitions.at(i) = NULL;
	}
	// clear vector of pointers
	transitions.clear();

	// same thing but for states
	for (int j = 0; j < states.size(); j++)
	{
		delete states.at(j);
		states.at(j) = NULL;
	}
	// clear vector of pointers
	states.clear();

	// Calls delete on every element inside of the vector
	currentState = nullptr;

	// Delete deck
	delete deck;
	deck = nullptr;

	// Delete map
	delete map;
	map = nullptr;
}

GameEngine::GameEngine(const GameEngine& gameEngine)
{
	this->states = gameEngine.states;
	this->transitions = gameEngine.transitions;
	this->players = gameEngine.players;
	this->map = new Map(*gameEngine.map);
	this->deck = new Deck(*gameEngine.deck);
}

GameEngine& GameEngine::operator=(const GameEngine& gameEngine)
{
	this->states = gameEngine.states;
	this->transitions = gameEngine.transitions;
	this->players = gameEngine.players;
	this->map = new Map(*gameEngine.map);
	this->deck = new Deck(*gameEngine.deck);
	return *this;
}

ostream& operator<<(ostream& out, const GameEngine& gameEngine)
{
	for (int i = 0; i < gameEngine.transitions.size(); i++)
	{
		out << *gameEngine.transitions.at(i) << "\n";
	}
	return out;
}

Map* GameEngine::getMap()
{
	return map;
}

void GameEngine::setMap(Map* newMap)
{
	map = newMap;
}

Deck* GameEngine::getDeck()
{
	return deck;
}

void GameEngine::setDeck(Deck* newDeck)
{
	deck = newDeck;
}

void GameEngine::addPlayer(Player* player)
{
	players.push_back(player);
}

void GameEngine::removePlayer(Player* player)
{
	players.erase(remove(players.begin(), players.end(), player), players.end());
	//delete(player); MEMORY LEAK
}

bool GameEngine::checkState(string command)
{
	for (int i = 0; i < transitions.size(); i++)
	{
		if (currentState->stateName == transitions[i]->current->stateName && command == transitions[i]->command)
		{
			return true;
		}
		else if (currentState->stateName == "win" && command == "end") return true;
	}
	return false;
}

bool GameEngine::changeState(string command)
{
	for (int i = 0; i < transitions.size(); i++)
	{
		if (currentState->stateName == transitions[i]->current->stateName && command == transitions[i]->command)
		{
			currentState = transitions[i]->next;
			cout << *currentState;
			//Notify(this);
			return true;
		}
		else if (currentState->stateName == "win" && command == "end") return true;
	}
	//Notify(this);
	return false;
}

State* GameEngine::newState(string stateName)
{
	State* state = new State(stateName);
	states.push_back(state);
	return state;
}

void GameEngine::newTransition(State* current, State* next, string command)
{
	transitions.push_back(new Transition(current, next, command));
}

void GameEngine::end()
{
	delete this;
	cout << "Thank you for playing!" << endl;
}

// Game Startup Phase

void GameEngine::startupPhase(CommandProcessor* cp)
{
	// Use the command list to get the commands, make sure to change states in between commands
	for (Command* c : cp->getCommandList()) {
		string command = c->getCommandStr();

		if (command == "loadmap") {
			// Load the map (how to parse the filename from the command?)
			string effect = c->getEffect();
			std::regex extractionPattern(".*(.*\\.map).*");
			std::smatch match;

			// We found a map file name from the commmand's effect!
			if (std::regex_search(effect, match, extractionPattern)) {
				string mapFileName = "Assets/" + (string)match[1];
				setMap(MapLoader::createMapfromFile(mapFileName));
				changeState("validatemap");
			}
		}

		// Do I have to check if we are in a valid state before executing the command?
		else if (command == "validatemap") {
			// Validate the map
			map->validate();

			if (map->isValid()) {
				changeState("addplayer");
			}

			else {
				// Does the state go back to loadmap, or do we just fail and exit?
				cout << "An invalid map has been loaded." << endl;
			}
		}

		else if (command == "addplayer") {
			// Add player (This part should loop so as to ensure that we have 2-6 players in the game.)
			string effect = c->getEffect();

			std::regex extractionPattern("(.*) player has been added");
			std::smatch match;

			// Check to see if we have 2-6 players in the game

			if (players.size() < 6) {
				if (std::regex_search(effect, match, extractionPattern)) {
					addPlayer(new Player(match[1], new Hand));
				}
			}

			else {
				// Let the user know that they cannot add anymore players
				cout << "Limit of players in game has been reached, no new players may be added." << endl;
			}


			if (players.size() >= 2) {
				// Switch states
				changeState("gamestart");
			}

			else {
				// Let the user know that there needs to be more players for the game to start
				cout << "There must be at least 2 players before the game can start." << endl;
			}
		}

		else if (command == "gamestart") {
			/* Gamestart command does the following:
			*  a) Evenly pass out territories to players (remainder goes to the neutral player).

			*  b) Determine the order in which players get their turns (Randomly rearrange this class's Players list)

			*  c) Give 50 armies to each player, which are placed in their respective reinforcement pool (new Player field)

			*  d) Let each player draw 2 cards from the deck using Deck's draw() method (Call Player.getHand()->push_back(Deck.draw())?)

			*  e) Switch the game to the "play" state. (Call mainGameLoop())
			*/
			
			// Assign territories - TODO: Come up with a way to fairly distribute all countries between players
			int neutralTerritories = map->getTerritories().size() % players.size();
			int distrbutedTerritories = map->getTerritories().size() - neutralTerritories;

			// TODO: Randomize the territories and then pass them out to each player
			for (Player* p : players) {

			}

			// Determine the turn order randomly - Re-arrange the players in the vector
			
			// Store randomly sorted arrangement of players
			vector<Player*> tmp;

			// Initialize random seed
			srand(time(NULL));

			while (players.size() > 0) {
				// Generate a random number from 0 to the final index in the players vector
				int choose = rand() % (players.size() - 1);

				// Place randomly selected player in new vector
				tmp.push_back(players.at(choose));

				// Exclude newly placed player from next choice
				players.erase(players.begin()+choose);
			}

			// Reset players vector
			for (Player* player : tmp) {
				players.push_back(player);
			}

			// Give each player 50 armies to begin with and let them draw 2 cards from the deck
			for (Player* p : players) {
				// Give 50 armies
				p->setReinforcementPool(50);

				// Draw 2 cards for the player
				p->getHand()->addHand(deck->draw());
				p->getHand()->addHand(deck->draw());
			}

			// Switch the game to the play phase
			mainGameLoop();
		}
	}
}

// Main Game Loop

void GameEngine::mainGameLoop() {

	/*This loop shall continue until only one of the players owns all the territories in the map, at which point a winner is
	announced and the game ends.*/

	bool onePlayerOwnsAllTerritories = true;
	int numTotalTerritories = map->getTerritories().size(); // GET TERRITORIES CAUSES AN ERROR WHEN THERE IS NO MAP

	do {

	    /*
	    The main game loop also checks for any player that does not control at least one
	    territory; if so, the player is removed from the game
	    */
	    for (Player* p : players) {
	        if (p->toDefend().empty()) {
				removePlayer(p);
	        }
	        if (p->toDefend().size() >= numTotalTerritories) {
				onePlayerOwnsAllTerritories = true;
				// Announce this player as winner
				// announceWinner(p);
				// break;
	            // End game
	        }
	    }
	
	    // Reinforcement Phase
		changeState("endexecorders");
	    reinforcementPhase();

	    /*
	    Issuing Orders Phase � Players issue orders and place them in their order list through a call to the
	    Player::issueOrder() method. This method is called in round-robin fashion across all players by the
	    game engine. This must be implemented in a function/method named issueOrdersPhase() in the game
	    engine.
	    */
		changeState("issueorder");
	    issueOrdersPhase();

	    /*
	    Orders Execution Phase � Once all the players have signified in the same turn that they are not issuing
	    one more order, the game engine proceeds to execute the top order on the list of orders of each player in
	    a round-robin fashion (i.e. the �Order Execution Phase��see below). Once all the players� orders have
	    been executed, the main game loop goes back to the reinforcement phase. This must be implemented in
	    a function/method named executeOrdersPhase() in the game engine.
	    */
		changeState("issueordersend");
	    executeOrdersPhase();
	} while (!onePlayerOwnsAllTerritories);
}

void GameEngine::reinforcementPhase() {
	/*
	Reinforcement Phase � Players are given a number of armies that depends on the number of territories
	they own, (# of territories owned divided by 3, rounded down). If the player owns all the territories of an
	entire continent, the player is given a number of armies corresponding to the continent�s control bonus
	value. In any case, the minimal number of reinforcement armies per turn for any player is 3. These armies
	are placed in the player�s reinforcement pool. This must be implemented in a function/method named
	reinforcementPhase() in the game engine.
	*/

	for (Player* p : players) {
	    // Armies = # of territories owned divided by 3, rounded down : or 3 minimum
	    int armies = floor(p->toDefend().size() / 3);

	    // Bonus for owning all continent's territories, gets added
		int continentBonus = 0;

		// continentBonus = continent.getArmies();
		continentBonus = map->calculateContinentBonus(p);

	    // Place armies in player's reinforcement pool
	    p->setReinforcementPool(max(armies + continentBonus, 3));
	}
}

void GameEngine::issueOrdersPhase() {
	/*
	The issuing orders phase decision-making is implemented in the player�s issueOrder() method, which
	implements the following:

	// To attack -> vector<Territory*> getAdjacentTerritories(); what about priority
	� The player decides which neighboring territories are to be attacked in priority (as a list return by the
	toAttack() method), and which of their own territories are to be defended in priority (as a list returned by
	the toDefend() method).
	� The player issues deploy orders on its own territories that are in the list returned by toDefend(). As long
	as the player has armies still to deploy (see startup phase and reinforcement phase), it will issue a deploy
	order and no other order. Once it has deployed all its available armies, it can proceed with other kinds of
	orders.
	� The player issues advance orders to either (1) move armies from one of its own territory to the other in
	order to defend them (using toDefend() to make the decision), and/or (2) move armies from one of its
	territories to a neighboring enemy territory to attack them (using toAttack() to make the decision).
	� The player uses one of the cards in their hand to issue an order that corresponds to the card in question.
	Note that the orders should not be validated as they are issued. Orders are to be validated only when they are
	executed in the orders execution phase. This must be implemented in a function/method named
	issueOrdersPhase() in the game engine. The decision-making code must be implemented within the
	issueOrder() method of the player class in the Player.cpp/Player.h files.
	*/

	for (Player* p : players) {
		// Deploy until no more reinforcements
		// create deploy order obj
		// input num armies to deploy
		// Deploy(Player* orderOwner, int noOfArmies, Territory* target); //Parametrized Constructor.
		// player->issueOrder(new Deploy(p, int noOfArmies, Territory* target))

		// Advance
		// advance obj
		// player->issueOrder(

		// Card
		// show user their hand
		// choose a card to "play"
		// play adds an order to the player's order list
	}
}

void GameEngine::executeOrdersPhase() {
	for (Player* p : players) {
		// for each p, get order list, top to bottom, order->execute (validation done by execute)

	}
    //Something for the Negotiate order for Orders.cpp -- Abhay
    for(auto it : players){
        it->cannotAttack.clear();
    }
}


//******************
// stringToLog Implementation for ILoggable
string GameEngine::stringToLog() {
	return "Current GameEngine State: " + currentState->stateName;
}

//Neutral Player related stuff for Blockade order in Orders.cpp
//May need to change for A3

Player* GameEngine::getNeutralPlayer(){
    for(auto it : players){
        if(it->getName() == "NEUTRAL"){
            return it;
        }
    }
    Player* neutralPlayer = new Player("NEUTRAL", nullptr);
    this->players.push_back(neutralPlayer);
    return neutralPlayer;
}