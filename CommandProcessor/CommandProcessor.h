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
class State;
class Transition;

class Command : public ILoggable, public Subject {
public:
	enum class commandType { loadmap, validatemap, addplayer, gamestart, replay, quit };

	// If the command is invalid (gibberish), we still need to keep track of it, so let's make a constructor that only takes in the command's name
	Command(string, Observer*);
	Command(commandType, string, Observer*);
	Command(const Command& command);
	Command& operator= (const Command&);
	void saveEffect(Command*);
	string getCommandStr();
	void setCommandStr();
	string getEffect();
	string getToAdd();

	// stringToLog Implementation for ILoggable
	string stringToLog();
private:
	string commandstr;
	string effect{ "Invalid Command" };
	string toAdd{ "" };
	int commandNumber{ -1 };
};

class CommandProcessor : public ILoggable, public Subject {
public:
	CommandProcessor(Observer*);
	CommandProcessor(const CommandProcessor&);
	CommandProcessor& operator= (const CommandProcessor&);
	~CommandProcessor();
	virtual Command* readCommand();
	void getCommand(GameEngine*, CommandProcessor*);
	void saveCommand(Command*);
	void saveValidCommand(Command*);
	bool validate(Command*, GameEngine*);
	vector<Command*> getCommandList();
	vector<Command*> getValidCommandList();
	int getIndexCmdVector(string);
	bool getExitProgram();
	void setcmdProPause(bool);
	bool getcmdProPause();

	// stringToLog Implementation for ILoggable
	string stringToLog();

	friend ostream& operator<< (ostream&, const vector<Command*>);

private:
	Observer* logger;
	vector<Command*> commandList;
	vector<Command*> validCommandList;
	bool exitProgram = false;
	bool cmdProPause = false;
	vector<string> commandVector = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" };
};

class FileLineReader {
public:
	FileLineReader();
	FileLineReader(const FileLineReader&);
	FileLineReader& operator= (const FileLineReader&);
	void readLineFromFile(string);
	vector<string> getFileContent();

	friend ostream& operator<< (ostream&, const vector<string>);

private:
	vector<string> fileContent;
};

class FileCommandProcessorAdapter : public CommandProcessor {
public:
	FileCommandProcessorAdapter(FileLineReader*, Observer*);
	FileCommandProcessorAdapter(const FileCommandProcessorAdapter&);
	FileCommandProcessorAdapter& operator= (const FileCommandProcessorAdapter&);
	~FileCommandProcessorAdapter();
	FileLineReader* getFileLineReader();
	Command* readCommand();

	friend ostream& operator<< (ostream&, const vector<string>);

private:
	Observer* logger;
	FileLineReader* flr;
	int index{ -1 };
	vector<string> commands{};
};