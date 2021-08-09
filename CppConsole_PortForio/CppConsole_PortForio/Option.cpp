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
	Text.push_back((char*)"메뉴 이동");
	Text.push_back((char*)"게임 시작");

	vector<Vector3> OptionTrans;
	OptionTrans.push_back(Vector3(CONSOL_MAX_WIDTH / 2 - (float)(strlen(Text[0]) / 2) - (float)strlen(Text[0]), 23));
	OptionTrans.push_back(Vector3(CONSOL_MAX_WIDTH / 2 - (float)(strlen(Text[1]) / 2) + (float)strlen(Text[1]), 23));

	TextPos = OptionTrans;

	Star = (char*)"★";
	StarPos = OptionTrans[0];
	StarPos.x -= 2;
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
			vector<Vector3>::iterator iter = TextPos.begin();
			StarPos = TextPos[0];
			StarPos.x -= 2;
		}
		if (Choice >= 2)
		{
			vector<Vector3>::iterator iter = TextPos.end() - 1;
			StarPos = TextPos[1];
			StarPos.x -= 2;
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
				GETSINGLETON(SceneManager)->SetScene(SCENEID_MENU);
				break;
			case 2:
				GETSINGLETON(SceneManager)->SetScene(SCENEID_STAGE);
				break;
			}
		}
	}
}

void Option::Render()
{
	
	
	GETSINGLETON(DoubleBuffer)->WriteBuffer(CONSOL_MAX_WIDTH/2 - (int)(strlen((char*)"게임 설명")/2), 4, (char*)"게임 설명");
	
	GETSINGLETON(DoubleBuffer)->WriteBuffer(15, 8, (char*)"게임 목적");
	GETSINGLETON(DoubleBuffer)->WriteBuffer(17, 9, (char*)"열쇠를 획득하여 출구를 열고 미로를 탈출하세요!");
	
	GETSINGLETON(DoubleBuffer)->WriteBuffer(15, 12, (char*)"조작키");
	GETSINGLETON(DoubleBuffer)->WriteBuffer(17, 13, (char*)"←↑↓→");

	GETSINGLETON(DoubleBuffer)->WriteBuffer(15, 16, (char*)"오브젝트 설명");
	GETSINGLETON(DoubleBuffer)->WriteBuffer(17, 17, (char*)"*: 플레이어");
	GETSINGLETON(DoubleBuffer)->WriteBuffer(17, 18, (char*)"=: 벽");
	GETSINGLETON(DoubleBuffer)->WriteBuffer(17, 19, (char*)" : 길");
	GETSINGLETON(DoubleBuffer)->WriteBuffer(17, 20, (char*)"k: 열쇠");

	{
		vector<char*>::iterator titer = Text.begin();
		vector<Vector3>::iterator piter = TextPos.begin();

		for (int i = 0; i < Text.size(); ++i)
		{
			GETSINGLETON(DoubleBuffer)->WriteBuffer((int)(*piter).x, (int)(*piter).y, (*titer), 8);
			if(i == Choice - 1)
				GETSINGLETON(DoubleBuffer)->WriteBuffer((int)(*piter).x, (int)(*piter).y, (*titer));

			titer++;
			piter++;
		}
	}
	GETSINGLETON(DoubleBuffer)->WriteBuffer((int)StarPos.x, (int)StarPos.y, Star, StarColor);
}

void Option::Release()
{
}