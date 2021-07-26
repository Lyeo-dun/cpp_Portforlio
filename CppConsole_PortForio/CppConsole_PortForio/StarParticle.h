#pragma once
#include "Object.h"
class StarParticle : public Object
{
	Vector3 Direction;
	char* Texture;

	float Speed = 0.4f;

	bool inParticleAni;

	ULONGLONG Time;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void SetDirection(Vector3 _dir) { Direction = _dir; }
	bool GetInParticleAni() { return inParticleAni; }

public:
	StarParticle();
	virtual ~StarParticle();
};

