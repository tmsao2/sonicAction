#include "GameScene.h"
#include "ResultScene.h"
#include "PauseScene.h"
#include "Playing3DScene.h"
#include "SceneController.h"
#include "../Game.h"
#include "../Input.h"
#include "../Camera.h"
#include "../Collider.h"
#include "../Map/Ground.h"
#include "../Map/Stage.h"
#include "../Map/BackGround.h"
#include "../Map/BlockFactory.h"
#include "../Game/Actor.h"
#include "../Game/Player.h"
#include "../Game/Enemy.h"
#include "../Game/Ant.h"
#include "../Game/OnceSpawner.h"
#include "../Game/Event.h"
#include "../Game/HUD.h"
#include "../Game/EventQueue.h"
#include "../System/FileSystem.h"
#include "../System/SoundLoader.h"
#include <algorithm>
#include <DxLib.h>


GameScene::GameScene(SceneController& controller) :Scene(controller)
{
	auto size = Game::GetInstance().GetConfig().GetScreenSize();
	_camera = std::make_unique<Camera>();
	_player = std::make_shared<Player>(*_camera);
	_actors.emplace_back(_player);
	
	_camera->AddPlayer(_player);
	_ground = std::make_unique<Ground>(*_camera);

	_hud = std::make_shared<HUD>();
	_eventQ = std::make_unique<EventQueue>();
	_eventQ->AddObserver(_hud);

	_stage = std::make_unique<Stage>(*_camera,*_eventQ);
	_stage->DataLoad("level/sonic_level1.fmf");
	_stage->BuildGround(*_ground);
	_stage->BuildSpawner(*_player);

	_spawners = _stage->Spawenrs();

	SoundData bgm;
	Game::GetInstance().GetFileSystem()->Load("bgm/bgm.wav", bgm);
	_bgmH = bgm.GetHandle();

	_bg = std::make_unique<BackGround>(*_camera);
	_bg->AddParts("img/bg-clouds.png", Vector2f(0, 0), 0.1, true, LayoutType::repeat, size);
	_bg->AddParts("img/bg-mountains.png", Vector2f(0, -30), 0.4, true, LayoutType::repeat, size);
	_bg->AddParts("img/tree.png", Vector2f(0, 0), 0.9, true, LayoutType::repeat, size);
}

GameScene::~GameScene()
{
	if (CheckSoundMem(_bgmH)) {
		StopSoundMem(_bgmH);
	}
}


void GameScene::CheckActorCol(std::shared_ptr<Actor> actor)
{
	auto prect = _player->GetCollider();
	auto erect = actor->GetCollider();
	if (Collider::IsCollided(prect, erect))
	{
		actor->OnCollision(*_player);
	}
}

void GameScene::CheckBlockCol(std::shared_ptr<Actor> actor)
{
	bool isOn = false;
	auto viewrange = _camera->GetViewRange();
	auto& blocks = _stage->Blocks();
	for (auto& b : blocks)
	{
		auto& brect = b->GetCollider();
		auto& prect = actor->GetCollider();
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
			isOn = prect.center.y < brect.center.y;
			b->OnCollision((*_player), rc);
		}
	}
}

void GameScene::CheckGround(std::shared_ptr<Actor> actor)
{
	float grad;
	Vector2f vec;
	float y = _ground->GetGroundY(&(*actor), grad, vec);
	auto p_vec = actor->GetVelocity().Normalized();
	auto dot = Dot(Vector2f(vec.y, -vec.x), p_vec);
	if (dot < 0)
	{
		actor->OnGround(grad, y);
	}
}

void GameScene::CheckEventCol(std::shared_ptr<Actor> actor)
{
	auto viewrange = _camera->GetViewRange();
	auto& events = _stage->Events();
	for (auto& e : events)
	{
		auto& erect = e->GetCollider();
		auto& prect = actor->GetCollider();
		if (erect.Right() < viewrange.Left() || erect.Left() > viewrange.Right())
		{
			continue;
		}
		if (Collider::IsCollided(prect, erect))
		{
			e->OnCollision();
		}
	}
	auto it = std::remove_if(events.begin(), events.end(), [](std::shared_ptr<Event> e)
	{
		return !e->IsAvailvale();
	});

	events.erase(it, events.end());
}

void GameScene::Update(const Input& input)
{
	if (!CheckSoundMem(_bgmH))
	{
		PlaySoundMem(_bgmH, DX_PLAYTYPE_LOOP);
	}
	auto size = Game::GetInstance().GetConfig().GetScreenSize();
	_camera->Update();
	_camera->SetRange(size);
	_eventQ->Notify();

	for (auto& actor : _actors)
	{
		if (actor == _player)
		{
			if (!_player->IsDying() && !_player->IsDie())
			{
				CheckGround(_player);
				CheckBlockCol(_player);
				CheckEventCol(_player);
			}
			if (_player->GetPosition().y >= _ground->GetDeadLine())
			{
				_player->OnDead();
				_camera->RemovePlayer(_player);
			}
		}
		else
		{
			if (!actor->IsDying() && !actor->IsDie())
			{
				if (!_player->IsDying() && !_player->IsDie())
				{
					CheckActorCol(actor);
				}
				CheckGround(actor);
			}
		}
	}

	for (auto spawner : _spawners)
	{
		spawner->Update(_actors);
	}

	for (auto actor : _actors)
	{
		actor->Update(input);
	}

	_stage->Update();
	auto it = std::remove_if(_actors.begin(), _actors.end(), [](const std::shared_ptr<Actor>& actor)
	{
		return actor->IsDie();
	});
	if (!_player->IsDie())
	{
		_actors.erase(it, _actors.end());
	}
	if(_player->IsDie())
	{
		_controller.ChangeScene(std::make_unique<GameScene>(_controller));
	}
	
	if (input.IsTriggered(0, COMMAND::OK))
	{
		_controller.ChangeScene(std::make_unique<Playing3DScene>(_controller));
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
	}
	_hud->Draw();
	DrawString(12, 0, "Game", 0xffffff);
}
