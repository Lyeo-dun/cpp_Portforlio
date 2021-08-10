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

int main(void)
{
	//배열은 리스트, 삭제는 #define safe delete
	list<ObjectPool*> Array;

	{
		int i = 0;
		for (i = 0; i < 128; ++i)
		{
			Array.push_back(new ObjectPool);
		}
		i = 0;
		for (list<ObjectPool*>::iterator iter = Array.begin(); iter != Array.end(); ++iter)
		{
			(*iter)->Active = false;
			(*iter)->Key = i;
			(*iter)->Value = 0;

			i++;
		}
	}

	while (true)
	{
		system("cls");

		if (GetAsyncKeyState(VK_RETURN))
			for (list<ObjectPool*>::iterator iter = Array.begin(); iter != Array.end(); ++iter)
			{
				if (!(*iter)->Active)
				{
					(*iter)->Active = true;
					break;
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