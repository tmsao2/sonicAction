#pragma once
#include "Geometry.h"
#include <memory>
#include <vector>
#include <map>

class Ground;
class Block;
class Camera;

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

class Stage
{
private:
	Rect _stageRange;

	FMF _fmfdata;

	const Camera& _camera;

	int CheckRunLength(int& idxX,int& idxY,int no,std::vector<unsigned char> data);
	std::map<unsigned char,std::vector<Vector2f>> _terraPositions;
	std::vector<std::unique_ptr<Block>> _blocks;

public:
	Stage(const Camera& c);
	~Stage();
	const std::vector<std::unique_ptr<Block>>& Blocks()const;
	void Update();
	void Draw();
	void DataLoad(const char* path);
	void BuildGround(Ground& g);
};

