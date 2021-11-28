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

// Command class - object containing the information the user has written
class Command : public ILoggable, public Subject {
public:
	enum class commandType { loadmap, validatemap, addplayer, gamestart, replay, quit, gameend,tournament};

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

	friend ostream& operator<< (ostream&, const Command&);

private:
	string commandstr;
	string effect{ "Invalid Command" };

	// Additional string to add for commands such as loadmap and addplayer to get an output such as loadmap <map name>
	string toAdd{ "" };

	// Integer ID to idenfity the different types of commands. By default this is -1 for invalid commands
	int commandNumber{ -1 };
};

// CommandProcessor class - reads the console
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

	friend ostream& operator<< (ostream&, const vector<Command*>&);

private:
	Observer* logger;

	// Vector of all commands written in the console
	vector<Command*> commandList;

	// Vector of all valid commands written in the console
	vector<Command*> validCommandList;

	// Boolean to see if the program should exit
	bool exitProgram = false;

	// Boolean to see if the commandProcessor should pause
	bool cmdProPause = false;

	// Vector of valid commands
	vector<string> commandVector = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit", "gameend", "tournament"};
};

// FileLineReader class - reads from a file
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

// FileCommandProcessorAdapter class - adapts the content read from a file for the CommandProcessor to understand
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

	// Index representing each line read by the file. Starts at -1 since the readCommand() method increases it by one every time it is called.
	int index{ -1 };

	// Vector of all commands read from the file
	vector<string> commands{};
};