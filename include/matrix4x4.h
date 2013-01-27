#ifndef __M_MATH_LIB_MATRIX4X4__
#define __M_MATH_LIB_MATRIX4X4__

#include "define.h"
#include "vector3.h"

class EulerAngles;
class Quaternion;

class Matrix4x4
{
public:
	union
	{
		struct 
		{
			float m11,m12,m13,m14;
			float m21,m22,m23,m24;
			float m31,m32,m33,m34;
			float m41,m42,m43,m44;
		};
		float m[16];
	};
	

	Matrix4x4()
	{
	}

	Matrix4x4(const Matrix4x4& v)
	{
		memcpy(m,v.m,16 * sizeof(float));
	}

	explicit Matrix4x4(float* m)
	{
		memcpy(this->m,m,16*sizeof(float));
	}

	Matrix4x4(float _11,float _12,float _13,float _14
			,float _21,float _22,float _23,float _24
			,float _31,float _32,float _33,float _34
			,float _41,float _42,float _43,float _44)
	{
		m11=_11,m12=_12,m13=_13,m14=_14;
		m21=_21,m22=_22,m23=_23,m24=_24;
		m31=_31,m32=_32,m33=_33,m34=_34;
		m41=_41,m42=_42,m43=_43,m44=_44;
	}

	void identity()
	{
		m[0]=1.0f,m[1]=0.0f,m[2]=0.0f,m[3]=0.0f;
		m[4]=0.0f,m[5]=1.0f,m[6]=0.0f,m[7]=0.0f;
		m[8]=0.0f,m[9]=0.0f,m[10]=1.0f,m[11]=0.0f;
		m[12]=0.0f,m[13]=0.0f,m[14]=0.0f,m[15]=1.0f;
	}

	void set(float* m)
	{
		memcpy(this->m,m,16*sizeof(float));
	}

	Matrix4x4& operator=(const Matrix4x4& matrix)
	{
		if (&matrix == this)
			return *this;
		else
		{
			memcpy(m,matrix.m,16*sizeof(float));
			return *this;
		}
	}

	Matrix4x4 operator+ (const Matrix4x4& matrix) const
	{
		float rm[16];
		for (size_t i = 0; i < 16; ++i)
		{
			rm[i] = m[i] + matrix.m[i];
		}
		return Matrix4x4(rm);
	}

	Matrix4x4 operator- (const Matrix4x4& matrix) const
	{
		float rm[16];
		for (size_t i = 0; i < 16; ++i)
		{
			rm[i] = m[i] - matrix.m[i];
		}
		return Matrix4x4(rm);
	}

	Matrix4x4 operator* (const Matrix4x4& matrix) const
	{
		float rm[16];
		memset(rm,0,16*sizeof(float));

		for (size_t i=0; i<4; ++i)
		{
			for (size_t j=0; j<4; ++j)
			{
				for (size_t n=0; n<4; ++n)
				{
					rm[i*4+j] += m[i*4+n]*matrix.m[n*4+j];
				}
			}
		}
		return Matrix4x4(rm);
	}

	Matrix4x4 operator* (float f) const
	{
		float rm[16];
		for (size_t i=0; i < 16; ++i)
		{
			rm[i] = m[i] * f;
		}
		return Matrix4x4(rm);
	}

	Matrix4x4 operator/ (float f) const
	{
		assert(f >= EPSINON);
		float invf = 1.0f / f;
		float rm[16];
		for (size_t i=0; i < 16; ++i)
		{
			rm[i] = m[i] * invf;
		}
		return Matrix4x4(rm);
	}

	bool operator== (const Matrix4x4& v) const
	{
		for (size_t i=0 ; i<16; ++i)
		{
			if (!fequal(m[i],v.m[i]))
			{
				return false;
			}
		}
		return true;
	}

	bool operator!= (const Matrix4x4& v) const
	{
		for (size_t i=0 ; i<16; ++i)
		{
			if (fequal(m[i],v.m[i]))
			{
				return false;
			}
		}
		return true;
	}

