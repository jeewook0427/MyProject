#include "ButtonFunction.h"
#include "pch.h"

//void ButtonFunction::ChangeScene()
//{
//	SceneManager::GetSingleton()->ChangeScene("��Ʋ", "�ε�1");
//}
//
//void ButtonFunction::QuitProgram()
//{
//	if (MessageBox(g_hWnd, "���α׷��� �����Ͻðڽ��ϱ�?", "����Ȯ��", MB_OKCANCEL) == IDOK)
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
	if (MessageBox(g_hWnd, "���α׷��� �����Ͻðڽ��ϱ�?", "����Ȯ��", MB_OKCANCEL) == IDOK)
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
