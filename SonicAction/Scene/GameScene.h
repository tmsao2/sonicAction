#pragma once
#include "Scene.h"
#include "../Geometry.h"
#include <memory>
#include <vector>

class Actor;
class Player;
class Camera;
class Ground;
class Stage;
class BackGround;

class GameScene :
	public Scene
{
private:
	std::vector<std::shared_ptr<Actor>> _actors;
	std::shared_ptr<Player> _player;
	std::unique_ptr<BackGround> _bg;
	std::unique_ptr<Camera> _camera;
	std::unique_ptr<Ground> _ground;
	std::unique_ptr<Stage> _stage;
public:
	GameScene(SceneController& controller);
	~GameScene();
	void Update(const Input& input)override final;
	void Draw()override final;
};

