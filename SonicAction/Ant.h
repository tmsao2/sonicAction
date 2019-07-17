#pragma once
#include "Enemy.h"
#include "Geometry.h"


class Ant :
	public Enemy
{
private:
	Vector2f _pos;
	Vector2f _vel;
public:
	Ant(const Player& player,Vector2f pos);
	~Ant();
	void Update();
	void Draw();
};

