#pragma once
#include "Loader.h"
#include <map>
#include <string>

class ImageLoader :
	public Loader
{
private:
	std::map<std::string, int> _table;
public:
	ImageLoader();
	~ImageLoader();
	bool Load(const char* path, Data& data)override;
};

class ImageData :
	public Data
{
	friend ImageLoader;
private:
	int _handle;
public:
	int GetHandle()const;
};


