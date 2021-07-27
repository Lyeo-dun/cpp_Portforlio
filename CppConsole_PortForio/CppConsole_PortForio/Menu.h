#pragma once
#include "Scene.h"

class Menu : public Scene
{

	map<string, vector<char*>> Text;
	
	int StarColor;
	
	map<string, Vector3> Trans;	

	bool Logo_Ani;
	bool ViewChioce;
	
	int Choice;

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

