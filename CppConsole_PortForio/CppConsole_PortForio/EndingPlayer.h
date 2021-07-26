#pragma once
#include "Object.h"

class EndingPlayer:public Object
{
	char* Texture;
	float Speed = 0.5f;

	ULONGLONG PlayerAniStartTime;
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

public:
	EndingPlayer();
	~EndingPlayer();
};

