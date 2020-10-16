#pragma once
#include "GameNode.h"
class Item;
class Ash;
class KofPlayer;
class Tank;
class Missile;
class Enemy;
class EnemyManager;
class StageManager;
class Image;
class MainGame : public GameNode
{
private:
	HDC hdc;
	bool isInit;
	HANDLE hTimer;

	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	Ash* ash;
	Item* cnady;
	//Enemy* enemy;
	EnemyManager* enemyMgr;
	StageManager* stageMgr;
	Image* bg;
	Image* backBuffer;
	Image* intro;
	Image* gameover;
	int bgcount=1;
	float introTime = 0;
	int introFramX = 0;
	bool isStart = false;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	float GetAngle(float x1, float y1, float x2, float y2);
	float GetDistance(float x1, float y1, float x2, float y2);
	bool CheckCollision(Missile* m1, Missile* m2);

	MainGame();
	~MainGame();
};

