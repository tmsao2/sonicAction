#pragma once
#include "Geometry.h"
#include <vector>
#include <memory>

class Player;

class Camera
{
private:
	Vector2f _initPos;
	Vector2f _pos;
	Rect _viewRange;

	Vector2f GetAvgPosition()const;
	void SubmitPos();

	std::vector<std::shared_ptr<Player>> _players;
public:
	Camera();
	~Camera();

	void AddPlayer(std::shared_ptr<Player>);
	void RemovePlayer(std::shared_ptr<Player>);

	void SetRange(Size& stageSize);

	void Update();

	const Vector2f& GetPosition()const;

	const Vector2f GetOffset()const;

	const Rect& GetViewRange()const;
};

