#pragma once
#include "Scene.h"
class TitleScene :
	public Scene
{
private:
	int imgH;
	void FadeInUpdate(const Input& input);
	void WaitUpdate(const Input& input);
	void FadeOutUpdate(const Input& input);
	
	void (TitleScene::*_updater)(const Input& input);

	void NormalDraw();
	void FadeDraw();

	void (TitleScene::*_drawer)();
	int _fadeCnt;
public:
	TitleScene(SceneController& controller);
	~TitleScene();
	void Update(const Input& input)override final;
	void Draw()override final;
};

