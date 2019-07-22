#pragma once
#include <string>
#include <memory>
#include <map>

class Loader;
class Data;

class FileSystem
{
private:
	std::map<std::string, std::shared_ptr<Loader>> _loaders;
	std::string GetExtension(const char* path);
public:
	FileSystem();
	~FileSystem();
	bool Load(const char* filepath, Data& data);
};

