#pragma once


class Event;

class EventObserver
{
public:
	EventObserver();
	virtual ~EventObserver();
	virtual bool OnNotify(Event*) = 0;
};

