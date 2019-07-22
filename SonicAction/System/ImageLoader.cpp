#include "ImageLoader.h"



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
		img._handle=
	}
	return false;
}

int ImageData::GetHandle()const
{
	return _handle;
}
