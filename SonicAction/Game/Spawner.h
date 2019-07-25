#pragma once
#include <memory>
#include <vector>


class Enemy;
class Actor;

class Spawner
{
protected:
	std::shared_ptr<Enemy> _original;//プロトタイプ

	//クローン生成…派生クラスから呼ぶ
	std::shared_ptr<Enemy> CreateClone();
public:
	Spawner(std::shared_ptr<Enemy> origin);
	virtual ~Spawner();
	virtual std::shared_ptr<Enemy> Spawn() = 0;
	virtual void Update(std::vector<std::shared_ptr<Actor>>& actors) = 0;
};

