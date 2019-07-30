#pragma once
#include "../Geometry.h"
#include <memory>
#include <vector>
#include <map>

class Ground;
class Block;
class Camera;
class Player;
class Spawner;
class Event;

struct FMF
{
	int identifier;
	int size;
	int mapWidth;
	int mapHeight;
	char chipH;
	char chipW;
	char layerCount;
	char bitCount;
};

enum class EnemyType
{
	ant = 1,
	locust = 2,
	lizard = 3,
	nightmare = 4,
	ant_side = 5,
	locust_side = 6,
	lizard_random = 7
};

class Stage
{
private:
	Rect _stageRange;

	FMF _fmfdata;

	const Camera& _camera;

	int CheckRunLength(int& idxX,int& idxY,int no,std::vector<unsigned char> data);

	std::map<unsigned char,std::vector<Vector2f>> _terraPositions;
	std::map<unsigned char, std::vector<Vector2f>> _spawnerPositions;

	std::vector<std::unique_ptr<Block>> _blocks;
	std::vector<std::shared_ptr<Event>> _events;
	std::vector<std::shared_ptr<Spawner>> _spawners;

public:
	Stage(const Camera& c);
	~Stage();
	const std::vector<std::unique_ptr<Block>>& Blocks()const;
	const std::vector<std::shared_ptr<Event>>& Events()const;
	const std::vector<std::shared_ptr<Spawner>>& Spawenrs()const;
	void Update();
	void Draw();
	void DataLoad(const char* path);
	void BuildGround(Ground& g);
	void BuildSpawner(const Player& player);
};

