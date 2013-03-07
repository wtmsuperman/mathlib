#ifndef __M_MATH_LIB_VEC3__
#define __M_MATH_LIB_VEC3__

#include "define.h"
#include "matrix3x3.h"
#include "quaternion.h"

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

	/** Generates a vector perpendicular to this vector (eg an 'up' vector).
            @remarks
                This method will return a vector which is perpendicular to this
                vector. There are an infinite number of possibilities but this
                method will guarantee to generate one of them. If you need more
                control you should use the Quaternion class.
        */
	inline Vector3 perpendicular(void) const
    {
            static const float fSquareZero = (float)(1e-06 * 1e-06);

            Vector3 perp = crossProduct(*this, Vector3::UNIT_X);

            // Check length
            if( perp.squaredLength() < fSquareZero )
            {
                /* This vector is the Y axis multiplied by a scalar, so we have
                   to use another axis.
                */
                perp = this->crossProduct( Vector3::UNIT_Y,*this);
            }
			perp.normalize();

            return perp;
    }

	/** Generates a new random vector which deviates from this vector by a
            given angle in a random direction.
            @remarks
                This method assumes that the random number generator has already
                been seeded appropriately.
            @param
                angle The angle at which to deviate
            @param
                up Any vector perpendicular to this one (which could generated
                by cross-product of this vector and any other non-colinear
                vector). If you choose not to provide this the function will
                derive one on it's own, however if you provide one yourself the
                function will be faster (this allows you to reuse up vectors if
                you call this method more than once)
            @return
                A random vector which deviates from this vector by angle. This
                vector will not be normalised, normalise it if you wish
                afterwards.
        */
        inline Vector3 randomDeviant(
            float theta,
            const Vector3& up = Vector3::ZERO ) const
        {
            Vector3 newUp;

            if (up == Vector3::ZERO)
            {
                // Generate an up vector
                newUp = this->perpendicular();
            }
            else
            {
                newUp = up;
            }

            // Rotate up vector by random amount around this
            Quaternion q;
			q.setToRotateAxis(*this,randf() * k2PI);
			Matrix3x3 r(q);
            newUp = newUp * r;

            // Finally rotate this by given angle around randomised up
			q.setToRotateAxis( newUp, theta );
			r.fromQuaternion(q);
            return (*this) * r;
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