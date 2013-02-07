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
inline T clamp(const T& val,const T& minVal,const T maxVal)
{
	assert(minVal <= maxVal);
	return std::max<T>(minVal,std::min<T>(val,maxVal));
}

//remeber to seed by call srand()

inline float randf(float low,float high)
{
	if (low >= high)
		return low;
	return (high-low) * ((rand()%10000) * 0.0001f) + low;
}

inline long randl(long low,long high)
{
	if (low >= high)
		return low;
	return (long)( (high-low) * ((rand()%10000) * 0.0001f) + low);
}

#endif