#ifndef __M_MATH_QUATERNION__
#define __M_MATH_QUATERNION__

#include "define.h"

class Vector3;
class EulerAngles;

class Quaternion
{
public:
	float w,x,y,z;
	Quaternion()
	{
		identity();
	}

	Quaternion(float W,float X,float Y,float Z)
		:w(W),x(X),y(Y),z(Z)
	{
	}

	//四元数模长,主要是用来判断是否是单位四元数
	float length() const
	{
		return sqrt(w*w+x*x+y*y+z*z);
	}

	void normalize()
	{
		float l = sqrt(w*w+x*x+y*y+z*z);
		if ( l > EPSINON)
		{
			float oneOverMag = 1.0f / l;
			w *= oneOverMag;
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}else{
			assert(l <= EPSINON);
			identity();
		}
	}

	void identity()
	{
		w = 1.0f,x=0.0f,y=0.0f,z=0.0f;
	}

	Quaternion operator* (const Quaternion& q) const
	{
		//   w , x , y , z
		//w w^2,wx ,wy ,wz
		//x xw, -1 ,xy ,xz
		//y yw, yx ,-1 ,yz
		//z zw, zx ,zy ,-1

		return Quaternion(
			w*q.w - x*q.x - y*q.y - z*q.z,
			w*q.x + x*q.w + y*q.z - z*q.y,
			w*q.y + y*q.w - x*q.z + z*q.x,
			w*q.z + z*q.w + x*q.y - y*q.x
			);
	}

	Quaternion& operator*= (const Quaternion& q)
	{
		float nw = w*q.w - x*q.x - y*q.y - z*q.z;
		float nx = w*q.x + x*q.w + y*q.z - z*q.y;
		float ny = w*q.y + y*q.w - x*q.z + z*q.x;
		float nz = w*q.z + z*q.w + x*q.y - y*q.x;
		w = nw,x = nx,y = ny, z = nz;
		return *this;
	}

	Quaternion operator+ (const Quaternion& q) const
	{
		return Quaternion(w+q.w,x+q.x,y+q.y,z+q.z);
	}

	Quaternion& operator+= (const Quaternion& q)
	{
		w += q.w;
		x += q.x;
		y += q.y;
		z += q.z;
		return *this;
	}

	void setToRotateX(float theta)
	{
		float thetaOver2 = theta * 0.5f;
		w = cosf(thetaOver2);
		x = sinf(thetaOver2);
		y = 0.0f;
		z = 0.0f;
	}

	void setToRotateY(float theta)
	{
		float thetaOver2 = theta*0.5f;
		w = cosf(thetaOver2);
		x = 0.0f;
		y = sinf(thetaOver2);
		z = 0.0f;
	}

	void setToRotateZ(float theta)
	{
		float thetaOver2 = theta*0.5f;
		w = cosf(thetaOver2);
		x = 0.0f;
		y = 0.0f;
		z = sinf(thetaOver2);
	}

	void setToRotateAxis(const Vector3& axis,float theta);
	void setToRotateObjectToInertial(const EulerAngles& e);
	void setToRotateInertialToObject(const EulerAngles& e);
	
	/*
	If you call this with a dest vector that is close to the inverse
    of this vector, we will rotate 180 degrees around the 'fallbackAxis'
	(if specified, or a generated axis if not) since in this case
	ANY axis of rotation is valid.
	*/
	void setToRatationTo(const Vector3& v1,const Vector3& v2);


	float getRotationAngle() const
	{
		return safeAcos(w) * 2.0f;
	}

	Vector3 getRotationAxis() const;

	Vector3 xAxis() const;
	Vector3 yAxis() const;
	Vector3 zAxis() const;

	static const Quaternion ZERO;
	static const Quaternion IDENTITY;
};

Quaternion slerp(const Quaternion& q1,const Quaternion& q2,float f);

inline Quaternion conjugate(const Quaternion& q)
{
	return Quaternion(q.w,-q.x,-q.y,-q.z);
}
inline float dotProduct(const Quaternion& q,const Quaternion& q1);

#endif