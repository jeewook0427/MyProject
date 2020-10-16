#include "Timer.h"
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib") //���� Ÿ�̸� �������� ��. �Ӽ�->��Ŀ->�Է�->�߰� ���Ӽ����� �߰��ϴ°� �ڵ�� ǥ��.

HRESULT Timer::Init()
{
	//bool	isHardware;			// ���� Ÿ�̸Ӹ� �� �� �ִ��� ����.
	//float	timeScale;			// ��� �������� �ʴ� �������� ����� �������� �ð������� ��ȯ
	//float	timeElapsed;		// ������ �ð��� ���� �ð��� ������� ����. --> DeltaTime�� �ȴ�.
	//__int64	currTime;			// ���� �ð� (���� Ÿ�̸� ��)
	//__int64	lastTime;			// ���� �ð� (���� Ÿ�̸� ��)
	//__int64	periodFrequency;	// ���� Ÿ�̸��� ���ļ� (�ʴ� ������), �������� ������ 0��ȯ.


	 //������ ���ѿ� ���� ����
	frameRate = 0;
	FPSFrameCount = 0;
	FPSTimeElapsed = 0;
	worldTime = 0;

	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
	{
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime); // ����ð�(�������� ������)
		timeScale = 1.0f / periodFrequency;
	}
	else
	{
		isHardware = false;
		lastTime = timeGetTime(); // 1�� �ڿ� ~ 1000�� �ɰ�
		timeScale = 0.001f;
	}

	return S_OK;
}

void Timer::Tick(float lockFPS)
{
	if (isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	}
	else
	{
		currTime = timeGetTime();
	}

	timeElapsed = (currTime - lastTime) * timeScale;

	if (lockFPS > 0.0f)
	{
		while (timeElapsed < (1.0f / lockFPS))
		{
			if (isHardware)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
			}
			else
			{
				currTime = timeGetTime();
			}

			timeElapsed = (currTime - lastTime) * timeScale;
		}
	}

	worldTime += timeElapsed;

	FPSFrameCount++;
	FPSTimeElapsed += timeElapsed;

	if (FPSTimeElapsed > 1.0f) //1�ʰ� �ɶ�����
	{
		frameRate = FPSFrameCount; // 1�ʿ� �������� ������ �ƴ°�..
		FPSFrameCount = 0;
		FPSTimeElapsed = 0;
	}

	lastTime = currTime;
}
