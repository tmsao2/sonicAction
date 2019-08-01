#include "Playing3DScene.h"
#include "SceneController.h"
#include "ResultScene.h"
#include "../Input.h"


Playing3DScene::Playing3DScene(SceneController & controller) :Scene(controller)
{
	// pmxファイルを読み込み
	_modelH = MV1LoadModel("3Dモデル/models/シスタークレア.pmx");
	// カメラの設定
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 12.0f, -20.0f), VGet(0.0f, 10.0f, 1.0f));
	SetCameraNearFar(0.42f, 103.0f);
}

Playing3DScene::~Playing3DScene()
{
	MV1DeleteModel(_modelH);
}

void Playing3DScene::Update(const Input & input)
{
	if (input.IsTriggered(0, COMMAND::OK))
	{
		_controller.ChangeScene(std::make_unique<ResultScene>(_controller));
	}
	auto pos = MV1GetPosition(_modelH);
	auto rad = MV1GetRotationXYZ(_modelH);
	if (input.IsPressed(0, COMMAND::LEFT))
	{
		pos.x -= 1;
	}
	if (input.IsPressed(0, COMMAND::RIGHT))
	{
		pos.x += 1;
	}
	if (input.IsPressed(0, COMMAND::UP))
	{
		pos.y += 1;
	}
	if (input.IsPressed(0, COMMAND::DOWN))
	{
		pos.y -= 1;
	}
	if (input.IsPressed(0, COMMAND::BACK))
	{
		pos.z += 1;
	}
	if (input.IsPressed(0, COMMAND::FRONT))
	{
		pos.z -= 1;
	}
	if (input.IsPressed(0, COMMAND::ROTATE))
	{
		rad.y += 5.0f*DX_PI_F / 180.0f;
	}
	if (input.IsPressed(0, COMMAND::JUMP))
	{
		MV1AttachAnim(_modelH, 0);
	}
	MV1SetPosition(_modelH, pos);
	MV1SetRotationXYZ(_modelH, rad);
}

void Playing3DScene::Draw()
{
	MV1DrawModel(_modelH);
}
