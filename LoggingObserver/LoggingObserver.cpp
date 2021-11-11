#include "../LoggingObserver/LoggingObserver.h"


void Subject::Attach(Observer* _logger) {
	_observer = _logger;
}

void Subject::Detach() {
	if (_observer != nullptr) { _observer = nullptr; }
}

void Subject::Notify(ILoggable* _loggable_object) {
	if (_observer != nullptr) _observer->Update(_loggable_object);
}

void LogObserver::Update(ILoggable* _loggable_object)
{
	// opening output file stream
	ofstream logfile;
	logfile.open("gamelog.txt", ofstream::app); // append setting. If gamelog.txt is not found, it will create it.
	logfile << _loggable_object->stringToLog() << endl; // output the stringToLog to the output file
	logfile.close(); // close the output file stream
}