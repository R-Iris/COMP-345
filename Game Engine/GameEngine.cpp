#include "GameEngine.h"
#include "../CommandProcessor/CommandProcessor.h"
#include "../Player/Player.h"
#include <regex>
#include <math.h>
#include <random>
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

GameEngine::GameEngine() : currentState(nullptr), deck(new Deck()), cmd_currentState(nullptr), map(nullptr) {
    players.push_back(new Player("NEUTRAL",new Hand(),this));
}
GameEngine::GameEngine(Observer* _obs) : currentState(nullptr), deck(new Deck()), _observer(_obs), cmd_currentState(nullptr), map(nullptr) {
    this->Attach(_obs);
    players.push_back(new Player("NEUTRAL",new Hand(),this));
}

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

	cmd_currentState = nullptr;

	// Delete deck
	delete deck;
	deck = nullptr;

	// Set _observer to nullptr
	_observer = nullptr;

	this->Detach();
}

GameEngine::GameEngine(const GameEngine& gameEngine)
{
	this->states = gameEngine.states;
	this->transitions = gameEngine.transitions;
	this->players = gameEngine.players;
	this->map = new Map(*gameEngine.map);
	this->deck = new Deck(*gameEngine.deck);
	this->Attach(gameEngine._observer);
}

GameEngine& GameEngine::operator=(const GameEngine& gameEngine)
{
	this->states = gameEngine.states;
	this->transitions = gameEngine.transitions;
	this->players = gameEngine.players;
	this->map = new Map(*gameEngine.map);
	this->deck = new Deck(*gameEngine.deck);
	this->Attach(gameEngine._observer);
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
}

bool GameEngine::checkState(string command)
{
	for (int i = 0; i < transitions.size(); i++)
	{
		if (cmd_currentState->stateName == transitions[i]->current->stateName && command == transitions[i]->command)
		{
			cmd_currentState = transitions[i]->next;
			cout << *cmd_currentState;
			return true;
		}
		else if (cmd_currentState->stateName == "win" && command == "end") return true;
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
			Notify(this);
			return true;
		}
		else if (currentState->stateName == "win" && command == "end") return true;
	}
	Notify(this);
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

// Used when the player enters 'quit'
void GameEngine::end()
{
	delete this;
	cout << "Thank you for playing!" << endl;
}

// Game Startup Phase

