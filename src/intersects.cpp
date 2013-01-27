#include "AABB3.h"
#include "plane.h"
#include "ray.h"

bool intersects(const Ray& ray,const AABB3& aabb3,float* ot)
{
	const Vector3& min = aabb3.min;
	const Vector3& max = aabb3.max;
	const Vector3& rayOrg = ray.position;
	const Vector3& rayDir = ray.direction;

	if (rayOrg > min && rayOrg < max)
	{
		if (ot != 0)
			*ot = 0.0f;
		return true;
	}
	
	Vector3 hitpoint;
	bool hit = false;
	float lowt = 0.0f;
	float t;

	//min x
	if (rayOrg.x <= min.x && rayDir.x > 0.0f){
		t = (min.x - rayOrg.x) / rayDir.x;
		if ( t >= 0.0f){
			hitpoint = rayOrg + rayDir * t;
			if (hitpoint.y >= min.y && hitpoint.y <= max.y
				&& hitpoint.z >= min.z && hitpoint.z <= max.z
				&& (!hit || t < lowt)){
					lowt = t;
					hit = true;
			}
		}
	}
	//max x
	if (rayOrg.x >= max.x && rayDir.x < 0.0f){
		t = (rayOrg.x - max.x) / rayDir.x;
		if (t >= 0.0f){
			hitpoint = rayOrg + rayDir * t;
			if (hitpoint.y >= min.y && hitpoint.y <= max.y
				&& hitpoint.z >= min.z && hitpoint.z <= max.z
				&& (!hit || t < lowt)){
					lowt = t;
					hit = true;
			}
		}
	}
	//min y
	if (rayOrg.y <= min.y && rayDir.y > 0.0f){
		t = (min.y - rayOrg.y) / rayDir.y;
		if ( t >= 0.0f){
			hitpoint = rayOrg + rayDir * t;
			if (hitpoint.x >= min.x && hitpoint.x <= max.x
				&& hitpoint.z >= min.z && hitpoint.z <= max.z
				&& (!hit || t < lowt)){
					lowt = t;
					hit = true;
			}
		}
	}
	//max y
	if (rayOrg.y >= max.y && rayDir.y < 0.0f){
		t = (rayOrg.y - max.y) / rayDir.y;
		if ( t >= 0.0f){
			hitpoint = rayOrg + rayDir * t;
			if (hitpoint.x >= min.x && hitpoint.x <= max.x
				&& hitpoint.z >= min.z && hitpoint.z <= max.z
				&& (!hit || t < lowt)){
					lowt = t;
					hit = true;
			}
		}
	}
	//min z
	if (rayOrg.z <= min.z && rayDir.z > 0.0f){
		t = (min.z - rayOrg.z) / rayDir.z;
		if ( t >= 0.0f){
			hitpoint = rayOrg + rayDir * t;
			if (hitpoint.x >= min.x && hitpoint.x <= max.x
				&& hitpoint.y >= min.y && hitpoint.y <= max.y
				&& (!hit || t < lowt)){
					lowt = t;
					hit = true;
			}
		}
	}
	//max z
	if (rayOrg.z >= max.z && rayDir.z < 0.0f){
		t = (rayOrg.z - max.z) / rayDir.z;
		if ( t >= 0.0f){
			hitpoint = rayOrg + rayDir * t;
			if (hitpoint.x >= min.x && hitpoint.x <= max.x
				&& hitpoint.y >= min.y && hitpoint.y <= max.y
				&& (!hit || t < lowt)){
					lowt = t;
					hit = true;
			}
		}
	}

	if (ot != 0)
	{
		*ot = lowt;
	}

	return hit;
}


bool intersects(const Ray& ray,const Plane& plane,float* t)
{
	float d = plane.normal.dot(ray.direction);
	if (abs(d) < EPSINON)
	{
		return false;
	}
	if (t != 0)
	{
		*t = -(plane.delta + ray.position.dot(plane.normal) / d);
	}

	return true;
}

bool intersects(const AABB3& box1,const AABB3& box2,AABB3* out)
{
	if (box1.min.x > box2.max.x)
		return false;
	if (box1.max.x < box2.min.x)
		return false;
	if (box1.min.y > box2.max.y)
		return false;
	if (box1.max.y < box2.min.y)
		return false;
	if (box1.min.z > box2.max.z)
		return false;
	if (box1.max.z < box2.min.z)
		return false;

	if (out != 0)
	{
		AABB3& ob = *out;
		ob.min.x = std::max(box1.min.x,box2.min.x);
		ob.max.x = std::min(box1.max.x,box2.max.x);
		ob.min.y = std::max(box1.min.y,box2.min.y);
		ob.max.y = std::min(box1.max.y,box2.max.y);
		ob.min.z = std::max(box1.min.z,box2.min.z);
		ob.max.z = std::min(box1.max.z,box2.max.z);
	}

	return true;
}

bool intersects(const Ray& ray,const Vector3* v)
{
	return true;
}