#include "GameEngine.h"

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

GameEngine::GameEngine() : currentState(nullptr) {}
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
}

GameEngine::GameEngine(const GameEngine& gameEngine)
{
	this->states = gameEngine.states;
	this->transitions = gameEngine.transitions;
}

GameEngine& GameEngine::operator=(const GameEngine& gameEngine)
{
	this->states = gameEngine.states;
	this->transitions = gameEngine.transitions;
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

bool GameEngine::changeState(string command)
{
	for (int i = 0; i < transitions.size(); i++)
	{
		if (currentState->stateName == transitions[i]->current->stateName && command == transitions[i]->command)
		{
			currentState = transitions[i]->next;
			cout << *currentState;
			return true;
		}
		else if (currentState->stateName == "win" && command == "end") return true;
	}
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

void GameEngine::startupPhase()
{
}

// Main Game Loop

void GameEngine::mainGameLoop() {
	/*
	This loop shall continue until only one of the players owns all the territories in the map, at which point a winner is
	announced and the game ends.
	*/
	bool onePlayerOwnsAllTerritories = true;
	/*int numTotalTerritories = map->getTerritories().size();*/

	//do {
	//
	//    /*
	//    The main game loop also checks for any player that does not control at least one
	//    territory; if so, the player is removed from the game
	//    */
	//    for (Player* p : players) {
	//        if (p->toDefend().empty()) {
	//            // Remove p from game
	//        }
	//        if (p->toDefend().size() >= numTotalTerritories) {
	//            // Announce this player as winner
	//            // End game
	//        }
	//    }
	//
	//    // Reinforcement Phase
	//    reinforcementPhase();

	//    /*
	//    Issuing Orders Phase � Players issue orders and place them in their order list through a call to the
	//    Player::issueOrder() method. This method is called in round-robin fashion across all players by the
	//    game engine. This must be implemented in a function/method named issueOrdersPhase() in the game
	//    engine.
	//    */
	//    issueOrdersPhase();

	//    /*
	//    Orders Execution Phase � Once all the players have signified in the same turn that they are not issuing
	//    one more order, the game engine proceeds to execute the top order on the list of orders of each player in
	//    a round-robin fashion (i.e. the �Order Execution Phase��see below). Once all the players� orders have
	//    been executed, the main game loop goes back to the reinforcement phase. This must be implemented in
	//    a function/method named executeOrdersPhase() in the game engine.
	//    */
	//    executeOrdersPhase();
	//} while (!onePlayerOwnsAllTerritories);
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

	//for (Player* p : players) {
	//    // Armies = # of territories owned divided by 3, rounded down : or 3 minimum
	//    int armies = floor(p->toDefend().size() / 3);
	//    // Bonus for owning all continent's territories, does it get added to armies, or replaces it?
	//    // Also how to find if a player owns all territories from a continent
	//    // How to retrieve a continent's control bonus value
	//    // armies = armies + continentControlBonus? OR armies = continentControlBonus?

	//    // Place armies in player's reinforcement pool
	//    // p.reinforcementPool(max(armies, 3));
	//}
}

void GameEngine::issueOrdersPhase() {
	/*
	The issuing orders phase decision-making is implemented in the player�s issueOrder() method, which
	implements the following:
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

	/*for (Player* p : players) {
	}*/
}

void GameEngine::executeOrdersPhase() {
}

/*
//******************
// stringToLog Implementation for ILoggable
ostream& GameEngine::stringToLog(ostream& os) {
	os << this;
	return os;
}
*/