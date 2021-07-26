#include "EndingPlayer.h"
#include "DoubleBuffer.h"
#include "EndingManager.h"

EndingPlayer::EndingPlayer()
{
}

EndingPlayer::~EndingPlayer()
{
	Release();
}

void EndingPlayer::Initialize()
{
	Texture = (char*)"¡Ú";

	TransInfo.Position = Vector3(0, 0);
	TransInfo.Scale = Vector3(1, 1);
	Color = 14;

	PlayerAniStartTime = GetTickCount64();

}

void EndingPlayer::Update()
{
	if (PlayerAniStartTime + 1000 < GetTickCount64())
	{
		if (EndingManager::GetInstance()->GetPlayerAni())
		{
			if (TransInfo.Position.x > (41 / 2))
			{
				TransInfo.Position.x -= Speed;
			}
			if (TransInfo.Position.y > (21 / 2))
			{
				TransInfo.Position.y -= Speed;
			}

			if (TransInfo.Position.x <= (41 / 2) && TransInfo.Position.y <= (21 / 2))
			{
				EndingManager::GetInstance()->AddViewRange(Speed);
			}
		}
	}

}

void EndingPlayer::Render()
{

	DoubleBuffer::GetInstance()->WriteBuffer((int)TransInfo.Position.x * 2, (int)TransInfo.Position.y, Texture, Color);
}

void EndingPlayer::Release()
{
}