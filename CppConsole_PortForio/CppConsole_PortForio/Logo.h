#pragma once
#include "Scene.h"

class Logo : public Scene
{
	int StarColor;
	vector<char*> LogoText;
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

