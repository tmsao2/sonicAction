#pragma once
#include <memory>
#include "Geometry.h"

class Input;
class SceneController;
class FileSystem;

class Game
{
private:
	///�����֎~
	Game();
	///����֎~
	Game(const Game&) = delete;
	///�R�s�[�֎~
	Game& operator=(Game&) = delete;

	struct GameDeleter
	{
		void operator()(Game *game)const {
			delete game;
		}
	};


	std::unique_ptr<Input> _input;
	std::unique_ptr<SceneController> _sceneController;
	std::shared_ptr<FileSystem> _fileSystem;

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

	std::shared_ptr<FileSystem> GetFileSystem();

	float GetGravity()const;
	
	///������
	void Init();
	///�X�V
	void Run();
	///���͏�����
	void InputInit();
	///�I��
	void End();


};

