#include "Game.h"
#include "Input.h"
#include "Scene/SceneController.h"
#include "System/FileSystem.h"
#include <DxLib.h>


constexpr int screen_size_x = 1024;
constexpr int screen_size_y = 576;

Game::Game()
{
}


Game::~Game()
{
}


const Game::Config & Game::GetConfig() const
{
	return _config;
}


std::shared_ptr<FileSystem> Game::GetFileSystem()
{
	return _fileSystem;
}

float Game::GetGravity() const
{
	return 0.4f;
}

void Game::Init()
{
	DxLib::SetGraphMode(screen_size_x, screen_size_y, 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetMainWindowText("ソニック的な～");
	if (DxLib_Init() == -1) 
	{
		return;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	InputInit();
	_fileSystem = std::make_shared<FileSystem>();
}

void Game::Run()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_input->Update();
		_sceneController->SceneUpdate(*_input);

		ClsDrawScreen();
		
		_sceneController->SceneDraw();

		ScreenFlip();
	}
}

void Game::InputInit()
{
	_input = std::make_unique<Input>();

	_input->AddCommand(0, COMMAND::UP, 0, KEY_INPUT_UP);
	_input->AddCommand(0, COMMAND::DOWN, 0, KEY_INPUT_DOWN);
	_input->AddCommand(0, COMMAND::RIGHT, 0, KEY_INPUT_RIGHT);
	_input->AddCommand(0, COMMAND::LEFT, 0, KEY_INPUT_LEFT);
	_input->AddCommand(0, COMMAND::BACK, 0, KEY_INPUT_Q);
	_input->AddCommand(0, COMMAND::FRONT, 0, KEY_INPUT_E);
	_input->AddCommand(0, COMMAND::ROTATE, 0, KEY_INPUT_R);
	_input->AddCommand(0, COMMAND::JUMP, 0, KEY_INPUT_SPACE);
	_input->AddCommand(0, COMMAND::ATTACK, 0, KEY_INPUT_X);

	_input->AddCommand(0, COMMAND::OK,0, KEY_INPUT_RETURN);
	_input->AddCommand(0, COMMAND::PAUSE, 0, KEY_INPUT_P);

	auto padnum = _input->GetJoypadCount();
	for (int i = 0; i < padnum; i++)
	{
		_input->AddCommand(i, COMMAND::UP, i + 1, PAD_INPUT_UP);
		_input->AddCommand(i, COMMAND::DOWN, i + 1, PAD_INPUT_DOWN);
		_input->AddCommand(i, COMMAND::RIGHT, i + 1, PAD_INPUT_RIGHT);
		_input->AddCommand(i, COMMAND::LEFT, i + 1, PAD_INPUT_LEFT);
		_input->AddCommand(i, COMMAND::JUMP, i + 1, PAD_INPUT_4);
		_input->AddCommand(i, COMMAND::ATTACK, i + 1, PAD_INPUT_3);
		_input->AddCommand(i, COMMAND::OK, i + 1, PAD_INPUT_7);
		_input->AddCommand(i, COMMAND::PAUSE, i + 1, PAD_INPUT_R);
	}
	_sceneController = std::make_unique<SceneController>();
}

void Game::End()
{
	DxLib_End();
}


Game::Config::Config()
{
	winSize.w = screen_size_x;
	winSize.h = screen_size_y;
}

const Size & Game::Config::GetScreenSize() const
{
	return winSize;
}
