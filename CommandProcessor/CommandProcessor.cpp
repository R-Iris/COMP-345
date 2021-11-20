#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
#include "CommandProcessor.h"

using namespace std;

// Default constructor
Command::Command(string commandstr, Observer* _obs) : commandstr(commandstr) {
	this->Attach(_obs);
}

// Constructors assigning a enum type for commands that are valid
Command::Command(commandType command, string toAdd, Observer* _obs) {
	switch (command) {
	case commandType::loadmap:
		commandstr = "loadmap";
		this->toAdd = toAdd;
		commandNumber = 0;
		break;
	case commandType::validatemap:
		commandstr = "validatemap";
		commandNumber = 1;
		break;
	case commandType::addplayer:
		commandstr = "addplayer";
		this->toAdd = toAdd;
		commandNumber = 2;
		break;
	case commandType::gamestart:
		commandstr = "gamestart";
		commandNumber = 3;
		break;
	case commandType::replay:
		commandstr = "replay";
		commandNumber = 4;
		break;
	case commandType::quit:
		commandstr = "quit";
		commandNumber = 5;
		break;
	case commandType::gameend:
		commandstr = "gameend";
		commandNumber = 6;
		break;
    case commandType::tournament:
        commandstr = "tournament";
        commandNumber = 7;
        break;
	}
	this->Attach(_obs);
}

// Copy constructor
Command::Command(const Command& command) : commandstr(command.commandstr), effect(command.effect), toAdd(command.toAdd), commandNumber(command.commandNumber) { }

// Overloading the assignment operator
Command& Command::operator= (const Command& command) {
	this->commandstr = command.commandstr;
	this->commandNumber = command.commandNumber;
	this->effect = command.effect;
	this->toAdd = command.toAdd;

	return *this;
}

// Saves a string effect depending on which type of command it is
void Command::saveEffect(Command* command) {

	// Switch chase to save the effect of valid commands
	switch (command->commandNumber) {
	case 0:
		command->effect = command->toAdd + " has been successfully loaded";
		break;
	case 1:
		command->effect = "The map has been validated";
		break;
	case 2:
		command->effect = "Player " + command->toAdd + " has been successfully added to the game";
		break;
	case 3:
		command->effect = "The game has started";
		break;
	case 4:
		command->effect = "Replaying the game";
		break;
	case 5:
		command->effect = "Quitting the game";
		break;
	case 6:
		command->effect = "Command for testing purposes that skips the main game loop";
		break;
    case 7:
        command->effect = "Entering tournament mode";
        break;
	}
	Notify(this);
}

// Getter for the command entered
string Command::getCommandStr() {
	return commandstr;
}

// Sets the commands with a specific format
void Command::setCommandStr() {
	this->commandstr = this->commandstr + "<" + this->toAdd + ">";
}

// Getter for the effect
string Command::getEffect() {
	return effect;
}

// Getter for the addition to the command entered
string Command::getToAdd() {
	return toAdd;
}

// stringToLog implementation for ILoggable
string Command::stringToLog() {
	string command = "Command issued: " + getCommandStr()
		+ "\nCommand's effect: " + getEffect();
	return command;
}

// Overloading the output operator
ostream& operator<< (ostream& out, const Command& command) {
	return out << "Command: " << command.commandstr << command.toAdd << " | Effect: " << command.effect << '\n';
}

// Default constructor
CommandProcessor::CommandProcessor(Observer* _obs) : logger(_obs) {
	this->Attach(_obs);
}

// Copy constructor
CommandProcessor::CommandProcessor(const CommandProcessor& cmdPro) : logger(cmdPro.logger), exitProgram(cmdPro.exitProgram), cmdProPause(cmdPro.cmdProPause) {
	for (int i = 0; i < cmdPro.commandList.size(); i++) {
		commandList.push_back(cmdPro.commandList[i]);
	}

	for (int i = 0; i < cmdPro.validCommandList.size(); i++) {
		commandList.push_back(cmdPro.validCommandList[i]);
	}
}

// Overloading the assignment operator
CommandProcessor& CommandProcessor::operator= (const CommandProcessor& cmdPro) {
	this->logger = cmdPro.logger;
	this->commandList = cmdPro.commandList;
	this->validCommandList = cmdPro.validCommandList;
	this->exitProgram = cmdPro.exitProgram;
	this->cmdProPause = cmdPro.cmdProPause;

	return *this;
}

// Destructor for CommandProcessor
CommandProcessor::~CommandProcessor()
{
	this->Detach();
	logger = nullptr;
}

