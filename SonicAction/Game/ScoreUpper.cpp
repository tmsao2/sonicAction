#include "ScoreUpper.h"



ScoreUpper::ScoreUpper(EventQueue& e, int score) :Event(e),_score(score)
{
	_deleteByQueue = true;
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
	return EventType::score;
}

const Rect & ScoreUpper::GetCollider()
{
	return _rect;
}

void ScoreUpper::OnCollision()
{
}

int ScoreUpper::GetScore()
{
	return _score;
}
