#pragma once
#include <vector>
#include "../Geometry.h"

class Camera;
class Actor;

enum class EdgeType 
{
	none,
	left,
	right,
	both
};

struct Terrain
{
	EdgeType type;
	Segment seg;
	Terrain(){}
	Terrain(EdgeType t, const Segment& s) :type(t), seg(s){}
	Terrain(EdgeType t, const Vector2f& posa,
		const Vector2f& posb) :type(t), seg(posa,posb) {}
};

class Ground
{
private:
	int _imgH;
	int _lavaH,_lava2H;
	const Camera& _camera;
	std::vector<Terrain> _terrain;

	void DrawBottomGround(const Vector2f& s_pos, const Vector2f& e_pos, EdgeType t);

public:
	Ground(const Camera& c);
	~Ground();
	void Draw();
	float GetGroundY(Actor* actor,float& grad,Vector2f& v)const;
	int GetDeadLine()const;
	void AddSegment(const Segment& s,EdgeType t);
	void AddSegment(const Vector2f& posA, const Vector2f& posB, EdgeType t);
};