// Reads the command from the console
Command* CommandProcessor::readCommand() {
	string commandstr{};
	string toAdd{};
	int index{};

	cin >> commandstr;

	// When the commandProcessor reads the following commands, it prompts the user to give more information
	if (commandstr == "loadmap") {
		cout << "Which map do you wish to load? ";
		cin >> toAdd;
		cout << '\n';
	}
	else if (commandstr == "addplayer") {
		cout << "Which player do you wish to add? ";
		cin >> toAdd;
		cout << '\n';
	}
    else if(commandstr == "tournament"){
        toAdd = "-M ";
        cout << "Insert a list of map files you wish to add (separated by a comma): ";
        cin >> toAdd; toAdd += " -P ";
        cout << '\n';
        cout << "Insert a list of player strategies you wish to add (separated by a comma): ";
        cin >> toAdd; toAdd += " -G ";
        cout << '\n';
        cout << "Enter the number of games you wish to play on each map : ";
        cin >> toAdd; toAdd += " -D ";
        cout << '\n';
        cout << "Finally enter the max number of turns for each game: ";
        cin >> toAdd;
        cout << '\n';
    }
	else if (commandstr == "gamestart") {
		setcmdProPause(true);
	}

	// Switch case to decide which command object to create based on the user's input
	switch (getIndexCmdVector(commandstr)) {
	case 0:
		return new Command(Command::commandType::loadmap, toAdd, logger);
	case 1:
		return new Command(Command::commandType::validatemap, toAdd, logger);
	case 2:
		return new Command(Command::commandType::addplayer, toAdd, logger);
	case 3:
		return new Command(Command::commandType::gamestart, toAdd, logger);
	case 4:
		return new Command(Command::commandType::replay, toAdd, logger);
	case 5:
		return new Command(Command::commandType::quit, toAdd, logger);
	case 6:
		return new Command(Command::commandType::gameend, toAdd, logger);
    case 7:
        return new Command(Command::commandType::tournament,toAdd,logger);
	default:
		// If none of the valid commands are read then the default constructor with the user's input is called
		return new Command(commandstr, logger);
	}
}

// getCommand reads the command, validates it and saves the command
void CommandProcessor::getCommand(GameEngine* game, CommandProcessor* cmd) {
	Command* command = cmd->readCommand();

	// If the command is valid we save it in both the valid commands vector and the general vector
	if (validate(command, game)) {
		saveValidCommand(command);
	}

	saveCommand(command);
}

// Validates the method
bool CommandProcessor::validate(Command* command, GameEngine* game) {

	// Checks if the command can be called in the current state
	if (game->checkState(command->getCommandStr())) {

		// If the commands are the following then we add the toAdd string to get an output such as loadmap <map name>
		if (command->getCommandStr() == "loadmap") {
			command->setCommandStr();
		}
		else if (command->getCommandStr() == "addplayer") {
			command->setCommandStr();
		}
		else if (command->getCommandStr() == "quit") {
			cout << "Quitting the game.";

			// Setting the exitProgram boolean to true in order to stop the program
			exitProgram = true;
		}

		// Save the effect if the commands are valid
		command->saveEffect(command);
		return true;
	}

	cout << "Invalid command.\n";

	return false;
}

// Saves the command in the general command list
void CommandProcessor::saveCommand(Command* command) {
	commandList.push_back(command);
	Notify(this);
}

// Saves the command in the valid command list
void CommandProcessor::saveValidCommand(Command* command) {
	validCommandList.push_back(command);
}

// Gets the vector of the general command list
vector<Command*> CommandProcessor::getCommandList() {
	return commandList;
}

// Gets the vector of the valid command list
vector<Command*> CommandProcessor::getValidCommandList() {
	return validCommandList;
}

// Changes the string commandstr to an integer
int CommandProcessor::getIndexCmdVector(string commandstr) {
	for (int i = 0; i < commandVector.size(); i++) {
		if (commandVector[i] == commandstr) { return i; }
	}

	return -1;
}

// Returns bool exitProgram (if true = the program stops)
bool CommandProcessor::getExitProgram() {
	return exitProgram;
}

// Sets the bool cmdProPause (if true = the cmdPro is paused
void CommandProcessor::setcmdProPause(bool isPaused) {
	cmdProPause = isPaused;
}

// Gets the bool cmdProPause
bool CommandProcessor::getcmdProPause() {
	return cmdProPause;
}

// stringToLog implementation for ILoggable
string CommandProcessor::stringToLog()
{
	return "Inserted command: " + commandList.back()->getCommandStr() + " into the list.";
}

// Overloading the output operator
ostream& operator<< (ostream& out, const vector<Command*>& commandList) {
	out << "\n[ ";
	for (int i = 0; i < commandList.size(); i++) {
		out << "\nCommand: " + commandList[i]->getCommandStr() + " || Effect: " + commandList[i]->getEffect();
		if (i != commandList.size() - 1) out << ", ";
	}
	out << " \n]\n";

	return out;
}

