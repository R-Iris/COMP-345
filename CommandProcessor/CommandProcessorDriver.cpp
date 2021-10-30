#include <iostream>
#include <istream>
#include "CommandProcessor.h"

using namespace std;

int main() {
	CommandProcessor* commandprocessor = new CommandProcessor();

	cout << "Please enter a command" << '\n';
	commandprocessor->getCommand();
	cout << commandprocessor->getCommandList();

	return 0;
}