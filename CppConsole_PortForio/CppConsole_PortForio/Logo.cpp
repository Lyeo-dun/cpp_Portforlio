#include "Logo.h"
#include "SceneManager.h"
#include "DoubleBuffer.h"


Logo::Logo()
{
}

Logo::~Logo()
{
}


void Logo::Initialize()
{
	LogoText.push_back((char*)" __    __   ____  __ __  _____ ______   ____  ____  ");
	LogoText.push_back((char*)"|  |__|  | /    ||  |  |/ ___/|      | /    ||    \\ ");
	LogoText.push_back((char*)"|  |  |  ||  o  ||  |  (   \\_ |      ||  o  ||  D  )");
	LogoText.push_back((char*)"|  |  |  ||     ||  ~  |\\__  ||_|  |_||     ||    / ");
	LogoText.push_back((char*)"|  `  '  ||  _  ||___, |/  \\ |  |  |  |  _  ||    \\ ");
	LogoText.push_back((char*)" \\      / |  |  ||     |\\    |  |  |  |  |  ||  .  \\");
	LogoText.push_back((char*)"  \\_/\\_/  |__|__||____/  \\___|  |__|  |__|__||__|\\_|");

	float x = 82 / 2 - (float)strlen(LogoText[5]) / 2;
	float y = 21 / 2 - 3.5f;

	TransInfo.Position = Vector3(x, y);

	StarColor = rand() % 6 + 9;
	Time = GetTickCount64();
}

void Logo::Update()
{
	if (Time + 100 < GetTickCount64()) 
	{
		StarColor = rand() % 6 + 9;
		
		Time = GetTickCount64();
	}

	if (GetAsyncKeyState(VK_RETURN)) 
	{
		GETSINGLETON(SceneManager)->SetScene(SCENEID_MENU);
	}

}

void Logo::Render()
{
	{
		int i = 0;
		for (vector<char*>::iterator iter = LogoText.begin(); iter != LogoText.end(); ++iter)
		{	
			GETSINGLETON(DoubleBuffer)->WriteBuffer((int)TransInfo.Position.x, (int)TransInfo.Position.y + i, *iter, 15);
			i++;
		}
	}
	GETSINGLETON(DoubleBuffer)->WriteBuffer((int)(TransInfo.Position.x + strlen(LogoText[6]) - 1), (int)TransInfo.Position.y + 6, (char*)"★", StarColor);
	GETSINGLETON(DoubleBuffer)->WriteBuffer(
		int(41 - strlen((char*)"게임을 시작하려면 엔터키를 눌러주세요!")/2), (int)TransInfo.Position.y + 8,
		(char*)"게임을 시작하려면 엔터키를 눌러주세요!", StarColor);
}

void Logo::Release()
{
}
