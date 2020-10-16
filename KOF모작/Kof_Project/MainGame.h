#pragma once
#include "GameNode.h"

class Image;
class BackGround;
class UIManager;
class BattleManager;
class Character;

class MainGame : public GameNode
{
private:
	bool isInit;
	HANDLE hTimer;

	bool isPlayer1Select;
	bool isPlayer2Select;
	/*HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	*/
	Image* backBuffer;
	
	BackGround* background;
	UIManager* uimanager;
	BattleManager* battlemanager;
	Character* player1;
	Character* player2;

	char sZtext[60];

	int bgKeyframeX;
	int bgKeyframeY;
	int gameProcess;

	struct Key
	{
		int player1right;
		int player1left;
		int player1select;
		int player2right;
		int player2left;
		int player2select;

	};

	FPOINT player1select;
	FPOINT player2select;

	Key key;

	MCI_OPEN_PARMS mciOpenParam_selectBGM;
	MCI_PLAY_PARMS mciPlayParam_selectBGM;
	DWORD wDeviceID_selectBGM;;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	float GetAngle(float x1, float y1, float x2, float y2);
	float GetDistance(float x1, float y1, float x2, float y2);

	void KeyInput();
	void KeyInit();
	void CheckSelect();
	void TextPrint(HDC hdc);
	//bool CheckCollision(Missile* m1, Missile* m2);

	MainGame();
	~MainGame();
};

