#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include "CommandProcessor.h"

using namespace std;

Command::Command(string commandstr) : commandstr(commandstr), effect("N/A") { }

//Temporary method, probably wrong
void Command::saveEffect(string commandstr) {
	if (commandstr == "loadmap") {
		this->effect = "A map has been loaded";
	}
}

string Command::getCommandStr() {
	return commandstr;
}

string Command::getEffect() {
	return effect;
}

Command* CommandProcessor::readCommand() {
	string commandstr;
	cin >> commandstr;

	return new Command(commandstr);
}

void CommandProcessor::getCommand() {
	Command* command = readCommand();

	validate(command);
	saveCommand(command);
}

//Should this use GameEngine?
bool CommandProcessor::validate(Command* command) {
	//saveEffect called if the command is true

	command->saveEffect(command->getCommandStr());
	return true;
}

void CommandProcessor::saveCommand(Command* command) {
	commandList.push_back(command);
}

vector<Command*> CommandProcessor::getCommandList() {
	return commandList;
}

ostream& operator<< (ostream& out, const vector<Command*> commandList) {
	out << "\n[ ";
	for (int i = 0; i < commandList.size(); i++) {
		out << '\n' + commandList[i]->getCommandStr() + " : " + commandList[i]->getEffect();
		if (i != commandList.size() - 1) out << ", ";
	}
	out << " \n]\n";

	return out;
}