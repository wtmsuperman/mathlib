#include "AABB3.h"
#include "matrix4x4.h"

void AABB3::add(const Vector3& point)
{
	if (min.x > point.x)
		min.x = point.x;
	if (min.y > point.y)
		min.y = point.y;
	if (min.z > point.z)
		min.z = point.z;
	if (max.x < point.x)
		max.x = point.x;
	if (max.y < point.y)
		max.y = point.y;
	if (max.z < point.z)
		max.z = point.z;
}

void AABB3::add(const AABB3& box)
{
	if (min.x > box.min.x)
		min.x = box.min.x;
	if (min.y > box.min.y)
		min.y = box.min.y;
	if (min.z > box.min.z)
		min.z = box.min.z;
	if (max.x < box.max.x)
		max.x = box.max.x;
	if (max.y < box.max.y)
		max.y = box.max.y;
	if (max.z < box.max.z)
		max.z = box.max.z;
}

Vector3 AABB3::closestPointTo(const Vector3& p) const
{
	Vector3 r;
	if (p.x < min.x)
		r.x = min.x;
	else if (p.x > max.x)
		r.x = max.x;
	else
		r.x = p.x;

	if (p.y < min.y)
		r.y = min.y;
	else if (p.y > max.y)
		r.y = max.y;
	else
		r.y = p.y;

	if (p.z < min.z)
		r.z = min.z;
	else if (p.z > max.z)
		r.z = max.z;
	else
		r.z = p.z;

	return r;
}

void AABB3::setToTransformedBox(const AABB3& box,const Matrix4x4& m)
{
	if (box.isEmpty())
	{
		makeEmpty();
		return;
	}


	min = max = m.getTranslation();

	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j=0; j < 3; ++j)
		{
			float mm = m.get(i,j);
			if (mm > 0.0f)
			{
				min[j] += mm * box.min[i];
				max[j] += mm * box.max[i];
			}
			else
			{
				min[j] += mm * box.max[i];
				max[j] += mm * box.min[i];
			}
		}
	}

	/*
	Vector3 oldMin, oldMax, currentCorner;

	// Getting the old values so that we can use the existing merge method.
	oldMin = min;
	oldMax = max;

	// reset
	makeEmpty();

	// We sequentially compute the corners in the following order :
	// 0, 6, 5, 1, 2, 4 ,7 , 3
	// This sequence allows us to only change one member at a time to get at all corners.

	// For each one, we transform it using the matrix
	// Which gives the resulting point and merge the resulting point.

	// First corner 
	// min min min
	currentCorner = oldMin;
	add( currentCorner * m);

	// min,min,max
	currentCorner.z = oldMax.z;
	add(  currentCorner * m);

	// min max max
	currentCorner.y = oldMax.y;
	add( currentCorner * m );

	// min max min
	currentCorner.z = oldMin.z;
	add( currentCorner * m );

	// max max min
	currentCorner.x = oldMax.x;
	add( currentCorner * m );

	// max max max
	currentCorner.z = oldMax.z;
	add( currentCorner * m );

	// max min max
	currentCorner.y = oldMin.y;
	add( currentCorner * m );

	// max min min
	currentCorner.z = oldMin.z;
	add( currentCorner * m );
	*/
}

Vector3 AABB3::corner(int i ) const
{
	assert(i >= 0 && i <= 7);
	return Vector3(
		(i & 1) ? max.x : min.x,
		(i & 2) ? max.y : min.y,
		(i & 4) ? max.z : min.z
		);
}