#include "../LoggingObserver/LoggingObserver.h"


void Subject::Attach(Observer* _logger) {
	_observer = _logger;
}

void Subject::Detach() {
	if (_observer != nullptr) { _observer = nullptr; }
}

void Subject::Notify(ILoggable* _loggable_object) {
	_observer->Update(_loggable_object);

}

void LogObserver::Update(ILoggable* _loggable_object)
{
	ofstream logfile;
	logfile.open("gamelog.txt", ofstream::app);
	logfile << _loggable_object->stringToLog();
	logfile.close();
}