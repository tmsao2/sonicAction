#pragma once
#include "Scene.h"
class OptionScene :
	public Scene
{
public:
	OptionScene(SceneController& controller);
	~OptionScene();
	void Update(const Input& input)override final;
	void Draw()override final;
};

