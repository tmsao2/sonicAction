#pragma once
#include "Loader.h"
#include "../Geometry.h"
#include <map>
#include <string>
#include <vector>


enum class RectType
{
	none,
	attack,
	damage,
	push
};

struct ActionRect
{
	RectType type;
	Rect rc;
	ActionRect() :type(RectType::none), rc(0, 0, 0, 0) {}
	ActionRect(RectType t, Rect r) :type(t), rc(r) {}
};

struct CutInfo
{
	Rect rc;
	Vector2 center;
	int duration;
	std::vector<ActionRect> actrects;
};

struct ActionInfo
{
	bool isLoop;
	std::vector<CutInfo> cuts;
};

struct ActionSet
{
	std::map<std::string, ActionInfo> actInfo;
};


class ActionLoader :
	public Loader
{
private:
	std::map<std::string, std::vector<unsigned char>> _table;
public:
	ActionLoader();
	~ActionLoader();
	bool Load(const char* path, Data& data)override;
};

class ActionData :
	public Data
{
	friend ActionLoader;
private:
	std::vector<unsigned char>* _data;
public:
	std::vector<unsigned char>* GetRawData();
	static void ReadData(void* inDst, size_t bytenum, size_t& cursor, ActionData& act);
	static void BuildActionSet(ActionData& actdata, ActionSet& actset, std::string& imgpath);
};
