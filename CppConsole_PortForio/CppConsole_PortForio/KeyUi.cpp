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
	texture.insert(make_pair("Static", (char*)"ขา  "));

	KeyCount = 0;
	isAni = false;

	map<string, char*>::iterator iter = texture.find("Static");
	TransInfo.Position = Vector3(float(41 - strlen((*iter).second)), 22.0f);
	Color = 15;

	texture.insert(make_pair("Ani", (char*)"ขา"));
	KeyPos = Vector3(0, 0);

	AfterKeyCount = 0;

	Time.insert(make_pair("Frame", GetTickCount64()));
	Time.insert(make_pair("AddCountTime", GetTickCount64()));
	checkAddTime = false;
}

void KeyUi::Update()
{
	if (isAni)
	{
			if (Time.find("Frame")->second + 50 < GetTickCount64())
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

						Time.find("AddCountTime")->second = GetTickCount64();
					}
					if (Time.find("AddCountTime")->second + 300 < GetTickCount64())
					{
						KeyCount = AfterKeyCount;
						Color = 15;
						
						checkAddTime = false;						
						isAni = false;
					}
				}

				Time.find("Frame")->second = GetTickCount64();
		}
	}
}

void KeyUi::Render()
{
	if (isAni)
	{
		map<string, char*>::iterator iter = texture.find("Ani");
		DoubleBuffer::GetInstance()->WriteBuffer(
			(int)KeyPos.x * 2 + 4,
			(int)KeyPos.y, (*iter).second, Color);
	}

	map<string, char*>::iterator iter = texture.find("Static");
	DoubleBuffer::GetInstance()->WriteBuffer(
		(int)TransInfo.Position.x * 2,
		(int)TransInfo.Position.y, (*iter).second, Color);
	
	DoubleBuffer::GetInstance()->WriteBuffer(
		(int)TransInfo.Position.x * 2 + 4,
		(int)TransInfo.Position.y, KeyCount, 15);

}

void KeyUi::Release()
{
}