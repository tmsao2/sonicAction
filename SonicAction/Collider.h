#pragma once
#include "Geometry.h"

class Collider
{
public:
	Collider();
	~Collider();
	static bool IsCollided(const Rect& a, const Rect& b);
};

