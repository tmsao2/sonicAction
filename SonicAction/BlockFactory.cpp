#include "BlockFactory.h"
#include "Collider.h"
#include "Game/Actor.h"
#include "Game.h"
#include "Camera.h"
#include <DxLib.h>

int _blockH = -1;
constexpr int fixed_block = 5;
constexpr int block_size = 32;
constexpr int move_frame = 120;

class Brick :public Block{
public:
	Brick(const Vector2& pos,const Camera& c) :Block(Rect(pos, Size(block_size, block_size)),c) {
		_blockH = LoadGraph("img/blocks.png");
	}

	void Update()override 
	{

	}

	void Draw()override 
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
			16, 0, 16, 16, _blockH, true);
	}

	void OnCollision(Actor* actor, const Rect& rc)override 
	{
		auto vel = actor->GetVelocity();
		auto accel = actor->GetAccel();
		auto sz = Size(0, 0);
		if (rc.Height() <= rc.Width())
		{
			if (rc.center.y < 0)
			{
				actor->OnGround(0);
				accel.x = 0;
			}
			if (rc.center.y == 0)return;
			vel.y = 0;
			accel.y = 0;
			sz.h = rc.Height()*(rc.center.y / abs(rc.center.y));
		}
		else
		{
			if (rc.center.x == 0)return;
			sz.w = rc.Width()*(rc.center.x / abs(rc.center.x));
			vel.x = 0;
			accel.x = 0;
		}
		actor->SetVelocity(vel);
		actor->SetAccel(accel);
		actor->PushBack(sz.w, sz.h);
	}

};

class Slide :public Block {
private:
	int _speed;
	int _frame = 0;
public:
	Slide(const Vector2& pos, const Camera& cam, unsigned int runLength = 1) :
		Block(Rect(pos, Size(block_size* fixed_block, block_size)), cam), _speed((int)runLength) {
		_blockH = LoadGraph("img/blocks.png");
	}

	void Update()override
	{
		auto cnt = ++_frame%move_frame;
		if (cnt == 0)
		{
			_speed = _speed > 0 ? -_speed : -1*_speed;
		}
		_rect.center.x += _speed;
	}

	void Draw()override
	{
		auto c = _camera.GetOffset();
		for (int i = 0; i < fixed_block; ++i)
		{
			auto range = _camera.GetViewRange();
			if (_rect.Right() - _rect.Width() / fixed_block * (fixed_block - (i + 1)) < range.Left()
				|| _rect.Left() + _rect.Width() / fixed_block * i > range.Right())
			{
				continue;
			}
			DrawRectExtendGraph(
				_rect.Left() + _rect.Width() / fixed_block * i - c.x,
				_rect.Top() - c.y,
				_rect.Right()-_rect.Width()/ fixed_block * (fixed_block - (i+1)) - c.x,
				_rect.Bottom() - c.y,
				0, 16 * 7, 16, 16, _blockH, true);
		}
	}

	void OnCollision(Actor* actor, const Rect& rc)override
	{
		auto vel = actor->GetVelocity();
		auto accel = actor->GetAccel();
		auto sz = Size(0, 0);
		if (rc.Height() < rc.Width())
		{
			if (rc.center.y < 0)
			{
				actor->OnGround(0);
				actor->PushBack(_speed, 0);
			}
			if (rc.center.y == 0)return;
			vel.y = 0;
			accel.y = 0;
			sz.h = rc.Height()*(rc.center.y / abs(rc.center.y));
		}
		else
		{
			if (rc.center.x == 0)return;
			sz.w = rc.Width()*(rc.center.x / abs(rc.center.x));
			vel.x = 0;
			accel.x = 0;
		}
		actor->SetVelocity(vel);
		actor->SetAccel(accel);
		actor->PushBack(sz.w, sz.h);
	}
		
};

class Lift :public Block {
private:
	int _speed;
	int _frame=0;
public:
	Lift(const Vector2& pos, const Camera& cam, unsigned int runLength = 1) :
		Block(Rect(pos, Size(block_size*fixed_block, block_size)), cam), _speed((int)runLength) {
		_blockH = LoadGraph("img/blocks.png");
	}

	void Update()override
	{
		auto cnt = ++_frame%move_frame;
		if (cnt == 0)
		{
			_speed = _speed > 0 ? -_speed : -1 * _speed;
		}
		_rect.center.y += _speed;
	}

