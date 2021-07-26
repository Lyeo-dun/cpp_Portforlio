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
		Vector3 X = Vector3(c_D1.x - 0, c_D1.y - 21); //원점에서 A점 까지 벡터
		Vector3 Y = Vector3(c_D2.x - 0, c_D2.y - 21); //원점에서 B점 까지 벡터
		Vector3 P = Vector3(_p.x - 0, _p.y - 21); //원점에서 임의의 점 P까지 벡터

		double Alpa = P.x / X.x;
		double Beta = (P.y * -1) / (Y.y * -1);
		//A(D1) + B(D2) = P => 연립방정식으로 풀어야하지먄 현재는 둘 중 하나는 0이므로 그렇게까지 할 필요가 없음
		
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