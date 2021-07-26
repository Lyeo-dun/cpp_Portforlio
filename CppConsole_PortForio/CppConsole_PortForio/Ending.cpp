#include "Ending.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"
#include "EndingManager.h"


Ending::Ending()
{
}

Ending::~Ending()
{
}

void Ending::Initialize()
{
	EndingManager::GetInstance()->Initialize();
}

void Ending::Update()
{
	EndingManager::GetInstance()->Update();

	if (EndingManager::GetInstance()->GetChoice() == 1)
	{
		SceneManager::GetInstance()->SetScene(SCENEID_MENU);
	}
	if (EndingManager::GetInstance()->GetChoice() == 2)
	{
		exit(NULL);
	}
}

void Ending::Render()
{
	EndingManager::GetInstance()->Render();	
}

void Ending::Release()
{
	EndingManager::GetInstance()->Release();
}