#include "Key.h"
#include "DoubleBuffer.h"

Key::Key()
{
}

Key::~Key()
{
	Release();
}
 
void Key::Initialize()
{
	texture = (char*)"ขา";
	TransInfo.Position = Vector3(0, 0);
	TransInfo.Scale = Vector3(1, 1);

	Color = 15;
	MiniGameLevel = 1;
}

void Key::Update()
{

}

void Key::Render()
{
	DoubleBuffer::GetInstance()->WriteBuffer(
		(int)TransInfo.Position.x * 2,
		(int)TransInfo.Position.y, texture, Color);
}

void Key::Release()
{
}