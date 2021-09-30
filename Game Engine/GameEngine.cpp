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

Transition::Transition() : current(nullptr), next(nullptr)
{
}

Transition::~Transition()
{
    if (!next) delete next;
    delete current;
}

Transition::Transition(State* current, State* next)  : current(current), next(next)
{
}

Transition::Transition(const Transition &transition) : current(transition.current), next(transition.next)
{
}

Transition &Transition::operator=(const Transition &transition)
{
    this->current = transition.current;
    this->next = transition.next;
    return *this;
}

ostream &operator<<(ostream &out, const Transition &transition)
{
    out << "(From: " << transition.current->stateName << ", To: " << transition.current->stateName << ")" << endl;
    return out;
}

GameEngine::GameEngine()
{
    // Initializing states
    State* start = new State("start");
    State* map_loaded = new State("map_loaded");
    State* map_validated = new State("map_validated");
    State* players_added = new State("players_added");
    State* assign_reinforcement = new State("assign_reinforcement");
    State* issue_orders = new State("issue_orders");
    State* execute_orders = new State("execute_orders");
    State* win = new State("win");
    // Connecting states together
    Transition* trans1 = new Transition(start, map_loaded);
    Transition* trans2 = new Transition(map_loaded, map_validated);
    Transition* trans3 = new Transition(map_validated, players_added);
    Transition* trans4 = new Transition(players_added, assign_reinforcement);
    Transition* trans5 = new Transition(assign_reinforcement, issue_orders);
    Transition* trans6 = new Transition(issue_orders, execute_orders);
    Transition* trans7 = new Transition(execute_orders, assign_reinforcement);
    Transition* trans8 = new Transition(execute_orders, win);
    Transition* trans9 = new Transition(win, start);
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
    // Initializing currentState
    currentState = start;
    // Announce current state
    cout << *currentState;
}

GameEngine::~GameEngine()
{
    // Calls delete on every element inside of the vector
    transitions.clear();
    currentState = nullptr;
}

GameEngine::GameEngine(vector<Transition*>& transitions, State* currentState)
{
    this->transitions = transitions;
    this->currentState = currentState;
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
        out << *gameEngine.transitions.at(i) << endl;
    }
    return out;
}

bool GameEngine::changeState(string command)
{
    if (currentState->stateName == transitions[0]->current->stateName && command == "loadmap")
    {
        currentState = transitions[0]->next;
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[1]->current->stateName && command == "loadmap")
    {
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[1]->current->stateName && command == "validatemap")
    {
        currentState = transitions[1]->next;
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[2]->current->stateName && command == "addplayer")
    {
        currentState = transitions[2]->next;
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[3]->current->stateName && command == "addplayer")
    {
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[3]->current->stateName && command == "assigncountries")
    {
        currentState = transitions[3]->next;
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[4]->current->stateName && command == "issueorder")
    {
        currentState = transitions[4]->next;
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[5]->current->stateName && command == "issueorder")
    {
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[5]->current->stateName && command == "endissueorders")
    {
        currentState = transitions[5]->next;
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[6]->current->stateName && command == "execorder")
    {
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[6]->current->stateName && command == "endexecorders")
    {
        currentState = transitions[6]->next;
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[6]->current->stateName && command == "win")
    {
        currentState = transitions[7]->next;
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[8]->current->stateName && command == "play")
    {
        currentState = transitions[8]->next;
        cout << *currentState;
        return true;
    }
    else if (currentState->stateName == transitions[8]->current->stateName && command == "end")
    {
        return true;
    }
    return false;
}


void end(GameEngine *game)
{
    delete game; // Comment out to test copy constructor
    game = NULL; // Comment out to test copy constructor

    cout << "Thank you for playing!" << endl;
    exit(0); // Comment out to test copy constructor
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
    delete copygame;
    copygame = NULL;
    delete equalsGame;
    equalsGame = NULL;
    end(game);
}