#include "LoadingScene.h"
#include "Image.h"

HRESULT LoadingScene::Init()
{

	logo = ImageManager::GetSingleton()->FindImage("loadingLogo");
	return S_OK;
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{

}

void LoadingScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	if (logo)
		logo->Render(hdc, WINSIZE_X / 4 + 400, WINSIZE_Y / 2 - 54);

	//PatBlt(hdc, WINSIZE_X / 4, WINSIZE_Y / 2 + 50, SceneManager::loadingPercent * 10, 10, WHITENESS);
	hBrush = CreateSolidBrush(RGB(235, 95, 0));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, WINSIZE_X / 4, WINSIZE_Y / 2 + 30, WINSIZE_X / 4 + SceneManager::loadingPercent * 10, WINSIZE_Y / 2 + 40);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);


	strcpy_s(font.lfFaceName, "Consolas");
	font.lfHeight = 15;
	font.lfWeight = 600;
	hFont = CreateFontIndirect((LOGFONTA*)&font);
	hOldFont = (HFONT)SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(235, 95, 0));
	wsprintf(SceneManager::strText, "loading... (%d %%)", SceneManager::loadingPercent);
	TextOut(hdc, WINSIZE_X / 4, WINSIZE_Y / 2 + 50, SceneManager::strText, strlen(SceneManager::strText));
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);


}

LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}
