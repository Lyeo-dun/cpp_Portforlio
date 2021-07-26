#include "Menu.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}


void Menu::Initialize()
{
	LogoText[0] = (char*)" __    __   ____  __ __  _____ ______   ____  ____  ";
	LogoText[1] = (char*)"|  |__|  | /    ||  |  |/ ___/|      | /    ||    \\ ";
	LogoText[2] = (char*)"|  |  |  ||  o  ||  |  (   \\_ |      ||  o  ||  D  )";
	LogoText[3] = (char*)"|  |  |  ||     ||  ~  |\\__  ||_|  |_||     ||    / ";
	LogoText[4] = (char*)"|  `  '  ||  _  ||___, |/  \\ |  |  |  |  _  ||    \\ ";
	LogoText[5] = (char*)" \\      / |  |  ||     |\\    |  |  |  |  |  ||  .  \\";
	LogoText[6] = (char*)"  \\_/\\_/  |__|__||____/  \\___|  |__|  |__|__||__|\\_|";

	float x = 41 - float(strlen(LogoText[0]) / 2);
	float y = 21 / 2 - 3.5f;

	Logo_TransInfo.Position = Vector3(x, y);
	Logo_Ani = true;

	ChoiceMenu[0] = (char*)"게임 시작";
	ChoiceMenu[1] = (char*)"게임 설명";
	ChoiceMenu[2] = (char*)"게임 종료";

	x = 41 - (float)(strlen(ChoiceMenu[0]) / 2);
	y = Logo_TransInfo.Position.y + 8.0f;

	Choice_TransInfo.Position = Vector3(x, y);
	ViewChioce = false;
	Choice = 1;

	Star = (char*)"★";
	x = Logo_TransInfo.Position.x + strlen(LogoText[6]) - 1;
	y = Logo_TransInfo.Position.y + 6.0f;
	Star_TransInfo.Position = Vector3(x, y);
	StarColor = rand() % 6 + 9;

	Time = GetTickCount64(); 
}

void Menu::Update()
{
	if(Time + 100 < GetTickCount64())
	{
		if (Logo_Ani)
		{
			Logo_TransInfo.Position.y -= 0.3f; 
			Star_TransInfo.Position.y = Logo_TransInfo.Position.y + 6.0f;
			if (Logo_TransInfo.Position.y < 21 / 2 - 6.0f)
			{
				Logo_Ani = false;
			}
		}
		else
		{
			if (Choice_TransInfo.Position.x - 2 < Star_TransInfo.Position.x)
				Star_TransInfo.Position.x -= 1.5f;

			if (Choice_TransInfo.Position.y > Star_TransInfo.Position.y)
				Star_TransInfo.Position.y ++;

			if (ViewChioce)
			{
				if (GetAsyncKeyState(VK_DOWN))
				{
					if (Choice < 3)
					{
						Choice++;
						Star_TransInfo.Position.y++;
						StarColor++;
						
						if (StarColor > 14) 
						{
							StarColor = 9;
						}
					}
				}
				if (GetAsyncKeyState(VK_UP))
				{
					if (Choice > 1)
					{
						Choice--;
						Star_TransInfo.Position.y--;
						StarColor++;

						if (StarColor > 14) 
						{
							StarColor = 9;
						}
					}
				}
			}
		}

		Time = GetTickCount64();
	}

	
	if (Choice_TransInfo.Position.x - 2 >= Star_TransInfo.Position.x 
		&& Choice_TransInfo.Position.y <= Star_TransInfo.Position.y)
	{
		ViewChioce = true;
	}

	if (ViewChioce)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			switch (Choice)
			{
			case 1:
				SceneManager::GetInstance()->SetScene(SCENEID_STAGE);
				break;
			case 2:
				SceneManager::GetInstance()->SetScene(SCENEID_OPTION);
				break;
			case 3:
				SceneManager::GetInstance()->SetScene(SCENEID_EXIT);
				break;
			}
		}
	}
}

void Menu::Render()
{
	for (int i = 0; i < 7; ++i)
	{
		DoubleBuffer::GetInstance()->WriteBuffer((int)Logo_TransInfo.Position.x, (int)Logo_TransInfo.Position.y + i, LogoText[i], 15);
	}

	DoubleBuffer::GetInstance()->WriteBuffer((int)Star_TransInfo.Position.x, (int)Star_TransInfo.Position.y, Star, StarColor);

	if(ViewChioce)
		for (int i = 0; i < 3; ++i)
		{
			DoubleBuffer::GetInstance()->WriteBuffer((int)Choice_TransInfo.Position.x, int(Choice_TransInfo.Position.y + i), ChoiceMenu[i], 8);
			if (Choice - 1 == i)
			{
				DoubleBuffer::GetInstance()->WriteBuffer((int)Choice_TransInfo.Position.x, int(Choice_TransInfo.Position.y + i), ChoiceMenu[i]);
			}
		}
}

void Menu::Release()
{
}