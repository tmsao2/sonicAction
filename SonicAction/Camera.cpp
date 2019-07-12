#include "Camera.h"
#include "Game/Player.h"


Vector2f Camera::GetAvgPosition() const
{
	Vector2f pos(0, 0);
	for (auto p : _players) {
		pos += p->GetPosition();
	}
	pos /= static_cast<float>(_players.size());
	return pos;
}

void Camera::SubmitPos()
{
	_initPos = GetAvgPosition();
	_pos = _initPos;
}

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::AddPlayer(std::shared_ptr<Player> player)
{
	_players.emplace_back(player);
	SubmitPos();
}

void Camera::RemovePlayer(std::shared_ptr<Player> player)
{
	auto itr = _players.begin();
	for (auto p : _players)
	{
		if (p == player)
		{
			_players.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void Camera::SetRange(Size & stageSize)
{
	_viewRange = Rect(static_cast<int>(_pos.x), static_cast<int>(_pos.y), stageSize.w, stageSize.h);
}

void Camera::Update()
{
	if (!_players.empty())
	{
		_pos = GetAvgPosition();
	}
	_pos.x = max(_pos.x, _initPos.x);
	//_pos.y = min(_pos.y, _initPos.y);
}

const Vector2f& Camera::GetPosition() const
{
	return _pos;
}

const Vector2f  Camera::GetOffset() const
{
	return _pos - _initPos;
}

const Rect & Camera::GetViewRange() const
{
	return _viewRange;
}
