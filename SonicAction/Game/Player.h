#pragma once
#include "Actor.h"

class Player :
	public Actor
{
private:
	int _imgH;
	Vector2f _vel = Vector2f(0.0f, 0.0f);
	Vector2f _accel = Vector2f(0.0f, 0.0f);
	int _jumpframe;
	int _jumpSE;
	int _deadSE;
	int _speed;
	bool _isAerial;
	bool Move(const Input & input);

	void Neutral();
	void Run();
	void Jump();

	void Accelerator(const Input & input);

	void NeutralUpdate(const Input& input);
	void RunUpdate(const Input& input);
	void JumpUpdate(const Input& input);
	void AttackUpdate(const Input& input);
	void DyingUpdate(const Input& input);
	void DieUpdate(const Input& input);

	void (Player::*_updater)(const Input& input);

public:
	Player(const Camera&);
	Player(const Camera&, const Vector2f);
	Player(const Camera&, float x, float y);
	~Player();
	bool IsAerial();
	bool IsDie();
	bool IsDying();
	void HitBlock(int blocktop);
	void OnGround(float grad, float adjustY = -1.0f);
	void OnDead();
	void PushBack(float x, float y);
	void Update(const Input& input)override final;
	void Draw()override final;
	Vector2f GetPosition()const;
	Vector2f GetVelocity()const;
	Vector2f GetAccel()const;
	const Rect& GetCollider();
	void SetVelocity(const Vector2f& v);
	void SetAccel(const Vector2f& a);
};

