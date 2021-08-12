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
	//�Ѿ��� ���� �ε����� �� �����ϱ�!
	list<Object*> EnableList; //���� ����� ������Ʈ ����Ʈ(������ �� ������Ʈ ����Ʈ)
	list<Object*> DesableList; //����� ��ģ ������Ʈ ����Ʈ

	while (true)
	{
		system("cls");

		Output(2, 15, "��");

		check = false;

		//Ű �Է� �̺�Ʈ
		if (GetAsyncKeyState(VK_RETURN))
			check = true;//�ѹ��� �Է¹���

		if (check)
		{
			//DesableList�� �ִ��� Ȯ��
			if (DesableList.empty())
			{
				//���ٸ� ���ο� ������Ʈ�� �����
				for (int i = 0; i < 5; ++i)
				{
					DesableList.push_back(new Object);
				}
			}

			//�߰��� ������Ʈ �ϳ� ����
			list<Object*>::iterator iter = DesableList.begin();

			//�ʱ�ȭ
			(*iter)->Initialize();

			//����� ����Ʈ �߰�
			EnableList.push_back((*iter));
			//���� ����Ʈ������ ����
			DesableList.pop_front();

		}

		//Render
		for (list<Object*>::iterator iter = EnableList.begin(); iter != EnableList.end();/*������ ���� ����*/)
		{
			(*iter)->Update();
			(*iter)->Output();

			//������Ʈ�� value���� ���� �� �̻��� �ȴٸ� 
			if ((*iter)->GetPosition().x > 120 - (*iter)->GetScale().x)
			{
				//���� ����Ʈ���� DesableList�� �ű�
				DesableList.push_back((*iter));
				//���� ����Ʈ���� ����
				iter = EnableList.erase(iter);
			}
			else
				++iter; //������
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