// Default constructor
FileLineReader::FileLineReader() { }

// Copy constructor
FileLineReader::FileLineReader(const FileLineReader& fileReader) {
	for (int i = 0; i < fileReader.fileContent.size(); i++) {
		fileContent.push_back(fileReader.fileContent[i]);
	}
}

// Overloading the assignment operator
FileLineReader& FileLineReader::operator= (const FileLineReader& fileReader) {
	this->fileContent = fileReader.fileContent;

	return *this;
}

// Reading from the file
void FileLineReader::readLineFromFile(string fileName) {
	vector<string> lines;
	fileName = fileName + ".txt";
	ifstream myfile(fileName);

	// If the file is open we can read from it
	if (myfile.is_open()) {
		string line;

		// While the file contains something we add each line to the lines vector
		while (getline(myfile, line)) {
			lines.push_back(line);
		}

		// Closing the file
		myfile.close();

		// Copying the lines vector into the fileContent vector
		for (int i = 0; i < lines.size(); i++) {
			fileContent.push_back(lines[i]);
		}
	}
	else {
		cout << "Couldn't find the mentioned file." << '\n';
	}
}

// Returns the vector containing every line in the file read
vector<string> FileLineReader::getFileContent() {
	return fileContent;
}

// Overloading the output operator
ostream& operator<< (ostream& out, const vector<string> lines) {
	out << "\n[ ";
	for (int i = 0; i < lines.size(); i++) {
		out << "\n" + lines[i];
		if (i != lines.size() - 1) out << ", ";
	}
	out << " \n]\n";

	return out;
}

// Default constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* flr, Observer* _obs) : CommandProcessor(_obs), flr(flr), logger(_obs) {
	for (int i = 0; i < flr->getFileContent().size(); i++) {
		commands.push_back(flr->getFileContent().at(i));
	}
}

// Copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& fileAdapter) : CommandProcessor(logger), logger(fileAdapter.logger),
flr(fileAdapter.flr), index(fileAdapter.index) {
	for (int i = 0; i < flr->getFileContent().size(); i++) {
		commands.push_back(flr->getFileContent().at(i));
	}
}

// Overloading the assignment operator
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator= (const FileCommandProcessorAdapter& fileAdapter) {
	this->logger = fileAdapter.logger;
	this->flr = fileAdapter.flr;
	this->index = fileAdapter.index;

	for (int i = 0; i < flr->getFileContent().size(); i++) {
		commands.push_back(flr->getFileContent().at(i));
	}

	return *this;
}

// Destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
	flr = nullptr;
	logger = nullptr;
}

// Returns a pointer to the fileLineReader
FileLineReader* FileCommandProcessorAdapter::getFileLineReader() {
	return flr;
}

// readCommand method adapter
Command* FileCommandProcessorAdapter::readCommand() {
	string toAdd{ "" };
	
	// Using a space delimiter when reading from a file for lines such as "loadmap mapname"
	string delimiter{ " " };

	// The position of the delimiter
	size_t pos{};

	// The word before the delimiter
	string firstWord{ "" };

	// The word after the delimiter
	string secondWord{ "" };

	// Increasing the index of the line
	index++;

	// If the delimiter is found and is not at the end of the string
	if (commands[index].find(delimiter) != string::npos) {

		// Separating every line at the delimiter " " into two words
		pos = commands[index].find(delimiter);
		string firstWord(commands[index].substr(0, pos));
		string secondWord(commands[index].substr(pos + 1));

		if (firstWord == "loadmap") {
			return new Command(Command::commandType::loadmap, secondWord, logger);
		}
		else if (firstWord == "addplayer") {
			return new Command(Command::commandType::addplayer, secondWord, logger);
		}
        else if(firstWord == "tournament"){
            return new Command(Command::commandType::tournament,secondWord,logger);
        }
	}

	// If the delimiter is not found then we can read the line normally
	else if (commands[index] == "validatemap") {
		return new Command(Command::commandType::validatemap, toAdd, logger);
	}
	else if (commands[index] == "gamestart") {
		setcmdProPause(true);
		return new Command(Command::commandType::gamestart, toAdd, logger);
	}
	else if (commands[index] == "replay") {
		return new Command(Command::commandType::replay, toAdd, logger);
	}
	else if (commands[index] == "quit") {
		return new Command(Command::commandType::quit, toAdd, logger);
	}
	else if (commands[index] == "gameend") {
		return new Command(Command::commandType::gameend, toAdd, logger);
	}
	else {
		return new Command(commands[index], logger);
	}
}