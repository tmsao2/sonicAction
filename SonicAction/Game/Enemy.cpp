#include "Enemy.h"
#include "Player.h"
#include "../Camera.h"
#include "../Game.h"
#include "../System/FileSystem.h"
#include "../System/SoundLoader.h"


Enemy::Enemy(const Camera & camera, const Player & player, const Vector2f & pos):Actor(camera, pos),_player(player)
{
	SoundData dead;
	Game::GetInstance().GetFileSystem()->Load("se/poko.wav", dead);
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
