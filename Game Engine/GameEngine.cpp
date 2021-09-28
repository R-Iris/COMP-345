#include "GameEngine.h"

// Members of State Class

State::State() : stateName("none"), nextState(nullptr)
{
}

State::State(string name, State *nextState) : stateName(name), nextState(nextState)
{
}

State::State(string name) : stateName(name), nextState(nullptr)
{
}

State::State(const State *state) : stateName(state->stateName), nextState(state->nextState)
{
}

State &State::operator=(const State *state)
{
    this->stateName = state->stateName;
    this->nextState = state->nextState;
    return *this;
}

ostream &operator<<(ostream &out, const State *state)
{
    out << "Current State: " << state->stateName << endl;
    out << "Next Available State: " << state->nextState->stateName << endl;
    return out;
}

// Members of Transition Class

Transition::Transition()
{
    // Initializing states
    State *start = new State("start");
    states.push_back(start);
    State *map_loaded = new State("map_loaded");
    states.push_back(map_loaded);
    State *map_validated = new State("map_validated");
    states.push_back(map_validated);
    State *players_added = new State("players_added");
    states.push_back(players_added);
    State *assign_reinforcement = new State("assign_reinforcement");
    states.push_back(assign_reinforcement);
    State *issue_orders = new State("issue_orders");
    states.push_back(issue_orders);
    State *execute_orders = new State("execute_orders");
    states.push_back(execute_orders);
    State *win = new State("win");
    states.push_back(win);
    // Connecting states together
    start->nextState = map_loaded;
    map_loaded->nextState = map_validated;
    map_validated->nextState = players_added;
    players_added->nextState = assign_reinforcement;
    assign_reinforcement->nextState = issue_orders;
    issue_orders->nextState = execute_orders;
    execute_orders->nextState = assign_reinforcement;
    win->nextState = start;
    // Initializing currentState
    currentState = start;
    // Announce current state
    cout << currentState;
}

Transition::~Transition()
{
    states.clear();
    currentState = nullptr;
}

Transition::Transition(const Transition *transition) : states(transition->states), currentState(transition->currentState)
{
}

Transition &Transition::operator=(const Transition *transition)
{
    this->states = transition->states;
    this->currentState = transition->currentState;
    return *this;
}

ostream &operator<<(ostream &out, const Transition *transition)
{
    int size = transition->states.size();
    for (int i = 0; i < size; i++)
    {
        out << "State(" << i << "): " << transition->states.at(i)->stateName << endl;
    }
    return out;
}

bool Transition::changeState(string command)
{
    if (currentState->stateName == states[0]->stateName && command == "loadmap")
    {
        currentState = currentState->nextState;
        cout << currentState;
        return true;
    }
    else if (currentState == states[1] && command == "loadmap")
    {
        cout << currentState;
        return true;
    }
    else if (currentState == states[1] && command == "validatemap")
    {
        currentState = currentState->nextState;
        cout << currentState;
        return true;
    }
    else if (currentState == states[2] && command == "addplayer")
    {
        currentState = currentState->nextState;
        cout << currentState;
        return true;
    }
    else if (currentState == states[3] && command == "addplayer")
    {
        cout << currentState;
        return true;
    }
    else if (currentState == states[3] && command == "assigncountries")
    {
        currentState = currentState->nextState;
        cout << currentState;
        return true;
    }
    else if (currentState == states[4] && command == "issueorder")
    {
        currentState = currentState->nextState;
        cout << currentState;
        return true;
    }
    else if (currentState == states[5] && command == "issueorder")
    {
        cout << currentState;
        return true;
    }
    else if (currentState == states[5] && command == "endissueorders")
    {
        currentState = currentState->nextState;
        cout << currentState;
        return true;
    }
    else if (currentState == states[6] && command == "execorder")
    {
        cout << currentState;
        return true;
    }
    else if (currentState == states[6] && command == "endexecorders")
    {
        currentState = currentState->nextState;
        cout << currentState;
        return true;
    }
    else if (currentState == states[6] && command == "win")
    {
        currentState = states[7];
        cout << currentState;
        return true;
    }
    else if (currentState == states[7] && command == "play")
    {
        currentState = currentState->nextState;
        cout << currentState;
        return true;
    }
    else if (currentState == states[7] && command == "end")
    {
        return true;
    }
    return false;
}

void end(Transition *game)
{
    delete game; // Comment out to test copy constructor
    game = NULL; // Comment out to test copy constructor

    cout << "Thank you for playing!" << endl;
    exit(0); // Comment out to test copy constructor
}

void playGame()
{
    Transition *game = new Transition();
    // Transition *copygame = new Transition(*game); // Copied game using copy constructor
    // cout << *game; // Test insertion operator
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
        // cout << "copygame State: " << copygame->currentState << endl; // Test copied state object
    }
    end(game);
    // Test copy constructor
    // while (copygame->getState() != "win" || command != "end")
    // {
    //     cout << "Please enter command: ";
    //     cin >> command;
    //     while (!copygame->isValid(command))
    //     {
    //         cout << "Command invalid, please try again: ";
    //         cin >> command;
    //     }
    //     copygame->changeState(command);
    //     cout << "\"game\" State: " << *game << endl;
    // }
    // end(copygame);
}