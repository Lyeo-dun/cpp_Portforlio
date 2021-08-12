#pragma once
#include "Headers.h"
#include "Define.h"

class Object;
class PrototypeManager
{
public:
	DECLARE_SINGLETON(PrototypeManager)

private:
	map<string, Object*> PrototypeList;

public:
	void Initialize();
	Object* FindObject(string _str);

private:
	PrototypeManager();
public:
	~PrototypeManager();
};

