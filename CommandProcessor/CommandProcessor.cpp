#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include "CommandProcessor.h"

using namespace std;

Command::Command(string command) : command(command), effect("N/A") { }

//Temporary method, probably wrong
void Command::saveEffect(string effect) {
	this->effect = effect;
}

Command* CommandProcessor::readCommand() {
	string commandstr;
	cin >> commandstr;

	return new Command(commandstr);
}

void CommandProcessor::getCommand() {
	validate(readCommand());
	saveCommand(readCommand());
}

//Should this use GameEngine?
bool CommandProcessor::validate(Command* command) {
	//saveEffect called if the command is true
}

void CommandProcessor::saveCommand(Command* command) {

}