#include "SoundLoader.h"
#include <DxLib.h>


SoundLoader::SoundLoader()
{
}


SoundLoader::~SoundLoader()
{
}

bool SoundLoader::Load(const char * path, Data & data)
{
	SoundData& sound = dynamic_cast<SoundData&>(data);

	auto it = _table.find(path);
	if (it == _table.end())
	{
		sound._handle = LoadSoundMem(path);
		if (sound._handle == -1)
		{
			return false;
		}
		else
		{
			_table[path] = sound._handle;
			return true;
		}
	}
	else
	{
		sound._handle = _table[path];
	}
	return false;
}

int SoundData::GetHandle() const
{
	return _handle;
}