void GameEngine::startupPhase(CommandProcessor* cp)
{
	// Reset the state of the game every time we start a new one.
	resetContext();

	// Use the command list to get the commands, make sure to change states in between commands
	for (Command* c : cp->getValidCommandList()) {
		// Display the current state
		cout << endl;
		cout << "Current state: " << currentState->stateName << endl << endl;

		string command = c->getCommandStr();

		if (command.find("loadmap") != std::string::npos) {
			// Load the map (how to parse the filename from the command?)
			string effect = c->getEffect();
			std::regex extractionPattern("(.*.map)");
			std::smatch match;

			// We found a map file name from the commmand's effect!
			if (std::regex_search(effect, match, extractionPattern)) {
				string mapFileName = (string)match[1];
				setMap(MapLoader::createMapfromFile(mapFileName)); // <-- TODO: Make sure this is an absolute path!
				
				// Transition to 'validatemap' state, Handle failure
				if (!changeState("loadmap")) {
					cout << "ERROR: Could not transition to 'loadmap' from current state " << currentState->stateName << endl;
				}
			}
		}

		// Do I have to check if we are in a valid state before executing the command?
		else if (command == "validatemap") {
			// Validate the map
			map->validate();

			if (map->isValid()) {
				// Transition to 'addplayer' state, handle failure
				if (!changeState("validatemap")) {
					cout << "ERROR: Could not to transition to 'validatemap' from current state " << currentState->stateName << endl;
				}
			}

			else {
				// Does the state go back to loadmap, or do we just fail and exit?
				cout << "An invalid map has been loaded." << endl;
			}
		}

		else if (command.find("addplayer") != std::string::npos) {
			// Add player (This part should loop so as to ensure that we have 2-6 players in the game.)
			string effect = c->getEffect();

			std::regex extractionPattern("Player (.*) has");
			std::smatch match;

			// Check to see if we have 2-6 players in the game
			if (players.size() < 6) {
				if (std::regex_search(effect, match, extractionPattern)) {
					// TODO: Check if player name corresponds to one of the player strategies, if so, create the corresponding type of player. If not, create a human player.
					if (match[1] == "Aggressive" || match[1] == "aggressive" || match[1] == "AGGRESSIVE") {
						// Create and add aggressive player
						Player* p = nullptr;
						p = new Player("Aggressive", new Hand, this, new AggressivePlayerStrategy(NULL));
						p->getPlayerStrategy()->setPlayer(p);
						addPlayer(p);
					}
					
					else if (match[1] == "Cheater" || match[1] == "cheater" || match[1] == "CHEATER") {
						// Create and add cheater player
						Player* p = nullptr;
						p = new Player("Cheater", new Hand, this, new CheaterPlayerStrategy(NULL));
						p->getPlayerStrategy()->setPlayer(p);
						addPlayer(p);
					}
					
					else if (match[1] == "Benevolent" || match[1] == "benevolent" || match[1] == "BENEVOLENT") {
						// Create and add benevolent player
						Player* p = nullptr;
						p = new Player("Benevolent", new Hand, this, new BenevolentPlayerStrategy(NULL));
						p->getPlayerStrategy()->setPlayer(p);
						addPlayer(p);
					}

					else if (match[1] == "Neutral" || match[1] == "neutral" || match[1] == "NEUTRAL") {
						// Create and add neutral player
						Player* p = nullptr;
						p = new Player("Neutral", new Hand, this, new NeutralPlayerStrategy(NULL));
						p->getPlayerStrategy()->setPlayer(p);
						addPlayer(p);
					}
					
					else {
						// Create and add human player
						addPlayer(new Player(match[1], new Hand, this));
					}
				}
			}

			else {
				// Let the user know that they cannot add anymore players
				cout << "Limit of players in game has been reached, no new players may be added." << endl;
			}


			if (players.size() >= 2) {
				// Switch states

				// Check if state changed successfully, otherwise handle failure.
				if (!changeState("addplayer")) {
					cout << "ERROR: Could not transition to 'addplayer' from current state " << currentState->stateName << endl;
				}
			}

			else {
				// Let the user know that there needs to be more players for the game to start
				cout << "There must be at least 2 players before the game can start." << endl;
			}
		}

		else if (command == "gamestart") {
			// Initialize random seed
			srand(time(NULL));

			/* Gamestart command does the following:
			*  a) Evenly pass out territories to players (remainder goes to the neutral player).

			*  b) Determine the order in which players get their turns (Randomly rearrange this class's Players list)

			*  c) Give 50 armies to each player, which are placed in their respective reinforcement pool (new Player field)

			*  d) Let each player draw 2 cards from the deck using Deck's draw() method

			*  e) Switch the game to the "play" state. (Call mainGameLoop())
			*/
			
			// Assign territories - Come up with a way to fairly distribute all countries between players
			int neutralTerritories = map->getTerritories().size() % players.size();
			int distrbutedTerritories = map->getTerritories().size() - neutralTerritories;

			// Randomize the territories and then pass them out to each player
			// ===============================================================

			// Define the number of territories each player will get (remove from denominator, since the neutral player shouldn't get its own territories yet.)
			int territoriesPerPlayer = distrbutedTerritories / (players.size() - 1);

			// Keep track of which territories we've already handed out
			vector<int> taken;

			// For each player, pass this number of territories out.
			for (Player* p : players) {
				if (p->getName() != getNeutralPlayer()->getName()) {
					int i = 0;

					while (i < territoriesPerPlayer) {
						// Generate the index of a random territory
						int choose = rand() % map->getTerritories().size();

						// If it hasn't already been taken, then give it to the player.
						if (!std::count(taken.begin(), taken.end(), choose)) {
							p->addOwnedTerritory(map->getTerritories().at(choose));
							taken.push_back(choose);
							i++;
						}
					}
				}
			}

			// Assign unassigned territories to Neutral player (How to get neutral player?).
			for (Territory* t : map->getTerritories()) {
				bool owned = false;

				for (Player* p : players) {
					if (p->ownsTerritory(t)) {
						owned = true;
						break;
					}
				}

				if (!owned) {
					getNeutralPlayer()->addOwnedTerritory(t);
				}
			}

			// Determine the turn order randomly - Re-arrange the players in the vector
			std::shuffle(players.begin(), players.end(), std::random_device()); // This is not total randomization, given 'n' players this will produce the same shuffle order of those 'n' players.

			// Give each player 50 armies to begin with and let them draw 2 cards from the deck
			for (Player* p : players) {
				if (p->getName() != getNeutralPlayer()->getName()) {
					// Give 50 armies
					p->setReinforcementPool(50);

					// Draw 2 cards for the player
					p->getHand()->addHand(deck->draw());
					p->getHand()->addHand(deck->draw());
				}
			}

			// Switch the game to the play phase
			
			// Command processor setter for bool
			//cmd_game pointer points to win state

			if (!changeState("gamestart")) {
				cout << "ERROR: Could not transition to 'gamestart' from current state " << currentState->stateName << endl;
			}

			else {
				mainGameLoop();
			}
		}

		else if (command == "tournament") {
			//cout << "Current command: " << command << endl;
			//cout << "Current effect: " << c->getEffect() << endl;

			vector<string> mapFiles;
			vector<string> playerStrats;
			int numGames = 0;
			int maxRounds = 0;

			string effect = c->getEffect();

			// Parse command string
			char* effectStr = new char[effect.length() + 1];
			strcpy(effectStr, effect.c_str());
			
			char* fields = strtok(effectStr, " ,");

			while (fields != NULL) {
				string toCompare(fields);

				if (toCompare == "-M") {
					// Get map files
					//cout << "Reading maps..." << endl;

					do {
						fields = strtok(NULL, " ,");
						toCompare = string(fields);

						if (toCompare != "-P")
							mapFiles.push_back(toCompare); // Save the map file that was passed in for later use.
					} while (toCompare != "-P");
				}

				if (toCompare == "-P") {
					// Get player strategies
					//cout << "Reading strategies..." << endl;

					do {
						fields = strtok(NULL, " ,");
						toCompare = string(fields);

						if (toCompare != "-G")
							playerStrats.push_back(toCompare); // Save the player strategy that was passed in for later use.
					} while (toCompare != "-G");
				}

				if (toCompare == "-G") {
					// Get number of games to be played on each map
					//cout << "Reading number of games..." << endl;
					
					fields = strtok(NULL, " ,");
					toCompare = string(fields);
					numGames = stoi(toCompare);

					fields = strtok(NULL, " ,");
					toCompare = string(fields);
				}

				if (toCompare == "-D") {
					// Get max number of rounds for each game
					//cout << "Reading number of rounds..." << endl;

					fields = strtok(NULL, " ,");
					toCompare = string(fields);
					maxRounds = stoi(toCompare);
				}

				fields = strtok(NULL, " ,");

			}

			/* PLAN FOR THE TOURNAMENT MODE:
				* If we enter "tournament mode", we need to automate 'G' games (G is an argument provided to the command)
				* A game is set up and subsequently played via commands in the CommandProcessor's valid command list
				* Order to properly start a game is: loadmap, validatemap, addplayer, gamestart
				* 'gamestart' command should call mainGameLoop() after ensuring that the game's context is valid.
				* Once mainGameLoop() terminates, flow should return to startupPhase() to start the next game, if necessary.
				* TODO: mainGameLoop() should also self-terminate once the max number of turns has been reached.
				  * Add a variable that counts the number of turns that have been taken.
				* TODO: Once a game terminates, we need to write the result into "the" log file (gamelog.txt)
			*/

			this->max_rounds = maxRounds; // Set the maximum number of rounds

			// TODO: Add functionality to 'addplayer' to instantiate and add the different types of players based on a certain name being provided for each one?

            //Modifying Tournament Result
            tournamentResult = "Tournament Mode: \nM: ";
            for(string mapFileName : mapFiles){
                tournamentResult += mapFileName + ", ";
            }
            tournamentResult += "\nP: ";
            for(string playerStrat : playerStrats){
                tournamentResult += playerStrat + ", ";
            }
            tournamentResult += "\nG: " + numGames;
            tournamentResult += "\nD: " + maxRounds;

            tournamentResult += "\n\nResults: \n\n";

			for (string mapFileName : mapFiles) { // mapFileName is what should be passed to the loadmap command

                tournamentResult += mapFileName + " : \n";

				CommandProcessor* cp2 = new CommandProcessor(this->_observer);

				for (int i = 0; i < numGames; i++) {
                    tournamentResult += "Game " + (numGames + 1);
                    tournamentResult += ": \n";

					// Populate the command list with the commands necessary to start a new game
					// Order to properly start a game is: loadmap, validatemap, addplayer, gamestart
					// 1) Add loadmap command
					Command* loadmap = new Command(Command::commandType::loadmap, mapFileName, this->_observer);
					loadmap->saveEffect(loadmap);
					cp2->saveValidCommand(loadmap);

					// 2) Add validatemap command
					Command* validatemap = new Command(Command::commandType::validatemap, "", this->_observer);
					validatemap->saveEffect(validatemap);
					cp2->saveValidCommand(validatemap);

					// 3) Add addplayer commands
					for (string strategy : playerStrats) {
						Command* addplayer = new Command(Command::commandType::addplayer, strategy, this->_observer);
						addplayer->saveEffect(addplayer);
						cp2->saveValidCommand(addplayer);
					}

					// 4) Add gamestart command
					Command* gamestart = new Command(Command::commandType::gamestart, "", this->_observer);
					gamestart->saveEffect(gamestart);
					cp2->saveValidCommand(gamestart);
				}
				// Start a new game
				startupPhase(cp2);
			}
            Notify(this);
		}
	}
}

