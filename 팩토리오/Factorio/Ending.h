#pragma once
#include "pch.h"


class Ending
{
private:
	Image* greenBox;

	bool isRender;

	Image* endingMenu;
	char strText[256];

	Image* replayBtImg;
	Image* quitBtImg;
	RECT replayBtRc;
	RECT quitBtRc;
	BUTTON_STATE replayBtState;
	BUTTON_STATE quitBtState;

public:
	void Update();
	void Render(HDC hdc);

	Ending();
	~Ending();
};

