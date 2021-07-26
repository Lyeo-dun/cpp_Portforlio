#pragma once
#include "Object.h"
class KeyUi : public Object
{
	map<string, char*> texture;

	int KeyCount;
	bool isAni;

	Vector3 KeyPos;
	int AfterKeyCount;
	int EatKeyColor;

	map<string, ULONGLONG> Time;
	bool checkAddTime;
public:
	void AddKeyCount() { AfterKeyCount += 1; }
	int GetKeyCount() { return KeyCount; }
	bool GetisAni() { return isAni; }
	void SetKeyAni(Vector3 _pos, int _color)
	{ 
		KeyPos = _pos;
		EatKeyColor = _color;
		isAni = true;
	}

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

public:
	KeyUi();
	~KeyUi();
};

