#pragma once
#include "Event.h"
class ScoreUpper :
	public Event
{
private:
	Rect _rect;
public:
	ScoreUpper(EventQueue& e);
	~ScoreUpper();
	void Draw();
	void Update();
	EventType GetEventType()const;
	const Rect& GetCollider();
	void OnCollision();
};

