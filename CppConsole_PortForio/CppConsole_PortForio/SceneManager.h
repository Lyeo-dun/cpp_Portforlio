#pragma once
#include "Headers.h"
#include "Singleton.h"

class Scene;
class SceneManager
{
public:
	DECLARE_SINGLETON(SceneManager)

private:
	Scene* SceneState;

public:
	void SetScene(SCENEID _SceneId);
	void Update();
	void Render();
	void Release();

public:
	SceneManager();
	~SceneManager();
};