#include <iostream>
#include <Windows.h>
#include <list>

using namespace std;

template<typename T>
void Safe_Delete(T& _obj)
{
	delete (_obj);
	_obj = NULL;
}
#define SAFE_DELETE(type) Safe_Delete(type)

struct ObjectPool
{
	int Key;
	int Value;
	bool Active;

	ObjectPool() : Key(0), Value(0), Active(false) {}
	ObjectPool(int _Key, int _Value, bool _Active) : Key(_Key), Value(_Value), Active(_Active) {}
	~ObjectPool() {}
};

bool check = false;
int Count = 0;

int main(void)
{
	//배열은 리스트, 삭제는 #define safe delete
	list<ObjectPool*> Array;

	while (true)
	{
		system("cls");

		check = false;

		if (GetAsyncKeyState(VK_RETURN))
			check = true;
		
		if (check)
		{
			if (Array.empty())
			{
				ObjectPool* pTmp = new ObjectPool(Count++, 0, false);
				Array.push_back(pTmp);
			}
			else 
			{
				list<ObjectPool*>::iterator iter = Array.begin();
				for (iter = Array.begin(); iter != Array.end(); ++iter)
				{
					if (!(*iter)->Active)
					{
						(*iter)->Active = true;
						(*iter)->Value = 0;
						break;
					}
				}
				if (iter == Array.end())
				{
					ObjectPool* pTmp = new ObjectPool(Count++, 0, false);
					Array.push_back(pTmp);
				}
			}
		}


		for (list<ObjectPool*>::iterator iter = Array.begin(); iter != Array.end(); ++iter)
		{
			if ((*iter)->Active)
			{
				(*iter)->Value++;
				cout << "Key: " << (*iter)->Key << ", Value: " << (*iter)->Value << endl << endl;;

				if ((*iter)->Value >= 50)
				{
					(*iter)->Active = false;
					(*iter)->Value = 0;
				}
			}
		}

		Sleep(50);
	}

	for (list<ObjectPool*>::iterator iter = Array.begin(); iter != Array.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	Array.clear();

	return 0;
}