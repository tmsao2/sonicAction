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

	//�o�[�W�����ǂݍ���
	float version = 0.0f;
	FileRead_read(&version, sizeof(version), actionH);
	assert(version == 1.01f);

	//�t�@�C�����̃T�C�Y
	int filenamesize = 0;
	FileRead_read(&filenamesize, sizeof(filenamesize), actionH);

	//�t�@�C����
	std::string imgfilepath;
	imgfilepath.resize(filenamesize);
	FileRead_read(&imgfilepath[0], filenamesize, actionH);

	//���̃A�v���P�[�V��������̑��΃p�X�ɕϊ�
	auto ipos = imgfilepath.find_first_of("/") + 1;
	_actionData.imgFilePath = imgfilepath.substr(ipos,imgfilepath.size());

	//�A�N�V������
	int actionCnt = 0;
	FileRead_read(&actionCnt, sizeof(actionCnt), actionH);

	for (int idx = 0; idx < actionCnt; ++idx) 
	{
		//�A�N�V�������̐�
		int actnamesize = 0;
		FileRead_read(&actnamesize, sizeof(actnamesize), actionH);

		//�A�N�V������
		std::string actname;
		actname.resize(actnamesize);
		FileRead_read(&actname[0], actnamesize, actionH);

		ActionInfo actInfo;

		//���[�v���
		FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), actionH);

		//�J�b�g��
		int cutCnt = 0;
		FileRead_read(&cutCnt, sizeof(cutCnt), actionH);

		//�J�b�g�f�[�^
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
		_actionData.actInfo[actname] = actInfo;
	}


	FileRead_close(actionH);
}

bool Actor::AdvanceAnimetion()
{
	if ((signed)_frame < _actionData.actInfo[_currentAct].cuts[_nowidx].duration) {
		_frame++;
	}
	else {
		_frame = 0;
		if (_nowidx < (signed)_actionData.actInfo[_currentAct].cuts.size() - 1) {
			++_nowidx;
		}
		else {
			if (_actionData.actInfo[_currentAct].isLoop) {
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
}

Actor::Actor(const Camera & c, const Vector2f p) : _camera(c),_pos(p)
{
}

Actor::Actor(const Camera & c, float x, float y) : _camera(c),_pos(x,y)
{
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

const Rect& Actor::GetCollider()
{
	auto& actInfo = _actionData.actInfo[_currentAct];
	auto& cut = actInfo.cuts[0];
	_rect=GetRect(cut.actrects[0].rc);
	return _rect;
}

void Actor::DebagDraw()
{
	auto& actInfo = _actionData.actInfo[_currentAct];
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
