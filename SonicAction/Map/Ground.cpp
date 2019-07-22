#include "Ground.h"
#include "../Camera.h"
#include "../Game.h"
#include "../Game/Actor.h"
#include <algorithm>
#include <DxLib.h>


Ground::Ground(const Camera& c) :_camera(c)
{
	_imgH = LoadGraph("img/atlas0.png");
	_lavaH = LoadGraph("img/lava.png");
	_lava2H = LoadGraph("img/lava2.png");
}

Ground::~Ground()
{
}

void Ground::DrawBottomGround(const Vector2f& s_pos, const Vector2f& e_pos, EdgeType t)
{
	int cutX;
	switch (t)
	{
	case EdgeType::none:
		cutX = 64;
		break;
	case EdgeType::left:
		cutX = 32;
		break;
	case EdgeType::right:
		cutX = 96;
		break;
	default:
		break;
	}
	DrawRectModiGraph(s_pos.x, s_pos.y, e_pos.x, e_pos.y,
		e_pos.x, e_pos.y + 64, s_pos.x, s_pos.y + 64,
		cutX, 32, 32, 32, _imgH, true);

	float yposmax = max(s_pos.y, e_pos.y);

	DrawRectModiGraph(s_pos.x, s_pos.y + 64, e_pos.x, e_pos.y + 64,
		e_pos.x, yposmax + 64 + 64, s_pos.x, yposmax + 64 + 64,
		cutX, 64, 32, 32, _imgH, true);

	yposmax += 128;

	while (yposmax < 640)
	{
		DrawRectExtendGraph(s_pos.x, yposmax - 1,
			e_pos.x, yposmax + 64, cutX, 64, 32, 32, _imgH, true);
		yposmax += 64;
	}
}

void Ground::Draw()
{
	auto c = _camera.GetOffset();
	auto wsize = Game::GetInstance().GetConfig().GetScreenSize();
	for (auto& tera : _terrain)
	{
		int cnt = (int)(tera.seg.end.x - tera.seg.start.x) / 64;
		int mod = (int)(tera.seg.end.x - tera.seg.start.x) % 64;
		float grad = (tera.seg.end.y - tera.seg.start.y) / (tera.seg.end.x - tera.seg.start.x);

		auto sPos = tera.seg.start - c;
		auto ePos = tera.seg.end - c;
		
		for (int i = 0; i < cnt; ++i)
		{
			int w = 64;
			if (i == cnt - 1 && mod > 0)
			{
				w = mod + w;
			}
			Vector2f posa(sPos.x + i * 64, sPos.y + grad * i * 64 );
			Vector2f posb(sPos.x + i * 64 + w, sPos.y + grad * (i * 64 + w));
			auto type = tera.type;

			if ((posa.x < 0 && posb.x < 0) || (posa.x > wsize.w && posb.x > wsize.w))
			{
				continue;
			}
			if (i == 0 && type == EdgeType::left)
			{
				type = EdgeType::left;
			}
			else if (mod == 0 && i == cnt - 1 && type == EdgeType::right)
			{
				type = EdgeType::right;
			}
			else
			{
				type = EdgeType::none;
			}
			DrawBottomGround(posa, posb, type);
		}
		auto type = tera.type;

		Vector2f posa(sPos.x + cnt * 64, sPos.y + grad * cnt * 64);
		Vector2f posb(sPos.x + cnt * 64 + mod, sPos.y + grad * (cnt * 64 + mod));

		DrawBottomGround(posa, posb,type==EdgeType::right?tera.type:EdgeType::none);
	}

	int w, h;
	GetGraphSize(_lavaH, &w, &h);
	auto y = GetDeadLine() - c.y;
	if (y < wsize.h)
	{
		int x = 0;
		while (x < wsize.w)
		{
			DrawGraph(x, y - 168, _lavaH, true);
			DrawGraph(x, y - 168 + h, _lava2H, true);
			x += w;
		}
	}
#ifdef _DEBUG
	auto fps = GetFPS();
	auto drawCallCnt = GetDrawCallCount();
	DrawFormatString(12, 18, 0xffffff, "FPS=%f",fps);
	DrawFormatString(12, 38, 0xffffff, "DC=%d",drawCallCnt);
#endif // _DEBUG

}

int Ground::GetGroundY(Actor* actor,float& grad)const
{
	auto pos = actor->GetPosition();


	auto lambda= [pos](const Terrain& s) {
		return s.seg.start.x <= pos.x && pos.x <= s.seg.end.x;
	};

	auto it = std::find_if(_terrain.begin(), _terrain.end(), lambda);

	if (it == _terrain.end())return INT_MIN;

	float y = 0;
	do
	{
		grad = (it->seg.end.y - it->seg.start.y) / (it->seg.end.x - it->seg.start.x);
		y = it->seg.start.y + grad * (pos.x - it->seg.start.x);

		if (y >= pos.y - 30) break;

		it = std::find_if(it + 1, _terrain.end(), lambda);
	} while (it!=_terrain.end());

	if (it == _terrain.end())return INT_MIN;

	if (fabsf(pos.x - it->seg.start.x) < 4.0f)
	{
		if (it - 1 == _terrain.begin())return y;
		float t = fabsf(pos.x - it->seg.start.x) / 4.0f;
		auto& prv = *(it - 1);
		auto grad2 = (prv.seg.end.y - prv.seg.start.y) / (prv.seg.end.x - prv.seg.start.x);
		grad = grad * t + (1.0f - t)*(grad2 + grad) / 2;
	}
	else if (fabsf(pos.x - it->seg.end.x) < 4.0f)
	{
		if (it + 1 == _terrain.end())return y;
		float t = fabsf(pos.x - it->seg.end.x) / 4.0f;
		auto& next = *(it + 1);
		auto grad2 = (next.seg.end.y - next.seg.start.y) / (next.seg.end.x - next.seg.start.x);
		grad = grad * t + (1.0f - t)*(grad2 + grad) / 2;
	}

	return y;
}

int Ground::GetDeadLine() const
{
	return 1500;
}

void Ground::AddSegment(const Segment & seg, EdgeType t)
{
	_terrain.emplace_back(t,seg);
}

void Ground::AddSegment(const Vector2f & posA, const Vector2f & posB, EdgeType t)
{
	_terrain.emplace_back(t,posA, posB);
}
