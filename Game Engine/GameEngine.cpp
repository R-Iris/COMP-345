#include "GameEngine.h"
#include <iostream>
using namespace std;

string *currentState;
int *currentStatePosition;
string states[8] = {"start", "map loaded", "map validated", "players added", "assign reinforcements", "issue orders", "execute orders", "win"};
bool *transition;
bool *isValid;

// Default constructor for state, sets the current state
State::State()
{
    *currentState = *states[0];
    *currentStatePosition = 0;
    *transition = false;
    *isValid = true;
    showState();
}

// Prints out the current state
void State::showState()
{
    cout << "State: " << *currentState << endl;
}

string State::getState()
{
    return *currentstate;
}

bool State::changeState(string &issuedCommand)
{
    if (currentState == *states[0] && issuedCommand == "loadmap")
    {
        *currentStatePosition = 1;
        *currentState = *states[1];
        showState();
    }
    else if (currentState == *states[1] && issuedCommand == "loadmap")
    {
        showState();
    }
    else if (currentState == *states[1] && issuedCommand == "validatemap")
    {
        *currentStatePosition = 2;
        *currentState = *states[2];
        showState();
    }
    else if (currentState == *states[2] && issuedCommand == "addplayer")
    {
        *currentStatePosition = 3;
        *currentState = *states[3];
        showState();
    }
    else if (currentState == *states[3] && issuedCommand == "addplayer")
    {
        showState();
    }
    else if (currentState == *states[3] && issuedCommand == "assigncountries")
    {
        *currentStatePosition = 4;
        *currentState = *states[4];
        showState();
        *transition = true;
    }
    else if (currentState == *states[4] && issuedCommand == "issueorder")
    {
        *currentStatePosition = 5;
        *currentState = *states[5];
        showState();
    }
    else if (currentState == *states[5] && issuedCommand == "issueorder")
    {
        showState();
    }
    else if (currentState == *states[5] && issuedCommand == "endissueorders")
    {
        *currentStatePosition = 6;
        *currentState = *states[6];
        showState();
    }
    else if (currentState == *states[6] && issuedCommand == "execorder")
    {
        showState();
    }
    else if (currentState == *states[6] && issuedCommand == "endexecorders")
    {
        *currentStatePosition = 4;
        *currentState = *states[4];
        showState();
    }
    else if (currentState == *states[6] && issuedCommand == "win")
    {
        *currentStatePosition = 7;
        *currentState = *states[7];
        showState();
    }
    else if (currentState == *states[7] && issuedCommand == "play")
    {
        *currentStatePosition = 0;
        *currentState = *states[0];
        showState();
        *transition = true;
    }
    else if (currentState == *states[7] && issuedCommand == "end")
    {
        *transition = true;
    }
    else
    {
        *isValid = false;
    }
    return *isValid;
}

void del()
{
    delete currentState;
    delete currentStatePosition;
    delete states;
    delete transition;
    delete isValid;
    currentState, currentStatePosition, states, transition, isValid = NULL;
}

// Certain actions may eventually trigger a transition to another state
Transition::Transition(string &issuedCommand)
{
}

// Command::Command()
// {
//     cout << "You haven't issued a command.";
// }
// Command::Command(string &issuedCommand)
// {
//     Transition(*issuedCommand);
// }

void playGame()
{
    State game = new State();
    while (game.getState != "end")
    {
        while (*game.isValid)
        {
            cout << "Please enter command: ";
            string *command = nullptr;
            cin >> *command;
        }
        game.changeState(*command);
    }
    end(game);
}

void end(State game)
{
    game.del();
    exit(0);
}