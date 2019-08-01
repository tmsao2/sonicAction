#pragma once
#include "Scene.h"

class Playing3DScene :
	public Scene
{
private:
	int _modelH;
public:
	Playing3DScene(SceneController& controller);
	~Playing3DScene();
	void Update(const Input& input)override final;
	void Draw()override final;
};

