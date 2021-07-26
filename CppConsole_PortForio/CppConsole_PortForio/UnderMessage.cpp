#include "UnderMessage.h"
#include "DoubleBuffer.h"
#include "EndingManager.h"

UnderMessage::UnderMessage()
{
}

UnderMessage::~UnderMessage()
{
	Release();
}

void UnderMessage::Initialize()
{
	Texture[0] = (char*)"  |  |  |  |  ||  _  ||  |  ||     \\    |___, ||     ||  :  | __ ";
	Texture[1] = (char*)"  |  |  |  |  ||  |  ||  |  ||  .  |    |     ||     ||     ||  |";
	Texture[2] = (char*)"  |__|  |__|__||__|__||__|__||__|\\_|    |____/  \\___/  \\__,_||__|";

	TransInfo.Scale = Vector3((float)strlen(Texture[2]), 3);
	TransInfo.Position = Vector3(float(82 - TransInfo.Scale.x / 2), 10.5f + TransInfo.Scale.y/2);

	Color = 0;
	ColorAlpaValue = 0;

	checkTime = false;
}

void UnderMessage::Update()
{
	if (TransInfo.Position.x > 41)
	{
		TransInfo.Position.x += -Speed;
	}
	else 
	{
		TransInfo.Position.x = 41.0f;
		if (!checkTime)
		{
			checkTime = true;
			ExitTime = GetTickCount64();
		}
		else
		{
			if (ExitTime + 500 < GetTickCount64())
			{
				EndingManager::GetInstance()->SetTextureAni(false);
				EndingManager::GetInstance()->SetSelectMenu(true);
			}
		}
	}

	if (ColorAlpaValue < 3)
	{
		ColorAlpaValue += 0.2f;
	}

	switch ((int)ColorAlpaValue)
	{
	case 0:
		Color = 0;
		break;
	case 1:
		Color = 8;
		break;
	case 2:
		Color = 7;
		break;
	case 3:
		Color = 15;
		break;
	}
}

void UnderMessage::Render()
{
	for (int i = 0; i < 3; i++)
	{
		DoubleBuffer::GetInstance()->WriteBuffer(int(TransInfo.Position.x - TransInfo.Scale.x / 2), int(TransInfo.Position.y - TransInfo.Scale.y / 2) + i, Texture[i], Color);
	}
}

void UnderMessage::Release()
{
}