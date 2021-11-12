#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// ILoggable class, all derived classes must implement stringToLog()
class ILoggable
{
public:
	// Default constructor (unused)
	ILoggable();
	// Copy constructor (unused)
	ILoggable(const ILoggable& s);
	// Assignment operator (unused)
	ILoggable& operator=(const ILoggable& s);
	// Stream insertion operator (unused)
	friend ostream& operator<<(ostream& os, const ILoggable& s);
	// Implemented by a derived class, must return a string that represents the class
	virtual string stringToLog() = 0;
};

// Observer abstract class
class Observer
{
public:
	// Default constructor (unused)
	Observer();
	// Copy constructor (unused)
	Observer(const Observer& s);
	// Assignment operator (unused)
	Observer& operator=(const Observer& s);
	// Stream insertion operator (unused)
	friend ostream& operator<<(ostream& os, const Observer& s);
	// Abstract Update method to be defined by LogObserver
	virtual void Update(ILoggable* _loggable_object) = 0;
};

// Observer implementation class which outputs to the log file
class LogObserver : public Observer
{
public:
	// Default constructor (unused)
	LogObserver();
	// Copy constructor (unused)
	LogObserver(const LogObserver& s);
	// Assignment operator (unused)
	LogObserver& operator=(const LogObserver& s);
	// Stream insertion operator (unused)
	friend ostream& operator<<(ostream& os, const LogObserver& s);
	// Will output the stringToLog implementation from a derived class of ILoggable into the log file
	void Update(ILoggable* _loggable_object);
};

// Subject class, all derived classes can Attach() or Detach() itself from the observer
// Houses Notify() which calls the Observer's (implemented) update method
class Subject
{
public:
	// Default constructor (unused)
	Subject();
	// Destructor .. should NOT delete Observer, only set local observer object to nullptr
	~Subject();
	// Copy constructor (unused)
	Subject(const Subject &s);
	// Assignment operator (unused)
	Subject& operator=(const Subject& s);
	// Stream insertion operator (unused)
	friend ostream& operator<<(ostream& os, const Subject& s);
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