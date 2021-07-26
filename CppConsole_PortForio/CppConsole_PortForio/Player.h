#pragma once
#include "Object.h"

class Player : public Object
{
	char* Texture;

	float MiniGame1_Speed;

	Vector3 CurrentPlayerPos;
	int CountKey;
	int CollisionKey;

	bool MiniGame_Move;

	ULONGLONG MiniGameStartTime;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

public:
	Player();
	~Player();
};

