#include "ButtonFunction.h"
#include "pch.h"

//void ButtonFunction::ChangeScene()
//{
//	SceneManager::GetSingleton()->ChangeScene("배틀", "로딩1");
//}
//
//void ButtonFunction::QuitProgram()
//{
//	if (MessageBox(g_hWnd, "프로그램을 종료하시겠습니까?", "종료확인", MB_OKCANCEL) == IDOK)
//	{
//		PostQuitMessage(0);
//	}
//}

void ButtonFunction::ChangeScene(const char* sceneName, const char* loadingName)
{
	SceneManager::GetSingleton()->ChangeScene(sceneName, loadingName);
}

void ButtonFunction::QuitProgram(void)
{
	if (MessageBox(g_hWnd, "프로그램을 종료하시겠습니까?", "종료확인", MB_OKCANCEL) == IDOK)
	{
		PostQuitMessage(0);
	}
}

ButtonFunction::ButtonFunction()
{
}

ButtonFunction::~ButtonFunction()
{
}
