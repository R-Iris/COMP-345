#pragma once
#include <string>
#include <vector>

#include "../Game Engine/GameEngine.h"

using namespace std;

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
	int commandNumber;
};

class CommandProcessor {
public:
	virtual Command* readCommand();
	void getCommand();
	void saveCommand(Command*);
	bool validate(Command*);
	vector<Command*> getCommandList();
	int getIndexCmdVector(string);

	friend ostream& operator<< (ostream&, const vector<Command*>);

private:
	vector<Command*> commandList;
	string toAdd;
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