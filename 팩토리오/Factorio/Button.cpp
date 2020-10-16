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
				(btnFunc->*memberFunc)(args->sceneName, args->loadingName);	//�Լ��� ȣ���ϴ� ��ü �ʿ�
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
	this->memberFunc = btnFunc;	// �Լ� ȣ�� ��ü
	this->btnFunc = bf;			// ȣ��Ǵ� ����Լ�
	this->args = args;			// �Ű�����
}

Button::Button()
{
}

Button::~Button()
{
}
