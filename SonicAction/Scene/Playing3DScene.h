#pragma once
#include "Scene.h"
#include <vector>
#include <memory>
#include "../Geometry.h"

struct Anim
{
	int modelH;
	int animIdx;
	float animTime;
	float totalTime;
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
	std::vector<Anim> _anim;
	std::shared_ptr<Camera3D> _camera;
public:
	Playing3DScene(SceneController& controller);
	~Playing3DScene();
	void Update(const Input& input)override final;
	void Draw()override final;
};

