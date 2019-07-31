#pragma once
#include "Event.h"

class Camera;

class Coin :
	public Event
{
private:
	int _imgH;
	Rect _rect;
	const Camera& _camera;
public:
	Coin(const Vector2& pos, const Camera& c,EventQueue& e);
	~Coin();
	void Draw();
	void Update();
	EventType GetEventType()const;
	const Rect& GetCollider();
	void OnCollision();
};

