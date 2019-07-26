#include "Actor.h"
#include "../Game.h"
#include "../Camera.h"
#include "../Collider.h"
#include "../System/FileSystem.h"
#include "../System/ImageLoader.h"
#include <assert.h>


void Actor::ChangeAction(const char* act)
{
	_frame = 0;
	_nowidx = 0;
	_currentAct = act;
}

void Actor::LoadAction(const char* filepath)
{
	ActionData act;
	Game::GetInstance().GetFileSystem()->Load(filepath, act);
	auto actdata = act.GetRawData();
	std::string imgFilePath = "";
	ActionData::BuildActionSet(act, *_actionSet, imgFilePath);
	ImageData data;
	Game::GetInstance().GetFileSystem()->Load(imgFilePath.c_str(), data);
	_imgH = data.GetHandle();
}

bool Actor::AdvanceAnimetion()
{
	if ((signed)_frame < _actionSet->actInfo[_currentAct].cuts[_nowidx].duration) {
		_frame++;
	}
	else {
		_frame = 0;
		if (_nowidx < (signed)_actionSet->actInfo[_currentAct].cuts.size() - 1) {
			++_nowidx;
		}
		else {
			if (_actionSet->actInfo[_currentAct].isLoop) {
				_nowidx = 0;
			}
			else
			{
				return true;
			}
		}
	}
	return false;
}

Actor::Actor(const Camera& c):_camera(c)
{
	_actionSet = std::make_shared<ActionSet>();
}

Actor::Actor(const Camera & c, const Vector2f p) : _camera(c),_pos(p)
{
	_actionSet = std::make_shared<ActionSet>();
}

Actor::Actor(const Camera & c, float x, float y) : _camera(c),_pos(x,y)
{
	_actionSet = std::make_shared<ActionSet>();
}

const Rect Actor::GetRect(const Rect& rec) const
{
	Rect rc = rec;
	rc.size.w *= 3;
	rc.size.h *= 3;
	auto offset = _isLeft ? rc.size.w : rc.size.w / 2;

	rc.center.x = rc.center.x + _pos.x;
	rc.center.y = rc.center.y + _pos.y-rc.size.h/4;
	return rc;
}

const Rect & Actor::GetCollider()
{
	auto& actInfo = _actionSet->actInfo[_currentAct];
	auto& cut = actInfo.cuts[0];
	_rect = GetRect(cut.actrects[0].rc);
	return _rect;
}

void Actor::DebagDraw()
{
	auto& actInfo = _actionSet->actInfo[_currentAct];
	auto& cut = actInfo.cuts[0];

	auto c = _camera.GetOffset();

	for (ActionRect& act : cut.actrects) {
		Rect rc = GetRect(act.rc);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(rc.Left()-c.x, rc.Top() - c.y, rc.Right()-c.x, rc.Bottom() - c.y, 0xff0000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawBox(rc.Left() - c.x, rc.Top() - c.y, rc.Right() - c.x, rc.Bottom() - c.y, 0xff0000, false);
	}
}

Actor::~Actor()
{
}
