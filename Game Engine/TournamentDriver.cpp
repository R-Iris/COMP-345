#include <iostream>
#include "../CommandProcessor/CommandProcessor.h"
#include "GameEngine.h"
using namespace std;

int main() {
    const int CARDS_IN_DECK = 52;

    // Instantiate Observer object
    Observer *_observer = new LogObserver();

    CommandProcessor *commandprocessor = new CommandProcessor(_observer);

    GameEngine *game = new GameEngine(_observer);
    game->setDeck(new Deck(CARDS_IN_DECK));

    State *start = game->newState("start");
    State *tournament_mode = game->newState("tournament_mode");
    State *map_loaded = game->newState("map_loaded");
    State *map_validated = game->newState("map_validated");
    State *players_added = game->newState("players_added");
    State *assign_reinforcement = game->newState("assign_reinforcement");
    State *win = game->newState("win");
    State *end_game = game->newState("end_game");


    game->newTransition(start, map_loaded, "loadmap");
    game->newTransition(start, tournament_mode, "tournament");
    game->newTransition(map_loaded, map_loaded, "loadmap");
    game->newTransition(map_loaded, map_validated, "validatemap");
    game->newTransition(map_validated, players_added, "addplayer");
    game->newTransition(players_added, players_added, "addplayer");
    game->newTransition(tournament_mode, end_game, "quit");
    game->newTransition(players_added, assign_reinforcement, "gamestart");
    game->newTransition(assign_reinforcement, win, "gameend");    //For testing purposes
    game->newTransition(win, start, "replay");
    game->newTransition(win, end_game, "quit");

    game->cmd_currentState = start;
    game->currentState = start;

    string answer;
    string file;

    cout << "Here, we read the commands that will be executed by startupPhase()" << endl;
    cout << "==================================================================" << endl << endl;
    cout << "Do you wish to accept commands from the console or read them from a file? " << '\n';

    cin >> answer;

    if (answer == "console") {
        cout << "Please enter a command" << '\n';
        while (!(commandprocessor->getExitProgram())) {
            commandprocessor->getCommand(game, commandprocessor);
        }
    } else if (answer == "file") {
        cout << "\nWhich file do you wish to open? " << '\n';

        cin >> file;

        cout << '\n';

        auto* fileReader = new FileLineReader();
        fileReader->readLineFromFile(file);

        auto* filecmd = new FileCommandProcessorAdapter(fileReader, _observer);

        while (!(commandprocessor->getExitProgram())) {
            commandprocessor->getCommand(game, filecmd);
        }

        delete filecmd;delete fileReader;delete commandprocessor;
        commandprocessor = NULL;filecmd = NULL;fileReader = NULL;
    }

    game->startupPhase(commandprocessor);

    cout << "END OF TOURNAMENT DRIVER" << endl;

    delete game;delete commandprocessor;delete _observer;
    game = NULL;commandprocessor = NULL;_observer = NULL;
}

///home/abhay/Documents/Cpp/COMP-345/Map/Assets/solar.map