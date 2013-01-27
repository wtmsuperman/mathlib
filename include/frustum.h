#ifndef __M_MATH_FRUSTUM__
#define __M_MATH_FRUSTUM__

class Vector3;
class AABB3;
class Matrix4x4;

#include "plane.h"

class Frustum
{
public:
	enum FrustumPlane
	{
		FRUSTUM_PLANE_NEAR   = 0,
        FRUSTUM_PLANE_FAR    = 1,
        FRUSTUM_PLANE_LEFT   = 2,
        FRUSTUM_PLANE_RIGHT  = 3,
        FRUSTUM_PLANE_TOP    = 4,
        FRUSTUM_PLANE_BOTTOM = 5
	};

	Frustum(){}
	~Frustum(){}
	explicit Frustum(const Plane* planes);


	/**************************************************
	//Calculate the frustum clipping planes
	//following the directx roles
	//the matrix could be prjection matrix , the combined view and projection matrices
	//or the combined world, view, and projection matrices
	//the algorithm see:
	//http://www8.cs.umu.se/kurser/5DV051/HT12/lab/plane_extraction.pdf
	**************************************************/
	void d3dCalcFromMatrix(const Matrix4x4& m);

	/**************************************************
	//Calculate from view matrix and projection matrix
	//following the directx roles
	//the clipping planes would in the world space
	**************************************************/
	void d3dCalcFromProjAndView(const Matrix4x4& view,const Matrix4x4& proj);

	/**************************************************
	//Calculate from view matrix and projection matrix
	//following the directx roles
	//the clipping planes would in the world space
	//
	//not finished yet
	**************************************************/
	void oglCalcFromProjAndView(const Matrix4x4& proj,const Matrix4x4& view);

	bool isInside(const Vector3& point) const;
	bool isInside(const AABB3& aabb3) const;

	Plane clippingPlanes[6];
};

#endif