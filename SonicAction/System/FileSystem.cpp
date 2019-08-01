#include "FileSystem.h"
#include "Loader.h"
#include "ImageLoader.h"
#include "ActionLoader.h"
#include "SoundLoader.h"

std::string FileSystem::GetExtension(const char * path)
{
	std::string str = path;
	auto idx = str.rfind('.') + 1;
	return str.substr(idx, str.length() - idx);
}

FileSystem::FileSystem()
{
	_loaders["bmp"] = _loaders["png"] = _loaders["jpg"] = std::make_shared<ImageLoader>();
	_loaders["act"] = std::make_shared<ActionLoader>();
	_loaders["wav"] = std::make_shared<SoundLoader>();
}


FileSystem::~FileSystem()
{
}

bool FileSystem::Load(const char * filepath, Data & data)
{
	auto ext = GetExtension(filepath);
	return _loaders[ext]->Load(filepath,data);
}
