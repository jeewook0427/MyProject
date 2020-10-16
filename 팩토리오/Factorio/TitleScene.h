#pragma once
#include "GameNode.h"
class Button;
class ButtonFunction;
class TitleScene : public GameNode
{
private:
	HBRUSH hBrush, hOldBrush;
	HPEN hPen, hOldPen;

	Image* bg;
	Image* menu;

	Button* button1;


	ARGUMENT_INFO* args1;
	ButtonFunction* btnFunc;

public:

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);



	TitleScene();
	~TitleScene();
};

