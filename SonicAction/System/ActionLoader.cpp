#include "ActionLoader.h"
#include <DxLib.h>


ActionLoader::ActionLoader()
{
}


ActionLoader::~ActionLoader()
{
}

bool ActionLoader::Load(const char * path, Data & data)
{
	ActionData& action = dynamic_cast<ActionData&>(data);

	auto size = FileRead_size(path);
	_table[path].resize(size);
	auto h = FileRead_open(path);
	FileRead_read(_table[path].data(), size, h);
	FileRead_close(h);
	action._data = &_table[path];
	return true;
}

std::vector<unsigned char>* ActionData::GetRawData()
{
	return _data;
}

void ActionData::ReadData(void * inDst, size_t bytenum, size_t & cursor, ActionData & act)
{
	char* dst = (char*)inDst;
	std::copy(act.GetRawData()->begin() + cursor,
		act.GetRawData()->begin() + cursor + bytenum,
		dst);
	cursor += bytenum;
}

void ActionData::BuildActionSet(ActionData & actdata, ActionSet & actset, std::string & imgpath)
{
	
	size_t cursor=0;

	//バージョン読み込み
	float version = 0.0f;
	ReadData(&version, sizeof(version), cursor, actdata);

	//ファイル名のサイズ
	int filenamesize = 0;
	ReadData(&filenamesize, sizeof(filenamesize), cursor, actdata);

	//ファイル名
	imgpath.resize(filenamesize);
	ReadData(&imgpath[0], filenamesize, cursor, actdata);

	//このアプリケーションからの相対パスに変換
	auto ipos = imgpath.find_first_of("/") + 1;
	imgpath = imgpath.substr(ipos, imgpath.size());

	//アクション数
	int actionCnt = 0;
	ReadData(&actionCnt, sizeof(actionCnt), cursor, actdata);

	for (int idx = 0; idx < actionCnt; ++idx)
	{
		//アクション名の数
		int actnamesize = 0;
		ReadData(&actnamesize, sizeof(actnamesize), cursor, actdata);

		//アクション名
		std::string actname;
		actname.resize(actnamesize);
		ReadData(&actname[0], actnamesize, cursor, actdata);

		ActionInfo actInfo;

		//ループ情報
		ReadData(&actInfo.isLoop, sizeof(actInfo.isLoop), cursor, actdata);

		//カット数
		int cutCnt = 0;
		ReadData(&cutCnt, sizeof(cutCnt), cursor, actdata);

		//カットデータ
		actInfo.cuts.resize(cutCnt);
		for (int i = 0; i < cutCnt; ++i)
		{
			ReadData(&actInfo.cuts[i], sizeof(actInfo.cuts[i]) - sizeof(actInfo.cuts[i].actrects), cursor, actdata);

			int actrcCnt = 0;
			ReadData(&actrcCnt, sizeof(actrcCnt), cursor, actdata);

			if (actrcCnt > 0)
			{
				actInfo.cuts[i].actrects.resize(actrcCnt);
				for (auto& actrect : actInfo.cuts[i].actrects)
				{
					ReadData(&actrect, sizeof(actrect), cursor, actdata);
				}
			}
		}
		actset.actInfo[actname] = actInfo;
	}
}
