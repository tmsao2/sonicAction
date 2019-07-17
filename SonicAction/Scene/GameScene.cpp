#include "GameScene.h"
#include "ResultScene.h"
#include "PauseScene.h"
#include "../Game.h"
#include "../Input.h"
#include "../Camera.h"
#include "../Ground.h"
#include "../Stage.h"
#include "../BackGround.h"
#include "../Game/Actor.h"
#include "../Game/Player.h"
#include "../BlockFactory.h"
#include "../Collider.h"
#include "SceneController.h"
#include <DxLib.h>

GameScene::GameScene(SceneController& controller) :Scene(controller)
{
	auto size = Game::GetInstance().GetConfig().GetScreenSize();
	_camera = std::make_unique<Camera>();
	_player = std::make_shared<Player>(*_camera, size.w /2, size.h/2);
	_actors.emplace_back(_player);
	_bg = std::make_unique<BackGround>(*_camera);
	_camera->AddPlayer(_player);
	_ground = std::make_unique<Ground>(*_camera,*_player);
	_stage = std::make_unique<Stage>(*_camera);
	_stage->DataLoad("level/level1.fmf");
	_stage->BuildGround(*_ground);
	_bg->AddParts("img/bg-clouds.png", Vector2f(0, 0), 0.1, true, LayoutType::repeat, size);
	_bg->AddParts("img/bg-mountains.png", Vector2f(0, -30), 0.4, true, LayoutType::repeat, size);
	_bg->AddParts("img/tree.png", Vector2f(0, 0), 0.9, true, LayoutType::repeat, size);
}

GameScene::~GameScene()
{
}

void GameScene::Update(const Input& input)
{
	auto size = Game::GetInstance().GetConfig().GetScreenSize();
	_camera->Update();
	_camera->SetRange(size);

	
	if (!_player->IsDying()&&!_player->IsDie())
	{
		auto viewrange = _camera->GetViewRange();
		auto& blocks = _stage->Blocks();
		for (auto& b : blocks)
		{
			auto& brect = b->GetCollider();
			auto& prect = _player->GetCollider();
			if (brect.Right() < viewrange.Left() || brect.Left() > viewrange.Right())
			{
				continue;
			}
			if (Collider::IsCollided(prect, brect))
			{
				auto w = min(prect.Right(), brect.Right()) - max(prect.Left(), brect.Left());
				auto h = min(prect.Bottom(), brect.Bottom()) - max(prect.Top(), brect.Top());
				auto size = Size(w, h);

				Rect rc;
				rc.center = prect.center - brect.center;
				rc.size = size;

				b->OnCollision(&(*_player), rc);
			}
		}
		if (_player->GetVelocity().y > 0)
		{
			float grad;
			float y = _ground->GetGroundY(grad);
			_player->OnGround(y, grad);
		}
		if (_player->GetPosition().y >= _ground->GetDeadLine())
		{
			_player->OnDead();
			_camera->RemovePlayer(_player);
		}
	}

	for (auto actor : _actors)
	{
		actor->Update(input);
	}

	_stage->Update();

	if(_player->IsDie())
	{
		_controller.ChangeScene(std::make_unique<GameScene>(_controller));
	}
	
	if (input.IsTriggered(0, COMMAND::OK))
	{
		_controller.ChangeScene(std::make_unique<ResultScene>(_controller));
	}
	if (input.IsTriggered(0, COMMAND::PAUSE)) 
	{
		_controller.PushScene(std::make_unique<PauseScene>(_controller));
	}
}

void GameScene::Draw()
{
	_bg->DrawBg();
	_ground->Draw();
	_stage->Draw();
	for (auto actor : _actors) {
		actor->Draw();
		actor->DebagDraw();
	}
	DrawString(12, 0, "Game", 0xffffff);
}
