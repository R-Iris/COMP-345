#pragma once

#include <iostream>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class ILoggable
{
	virtual ostream& stringToLog(ostream& os) = 0;
};

class Observer
{
public:
	void Update(ILoggable& _loggable_object);
};

class LogObserver : Observer
{
public:
	void Update(ILoggable& _loggable_object);
};

class Subject
{
public:
	~Subject();
	void Attach(Observer& _observed_object);
	void Detach(Observer& _observed_object);
	void Notify(ILoggable& _loggable_object);
private:
	list<Observer*> _observed_objects;
};