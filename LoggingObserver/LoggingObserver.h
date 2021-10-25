#pragma once

#include <iostream>
#include <list>
#include <string>
#include <ofstream>
#include <string>
using namespace std;


class Observer
{
	virtual void Update(ILoggable& _observed_object) = 0;
};

class ILoggable
{
	virtual void stringToLog() = 0;
};

class Subject 
{
public:
	Subject();
	~Subject();
	void Attach(ILoggable& _loggable_object);
	void Detach(ILoggable& _loggable_object);
	void Notify();
private:
	list<ILoggable*>* _loggable_objects;
};


class LogObserver : Observer
{
	void Update(ILoggable& _observed_object);
};