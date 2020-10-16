#pragma once
#include "GameNode.h"
#include "pch.h"
/*

함수포인터 (함수의 주소를 담는 변수)
포인터 (변수의 주소를 담는 변수)
int a = 10;
int* pA = &a;

int sum(int a, int b);
리턴타입 (*함수포인터이름) (매개변수1의 타입, 매개변수2의 타입);
int (*calculatePointer)(int, int);

void func(void);			// 함수의 원형을 선언
void (*funcPointer)(void);	// 함수포인터(변수)를 선언
funcPointer = func;			// 함수포인터에 함수의 주소를 대입

func();
funcPointer();				// == func();

void makeRect(void);
funcPointer = makeRect;
funcPointer();				// == makeRect();

*/

class Image;

class ButtonFunction;
class Button : public GameNode
{
private:
	BUTTON_STATE state;
	Image* image;
	RECT rc;

	POINT btnDownFramePoint;
	POINT btnUpFramePoint;

	// 버튼 동작을 위한 함수 (함수포인터)
	void(*buttonFunc)(void);
	void(ButtonFunction::*memberFunc)(const char*, const char*);
	ButtonFunction* btnFunc;
	ARGUMENT_INFO* args, args1;

	//HRESULT(*buttonFunc)(string, string);

public:

	HRESULT Init(const char* imageName, int posX, int posY, POINT downFramePoint, POINT upFramePoint);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetButtonFunc(ButtonFunction * bf, void(ButtonFunction::* btnFunc)(const char *, const char *), ARGUMENT_INFO * args);
	Button();
	virtual ~Button();
};

