#include "mathlib.h"
#include <math.h>

void testMatrix()
{
	float r[16] = {
		2,0,0,3,
		0,3,3,5,
		4,0,0,0,
		0,0,0,1
	};
	Matrix4x4 m(r);

	float t[16]={
		1,1,1,1,
		1,0,0,0,
		1,0,0,0,
		1,1,1,1
	};

	Matrix4x4 tt(t);

	Matrix4x4 s = tt*m;

	for (size_t i=0; i<4; ++i)
	{
		for (size_t j=0; j<4; ++j)
		{
			std::cout << s.m[i*4+j] << ",";
		}
		std::cout << std::endl;
	}

	//std::cout << (s!=m);
}

void testMathFunc()
{
	std::cout << "90 degree:" << degreeToRadians(90)<< ",test:" << (degreeToRadians(90) == PI_OVER_2) << std::endl;
	std::cout << "pi radians:" << radiansToDegree(PI) << ",test:" << (radiansToDegree(PI) == 180) << std::endl;

	std::cout << "1.0f == 1.0000001f,test:" << fequal(1.0f,1.0000001f) << std::endl;
	std::cout << "1.0f != -1.0f,test:" << fequal(1.0f,-1.0f) << std::endl;
	std::cout << "2.0f != 3.0f,test:" << fequal(2.0f,3.0f) << std::endl;
	

	std::cout << "4/3 PI,wrap:" <<wrapPi(4.0f/3.0f * PI) <<std::endl;
	std::cout << "6PI,wrap:" << wrapPi(6.0f*PI) << ",test:"<< fequal(0.0f,wrapPi(6.0f*PI)) << std::endl;
	std::cout << "-10PI,wrap:" << wrapPi(-10.0f*PI) << std::endl;
	std::cout << "3/2 PI,wrap:" << wrapPi(3.0f/2.0f * PI) << ",degree:" << radiansToDegree(wrapPi(3.0f/2.0f * PI)) << std::endl;

	std::cout << "acos(1.0f):" << safeAcos(1.0f) << std::endl;
	std::cout << "acos(2.0f):" << safeAcos(2.0f) << std::endl;
	std::cout << "acos(0.5f):" << safeAcos(0.5f) << ",degree:" << radiansToDegree(safeAcos(0.5f)) << std::endl;
	std::cout << "acos(-0.5f):" << safeAcos(-0.5f) <<  ",degree:" << radiansToDegree(safeAcos(-0.5f)) << std::endl;

	float s,c;
	sinCos(degreeToRadians(60.0f),&s,&c);
	std::cout << "sinCos(60):" << s << "," << c << ",theta:" << radiansToDegree(asinf(s)) << std::endl;
}

void testNewFunc()
{
	std::cout << " 10 > -10 and 10 < 20,return 10:" << clamp(10,-10,20) << std::endl;
	std::cout << " 5 > 6 and 5 < 9,return 6:" << clamp(5,6,9) << std::endl;
	std::cout << " 1 > -2 and 1 < 0,return 0:" << clamp(1,-2,0) << std::endl;

	Vector3 up(0.0f,1.0f,0.0f);
	Vector3 zero = Vector3::ZERO;

	std::cout << radiansToDegree(up.angleBetween(zero)) << std::endl;

	Vector3 _45(1.0f,1.0f,0.0f);
	Vector3 right(1.0f,0.0f,0.0f);
	std::cout << radiansToDegree(_45.angleBetween(right)) << std::endl;

	Vector3 _111(1.0f,1.0f,1.0f);
	std::cout << radiansToDegree(_111.angleBetween(zero)) << std::endl;
}


void testAABB()
{
	AABB3 boundingBox;
	std::cout << "test isEmpty() : " << boundingBox.isEmpty() << std::endl;
	boundingBox.add(Vector3(1.0f,1.0f,1.0f));
	std::cout << "test add point: " << boundingBox.xSize() << std::endl;
}
int main()
{
	//testMathFunc();
	//testNewFunc();
	testAABB();
	system("pause");
	return 0;
}