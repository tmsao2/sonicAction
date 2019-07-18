#include "Enemy.h"
#include "../Camera.h"
#include "Player.h"


Enemy::Enemy(const Camera & camera, const Player & player, const Vector2f & pos):Actor(camera, pos),_player(player)
{
}

Enemy::~Enemy()
{
}
