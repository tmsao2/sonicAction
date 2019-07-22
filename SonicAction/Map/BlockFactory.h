#pragma once
#include <memory>
#include "../Geometry.h"

enum class BlockType
{
	none,
	brick,
	slide,
	lift,
	pendulum,
	braken,
};

class Actor;
class Camera;

class Block {
protected:
	Block();
	Block(const Rect& rect,const Camera& c);
	Rect _rect;
	const Camera& _camera;
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void OnCollision(Actor* actor, const Rect& rc) = 0;

	const Rect& GetCollider()const;
};


class BlockFactory
{
private:
	const Camera& _camera;
	
public:
	BlockFactory(const Camera& c);
	~BlockFactory();
	std::unique_ptr<Block> Create(BlockType type, const Vector2& pos, unsigned int speed = 1);
};

