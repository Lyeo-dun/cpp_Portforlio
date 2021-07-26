#pragma once
#include "Object.h"
class HitPoint : public Object
{
	char* texture;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

public:
	void SetLevel(int _level);
public:
	HitPoint();
	~HitPoint();
};

