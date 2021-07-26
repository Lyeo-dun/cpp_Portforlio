#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "DoubleBuffer.h"
#include "ColliderManager.h"
#include "MathManager.h"
#include "Player.h"
#include "MiniGameBar.h"
#include "HitPoint.h"
#include "Key.h"
#include "KeyUi.h"
#include "SceneManager.h"

ObjectManager* ObjectManager::m_pInstance = nullptr;

ObjectManager::ObjectManager()
{
	m_isMiniGameMode = false;
}
ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize()
{

	MiniGameBar1 = ObjectFactory<MiniGameBar>::CreateObject();
	m_pHitPoint = ObjectFactory<HitPoint>::CreateObject();		

	m_pPlayer = ObjectFactory<Player>::CreateObject();
	PlayerPos = m_pPlayer->GetPosition();
	//offset = Vector3(5, 3);
	
	for (int i = 0; i < 4; i++)
	{
		m_pKey[i] = ObjectFactory<Key>::CreateObject();
	}
	m_pKeyUI = ObjectFactory<KeyUi>::CreateObject();

	Vector3 KeyPoint[4];
	{
		int i = 0;

		for (int _x = 1; _x < 3; _x++)
		{
			int x = rand() % (39 / 3) + (_x * (39 / 3) + 1);
			int y = rand() % (20 / 2);

			while (Map[y][x] == 1)
			{
				x = rand() % (39 / 3) + (_x * (39 / 3) + 1);
				y = rand() % (20 / 2);
			}	
			KeyPoint[i] = Vector3((float)x, (float)y);
			i++;
		}

		for (int _x = 0; _x < 2; _x++)
		{
			int x = rand() % (39 / 3) + (_x * (39 / 3) + 1);
			int y = rand() % (20 / 2) + (20 / 2);

			while (Map[y][x] == 1)
			{
				x = rand() % (39 / 3) + (_x * (39 / 3) + 1);
				y = rand() % (20 / 2) + (20 / 2);
			}
			KeyPoint[i] = Vector3((float)x, (float)y);
			i++;
		}
	}
	for (int i = 0; i < 4; i++)
	{	
		m_pKey[i]->SetPosition(Vector3((float)KeyPoint[i].x, (float)KeyPoint[i].y));
		((Key*)m_pKey[i])->SetGameLevel(i + 1);
	}

	for (int i = 1; i < 4; i++)
	{
		Vector3 WallPosition = m_pKey[i]->GetPosition();

		if (Map[(int)WallPosition.y][(int)WallPosition.x - 1] == 0)
		{
			Map[(int)WallPosition.y][(int)WallPosition.x - 1] = 7;
		}

		if (Map[(int)WallPosition.y][(int)WallPosition.x + 1] == 0)
		{
			Map[(int)WallPosition.y][(int)WallPosition.x + 1] = 7;
		}

		if (Map[(int)WallPosition.y - 1][(int)WallPosition.x] == 0)
		{
			Map[(int)WallPosition.y - 1][(int)WallPosition.x] = 7;
		}

		if (Map[(int)WallPosition.y + 1][(int)WallPosition.x] == 0)
		{
			Map[(int)WallPosition.y + 1][(int)WallPosition.x] = 7;
		}
	}
	
	KeyCount = 4;
	KeyEatCount = 0;

	isBreak = 7;

	Clear = false;
	ViewNextKey = false;

	for (int y = 0; y < 21; y++)
	{
		for (int x = 0; x < 41; x++)
		{
			if (Map[y][x] == 3)
			{
				EndPoint = Vector3((float)x, (float)y);
			}
		}
	}

	Time = GetTickCount64();
}

void ObjectManager::Update()
{
	if (Time + 25 < GetTickCount64())
	{
		if(!((KeyUi*)m_pKeyUI)->GetisAni())
		{			
			if (isBreak < 7)
			{
				BreakWall(isBreak);
			}
			
			m_pPlayer->Update();
		}
		
		//if (GetAsyncKeyState('Q'))
		//{
		//	EditMode = !EditMode;
		//}

		if (KeyEatCount >= 4)
		{			
			Transforms EndTile;
			EndTile.Position = EndPoint;
			EndTile.Scale = Vector3(1, 1);
			if (CollisionManager::CollisionRact(m_pPlayer->GetTrans(), EndTile))
			{
				Clear = true;
			}
		}
		Time = GetTickCount64();
	}
	if (m_isMiniGameMode)
	{
		MiniGameBar1->Update();
		m_pHitPoint->Update();
	}

	if (!m_isMiniGameMode)
	{
		PlayerPos = m_pPlayer->GetPosition();
		m_pKeyUI->Update();
	}
	
	// 시야를 rect로 할때
	/*if (!m_isMiniGameMode)
	{
		//플레이어의 위치에 따라 출력 범위 지정
		PlayerPos = m_pPlayer->GetPosition();
		DrawStart_x = int(PlayerPos.x - offset.x);
		if (offset.x > PlayerPos.x)
			DrawStart_x = 0;
		DrawStart_y = int(PlayerPos.y + offset.y);
		if (20 - offset.y < PlayerPos.y)
			DrawStart_y = 20;
		currentDrawX = DrawStart_x;
		currentDrawY = DrawStart_y;
		DrawEndY = int(PlayerPos.y - offset.y);
		if ((0 + offset.y) > PlayerPos.y)
			DrawEndY = 0;
		DrawEndX = int(PlayerPos.x + offset.x);
		if ((41 - offset.x) < PlayerPos.x)
			DrawEndX = 41;
	}*/
}

