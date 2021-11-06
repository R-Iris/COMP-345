#pragma once
#include <string>
#include <vector>

#include "../Game Engine/GameEngine.h"

using namespace std;

class GameEngine;

class Command {
public:
	enum class commandType { loadmap, validatemap, addplayer, gamestart, replay, quit };
	//If the command is invalid (gibberish), we still need to keep track of it, so let's make a constructor that only takes in the command's name
	Command(string);
	Command(commandType);
	void saveEffect(Command*, string);
	string getCommandStr();
	void setCommandStr(string);
	string getEffect();

private:
	string commandstr;
	string effect; //Ask teacher about what the effect is
	int commandNumber{-1};
};

class CommandProcessor {
public:
	virtual Command* readCommand();
	void getCommand(GameEngine* game);
	void saveCommand(Command*);
	void saveValidCommand(Command*);
	bool validate(Command*, GameEngine*);
	vector<Command*> getCommandList();
	vector<Command*> getValidCommandList();
	int getIndexCmdVector(string);
	bool getExitProgram();

	friend ostream& operator<< (ostream&, const vector<Command*>);

private:
	vector<Command*> commandList;
	vector<Command*> validCommandList;
	string toAdd{ "" };
	bool exitProgram = false;
	vector<string> commandVector = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" };
};

class FileLineReader {
public:
	string readLineFromFile();
};

class FileCommandProcessorAdapter :Command {
public:
	virtual Command* readCommand();

private:
	FileLineReader flr;
};