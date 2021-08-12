#include "PrototypeManager.h"
#include "Object.h"


PrototypeManager::PrototypeManager()
{
}

PrototypeManager::~PrototypeManager()
{
}

void PrototypeManager::Initialize()
{
	//** Prototype 생성
	Transform TransInfo;
	TransInfo.Position = Vector3(0.0f, 0.0f);

	PrototypeList["Object"] = new Object(TransInfo);
}

Object* PrototypeManager::FindObject(string _str)
{
	//** map에 오브젝트가 있는지 확인. 
	map<string, Object*>::iterator iter = PrototypeList.find(_str);

	//** 찾는 오브젝트가 없다면 nullptr 을 반환.
	if (iter == PrototypeList.end())
		return nullptr;

	//** 아니라면 찾은 오브젝트를 반환.
	return iter->second;
}