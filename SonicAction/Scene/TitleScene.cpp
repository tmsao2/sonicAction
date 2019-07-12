#include "TitleScene.h"
#include "GameScene.h"
#include "../Input.h"
#include "../Game.h"
#include "SceneController.h"
#include <DxLib.h>


constexpr int _fade_interval = 60;

void TitleScene::FadeInUpdate(const Input & input)
{
	if (--_fadeCnt <= 0) 
	{
		_updater = &TitleScene::WaitUpdate;
		_drawer = &TitleScene::NormalDraw;
	}
}

void TitleScene::WaitUpdate(const Input & input)
{
	if (input.IsTriggered(0, COMMAND::OK))
	{
		_updater = &TitleScene::FadeOutUpdate;
		_drawer = &TitleScene::FadeDraw;
	}
}

void TitleScene::FadeOutUpdate(const Input & input)
{
	if (++_fadeCnt >= _fade_interval)
	{
		_controller.ChangeScene(std::make_unique<GameScene>(_controller));
	}
}


TitleScene::TitleScene(SceneController& controller):Scene(controller)
{
	imgH = DxLib::LoadGraph("img/sonic.jpg");
	_fadeCnt = _fade_interval;
	_updater = &TitleScene::FadeInUpdate;
	_drawer = &TitleScene::FadeDraw;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(const Input & input)
{
	(this->*_updater)(input);
}

void TitleScene::NormalDraw()
{
	DrawGraph(0, 0, imgH, false);
	DrawString(10, 10, "Title", 0xffffff);
}

void TitleScene::FadeDraw()
{
	auto size = Game::GetInstance().GetConfig().GetScreenSize();
	DrawGraph(0, 0, imgH, false);
	DrawString(10, 10, "Title", 0xffffff);
	SetDrawBlendMode(DX_BLENDMODE_MULA, _fadeCnt * 255 / _fade_interval);
	DrawBox(0, 0, size.w, size.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void TitleScene::Draw()
{
	(this->*_drawer)();
}
