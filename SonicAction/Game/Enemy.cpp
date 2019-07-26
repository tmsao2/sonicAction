#include "Enemy.h"
#include "../Camera.h"
#include "Player.h"


Enemy::Enemy(const Camera & camera, const Player & player, const Vector2f & pos):Actor(camera, pos),_player(player)
{
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
