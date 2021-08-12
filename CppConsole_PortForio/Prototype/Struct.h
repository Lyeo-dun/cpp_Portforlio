#pragma once
struct Vector3
{
	float x, y, z;

	Vector3() {}
	Vector3(float _x, float _y, float _z = 0) : x(_x), y(_y), z(_z) {}
};
struct Transform
{
	Vector3 Position;
	Vector3 Scale;
	int Index;
};