#include "TitleScene.h"
#include "Image.h"
#include "Button.h"
#include "ButtonFunction.h"

HRESULT TitleScene::Init()
{
	bg = ImageManager::GetSingleton()->FindImage("titleBg");
	menu = ImageManager::GetSingleton()->FindImage("menu");

	//SoundManager::GetSingleton()->AddSound("Dark Waltz.mp3", "Sound/Dark Waltz.mp3", true, true);

	//ImageManager::GetSingleton()->AddImage("일반버튼", "Image/button.bmp", 0.0f, 0.0f, 121, 62, 1, 2, false, NULL);

	btnFunc = new ButtonFunction();

	POINT upFramePoint = { 0, 0 };
	POINT downFramePoint = { 0, 1 };

	button1 = new Button();
	button1->Init("playBt", WINSIZE_X / 2, WINSIZE_Y / 2 - 100, downFramePoint, upFramePoint);

	args1 = new ARGUMENT_INFO;
	args1->sceneName = "inGameScene";
	args1->loadingName = "loadingScene";
	button1->SetButtonFunc(btnFunc, &ButtonFunction::ChangeScene, args1);


	/*
		button2 = new Button();
		button2->Init("일반버튼", 450, 150, downFramePoint, upFramePoint);

		args1 = new ARGUMENT_INFO;
		args1->sceneName = "타일맵툴";
		args1->loadingName = "loadingscene";
		button2->SetButtonFunc(btnFunc, &ButtonFunction::ChangeScene1, args1);*/

		//	, &ButtonFunction::QuitProgram1);

	return S_OK;
}

void TitleScene::Release()
{
	SAFE_DELETE(args1);

	button1->Release();
	SAFE_DELETE(button1);

	//button2->Release();
	//SAFE_DELETE(button2);

	SAFE_DELETE(btnFunc);
}

void TitleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		SceneManager::GetSingleton()->ChangeScene("inGameScene", "loadingScene");
	}

	//SoundManager::GetSingleton()->Update();

	if (button1)	button1->Update();
	//if (button2)	button2->Update();
}

void TitleScene::Render(HDC hdc)
{
	if (bg)
		bg->Render(hdc, 0, 0);
	if (menu)
		menu->AlphaRender(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, 200);
	if (button1)
		button1->Render(hdc);
	/*hBrush = CreateSolidBrush(RGB(84, 84, 84));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	hPen = CreatePen(PS_SOLID, 0, RGB(84, 84, 84));
	hOldPen= (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, WINSIZE_X / 3 + 10, WINSIZE_Y / 4 + 100, WINSIZE_X / 3 * 2 - 5, WINSIZE_Y / 4 + 150);
	Rectangle(hdc, WINSIZE_X / 3 + 10, WINSIZE_Y / 4 + 160, WINSIZE_X / 3 * 2 - 5, WINSIZE_Y / 4 + 210);
	Rectangle(hdc, WINSIZE_X / 3 + 10, WINSIZE_Y / 4 + 220, WINSIZE_X / 3 * 2 - 5, WINSIZE_Y / 4 + 270);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);*/
	//if (button1)	button1->Render(hdc);
	//if (button2)	button2->Render(hdc);


}


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}