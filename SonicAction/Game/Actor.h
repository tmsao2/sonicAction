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
	ancor,
	attack,
	damage
};

struct ActionRect
{
	RectType type;
	Rect rc;
	ActionRect() :type(RectType::ancor), rc(0, 0, 0, 0){}
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

	const Rect& GetCollider()const;
	virtual ~Actor();
	virtual void Update(const Input&) = 0;
	virtual void Draw() = 0;
	virtual void PushBack(float x, float y) = 0;
	virtual void OnGround(int groundline, float grad) = 0;
};

