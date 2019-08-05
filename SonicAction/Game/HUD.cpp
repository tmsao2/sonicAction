#include "HUD.h"
#include "Event.h"
#include "../System/ImageLoader.h"
#include "../System/FileSystem.h"
#include "../Game.h"

HUD::HUD()
{
	ImageData data;
	Game::GetInstance().GetFileSystem()->Load("img/atlas.png", data);
	_coinH = data.GetHandle();
}


HUD::~HUD()
{
}

void HUD::Draw()
{
	DrawRectGraph(50, 50, 16, 0, 10, 16, _coinH, true);
	DrawFormatString(70, 50, 0xffffff, " × %d", _coinNum);
	DrawFormatString(70, 80, 0xffffff, "スコア　%d", _score);
}

void HUD::Update()
{
}

bool HUD::OnNotify(Event* e)
{
	if (e->GetEventType() == EventType::coin)
	{
		++_coinNum;
		return true;
	}
	else if(e->GetEventType() == EventType::score)
	{
		_score += e->GetScore();
		return true;
	}
	return false;
}
