#include "mathlib.h"

const Vector3 Vector3::ZERO(0.0f,0.0f,0.0f);
const Vector3 Vector3::UNIT_X(1.0f,0.0f,0.0f);
const Vector3 Vector3::UNIT_Y(0.0f,1.0f,0.0f);
const Vector3 Vector3::UNIT_Z(0.0f,0.0f,1.0f);

float safeAcos(float x)
{
	if (x <= -1.0f)
		return PI;
	else if (x >= 1.0f)
		return 0.0f;
	else
		return acosf(x);
}

float wrapPi(float theta)
{
	theta += PI;
	theta -= floor(theta * ONE_OVER_2PI) * k2PI;
	theta -= PI;
	return theta;
}

Vector3 randVector3(const Vector3& low,const Vector3& high)
{
	if (low >= high)
		return low;

	return Vector3(randf(low.x,high.x),randf(low.y,high.y),randf(low.z,high.z));
}
