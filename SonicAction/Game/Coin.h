#pragma once
#include "Event.h"


class Coin :
	public Event
{
private:
	int _imgH;
public:
	Coin(const Vector2& pos, const Camera& c);
	~Coin();
	void Draw();
	void Update();
	EventType GetEventType()const;
};

