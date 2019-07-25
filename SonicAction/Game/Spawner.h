#pragma once
#include <memory>
#include <vector>


class Enemy;
class Actor;

class Spawner
{
protected:
	std::shared_ptr<Enemy> _original;//�v���g�^�C�v

	//�N���[�������c�h���N���X����Ă�
	std::shared_ptr<Enemy> CreateClone();
public:
	Spawner(std::shared_ptr<Enemy> origin);
	virtual ~Spawner();
	virtual std::shared_ptr<Enemy> Spawn() = 0;
	virtual void Update(std::vector<std::shared_ptr<Actor>>& actors) = 0;
};

