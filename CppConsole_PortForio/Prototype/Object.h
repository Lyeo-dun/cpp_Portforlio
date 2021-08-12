#pragma once
#include "Headers.h"

class Object
{
private:
	string str;
	Transform Transinfo;
public:
	//클론 객체를 생성
	Object* Clone() { return new Object(*this); }
	
	Vector3 GetPosition() { return Transinfo.Position; }
	void SetPosition(Vector3 _Pos) { Transinfo.Position = _Pos; }
	Vector3 GetScale() { return Transinfo.Scale; }
	void SetScale(Vector3 _Scale) { Transinfo.Scale = _Scale; }

public:
	void Initialize();
	int Update();
	void Render(int n);

public:
	void SetIndex(int _index) { Transinfo.Index = _index; }

public:
	Object();
	Object(const Transform& _TransInfo) : Transinfo(_TransInfo) {}
	~Object();
};

