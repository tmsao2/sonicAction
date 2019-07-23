#include "ImageLoader.h"
#include <DxLib.h>


ImageLoader::ImageLoader()
{
}


ImageLoader::~ImageLoader()
{
}

bool ImageLoader::Load(const char * path, Data & data)
{
	ImageData& img = dynamic_cast<ImageData&>(data);
	auto it = _table.find(path);
	if (it == _table.end())
	{
		img._handle = LoadGraph(path);
		if (img._handle == -1)
		{
			return false;
		}
		else
		{
			_table[path] = img._handle;
			return true;
		}
	}
	else
	{
		img._handle = _table[path];
	}
	return false;
}

int ImageData::GetHandle()const
{
	return _handle;
}
