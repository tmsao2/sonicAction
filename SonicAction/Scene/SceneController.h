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
	///シーン切り替え
	void ChangeScene(std::unique_ptr<Scene> scene);

	///シーン挿入
	void PushScene(std::unique_ptr<Scene> scene);

	///シーン削除
	void PopScene();

	///更新処理
	void SceneUpdate(const Input& input);
	void SceneDraw();
};

