#include "MainUpdate.h"
#include "DoubleBuffer.h"
#include "SceneManager.h"

MainUpdate::MainUpdate()
{
}

MainUpdate::~MainUpdate()
{
	Release();
}

void MainUpdate::Initialize()
{
	GETSINGLETON(DoubleBuffer)->CreateBuffer(CONSOL_MAX_WIDTH, CONSOL_MAX_HEIGHT);
	GETSINGLETON(SceneManager)->SetScene(SCENEID_LOGO);
}

void MainUpdate::Update()
{
	GETSINGLETON(SceneManager)->Update();

	GETSINGLETON(DoubleBuffer)->FlippingBuffer();
	GETSINGLETON(DoubleBuffer)->ClearBuffer();
}

void MainUpdate::Render()
{
	GETSINGLETON(SceneManager)->Render();
}

void MainUpdate::Release()
{
	GETSINGLETON(SceneManager)->Release();
	GETSINGLETON(DoubleBuffer)->DestroyBuffer();
}