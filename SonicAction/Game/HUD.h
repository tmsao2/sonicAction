#pragma once
#include "EventObserver.h"

class HUD :
	public EventObserver
{
private:
	int _coinH;
	int _coinNum = 0;
	int _score = 0;
public:
	HUD();
	~HUD();
	void Draw();
	void Update();
	bool OnNotify(Event* e);
};

