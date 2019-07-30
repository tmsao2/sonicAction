#include "Coin.h"
#include "../System/FileSystem.h"
#include "../System/ImageLoader.h"
#include "../Camera.h"
#include "../Game.h"


Coin::Coin(const Vector2 & pos, const Camera & c):Event(Rect(pos,Size(32,32)),c)
{
	ImageData data;
	Game::GetInstance().GetFileSystem()->Load("img/atlas.png", data);
	_imgH = data.GetHandle();
}

Coin::~Coin()
{
}

void Coin::Draw()
{
	auto range = _camera.GetViewRange();
	if (_rect.Right() < range.Left() || _rect.Left() > range.Right())
	{
		return;
	}
	auto c = _camera.GetOffset();
	DrawRectExtendGraph(
		_rect.Left() - c.x,
		_rect.Top() - c.y,
		_rect.Right() - c.x,
		_rect.Bottom() - c.y,
		16, 0, 16, 16, _imgH, true);
}

void Coin::Update()
{
}

EventType Coin::GetEventType() const
{
	return EventType::coin;
}
