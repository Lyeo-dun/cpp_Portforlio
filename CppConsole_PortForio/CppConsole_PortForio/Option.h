#pragma once
#include "Scene.h"

class Option : public Scene
{
	ULONGLONG StartTime;
	ULONGLONG Time;

	vector<char*> Text;
	vector<Vector3> TextPos;
	
	char* Star;
	Vector3 StarPos;
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