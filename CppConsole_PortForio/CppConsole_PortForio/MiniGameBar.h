#pragma once
#include "Object.h"

class MiniGameBar : public Object
{
	char* texture;

public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;

public:
	MiniGameBar();
	~MiniGameBar();
};

