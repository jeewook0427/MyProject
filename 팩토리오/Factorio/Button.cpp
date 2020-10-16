#include "Button.h"
#include "Image.h"
#include "ButtonFunction.h"


HRESULT Button::Init(const char * imageName, int posX, int posY, POINT downFramePoint, POINT upFramePoint)
{
	state = BUTTON_STATE::NONE;
	pos.x = posX;
	pos.y = posY;
	btnDownFramePoint = downFramePoint;
	btnUpFramePoint = upFramePoint;

	image = ImageManager::GetSingleton()->FindImage(imageName);

	rc = GetRectToCenter(pos.x, pos.y, image->GetFrameWidth(), image->GetFrameHeight());

	this->buttonFunc = nullptr;


	return S_OK;
}

void Button::Release()
{
}

void Button::Update()
{

	if (PtInRect(&rc, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			state = BUTTON_STATE::DOWN;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON) && state == BUTTON_STATE::DOWN)
		{
			state = BUTTON_STATE::UP;

			if (buttonFunc)
				buttonFunc();
			else if (btnFunc && memberFunc)
				(btnFunc->*memberFunc)(args->sceneName, args->loadingName);	//함수를 호출하는 주체 필요
		}
	}

	else
	{
		state = BUTTON_STATE::NONE;
	}


}

void Button::Render(HDC hdc)
{
	switch (state)
	{
	case BUTTON_STATE::DOWN:
		if (image)
			image->FrameRender(hdc, pos.x, pos.y, btnDownFramePoint.x, btnDownFramePoint.y);
		break;
	case BUTTON_STATE::NONE:
	case BUTTON_STATE::UP:
		if (image)
			image->FrameRender(hdc, pos.x, pos.y, btnUpFramePoint.x, btnUpFramePoint.y);
		break;


	}
}

void Button::SetButtonFunc(ButtonFunction * bf, void(ButtonFunction::* btnFunc)(const char *, const char *), ARGUMENT_INFO * args)
{
	this->memberFunc = btnFunc;	// 함수 호출 객체
	this->btnFunc = bf;			// 호출되는 멤버함수
	this->args = args;			// 매개변수
}

Button::Button()
{
}

Button::~Button()
{
}
