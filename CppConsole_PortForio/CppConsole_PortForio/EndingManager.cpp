#include "EndingManager.h"
#include "ObjectFactory.h"
#include "EndingPlayer.h"
#include "MathManager.h"
#include "DoubleBuffer.h"
#include "StarParticle.h"
#include "TextMessage.h"


EndingManager* EndingManager::m_pInstance = nullptr;

EndingManager::EndingManager()
{
}

EndingManager::~EndingManager()
{
}

void EndingManager::Initialize()
{
	
	for (int y = 0; y < 21; y++)
	{
		for (int x = 0; x < 41; x++)
		{
			if (Map[y][x] == 3)
			{
				StartPoint = Vector3((float)x, (float)y);
			}
		}
	}

	isPlayerAni = true;
	isSideAni = false;

	m_pPlayer = ObjectFactory<EndingPlayer>::CreateObject();
	m_pPlayer->SetPosition(StartPoint);
	ViewRange = 3.0f;
	MaxViewRange = MathManager::GetDistance(Vector3(0, 0), Vector3(41, 21)) / 2;
	checkViewRange = false;

	D1_X = Vector3(82, 21);
	D2_Y = Vector3(0, -21);

	for (int i = 0; i < 8; ++i)
	{
		m_pParticle[i] = ObjectFactory<StarParticle>::CreateObject();
	}

	((StarParticle*)m_pParticle[0])->SetDirection(Vector3(1, 1));
	((StarParticle*)m_pParticle[1])->SetDirection(Vector3(1, -1));
	((StarParticle*)m_pParticle[2])->SetDirection(Vector3(-1, -1));
	((StarParticle*)m_pParticle[3])->SetDirection(Vector3(-1, 1));
	((StarParticle*)m_pParticle[4])->SetDirection(Vector3(-1, 0));
	((StarParticle*)m_pParticle[5])->SetDirection(Vector3(1, 0));
	((StarParticle*)m_pParticle[6])->SetDirection(Vector3(0, -1));
	((StarParticle*)m_pParticle[7])->SetDirection(Vector3(0, 1));

	
	isParticle = false;
	ParticleControl = 1;

	m_pTextMessage = ObjectFactory<TextMessage>::CreateObject();
	isTextMessage = false;

	isExit = false;

	Choice = 0;
	ChoiceMenu[0] = (char*)"메뉴 이동";
	ChoiceMenu[1] = (char*)"게임 종료";
	Choice_Pos = Vector3(41, (m_pTextMessage->GetPosition().y + m_pTextMessage->GetScale().y / 2) + 3);

	Star = (char*)"★";
	Star_Pos = Vector3(41 - (float)strlen(ChoiceMenu[0])/2 - 3, Choice_Pos.y - 1.0f);
	star_y = 1;
	Star_Color = rand() % 6 + 9;
	isSelectMenu = false;

	FrameTime = GetTickCount64();
}

void EndingManager::Update()
{

	if (FrameTime + 50 < GetTickCount64())
	{
		m_pPlayer->Update();

		if (!isPlayerAni)
		{
			if (!checkViewRange)
			{
				MaxViewRange = MathManager::GetDistance(Vector3(0, 0), Vector3(41, 21));
				isSideAni = true;
				checkViewRange = true;
			}
		}
		if (isSideAni)
		{
			D1_X.x -= 2;
			D2_Y.y += 1;
		}

		if (D2_Y.y >= 20)
		{
			isSideAni = false;
			isParticle = true;
		}

		if (isParticle)
		{
			for (int i = 0; i < ParticleControl; ++i)
			{
				m_pParticle[i]->Update();
			}

			if (ParticleControl < 8)
			{
				ParticleControl += 1;
			}

			for (int i = 0; i < 8; ++i)
			{
				if (((StarParticle*)m_pParticle[i])->GetInParticleAni())
				{
					break;
				}

				if (i == 7)
				{
					isParticle = false;
					isTextMessage = true;
				}
			}
		}

		if (isTextMessage)
		{
			m_pTextMessage->Update();
		}

		if (isSelectMenu)
		{
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (star_y < 2)
				{
					star_y++;
					Star_Pos.y++;
					Star_Color++;
					if (Star_Color > 14)
					{
						Star_Color = 9;
					}
				}
			}
			if (GetAsyncKeyState(VK_UP))
			{
				if (star_y > 1)
				{
					star_y--;
					Star_Pos.y--;
					Star_Color++;
					if (Star_Color > 14)
					{
						Star_Color = 9;
					}
				}
			}
			if (GetAsyncKeyState(VK_RETURN))
			{
				Choice = star_y;
			}
		}
		FrameTime = GetTickCount64();
	}
	
}

