#include "Playing3DScene.h"
#include "SceneController.h"
#include "ResultScene.h"
#include "../Game.h"
#include "../Input.h"


constexpr int sp_radius = 32;

Playing3DScene::Playing3DScene(SceneController & controller) :Scene(controller)
{
	// pmxファイルを読み込み
	_anim.resize(1);
	_anim[0].modelH = MV1LoadModel("3Dモデル/本間ひまわり/本間ひまわり.pmx");
	/*_anim[1].modelH = MV1LoadModel("3Dモデル/赤羽葉子/赤羽葉子(修正版).pmx");
	_anim[2].modelH = MV1LoadModel("3Dモデル/叶/通常衣装/叶.pmx");
	_anim[3].modelH = MV1LoadModel("3Dモデル/葛葉/葛葉.pmx");*/

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);

	//3Dモデルの設定
	for (int i = 0; i < _anim.size(); ++i)
	{
		_anim[i].animIdx = MV1AttachAnim(_anim[i].modelH, 0);
		_anim[i].totalTime = MV1GetAttachAnimTotalTime(_anim[i].modelH, _anim[i].animIdx);
		MV1SetPosition(_anim[i].modelH, VGet(15.0f*i, 32.0f, 1.0f));
		_anim[i].dir = VGet(0, 0, 1);
		_anim[i].pos = MV1GetPosition(_anim[i].modelH);
	}

	// カメラの設定
	_camera = std::make_shared<Camera3D>();
	_camera->eye = VGet(0, 40.0f, -50.0f);
	_camera->target = _anim[0].pos;
	_camera->viewray = VSub(_camera->target, _camera->eye);

	SetCameraPositionAndTarget_UpVecY(_camera->eye, _camera->target);
	SetCameraNearFar(1.0f, 1000.0f);
	SetupCamera_Perspective(45.0f*DX_PI_F / 180.0f);
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
	PlayerUpdate(input);
	CameraUpdate(input);
	
	if (input.IsTriggered(0, COMMAND::OK))
	{
		_controller.ChangeScene(std::make_unique<ResultScene>(_controller));
	}
}

void Playing3DScene::DrawCube()
{
	constexpr float tileSize = 25.0f;
	auto leftTop = VGet(-tileSize / 2, 0, -tileSize / 2);
	auto rightBottom = VGet(tileSize / 2, -1, tileSize / 2);
	int a = 0;
	auto wsize = Game::GetInstance().GetConfig().GetScreenSize();
	for (int i = -4; i < 5; ++i)
	{
		for (int j = -4; j < 5; ++j)
		{
			auto vTop = leftTop;
			auto vBottom = rightBottom;
			vTop.x += j * tileSize;
			vTop.z += i * tileSize;
			vBottom.x += j * tileSize;
			vBottom.z += i * tileSize;
			a = (abs(i) + abs(j)) * 32;
			auto col = GetColor(255 - a, 128 - a, 255);
			DrawCube3D(vBottom, vTop, col, 0xffffff, true);
		}
	}
}

void Playing3DScene::CameraUpdate(const Input & input)
{
	_camera->target = _anim[0].pos;

	auto rray = VScale(_camera->viewray, -1);

	if (input.IsPressed(0, COMMAND::RLEFT))
	{
		rray = VAdd(rray, VNorm(VCross(_camera->viewray, VGet(0, 1, 0))));
	}
	if (input.IsPressed(0, COMMAND::RRIGHT))
	{
		rray = VAdd(rray, VNorm(VCross(VGet(0, 1, 0), _camera->viewray)));
	}
	if (input.IsPressed(0, COMMAND::RUP))
	{
		rray = VAdd(rray, VNorm(VCross(_camera->viewray, VGet(1, 0, 0))));
	}
	if (input.IsPressed(0, COMMAND::RDOWN))
	{
		rray = VAdd(rray, VNorm(VCross(VGet(1, 0, 0), _camera->viewray)));
	}
	
	_camera->eye = VAdd(_camera->target, VScale(VNorm(rray), VSize(_camera->viewray)));
	_camera->viewray = VSub(_camera->target, _camera->eye);

	SetCameraPositionAndTarget_UpVecY(_camera->eye, _camera->target);
}

void Playing3DScene::PlayerUpdate(const Input & input)
{
	auto sn = VNorm(VSub(_anim[0].pos, VGet(0,0,0)));
	if (input.IsPressed(0, COMMAND::UP))
	{
		auto rvec = VNorm(VCross(sn, _camera->viewray));
		_anim[0].dir = VNorm(VCross(rvec, sn));
		_anim[0].pos = VAdd(_anim[0].pos, VScale(_anim[0].dir, 0.5f));
		_anim[0].animTime += 0.5f;
	}
	if (input.IsPressed(0, COMMAND::DOWN))
	{
		auto rvec = VNorm(VCross(sn, _camera->viewray));
		_anim[0].dir = VNorm(VCross(sn, rvec));
		_anim[0].pos = VAdd(_anim[0].pos, VScale(_anim[0].dir, 0.5f));
		_anim[0].animTime += 0.5f;
	}
	if (input.IsPressed(0, COMMAND::RIGHT))
	{
		_anim[0].dir = VNorm(VCross(sn, _camera->viewray));
		_anim[0].pos = VAdd(_anim[0].pos, VScale(_anim[0].dir, 0.5f));
		_anim[0].animTime += 0.5f;
	}
	if (input.IsPressed(0, COMMAND::LEFT))
	{
		_anim[0].dir = VNorm(VCross(_camera->viewray, sn));
		_anim[0].pos = VAdd(_anim[0].pos, VScale(_anim[0].dir, 0.5f));
		_anim[0].animTime += 0.5f;
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

	if (VSize(VSub(_anim[0].pos, VGet(0, 0, 0))) > sp_radius)
	{
		sn= VNorm(VSub(_anim[0].pos, VGet(0, 0, 0)));
		_anim[0].pos = VScale(sn, sp_radius);
	}

	MV1SetRotationZYAxis(_anim[0].modelH, -_anim[0].dir, sn, 0.0f);
	MV1SetPosition(_anim[0].modelH, _anim[0].pos);

}

void Playing3DScene::Draw()
{
	//DrawCube();
	DrawSphere3D(VGet(0, 0, 0), sp_radius, 32, 0x88ffaa, 0xffffff, false);
	for (int i = 0; i < _anim.size(); ++i)
	{
		MV1DrawModel(_anim[i].modelH);
	}
}
