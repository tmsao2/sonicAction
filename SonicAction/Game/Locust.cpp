#include "Locust.h"
#include "../Camera.h"
#include "../Game.h"
#include "../System/FileSystem.h"
#include "../System/ImageLoader.h"
#include "Player.h"


constexpr int jump_frame = 60;

Locust::Locust(const Camera & camera, const Player & player, int x, int y, EventQueue& e) :Enemy(camera, player, Vector2f(x, y),e)
{
	LoadAction("action/locust.act");
	auto sign = player.GetPosition().x - x;
	sign = sign / abs(sign);
	_vel.x = sign;
	_pos = Vector2f(x, y);
	_angle = 0;
	_isLeft = true;
	_isReverse = false;
	_isAerial = false;
	ChangeAction("idle");
	_updater = &Locust::NormalUpdate; 
}

void Locust::Jump()
{
	_vel.y -= 12.0f;
	_jumpCnt = 0;
	_isAerial = true;
	ChangeAction("jump");
	_updater = &Locust::JumpUpdate;
}

void Locust::NormalUpdate()
{
	_vel += _accel;
	auto sign = _player.GetPosition().x - _pos.x;
	if (abs(sign) > 50)
	{
		sign = sign / abs(sign);
		_isLeft = sign > 0 ? true : false;
		_vel.x = sign;
	}
	if (++_jumpCnt > jump_frame)
	{
		Jump();
	}
}

void Locust::JumpUpdate()
{
	if (!_isAerial)
	{
		ChangeAction("idle");
		_updater = &Locust::NormalUpdate;
	}
	auto sign = _player.GetPosition().x - _pos.x;
	if (abs(sign) > 50)
	{
		sign = sign / abs(sign);
		_isLeft = sign > 0 ? true : false;
		_vel.x = sign;
	}
}

void Locust::DyingUpdate()
{
	_vel += _accel;
	auto h = Game::GetInstance().GetConfig().GetScreenSize().h;

	if (_pos.y - 200 - _camera.GetOffset().y > h) {
		_updater = &Locust::DieUpdate;
	}
}

void Locust::DieUpdate()
{
}

std::shared_ptr<Enemy> Locust::MakeClone()
{
	return std::make_shared<Locust>(*this);
}


Locust::~Locust()
{
}

void Locust::Update(const Input & input)
{
	_pos += _vel;
	auto g = Game::GetInstance().GetGravity();
	_vel.y += g;
	AdvanceAnimetion();
	(this->*_updater)();
}

void Locust::Draw()
{
	auto& actInfo = _actionSet->actInfo[_currentAct];
	auto& cut = actInfo.cuts[_nowidx];
	auto rc = cut.rc;
	auto centerX = _isLeft ? rc.Width() - cut.center.x : cut.center.x;
	auto c = _camera.GetOffset();
	auto pos = _pos - c;
	DrawRectRotaGraph2(static_cast<int>(pos.x), static_cast<int>(pos.y), rc.Left(), rc.Top(), rc.Width(), rc.Height(), centerX, cut.center.y, 3.0f, _angle, _imgH, true, _isLeft, _isReverse);

}

void Locust::OnGround(float grad, float adjustY)
{
	if (adjustY == INT_MIN)
	{
		return;
	}
	if (_pos.y > adjustY)
	{
		_vel.y = 0;
		_pos.y = adjustY;
		_isAerial = false;
		_angle = atanf(grad);
	}
}

void Locust::OnDead()
{
	if (IsDie() || IsDying())return;
	_angle = 0.0f;
	_vel.x = 0.0f;
	_vel.y = -5.0f;
	_accel.x = 0.0f;
	_accel.y = 0.1f;
	_isReverse = true;
	_updater = &Locust::DyingUpdate;
}

bool Locust::IsDie()
{
	return _updater == &Locust::DieUpdate;
}

bool Locust::IsDying()
{
	return _updater == &Locust::DyingUpdate;
}

Vector2f Locust::GetVelocity() const
{
	return _vel;
}

void Locust::SetVelocity(const Vector2f & v)
{

}

Vector2f Locust::GetAccel() const
{
	return _accel;
}

void Locust::SetAccel(const Vector2f & a)
{
}

Vector2f Locust::GetPosition() const
{
	return _pos;
}

void Locust::PushBack(float x, float y)
{
	_pos.x += x;
	_pos.y += y;
}
