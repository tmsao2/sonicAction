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
	int padno;	///機器番号
	int code;	///入力コード
	PeripheralInfo(){}
	PeripheralInfo(int p_no, int c) :padno(p_no), code(c) {}

};

bool operator<(const PeripheralInfo& lval, const PeripheralInfo& rval);

class Input
{
private:
	///プレイヤー番号と文字列から実際の機器番号と入力コードを探す
	std::vector<std::multimap<COMMAND, PeripheralInfo>> _inputTable;
	///機器番号と入力コードから対応するプレイヤーと文字列を探す
	std::map<PeripheralInfo, std::pair<int, COMMAND>> _inputMap;

	char keystate[256];
	std::vector<int> padstate;
	///現在の入力情報
	std::vector<std::map<COMMAND, bool>> _currentInputState;
	///1フレーム前の入力情報
	std::vector<std::map<COMMAND, bool>> _oldInputState;

public:
	Input();
	~Input();
	void Update();
	///コマンド追加
	///@param pno プレイヤー番号
	///@param cmd コマンド名 
	///@param perino 機器番号
	///@param code 入力コード
	void AddCommand(int pno, COMMAND cmd, int perino, int code);

	///押している間
	///押した瞬間
	///@param pno プレイヤー番号
	///@param cmd コマンド名 
	bool IsPressed(int pno, COMMAND cmd)const;
	bool IsTriggered(int pno, COMMAND cmd)const;
	bool IsReleased(int pno, COMMAND cmd)const;
	bool IsPressing(int pno, COMMAND cmd)const;

	///パッド数取得
	int GetJoypadCount()const;

	///プレイヤー数設定
	void SetPlayerNum(int num);
};

