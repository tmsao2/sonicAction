#include "Playing3DScene.h"
#include "SceneController.h"
#include "ResultScene.h"
#include "../Input.h"


Playing3DScene::Playing3DScene(SceneController & controller) :Scene(controller)
{
	// pmxファイルを読み込み
	_anim.resize(4);
	_anim[0].modelH = MV1LoadModel("3Dモデル/本間ひまわり/本間ひまわり.pmx");
	/*_anim[1].modelH = MV1LoadModel("3Dモデル/赤羽葉子/赤羽葉子(修正版).pmx");
	_anim[2].modelH = MV1LoadModel("3Dモデル/叶/通常衣装/叶.pmx");
	_anim[3].modelH = MV1LoadModel("3Dモデル/葛葉/葛葉.pmx");*/

	// カメラの設定
	_camera = std::make_shared<Camera3D>();
	_camera->eye = VGet(0, 25.0f, -20.0f);
	_camera->target = VGet(0, 25.0f, 1.0f);
	_camera->viewray = VSub(_camera->target, _camera->eye);

	SetCameraPositionAndTarget_UpVecY(_camera->eye, _camera->target);
	SetCameraNearFar(0.1f, 100.0f);
	SetupCamera_Perspective(45.0f*DX_PI_F / 180.0f);
	for (int i = 0; i < _anim.size(); ++i)
	{
		_anim[i].animIdx = MV1AttachAnim(_anim[i].modelH, 0);
		_anim[i].totalTime = MV1GetAttachAnimTotalTime(_anim[i].modelH, _anim[i].animIdx);
		MV1SetPosition(_anim[i].modelH, VGet(15.0f*i, 10.0f, 1.0f));
	}
}

Playing3DScene::~Playing3DScene()
{
	for (int i = 0; i < _anim.size(); ++i)
	{
		MV1DeleteModel(_anim[i].modelH);
	}
}

void Playing3DScene::Update(const Input & input)
{
	for (int i = 0; i < _anim.size(); ++i)
	{
		_anim[i].animTime += 0.5f;
	}
	if (input.IsTriggered(0, COMMAND::OK))
	{
		_controller.ChangeScene(std::make_unique<ResultScene>(_controller));
	}
	
	if (input.IsPressed(0, COMMAND::LEFT))
	{
		_camera->viewray.x -= 1.0f;
	}
	if (input.IsPressed(0, COMMAND::RIGHT))
	{
		_camera->viewray.x += 1.0f;
	}
	if (input.IsPressed(0, COMMAND::UP))
	{
		_camera->viewray.y += 1.0f;
	}
	if (input.IsPressed(0, COMMAND::DOWN))
	{
		_camera->viewray.y -= 1.0f;
	}
	if (input.IsPressed(0, COMMAND::BACK))
	{
		_camera->viewray.z += 1.0f;
	}
	if (input.IsPressed(0, COMMAND::FRONT))
	{
		_camera->viewray.z -= 1.0f;
	}
	if (input.IsPressed(0, COMMAND::ROTATE))
	{
		auto mat = MGetRotY(5.0f*DX_PI_F / 180.0f);
		_camera->viewray = VTransformSR(_camera->viewray, mat);
	}
	
	for (int i = 0; i < _anim.size(); ++i)
	{
		if (_anim[i].totalTime <= _anim[i].animTime)
		{
			_anim[i].animTime = 0.0f;
		}
	}
	for (int i = 0; i < _anim.size(); ++i)
	{
		MV1SetAttachAnimTime(_anim[i].modelH, _anim[i].animIdx, _anim[i].animTime);
	}
	SetCameraPositionAndTarget_UpVecY(VSub(_camera->eye, _camera->viewray), _camera->target);
}

void Playing3DScene::Draw()
{
	for (int i = 0; i < _anim.size(); ++i)
	{
		MV1DrawModel(_anim[i].modelH);
	}
}
