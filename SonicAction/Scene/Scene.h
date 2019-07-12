#pragma once
class Input;
class SceneController;

class Scene
{
protected:
	SceneController& _controller;

public:
	Scene(SceneController& controller);
	virtual ~Scene();
	virtual void Update(const Input& input) = 0;
	virtual void Draw() = 0;
};

