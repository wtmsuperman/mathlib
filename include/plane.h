#ifndef __M_MATH_PLANE__
#define __M_MATH_PLANE__

#include "vector3.h"
class AABB3;

/************************************
//defination p*n + d = 0
************************************/
class Plane
{
public:
	enum Side
	{
		POSITIVE_SIDE,
		NEGTIVE_SIDE,
		NO_SIDE,
		BOTH_SIDE,
	};

	Vector3 normal;
	float delta;

	Plane(const Vector3& n,float d)
		:normal(n),delta(d)
	{}

	Plane(float a,float b,float c,float d)
		:normal(a,b,c),delta(d)
	{}

	Plane()
	{
		normal = Vector3::ZERO;
		delta = 0.0f;
	}

	Plane(const Vector3& normal,const Vector3 point)
	{
		redefine(normal,point);
	}

	Plane(const Vector3& v1,const Vector3& v2,const Vector3& v3)
	{
		redefine(v1,v2,v3);
	}

	void redefine(const Vector3& normal,const Vector3& point);
	void redefine(const Vector3& v1,const Vector3& v2,const Vector3& v3);

	float dotCoord(const Vector3& point) const
	{
		return normal.dot(point) + delta;
	}

	float getDistance(const Vector3& point) const
	{
		return dotCoord(point);
	}

	Side classify(const Vector3& point) const
	{
		float t = dotCoord(point);

		if (t < 0.0f){
			return NEGTIVE_SIDE;
		}
		else if (t > 0.0f){
			return POSITIVE_SIDE;
		}
		else{
			return NO_SIDE;
		}

	}

	void normalize();

	Side classify(const AABB3 aabb3) const;
};

#endif