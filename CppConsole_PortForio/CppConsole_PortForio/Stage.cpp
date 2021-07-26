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
	ObjectManager::GetInstance()->Initialize();
	checkTime = false;
}

void Stage::Update()
{
	ObjectManager::GetInstance()->Update();

	if (ObjectManager::GetInstance()->GetClear())
	{
		if (!checkTime)
		{
			checkTime = true;	
			Time = GetTickCount64();
		}
		if (Time + 200 < GetTickCount64())
		{
			SceneManager::GetInstance()->SetScene(SCENEID_EXIT);
		}
	}
}

void Stage::Render()
{
	ObjectManager::GetInstance()->Render();
}

void Stage::Release()
{
	ObjectManager::GetInstance()->Release();
}