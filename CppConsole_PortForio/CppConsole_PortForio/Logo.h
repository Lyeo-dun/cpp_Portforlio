#pragma once
#include "Scene.h"

class Logo : public Scene
{
	int StarColor;
	char* LogoText[7];
	Transforms TransInfo;
	ULONGLONG Time;

	
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

public:
	Logo();
	~Logo();
};

