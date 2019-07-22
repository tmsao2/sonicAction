#include "BackGround.h"
#include "../Camera.h"
#include "../Game.h"
#include <DxLib.h>


BackGround::BackGround(const Camera& c) :_camera(c)
{
}


BackGround::~BackGround()
{
}

void BackGround::AddParts(const char * filepath, const Vector2f & pos, float rate, bool fromBottom, LayoutType type, Size size, int repeatX)
{
	auto& wsize = Game::GetInstance().GetConfig().GetScreenSize();
	auto handle = LoadGraph(filepath);
	int w, h;
	GetGraphSize(handle, &w, &h);
	float scale = 1.0f;
	if (size.w > 0) {
		scale = static_cast<float>(size.w) / static_cast<float>(w);
		w = size.w;
	}
	if (size.h > 0) {
		h = size.h;
	}
	else {
		h *= scale;
	}
	if (repeatX == -1) {
		repeatX = w;
	}
	auto p = pos;
	if (fromBottom) {
		p.y = wsize.h - pos.y - h;
	}
	_bgparts.emplace_back(handle, p, rate, type, repeatX, Size(w, h));
}


void BackGround::Update()
{
}

void BackGround::DrawBg()
{
	auto wsize = Game::GetInstance().GetConfig().GetScreenSize();
	auto offset = _camera.GetOffset();
	for (auto parts : _bgparts) {
		int w, h;
		int cnt;
		auto pos = Vector2f(0, 0);
		if (parts.type == LayoutType::repeat) {
			auto poffset = offset * parts.rate;
			pos = parts.initpos - Vector2f(static_cast<int>(poffset.x) % parts.repeatX, poffset.y);
			cnt = (wsize.w / parts.size.w) + 1;
		}
		else {
			auto poffset = offset * parts.rate;
			pos = parts.initpos - Vector2f(poffset.x, poffset.y);
			cnt = 1;
		}
		for (int i = 0; i < cnt; ++i) {
			DrawExtendGraph(pos.x, pos.y,
				pos.x + parts.size.w, pos.y + parts.size.h, 
				parts.handle, true);
			DrawExtendGraph(pos.x + parts.repeatX,pos.y, 
				pos.x + parts.repeatX + parts.size.w, pos.y + parts.size.h,
				parts.handle, true);
		}
	}
}

