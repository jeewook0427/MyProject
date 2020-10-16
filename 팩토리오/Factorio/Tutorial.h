#pragma once
#include "SingletonBase.h"
#include "pch.h"

#define Q_NUM 15

#define Q_START_X 0
#define Q_START_Y 500
#define Q_WIDTH 200
#define Q_HEIGHT 50

class Image;
class Tutorial : public SingletonBase<Tutorial>
{
private:
	Image* grayBox;
	Image* greenBox;

	bool startQuest[Q_NUM];
	bool succeedQuest[Q_NUM];

	bool renderQBox[3];
	POINT renderPos[3];
	char strText[3][256];
	bool succeedQuest_box[3];

	int helpIndex;
	bool helpOpen;
	RECT helpBox;
	Image* helpImage[3];
	char helpText[256];

	bool openBtOn;
	RECT openBtRc;

public:
	void SucceedQuest_0();
	void SucceedQuest_1();
	void SucceedQuest_2();
	void SucceedQuest_3();
	void SucceedQuest_4();
	void SucceedQuest_5();
	void SucceedQuest_6();
	void SucceedQuest_7();
	void SucceedQuest_8();
	void SucceedQuest_9();
	void SucceedQuest_10();
	void SucceedQuest_11();
	void SucceedQuest_12();
	void SucceedQuest_13();
	void SucceedQuest_14();

	void Update();
	void Render(HDC hdc);
	void HelpRender(HDC hdc);

	void SetHelpOpen() { helpOpen = !helpOpen; }

	Tutorial();
	~Tutorial() {}
};

