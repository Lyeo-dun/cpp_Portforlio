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
	LogoText.push_back((char*)" __    __   ____  __ __  _____ ______   ____  ____  ");
	LogoText.push_back((char*)"|  |__|  | /    ||  |  |/ ___/|      | /    ||    \\ ");
	LogoText.push_back((char*)"|  |  |  ||  o  ||  |  (   \\_ |      ||  o  ||  D  )");
	LogoText.push_back((char*)"|  |  |  ||     ||  ~  |\\__  ||_|  |_||     ||    / ");
	LogoText.push_back((char*)"|  `  '  ||  _  ||___, |/  \\ |  |  |  |  _  ||    \\ ");
	LogoText.push_back((char*)" \\      / |  |  ||     |\\    |  |  |  |  |  ||  .  \\");
	LogoText.push_back((char*)"  \\_/\\_/  |__|__||____/  \\___|  |__|  |__|__||__|\\_|");

	float x = 41 - float(strlen(LogoText[0]) / 2);
	float y = 21 / 2 - 3.5f;

	Logo_TransInfo.Position = Vector3(x, y);
	Logo_Ani = true;

	ChoiceMenu.insert(make_pair(1, (char*)"게임 시작"));
	ChoiceMenu.insert(make_pair(2, (char*)"게임 설명"));
	ChoiceMenu.insert(make_pair(3, (char*)"게임 종료"));
	
	x = 41 - (float)(strlen(ChoiceMenu.find(1)->second) / 2);
	y = Logo_TransInfo.Position.y + 8.0f;

	Choice_TransInfo.Position = Vector3(x, y);
	ViewChioce = false;
	Choice = 1;

	Star = (char*)"★";
	x = Logo_TransInfo.Position.x + strlen(LogoText[6])- 1;
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
	//로고 출력
	{
		int i = 0;
		for (vector<char*>::iterator iter = LogoText.begin(); iter != LogoText.end(); ++iter)
		{
			DoubleBuffer::GetInstance()->WriteBuffer((int)Logo_TransInfo.Position.x, (int)Logo_TransInfo.Position.y + i, LogoText[i], 15);
			i++;
		}
	}

	DoubleBuffer::GetInstance()->WriteBuffer((int)Star_TransInfo.Position.x, (int)Star_TransInfo.Position.y, Star, StarColor);

	//메뉴 출력
	if (ViewChioce)
	{
		int i = 0;
		for (map<int, char*>::iterator iter = ChoiceMenu.begin(); iter != ChoiceMenu.end(); ++iter)
		{
			DoubleBuffer::GetInstance()->WriteBuffer((int)Choice_TransInfo.Position.x, int(Choice_TransInfo.Position.y + i), iter->second, 8);
			if (Choice - 1 == i)
			{
				DoubleBuffer::GetInstance()->WriteBuffer((int)Choice_TransInfo.Position.x, int(Choice_TransInfo.Position.y + i), iter->second);
			}
			++i;
		}
	}
}

void Menu::Release()
{
}