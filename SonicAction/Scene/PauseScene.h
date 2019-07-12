#pragma once
#include "Scene.h"
class PauseScene :
	public Scene
{
private:
	int _winHeight;
public:
	PauseScene(SceneController& controller);
	~PauseScene();
	void Update(const Input& input)override final;
	void Draw()override final;
};

