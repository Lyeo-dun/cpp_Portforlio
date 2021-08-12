#include <iostream>
#include <Windows.h>
#include <list>
#include <map>
#include <string>

using namespace std;

template<typename T>
void Safe_Delete(T& _obj)
{
	delete (_obj);
	_obj = NULL;
}
#define SAFE_DELETE(type) Safe_Delete(type)

struct Vector3
{
	float x, y, z;

	Vector3() {}
	Vector3(float _x, float _y, float _z = 0) : x(_x), y(_y), z(_z) {}
};
struct Transform
{
	Vector3 Position;
	Vector3 Scale;
};
class Object
{
private:
	string Texture;
	Transform Transinfo;
public:
	void Initialize()
	{
		Texture = "-->";
		Transinfo.Position = Vector3(2, 15);
		Transinfo.Scale = Vector3(Texture.length(), 1);
	}
	void Update()
	{
		Transinfo.Position.x += 2.0f;
	}
	void Output()
	{
		COORD Pos = { Transinfo.Position.x, Transinfo.Position.y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

		cout << Texture << endl;
	}

	Vector3 GetPosition() { return Transinfo.Position; }
	void SetPosition(Vector3 _Pos) { Transinfo.Position = _Pos; }
	Vector3 GetScale() { return Transinfo.Scale; }
	Vector3 SetScale(Vector3 _Scale) { Transinfo.Scale = _Scale; }

public:
	Object() {}
	~Object() {}
};

bool check = false;
int Count = 0;

void Output(float _x, float _y, string _str);

int main(void)
{
	//총알이 벽에 부딪혔을 때 삭제하기!
	list<Object*> EnableList; //실제 사용한 오브젝트 리스트(랜더링 될 오브젝트 리스트)
	list<Object*> DesableList; //사용을 마친 오브젝트 리스트

	while (true)
	{
		system("cls");

		Output(2, 15, "◎");

		check = false;

		//키 입력 이벤트
		if (GetAsyncKeyState(VK_RETURN))
			check = true;//한번만 입력받음

		if (check)
		{
			//DesableList가 있는지 확인
			if (DesableList.empty())
			{
				//없다면 새로운 오브젝트를 만든다
				for (int i = 0; i < 5; ++i)
				{
					DesableList.push_back(new Object);
				}
			}

			//추가된 오브젝트 하나 선택
			list<Object*>::iterator iter = DesableList.begin();

			//초기화
			(*iter)->Initialize();

			//사용할 리스트 추가
			EnableList.push_back((*iter));
			//현재 리스트에서는 삭제
			DesableList.pop_front();

		}

		//Render
		for (list<Object*>::iterator iter = EnableList.begin(); iter != EnableList.end();/*증감문 따로 제어*/)
		{
			(*iter)->Update();
			(*iter)->Output();

			//오브젝트의 value값이 일정 값 이상이 된다면 
			if ((*iter)->GetPosition().x > 120 - (*iter)->GetScale().x)
			{
				//현재 리스트에서 DesableList로 옮김
				DesableList.push_back((*iter));
				//현재 리스트에서 삭제
				iter = EnableList.erase(iter);
			}
			else
				++iter; //증감문
		}

		{
			string descount = "Desable size: ";
			descount += to_string(DesableList.size());
			Output(4, 2, descount);

			descount = "Enable size: " + to_string(EnableList.size());
			Output(4, 3, descount);
		}

		Sleep(50);
	}

	for (list<Object*>::iterator iter = DesableList.begin(); iter != DesableList.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	DesableList.clear();

	for (list<Object*>::iterator iter = EnableList.begin(); iter != EnableList.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	EnableList.clear();

	return 0;
}

void Output(float _x, float _y, string _str)
{
	COORD Pos = { _x, _y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	cout << _str << endl;
}