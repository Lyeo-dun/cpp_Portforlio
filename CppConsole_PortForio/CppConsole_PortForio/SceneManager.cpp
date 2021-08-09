#include "SceneManager.h"
#include "Logo.h"
#include "Menu.h"
#include "Stage.h"
#include "Option.h"
#include "Ending.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::SetScene(SCENEID _SceneId)
{
	SAFE_RELEASE(SceneState);

	switch (_SceneId)
	{
	case SCENEID_LOGO:
		SceneState = new Logo;
		break;
	case SCENEID_MENU:
		SceneState = new Menu;
		break;
	case SCENEID_OPTION:
		SceneState = new Option;
		break;
	case SCENEID_STAGE:
		SceneState = new Stage;
		break;
	case SCENEID_EXIT:
		SceneState = new Ending;
		break;
	}
	SceneState->Initialize();
}

void SceneManager::Update()
{
	SceneState->Update();
}

void SceneManager::Render()
{
	SceneState->Render();
}

void SceneManager::Release()
{
	SceneState->Release();
	DESTROYSINGLETON(SceneManager);
}
