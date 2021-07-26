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
	if (!ObjectManager::GetInstance()->GetMiniGameMode())
	{
		Texture = (char*)"¡Ú";
		for (int y = 0; y < 21; y++)
		{
			for (int x = 0; x < 41; x++)
			{
				if (ObjectManager::GetInstance()->GetTileInfo(x, y) == 2)
				{
					TransInfo.Position = Vector3((float)x, (float)y);
					TransInfo.Scale = Vector3(1, 1);
				}
			}
		}
	}

	if (ObjectManager::GetInstance()->GetMiniGameMode())
	{
		Texture = (char*)"*";
		TransInfo.Position = Vector3(((ObjectManager::GetInstance()->GetGameBar()->GetPosition().x - ObjectManager::GetInstance()->GetGameBar()->GetScale().x / 2) + 3.0f), ObjectManager::GetInstance()->GetGameBar()->GetPosition().y);
		TransInfo.Scale = Vector3(1, 1);

		MiniGame1_Speed = -0.5;

		MiniGame_Move = true;
		MiniGameStartTime = GetTickCount64();
	}

	Color = 14;
}

void Player::Update()
{
	if (!ObjectManager::GetInstance()->GetMiniGameMode())
	{
		if (GetAsyncKeyState(VK_LEFT))
			if (ObjectManager::GetInstance()->GetTileInfo((int)TransInfo.Position.x - 1, (int)TransInfo.Position.y) != 1
				&& ObjectManager::GetInstance()->GetTileInfo((int)TransInfo.Position.x - 1, (int)TransInfo.Position.y) != 7)
			{
				CurrentPlayerPos = TransInfo.Position;
				TransInfo.Position.x -= 1;
			}

		if (GetAsyncKeyState(VK_RIGHT))
			if (ObjectManager::GetInstance()->GetTileInfo((int)TransInfo.Position.x + 1, (int)TransInfo.Position.y) != 1
				&& ObjectManager::GetInstance()->GetTileInfo((int)TransInfo.Position.x + 1, (int)TransInfo.Position.y) != 7)
			{
				CurrentPlayerPos = TransInfo.Position;
				TransInfo.Position.x += 1;
			}

		if (GetAsyncKeyState(VK_UP))
			if (ObjectManager::GetInstance()->GetTileInfo((int)TransInfo.Position.x, (int)TransInfo.Position.y - 1) != 1
				&& ObjectManager::GetInstance()->GetTileInfo((int)TransInfo.Position.x, (int)TransInfo.Position.y - 1) != 7)
			{
				CurrentPlayerPos = TransInfo.Position;
				TransInfo.Position.y -= 1;

				if (TransInfo.Position.y < 0)
				{
					TransInfo.Position.y += 1;
				}
			}

		if (GetAsyncKeyState(VK_DOWN))
			if (ObjectManager::GetInstance()->GetTileInfo((int)TransInfo.Position.x, (int)TransInfo.Position.y + 1) != 1
				&& ObjectManager::GetInstance()->GetTileInfo((int)TransInfo.Position.x, (int)TransInfo.Position.y + 1) != 7)
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
			if (ObjectManager::GetInstance()->GetKey(i) != nullptr)
			{
				if (CollisionManager::CollisionRact(TransInfo, ObjectManager::GetInstance()->GetKey(i)->GetTrans()))
				{
					CollisionKey = i;
					ObjectManager::GetInstance()->SetMiniGameMode(true);
					ObjectManager::GetInstance()->InMiniGame(CollisionKey);

					Initialize();
				}
			}
		}

	}

	if (ObjectManager::GetInstance()->GetMiniGameMode())
	{
		if (MiniGame_Move)
		{
			TransInfo.Position.x += MiniGame1_Speed;
			if (TransInfo.Position.x < ObjectManager::GetInstance()->GetGameBar()->GetPosition().x - ObjectManager::GetInstance()->GetGameBar()->GetScale().x / 2 + 3)
			{
				MiniGame1_Speed *= -1;
			}
			if (TransInfo.Position.x > ObjectManager::GetInstance()->GetGameBar()->GetPosition().x + ObjectManager::GetInstance()->GetGameBar()->GetScale().x / 2 - 1)
			{
				MiniGame1_Speed *= -1;
			}
		}

		if(MiniGameStartTime + 50 < GetTickCount64())
			if (GetAsyncKeyState(VK_SPACE))
			{
				MiniGame_Move = false;

				if (CollisionManager::CollisionRact(TransInfo, ObjectManager::GetInstance()->GetHitPoint()->GetTrans()))
				{
					ObjectManager::GetInstance()->PlayKeyUiAni(ObjectManager::GetInstance()->GetKey(CollisionKey)->GetPosition(), CollisionKey);
					ObjectManager::GetInstance()->KeyErease(CollisionKey);
					ObjectManager::GetInstance()->SetMiniGameMode(false);
					ObjectManager::GetInstance()->ReturnMaze();
					TransInfo.Position = CurrentPlayerPos;

					Color = 4;
					return;
				}

				ObjectManager::GetInstance()->SetMiniGameMode(false);
				ObjectManager::GetInstance()->ReturnMaze();

				TransInfo.Position = CurrentPlayerPos;
			}
	}
}

void Player::Render()
{
	if (!ObjectManager::GetInstance()->GetMiniGameMode())
	{
		DoubleBuffer::GetInstance()->WriteBuffer(
			(int)TransInfo.Position.x * 2,
			(int)TransInfo.Position.y, Texture, Color);
	}

	if (ObjectManager::GetInstance()->GetMiniGameMode())
	{
		DoubleBuffer::GetInstance()->WriteBuffer(
			(int)(TransInfo.Position.x - TransInfo.Scale.x/2),
			(int)(TransInfo.Position.y - TransInfo.Scale.y/2), Texture, Color);
	}
}

void Player::Release()
{
}
