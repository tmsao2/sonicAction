#include "Input.h"
#include <DxLib.h>


Input::Input()
{
	_inputTable.resize(GetJoypadCount()+1);
	_currentInputState.resize(GetJoypadCount()+1);
	_oldInputState.resize(GetJoypadCount()+1);
	padstate.resize(GetJoypadCount()+1);
}


Input::~Input()
{
}

void Input::Update()
{
	GetHitKeyStateAll(keystate);
	for (int i = 0; i < GetJoypadCount(); ++i) 
	{
		padstate[i] = GetJoypadInputState(i + 1);
	}
	_oldInputState = _currentInputState;
	for (auto& input : _inputMap) 
	{
		auto& pno = input.second.first;
		auto& cmd = input.second.second;
		if (input.first.padno == 0) 
		{
			_currentInputState[pno][cmd] = keystate[input.first.code];
		}
		else 
		{
			_currentInputState[pno][cmd] = _currentInputState[pno][cmd] || padstate[input.first.padno - 1] & input.first.code;
		}
	}
}

void Input::AddCommand(int pno, COMMAND cmd, int perino, int code)
{
	_inputTable[pno].emplace(cmd, PeripheralInfo(perino, code));
	_inputMap.emplace(PeripheralInfo(perino, code), std::make_pair(pno, cmd));
	_currentInputState[pno].emplace(cmd, false);
	_oldInputState[pno].emplace(cmd, false);
}

bool Input::IsPressed(int pno, COMMAND cmd) const
{
	auto& cs = _currentInputState[pno];
	if (cs.find(cmd) != cs.end()) 
	{
		return cs.find(cmd)->second;
	}
	return false;
}

bool Input::IsTriggered(int pno, COMMAND cmd) const
{
	auto& cs = _currentInputState[pno];
	auto& os = _oldInputState[pno];
	if ((cs.find(cmd) != cs.end()) && (os.find(cmd) != os.end())) 
	{
		return cs.find(cmd)->second & !os.find(cmd)->second;
	}

	return false;
}

bool Input::IsReleased(int pno, COMMAND cmd) const
{
	auto& cs = _currentInputState[pno];
	auto& os = _oldInputState[pno];
	if ((cs.find(cmd) != cs.end()) && (os.find(cmd) != os.end()))
	{
		return !cs.find(cmd)->second & os.find(cmd)->second;
	}

	return false;
}

bool Input::IsPressing(int pno, COMMAND cmd) const
{
	auto& cs = _currentInputState[pno];
	auto& os = _oldInputState[pno];
	if ((cs.find(cmd) != cs.end()) && (os.find(cmd) != os.end()))
	{
		return cs.find(cmd)->second & os.find(cmd)->second;
	}

	return false;
}

int Input::GetJoypadCount()const
{
	return GetJoypadNum();
}

void Input::SetPlayerNum(int num)
{
	_inputTable.resize(num);
	_currentInputState.resize(num);
}

bool operator<(const PeripheralInfo & lval, const PeripheralInfo & rval)
{
	if (lval.padno == rval.padno) 
	{
		return lval.code < rval.code;
	}
	return lval.padno < rval.padno;
}
