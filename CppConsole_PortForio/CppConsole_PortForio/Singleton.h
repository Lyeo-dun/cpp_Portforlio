#pragma once

#define DECLARE_SINGLETON(type)			\
static type** GetInstance()					\
{											\
	static type* pInstance = new type;		\
											\
	if (pInstance == NULL)					\
		pInstance = new type;				\
											\
	return &pInstance;						\
}											\
static void DestroyInstance()				\
{											\
	type** ppInstance = GetInstance();		\
											\
	if ((*ppInstance) != NULL)				\
	{										\
		delete* ppInstance;					\
		ppInstance = NULL;					\
	}										\
}
#define GETSINGLETON(type) (*type::GetInstance())
#define DESTROYSINGLETON(type) (*type::GetInstance())->DestroyInstance()