void GameEngine::resetContext() {
	// Clear map
	if (this->map != NULL) {
		delete this->map;
		this->map = NULL;
	}

	// Clear players
	for (int i = 0; i < this->players.size(); i++) {
		delete this->players.at(i);
		this->players.at(i) = NULL;
	}
	this->players.clear();
	getNeutralPlayer();

	// Reset Deck
	delete this->deck;
	this->deck = NULL;
	this->deck = new Deck(52);

	// Go back to start state
	this->currentState = this->states.at(0);
}

// Main Game Loop
void GameEngine::mainGameLoop() {
	/*This loop shall continue until only one of the players owns all the territories in the map, at which point a winner is
	announced and the game ends.*/

	bool onePlayerOwnsAllTerritories = false;

	// Get the total number of territories, 0 if there is no map
	int numTotalTerritories = 0;
	if (map != nullptr) {
		numTotalTerritories = map->getTerritories().size();
	}

	// Keep track of how many rounds have passed
	int roundsPassed = 0;

	do {
		if (roundsPassed >= this->max_rounds && this->max_rounds > 0) {
			// TODO: The game should end in a draw.
			cout << "Game has reached the maximum number of rounds... It's a draw. " << endl;
			break;
		}

	    for (Player* p : players) {

			// If player owns no territories, remove from game
	        if (p->toDefend().empty() && p->getName() != "NEUTRAL") {
				cout << "Player " << p->getName() << " has no more territories! Removing player " << p->getName() << " from the game!" << endl;
				removePlayer(p);
	        }

			// If player owns all the territories, they win
	        if (p->toDefend().size() >= numTotalTerritories) {

				// Used to break the loop
				onePlayerOwnsAllTerritories = true;

				// Announce this player as winner
				cout << "The winner is: " << p->getName() << "!" << endl;
				
				changeState("win");

				// NOTE: In tournament mode, this shouldn't hang for input from the user.
				cout << "Input \"replay\" to restart the game, or \"quit\" (or anything else) to quit the program:" << endl;
				string userInput;
				cin >> userInput;
				cout << endl;
				if (userInput == "replay") {
					changeState("replay");
					cout << "Restarting the game!" << endl;
				}
				return;
	        }
	    }
	
		if (!onePlayerOwnsAllTerritories) {
			// Reinforcement Phase
			changeState("endexecorders");
			reinforcementPhase();

			// Issue Orders Phase
			changeState("issueorder");
			issueOrdersPhase();

			// Execute Orders Phase
			changeState("issueordersend");
			executeOrdersPhase();
		}

		roundsPassed++;
	} while (!onePlayerOwnsAllTerritories);
}

