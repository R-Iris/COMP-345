#pragma once
#include <string>
#include <vector>

using namespace std;

class Command {
public:
	//If the command is invalid (gibberish), we still need to keep track of it, so let's make a constructor that only takes in the command's name
	Command(string);
	void saveEffect(string);

private:
	string command;
	string effect; //Ask teacher about what the effect is
};

class CommandProcessor {
public:
	virtual Command* readCommand();
	void getCommand();
	void saveCommand(Command*);
	void saveCommand(string, string);
	bool validate(Command*);

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