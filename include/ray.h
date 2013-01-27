#ifndef __M_MATH_RAY__
#define __M_MATH_RAY__

#include "vector3.h"
#include "intersects.h"

class Ray
{
public:
	Vector3 position;
	Vector3 direction;

	Ray(const Vector3& pos,const Vector3& dir):
			position(pos),direction(dir)
	{}
	Ray()
	{}

	Vector3 getPoint(float t) const
	{
		return position + direction * t;
	}

	bool intersects(const AABB3& aabb,float* t=0) const
	{
		return ::intersects(*this,aabb,t);
	}

	bool intersects(const Plane& plane,float* t=0) const
	{
		return ::intersects(*this,plane,t);
	}
};

#endif