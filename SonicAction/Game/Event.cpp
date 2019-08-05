#include "Event.h"
#include "../Camera.h"


Event::Event(EventQueue& e):_eventQ(e)
{
}


Event::~Event()
{
}

int Event::GetScore()
{
	return 0;
}
