#include "GameEngine.h"
#include <iostream>
using namespace std;

string *currentState;
string states[] = {"start", "map loaded", "map validated", "players added", "assign reinforcements", "issue orders", "execute orders", "win"};
State::State()
{
    currentState = &states[0];
}
void State::showState()
{
    cout << "State: " << *currentState << endl;
}

Transition::changeState()
{
}

Command::Command()
{
    cout << "You haven't issued a command.";
}
Command::Command(string &issuedCommand)
{
    GameEngine::Transition(*issuedCommand);
}
