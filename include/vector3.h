#ifndef __M_MATH_LIB_VEC3__
#define __M_MATH_LIB_VEC3__

#include "define.h"

class Vector3
{
public:
	union
	{
		struct
		{
			float x,y,z;
		};
		float v[3];
	};

	Vector3() : x(0.0f),y(0.0f),z(0.0f)
	{

	}
	Vector3(float fx,float fy,float fz)
		:x(fx),y(fy),z(fz)
	{
	}

	float length() const
	{
		return sqrtf(x*x + y*y + z*z);
	}

	float squaredLength() const
	{
		return x*x + y*y + z*z;
	}

	Vector3& operator= (const Vector3& val)
	{
		x = val.x;
		y = val.y;
		z = val.z;
		return *this;
	}

	Vector3 operator* (float v) const
	{
		return Vector3(x*v,y*v,z*v);
	}

	Vector3 operator/ (float v) const
	{
		assert(v != EPSINON);
		float rv = 1.0f/ v;
		return Vector3(x*rv,y*rv,z*rv);
	}

	Vector3 operator+ (const Vector3& v) const
	{
		return Vector3(x+v.x,y+v.y,z+v.z);
	}

	Vector3 operator- (const Vector3& v) const
	{
		return Vector3(x-v.x,y-v.y,z-v.z);
	}

	Vector3& operator+= (const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& operator-= (const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3& operator*= (float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	Vector3& operator /= (float f)
	{
		assert(f != EPSINON);
		float rf = 1.0f / f;
		x *= rf;
		y *= rf;
		z *= rf;
		return *this;
	}

	Vector3 operator -() const
	{
		return Vector3(-x,-y,-z);
	}

	bool operator > (const Vector3& v) const
	{
		return x > v.x && y > v.y && z > v.z;
	}

	bool operator >= (const Vector3& v) const 
	{
		return x >= v.x && y >= v.y && z >= v.z;
	}

	bool operator < (const Vector3& v) const
	{
		return x < v.x && y < v.y && z < v.z;
	}

	bool operator <= (const Vector3& v) const
	{
		return x <= v.x && y < v.y && z <= v.z;
	}

	float& operator[] (size_t i)
	{
		return v[i];
	}

	float operator[] (size_t i) const
	{
		return v[i];
	}

	float dot(const Vector3& v) const
	{
		return x*v.x + y*v.y + z*v.z;
	}

	void normalize()
	{
		float l = length();
		assert(l != EPSINON);
		float r = 1.0f / l;
		x *= r;
		y *= r;
		z *= r;
	}

	float distance(const Vector3& v) const
	{
		return (*this - v).length();
	}

	float squaredDistance(const Vector3& v) const
	{
		return (*this - v).squaredLength();
	}

	float angleBetween(const Vector3& v) const
	{
		float magMul = length() * v.length();
		if (magMul < EPSINON)
			magMul = EPSINON;

		float costheta = dot(v) / magMul;
		return safeAcos(costheta);
	}

	bool isZeroLength() const
	{
		return (squaredLength() == EPSINON * EPSINON);
	}

	bool operator== (const Vector3& v) const
	{
		return fequal(x,v.x) && fequal(y,v.y) && fequal(z,v.z);
	}

	bool operator!= (const Vector3& v) const
	{
		return !fequal(x,v.x) || !fequal(y,v.y) || !fequal(z,v.z);
	}

	static const Vector3 ZERO;
	static const Vector3 UNIT_X;
	static const Vector3 UNIT_Y;
	static const Vector3 UNIT_Z;

	static Vector3 crossProduct(const Vector3& v1,const Vector3& v2)
	{
		return Vector3(v1.y * v2.z - v1.z * v2.y
					,v1.z * v2.x - v1.x * v2.z
					,v1.x * v2.y - v1.y * v2.x);
	}
};
#endif