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

void ActionData::BuildActionSet(const ActionData & actdata, ActionSet & actset, std::string & imgpath)
{
	
	//int actionH = FileRead_open(filepath);

	////�o�[�W�����ǂݍ���
	//float version = 0.0f;
	//FileRead_read(&version, sizeof(version), actionH);

	////�t�@�C�����̃T�C�Y
	//int filenamesize = 0;
	//FileRead_read(&filenamesize, sizeof(filenamesize), actionH);

	////�t�@�C����
	//std::string imgfilepath;
	//imgfilepath.resize(filenamesize);
	//FileRead_read(&imgfilepath[0], filenamesize, actionH);

	////���̃A�v���P�[�V��������̑��΃p�X�ɕϊ�
	//auto ipos = imgfilepath.find_first_of("/") + 1;
	//_actionData.imgFilePath = imgfilepath.substr(ipos, imgfilepath.size());

	////�A�N�V������
	//int actionCnt = 0;
	//FileRead_read(&actionCnt, sizeof(actionCnt), actionH);

	//for (int idx = 0; idx < actionCnt; ++idx)
	//{
	//	//�A�N�V�������̐�
	//	int actnamesize = 0;
	//	FileRead_read(&actnamesize, sizeof(actnamesize), actionH);

	//	//�A�N�V������
	//	std::string actname;
	//	actname.resize(actnamesize);
	//	FileRead_read(&actname[0], actnamesize, actionH);

	//	ActionInfo actInfo;

	//	//���[�v���
	//	FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), actionH);

	//	//�J�b�g��
	//	int cutCnt = 0;
	//	FileRead_read(&cutCnt, sizeof(cutCnt), actionH);

	//	//�J�b�g�f�[�^
	//	actInfo.cuts.resize(cutCnt);
	//	for (int i = 0; i < cutCnt; ++i)
	//	{
	//		FileRead_read(&actInfo.cuts[i], sizeof(actInfo.cuts[i]) - sizeof(actInfo.cuts[i].actrects), actionH);

	//		int actrcCnt = 0;
	//		FileRead_read(&actrcCnt, sizeof(actrcCnt), actionH);

	//		if (actrcCnt > 0)
	//		{
	//			actInfo.cuts[i].actrects.resize(actrcCnt);
	//			for (auto& actrect : actInfo.cuts[i].actrects)
	//			{
	//				FileRead_read(&actrect, sizeof(actrect), actionH);
	//			}
	//		}
	//	}
	//	_actionData.actInfo[actname] = actInfo;
	//}


	//FileRead_close(actionH);
}
