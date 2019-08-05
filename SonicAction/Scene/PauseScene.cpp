#include "PauseScene.h"
#include "GameScene.h"
#include "OptionScene.h"
#include "../Input.h"
#include "../Game.h"
#include "SceneController.h"
#include <DxLib.h>

constexpr int _win_height_max = 150;

PauseScene::PauseScene(SceneController& controller) :Scene(controller)
{
	_winHeight = 0;
}

PauseScene::~PauseScene()
{
}

void PauseScene::Update(const Input & input)
{
	if (_win_height_max > _winHeight)
	{
		_winHeight += 2;
		return;
	}
	if (input.IsTriggered(0, COMMAND::RDOWN))
	{

	}
	if (input.IsTriggered(0, COMMAND::RUP))
	{

	}
	if (input.IsTriggered(0, COMMAND::PAUSE)) 
	{
		_controller.PopScene();
	}
	if (input.IsTriggered(0, COMMAND::OK)) 
	{
		_controller.PushScene(std::make_unique<OptionScene>(_controller));
	}
}

void PauseScene::Draw()
{
	auto size = Game::GetInstance().GetConfig().GetScreenSize();
	std::string str = "PAUSE";
	int len = GetDrawStringWidth(str.c_str(), str.length());
	DrawBox(size.w / 4, size.h / 2 - _winHeight, size.w / 4 + size.w / 2, size.h / 2 + _winHeight, 0x000000, true);
	DrawBox(size.w / 4, size.h / 2 - _winHeight, size.w / 4 + size.w / 2, size.h / 2 + _winHeight, 0xffffff, false);
	DrawString(size.w / 2 - len / 2, size.h / 4, str.c_str(), 0xffffff);
	DrawString(size.w / 2 - len / 2, size.h / 4, str.c_str(), 0xffffff);
	DrawString(size.w / 2 - len / 2, size.h / 2, str.c_str(), 0xffffff);
}
