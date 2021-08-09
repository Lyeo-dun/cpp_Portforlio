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
	GETSINGLETON(EndingManager)->Initialize();
}

void Ending::Update()
{
	GETSINGLETON(EndingManager)->Update();

	if (GETSINGLETON(EndingManager)->GetChoice() == 1)
	{
		GETSINGLETON(SceneManager)->SetScene(SCENEID_MENU);
	}
	if (GETSINGLETON(EndingManager)->GetChoice() == 2)
	{
		exit(NULL);
	}
}

void Ending::Render()
{
	GETSINGLETON(EndingManager)->Render();	
}

void Ending::Release()
{
	GETSINGLETON(EndingManager)->Release();
}