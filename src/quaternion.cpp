#include "quaternion.h"
#include "vector3.h"
#include "eulerAngles.h"
#include "matrix4x4.h"
#include <math.h>
#include <assert.h>

const Quaternion Quaternion::IDENTITY(1.0f,0.0f,0.0f,0.0f);
const Quaternion Quaternion::ZERO(0.0f,0.0f,0.0f,0.0f);

void Quaternion::setToRotateAxis(const Vector3& axis,float theta)
{
	assert(fabs(axis.length() - 1.0f) < 0.01f); //aixs must be normalized

	float thetaOver2 = theta * 0.5f;
	float sinThetaOver2 = sinf(thetaOver2);

	w = cosf(thetaOver2);
	x = sinThetaOver2 * axis.x;
	y = sinThetaOver2 * axis.y;
	z = sinThetaOver2 * axis.z;
}

void Quaternion::setToRotateInertialToObject(const EulerAngles& e)
{
	float sp,sb,sh;
	float cp,cb,ch;	
	sinCos(e.heading*0.5f,&sh,&ch);
	sinCos(e.pitch*0.5f,&sp,&cp);
	sinCos(e.bank*0.5f,&sb,&cb);

	w = ch*cp*cb + sh*sp*sb;
	x = -ch*sp*cb - sh*cp*sb;
	y = ch*sp*sb - sh*cp*cb;
	z = sh*sp*cb - ch*cp*sb;
}

void Quaternion::setToRotateObjectToInertial(const EulerAngles& e)
{
	float sp,sb,sh;
	float cp,cb,ch;
	sinCos(e.heading*0.5f,&sh,&ch);
	sinCos(e.pitch*0.5f,&sp,&cp);
	sinCos(e.bank*0.5f,&sb,&cb);

	w = ch*cp*cb + sh*sp*sb;
	x = ch*sp*cb + sh*cp*sb;
	y = -ch*sp*sb + sh*cp*cb;
	z = -sh*sp*cb + ch*cp*sb;
}

Vector3 Quaternion::getRotationAxis() const
{
	// w = cos(theta/2); sin(theta/2)^2 = 1 - w^2;
	float sinThetaOver2sp = 1 - w*w;
	//¾«¶ÈÓÐ´íÎó
	if (sinThetaOver2sp <= EPSINON)
	{
		return Vector3(1.0f,0.0f,0.0f);
	}

	float oneOverSinOneThetaOver2 = 1.0f / sqrt(sinThetaOver2sp);
	return Vector3(x*oneOverSinOneThetaOver2,y*oneOverSinOneThetaOver2,z*oneOverSinOneThetaOver2);
}

float dotProdcut(const Quaternion& q0,const Quaternion& q1)
{
	return q0.w * q1.w + q0.x * q1.x + q0.y*q1.y + q0.z*q1.z;
}

Quaternion slerp(const Quaternion& q1,const Quaternion& q2,float t)
{
	if (t <= 0.0f)
		return q1;
	if (t >= 1.0f)
		return q2;


	float cosOm = dotProdcut(q1,q2);
	assert(cosOm < 1.1f);
	float q2w = q2.w;
	float q2x = q2.x;
	float q2y = q2.y;
	float q2z = q2.z;

	if (cosOm < 0.0f)
	{
		q2w = -q2w;
		q2x = -q2x;
		q2y = -q2y;
		q2z = -q2z;
	}

	float k0,k1;

	if (cosOm > 0.9999f)
	{
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		float sinOm = 1 - cosOm*cosOm;
		float om = atan2f(sinOm,cosOm);
		float oneOverSinOm = 1 / sinf(om);

		k0 = sinf((1.0f-t)*om) * oneOverSinOm;
		k1 = sinf(t*om) * oneOverSinOm;
	}

	Quaternion result;
	result.w = k0 * q1.w + k1 * q2.w;
	result.x = k0 * q1.x + k1 * q2.x;
	result.y = k0 * q1.y + k1 * q2.y;
	result.z = k0 * q1.z + k1 * q2.z;
	return result;
}

Vector3 Quaternion::xAxis() const
{
	float ww = 2.0f * w;
	float xx = 2.0f * x;
	float yy = 2.0f * y;
	float zz = 2.0f * z;
	return Vector3(1.0f - yy*y - zz*z,xx*y + ww*z, xx*z - ww*y);
}

Vector3 Quaternion::yAxis() const
{
	float ww = 2.0f * w;
	float xx = 2.0f * x;
	float yy = 2.0f * y;
	float zz = 2.0f * z;
	return Vector3(xx*y - ww*z, 1.0f - xx*x - zz*z, yy*z + ww*x);
}

Vector3 Quaternion::zAxis() const
{
	float ww = 2.0f * w;
	float xx = 2.0f * x;
	float yy = 2.0f * y;
	float zz = 2.0f * z;

	return Vector3(xx*z + ww*y,yy*z - ww*x, 1.0f - xx*x - yy*y);
}

void Quaternion::setToRatationTo(const Vector3& v1,const Vector3& v2)
{
	/*
	http://www.euclideanspace.com/maths/algebra/vectors/angleBetween/index.htm
	*/

	float dot = v1.dot(v2);

	if (dot <= (EPSINON - 1.0f))
	{
		Vector3 vn = v1;
		vn.normalize();
		Vector3 c = Vector3::crossProduct(vn,Vector3::UNIT_X);
		if (c.isZeroLength())
		{
			c = Vector3::crossProduct(vn,Vector3::UNIT_Y);
		}
		c.normalize();
		setToRotateAxis(c,PI);
	}
	else
	{
		Vector3 c = Vector3::crossProduct(v1,v2);
		w = sqrtf(v1.squaredLength()*v2.squaredLength()) + dot;
		x = c.x;
		y = c.y;
		z = c.z;
		normalize();
	}
}