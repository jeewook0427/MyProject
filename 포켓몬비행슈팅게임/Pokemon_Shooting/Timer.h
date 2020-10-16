#pragma once
#include "pch.h"

class Timer
{
private:
	bool	isHardware;			// ���� Ÿ�̸Ӹ� �� �� �ִ��� ����.
	float	timeScale;			// ��� �������� �ʴ� �������� ����� �������� �ð������� ��ȯ
	float	timeElapsed;		// ������ �ð��� ���� �ð��� ������� ����. --> DeltaTime�� �ȴ�.
	__int64	currTime;			// ���� �ð� (���� Ÿ�̸� ��)
	__int64	lastTime;			// ���� �ð� (���� Ÿ�̸� ��)
	__int64	periodFrequency;	// ���� Ÿ�̸��� ���ļ� (�ʴ� ������), �������� ������ 0��ȯ.


	 //������ ���ѿ� ���� ����
	unsigned long frameRate;	 //������ �ֱ�
	unsigned long FPSFrameCount;
	float FPSTimeElapsed;
	float worldTime;			//�� �������� �� ��� �ð�

public:

	HRESULT Init();
	void Tick(float lockFPS = 0.0f); // �� ������ ���� �ð��� �� ��. ������ ������ �� ������ �����ϰڴ� ��� �־��ָ��.

	unsigned long GetFrameRate() { return frameRate; }
	float GetWolrdTime() { return worldTime; }
	float GetDeltaTime() { return timeElapsed; }

};