	void Draw()override
	{
		auto c = _camera.GetOffset();
		for (int i = 0; i < fixed_block; ++i)
		{
			auto range = _camera.GetViewRange();
			if (_rect.Right() - _rect.Width() / fixed_block * (fixed_block - (i + 1)) < range.Left()
				|| _rect.Left() + _rect.Width() / fixed_block * i > range.Right())
			{
				continue;
			}
			DrawRectExtendGraph(
				_rect.Left() + _rect.Width() / fixed_block * i - c.x,
				_rect.Top() - c.y,
				_rect.Right() - _rect.Width() / fixed_block * (fixed_block - (i + 1)) - c.x,
				_rect.Bottom() - c.y,
				0, 16 * 7, 16, 16, _blockH, true);
		}
	}

	void OnCollision(Actor* actor, const Rect& rc)override
	{
		auto vel = actor->GetVelocity();
		auto accel = actor->GetAccel();
		auto sz = Size(0, 0);

		if (rc.Height() < rc.Width())
		{
			if (rc.center.y < 0)
			{
				actor->OnGround(0);
				actor->PushBack(0, _speed);
			}
			if (rc.center.y == 0)return;
			vel.y = 0;
			accel.y = 0;
			sz.h = rc.Height()*(rc.center.y / abs(rc.center.y));
		}
		else
		{
			if (rc.center.x == 0)return;
			sz.w = rc.Width()*(rc.center.x / abs(rc.center.x));
			vel.x = 0;
			accel.x = 0;
		}
		actor->SetVelocity(vel);
		actor->SetAccel(accel);
		actor->PushBack(sz.w, sz.h);
	}
};

class Pendulum :public Block{
private:
	int _length;
	float _v = 0;
	Vector2f _vel;
	Vector2f _pivot;
public:
	Pendulum(const Vector2& pos, const Camera& cam, unsigned int runLength = 1) :
		Block(Rect(pos, Size(block_size*fixed_block, block_size)), cam), _length((int)runLength*block_size) {
		_blockH = LoadGraph("img/blocks.png");
		_pivot = Vector2f(_rect.Left(), _rect.Top());
		_rect.center.x = _pivot.x + _length;
	}

	void Update()override
	{
		auto g = Game::GetInstance().GetGravity();
		auto tensionVec = Vector2f(_rect.center.x,_rect.center.y) - _pivot;
		float theta = atan2f(tensionVec.y, tensionVec.x);
		float a = g * 0.5*cos(theta);
		_v += a;
		_vel.x += _v * sin(theta);
		_vel.y += _v * cos(theta);
		_rect.center.x += _vel.x;
		_rect.center.y += _vel.y;
	}

	void Draw()override
	{
		auto c = _camera.GetOffset();
		for (int i = 0; i < fixed_block; ++i)
		{
			auto range = _camera.GetViewRange();
			if (_rect.Right() - _rect.Width() / fixed_block * (fixed_block - (i + 1)) < range.Left()
				|| _rect.Left() + _rect.Width() / fixed_block * i > range.Right())
			{
				continue;
			}
			DrawRectExtendGraph(
				_rect.Left() + _rect.Width() / fixed_block * i - c.x,
				_rect.Top() - c.y,
				_rect.Right() - _rect.Width() / fixed_block * (fixed_block - (i + 1)) - c.x,
				_rect.Bottom() - c.y,
				0, 16 * 7, 16, 16, _blockH, true);
		}
		DrawLine(_pivot.x, _pivot.y, _rect.center.x, _rect.center.y, 0xff0000);
	}

	void OnCollision(Actor* actor, const Rect& rc)override
	{

	}
};


BlockFactory::BlockFactory(const Camera& c):_camera(c)
{
}


BlockFactory::~BlockFactory()
{
}

std::unique_ptr<Block> BlockFactory::Create(BlockType type, const Vector2 & pos,unsigned int speed)
{
	switch (type)
	{
	case BlockType::brick:
		return std::make_unique<Brick>(pos, _camera);
		break;
	case BlockType::lift:
		return std::make_unique<Lift>(pos, _camera, speed);
		break;
	case BlockType::slide:
		return std::make_unique<Slide>(pos, _camera, speed);
		break;
	case BlockType::pendulum:
		return std::make_unique<Pendulum>(pos, _camera, speed);
		break;
	default:
		return std::unique_ptr<Block>();
		break;
	}
}

Block::Block():_rect(Rect()),_camera(Camera::Camera())
{
}

Block::Block(const Rect & rect,const Camera& c):_rect(rect),_camera(c)
{
}

const Rect & Block::GetCollider() const
{
	return _rect;
}

