#include "Event.h"
#include "../Camera.h"


Event::Event(const Rect& rc, const Camera& c):_rect(rc),_camera(c)
{
}


Event::~Event()
{
}

const Rect & Event::GetCollider()
{
	return _rect;
}
