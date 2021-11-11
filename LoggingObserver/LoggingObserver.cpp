#include "../LoggingObserver/LoggingObserver.h"

ILoggable::ILoggable() {}
ILoggable::ILoggable(const ILoggable& s) {}
ILoggable& ILoggable::operator=(const ILoggable& s) { return *this; }

Subject::Subject() {}
Subject::~Subject() { this->_observer = nullptr; }
Subject::Subject(const Subject& s) : _observer(s._observer) {}
Subject& Subject::operator=(const Subject& s) 
{ 
	this->_observer = s._observer; 
	return *this;
}

void Subject::Attach(Observer* _logger) {
	_observer = _logger;
}

void Subject::Detach() {
	if (_observer != nullptr) { _observer = nullptr; }
}

void Subject::Notify(ILoggable* _loggable_object) {
	if (_observer != nullptr) _observer->Update(_loggable_object);
}

Observer::Observer() {}
Observer::Observer(const Observer& s) {}
Observer& Observer::operator=(const Observer& s) { return *this; }

LogObserver::LogObserver() {}
LogObserver::LogObserver(const LogObserver& s) {}
LogObserver& LogObserver::operator=(const LogObserver& s) { return *this; }

void LogObserver::Update(ILoggable* _loggable_object)
{
	// opening output file stream
	ofstream logfile;
	logfile.open("gamelog.txt", ofstream::app); // append setting. If gamelog.txt is not found, it will create it.
	logfile << _loggable_object->stringToLog() << endl; // output the stringToLog to the output file
	logfile.close(); // close the output file stream
}

ostream& operator<<(ostream& os, const ILoggable& s) { return os; }
ostream& operator<<(ostream& os, const Observer& s) { return os; }
ostream& operator<<(ostream& os, const LogObserver& s) { return os; }
ostream& operator<<(ostream& os, const Subject& s) { return os; }