#pragma once
#include "pch.h"
class ButtonFunction
{

public:
	void ChangeScene(const char* sceneName, const char* loadingName);	// const char로 형변환
	void QuitProgram(void);

	ButtonFunction();
	~ButtonFunction();
};

