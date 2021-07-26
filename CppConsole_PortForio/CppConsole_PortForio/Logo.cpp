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
	LogoText[0] = (char*)" __    __   ____  __ __  _____ ______   ____  ____  ";
	LogoText[1] = (char*)"|  |__|  | /    ||  |  |/ ___/|      | /    ||    \\ ";
	LogoText[2] = (char*)"|  |  |  ||  o  ||  |  (   \\_ |      ||  o  ||  D  )";
	LogoText[3] = (char*)"|  |  |  ||     ||  ~  |\\__  ||_|  |_||     ||    / ";
	LogoText[4] = (char*)"|  `  '  ||  _  ||___, |/  \\ |  |  |  |  _  ||    \\ ";
	LogoText[5] = (char*)" \\      / |  |  ||     |\\    |  |  |  |  |  ||  .  \\";
	LogoText[6] = (char*)"  \\_/\\_/  |__|__||____/  \\___|  |__|  |__|__||__|\\_|";

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
		SceneManager::GetInstance()->SetScene(SCENEID_MENU);
	}

}

void Logo::Render()
{
	for(int i = 0; i < 7; ++i)
	{
		DoubleBuffer::GetInstance()->WriteBuffer((int)TransInfo.Position.x, (int)TransInfo.Position.y + i, LogoText[i], 15);
	}
	DoubleBuffer::GetInstance()->WriteBuffer((int)(TransInfo.Position.x + strlen(LogoText[6]) - 1), (int)TransInfo.Position.y + 6, (char*)"★", StarColor);
	DoubleBuffer::GetInstance()->WriteBuffer(
		int(41 - strlen((char*)"게임을 시작하려면 엔터키를 눌러주세요!")/2), (int)TransInfo.Position.y + 8,
		(char*)"게임을 시작하려면 엔터키를 눌러주세요!", StarColor);
}

void Logo::Release()
{
}