void GameEngine::reinforcementPhase() {
	for (Player* p : players) {
	    // Armies = # of territories owned divided by 3, rounded down : or 3 minimum
	    int armies = floor(p->toDefend().size() / 3);
	    // Bonus for owning all of a continent's territories gets added to the armies
	    // Place armies in player's reinforcement pool
		// Minimum 3 armies, or armies + continent bonus
	    p->setReinforcementPool(max(p->getReinforcementPool() + armies + map->calculateContinentBonus(p), 3));
	}
}

void GameEngine::issueOrdersPhase() {
	// Issue orders for each player in the players list
	for (Player* p : players) {
        if(p->getName()!="NEUTRAL"){
            p->issueOrder();
        }
	}
}

void GameEngine::executeOrdersPhase() {
	for (Player* p : players) {
        //Executing deploys first
        if(p->getName()!="NEUTRAL"){
            for(Orders* o: p->getOrdersList()->ordersList){
                if(o->getName() == "Deploy"){
                    o->execute();
                    p->getOrdersList()->removeOrder(o);
                }
            }
        }
	}

	// Find the longest list length
	int longestList = 0;
	for (Player* p : players) {
		if (p->getName() != "NEUTRAL") {
			if (p->getOrdersList()->ordersList.size() > longestList) {
				longestList = p->getOrdersList()->ordersList.size();
			}
		}
	}

	// Round-robin execution of the other orders
	for (int i = 0; i < longestList; i++) {
		for (Player* p : players) {
			if (p->getName() != "NEUTRAL") {
				if (!p->getOrdersList()->ordersList.empty()) {
					Orders* o = p->getOrdersList()->ordersList.at(0);
					o->execute();
					p->getOrdersList()->removeOrder(o);
				}
			}
		}
	}

    //used for Advance order in Orders.cpp
    for(auto it:players){
        it->receivedCardThisTurn = false;
    }
}


//******************
// stringToLog Implementation for ILoggable
string GameEngine::stringToLog() {
	if(currentState->stateName!="tournament_mode"){
        return "Current GameEngine State: " + currentState->stateName;
    }
    else{
        return tournamentResult;
    }
}

//Neutral Player related stuff for Blockade order in Orders.cpp

Player* GameEngine::getNeutralPlayer(){
    for(auto it : players){
        if(it->getName() == "NEUTRAL"){
            return it;
        }
    }
    Player* neutralPlayer = new Player("NEUTRAL", new Hand(), this, new NeutralPlayerStrategy(NULL));
	neutralPlayer->getPlayerStrategy()->setPlayer(neutralPlayer);
    this->players.push_back(neutralPlayer);
    return neutralPlayer;
}