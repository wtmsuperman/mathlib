#include "frustum.h"

#include "AABB3.h"
#include "matrix4x4.h"
#include "vector3.h"
#include "intersects.h"

Frustum::Frustum(const Plane* planes)
{
	for (size_t i=0; i<6; ++i)
	{
		clippingPlanes[i] = planes[i];
	}
}

void Frustum::d3dCalcFromProjAndView(const Matrix4x4& view,const Matrix4x4& proj)
{
	d3dCalcFromMatrix(view * proj);
}

void Frustum::d3dCalcFromMatrix(const Matrix4x4& m)
{
	//left
	Plane& left = clippingPlanes[FRUSTUM_PLANE_LEFT];
	left.normal.x = m.m14 + m.m11;
	left.normal.y = m.m24 + m.m21;
	left.normal.z = m.m34 + m.m31;
	left.delta    = m.m44 + m.m41;
	left.normalize();
	//right
	Plane& right = clippingPlanes[FRUSTUM_PLANE_RIGHT];
	right.normal.x = m.m14 - m.m11;
	right.normal.y = m.m24 - m.m21;
	right.normal.z = m.m34 - m.m31;
	right.delta	   = m.m44 - m.m41;
	right.normalize();
	//bottom
	Plane& bottom = clippingPlanes[FRUSTUM_PLANE_BOTTOM];
	bottom.normal.x = m.m14 + m.m12;
	bottom.normal.y = m.m24 + m.m22;
	bottom.normal.z = m.m34 + m.m32;
	bottom.delta	= m.m44 + m.m42;
	bottom.normalize();
	//top
	Plane& top = clippingPlanes[FRUSTUM_PLANE_TOP];
	top.normal.x = m.m14 - m.m12;
	top.normal.y = m.m24 - m.m22;
	top.normal.z = m.m34 - m.m32;
	top.delta	 = m.m44 - m.m42;
	top.normalize();
	//near
	Plane& near = clippingPlanes[FRUSTUM_PLANE_NEAR];
	near.normal.x = m.m13;
	near.normal.y = m.m23;
	near.normal.z = m.m33;
	near.delta	  = m.m43;
	near.normalize();
	//far
	Plane& far = clippingPlanes[FRUSTUM_PLANE_FAR];
	far.normal.x = m.m14 - m.m13;
	far.normal.y = m.m24 - m.m23;
	far.normal.z = m.m34 - m.m33;
	far.delta	 = m.m44 - m.m43;
	far.normalize();
}

bool Frustum::isInside(const Vector3& point) const
{
	for (size_t i=0; i<6; ++i)
	{
		if (clippingPlanes[i].dotCoord(point) < 0.0f)
			return false;
	}
	return true;
}

bool Frustum::isInside(const AABB3& aabb3) const
{
	for (size_t i=0; i<6; ++i)
	{
		if (clippingPlanes[i].classify(aabb3) == Plane::NEGTIVE_SIDE){
			return false;
		}
	}
	return true;
}