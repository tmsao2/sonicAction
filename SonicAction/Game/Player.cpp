#include "Player.h"
#include "../Input.h"
#include "../Camera.h"
#include "../Game.h"

constexpr float max_speed = 30.0f;
constexpr float jump_power = 3.0f;

Player::Player(const Camera & c):Actor(c)
{
	_imgH = LoadGraph("image/atlas.png");
	_isLeft = false;
}

Player::Player(const Camera & c, const Vector2f p) :Actor(c,p)
{
	_imgH = LoadGraph("image/atlas.png");
	_pos = p;
	_isLeft = false;
}

Player::Player(const Camera & c, float x, float y):Actor(c,x,y)
{
	ReadActFile("action/player.act");
	_imgH = LoadGraph(_actionData.imgFilePath.c_str());
	_jumpSE = LoadSoundMem("se/jump.wav");
	_deadSE = LoadSoundMem("se/down.wav");
	_pos = Vector2f(x, y);
	_jumpframe = 0;
	_isAerial = true;
	_isLeft = false;
	_angle = 0.0f;
	_updater = &Player::NeutralUpdate;
	ChangeAction("idle");
}


Player::~Player()
{
}

bool Player::IsAerial()
{
	return _isAerial;
}

bool Player::IsDie()
{
	return _updater==&Player::DieUpdate;
}

bool Player::IsDying()
{
	return _updater == &Player::DyingUpdate;
}

void Player::HitBlock(int block)
{
	if (_vel.y < 0)
	{
		_vel.y = 0;
		_pos.y = _rect.size.h + block;
	}
}

void Player::OnGround(int groundline, float grad)
{
	if (groundline == INT_MIN)
	{
		return;
	}
	if (_pos.y > groundline)
	{
		_vel.y = 0;
		_pos.y = groundline;
		_angle = atanf(grad);
    	_isAerial = false;
	}
}

void Player::OnDead()
{
	if (IsDie()||IsDying())return;
	_angle = 0.0f;
	_vel.x = 0.0f;
	_vel.y = -12.0f;
	_accel.x = 0.0f;
	_accel.y = 0.1f;
	PlaySoundMem(_deadSE, DX_PLAYTYPE_BACK);
	ChangeAction("damage");
	_updater = &Player::DyingUpdate;
}

void Player::PushBack(float x, float y)
{
	_pos.x += x;
	_pos.y += y;
}

void Player::Update(const Input & input)
{
	AdvanceAnimetion();
	(this->*_updater)(input);
	Accelerator(input);
	_pos += _vel;
}

void Player::Draw()
{
	auto& actInfo = _actionData.actInfo[_currentAct];
	auto& cut = actInfo.cuts[_nowidx];
	auto rc = cut.rc;
	auto centerX = _isLeft ? rc.Width() - cut.center.x : cut.center.x;
	auto c = _camera.GetOffset();
	auto pos = _pos - c;
	DrawRectRotaGraph2(static_cast<int>(pos.x), static_cast<int>(pos.y), rc.Left(), rc.Top(), rc.Width(), rc.Height(),centerX,cut.center.y, 3.0f, _angle, _imgH, true, _isLeft);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	_rect = GetRect(rc);
	DrawBox(_rect.Left()-c.x, _rect.Top()-c.y, _rect.Right()-c.x, _rect.Bottom()-c.y, 0xff0000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

Vector2f Player::GetPosition() const
{
	return _pos;
}

Vector2f Player::GetVelocity() const
{
	return _vel;
}


bool Player::Move(const Input & input)
{
	if (input.IsPressed(0, COMMAND::RIGHT))
	{
		_isLeft = false;
		_accel.x = 0.1f;
	}
	else if (input.IsPressed(0, COMMAND::LEFT))
	{
		_isLeft = true;
		_accel.x = -0.1f;
	}
	else
	{
		return false;
	}
	return true;
}

void Player::Neutral()
{
	_accel.x = 0;
	_updater = &Player::NeutralUpdate;
	ChangeAction("idle");
}

void Player::Run()
{
	ChangeAction("run");
	_updater = &Player::RunUpdate;
}

void Player::Jump()
{
	_vel.y -= jump_power;
	_isAerial = true;
	++_jumpframe;
	ChangeAction("jump");
	PlaySoundMem(_jumpSE, DX_PLAYTYPE_BACK);
	_updater = &Player::JumpUpdate;
}

void Player::Accelerator(const Input & input)
{
	auto g = Game::GetInstance().GetGravity();
	auto sin = sinf(_angle);

	_vel += _accel;
	_vel.x += g * sin;
	_vel.y += g;
	if (fabsf(_vel.x) > max_speed)
	{
		_vel.x = _isLeft ? -max_speed : max_speed;
	}
	if (!input.IsPressed(0, COMMAND::RIGHT) &&
		!input.IsPressed(0, COMMAND::LEFT)||
		(_vel.x*_accel.x < 0))
	{
		_vel.x *= 0.95f;
	}
}

void Player::NeutralUpdate(const Input & input)
{
	if (Move(input))
	{
		Run();
	}
	if (input.IsTriggered(0, COMMAND::JUMP))
	{
		Jump();
	}
}

void Player::RunUpdate(const Input & input)
{
	if (!Move(input))
	{
		Neutral();
	}
	if (input.IsTriggered(0, COMMAND::JUMP))
	{
		Jump();
	}
}

void Player::JumpUpdate(const Input & input)
{
	_angle += _isLeft ? -0.4f : 0.4f;
	if (_jumpframe > 0)
	{
		if (input.IsPressed(0, COMMAND::JUMP))
		{
			++_jumpframe;
		}
		if (input.IsReleased(0, COMMAND::JUMP) || _jumpframe >= 5)
		{
			_vel.y = -jump_power * static_cast<float>(_jumpframe);
			_jumpframe = 0;
		}
	}
	if (!_isAerial)
	{
		_angle = 0;
		Neutral();
	}
	Move(input);
}

void Player::AttackUpdate(const Input & input)
{
	if (input.IsTriggered(0, COMMAND::ATTACK))
	{
		DrawString(static_cast<int>(_pos.x), static_cast<int>(_pos.y), "attack", 0xffffff);
	}
}

void Player::DyingUpdate(const Input & input)
{
	_vel += _accel;
	auto h = Game::GetInstance().GetConfig().GetScreenSize().h;

	if (_pos.y-200-_camera.GetOffset().y>h) {
		_updater = &Player::DieUpdate;
	}
}

void Player::DieUpdate(const Input & input)
{
}
