#pragma once
#include "Enemy.h"
#include "../Geometry.h"


class Ant :
	public Enemy
{
private:
	void NormalUpdate();
	void DyingUpdate();
	void DieUpdate();

	void (Ant::*_updater)();

public:
	Ant(const Camera& camera,const Player& player,int x,int y);
	~Ant();

	void Update(const Input& input)override final;
	void Draw()override final;

	void OnGround(float grad, float adjustY = -1.0f)override;
	void OnDead()override;

	bool IsDie()override;
	bool IsDying()override;

	Vector2f GetVelocity()const override;
	void SetVelocity(const Vector2f& v)override;

	Vector2f GetAccel()const override;
	void SetAccel(const Vector2f& a)override;

	const Rect& GetCollider()override;

	Vector2f GetPosition()const override;
	void PushBack(float x, float y)override;
	
};

