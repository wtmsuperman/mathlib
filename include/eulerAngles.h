#ifndef __M_MATH_LIB_EULER_ANGLES__
#define __M_MATH_LIB_EULER_ANGLES__

class Matrix4x4;
class Quaternion;
class Vector3;

class EulerAngles
{
public:
	float heading; //绕惯性坐标轴 y 类似yaw,yaw绕物体坐标轴y，顺时针为正
	float pitch; //绕x轴旋转,heading后，绕物体坐标轴，顺时针为正
	float bank; //绕z轴旋转,pitch后，绕物体坐标轴，逆时针为正

	//M = hpb; h表示heading旋转矩阵，p表示pitch旋转矩阵，b表示bank旋转矩阵
	
	EulerAngles(){};
	EulerAngles(float h,float p,float b)
		:heading(h),pitch(p),bank(b)
	{}
	
	void identity()
	{
		heading = pitch = bank = 0.0f;
	}

	//转换为限制欧拉角
	void canonize();

	void fromObjectToInertial(const Quaternion& q);
	void fromInertialToObject(const Quaternion& q);
	
	//因为旋转只考虑角位移，而无视位移，所以世界坐标这时等价于关系坐标
	void fromObjectToWorldMatrix(const Matrix4x4& m);
	void fromWorldToObjectMatrix(const Matrix4x4& m);
};

#endif