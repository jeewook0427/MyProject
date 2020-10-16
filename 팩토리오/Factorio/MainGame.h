#pragma once
#include "GameNode.h"

class MapManager;

class TitleScene;
class LoadingScene;
class MainGame : public GameNode
{
private:
	
	HDC hdc;
	bool isInit;
	HANDLE hTimer;

	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;


	Image* backBuffer;


	GameNode* tilemapScene;
	GameNode* titleScene;
	GameNode* inGameScene;
	GameNode* loadingScene;
	/*TitleScene* titlescene;
	BattleScene* battlescene;
	LoadingScene* loadingscene;*/


public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

