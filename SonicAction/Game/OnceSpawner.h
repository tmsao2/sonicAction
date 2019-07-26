#pragma once
#include "Spawner.h"
#include "../Geometry.h"
#include <memory>
#include <vector>

class Camera;

class OnceSpawner :
	public Spawner
{
private:
	bool _isSpawnerd = false;
	const Camera& _camera;
	Vector2f _pos;
public:
	OnceSpawner(const Camera& c,const Vector2f p,std::shared_ptr<Enemy> org);
	~OnceSpawner();

	std::shared_ptr<Enemy> Spawn();

	void Update(std::vector<std::shared_ptr<Actor>>& actors)override final;
};

