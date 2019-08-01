#include "ScoreUpper.h"



ScoreUpper::ScoreUpper(EventQueue& e) :Event(e)
{
}


ScoreUpper::~ScoreUpper()
{
}

void ScoreUpper::Draw()
{
}

void ScoreUpper::Update()
{
}

EventType ScoreUpper::GetEventType() const
{
	return EventType();
}

const Rect & ScoreUpper::GetCollider()
{
	return _rect;
}

void ScoreUpper::OnCollision()
{
}
