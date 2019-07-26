#include "OnceSpawner.h"
#include "../Camera.h"
#include "Enemy.h"

OnceSpawner::OnceSpawner(const Camera & c, const Vector2f p, std::shared_ptr<Enemy> org):_camera(c),_pos(p),Spawner(org)
{
}

OnceSpawner::~OnceSpawner()
{
}

std::shared_ptr<Enemy> OnceSpawner::Spawn()
{
	auto clone= CreateClone();
	clone->SetPosition(_pos);
	return clone;
}

void OnceSpawner::Update(std::vector<std::shared_ptr<Actor>>& actors)
{
	if (_isSpawnerd)return;
	auto range = _camera.GetViewRange();
	if (range.Left() < _pos.x && range.Right() > _pos.x)
	{
		actors.emplace_back(Spawn());
		_isSpawnerd = true;
	}

}