void EndingManager::Render()
{
	if (isPlayerAni)
	{
		for (int y = 0; y < 21; y++)
		{
			for (int x = 0; x < 41; x++)
			{
				if (MathManager::GetDistance(m_pPlayer->GetPosition(), Vector3((float)x, (float)y)) <= ViewRange)
				{
					switch (Map[y][x])
					{
					case 0:
						DoubleBuffer::GetInstance()->WriteBuffer(
							(int)x * 2, (int)y, (char*)"·", 8);
						break;
					case 1:
						DoubleBuffer::GetInstance()->WriteBuffer(
							(int)x * 2, (int)y, (char*)"■", 4);
						break;
					case 2:
						DoubleBuffer::GetInstance()->WriteBuffer(
							(int)x * 2, (int)y, (char*)"○", 10);
						break;
					case 3:
						DoubleBuffer::GetInstance()->WriteBuffer(
							(int)x * 2, (int)y, (char*)"●", 11);
						break;
					case 7:
						DoubleBuffer::GetInstance()->WriteBuffer(
							(int)x * 2, (int)y, (char*)"■", 9);
						break;
					}
				}
			}
		}
		m_pPlayer->Render();
	}
	else if(isSideAni)
	{
		for (int y = 0; y < 21; y++)
		{
			for (int x = 0; x < 41; x++)
			{
				if (MathManager::GetisTriangleRange(Vector3((float)x, (float)y), D1_X, D2_Y))
				{
					switch (Map[y][x])
					{
					case 0:
						DoubleBuffer::GetInstance()->WriteBuffer(
							(int)x * 2, (int)y, (char*)"·", 8);
						break;
					case 1:
						DoubleBuffer::GetInstance()->WriteBuffer(
							(int)x * 2, (int)y, (char*)"■", 4);
						break;
					case 2:
						DoubleBuffer::GetInstance()->WriteBuffer(
							(int)x * 2, (int)y, (char*)"○", 10);
						break;
					case 3:
						DoubleBuffer::GetInstance()->WriteBuffer(
							(int)x * 2, (int)y, (char*)"●", 11);
						break;
					case 7:
						DoubleBuffer::GetInstance()->WriteBuffer(
							(int)x * 2, (int)y, (char*)"■", 9);
						break;
					}

				}
			}
		}
		m_pPlayer->Render();
	}
	else if (isParticle)
	{
		for (int i = 0; i < ParticleControl; ++i)
		{
			m_pParticle[i]->Render();
		}
	}
	else if (isTextMessage)
	{
		m_pTextMessage->Render();
	}
	else if (isSelectMenu)
	{
		m_pTextMessage->Render();

		for (int i = 0; i < 2; ++i)
		{
			DoubleBuffer::GetInstance()->WriteBuffer(int(Choice_Pos.x - strlen(ChoiceMenu[i])/2), int((Choice_Pos.y - 1) + i), ChoiceMenu[i], 8);
			if (i == star_y - 1)
			{
				DoubleBuffer::GetInstance()->WriteBuffer(int(Choice_Pos.x - strlen(ChoiceMenu[i])/2), int((Choice_Pos.y - 1) + i), ChoiceMenu[i]);
			}
		}

		DoubleBuffer::GetInstance()->WriteBuffer(int(Star_Pos.x), int(Star_Pos.y), Star, Star_Color);
	}

}

void EndingManager::AddViewRange(const float _range)
{
	if (ViewRange < MaxViewRange)
		ViewRange += _range;
	else
	{
		ViewRange = MaxViewRange;
		isPlayerAni = false;
	}
}

void EndingManager::Release()
{
	SAFE_RELEASE(m_pPlayer);

	for (int i = 0; i < 8; i++)
	{
		SAFE_RELEASE(m_pParticle[i]);
	}

	SAFE_RELEASE(m_pTextMessage);
}

Vector3 EndingManager::GetPlayerPos() { return m_pPlayer->GetPosition(); }