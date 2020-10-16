#pragma once
#include "SingletonBase.h"
#include "pch.h"

class Timer;
class TimeManager : public SingletonBase<TimeManager>
{
private:

	Timer* timer;

	char strText[256];

	float testTime;
	bool isTestStart;


public:

	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update(float lockFPS = 0.0f);		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	float GetDeltaTime();
	void SetIsTestStart(bool b) { isTestStart = b; }
};

