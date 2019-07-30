#pragma once
#include "Actor.h"

class Player;
class Spawner;

class Enemy :
	public Actor
{
	friend Spawner;
protected:
	const Player& _player;
	bool _isReverse;
	virtual std::shared_ptr<Enemy> MakeClone() = 0;
public:
	Enemy(const Camera& camera,const Player& player,const Vector2f& pos);
	virtual ~Enemy();

	virtual void Update(const Input&) = 0;
	virtual void Draw() = 0;

	virtual void OnGround(float grad, float adjustY = -1.0f)override = 0;
	virtual void OnDead() = 0;
	virtual void OnCollision(Actor& actor)override;

	virtual Vector2f GetVelocity()const override = 0;
	virtual void SetVelocity(const Vector2f& v) override = 0;

	virtual Vector2f GetAccel()const override = 0;
	virtual void SetAccel(const Vector2f& a)override = 0;

	virtual Vector2f GetPosition()const override = 0;

	virtual void PushBack(float x, float y)override = 0;

	void SetPosition(const Vector2f& pos);

};

