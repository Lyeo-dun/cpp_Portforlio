#pragma once
#include "Headers.h"

class MathManager {
public:
	static float GetDistance(const Vector3& _obj, const Vector3& _target)
	{
		float Width = _target.x - _obj.x;
		float Height = _target.y - _obj.y;

		return sqrt((Width * Width) + (Height * Height));
	}

	static bool GetisTriangleRange(const Vector3& _p, const Vector3& c_D1, const Vector3& c_D2)
	{
		Vector3 X = Vector3(c_D1.x - 0, c_D1.y - 21); //�������� A�� ���� ����
		Vector3 Y = Vector3(c_D2.x - 0, c_D2.y - 21); //�������� B�� ���� ����
		Vector3 P = Vector3(_p.x - 0, _p.y - 21); //�������� ������ �� P���� ����

		double Alpa = P.x / X.x;
		double Beta = (P.y * -1) / (Y.y * -1);
		//A(D1) + B(D2) = P => �������������� Ǯ��������� ����� �� �� �ϳ��� 0�̹Ƿ� �׷��Ա��� �� �ʿ䰡 ����
		
		if (P.x == 0 || X.x == 0)
		{
			Alpa = 0;
		}
		if (P.y == 0 || Y.y == 0)
		{
			Beta = 0;
		}

		if ((Alpa >= 0 && Alpa <= 1) && (Beta >= 0 && Beta <= 1) && (Alpa + Beta <= 1))
		{
			return true;
		}

		return false;
	}
};