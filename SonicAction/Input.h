#pragma once
#include "Geometry.h"
#include <string>
#include <map>
#include <vector>

enum class COMMAND
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	BACK,
	FRONT,
	ROTATE,
	OK,
	PAUSE,
	JUMP,
	ATTACK
};

struct PeripheralInfo
{
	int padno;	///�@��ԍ�
	int code;	///���̓R�[�h
	PeripheralInfo(){}
	PeripheralInfo(int p_no, int c) :padno(p_no), code(c) {}

};

bool operator<(const PeripheralInfo& lval, const PeripheralInfo& rval);

class Input
{
private:
	///�v���C���[�ԍ��ƕ����񂩂���ۂ̋@��ԍ��Ɠ��̓R�[�h��T��
	std::vector<std::multimap<COMMAND, PeripheralInfo>> _inputTable;
	///�@��ԍ��Ɠ��̓R�[�h����Ή�����v���C���[�ƕ������T��
	std::map<PeripheralInfo, std::pair<int, COMMAND>> _inputMap;

	char keystate[256];
	std::vector<int> padstate;
	///���݂̓��͏��
	std::vector<std::map<COMMAND, bool>> _currentInputState;
	///1�t���[���O�̓��͏��
	std::vector<std::map<COMMAND, bool>> _oldInputState;

public:
	Input();
	~Input();
	void Update();
	///�R�}���h�ǉ�
	///@param pno �v���C���[�ԍ�
	///@param cmd �R�}���h�� 
	///@param perino �@��ԍ�
	///@param code ���̓R�[�h
	void AddCommand(int pno, COMMAND cmd, int perino, int code);

	///�����Ă����
	///�������u��
	///@param pno �v���C���[�ԍ�
	///@param cmd �R�}���h�� 
	bool IsPressed(int pno, COMMAND cmd)const;
	bool IsTriggered(int pno, COMMAND cmd)const;
	bool IsReleased(int pno, COMMAND cmd)const;
	bool IsPressing(int pno, COMMAND cmd)const;

	///�p�b�h���擾
	int GetJoypadCount()const;

	///�v���C���[���ݒ�
	void SetPlayerNum(int num);
};

