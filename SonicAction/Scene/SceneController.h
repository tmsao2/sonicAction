#pragma once
#include <deque>
#include <memory>

class Scene;
class Input;

class SceneController
{
private:
	std::deque<std::unique_ptr<Scene>> _scene;
public:
	SceneController();
	~SceneController();
	///�V�[���؂�ւ�
	void ChangeScene(std::unique_ptr<Scene> scene);

	///�V�[���}��
	void PushScene(std::unique_ptr<Scene> scene);

	///�V�[���폜
	void PopScene();

	///�X�V����
	void SceneUpdate(const Input& input);
	void SceneDraw();
};

