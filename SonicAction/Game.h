#pragma once
#include <memory>
#include "Geometry.h"

class Input;
class SceneController;

class Game
{
private:
	///生成禁止
	Game();
	///代入禁止
	Game(const Game&) = delete;
	///コピー禁止
	Game& operator=(Game&) = delete;

	struct GameDeleter
	{
		void operator()(Game *game)const {
			delete game;
		}
	};


	std::unique_ptr<Input> _input;
	std::unique_ptr<SceneController> _sceneController;

public:
	~Game();

	class Config {
	private:
		Size winSize;
	public:
		Config();
		const Size& GetScreenSize()const;
	};
	Config _config;
	const Config& GetConfig()const;

	static Game& GetInstance()
	{
		static Game s_Instance;

		return s_Instance;
	}

	float GetGravity()const;
	
	///初期化
	void Init();
	///更新
	void Run();
	///入力初期化
	void InputInit();
	///終了
	void End();


};

