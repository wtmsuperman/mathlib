#ifndef __M_MATH_AABB3__
#define __M_MATH_AABB3__

class Matrix4x4;
class Ray;
class Sphere;

#include "define.h"
#include "vector3.h"
#include "intersects.h"
#include "plane.h"

class AABB3
{
public:
	Vector3 min;
	Vector3 max;
public:
	AABB3()
	{
		makeEmpty();
	}

	Vector3 size() const
	{
		return max - min;
	}

	float xSize() const
	{
		return max.x - min.x;
	}

	float ySize() const
	{
		return max.y - min.y;
	}

	float zSize() const
	{
		return max.z - min.z;
	}

	void makeEmpty()
	{
		min.x = min.y = min.z = FLT_MAX;
		max.x = max.y = max.z = -FLT_MAX;
	}

	void makeInfinity()
	{
		min.x = min.y = min.z = -FLT_MAX;
		max.x = max.y = max.z = FLT_MAX;
	}

	bool isEmpty() const
	{
		return min.x > max.x || min.y > max.y || min.z > max.z;
	}

	Vector3 center() const
	{
		return (max + min) * 0.5f;
	}

	Vector3 corner(int i) const;

	void add(const Vector3& point);
	void add(const AABB3& box);

	void transform(const Matrix4x4& m)
	{
		AABB3 copy(*this);
		setToTransformedBox(copy,m);
	}

	void setToTransformedBox(const AABB3& box,const Matrix4x4& m);

	bool cantains(const Vector3& point) const
	{
		return point.x >= min.x && point.y >= min.y && point.z >= min.z
			&& point.x <= max.x && point.y <= max.y && point.z <= max.z;
	}

	Vector3 closestPointTo(const Vector3& point) const;
	
	bool intersects(const AABB3& box,AABB3* out=0) const
	{
		return ::intersects(*this,box,out);
	}

	Plane::Side intersects(const Plane& plane) const
	{
		return plane.classify(*this);
	}

	bool intersects(const Ray& ray,float* t=0) const
	{
		return ::intersects(ray,*this,t);
	}
};

Vector3 randVector3(const Vector3& low,const Vector3& high);

#endif