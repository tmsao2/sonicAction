#pragma once
#include "../Geometry.h"

enum class EventType
{
	coin = 1,
	ultimate=3,
	goal=5
};

class Camera;

class Event
{
protected:
	const Camera& _camera;
	Rect _rect;
public:
	Event(const Rect& rc, const Camera& c);
	~Event();
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual EventType GetEventType()const = 0;
	const Rect& GetCollider();
};

