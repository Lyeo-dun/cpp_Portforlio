#pragma once
#include "Headers.h"
#include "Singleton.h"

class DoubleBuffer
{
public:
	DECLARE_SINGLETON(DoubleBuffer)

private:
	int		m_iBufferIndex;		// ���� Index
	HANDLE	m_HBuffer[2];		// HANDLE

	// �ڵ��� ��ü���� � ����� �����ϱ� ���� �ٿ��� ������ ��ȣ. 
	// � ü���� �ο��ϴ� �ߺ����� �ʴ� ������.
	// �������� object�� structure ���� �����͸� ���� �ٷ����� ������ ���� ó��
	// ���輺 ������ ��ü�� ��Ī�ϴµ� �����͸� ���� �ʰ� ��ȣ�� �� ���̴�.
public:
	void CreateBuffer(const int& _width, const int& _height); // ���� ����
	void WriteBuffer(int x, int y, char* _str, int _color = 15/*����Ʈ �Ű�����*/);           // ���� ���� (���ڿ�)
	void WriteBuffer(int x, int y, int _ivalue, int _color = 15/*����Ʈ �Ű�����*/); // ���� ���� (����)
	void FlippingBuffer();                                  // ���� ��ȯ
	void ClearBuffer();                                     // ���� �����
	void DestroyBuffer();                                   // ���� ����

	bool MyCloseHandle(HANDLE& hFile);         // �����ϰ� CloseHandle ó��
	void SetColor(int color);
private:
	DoubleBuffer();
public:
	~DoubleBuffer();
};
