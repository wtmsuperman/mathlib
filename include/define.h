#ifndef __MATH_DEFINE__
#define __MATH_DEFINE__

#include <math.h>
#include <assert.h>
#include <iostream>

const float PI = 3.1415926f;
const float EPSINON = 0.00001f;
const float k2PI = PI * 2.0f;
const float ONE_OVER_PI = 1.0f / PI;
const float ONE_OVER_2PI = 1.0f / k2PI;
const float PI_OVER_2 = PI * 0.5f;

inline float degreeToRadians(float degree)
{
	return degree / 180.0f * PI;
}

inline float radiansToDegree(float radians)
{
	return radians / PI * 180.0f;
}

inline bool fequal(float a,float b)
{
	return fabs(a-b) <= EPSINON;
}

float safeAcos(float x);

float wrapPi(float theta);

//某些特定平台，同时计算，速度更快
inline void sinCos(float theta,float* outSin,float *outCos)
{
	*outSin = sinf(theta);
	*outCos = cosf(theta);
}

template<class T>
inline T clamp(T val,T minVal,T maxVal)
{
	assert(minVal <= maxVal);
	return std::max(minVal,std::min(val,maxVal));
}

#endif