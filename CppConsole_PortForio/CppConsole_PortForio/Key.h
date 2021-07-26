#pragma once
#include "Object.h"
class Key : public Object
{
	char* texture;
	
	int MiniGameLevel;
public:
	void SetGameLevel(int _level) 
	{ 
		MiniGameLevel = _level; 

		switch (MiniGameLevel)
		{
		case 1:
			Color = 10;
			break;
		case 2:
			Color = 11;
			break;
		case 3:
			Color = 12;
			break;
		case 4:
			Color = 13;
			break;
		}
	}
	int GetGameLevel() { return MiniGameLevel; }

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

public:
	Key();
	~Key();
};

