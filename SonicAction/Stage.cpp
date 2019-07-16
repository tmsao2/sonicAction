#include "Stage.h"
#include "Ground.h"
#include "BlockFactory.h"
#include "Collider.h"
#include "Camera.h"
#include <DxLib.h>
#include <algorithm>

constexpr int block_size = 32;
constexpr int brick_no = 1;
constexpr int lift_no = 2;
constexpr int slide_no = 3;
constexpr int pendulum_no = 4;

Stage::Stage(const Camera& c):_camera(c)
{
}


Stage::~Stage()
{
}

const std::vector<std::unique_ptr<Block>>& Stage::Blocks() const
{
	return _blocks;
}

void Stage::Update()
{
	for (auto& b : _blocks)
	{
		b->Update();
	}
}

void Stage::Draw()
{
	for (auto& b : _blocks)
	{
		b->Draw();
	}
}

void Stage::DataLoad(const char * path)
{
	int fmf_h = FileRead_open(path, false);
	FileRead_read(&_fmfdata, sizeof(_fmfdata), fmf_h);
	std::vector<unsigned char> tmp;
	tmp.resize(_fmfdata.mapWidth*_fmfdata.mapHeight);
	FileRead_read(tmp.data(), tmp.size(), fmf_h);

	for (size_t i = 0; i < tmp.size(); ++i)
	{
		auto no = tmp[i];
		if (no > 0)
		{
			_terraPositions[no - 1].emplace_back(
				(i%_fmfdata.mapWidth)*block_size,
				(i / _fmfdata.mapWidth)*block_size);
		}
	}

	for (auto& vec : _terraPositions)
	{
		std::sort(vec.second.begin(), vec.second.end(),
			[](const Vector2f& lpos, const Vector2f rpos) 
		{
			return lpos.x < rpos.x;
		});
	}

	BlockFactory bf(_camera);

	if (_fmfdata.layerCount == 2)
	{
		std::vector<unsigned char> blockdata(_fmfdata.mapWidth*_fmfdata.mapHeight);
		FileRead_read(blockdata.data(), blockdata.size(), fmf_h);
		for (int y = 0; y < _fmfdata.mapHeight; ++y)
		{
			for (int x = 0; x < _fmfdata.mapWidth; ++x)
			{
				auto no = blockdata[x + y * _fmfdata.mapWidth];
				if (no != 0)
				{
					int runlength;
					runlength = CheckRunLength(x, y, no, blockdata);
					_blocks.emplace_back(bf.Create((BlockType)no,
						Vector2(x*block_size, y*block_size), runlength));
				}
			}
		}
	}

	FileRead_close(fmf_h);
}

int Stage::CheckRunLength(int& idxX, int& idxY, int no, std::vector<unsigned char> data)
{
	int runlength = 1;
	if (no == 1)
	{
		return runlength;
	}
	for (idxX = idxX + 1; idxX < _fmfdata.mapWidth; ++idxX)
	{
		if (data[idxX + idxY * _fmfdata.mapWidth] == no)
		{
			++runlength;
		}
		else
		{
			--idxX;
			break;
		}
	}
	return runlength;
}

void Stage::BuildGround(Ground & g)
{
	for (auto terra : _terraPositions)
	{
		auto it = terra.second.begin();
		for (; it + 1 != terra.second.end(); ++it)
		{
			auto type = EdgeType::none;
			if (it == terra.second.begin())
			{
				type = EdgeType::left;
			}
			else if (it + 2 == terra.second.end())
			{
				type = EdgeType::right;
			}
			g.AddSegment(*it, *(it + 1),type);
		}
		terra.second.clear();
	}
	_terraPositions.clear();
}
