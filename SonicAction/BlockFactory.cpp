#include "BlockFactory.h"
#include "Collider.h"
#include "Game/Actor.h"
#include "Camera.h"
#include <DxLib.h>

int _blockH = -1;
constexpr int move_frame = 2;

class Brick :public Block{
public:
	Brick(const Vector2& pos,const Camera& c) :Block(Rect(pos, Size(32,32)),c) {
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
		auto sz = Size(0, 0);
		if (rc.Height() < rc.Width())
		{
			if (rc.center.y < 0)
			{
				actor->OnGround(_rect.Top(),0);
			}
			if (rc.center.y == 0)return;
			sz.h = rc.Height()*(rc.center.y / abs(rc.center.y));
		}
		else
		{
			if (rc.center.x == 0)return;
			sz.w = rc.Width()*(rc.center.x / abs(rc.center.x));
		}
		actor->PushBack(sz.w, 0);
	}

};

class Slide :public Block {
private:
	int _speed;
	int _frame = 0;
public:
	Slide(const Vector2& pos, const Camera& cam, unsigned int runLength = 1) :
		Block(Rect(pos, Size(32, 32)), cam), _speed((int)runLength) {
		_blockH = LoadGraph("img/blocks.png");
	}

	void Update()override
	{
		auto cnt = abs((++_frame / 180) % move_frame - move_frame / 2);
		if (cnt == 0)
		{
			_rect.center.x += _speed;
		}
		else if (cnt == 1)
		{
			_rect.center.x -= _speed;
		}
	}

	void Draw()override
	{
		auto range = _camera.GetViewRange();
		auto c = _camera.GetOffset();
		for (int i = 0; i < 5; ++i)
		{
			DrawRectExtendGraph(
				_rect.Left() - c.x + _rect.Width()*i,
				_rect.Top() - c.y,
				_rect.Right() - c.x + _rect.Width()*i,
				_rect.Bottom() - c.y,
				0, 16*7, 16, 16, _blockH, true);
		}
	}

	void OnCollision(Actor* actor, const Rect& rc)override
	{

	}
};

class Lift :public Block {
private:
	int _speed;
	int _frame=0;
public:
	Lift(const Vector2& pos, const Camera& cam, unsigned int runLength = 1) :
		Block(Rect(pos, Size(32, 32)), cam), _speed((int)runLength) {
		_blockH = LoadGraph("img/blocks.png");
	}

	void Update()override
	{
		auto cnt = abs((++_frame / 60) % move_frame - move_frame / 2);
		if (cnt == 0)
		{
			_rect.center.y += _speed;
		}
		else if (cnt == 1)
		{
			_rect.center.y -= _speed;
		}
	}

	void Draw()override
	{
		auto range = _camera.GetViewRange();
		auto c = _camera.GetOffset();
		for (int i = 0; i < 5; ++i)
		{
			DrawRectExtendGraph(
				_rect.Left() - c.x + _rect.Width()*i,
				_rect.Top() - c.y ,
				_rect.Right() - c.x + _rect.Width()*i,
				_rect.Bottom() - c.y,
				16, 16*7, 16, 16, _blockH, true);
		}
	}

	void OnCollision(Actor* actor, const Rect& rc)override
	{

	}
};

class Pendulum :public Block{
private:
	int _speed;
public:
	Pendulum(const Vector2& pos, const Camera& cam, unsigned int runLength = 1) :
		Block(Rect(pos, Size(32, 32)), cam), _speed((int)runLength) {
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
			32, 16, 16, 16, _blockH, true);
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

