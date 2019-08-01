#pragma once
#include "Loader.h"
#include <map>
#include <string>

class SoundLoader :
	public Loader
{
private:
	std::map<std::string, int> _table;
public:
	SoundLoader();
	~SoundLoader();
	bool Load(const char* path, Data& data)override;
};

class SoundData :
	public Data
{
	friend SoundLoader;
private:
	int _handle;
public:
	int GetHandle()const;
};

