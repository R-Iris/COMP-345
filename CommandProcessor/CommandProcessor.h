#pragma once
#include <string>
#include <vector>

//#include "../Game Engine/GameEngine.h"

using namespace std;

class Command {
public:
	//If the command is invalid (gibberish), we still need to keep track of it, so let's make a constructor that only takes in the command's name
	Command(string);
	void saveEffect(string);
	string getCommandStr();
	string getEffect();

private:
	string commandstr;
	string effect; //Ask teacher about what the effect is
};

class CommandProcessor {
public:
	virtual Command* readCommand();
	void getCommand();
	void saveCommand(Command*);
	bool validate(Command*);
	vector<Command*> getCommandList();
	
	friend ostream& operator<< (ostream&, const vector<Command*>);

private:
	vector<Command*> commandList;
};

class FileLineReader {
public:
	string readLineFromFile();
};

class FileCommandProcessorAdapter:Command {
public:
	virtual Command* readCommand();

private:
	FileLineReader flr;
};