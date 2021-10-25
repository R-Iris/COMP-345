#include "../LoggingObserver/LoggingObserver.h"

Subject::Subject() {
	_loggable_objects = new list<ILoggable*>;
}

Subject::~Subject() {
	delete _loggable_objects;
}

void Subject::Attach(ILoggable& _loggable_object) {
	_loggable_objects.insert(_loggable_object);
}

void Subject::Detach(ILoggable& _loggable_object) {
	_loggable_objects.remove(_loggable_object);
}

void Subject::Notify() {
	for (list<ILoggable*>::iterator i = _loggable_objects->begin(); i != _loggable_objects->end(); i++)
	{
		*i->Update();
	}
}

LogObserver::Update(ILoggable &_observed_object)
{
	ofstream logfile;
	logfile.open("gamelog.txt", ofstream::app);
	logfile << _observed_object->stringToLog();
	logfile.close();
}

