#pragma once
#include "../Geometry.h"

enum class EventType
{
	coin = 1,
	ultimate=3,
	goal=5
};

class Actor;
class EventQueue;

class Event
{
	friend EventQueue;
protected:
	bool _isAvailable = true;
	EventQueue& _eventQ;
public:
	Event(EventQueue& e);
	~Event();
	bool IsAvailvale()const { return _isAvailable; }
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual EventType GetEventType()const = 0;
	virtual const Rect& GetCollider() = 0;
	virtual void OnCollision() = 0;
};

