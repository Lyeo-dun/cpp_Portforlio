#include "Option.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"

Option::Option()
{
}

Option::~Option()
{
}


void Option::Initialize()
{
	Option_Button[0] = (char*)"메뉴 이동";
	Option_Trans[0].Position = Vector3(CONSOL_MAX_WIDTH / 2 - (float)(strlen(Option_Button[0]) / 2) - (float)strlen(Option_Button[0]), 23);

	Option_Button[1] = (char*)"게임 시작";
	Option_Trans[1].Position = Vector3(CONSOL_MAX_WIDTH / 2 - (float)(strlen(Option_Button[1]) / 2) + (float)strlen(Option_Button[1]), 23);

	Star = (char*)"★";
	Star_Trans.Position = Option_Trans[0].Position;
	Star_Trans.Position.x -= 2;
	StarColor = rand() % 3 + 10;

	Choice = 1;

	StartTime = GetTickCount64();
	Time = GetTickCount64();
}

void Option::Update()
{
	if (Time + 50 < GetTickCount64())
	{
		if (GetAsyncKeyState(VK_RIGHT))
		{
			if (Choice < 2) 
			{
				Choice++;
				StarColor++;
					
				if (StarColor > 14)
					StarColor = 10;
			}
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (Choice > 1)
			{
				Choice--;
				StarColor++;
					
				if (StarColor > 14)
					StarColor = 10;
			}
		}

		if (Choice <= 1)
		{
			Star_Trans.Position = Option_Trans[0].Position;
			Star_Trans.Position.x -= 2;
		}
		if (Choice >= 2)
		{
			Star_Trans.Position = Option_Trans[1].Position;
			Star_Trans.Position.x -= 2;
		}

		Time = GetTickCount64();
	}

	if (StartTime + 1000 < GetTickCount64())
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			switch (Choice)
			{
			case 1:
				SceneManager::GetInstance()->SetScene(SCENEID_MENU);
				break;
			case 2:
				SceneManager::GetInstance()->SetScene(SCENEID_STAGE);
				break;
			}
		}
	}
}

void Option::Render()
{
	DoubleBuffer::GetInstance()->WriteBuffer(CONSOL_MAX_WIDTH/2 - (int)(strlen((char*)"게임 설명")/2), 4, (char*)"게임 설명");
	
	DoubleBuffer::GetInstance()->WriteBuffer(15, 8, (char*)"게임 목적");
	DoubleBuffer::GetInstance()->WriteBuffer(17, 9, (char*)"열쇠를 획득하여 출구를 열고 미로를 탈출하세요!");
	
	DoubleBuffer::GetInstance()->WriteBuffer(15, 12, (char*)"조작키");
	DoubleBuffer::GetInstance()->WriteBuffer(17, 13, (char*)"←↑↓→");

	DoubleBuffer::GetInstance()->WriteBuffer(15, 16, (char*)"오브젝트 설명");
	DoubleBuffer::GetInstance()->WriteBuffer(17, 17, (char*)"*: 플레이어");
	DoubleBuffer::GetInstance()->WriteBuffer(17, 18, (char*)"=: 벽");
	DoubleBuffer::GetInstance()->WriteBuffer(17, 19, (char*)" : 길");
	DoubleBuffer::GetInstance()->WriteBuffer(17, 20, (char*)"k: 열쇠");

	for (int i = 0; i < 2; ++i)
	{
		DoubleBuffer::GetInstance()->WriteBuffer((int)Option_Trans[i].Position.x, 23, Option_Button[i], 8);
		if(i == Choice - 1)
			DoubleBuffer::GetInstance()->WriteBuffer((int)Option_Trans[i].Position.x, 23, Option_Button[i]);
	}

	DoubleBuffer::GetInstance()->WriteBuffer((int)Star_Trans.Position.x, (int)Star_Trans.Position.y, Star, StarColor);
}

void Option::Release()
{
}