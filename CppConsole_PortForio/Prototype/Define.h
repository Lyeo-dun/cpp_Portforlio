#pragma once

#define DECLARE_SINGLETON(type)					\
static type** GetInstance()						\
{												\
	static type* pInstance = new type;			\
												\
	if (pInstance == nullptr)					\
		pInstance = new type;					\
												\
	return &pInstance;							\
}												\
static void DestroyInstance()					\
{												\
	type** ppInstance = GetInstance();			\
												\
	if (ppInstance != nullptr)					\
	{											\
		delete ppInstance;						\
		ppInstance = nullptr;					\
	}											\
}

#define GETSINGLETON(type) (*type::GetInstance())
#define DESTROYSINGLETON(type) (*type::GetInstance())->DestroyInstance()

template<typename T>
void Safe_Delete(T& _obj)
{
	delete (_obj);
	_obj = nullptr;
}
#define SAFE_DELETE(type) Safe_Delete(type)