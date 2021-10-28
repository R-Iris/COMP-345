#include "GameEngine.h"

// Members of State Class

State::State() : stateName("none") {}
State::State(string name) : stateName(name) {}
State::State(const State &state) : stateName(state.stateName) {}

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

Transition::Transition() : current(nullptr), next(nullptr), command("none") {}
Transition::Transition(State* current, State* next, string command)  : current(current), next(next), command(command) {}
Transition::Transition(const Transition &transition) : current(transition.current), next(transition.next), command(transition.command) {}

Transition &Transition::operator=(const Transition &transition)
{
    // Intentionally making shallow copies to refer to the same states
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

GameEngine::GameEngine(const GameEngine &gameEngine)
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


//******************
// stringToLog Implementation for ILoggable
ostream& GameEngine::stringToLog(ostream& os) {
    os << this;
    return os;
}
