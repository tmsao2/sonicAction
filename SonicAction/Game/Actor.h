#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "../Geometry.h"
#include "../System/ActionLoader.h"

class Camera;
class Input;
class BoxCollider;

class Actor
{
protected:
	float _angle;
	Vector2f _pos;
	bool _isLeft;
	Rect _rect;
	std::string _currentAct;
	int _nowidx;
	const Camera& _camera;
	int _frame;
	std::unique_ptr<ActionSet> _actionSet;

	void ChangeAction(const char* act);
	void ReadActFile(const char* filepath);
	bool AdvanceAnimetion();

public:
	Actor(const Camera&);
	Actor(const Camera&,const Vector2f);
	Actor(const Camera&,float x,float y);

	const Rect GetRect(const Rect& rec)const;

	virtual const Rect& GetCollider() = 0;

	void DebagDraw();
	virtual ~Actor();
	virtual Vector2f GetVelocity()const = 0;
	virtual Vector2f GetAccel()const = 0;
	virtual Vector2f GetPosition()const = 0;
	virtual void SetVelocity(const Vector2f& v) = 0;
	virtual void SetAccel(const Vector2f& a) = 0;
	virtual void Update(const Input&) = 0;
	virtual void Draw() = 0;
	virtual void PushBack(float x, float y) = 0;
	virtual void OnGround(float grad,float adjustY = -1.0f) = 0;
};

