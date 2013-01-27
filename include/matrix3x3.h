#ifndef __M_MATH_MATRIX3X3__
#define __M_MATH_MATRIX3X3__

#include "define.h"

class Vector3;
class Quaternion;
class EulerAngles;

class Matrix3x3
{
public:
	union
	{
		float m[9];
		struct{
		float m11,m12,m13;
		float m21,m22,m23;
		float m31,m32,m33;
		};
	};

	explicit Matrix3x3(float* mtrix)
	{
		memcpy(m,mtrix,sizeof(float) * 9);
	}

	Matrix3x3()
	{}

	Matrix3x3(const Matrix3x3& val)
	{
		memcpy(m,val.m,sizeof(float) * 9);
	}

	explicit Matrix3x3(const Quaternion& q)
	{
		fromQuaternion(q);
	}

	Matrix3x3(const Vector3& axis,float angle)
	{
		setupRotateTo(axis,angle);
	}

	Matrix3x3(float _11,float _12,float _13
			,float _21,float _22,float _23
			,float _31,float _32,float _33
			)
			:m11(_11),m12(_12),m13(_13)
			,m21(_21),m22(_22),m23(_23)
			,m31(_31),m32(_32),m33(_33)
	{}

	Matrix3x3& operator=(const Matrix3x3& val)
	{
		if (&val == this)
			return *this;
		else
		{
			memcpy(m,val.m,sizeof(float) * 9);
			return *this;
		}	
	}

	void identity()
	{
		m11 = m22 = m33 = 1.0f;
		m12 = m13 = m21 = m23 = m31 = m32 = 0.0f;
	}

	void setupRotate(const EulerAngles& e);
	void setupRotateTo(const Vector3& axis,float angle);
	void fromQuaternion(const Quaternion& q);

	void transpose()
	{
		std::swap(m12,m21);
		std::swap(m13,m31);
		std::swap(m23,m32);
	}

	Matrix3x3 transposeCopy()
	{
		return Matrix3x3(m11,m21,m31
						,m12,m22,m32
						,m13,m23,m33);
	}
};

Vector3 operator* (const Vector3& v,const Matrix3x3& m);

#endif