#include "Enemy.h"
#include "Player.h"
#include "../Camera.h"
#include "../Game.h"
#include "../System/FileSystem.h"
#include "../System/SoundLoader.h"
#include "../Game/EventQueue.h"
#include "../Game/ScoreUpper.h"


Enemy::Enemy(const Camera & camera, const Player & player, const Vector2f & pos, EventQueue& e):Actor(camera, pos),_player(player),_eventQ(e)
{
	SoundData dead;
	Game::GetInstance().GetFileSystem()->Load("se/piko.wav", dead);
	_deadSE = dead.GetHandle();
}

Enemy::~Enemy()
{
}

void Enemy::OnCollision(Actor & actor)
{
	if (_pos.y > actor.GetPosition().y)
	{
		auto v = GetVelocity();
		actor.SetVelocity(Vector2f(v.x, -8.0f));
		PlaySoundMem(_deadSE, DX_PLAYTYPE_BACK);
		_eventQ.AddEvent(new ScoreUpper(_eventQ, 50));
		this->OnDead();
	}
	else
	{
		actor.OnDead();
	}
}

void Enemy::SetPosition(const Vector2f & pos)
{
	_pos = pos;
}
