#pragma once
#include "Scene.h"
class ResultScene :
	public Scene
{
public:
	ResultScene(SceneController& controller);
	~ResultScene();
	void Update(const Input& input)override final;
	void Draw()override final;
};

