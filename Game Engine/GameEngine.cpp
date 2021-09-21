#include "GameEngine.h"
#include <iostream>
using namespace std;

// Default constructor for state, sets the current state
State::State()
{
    // Populating states array with proper state names
    states[0] = "start";
    states[1] = "map loaded";
    states[2] = "map validated";
    states[3] = "players added";
    states[4] = "assign reinforcements";
    states[5] = "issue orders";
    states[6] = "execute orders";
    states[7] = "win";

    currentState = states[0];
    currentStatePosition = 0;
    showState();
}

// Prints out the current state
void State::showState()
{
    cout << "Game State: " << currentState << endl;
}

string State::getState()
{
    return currentState;
}

bool State::isValid(string command)
{
    if (currentState == states[0] && command == "loadmap")
    {
        return true;
    }
    else if (currentState == states[1] && command == "loadmap")
    {
        return true;
    }
    else if (currentState == states[1] && command == "validatemap")
    {
        return true;
    }
    else if (currentState == states[2] && command == "addplayer")
    {
        return true;
    }
    else if (currentState == states[3] && command == "addplayer")
    {
        return true;
    }
    else if (currentState == states[3] && command == "assigncountries")
    {
        return true;
    }
    else if (currentState == states[4] && command == "issueorder")
    {
        return true;
    }
    else if (currentState == states[5] && command == "issueorder")
    {
        return true;
    }
    else if (currentState == states[5] && command == "endissueorders")
    {
        return true;
    }
    else if (currentState == states[6] && command == "execorder")
    {
        return true;
    }
    else if (currentState == states[6] && command == "endexecorders")
    {
        return true;
    }
    else if (currentState == states[6] && command == "win")
    {
        return true;
    }
    else if (currentState == states[7] && command == "play")
    {
        return true;
    }
    else if (currentState == states[7] && command == "end")
    {
        return true;
    }
    else
        return false;
}

bool State::changeState(string issuedCommand)
{
    if (currentState == states[0] && issuedCommand == "loadmap")
    {
        currentStatePosition++;
        currentState = states[currentStatePosition];
        showState();
    }
    else if (currentState == states[1] && issuedCommand == "loadmap")
    {
        showState();
    }
    else if (currentState == states[1] && issuedCommand == "validatemap")
    {
        currentStatePosition++;
        currentState = states[currentStatePosition];
        showState();
    }
    else if (currentState == states[2] && issuedCommand == "addplayer")
    {
        currentStatePosition++;
        currentState = states[currentStatePosition];
        showState();
    }
    else if (currentState == states[3] && issuedCommand == "addplayer")
    {
        showState();
    }
    else if (currentState == states[3] && issuedCommand == "assigncountries")
    {
        currentStatePosition++;
        currentState = states[currentStatePosition];
        showState();
    }
    else if (currentState == states[4] && issuedCommand == "issueorder")
    {
        currentStatePosition++;
        currentState = states[currentStatePosition];
        showState();
    }
    else if (currentState == states[5] && issuedCommand == "issueorder")
    {
        showState();
    }
    else if (currentState == states[5] && issuedCommand == "endissueorders")
    {
        currentStatePosition++;
        currentState = states[currentStatePosition];
        showState();
    }
    else if (currentState == states[6] && issuedCommand == "execorder")
    {
        showState();
    }
    else if (currentState == states[6] && issuedCommand == "endexecorders")
    {
        currentStatePosition = 4;
        currentState = states[4];
        showState();
    }
    else if (currentState == states[6] && issuedCommand == "win")
    {
        currentStatePosition++;
        currentState = states[currentStatePosition];
        showState();
    }
    else if (currentState == states[7] && issuedCommand == "play")
    {
        currentStatePosition = 0;
        currentState = states[0];
        showState();
    }
}

// Launches states of game
void playGame()
{
    State *game = new State();
    string command = "";
    while (game->getState() != "win" || command != "end")
    {
        cout << "Please enter command: ";
        cin >> command;
        while (!game->isValid(command))
        {
            cout << "Command invalid, please try again: ";
            cin >> command;
        }
        game->changeState(command);
    }
    end(game);
}

// Ends game and calls del()
void end(State *game)
{
    delete game;
    game = NULL;

    cout << "Thank you for playing!";
    exit(0);
}
