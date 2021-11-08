#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
#include "CommandProcessor.h"

using namespace std;

Command::Command(string commandstr, Observer* _obs) : commandstr(commandstr) {
	this->Attach(_obs);
}

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
	}
	this->Attach(_obs);
}

void Command::saveEffect(Command* command) {
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
	}
	Notify(this);
}

string Command::getCommandStr() {
	return commandstr;
}

void Command::setCommandStr() {
	this->commandstr = this->commandstr + "<" + this->toAdd + ">";
}

string Command::getEffect() {
	return effect;
}

string Command::getToAdd() {
	return toAdd;
}

string Command::stringToLog() {
	string command = "Command issued: " + getCommandStr()
		+ "\nCommand's effect: " + getEffect();
	return command;
}

CommandProcessor::CommandProcessor(Observer* _obs) : logger(_obs) {
	this->Attach(_obs);
}

CommandProcessor::~CommandProcessor()
{
	this->Detach();
	logger = nullptr;
}

Command* CommandProcessor::readCommand() {
	string commandstr{};
	string toAdd{};
	int index{};

	cin >> commandstr;

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
	default:
		return new Command(commandstr, logger);
	}
}

void CommandProcessor::getCommand(GameEngine* game, CommandProcessor* cmd) {
	Command* command = cmd->readCommand();

	if (validate(command, game)) {
		saveValidCommand(command);
	}

	saveCommand(command);
}

bool CommandProcessor::validate(Command* command, GameEngine* game) {
	//Do not change state
	if (game->changeState(command->getCommandStr())) {
		if (command->getCommandStr() == "loadmap") {
			command->setCommandStr();
		}
		else if (command->getCommandStr() == "addplayer") {
			command->setCommandStr();
		}
		else if (command->getCommandStr() == "quit") {
			cout << "Quitting the game.";
			exitProgram = true;
		}
		command->saveEffect(command);
		return true;
	}

	return false;
}

void CommandProcessor::saveCommand(Command* command) {
	commandList.push_back(command);
	Notify(this);
}

void CommandProcessor::saveValidCommand(Command* command) {
	validCommandList.push_back(command);
}

vector<Command*> CommandProcessor::getCommandList() {
	return commandList;
}

vector<Command*> CommandProcessor::getValidCommandList() {
	return validCommandList;
}

int CommandProcessor::getIndexCmdVector(string commandstr) {
	for (int i = 0; i < commandVector.size(); i++) {
		if (commandVector[i] == commandstr) { return i; }
	}

	return -1;
}

bool CommandProcessor::getExitProgram() {
	return exitProgram;
}

string CommandProcessor::stringToLog()
{
	string _string_commandList = "";
	for (Command* c : commandList)
	{
		_string_commandList += "[Command: " + c->getCommandStr() + ", Effect: " + c->getEffect() + "]";

	}
	return "Command List: " + _string_commandList;
}

ostream& operator<< (ostream& out, const vector<Command*> commandList) {
	out << "\n[ ";
	for (int i = 0; i < commandList.size(); i++) {
		out << "\nCommand: " + commandList[i]->getCommandStr() + " || Effect: " + commandList[i]->getEffect();
		if (i != commandList.size() - 1) out << ", ";
	}
	out << " \n]\n";

	return out;
}

void FileLineReader::readLineFromFile(string fileName) {
	vector<string> lines;
	fileName = fileName + ".txt";
	ifstream myfile(fileName);

	if (myfile.is_open()) {
		string line;

		while (getline(myfile, line)) {
			lines.push_back(line);
		}

		myfile.close();

		cout << lines;

		fileContent = lines;
	}
	else {
		cout << "Couldn't find the mentioned file." << '\n';
	}
}

vector<string> FileLineReader::getFileContent() {
	return fileContent;
}


ostream& operator<< (ostream& out, const vector<string> lines) {
	out << "\n[ ";
	for (int i = 0; i < lines.size(); i++) {
		out << "\n" + lines[i];
		if (i != lines.size() - 1) out << ", ";
	}
	out << " \n]\n";

	return out;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* flr, Observer* _obs) : CommandProcessor(_obs), flr(flr), logger(_obs) { }

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
	flr = nullptr;
	logger = nullptr;
}

FileLineReader* FileCommandProcessorAdapter::getFileLineReader() {
	return flr;
}

Command* FileCommandProcessorAdapter::readCommand() {
	string toAdd{""};
	string delimiter{ " " };
	size_t pos{};

	string firstWord{ "" };
	string secondWord{ "" };

	vector<string> commands{ flr->getFileContent() }; 
	index++;

		if (commands[index].find(delimiter) != string::npos) {
			pos = commands[index].find(delimiter);
			string firstWord(commands[index].substr(0, pos));
			string secondWord(commands[index].substr(pos + 1));
			
			if (firstWord == "loadmap") {
				return new Command(Command::commandType::loadmap, secondWord, logger);
			}
			else if (firstWord == "addplayer") {
				return new Command(Command::commandType::addplayer, secondWord, logger);
			}
		}
		else if (commands[index] == "validatemap") {
			return new Command(Command::commandType::validatemap, toAdd, logger);
		}
		else if (commands[index] == "gamestart") {
			return new Command(Command::commandType::gamestart, toAdd, logger);
		}
		else if (commands[index] == "replay") {
			return new Command(Command::commandType::replay, toAdd, logger);
		}
		else if (commands[index] == "quit") {
			return new Command(Command::commandType::quit, toAdd, logger);
		}
		else {
			return new Command(commands[index], logger);
		}
}