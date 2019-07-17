#pragma once
class Player;
class Enemy
{
protected:
	const Player& _player;
public:
	Enemy(const Player& player);
	virtual ~Enemy();
	virtual void Update()=0;
	virtual void Draw()=0;
};

