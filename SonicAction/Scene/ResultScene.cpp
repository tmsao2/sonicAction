#include "ResultScene.h"
#include "TitleScene.h"
#include "../Input.h"
#include "SceneController.h"
#include <DxLib.h>


ResultScene::ResultScene(SceneController& controller) :Scene(controller)
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update(const Input& input)
{
	if (input.IsTriggered(0, COMMAND::OK)) 
	{
		_controller.ChangeScene(std::make_unique<TitleScene>(_controller));
	}
}

void ResultScene::Draw()
{
	DrawString(10, 10, "Result", 0xffffff);
}
