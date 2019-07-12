#include "OptionScene.h"
#include "GameScene.h"
#include "../Input.h"
#include "SceneController.h"
#include <DxLib.h>


OptionScene::OptionScene(SceneController& controller):Scene(controller)
{

}


OptionScene::~OptionScene()
{
}

void OptionScene::Update(const Input & input)
{
	if (input.IsTriggered(0, COMMAND::OK)) 
	{
		_controller.PopScene();
	}
}

void OptionScene::Draw()
{
	DrawString(480, 100, "OPTION", 0xffffff);
}
