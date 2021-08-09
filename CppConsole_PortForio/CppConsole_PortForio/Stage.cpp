#include "Stage.h"
#include "DoubleBuffer.h"
#include "ObjectManager.h"
#include "SceneManager.h"


Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	GETSINGLETON(ObjectManager)->Initialize();
	checkTime = false;
}

void Stage::Update()
{
	GETSINGLETON(ObjectManager)->Update();

	if (GETSINGLETON(ObjectManager)->GetClear())
	{
		if (!checkTime)
		{
			checkTime = true;	
			Time = GetTickCount64();
		}
		if (Time + 200 < GetTickCount64())
		{
			GETSINGLETON(SceneManager)->SetScene(SCENEID_EXIT);
		}
	}
}

void Stage::Render()
{
	GETSINGLETON(ObjectManager)->Render();
}

void Stage::Release()
{
	GETSINGLETON(ObjectManager)->Release();
}