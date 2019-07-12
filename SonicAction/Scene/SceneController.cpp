#include "SceneController.h"
#include "Scene.h"
#include "TitleScene.h"

SceneController::SceneController()
{
	_scene.push_front(std::make_unique<TitleScene>(*this));
}

SceneController::~SceneController()
{
}

void SceneController::ChangeScene(std::unique_ptr<Scene> scene)
{
	_scene.clear();
	_scene.push_front(move(scene));
}

void SceneController::PushScene(std::unique_ptr<Scene> scene)
{
	_scene.push_front(move(scene));
}

void SceneController::PopScene()
{
	_scene.pop_front();
}

void SceneController::SceneUpdate(const Input & input)
{
	_scene.front()->Update(input);
}

void SceneController::SceneDraw()
{
	for (auto itr = _scene.rbegin(); itr != _scene.rend(); itr++) 
	{
		itr->get()->Draw();
	}
}


