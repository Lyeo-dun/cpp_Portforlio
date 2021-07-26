#include "MiniGameBar.h"
#include "ObjectManager.h"
#include "DoubleBuffer.h"

MiniGameBar::MiniGameBar()
{
}

MiniGameBar::~MiniGameBar()
{
	Release();
}


void MiniGameBar::Initialize()
{
	texture = (char*)"[                          ]";
	
	TransInfo.Position = Vector3(41, 21 / 2);
	TransInfo.Scale = Vector3((float)strlen(texture), 1);
	Color = 15;
}

void MiniGameBar::Update()
{
}

void MiniGameBar::Render()
{
	DoubleBuffer::GetInstance()->WriteBuffer((int)(TransInfo.Position.x - TransInfo.Scale.x / 2),
		(int)(TransInfo.Position.y - TransInfo.Scale.y / 2), texture, Color);
}

void MiniGameBar::Release()
{
}