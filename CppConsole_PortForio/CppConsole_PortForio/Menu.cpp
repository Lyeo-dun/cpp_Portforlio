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
	vector<char*> LogoText;
	LogoText.push_back((char*)" __    __   ____  __ __  _____ ______   ____  ____  ");
	LogoText.push_back((char*)"|  |__|  | /    ||  |  |/ ___/|      | /    ||    \\ ");
	LogoText.push_back((char*)"|  |  |  ||  o  ||  |  (   \\_ |      ||  o  ||  D  )");
	LogoText.push_back((char*)"|  |  |  ||     ||  ~  |\\__  ||_|  |_||     ||    / ");
	LogoText.push_back((char*)"|  `  '  ||  _  ||___, |/  \\ |  |  |  |  _  ||    \\ ");
	LogoText.push_back((char*)" \\      / |  |  ||     |\\    |  |  |  |  |  ||  .  \\");
	LogoText.push_back((char*)"  \\_/\\_/  |__|__||____/  \\___|  |__|  |__|__||__|\\_|");

	Text.insert(make_pair("Logo", LogoText));
	
	float x = 41 - float(strlen(LogoText.front()) / 2);
	float y = 21 / 2 - 3.5f;

	Trans.insert(make_pair("Logo", Vector3(x, y)));
	Logo_Ani = true;

	vector<char*> ChoiceMenu;
	ChoiceMenu.push_back((char*)"게임 시작");
	ChoiceMenu.push_back((char*)"게임 설명");
	ChoiceMenu.push_back((char*)"게임 종료");
	Text.insert(make_pair("Choice", ChoiceMenu));
	
	x = 41 - (float)(strlen(ChoiceMenu.front()) / 2);
	y = Trans.find("Logo")->second.y + 8.0f;

	Trans.insert(make_pair("Choice", Vector3(x, y)));
	ViewChioce = false;
	Choice = 1;

	vector<char*> Star;
	Star.push_back((char*)"★");
	Text.insert(make_pair("Star", Star));

	x = Trans.find("Logo")->second.x + strlen(LogoText.back())- 1;
	y = Trans.find("Logo")->second.y + 6.0f;

	Trans.insert(make_pair("Star", Vector3(x, y)));
	StarColor = rand() % 6 + 9;

	Time = GetTickCount64(); 
}

void Menu::Update()
{
	if(Time + 100 < GetTickCount64())
	{
		if (Logo_Ani)
		{
			Trans.find("Logo")->second.y -= 0.3f;
			Trans.find("Star")->second.y = Trans.find("Logo")->second.y + 6.0f;
			if (Trans.find("Logo")->second.y < 21 / 2 - 6.0f)
			{
				Logo_Ani = false;
			}
		}
		else
		{
			if (Trans.find("Choice")->second.x - 2 < Trans.find("Star")->second.x)
				Trans.find("Star")->second.x -= 1.5f;

			if (Trans.find("Choice")->second.y > Trans.find("Star")->second.y)
				Trans.find("Star")->second.y ++;

			if (ViewChioce)
			{
				if (GetAsyncKeyState(VK_DOWN))
				{
					if (Choice < 3)
					{
						Choice++;
						Trans.find("Star")->second.y++;
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
						Trans.find("Star")->second.y--;
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
	
	if (Trans.find("Choice")->second.x - 2 >= Trans.find("Star")->second.x
		&& Trans.find("Choice")->second.y <= Trans.find("Star")->second.y)
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
	int i = 0;
	//로고 출력
	for (vector<char*>::iterator iter = Text.find("Logo")->second.begin(); iter != Text.find("Logo")->second.end(); ++iter)
	{
		DoubleBuffer::GetInstance()->WriteBuffer((int)Trans.find("Logo")->second.x, (int)Trans.find("Logo")->second.y + i, *iter, 15);
		i++;
	}

	for (vector<char*>::iterator iter = Text.find("Star")->second.begin(); iter != Text.find("Star")->second.end(); ++iter)
	{
		DoubleBuffer::GetInstance()->WriteBuffer((int)Trans.find("Star")->second.x, (int)Trans.find("Star")->second.y, *iter, StarColor);
	}

	//메뉴 출력
	if (ViewChioce)
	{
		i = 0;

		for (vector<char*>::iterator iter = Text.find("Choice")->second.begin(); iter != Text.find("Choice")->second.end(); ++iter)
		{
			DoubleBuffer::GetInstance()->WriteBuffer((int)Trans.find("Choice")->second.x, int(Trans.find("Choice")->second.y + i), *iter, 8);
			if (Choice - 1 == i)
			{
				DoubleBuffer::GetInstance()->WriteBuffer((int)Trans.find("Choice")->second.x, int(Trans.find("Choice")->second.y + i), *iter);
			}
			++i;
		}
	}
}

void Menu::Release()
{
}