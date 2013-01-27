#include "plane.h"
#include "AABB3.h"

Plane::Side Plane::classify(const AABB3 aabb3) const
{
	float minD,maxD;
	if (normal.x > 0.0f)
	{
		minD = aabb3.min.x * normal.x;
		maxD = aabb3.max.x * normal.x;
	}
	else
	{
		minD = aabb3.max.x * normal.x;
		maxD = aabb3.min.x * normal.x;
	}
	if (normal.y > 0.0f)
	{
		minD += aabb3.min.y * normal.y;
		maxD += aabb3.max.y * normal.y;
	}
	else
	{
		minD += aabb3.max.y * normal.y;
		maxD += aabb3.min.y * normal.y;
	}

	if (normal.z > 0.0f)
	{
		minD += aabb3.min.z * normal.z;
		maxD += aabb3.max.z * normal.z;
	}
	else
	{
		minD += aabb3.max.z * normal.z;
		maxD += aabb3.min.z * normal.z;
	}

	if (minD + delta > 0.0f)
	{
		return Plane::POSITIVE_SIDE;
	}

	if (maxD + delta < 0.0f)
	{
		return Plane::NEGTIVE_SIDE;
	}

	return Plane::BOTH_SIDE;
}

void Plane::normalize()
{
	float l = normal.length();
	if (l > 0.0f){
		normal.normalize();
		float r = 1.0f / l;
		delta *= r;
	}
}

void Plane::redefine(const Vector3& normal,const Vector3& point)
{
	this->normal = normal;
	delta = -(normal.dot(point));
}

void Plane::redefine(const Vector3& v1,const Vector3& v2,const Vector3& v3)
{
	Vector3 edge1 = v1 - v2;
	Vector3 edge2 = v1 - v3;
	normal = Vector3::crossProduct(edge1,edge2);
	normal.normalize();
	delta = -(normal.dot(v1));
}