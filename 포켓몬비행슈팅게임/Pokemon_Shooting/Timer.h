#pragma once
#include "pch.h"

class Timer
{
private:
	bool	isHardware;			// 고성능 타이머를 쓸 수 있는지 여부.
	float	timeScale;			// 경과 진동수를 초당 진동수로 나누어서 진동수를 시간단위로 변환
	float	timeElapsed;		// 마지막 시간과 현재 시간의 경과량을 저장. --> DeltaTime이 된다.
	__int64	currTime;			// 현재 시간 (고성능 타이머 값)
	__int64	lastTime;			// 이전 시간 (고성능 타이머 값)
	__int64	periodFrequency;	// 고성능 타이머의 주파수 (초당 진동수), 지원하지 않으면 0반환.


	 //프레임 제한에 사용될 변수
	unsigned long frameRate;	 //프레임 주기
	unsigned long FPSFrameCount;
	float FPSTimeElapsed;
	float worldTime;			//이 프레임의 총 경과 시간

public:

	HRESULT Init();
	void Tick(float lockFPS = 0.0f); // 한 프레임 마다 시간을 젤 것. 프레임 제한할 때 몇으로 제한하겠다 라고 넣어주면됨.

	unsigned long GetFrameRate() { return frameRate; }
	float GetWolrdTime() { return worldTime; }
	float GetDeltaTime() { return timeElapsed; }

};

