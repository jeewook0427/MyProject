#pragma once
#include "pch.h"
class ButtonFunction
{

public:
	void ChangeScene(const char* sceneName, const char* loadingName);	// const char�� ����ȯ
	void QuitProgram(void);

	ButtonFunction();
	~ButtonFunction();
};

