#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include "CommandProcessor.h"

using namespace std;

Command::Command(string commandstr, Observer* _obs) : commandstr(commandstr), effect("Invalid command"), commandNumber(-1){
	this->Attach(_obs);
}

Command::Command(commandType command, Observer* _obs) : effect("Invalid command"){
	switch (command) {
	case commandType::loadmap:
		commandstr = "loadmap";
		commandNumber = 0;
		break;
	case commandType::validatemap:
		commandstr = "validatemap";
		commandNumber = 1;
		break;
	case commandType::addplayer:
		commandstr = "addplayer";
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

void Command::saveEffect(Command* command, string toAdd) {
	switch (command->commandNumber) {
	case 0:
		command->effect = toAdd + " has been successfully loaded";
		break;
	case 1:
		command->effect = toAdd + " has been validated";
		break;
	case 2:
		command->effect = toAdd + " player has been added";
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

void Command::setCommandStr(string commandStr) {
	this->commandstr = this->commandstr + "<" + commandStr + ">";
}

string Command::getEffect() {
	return effect;
}

string Command::stringToLog()
{
	string command = "Command issued: " + getCommandStr() 
		+ "\nCommand's effect: " + getEffect();
	return command;
}

CommandProcessor::CommandProcessor(Observer* _obs) : logger(_obs)
{
	this->Attach(_obs);
}

CommandProcessor::~CommandProcessor()
{
	this->Detach();
	logger = nullptr;
}

Command* CommandProcessor::readCommand() {
	string commandstr{};
	int index{};

	cin >> commandstr;

	switch (getIndexCmdVector(commandstr)) {
	case 0:
		return new Command(Command::commandType::loadmap, logger);
	case 1:
		return new Command(Command::commandType::validatemap, logger);
	case 2:
		return new Command(Command::commandType::addplayer, logger);
	case 3:
		return new Command(Command::commandType::gamestart, logger);
	case 4:
		return new Command(Command::commandType::replay, logger);
	case 5:
		return new Command(Command::commandType::quit, logger);
	default:
		return new Command(commandstr, logger);
	}
}

void CommandProcessor::getCommand(GameEngine* game) {
	Command* command = readCommand();

	if (validate(command, game)) {
		saveValidCommand(command);
	}

	saveCommand(command);
}

bool CommandProcessor::validate(Command* command, GameEngine* game) {
	//Do not change state
	if (game->changeState(command->getCommandStr())) {
		if (command->getCommandStr() == "loadmap") {
			cout << "Which map do you wish to load? ";
			cin >> toAdd;
			cout << '\n';
			command->setCommandStr(toAdd);
		}
		else if (command->getCommandStr() == "addplayer") {
			cout << "What is the name of the player? ";
			cin >> toAdd;
			cout << '\n';
			command->setCommandStr(toAdd);
		}
		else if (command->getCommandStr() == "quit") {
			cout << "Quitting the game.";
			exitProgram = true;
		}
		command->saveEffect(command, toAdd);
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