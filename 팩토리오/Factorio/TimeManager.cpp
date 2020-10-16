#include "TimeManager.h"
#include "Timer.h"


HRESULT TimeManager::Init()
{
	timer = new Timer();
	timer->Init();

	return S_OK;
}

void TimeManager::Release()
{
	SAFE_DELETE(timer);
}

void TimeManager::Update(float lockFPS/* = 0.0f*/)
{
	if (timer)
	{
		timer->Tick(lockFPS);
	}

}

void TimeManager::Render(HDC hdc)
{

	if (timer)
	{
		SetBkMode(hdc, TRANSPARENT);

		/*wsprintf(strText, "FPS : %d", timer->GetFrameRate());
		TextOut(hdc, 10, 10, strText, strlen(strText));

		sprintf_s(strText, "WorldTime : %f", timer->GetWorldTime());
		TextOut(hdc, 10, 30, strText, strlen(strText));*/
	}

}

float TimeManager::GetDeltaTime()
{
	if (timer)
		return timer->GetDeltaTime();

	return 0.0f;
}

TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}
