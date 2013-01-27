#include "matrix4x4.h"
#include "vector3.h"
#include "quaternion.h"
#include "eulerAngles.h"

const Matrix4x4 Matrix4x4::IDENTITY(  1.0f,0.0f,0.0f,0.0f
									 ,0.0f,1.0f,0.0f,0.0f
									 ,0.0f,0.0f,1.0f,0.0f
									 ,0.0f,0.0f,0.0f,1.0f);

void Matrix4x4::setupParentToLocal(const Vector3& pos,const EulerAngles& orient)
{
	float sh,sp,sb,ch,cp,cb;
	sinCos(orient.heading,&sh,&ch);
	sinCos(orient.pitch,&sp,&cp);
	sinCos(orient.bank,&sb,&cb);

	m11 =  ch * cb + sh * sp * sb;
	m12 = -ch * sb + sh * sp * cb;
	m13 =  sh * cp;

	m21 = sb * cp;
	m22 = cb * cp;
	m23 = -sp;

	m31 = -sh * cb + ch * sp * sb;
	m32 =  sb * sh + ch * sp * cb;
	m33 =  ch * cp;

	m14=m24=m34=0.0f;
	
	m41 = -(pos.x * m11 + pos.y * m21 + pos.z * m31);
	m42 = -(pos.x * m12 + pos.y * m22 + pos.z * m32);
	m43 = -(pos.x * m13 + pos.y * m23 + pos.z * m33);

	m44 = 1.0f;
}

void Matrix4x4::setupLocalToParent(const Vector3& pos,const EulerAngles& orient)
{
	float sh,sp,sb,ch,cp,cb;
	sinCos(orient.heading,&sh,&ch);
	sinCos(orient.pitch,&sp,&cp);
	sinCos(orient.bank,&sb,&cb);

	m11 =  ch * cb + sh * sp * sb;
	m21 = -ch * sb + sh * sp * cb;
	m31 =  sh * cp;

	m12 = sb * cp;
	m22 = cb * cp;
	m32 = -sp;

	m13 = -sh * cb + ch * sp * sb;
	m23 =  sb * sh + ch * sp * cb;
	m33 =  ch * cp;

	m14=m24=m34=0.0f;
	
	m41 = pos.x;
	m42 = pos.y;
	m43 = pos.z;

	m44 = 1.0f;
}

void Matrix4x4::setupLocalToParent(const Vector3& pos,const Quaternion& q)
{
	float ww = 2.0f * q.w;
	float xx = 2.0f * q.x;
	float yy = 2.0f * q.y;
	float zz = 2.0f * q.z;

	m11 = 1.0f - yy*q.y - zz*q.z;
	m12 = xx*q.y + ww*q.z;
	m13 = xx*q.z - ww*q.y;
	m14 = 0.0f;

	m21 = xx*q.y - ww*q.z;
	m22 = 1.0f - xx*q.x - zz*q.z;
	m23 = yy*q.z + ww*q.x;
	m24 = 0.0f;

	m31 = xx*q.z + ww*q.y;
	m32 = yy*q.z - ww*q.x;
	m33 = 1.0f - xx*q.x - yy*q.y;
	m34 = 0.0f;

	m41 = pos.x,m42 = pos.y, m43 = pos.z, m44 =1.0f;
}

void Matrix4x4::setupParentToLocal(const Vector3& pos,const Quaternion& q)
{
	float ww = 2.0f * q.w;
	float xx = 2.0f * q.x;
	float yy = 2.0f * q.y;
	float zz = 2.0f * q.z;

	m11 = 1.0f - yy*q.y - zz*q.z;
	m21 = xx*q.y + ww*q.z;
	m31 = xx*q.z - ww*q.y;
	m14 = 0.0f;

	m12 = xx*q.y - ww*q.z;
	m22 = 1.0f - xx*q.x - zz*q.z;
	m32 = yy*q.z + ww*q.x;
	m24 = 0.0f;

	m13 = xx*q.z + ww*q.y;
	m23 = yy*q.z - ww*q.x;
	m33 = 1.0f - xx*q.x - yy*q.y;
	m34 = 0.0f;

	m41 = -(pos.x * m11 + pos.y * m21 + pos.z * m31);
	m42 = -(pos.x * m12 + pos.y * m22 + pos.z * m32);
	m43 = -(pos.x * m13 + pos.y * m23 + pos.z * m33);

	m44 = 1.0f;
}

void Matrix4x4::fromQuaternion(const Quaternion& q)
{
	float ww = 2.0f * q.w;
	float xx = 2.0f * q.x;
	float yy = 2.0f * q.y;
	float zz = 2.0f * q.z;

	m11 = 1.0f - yy*q.y - zz*q.z;
	m12 = xx*q.y + ww*q.z;
	m13 = xx*q.z - ww*q.y;
	m14 = 0.0f;

	m21 = xx*q.y - ww*q.z;
	m22 = 1.0f - xx*q.x - zz*q.z;
	m23 = yy*q.z + ww*q.x;
	m24 = 0.0f;

	m31 = xx*q.z + ww*q.y;
	m32 = yy*q.z - ww*q.x;
	m33 = 1.0f - xx*q.x - yy*q.y;
	m34 = 0.0f;

	m41 = m42 = m43 = 0.0f;
	m44 = 1.0f;
}