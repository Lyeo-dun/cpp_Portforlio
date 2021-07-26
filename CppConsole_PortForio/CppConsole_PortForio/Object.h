#pragma once
#include "Headers.h"

class Object
{
protected:
	Transforms TransInfo;
	int Color;

public:
	virtual void Initialize()PURE;
	virtual void Update()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

public:
	Transforms GetTrans() { return TransInfo; }
	void SetPosition(const Vector3 _pos) { TransInfo.Position = _pos; }
	Vector3 GetPosition() const { return TransInfo.Position; }
	Vector3 GetScale()const { return TransInfo.Scale; }
	void SetScale(const Vector3 _scale) { TransInfo.Scale = _scale; }
	void SetColor(const int _color = 15) { Color = _color; }
	int GetColor() const { return Color; }
public:
	Object();
	virtual ~Object();
};

