#pragma once

#include <iostream>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class ILoggable
{
public:
	virtual string stringToLog() = 0;
};

class Observer
{
public:
	virtual void Update(ILoggable* _loggable_object) = 0;
};

class LogObserver : public Observer
{
public:
	void Update(ILoggable* _loggable_object);
};

class Subject
{
public:
	void Attach(Observer* _logger);
	void Detach();
	void Notify(ILoggable* _loggable_object);
private:
	Observer* _observer;
};