#include "Ant.h"
#include "../Camera.h"
#include "../Game.h"
#include "../System/FileSystem.h"
#include "../System/ImageLoader.h"
#include "Player.h"

Ant::Ant(const Camera& camera, const Player& player,int x,int y):Enemy(camera,player,Vector2f(x,y))
{
	ReadActFile("action/ant.act");
	ImageData data;
	Game::GetInstance().GetFileSystem()->Load(_actionSet->imgFilePath.c_str(), data);
	_imgH = data.GetHandle();	auto sign = player.GetPosition().x - x;
	sign = sign / abs(sign);
	_vel.x = sign;
	_pos = Vector2f(x, y);
	_angle = 0;
	_isLeft = true;
	ChangeAction("idle");
	_updater = &Ant::NormalUpdate;
}

Ant::~Ant()
{
}

void Ant::NormalUpdate()
{
	auto g = Game::GetInstance().GetGravity();
	_vel.y += g;
	auto sign = _player.GetPosition().x - _pos.x;
	if (abs(sign) > 50)
	{
		sign = sign / abs(sign);
		_isLeft = sign > 0 ? true : false;
		_vel.x = sign;
	}
}

void Ant::DeadUpdate()
{
}

void Ant::Update(const Input & input)
{
	_pos += _vel;
	AdvanceAnimetion();
	(this->*_updater)();
}

void Ant::Draw()
{
	auto& actInfo = _actionSet->actInfo[_currentAct];
	auto& cut = actInfo.cuts[_nowidx];
	auto rc = cut.rc;
	auto centerX = _isLeft ? rc.Width() - cut.center.x : cut.center.x;
	auto c = _camera.GetOffset();
	auto pos = _pos - c;
	DrawRectRotaGraph2(static_cast<int>(pos.x), static_cast<int>(pos.y), rc.Left(), rc.Top(), rc.Width(), rc.Height(), centerX, cut.center.y, 3.0f, _angle, _imgH, true, _isLeft);

}

void Ant::OnGround(float grad, float adjustY)
{
	if (adjustY == INT_MIN)
	{
		return;
	}
	if (_pos.y > adjustY)
	{
		_vel.y = 0;
		_pos.y = adjustY;
		_angle = atanf(grad);
	}
}

void Ant::OnDead()
{
}

Vector2f Ant::GetVelocity() const
{
	return _vel;
}

Vector2f Ant::GetAccel() const
{
	return Vector2f();
}

const Rect & Ant::GetCollider()
{
	auto& actInfo = _actionSet->actInfo[_currentAct];
	auto& cut = actInfo.cuts[0];
	_rect = GetRect(cut.actrects[0].rc);
	return _rect;
}

Vector2f Ant::GetPosition() const
{
	return _pos;
}

void Ant::PushBack(float x, float y)
{
	_pos.x += x;
	_pos.y += y;
}

void Ant::SetVelocity(const Vector2f & v)
{
}

void Ant::SetAccel(const Vector2f & a)
{
}
