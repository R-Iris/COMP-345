#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include "CommandProcessor.h"

using namespace std;

Command::Command(string commandstr) : commandstr(commandstr), effect("N/A"), commandNumber(-1) { }

Command::Command(commandType command) : effect("N/A") {
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

Command* CommandProcessor::readCommand() {
	string commandstr{};
	int index{};

	cin >> commandstr;

	switch (getIndexCmdVector(commandstr)) {
	case 0:
		return new Command(Command::commandType::loadmap);
		break;
	case 1:
		return new Command(Command::commandType::validatemap);
		break;
	case 2:
		return new Command(Command::commandType::addplayer);
		break;
	case 3:
		return new Command(Command::commandType::gamestart);
		break;
	case 4:
		return new Command(Command::commandType::replay);
		break;
	case 5:
		return new Command(Command::commandType::quit);
		break;
	default:
		return new Command(commandstr);
	}
}

void CommandProcessor::getCommand() {
	Command* command = readCommand();

	validate(command);
	saveCommand(command);
}

//Should this use GameEngine?
bool CommandProcessor::validate(Command* command) {
	//saveEffect called if the command is true
	if (command->getCommandStr() == "loadmap") {
		cout << "Which map do you wish to load? ";
		cin >> toAdd;
		cout << '\n';
		command->setCommandStr(toAdd);
	}

	command->saveEffect(command, toAdd);
	return true;
}

void CommandProcessor::saveCommand(Command* command) {
	commandList.push_back(command);
}

vector<Command*> CommandProcessor::getCommandList() {
	return commandList;
}

int CommandProcessor::getIndexCmdVector(string commandstr) {
	for (int i = 0; i < commandVector.size(); i++) {
		if (commandVector[i] == commandstr) { return i; }
	}

	return -1;
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