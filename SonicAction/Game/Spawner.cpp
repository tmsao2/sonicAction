#include "Spawner.h"



std::shared_ptr<Enemy> Spawner::CreateClone()
{
	return std::shared_ptr<Enemy>();
}

Spawner::Spawner(std::shared_ptr<Enemy> origin)
{

}

Spawner::~Spawner()
{

}
