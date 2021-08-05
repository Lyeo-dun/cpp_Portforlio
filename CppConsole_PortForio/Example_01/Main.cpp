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


list<StudentInfo> StudentList;


void LoadDate();
void ScoreSwap(StudentInfo& _A, StudentInfo& _B);

void KorSort();
void EngSort();
void MathSort();

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

	while (true)
	{
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
			KorSort();
			break;
		case 2:
			EngSort();
			break;
		case 3:
			MathSort();
			break;
		case 4:
			exit(NULL);
			break;
		}
		

		for (list<StudentInfo>::iterator iter = StudentList.begin();
			iter != StudentList.end(); ++iter)
		{
			cout << iter->Index << " : " << iter->Name << endl;
			cout << "���� ���� : " << iter->Kor << endl;
			cout << "���� ���� : " << iter->Eng << endl;
			cout << "���� ���� : " << iter->Math << endl << endl;
		}

		system("pause");
		system("cls");
	}


	return 0;
}

void KorSort()
{
	for (list<StudentInfo>::iterator iter = StudentList.begin(); iter != StudentList.end(); ++iter)
	{
		for (list<StudentInfo>::iterator iter2 = iter; iter2 != StudentList.end(); ++iter2)
		{
			if ((*iter).Kor < (*iter2).Kor)
			{
				ScoreSwap((*iter), (*iter2));
			}
		}
	}
}
void EngSort()
{
	for (list<StudentInfo>::iterator iter = StudentList.begin(); iter != StudentList.end(); ++iter)
	{
		for (list<StudentInfo>::iterator iter2 = iter; iter2 != StudentList.end(); ++iter2)
		{
			if ((*iter).Eng < (*iter2).Eng)
			{
				ScoreSwap((*iter), (*iter2));
			}
		}
	}
}
void MathSort()
{
	for (list<StudentInfo>::iterator iter = StudentList.begin(); iter != StudentList.end(); ++iter)
	{
		for (list<StudentInfo>::iterator iter2 = iter; iter2 != StudentList.end(); ++iter2)
		{
			if ((*iter).Math < (*iter2).Math)
			{
				ScoreSwap((*iter), (*iter2));
			}
		}
	}
}
void ScoreSwap(StudentInfo& _A, StudentInfo& _B)
{
	StudentInfo Tmp = _A;

	_A = _B;
	_B = Tmp;
}

void LoadDate()
{
	//** �����͸� �ҷ��´�.
	FILE* pFileCSV = fopen("StudenInfoList.csv", "r");

	//** ������ ������ �о�´�.
	while (!feof(pFileCSV))
	{
		StudentInfo Info;

		char buffer[128] = "";

		fscanf(pFileCSV, "%d,%d,%d,%d,%s",
			&Info.Index, &Info.Kor, &Info.Eng, &Info.Math, buffer);


		//** �о�� ���ڿ��� �����Ϳ� �°� �����Ѵ�.
		Info.Name = new char[4];
		strcpy(Info.Name, buffer);

		//** ����Ʈ�� �߰��Ѵ�.
		StudentList.push_back(Info);
	}

	//** ������ �ݴ´�.
	fclose(pFileCSV);
}
