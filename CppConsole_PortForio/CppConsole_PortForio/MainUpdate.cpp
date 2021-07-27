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
	DoubleBuffer::GetInstance()->CreateBuffer(CONSOL_MAX_WIDTH, CONSOL_MAX_HEIGHT);
	SceneManager::GetInstance()->SetScene(SCENEID_STAGE);
}

void MainUpdate::Update()
{
	SceneManager::GetInstance()->Update();

	DoubleBuffer::GetInstance()->FlippingBuffer();
	DoubleBuffer::GetInstance()->ClearBuffer();
}

void MainUpdate::Render()
{
	SceneManager::GetInstance()->Render();
}

void MainUpdate::Release()
{
	SceneManager::GetInstance()->Release();
	DoubleBuffer::GetInstance()->DestroyBuffer();
}