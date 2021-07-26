#pragma once
#include "Object.h"
class UnderMessage : public Object
{
	char* Texture[3];

	float ColorAlpaValue;

	float Speed = 0.3f;

	ULONGLONG ExitTime;
	bool checkTime;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	

public:
	UnderMessage();
	virtual ~UnderMessage();
};

