#pragma once
#include "Object.h"

class TextMessage : public Object
{
	Object* TopText;
	Object* UnderText;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	TextMessage();
	virtual ~TextMessage();

};

