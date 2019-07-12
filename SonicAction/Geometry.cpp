#include "Geometry.h"
#include <DxLib.h>
#include <cmath>

Size::Size() : w(0), h(0) {}
Size::Size(int inx, int iny):w(inx),h(iny) {}

Rect::Rect() : center(0, 0), size(0, 0) {}
Rect::Rect(int x, int y, int w, int h):center(x,y),size(w,h) {}
Rect::Rect(const Vector2 & pos, const Size & sz) : center(pos), size(sz) {}

const int Rect::Left() const
{
	return center.x - size.w / 2;
}

const int Rect::Right() const
{
	return center.x + size.w / 2;
}

const int Rect::Top() const
{
	return center.y - size.h / 2;
}

const int Rect::Bottom() const
{
	return center.y + size.h / 2;
}

Size Rect::OverlapSize(Rect ra, Rect rb)
{
	auto w = min(ra.Right(), rb.Right()) - max(ra.Left(), rb.Left());
	auto h = min(ra.Bottom(), rb.Bottom()) - max(ra.Top(), rb.Top());
	return Size(w, h);
}

void Rect::Draw(unsigned int color)
{
	DrawBox(Left(), Top(), Right(), Bottom(), color, false);
}

void Rect::Draw(const Vector2 & offset, unsigned int color)
{

}


void Vector2f::Zero()
{
	x = y = 0;
}

float Vector2f::Magnitude() const
{
	return sqrt(x * x + y * y);
}

void Vector2f::Normalize()
{
	float m = Magnitude();
	x = x / m;
	y = y / m;
}

const Vector2f Vector2f::Normalized() const
{
	float size = Magnitude();

	if (size == 0)
		return Vector2f();

	return Vector2f(x / size, y / size);
}

const VECTOR Vector2f::V_Cast() const
{
	return VGet(x, y, 0);
}

Vector2f operator+(const Vector2f & lv, const Vector2f rv)
{
	return Vector2f(lv.x + rv.x, lv.y + rv.y);
}

Vector2f operator-(const Vector2f & lv, const Vector2f rv)
{
	return Vector2f(lv.x - rv.x, lv.y - rv.y);
}

Vector2f operator-(const Vector2f & lv, const float rv) {
	return Vector2f(lv.x - rv, lv.y - rv);
}

Vector2f operator-(const Vector2f & lv)
{
	return Vector2f(-lv.x, -lv.y);
}

Vector2f operator*(const Vector2f & lv, const float rv)
{
	return Vector2f(lv.x * rv, lv.y * rv);
}

Vector2f operator*(const float lv, const Vector2f rv)
{
	return Vector2f(lv * rv.x, lv * rv.y);
}

Vector2f operator/(const Vector2f & lv, const float rv)
{
	return Vector2f(lv.x / rv, lv.y / rv);
}

Vector2f operator/(const Vector2f & lv, const Vector2f & rv) {
	return Vector2f(lv.x / rv.x, lv.y / rv.y);
}

float Dot(const Vector2f & v1, const Vector2f & v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Cross(const Vector2f & v1, const Vector2f & v2)
{
	return ((v1.x * v2.y) - (v2.x * v1.y));
}

Circle::Circle():pos(0,0),radius(0){}

Circle::Circle(float x, float y, float r) : pos(x, y), radius(r) {}

Circle::Circle(const Vector2f & p, float r) : pos(p), radius(r) {}

void Circle::Draw(unsigned int color)
{
	DrawCircle(static_cast<int>(pos.x), static_cast<int>(pos.y), radius, color,false);
}

Segment::Segment() :start(0, 0), end(0, 0) {}

Segment::Segment(const Vector2f & p1, const Vector2f & p2) : start(p1), end(p2) {}

Segment::Segment(float ax, float ay, float bx, float by) : start(ax, ay), end(bx, by) {}

void Segment::Draw(unsigned int color)
{
	DrawLine(start.x, start.y, end.x, end.y, color);
}

Geometry::Geometry()
{
}

Geometry::~Geometry()
{
}

Vector2 operator+(const Vector2 & lv, const Vector2 rv)
{
	return Vector2(lv.x + rv.x, lv.y + rv.y);
}

Vector2 operator-(const Vector2 & lv, const Vector2 rv)
{
	return Vector2(lv.x - rv.x, lv.y - rv.y);
}

Vector2 operator-(const Vector2 & lv, const int rv)
{
	return Vector2(lv.x - rv, lv.y - rv);
}

Vector2 operator-(const Vector2 & lv)
{
	return Vector2(-lv.x, -lv.y);
}

Vector2 operator*(const Vector2 & lv, const int rv)
{
	return Vector2(lv.x * rv, lv.y * rv);
}

Vector2 operator*(const int lv, const Vector2 rv)
{
	return Vector2(lv * rv.x, lv * rv.y);
}

Vector2 operator/(const Vector2 & lv, const int rv)
{
	return Vector2(lv.x / rv, lv.y / rv);
}

Vector2 operator/(const Vector2 & lv, const Vector2 & rv)
{
	return Vector2(lv.x / rv.x, lv.y / rv.y);
}
