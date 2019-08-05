#pragma once
#include "Scene.h"
#include <vector>
#include <memory>
#include "../Geometry.h"

struct Player3D
{
	int modelH;
	int animIdx;
	float animTime;
	float totalTime;
	VECTOR pos;
	VECTOR dir;
};

struct Camera3D
{
	VECTOR eye;
	VECTOR target;
	VECTOR viewray;
};

class Playing3DScene :
	public Scene
{
private:
	std::vector<Player3D> _anim;
	std::shared_ptr<Camera3D> _camera;
	void DrawCube();
	void CameraUpdate(const Input& input);
	void PlayerUpdate(const Input& input);
public:
	Playing3DScene(SceneController& controller);
	~Playing3DScene();
	void Update(const Input& input)override final;
	void Draw()override final;
};

