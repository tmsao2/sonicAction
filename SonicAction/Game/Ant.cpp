#include "Ant.h"
#include "../Camera.h"
#include "Player.h"


Ant::Ant(const Camera& camera, const Player& player,int x,int y):Enemy(camera,player,Vector2f(x,y))
{
	ReadActFile("action/ant.act");
	_imgH = LoadGraph(_actionData.imgFilePath.c_str());
	auto sign = player.GetPosition().x - x;
	sign = sign * abs(sign);
	_vel.x = sign;
	_pos = Vector2f(x, y);
	ChangeAction("idle");
}

Ant::~Ant()
{
}

void Ant::Update(const Input & input)
{
	_pos += _vel;
	AdvanceAnimetion();
}

void Ant::Draw()
{
	auto& actInfo = _actionData.actInfo[_currentAct];
	auto& cut = actInfo.cuts[_nowidx];
	auto rc = cut.rc;
	auto centerX = _isLeft ? rc.Width() - cut.center.x : cut.center.x;
	auto c = _camera.GetOffset();
	auto pos = _pos - c;
	DrawRectRotaGraph2(static_cast<int>(pos.x), static_cast<int>(pos.y), rc.Left(), rc.Top(), rc.Width(), rc.Height(), centerX, cut.center.y, 3.0f, _angle, _imgH, true, _isLeft);
}

void Ant::OnGround(float grad, float adjustY)
{
}

void Ant::OnDead()
{
}

Vector2f Ant::GetVelocity() const
{
	return Vector2f();
}

Vector2f Ant::GetAccel() const
{
	return Vector2f();
}

const Rect & Ant::GetCollider()
{
	auto& actInfo = _actionData.actInfo[_currentAct];
	auto& cut = actInfo.cuts[0];
	_rect = GetRect(cut.actrects[0].rc);
	return _rect;
}

void Ant::PushBack(float x, float y)
{
}

void Ant::SetVelocity(const Vector2f & v)
{
}

void Ant::SetAccel(const Vector2f & a)
{
}
