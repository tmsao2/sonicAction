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

	//�o�[�W�����ǂݍ���
	float version = 0.0f;
	ReadData(&version, sizeof(version), cursor, actdata);

	//�t�@�C�����̃T�C�Y
	int filenamesize = 0;
	ReadData(&filenamesize, sizeof(filenamesize), cursor, actdata);

	//�t�@�C����
	imgpath.resize(filenamesize);
	ReadData(&imgpath[0], filenamesize, cursor, actdata);

	//���̃A�v���P�[�V��������̑��΃p�X�ɕϊ�
	auto ipos = imgpath.find_first_of("/") + 1;
	imgpath = imgpath.substr(ipos, imgpath.size());

	//�A�N�V������
	int actionCnt = 0;
	ReadData(&actionCnt, sizeof(actionCnt), cursor, actdata);

	for (int idx = 0; idx < actionCnt; ++idx)
	{
		//�A�N�V�������̐�
		int actnamesize = 0;
		ReadData(&actnamesize, sizeof(actnamesize), cursor, actdata);

		//�A�N�V������
		std::string actname;
		actname.resize(actnamesize);
		ReadData(&actname[0], actnamesize, cursor, actdata);

		ActionInfo actInfo;

		//���[�v���
		ReadData(&actInfo.isLoop, sizeof(actInfo.isLoop), cursor, actdata);

		//�J�b�g��
		int cutCnt = 0;
		ReadData(&cutCnt, sizeof(cutCnt), cursor, actdata);

		//�J�b�g�f�[�^
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