void ObjectManager::Render()
{
	if (!m_isMiniGameMode)
	{
		//rect view
		/*for (DrawStart_y = currentDrawY; DrawStart_y >= DrawEndY; DrawStart_y--)
		{
			for (DrawStart_x = currentDrawX; DrawStart_x <= DrawEndX; DrawStart_x++)
			{
				switch (Map[DrawStart_y][DrawStart_x])
				{
				case 0:
					DoubleBuffer::GetInstance()->WriteBuffer(
						DrawStart_x * 2, DrawStart_y, (char*)"·", 8);
					break;
				case 1:
					DoubleBuffer::GetInstance()->WriteBuffer(
						DrawStart_x * 2, DrawStart_y, (char*)"■", 4);
					break;
				case 2:
					DoubleBuffer::GetInstance()->WriteBuffer(
						DrawStart_x * 2, DrawStart_y, (char*)"○", 10);
					break;
				case 3:
					DoubleBuffer::GetInstance()->WriteBuffer(
						DrawStart_x * 2, DrawStart_y, (char*)"●", 11);
					break;
				case 4:
					DoubleBuffer::GetInstance()->WriteBuffer(
						DrawStart_x * 2, DrawStart_y, (char*)"¶", 15);
					break;
				}
			}
		}*/

		//circle view
		//if (!EditMode)
		{
			for (int y = 0; y < 21; y++)
			{
				for (int x = 0; x < 41; x++)
				{
					if (MathManager::GetDistance(PlayerPos, Vector3((float)x, (float)y)) <= 3)
					{
						switch (Map[y][x])
						{
						case 0:
							DoubleBuffer::GetInstance()->WriteBuffer(
								x * 2, y, (char*)"·", 8);
							break;
						case 1:
							DoubleBuffer::GetInstance()->WriteBuffer(
								x * 2, y, (char*)"■", 4);
							break;
						case 2:
							DoubleBuffer::GetInstance()->WriteBuffer(
								x * 2, y, (char*)"○", 10);
							break;
						case 3:
							DoubleBuffer::GetInstance()->WriteBuffer(
								x * 2, y, (char*)"●", 11);
							break;
						case 7:
							DoubleBuffer::GetInstance()->WriteBuffer(
								x * 2, y, (char*)"■", 9);
							break;
						}
					}

					if (ViewNextKey)
					{
						if (isBreak < 4)
						{
							if (MathManager::GetDistance(m_pKey[isBreak]->GetPosition(), Vector3((float)x, (float)y)) <= 2)
							{
								switch (Map[y][x])
								{
								case 0:
									DoubleBuffer::GetInstance()->WriteBuffer(
										x * 2, y, (char*)"·", 8);
									break;
								case 1:
									DoubleBuffer::GetInstance()->WriteBuffer(
										x * 2, y, (char*)"■", 4);
									break;
								case 2:
									DoubleBuffer::GetInstance()->WriteBuffer(
										x * 2, y, (char*)"○", 10);
									break;
								case 3:
									DoubleBuffer::GetInstance()->WriteBuffer(
										x * 2, y, (char*)"●", 11);
									break;
								case 7:
									DoubleBuffer::GetInstance()->WriteBuffer(
										x * 2, y, (char*)"■", 9);
									break;
								}

								m_pKey[isBreak]->Render();
							}
						}
						else
						{
							if (MathManager::GetDistance(EndPoint, Vector3((float)x, (float)y)) <= 2)
							{
								switch (Map[y][x])
								{
								case 0:
									DoubleBuffer::GetInstance()->WriteBuffer(
										x * 2, y, (char*)"·", 8);
									break;
								case 1:
									DoubleBuffer::GetInstance()->WriteBuffer(
										x * 2, y, (char*)"■", 4);
									break;
								case 2:
									DoubleBuffer::GetInstance()->WriteBuffer(
										x * 2, y, (char*)"○", 10);
									break;
								case 3:
									DoubleBuffer::GetInstance()->WriteBuffer(
										x * 2, y, (char*)"●", 11);
									break;
								case 7:
									DoubleBuffer::GetInstance()->WriteBuffer(
										x * 2, y, (char*)"■", 9);
									break;
								}
							}
						}
					}
				}
			}

			for (int i = 0; i < 4; ++i)
			{
				if (m_pKey[i] != nullptr)
				{
					if (MathManager::GetDistance(PlayerPos, m_pKey[i]->GetPosition()) <= 5)
						m_pKey[i]->Render();
				}
			}

		}
		/*if (EditMode)
		{
			for (int y = 0; y < 21; y++)
			{
				for (int x = 0; x < 41; x++)
				{
					{
						switch (Map[y][x])
						{
						case 0:
							DoubleBuffer::GetInstance()->WriteBuffer(
								x * 2, y, (char*)"·", 8);
							break;
						case 1:
							DoubleBuffer::GetInstance()->WriteBuffer(
								x * 2, y, (char*)"■", 4);
							break;
						case 2:
							DoubleBuffer::GetInstance()->WriteBuffer(
								x * 2, y, (char*)"○", 10);
							break;
						case 3:
							DoubleBuffer::GetInstance()->WriteBuffer(
								x * 2, y, (char*)"●", 11);
							break;
						case 7:
							DoubleBuffer::GetInstance()->WriteBuffer(
								x * 2, y, (char*)"■", 9);
							break;
						}
					}
				}
			}
			for (int i = 0; i < 4; ++i)
			{
				if (m_pKey[i] != nullptr)
				{
					m_pKey[i]->Render();
				}
			}
		}
		*/
		m_pKeyUI->Render();
	}
	if (m_isMiniGameMode)
	{
		MiniGameBar1->Render();	
		m_pHitPoint->Render();
	}

	m_pPlayer->Render();

}

