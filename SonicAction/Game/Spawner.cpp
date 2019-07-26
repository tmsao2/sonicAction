#include "Spawner.h"
#include "Enemy.h"


std::shared_ptr<Enemy> Spawner::CreateClone()
{
	return _original->MakeClone();
}

Spawner::Spawner(std::shared_ptr<Enemy> origin):_original(origin)
{

}

Spawner::~Spawner()
{

}
