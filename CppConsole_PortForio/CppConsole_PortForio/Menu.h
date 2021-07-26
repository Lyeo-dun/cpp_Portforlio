#pragma once
#include "Scene.h"

class Menu : public Scene
{
	char* LogoText[7];
	Transforms Logo_TransInfo;
	bool Logo_Ani;

	int Choice;
	char* ChoiceMenu[3];
	Transforms Choice_TransInfo;
	bool ViewChioce;
	
	char* Star;
	Transforms Star_TransInfo;
	int StarColor;

	ULONGLONG Time;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

public:
	Menu();
	~Menu();
};

