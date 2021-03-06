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
	//	cout << "국어 점수 : " << iter->Kor << endl;
	//	cout << "영어 점수 : " << iter->Eng << endl;
	//	cout << "수학 점수 : " << iter->Math << endl << endl;
	//}

	//** 읽어온 데이터를 각각의 점수에 따라 내림차순 정렬을 할것이다.
	//** 국어, 영어, 수학 점수별로 선택한 후 선택된 과목의 점수를 내림차순 정렬할것.
	{

		list<StudentInfo*> StdSortList;

		StdSortList = StudentList;

		cout << "정렬 기준을 선택해주세요!" << endl;
		cout << "1. 국어 점수" << endl;
		cout << "2. 영어 점수" << endl;
		cout << "3. 수학 점수" << endl;
		cout << "4. 종료!" << endl;

		int Choice = 0;
		cin >> Choice;

		
		switch (Choice)
		{
		case 1:
			StdSortList.sort(KorComp);
			break;
		case 2:
			StdSortList.sort(EngComp); //가장 효율적임
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
		
		//정렬한 것 출력
		/*for (list<StudentInfo*>::iterator iter = StdSortList.begin();
			iter != StdSortList.end(); ++iter)
		{
			cout << (*iter)->Index << " : " << (*iter)->Name << endl;
			cout << "국어 점수 : " << (*iter)->Kor << endl;
			cout << "영어 점수 : " << (*iter)->Eng << endl;
			cout << "수학 점수 : " << (*iter)->Math << endl << endl;
		}*/
	 

		//map에 과목별로 push
		for (list<StudentInfo*>::iterator iter = StdSortList.begin();
			iter != StdSortList.end(); ++iter)
		{
			InputMap("국어", (*iter)->Kor);
			InputMap("영어", (*iter)->Eng);
			InputMap("수학", (*iter)->Math);
		}

		//맵 출력
		for (map<string, list<int>>::iterator iter = StudentMap.begin();
			iter != StudentMap.end(); ++iter)
		{
			for (list<int>::iterator iter2 = iter->second.begin();
				iter2 != iter->second.end(); ++iter2)
			{
				cout << iter->first << " 점수 : " << (*iter2) << endl;
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
				//데이터 순번이 바뀌는 것 자체가 문제는 x
				//이것말고는 다른 백업 데이터가 있는 것도 아님
				//따라서 새로운 컨테이너에서 복사해서 정렬하는게 맞는 것
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
	//** 에디터를 불러온다.
	FILE* pFileCSV = fopen("StudenInfoList.csv", "r");

	if (pFileCSV == nullptr)
		return;

	//** 파일을 완전이 읽어온다.
	while (!feof(pFileCSV))
	{
		StudentInfo* Info = new StudentInfo;

		char buffer[128] = "";

		fscanf(pFileCSV, "%d,%d,%d,%d,%s",
			&Info->Index, &Info->Kor, &Info->Eng, &Info->Math, buffer);

		//** 읽어온 문자열을 포인터에 맞게 변경한다.
		Info->Name = new char[4];
		strcpy(Info->Name, buffer);

		//** 리스트에 추가한다.
		StudentList.push_back(Info);
	}

	StudentList.pop_back();

	//** 파일을 닫는다.
	fclose(pFileCSV);
}
