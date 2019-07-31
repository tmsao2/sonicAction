#pragma once
#include <vector>
#include <memory>
#include "../Geometry.h"

class Event;
class EventObserver;

class EventQueue
{
private:
	std::vector<std::shared_ptr<EventObserver>> _observer;
	std::vector<Event*> _events;
public:
	EventQueue();
	~EventQueue();
	void Notify();
	void AddObserver(std::shared_ptr<EventObserver> ob);
	void RemoveObserver(std::shared_ptr<EventObserver> ob);
	void AddEvent(Event* e);
};

