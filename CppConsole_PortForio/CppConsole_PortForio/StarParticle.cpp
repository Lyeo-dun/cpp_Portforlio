#include "StarParticle.h"
#include "DoubleBuffer.h"
#include "EndingManager.h"
#include "MathManager.h"

StarParticle::StarParticle()
{
}

StarParticle::~StarParticle()
{
}

void StarParticle::Initialize()
{
	Texture = (char*)"*";

	TransInfo.Position = Vector3(20.5, 10.5);
	TransInfo.Scale = Vector3(1, 1);
	Color = 14;

	inParticleAni = false;
}

void StarParticle::Update()
{
	if (!inParticleAni)
	{
		inParticleAni = true;
		Time = GetTickCount64();
	}
	if (inParticleAni)
	{
		if (Time + 100 < GetTickCount64())
		{
			TransInfo.Position.x += Direction.x * Speed;
			TransInfo.Position.y += Direction.y * Speed;
		}

		if (MathManager::GetDistance(TransInfo.Position, EndingManager::GetInstance()->GetPlayerPos()) > 5)
		{
			inParticleAni = false;
		}
	}
}

void StarParticle::Render()
{
	if (inParticleAni)
	{
		DoubleBuffer::GetInstance()->WriteBuffer((int)TransInfo.Position.x * 2, (int)TransInfo.Position.y, Texture, Color);
	}
}

void StarParticle::Release()
{
}
