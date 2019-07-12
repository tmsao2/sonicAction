#include "Collider.h"

Collider::Collider()
{
}


Collider::~Collider()
{
}

bool Collider::IsCollided(const Rect& arc, const Rect& brc)
{
	return (abs(arc.center.y - brc.center.y) < (arc.Height() + brc.Height()) / 2 &&
		abs(arc.center.x - brc.center.x) < (arc.Width() + brc.Width()) / 2);
}
