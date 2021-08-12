#include "Object.h"

Object::Object()
{
}
Object::~Object()
{
}
void Object::Initialize()
{
	str = "Object";
	Transinfo.Position = Vector3(0.0f, 0.0f);
	Transinfo.Index = 0;
}
int Object::Update()
{
	return 0;
}
void Object::Render(int n)
{
	COORD Pos = { Transinfo.Position.x, Transinfo.Position.y + n};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	cout << Transinfo.Index << " : " << str << endl;
}