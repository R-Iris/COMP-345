#include "GameEngine.h"

// Members of State Class

State::State() : stateName("none")
{
}

State::State(string name) : stateName(name)
{
}

State::State(const State &state) : stateName(state.stateName)
{
}

State &State::operator=(const State &state)
{
    this->stateName = state.stateName;
    return *this;
}

ostream &operator<<(ostream &out, const State &state)
{
    out << "Current State: " << state.stateName << endl;
    return out;
}

// Members of Transition Class

Transition::Transition() : current(nullptr), next(nullptr), command("none")
{
}

Transition::~Transition()
{
    cout << "Destructor of Transition has been called" << endl;
}

Transition::Transition(State* current, State* next, string command)  : current(current), next(next), command(command)
{
}

Transition::Transition(const Transition &transition) : current(transition.current), next(transition.next), command(transition.command)
{
}

Transition &Transition::operator=(const Transition &transition)
{
    this->current = transition.current;
    this->next = transition.next;
    this->command = transition.command;
    return *this;
}

ostream &operator<<(ostream &out, const Transition &transition)
{
    out << "(From: " << transition.current->stateName << ", To: " << transition.next->stateName << ")" << endl;
    return out;
}

// Members of GameEngine class

GameEngine::GameEngine()
{
    // Initializing states
    State* start = new State("start"); states.push_back(start);
    State* map_loaded = new State("map_loaded"); states.push_back(map_loaded);
    State* map_validated = new State("map_validated"); states.push_back(map_validated);
    State* players_added = new State("players_added"); states.push_back(players_added);
    State* assign_reinforcement = new State("assign_reinforcement"); states.push_back(assign_reinforcement);
    State* issue_orders = new State("issue_orders"); states.push_back(issue_orders);
    State* execute_orders = new State("execute_orders"); states.push_back(execute_orders);
    State* win = new State("win"); states.push_back(win);

    // Connecting states together
    Transition* trans1 = new Transition(start, map_loaded, "loadmap");
    Transition* trans2 = new Transition(map_loaded, map_loaded, "loadmap");
    Transition* trans3 = new Transition(map_loaded, map_validated, "validatemap");
    Transition* trans4 = new Transition(map_validated, players_added, "addplayer");
    Transition* trans5 = new Transition(players_added, players_added, "addplayer");
    Transition* trans6 = new Transition(players_added, assign_reinforcement, "assigncountries");
    Transition* trans7 = new Transition(assign_reinforcement, issue_orders, "issueorder");
    Transition* trans8 = new Transition(issue_orders, issue_orders, "issueorder");
    Transition* trans9 = new Transition(issue_orders, execute_orders, "endissueorders");
    Transition* trans10 = new Transition(execute_orders, execute_orders, "execorder");
    Transition* trans11 = new Transition(execute_orders, assign_reinforcement, "endexecorders");
    Transition* trans12 = new Transition(execute_orders, win, "win");
    Transition* trans13 = new Transition(win, start, "play");
    Transition* trans14 = new Transition(start, win, "test");

    // Pushing transitions to transition vector
    transitions.push_back(trans1);
    transitions.push_back(trans2);
    transitions.push_back(trans3);
    transitions.push_back(trans4);
    transitions.push_back(trans5);
    transitions.push_back(trans6);
    transitions.push_back(trans7);
    transitions.push_back(trans8);
    transitions.push_back(trans9);
    transitions.push_back(trans10);
    transitions.push_back(trans11);
    transitions.push_back(trans12);
    transitions.push_back(trans13);
    transitions.push_back(trans14);
    // Initializing currentState
    currentState = start;
    // Announce current state
    cout << *currentState;
}

GameEngine::~GameEngine()
{
    cout << "Destructor of GameEngine has been called" << endl;
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

GameEngine::GameEngine(const GameEngine &gameEngine)
{
    this->states = gameEngine.states;
    this->transitions = gameEngine.transitions;
    this->currentState = gameEngine.currentState;
}

GameEngine& GameEngine::operator=(const GameEngine& gameEngine) 
{
    this->transitions = gameEngine.transitions;
    this->currentState = gameEngine.currentState;
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


void end(GameEngine *game)
{
    delete game;
    game = NULL;

    cout << "Thank you for playing!" << endl;
    exit(0);
}

void playGame()
{
    GameEngine *game = new GameEngine();
    GameEngine *copygame = new GameEngine(*game); // Copied game using copy constructor
    GameEngine* equalsGame = game;
    cout << "Memory Address of Original game object: " << &game << endl;
    cout << "Memory Address of Copied (=) game object: " << &equalsGame << endl;
    cout << "GameEngine insertion operator: " << *game; // Test insertion operator
    string command = "";
    while (game->currentState->stateName != "win" || command != "end")
    {
        cout << "Please enter command: ";
        cin >> command;
        while (!game->changeState(command))
        {
            cout << "Command invalid, please try again: ";
            cin >> command;
        }
        cout << "copygame State: " << *copygame->currentState << endl; // Test copied state object
    }
    //delete copygame;
    //copygame = NULL;
    //delete equalsGame;
    //equalsGame = NULL;
    end(game);
}