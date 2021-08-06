#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <fstream>

using namespace std;

struct StudentInfo
{
	char* Name;
	int Index;

	int Kor;
	int Eng;
	int Math;
};


list<StudentInfo*> StudentList;
map<string, list<int>> StudentMap;


void LoadDate();
void ScoreSwap(StudentInfo* _A, StudentInfo* _B);
void InputMap(string _Key, int Score);

bool KorComp(const StudentInfo* _A, const StudentInfo* _B);
bool EngComp(const StudentInfo* _A, const StudentInfo* _B);

int main(void)
{
	LoadDate();


	//for (list<StudentInfo>::iterator iter = StudentList.begin();
	//	iter != StudentList.end(); ++iter)
	//{
	//	cout << iter->Index << " : " << iter->Name << endl;
	//	cout << "���� ���� : " << iter->Kor << endl;
	//	cout << "���� ���� : " << iter->Eng << endl;
	//	cout << "���� ���� : " << iter->Math << endl << endl;
	//}

	//** �о�� �����͸� ������ ������ ���� �������� ������ �Ұ��̴�.
	//** ����, ����, ���� �������� ������ �� ���õ� ������ ������ �������� �����Ұ�.
	{

		list<StudentInfo*> StdSortList;

		StdSortList = StudentList;

		cout << "���� ������ �������ּ���!" << endl;
		cout << "1. ���� ����" << endl;
		cout << "2. ���� ����" << endl;
		cout << "3. ���� ����" << endl;
		cout << "4. ����!" << endl;

		int Choice = 0;
		cin >> Choice;

		
		switch (Choice)
		{
		case 1:
			StdSortList.sort(KorComp);
			break;
		case 2:
			StdSortList.sort(EngComp); //���� ȿ������
			break;
		case 3:
			for (list<StudentInfo*>::iterator iter = StdSortList.begin(); iter != StdSortList.end(); ++iter)
			{
				for (list<StudentInfo*>::iterator iter2 = iter; iter2 != StdSortList.end(); ++iter2)
				{
					if ((*iter)->Math < (*iter2)->Math)
					{
						StudentInfo* pTemp = (*iter);
						(*iter) = (*iter2);
						(*iter2) = pTemp;
					}
				}
			}
			break;
		case 4:
			exit(NULL);
			break;
		}
		
		//������ �� ���
		/*for (list<StudentInfo*>::iterator iter = StdSortList.begin();
			iter != StdSortList.end(); ++iter)
		{
			cout << (*iter)->Index << " : " << (*iter)->Name << endl;
			cout << "���� ���� : " << (*iter)->Kor << endl;
			cout << "���� ���� : " << (*iter)->Eng << endl;
			cout << "���� ���� : " << (*iter)->Math << endl << endl;
		}*/
	 

		//map�� ���񺰷� push
		for (list<StudentInfo*>::iterator iter = StdSortList.begin();
			iter != StdSortList.end(); ++iter)
		{
			InputMap("����", (*iter)->Kor);
			InputMap("����", (*iter)->Eng);
			InputMap("����", (*iter)->Math);
		}

		//�� ���
		for (map<string, list<int>>::iterator iter = StudentMap.begin();
			iter != StudentMap.end(); ++iter)
		{
			for (list<int>::iterator iter2 = iter->second.begin();
				iter2 != iter->second.end(); ++iter2)
			{
				cout << iter->first << " ���� : " << (*iter2) << endl;
			}
			cout << endl;
		}
	}


	return 0;
}
void InputMap(string _Key, int Score)
{
	map<string, list<int>>::iterator iter = StudentMap.find(_Key);

	if (iter == StudentMap.end())
	{
		list<int> _score;
		_score.push_back(Score);

		StudentMap.insert(make_pair(_Key, _score));
	}
	else
	{
		iter->second.push_back(Score);
	}
}
bool KorComp(const StudentInfo* _A, const StudentInfo* _B)
{
	/*for (list<StudentInfo>::iterator iter = StudentList.begin(); iter != StudentList.end(); ++iter)
	{
		for (list<StudentInfo>::iterator iter2 = iter; iter2 != StudentList.end(); ++iter2)
		{
			if ((*iter).Kor < (*iter2).Kor)
			{
				ScoreSwap((*iter), (*iter2));
				//������ ������ �ٲ�� �� ��ü�� ������ x
				//�̰͸���� �ٸ� ��� �����Ͱ� �ִ� �͵� �ƴ�
				//���� ���ο� �����̳ʿ��� �����ؼ� �����ϴ°� �´� ��
			}
		}
	}*/
	return _A->Kor > _B->Kor;
}
bool EngComp(const StudentInfo* _A, const StudentInfo* _B)
{
	return _A->Eng > _B->Eng;
}
void ScoreSwap(StudentInfo* _A, StudentInfo* _B)
{
	StudentInfo* Tmp = _A;

	_A = _B;
	_B = Tmp;
}

void LoadDate()
{
	//** �����͸� �ҷ��´�.
	FILE* pFileCSV = fopen("StudenInfoList.csv", "r");

	if (pFileCSV == nullptr)
		return;

	//** ������ ������ �о�´�.
	while (!feof(pFileCSV))
	{
		StudentInfo* Info = new StudentInfo;

		char buffer[128] = "";

		fscanf(pFileCSV, "%d,%d,%d,%d,%s",
			&Info->Index, &Info->Kor, &Info->Eng, &Info->Math, buffer);

		//** �о�� ���ڿ��� �����Ϳ� �°� �����Ѵ�.
		Info->Name = new char[4];
		strcpy(Info->Name, buffer);

		//** ����Ʈ�� �߰��Ѵ�.
		StudentList.push_back(Info);
	}

	StudentList.pop_back();

	//** ������ �ݴ´�.
	fclose(pFileCSV);
}
