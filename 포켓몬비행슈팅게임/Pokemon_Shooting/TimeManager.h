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

	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update(float lockFPS = 0.0f);		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	float GetDeltaTime();
	void SetIsTestStart(bool b) { isTestStart = b; }
};

