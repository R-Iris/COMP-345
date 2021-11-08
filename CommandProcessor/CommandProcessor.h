#pragma once
#include <string>
#include <vector>

#include "../Game Engine/GameEngine.h"
#include "../LoggingObserver/LoggingObserver.h"

using namespace std;

class GameEngine;
class Observer;
class ILoggable;
class Subject;

class Command  : public ILoggable, public Subject  {
public:
	enum class commandType { loadmap, validatemap, addplayer, gamestart, replay, quit };
	//If the command is invalid (gibberish), we still need to keep track of it, so let's make a constructor that only takes in the command's name
	Command(string, Observer*);
	Command(commandType, Observer*);
	void saveEffect(Command*, string);
	string getCommandStr();
	void setCommandStr(string);
	string getEffect();

	//******************
	// stringToLog Implementation for ILoggable
	string stringToLog();
private:
	string commandstr;
	string effect;
	int commandNumber{-1};
};

class CommandProcessor  : public ILoggable, public Subject  {
public:
	CommandProcessor(Observer*);
	~CommandProcessor();
	virtual Command* readCommand();
	void getCommand(GameEngine*);
	void saveCommand(Command*);
	void saveValidCommand(Command*);
	bool validate(Command*, GameEngine*);
	vector<Command*> getCommandList();
	vector<Command*> getValidCommandList();
	int getIndexCmdVector(string);
	bool getExitProgram();
	
	//******************
	// stringToLog Implementation for ILoggable
	string stringToLog();

	friend ostream& operator<< (ostream&, const vector<Command*>);

private:
	Observer* logger;
	vector<Command*> commandList;
	vector<Command*> validCommandList;
	string toAdd{ "" };
	bool exitProgram = false;
	vector<string> commandVector = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" };
};

class FileLineReader {
public:
	string readLineFromFile(string);
private:
	Observer* logger;
};

class FileCommandProcessorAdapter : public CommandProcessor {
public:
	FileCommandProcessorAdapter(Observer*);
	//~FileCommandProcessorAdapter();
	FileLineReader* getFileLineReader();
	Command* readCommand();

private:
	Observer* logger;
	FileLineReader* flr;
};