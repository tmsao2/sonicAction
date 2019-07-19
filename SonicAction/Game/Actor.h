#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "../Geometry.h"

class Camera;
class Input;
class BoxCollider;

enum class RectType
{
	none,
	attack,
	damage,
	push
};

struct ActionRect
{
	RectType type;
	Rect rc;
	ActionRect() :type(RectType::none), rc(0, 0, 0, 0){}
	ActionRect(RectType t, Rect r) :type(t), rc(r){}
};

struct CutInfo 
{
	Rect rc;
	Vector2 center;
	int duration;
	std::vector<ActionRect> actrects;
};

struct ActionInfo
{
	bool isLoop;
	std::vector<CutInfo> cuts;
};

struct ActionData
{
	std::string imgFilePath;
	std::map<std::string, ActionInfo> actInfo;
};

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
	ActionData _actionData;

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

