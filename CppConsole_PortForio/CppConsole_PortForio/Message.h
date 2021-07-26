#pragma once
#include "Object.h"
class Message : public Object
{
	char* Texture[4];

	float ColorAlpaValue;

	float Speed = 0.3f;
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	Message();
	virtual ~Message();
};

