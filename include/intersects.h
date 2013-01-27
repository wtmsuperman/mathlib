#ifndef __M_MATH_INTERSECTS__
#define __M_MATH_INTERSECTS__

class Ray;
class AABB3;
class Vector3;
class Plane;

bool intersects(const Ray& ray,const AABB3& aabb3,float* t=0);
bool intersects(const Ray& ray,const Plane& plane,float* t=0);

bool intersects(const AABB3& box1,const AABB3& box2,AABB3* out=0);

// collision test for the ray and the mesh.
// param:
// Ray& ray
// Vector* v the array of mesh vertex
bool intersects(const Ray& ray,const Vector3* v);

#endif