void ObjectManager::Release()
{
	SAFE_RELEASE(m_pPlayer);
	SAFE_RELEASE(MiniGameBar1);
	SAFE_RELEASE(m_pHitPoint);

	for (int i = 0; i < KeyCount; i++)
	{
		SAFE_RELEASE(m_pKey[i]);
	}

	SAFE_RELEASE(m_pKeyUI);
}

void ObjectManager::BreakWall(int _index)
{
	if (_index < 4)
	{
		if (Map[(int)m_pKey[_index]->GetPosition().y][(int)m_pKey[_index]->GetPosition().x - 1] == 7)
		{
			Map[(int)m_pKey[_index]->GetPosition().y][(int)m_pKey[_index]->GetPosition().x - 1] = 0;
		}

		if (Map[(int)m_pKey[_index]->GetPosition().y][(int)m_pKey[_index]->GetPosition().x + 1] == 7)
		{
			Map[(int)m_pKey[_index]->GetPosition().y][(int)m_pKey[_index]->GetPosition().x + 1] = 0;
		}

		if (Map[(int)m_pKey[_index]->GetPosition().y - 1][(int)m_pKey[_index]->GetPosition().x] == 7)
		{
			Map[(int)m_pKey[_index]->GetPosition().y - 1][(int)m_pKey[_index]->GetPosition().x] = 0;
		}

		if (Map[(int)m_pKey[_index]->GetPosition().y + 1][(int)m_pKey[_index]->GetPosition().x] == 7)
		{
			Map[(int)m_pKey[_index]->GetPosition().y + 1][(int)m_pKey[_index]->GetPosition().x] = 0;
		}
	}
	if(_index >= 4)
	{
		Map[(int)EndPoint.y - 1][(int)EndPoint.x] = 0;	
	}

	m_pPlayer->SetColor(14);
	ViewNextKey = false;
	isBreak = 7;
}

void ObjectManager::InMiniGame(int _index)
{
	((HitPoint*)m_pHitPoint)->SetLevel(((Key*)m_pKey[_index])->GetGameLevel());
}

void ObjectManager::KeyErease(int _keyCount)
{	
	SAFE_RELEASE(m_pKey[_keyCount]);
	ViewNextKey = true;
	isBreak = _keyCount + 1;

	KeyEatCount++;
	
}

void ObjectManager::PlayKeyUiAni(Vector3 _startpos, int _keyCount)
{
	((KeyUi*)m_pKeyUI)->AddKeyCount();
	((KeyUi*)m_pKeyUI)->SetKeyAni(_startpos, m_pKey[_keyCount]->GetColor());
}

void ObjectManager::ReturnMaze()
{
	m_pPlayer->Initialize();

	PlayerPos = m_pPlayer->GetPosition();
//	offset = Vector3(5, 3);
	Time = GetTickCount64();
}