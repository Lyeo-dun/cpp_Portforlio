#include "Headers.h"
#include "PrototypeManager.h"
#include "Object.h"

list<Object*> pObjList;

void Init(string _str)
{
	//원본 객체 찾기
	Object* pObj = GETSINGLETON(PrototypeManager)->FindObject(_str);

	//찾는 객체가 없다면 오류메세지 출력 후 함수 종료
	if (pObj == nullptr)
	{
		COORD Pos = { 50, 15 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

		cout << " 복제할 원본 객체가 없음 " << endl;
		return; //함수 종료
	}
	else //찾는 객체가 있다면 복사
	{
		int i = 0;
		for (i = 0; i < 3; ++i)
		{
			pObjList.push_back(pObj->Clone()); //참조된 원형 객체의 복사본 넘김			
		}
		i = 0;
		for (list<Object*>::iterator iter = pObjList.begin(); iter != pObjList.end(); ++iter)
		{
			(*iter)->Initialize(); //복사본 초기화
			(*iter)->SetIndex(i + 1); //복사본의 인덱스값을 변경
			i++;
		}
	}
}

int main(void)
{
	/*
	* 대량 생산을 위한 생산과정
	* objectpool은 사람이 생산하는 것과 같다
	* 하지만 prototype의 경우 기계를 들여놓는 것과 같음
	*/

	//Index 1, 2, 3으로 출력

	//prototype manager 초기화
	GETSINGLETON(PrototypeManager)->Initialize();

	Init("Object"); //그냥 가지고 오게 될 경우 없다면 에러가 날 것이기 때문에

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
* 초기구문
* 변경사항에 대한 구문
* 출력 구문
* 삭제
*/