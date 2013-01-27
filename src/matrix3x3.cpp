#include "matrix3x3.h"
#include "vector3.h"
#include "quaternion.h"
#include "eulerAngles.h"

void Matrix3x3::setupRotate(const EulerAngles& e)
{
	float sh,sp,sb,ch,cp,cb;
	sinCos(e.heading,&sh,&ch);
	sinCos(e.pitch,&sp,&cp);
	sinCos(e.bank,&sb,&cb);

	m11 =  ch * cb + sh * sp * sb;
	m12 = -ch * sb + sh * sp * cb;
	m13 =  sh * cp;

	m21 = sb * cp;
	m22 = cb * cp;
	m23 = -sp;

	m31 = -sh * cb + ch * sp * sb;
	m32 =  sb * sh + ch * sp * cb;
	m33 =  ch * cp;
}

void Matrix3x3::setupRotateTo(const Vector3& axis,float angle)
{
	assert(fabs(axis.length() - 1.0f) < 0.1f);

	float s,c;
	sinCos(angle,&s,&c);

	float a = 1.0f - c;
	float ax = a * axis.x;
	float ay = a * axis.y;
	float az = a * axis.z;

	m11 = ax*axis.x + c;
	m12 = ax*axis.y + axis.z*s;
	m13 = ax*axis.z - axis.y*s;

	m21 = ay*axis.x - axis.z*s;
	m22 = ay*axis.y + c;
	m23 = ay*axis.z + axis.x*s;

	m31 = az*axis.x + axis.y*s;
	m32 = az*axis.y - axis.x*s;
	m33 = az*axis.z + c;
}

void Matrix3x3::fromQuaternion(const Quaternion& q)
{
	float ww = 2.0f * q.w;
	float xx = 2.0f * q.x;
	float yy = 2.0f * q.y;
	float zz = 2.0f * q.z;

	m11 = 1.0f - yy*q.y - zz*q.z;
	m12 = xx*q.y + ww*q.z;
	m13 = xx*q.z - ww*q.y;

	m21 = xx*q.y - ww*q.z;
	m22 = 1.0f - xx*q.x - zz*q.z;
	m23 = yy*q.z + ww*q.x;

	m31 = xx*q.z + ww*q.y;
	m32 = yy*q.z - ww*q.x;
	m33 = 1.0f - xx*q.x - yy*q.y;
}

Vector3 operator*(const Vector3& v,const Matrix3x3& m)
{
	return Vector3(
		 v.x*m.m11 + v.y*m.m21 + v.z*m.m31
		,v.x*m.m12 + v.y*m.m22 + v.z*m.m32
		,v.x*m.m13 + v.y*m.m23 + v.z*m.m33
		);
}