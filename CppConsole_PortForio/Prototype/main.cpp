#include "Headers.h"
#include "PrototypeManager.h"
#include "Object.h"

list<Object*> pObjList;

void Init(string _str)
{
	//���� ��ü ã��
	Object* pObj = GETSINGLETON(PrototypeManager)->FindObject(_str);

	//ã�� ��ü�� ���ٸ� �����޼��� ��� �� �Լ� ����
	if (pObj == nullptr)
	{
		COORD Pos = { 50, 15 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

		cout << " ������ ���� ��ü�� ���� " << endl;
		return; //�Լ� ����
	}
	else //ã�� ��ü�� �ִٸ� ����
	{
		int i = 0;
		for (i = 0; i < 3; ++i)
		{
			pObjList.push_back(pObj->Clone()); //������ ���� ��ü�� ���纻 �ѱ�			
		}
		i = 0;
		for (list<Object*>::iterator iter = pObjList.begin(); iter != pObjList.end(); ++iter)
		{
			(*iter)->Initialize(); //���纻 �ʱ�ȭ
			(*iter)->SetIndex(i + 1); //���纻�� �ε������� ����
			i++;
		}
	}
}

int main(void)
{
	/*
	* �뷮 ������ ���� �������
	* objectpool�� ����� �����ϴ� �Ͱ� ����
	* ������ prototype�� ��� ��踦 �鿩���� �Ͱ� ����
	*/

	//Index 1, 2, 3���� ���

	//prototype manager �ʱ�ȭ
	GETSINGLETON(PrototypeManager)->Initialize();

	Init("Object"); //�׳� ������ ���� �� ��� ���ٸ� ������ �� ���̱� ������

	{
		int i = 0;
		for (list<Object*>::iterator iter = pObjList.begin(); iter != pObjList.end(); ++iter)
			if ((*iter))
			{
				(*iter)->Render(i);
				i++;
			}
	}

	for (list<Object*>::iterator iter = pObjList.begin(); iter != pObjList.end(); ++iter)
	{
		SAFE_DELETE((*iter));
	}

	pObjList.clear();

	return 0;
}

/*
* �ʱⱸ��
* ������׿� ���� ����
* ��� ����
* ����
*/