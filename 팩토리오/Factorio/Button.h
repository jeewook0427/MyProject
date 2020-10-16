#pragma once
#include "GameNode.h"
#include "pch.h"
/*

�Լ������� (�Լ��� �ּҸ� ��� ����)
������ (������ �ּҸ� ��� ����)
int a = 10;
int* pA = &a;

int sum(int a, int b);
����Ÿ�� (*�Լ��������̸�) (�Ű�����1�� Ÿ��, �Ű�����2�� Ÿ��);
int (*calculatePointer)(int, int);

void func(void);			// �Լ��� ������ ����
void (*funcPointer)(void);	// �Լ�������(����)�� ����
funcPointer = func;			// �Լ������Ϳ� �Լ��� �ּҸ� ����

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

	// ��ư ������ ���� �Լ� (�Լ�������)
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

