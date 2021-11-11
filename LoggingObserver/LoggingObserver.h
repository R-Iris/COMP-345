#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// ILoggable class, all derived classes must implement stringToLog()
class ILoggable
{
public:
	// Implemented by a derived class, must return a string that represents the class
	virtual string stringToLog() = 0;
};

// Observer abstract class
class Observer
{
public:
	// Abstract Update method to be defined by LogObserver
	virtual void Update(ILoggable* _loggable_object) = 0;
};

// Observer implementation class which outputs to the log file
class LogObserver : public Observer
{
public:
	// Will output the stringToLog implementation from a derived class of ILoggable into the log file
	void Update(ILoggable* _loggable_object);
};

// Subject class, all derived classes can Attach() or Detach() itself from the observer
// Houses Notify() which calls the Observer's (implemented) update method
class Subject
{
public:
	// Attaches this class to the observer object
	void Attach(Observer* _logger);
	// Detaches this class from the observer object
	void Detach();
	// Calls the update method in Observer/LogObserver
	void Notify(ILoggable* _loggable_object);
private:
	// Observer object
	Observer* _observer = nullptr;
};