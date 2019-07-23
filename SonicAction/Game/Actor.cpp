#include "Actor.h"
#include "../Camera.h"
#include "../Collider.h"
#include <assert.h>


void Actor::ChangeAction(const char* act)
{
	_frame = 0;
	_nowidx = 0;
	_currentAct = act;
}

void Actor::ReadActFile(const char * filepath)
{
	int actionH = FileRead_open(filepath);

	//バージョン読み込み
	float version = 0.0f;
	FileRead_read(&version, sizeof(version), actionH);
	assert(version == 1.01f);

	//ファイル名のサイズ
	int filenamesize = 0;
	FileRead_read(&filenamesize, sizeof(filenamesize), actionH);

	//ファイル名
	std::string imgfilepath;
	imgfilepath.resize(filenamesize);
	FileRead_read(&imgfilepath[0], filenamesize, actionH);

	//このアプリケーションからの相対パスに変換
	auto ipos = imgfilepath.find_first_of("/") + 1;
	_actionSet->imgFilePath = imgfilepath.substr(ipos,imgfilepath.size());

	//アクション数
	int actionCnt = 0;
	FileRead_read(&actionCnt, sizeof(actionCnt), actionH);

	for (int idx = 0; idx < actionCnt; ++idx) 
	{
		//アクション名の数
		int actnamesize = 0;
		FileRead_read(&actnamesize, sizeof(actnamesize), actionH);

		//アクション名
		std::string actname;
		actname.resize(actnamesize);
		FileRead_read(&actname[0], actnamesize, actionH);

		ActionInfo actInfo;

		//ループ情報
		FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), actionH);

		//カット数
		int cutCnt = 0;
		FileRead_read(&cutCnt, sizeof(cutCnt), actionH);

		//カットデータ
		actInfo.cuts.resize(cutCnt);
		for (int i = 0; i < cutCnt; ++i)
		{
			FileRead_read(&actInfo.cuts[i], sizeof(actInfo.cuts[i]) - sizeof(actInfo.cuts[i].actrects), actionH);

			int actrcCnt = 0;
			FileRead_read(&actrcCnt, sizeof(actrcCnt), actionH);

			if (actrcCnt > 0)
			{
				actInfo.cuts[i].actrects.resize(actrcCnt);
				for (auto& actrect : actInfo.cuts[i].actrects)
				{
					FileRead_read(&actrect, sizeof(actrect), actionH);
				}
			}
		}
		_actionSet->actInfo[actname] = actInfo;
	}


	FileRead_close(actionH);
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
	_actionSet = std::make_unique<ActionSet>();
}

Actor::Actor(const Camera & c, const Vector2f p) : _camera(c),_pos(p)
{
	_actionSet = std::make_unique<ActionSet>();
}

Actor::Actor(const Camera & c, float x, float y) : _camera(c),_pos(x,y)
{
	_actionSet = std::make_unique<ActionSet>();
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
