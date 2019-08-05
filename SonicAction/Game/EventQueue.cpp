#include "EventQueue.h"
#include "Event.h"
#include "EventObserver.h"
#include <algorithm>

EventQueue::EventQueue()
{
}


EventQueue::~EventQueue()
{
}

void EventQueue::Notify()
{
	for (auto& ob : _observer)
	{
		for (auto& e : _events)
		{
			if (e->IsAvailvale())
			{
				if (ob->OnNotify(e))
				{
					e->_isAvailable = false;
				}
			}
		}
	}
	auto it=std::remove_if(_events.begin(), _events.end(), [](Event* e)
	{
		return !e->IsAvailvale();
	});
	auto itCpy = it;
	for (; itCpy != _events.end(); ++itCpy)
	{
		if ((*itCpy)->_deleteByQueue)
		{
			delete (*itCpy);
		}
	}
	_events.erase(it, _events.end());
}

void EventQueue::AddObserver(std::shared_ptr<EventObserver> ob)
{
	_observer.emplace_back(ob);
}

void EventQueue::RemoveObserver(std::shared_ptr<EventObserver> ob)
{
}

void EventQueue::AddEvent(Event* e)
{
	_events.emplace_back(e);
}
