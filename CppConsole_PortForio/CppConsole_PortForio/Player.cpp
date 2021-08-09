#include "Player.h"
#include "DoubleBuffer.h"
#include "ObjectManager.h"
#include "ColliderManager.h"

Player::Player()
{
}

Player::~Player()
{
	Release();
}

void Player::Initialize()
{
	if (!GETSINGLETON(ObjectManager)->GetMiniGameMode())
	{
		Texture = (char*)"¡Ú";
		for (int y = 0; y < 21; y++)
		{
			for (int x = 0; x < 41; x++)
			{
				if (GETSINGLETON(ObjectManager)->GetTileInfo(x, y) == 2)
				{
					TransInfo.Position = Vector3((float)x, (float)y);
					TransInfo.Scale = Vector3(1, 1);
				}
			}
		}
	}

	if (GETSINGLETON(ObjectManager)->GetMiniGameMode())
	{
		Texture = (char*)"*";
		TransInfo.Position = Vector3(((GETSINGLETON(ObjectManager)->GetGameBar()->GetPosition().x - GETSINGLETON(ObjectManager)->GetGameBar()->GetScale().x / 2) + 3.0f), GETSINGLETON(ObjectManager)->GetGameBar()->GetPosition().y);
		TransInfo.Scale = Vector3(1, 1);

		MiniGame1_Speed = -0.5;

		MiniGame_Move = true;
		MiniGameStartTime = GetTickCount64();
	}

	Color = 14;
}

void Player::Update()
{
	if (!GETSINGLETON(ObjectManager)->GetMiniGameMode())
	{
		if (GetAsyncKeyState(VK_LEFT))
			if (GETSINGLETON(ObjectManager)->GetTileInfo((int)TransInfo.Position.x - 1, (int)TransInfo.Position.y) != 1
				&& GETSINGLETON(ObjectManager)->GetTileInfo((int)TransInfo.Position.x - 1, (int)TransInfo.Position.y) != 7)
			{
				CurrentPlayerPos = TransInfo.Position;
				TransInfo.Position.x -= 1;
			}

		if (GetAsyncKeyState(VK_RIGHT))
			if (GETSINGLETON(ObjectManager)->GetTileInfo((int)TransInfo.Position.x + 1, (int)TransInfo.Position.y) != 1
				&& GETSINGLETON(ObjectManager)->GetTileInfo((int)TransInfo.Position.x + 1, (int)TransInfo.Position.y) != 7)
			{
				CurrentPlayerPos = TransInfo.Position;
				TransInfo.Position.x += 1;
			}

		if (GetAsyncKeyState(VK_UP))
			if (GETSINGLETON(ObjectManager)->GetTileInfo((int)TransInfo.Position.x, (int)TransInfo.Position.y - 1) != 1
				&& GETSINGLETON(ObjectManager)->GetTileInfo((int)TransInfo.Position.x, (int)TransInfo.Position.y - 1) != 7)
			{
				CurrentPlayerPos = TransInfo.Position;
				TransInfo.Position.y -= 1;

				if (TransInfo.Position.y < 0)
				{
					TransInfo.Position.y += 1;
				}
			}

		if (GetAsyncKeyState(VK_DOWN))
			if (GETSINGLETON(ObjectManager)->GetTileInfo((int)TransInfo.Position.x, (int)TransInfo.Position.y + 1) != 1
				&& GETSINGLETON(ObjectManager)->GetTileInfo((int)TransInfo.Position.x, (int)TransInfo.Position.y + 1) != 7)
			{
				CurrentPlayerPos = TransInfo.Position;
				TransInfo.Position.y += 1;

				if (TransInfo.Position.y > 20)
				{
					TransInfo.Position.y -= 1;
				}
			}

		for (int i = 0; i < 4; i++)
		{
			if (GETSINGLETON(ObjectManager)->GetKey(i) != nullptr)
			{
				if (CollisionManager::CollisionRact(TransInfo, GETSINGLETON(ObjectManager)->GetKey(i)->GetTrans()))
				{
					CollisionKey = i;
					GETSINGLETON(ObjectManager)->SetMiniGameMode(true);
					GETSINGLETON(ObjectManager)->InMiniGame(CollisionKey);

					Initialize();
				}
			}
		}

	}

	if (GETSINGLETON(ObjectManager)->GetMiniGameMode())
	{
		if (MiniGame_Move)
		{
			TransInfo.Position.x += MiniGame1_Speed;
			if (TransInfo.Position.x < GETSINGLETON(ObjectManager)->GetGameBar()->GetPosition().x - GETSINGLETON(ObjectManager)->GetGameBar()->GetScale().x / 2 + 3)
			{
				MiniGame1_Speed *= -1;
			}
			if (TransInfo.Position.x > GETSINGLETON(ObjectManager)->GetGameBar()->GetPosition().x + GETSINGLETON(ObjectManager)->GetGameBar()->GetScale().x / 2 - 1)
			{
				MiniGame1_Speed *= -1;
			}
		}

		if(MiniGameStartTime + 50 < GetTickCount64())
			if (GetAsyncKeyState(VK_SPACE))
			{
				MiniGame_Move = false;

				if (CollisionManager::CollisionRact(TransInfo, GETSINGLETON(ObjectManager)->GetHitPoint()->GetTrans()))
				{
					GETSINGLETON(ObjectManager)->PlayKeyUiAni(GETSINGLETON(ObjectManager)->GetKey(CollisionKey)->GetPosition(), CollisionKey);
					GETSINGLETON(ObjectManager)->KeyErease(CollisionKey);
					GETSINGLETON(ObjectManager)->SetMiniGameMode(false);
					GETSINGLETON(ObjectManager)->ReturnMaze();
					TransInfo.Position = CurrentPlayerPos;

					Color = 4;
					return;
				}

				GETSINGLETON(ObjectManager)->SetMiniGameMode(false);
				GETSINGLETON(ObjectManager)->ReturnMaze();

				TransInfo.Position = CurrentPlayerPos;
			}
	}
}

void Player::Render()
{
	if (!GETSINGLETON(ObjectManager)->GetMiniGameMode())
	{
		GETSINGLETON(DoubleBuffer)->WriteBuffer(
			(int)TransInfo.Position.x * 2,
			(int)TransInfo.Position.y, Texture, Color);

	}

	if (GETSINGLETON(ObjectManager)->GetMiniGameMode())
	{
		GETSINGLETON(DoubleBuffer)->WriteBuffer(
			(int)(TransInfo.Position.x - TransInfo.Scale.x/2),
			(int)(TransInfo.Position.y - TransInfo.Scale.y/2), Texture, Color);
	}
}

void Player::Release()
{
}
