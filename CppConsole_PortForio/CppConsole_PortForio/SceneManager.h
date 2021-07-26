#pragma once
#include "Headers.h"

class Scene;
class SceneManager
{
private:
	static SceneManager* m_pInstance;
public:
	static SceneManager* GetInstance() {
		if (m_pInstance == nullptr)
			m_pInstance = new SceneManager;

		return m_pInstance;
	}

private:
	Scene* SceneState;
public:
	void SetScene(SCENEID _SceneId);

	void Update();
	void Render();
	void Release();

public:
	~SceneManager();
private:
	SceneManager();
};

