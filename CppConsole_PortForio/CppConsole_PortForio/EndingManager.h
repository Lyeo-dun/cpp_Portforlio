#pragma once
#include "Headers.h"
#include "Singleton.h"

class Object;
class EndingManager
{
public:
	DECLARE_SINGLETON(EndingManager)

private:
	int Map[21][41] =
	{
	{ 1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
	{ 1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1 },
	{ 1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1 },
	{ 1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1 },
	{ 1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1 },
	{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1 },
	{ 1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1 },
	{ 1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1 },
	{ 1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1 },
	{ 1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1 },
	{ 1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1 },
	{ 1,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1 },
	{ 1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1 },
	{ 1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1 },
	{ 1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1 },
	{ 1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1 },
	{ 1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1 },
	{ 1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1 }
	};

	Object* m_pPlayer;
	Vector3 StartPoint;
	bool isPlayerAni;

	vector<Object*> m_pParticle;
	int ParticleControl;
	bool isParticle;

	Object* m_pTextMessage;
	bool isTextMessage;

	Vector3 D1_X;
	Vector3 D2_Y;
	bool isSideAni;

	bool checkViewRange;
	float ViewRange;
	float MaxViewRange;


	int Choice;
	char* ChoiceMenu[2];
	Vector3 Choice_Pos;	

	char* Star;
	int star_y;
	Vector3 Star_Pos;
	int Star_Color;
	bool isSelectMenu;


	bool isReturnGame;
	bool isExit;

	ULONGLONG FrameTime;
public:
	void AddViewRange(const float _range);
	void SetPlayerAni(const bool _isAni) { isPlayerAni = _isAni; }
	bool GetPlayerAni() { return isPlayerAni; }
	int GetMap(const int _x, const int _y) { return Map[_y][_x]; }
	Vector3 GetPlayerPos();
	void SetTextureAni(bool _isTexture) { isTextMessage = _isTexture; }
	void SetSelectMenu(const bool _isMenu) { isSelectMenu = _isMenu; }
	int GetChoice() { return Choice; }

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

public:
	~EndingManager();
private:
	EndingManager();
};

