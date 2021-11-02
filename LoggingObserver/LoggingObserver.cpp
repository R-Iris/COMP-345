#include "../LoggingObserver/LoggingObserver.h"

Subject::~Subject() {
	_observed_objects.clear();
}

void Subject::Attach(Observer& _observed_object) {
	_observed_objects.push_back(_observed_object);
}

void Subject::Detach(Observer& _observed_object) {
	_observed_objects.remove(_observed_object);
}

void Subject::Notify(ILoggable& _loggable_object) {
	for (list<Observer*>::iterator i = _observed_objects.begin(); i != _observed_objects.end(); i++)
	{
		i->Update();
	}
}

void LogObserver::Update(ILoggable &_loggable_object)
{
	ofstream logfile;
	logfile.open("gamelog.txt", ofstream::app);
	logfile << _loggable_object.stringToLog();
	logfile.close();
}