#pragma once
#include "Scene.h"

class Option : public Scene
{
	ULONGLONG StartTime;
	ULONGLONG Time;

	char* Option_Button[2];
	Transforms Option_Trans[2];

	char* Star;
	Transforms Star_Trans;
	int StarColor;

	int Choice;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

public:
	Option();
	~Option();
};