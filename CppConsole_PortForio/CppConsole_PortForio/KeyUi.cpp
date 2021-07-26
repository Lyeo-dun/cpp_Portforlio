#include "KeyUi.h"
#include "DoubleBuffer.h"
#include "ObjectManager.h"

KeyUi::KeyUi()
{
}

KeyUi::~KeyUi()
{
	Release();
}

void KeyUi::Initialize()
{
	Texture = (char*)"ขา  ";
	KeyCount = 0;
	isAni = false;
	TransInfo.Position = Vector3(float(41 - strlen(Texture)), 22.0f);
	Color = 15;

	KeyTexture = (char*)"ขา";
	KeyPos = Vector3(0, 0);

	AfterKeyCount = 0;

	Time = GetTickCount64();

	AddTime = GetTickCount64();
	checkAddTime = false;
}

void KeyUi::Update()
{
	if (isAni)
	{
			if (Time + 50 < GetTickCount64())
			{
				if (KeyPos.x < TransInfo.Position.x - 2)
				{
					KeyPos.x += 1.0f;
				}
				if (KeyPos.x > TransInfo.Position.x - 2)
				{
					KeyPos.x -= 1.0f;
				}

				if (KeyPos.y < TransInfo.Position.y)
				{
					KeyPos.y += 1.0f;
				}

				if (KeyPos.x == TransInfo.Position.x - 2 && KeyPos.y == TransInfo.Position.y)
				{	
					if (!checkAddTime)
					{
						checkAddTime = true;
						Color = EatKeyColor;
						
						AddTime = GetTickCount64();
					}
					if (AddTime + 300 < GetTickCount64())
					{
						KeyCount = AfterKeyCount;
						Color = 15;
						
						checkAddTime = false;						
						isAni = false;
					}
				}

			Time = GetTickCount64();
		}
	}
}

void KeyUi::Render()
{
	if (isAni)
	{
		DoubleBuffer::GetInstance()->WriteBuffer(
			(int)KeyPos.x * 2 + 4,
			(int)KeyPos.y, KeyTexture, Color);
	}

	DoubleBuffer::GetInstance()->WriteBuffer(
		(int)TransInfo.Position.x * 2,
		(int)TransInfo.Position.y, Texture, Color);
	
	DoubleBuffer::GetInstance()->WriteBuffer(
		(int)TransInfo.Position.x * 2 + 4,
		(int)TransInfo.Position.y, KeyCount, 15);

}

void KeyUi::Release()
{
}