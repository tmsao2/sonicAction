#pragma once
#include "Event.h"
class ScoreUpper :
	public Event
{
private:
	Rect _rect;
	int _score;
public:
	ScoreUpper(EventQueue& e,int score);
	~ScoreUpper();
	void Draw();
	void Update();
	EventType GetEventType()const;
	const Rect& GetCollider();
	void OnCollision();
	int GetScore()override final;
};

