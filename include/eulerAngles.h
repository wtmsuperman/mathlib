#ifndef __M_MATH_LIB_EULER_ANGLES__
#define __M_MATH_LIB_EULER_ANGLES__

class Matrix4x4;
class Quaternion;
class Vector3;

class EulerAngles
{
public:
	float heading; //�ƹ��������� y ����yaw,yaw������������y��˳ʱ��Ϊ��
	float pitch; //��x����ת,heading�������������ᣬ˳ʱ��Ϊ��
	float bank; //��z����ת,pitch�������������ᣬ��ʱ��Ϊ��

	//M = hpb; h��ʾheading��ת����p��ʾpitch��ת����b��ʾbank��ת����
	
	EulerAngles(){};
	EulerAngles(float h,float p,float b)
		:heading(h),pitch(p),bank(b)
	{}
	
	void identity()
	{
		heading = pitch = bank = 0.0f;
	}

	//ת��Ϊ����ŷ����
	void canonize();

	void fromObjectToInertial(const Quaternion& q);
	void fromInertialToObject(const Quaternion& q);
	
	//��Ϊ��תֻ���ǽ�λ�ƣ�������λ�ƣ���������������ʱ�ȼ��ڹ�ϵ����
	void fromObjectToWorldMatrix(const Matrix4x4& m);
	void fromWorldToObjectMatrix(const Matrix4x4& m);
};

#endif