	Matrix4x4& operator+= (const Matrix4x4& v)
	{
		for (size_t i=0; i<16; ++i)
		{
			m[i] += v.m[i];
		}
		return *this;
	}
	Matrix4x4& operator-= (const Matrix4x4& v)
	{
		for (size_t i=0; i<16; ++i)
		{
			m[i] -= v.m[i];
		}
		return *this;
	}
	Matrix4x4& operator*= (const Matrix4x4& v)
	{
		for (size_t i=0; i<4; ++i)
		{
			for (size_t j=0; j<4; ++j)
			{
				for (size_t n=0; n<4; ++n)
				{
					m[i*4+j] += m[i*4+n]*v.m[n*4+j];
				}
			}
		}
		return *this;
	}
	Matrix4x4& operator*=(float f)
	{
		for (size_t i=0; i<16; ++i)
		{
			m[i] *= f;
		}
		return *this;
	}
	Matrix4x4& operator/=(float f)
	{
		assert(f >= EPSINON);
		float invf = 1.0f / f;
		for (size_t i=0; i < 16; ++i)
		{
			m[i] *= invf;
		}
		return *this;
	}

	float get(size_t i,size_t j) const
	{
		return m[i*4 + j];
	}

	void translate(float x,float y,float z)
	{
		m41 = x,m42 = y,m43 = z,m44 = 1.0f;
	}

	void translate(const Vector3& v)
	{
		m41 = v.x,m42=v.y,m43=v.z,m44=1.0f;
	}

	void setupTranslate(float x,float y,float z)
	{
		m11=1.0f,m12=m13=m14=0.0f;
		m22=1.0f,m21=m23=m24=0.0f;
		m33=1.0f,m31=m32=m34=0.0f;
		m41=x,m42=y,m43=z,m44=1.0f;
	}

	void setupTranslate(const Vector3& v)
	{
		m11=1.0f,m12=m13=m14=0.0f;
		m22=1.0f,m21=m23=m24=0.0f;
		m33=1.0f,m31=m32=m34=0.0f;
		m41=v.x,m42=v.y,m43=v.z,m44=1.0f;
	}

	void setupScale(float s)
	{
		m11=s,m12=m13=m14=0.0f;
		m22=s,m21=m23=m24=0.0f;
		m33=s,m31=m32=m34=0.0f;
		m44=1.0f,m41=m42=m43=0.0f;
	}

	void setupScale(const Vector3& v)
	{
		m11=v.x,m12=m13=m14=0.0f;
		m22=v.y,m21=m23=m24=0.0f;
		m33=v.z,m31=m32=m34=0.0f;
		m44=1.0f,m41=m42=m43=0.0f;
	}

	void setupRotateX(float angle)
	{
		float sine;
		float cose;
		sinCos(angle,&sine,&cose);
		m[5]=cose,m[6]=sine,m[9]=-sine,m[10]=cose;
		m44=1.0f,m41=m42=m43=0.0f;
	};

	void setupRotateY(float angle)
	{
		float sine;
		float cose;
		sinCos(angle,&sine,&cose);
		m[0]=cose,m[2]=-sine,m[8]=sine,m[10]=cose;
		m44=1.0f,m41=m42=m43=0.0f;
	};

	void setupRotateZ(float angle)
	{
		float sine;
		float cose;
		sinCos(angle,&sine,&cose);
		m[0]=cose,m[1]=sine,m[4]=-sine,m[5]=cose;
		m44=1.0f,m41=m42=m43=0.0f;
	};

	Vector3 getTranslation() const
	{
		return Vector3(m41,m42,m43);
	}

	//void setupRotate(const Vector3& axis,float theta);

	void setupLocalToParent(const Vector3& pos,const EulerAngles& orient);
	void setupLocalToParent(const Vector3& pos,const Quaternion& q);
	void setupParentToLocal(const Vector3& pos,const EulerAngles& orient);
	void setupParentToLocal(const Vector3& pos,const Quaternion& q);

	void fromQuaternion(const Quaternion& q);

	static const Matrix4x4 IDENTITY;
};

inline Vector3 getPositionFromParentToLocal(const Matrix4x4& m)
{
	return Vector3(
		-(m.m41*m.m11 + m.m41*m.m12 + m.m43*m.m13),
		-(m.m41*m.m21 + m.m42*m.m22 + m.m43*m.m23),
		-(m.m41*m.m31 + m.m42*m.m32 + m.m43*m.m33)
		);
}


inline Vector3 getPositionFromLocalToParent(const Matrix4x4& m)
{
	return Vector3(m.m41,m.m42,m.m43);
}

inline Vector3 operator* (const Vector3& v,const Matrix4x4& m)
{
	return Vector3(
		 v.x*m.m11 + v.y*m.m21 + v.z*m.m31 + m.m41
		,v.x*m.m12 + v.y*m.m22 + v.z*m.m32 + m.m42
		,v.x*m.m13 + v.y*m.m23 + v.z*m.m33 + m.m43
		);
}

inline Vector3& operator*= (Vector3& v,const Matrix4x4& m)
{
	v = v * m;
	return v;
}

#endif