#include "HitPoint.h"
#include "ObjectManager.h"
#include "DoubleBuffer.h"

HitPoint::HitPoint()
{
}

HitPoint::~HitPoint()
{
	Release();
}

void HitPoint::Initialize()
{
	
	texture = (char*)"/////////";

	TransInfo.Scale = Vector3((float)strlen(texture), 1);
	TransInfo.Position = Vector3(ObjectManager::GetInstance()->GetGameBar()->GetPosition().x, ObjectManager::GetInstance()->GetGameBar()->GetPosition().y);

	Color = 4;
}

void HitPoint::SetLevel(int _level)
{
	switch (_level)
	{
	case 1:
		texture = (char*)"/////////";
		TransInfo.Scale = Vector3((float)strlen(texture), 1);
		break;
	case 2:
		texture = (char*)"///////";
		TransInfo.Scale = Vector3((float)strlen(texture), 1);
		break;
	case 3:
		texture = (char*)"/////";
		TransInfo.Scale = Vector3((float)strlen(texture), 1);
		break;
	case 4:
		texture = (char*)"///";
		TransInfo.Scale = Vector3((float)strlen(texture), 1);
		break;
	}
}

void HitPoint::Update()
{
}

void HitPoint::Render()
{
	DoubleBuffer::GetInstance()->WriteBuffer(int(TransInfo.Position.x - TransInfo.Scale.x/2), int(TransInfo.Position.y - TransInfo.Scale.y / 2), texture, Color);
}

void HitPoint::Release()
{
}
