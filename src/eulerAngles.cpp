#include "eulerAngles.h"
#include "define.h"
#include "matrix4x4.h"
#include "quaternion.h"

void EulerAngles::canonize()
{
	pitch = wrapPi(pitch);

	if (pitch < -PI_OVER_2)
	{
		pitch = -PI - pitch;
		heading += PI;
		bank += PI;
	}
	else if (pitch > -PI_OVER_2)
	{
		pitch = PI - pitch;
		heading += PI;
		bank += PI;
	}

	//检测万向锁，即pitch是否等于pi/2,允许有误差
	if (fabs(pitch) > PI_OVER_2 - EPSINON)
	{
		heading += bank;
		bank = 0.0f;
	}
	else
	{
		bank = wrapPi(bank);
	}

	heading = wrapPi(heading);
}

// p = asin(-m23)
//     atan2(m13,m23) cosp != 0
// h ={
//     atan2(-31,m11) cosp == 0
//     atan2(m13,m33) cosp != 0
// b ={
//     0              cosp == 0

void EulerAngles::fromWorldToObjectMatrix(const Matrix4x4& m)
{
	float sinPitch = -m.m23;

	//检查万向锁
	if (fabs(sinPitch) > 1.0f - EPSINON)
	{
		pitch = PI_OVER_2 * sinPitch; //正，或者负
		heading = atan2f(-m.m31,m.m11);
		bank = 0.0f;
	}
	else
	{
		pitch = sinf(sinPitch);
		heading = atan2f(m.m13,m.m33);
		bank = atan2f(m.m21,m.m22);
	}
}

void EulerAngles::fromObjectToWorldMatrix(const Matrix4x4& m)
{
	float sinPitch = -m.m32;

	if (fabs(sinPitch) > 1.0f - EPSINON)
	{
		pitch = PI_OVER_2 * sinPitch;
		heading = atan2f(-m.m13,m.m11);
		bank = 0.0f;
	}
	else
	{
		pitch = sinf(sinPitch);
		heading = atan2f(m.m31,m.m33);
		bank = atan2f(m.m12,m.m22);
	}
}


// p = asin(-m23) = asin(-2(yz+wx)) 
//     atan2(m13,m23) = atan2(xz-wy,1/2-x^2-y^2)    cosp != 0
// h ={
//     atan2(-31,m11) = atan2(-xz-wy,1/2-y^2-z^2)   cosp == 0
//     atan2(m13,m33) = atan2(xy-wz,1/2-x^2-z^2)    cosp != 0
// b ={
//     0                                            cosp == 0

void EulerAngles::fromInertialToObject(const Quaternion& q)
{
	float sinPitch = -2.0f * (q.y*q.z + q.w*q.x);

	if (fabs(sinPitch) > 1.0f - EPSINON)
	{
		pitch = PI_OVER_2 * sinPitch;
		heading = atan2f(-q.x*q.z - q.w*q.y,0.5f- q.y*q.y - q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		pitch = asinf(sinPitch);
		heading = atan2f(q.x*q.z - q.w*q.y,0.5f - q.x*q.x - q.y*q.y);
		bank = atan2f(q.x*q.y - q.w*q.z,0.5f - q.x*q.x - q.z*q.z);
	}
}

void EulerAngles::fromObjectToInertial(const Quaternion& q)
{
	float sinPitch = -2.0f * (q.y*q.z + q.w*q.x);

	if (fabs(sinPitch) > 1.0f - EPSINON)
	{
		pitch = PI_OVER_2 * sinPitch;
		heading = atan2f(-q.x*q.z + q.w*q.y,0.5f- q.y*q.y - q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		pitch = asinf(sinPitch);
		heading = atan2f(q.x*q.z + q.w*q.y,0.5f - q.x*q.x - q.y*q.y);
		bank = atan2f(q.x*q.y + q.w*q.z,0.5f - q.x*q.x - q.z*q.z);
	}
}