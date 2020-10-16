#pragma once
#include "GameNode.h"
#include "pch.h"

class Character;
class UIManager : public GameNode
{
	struct Player
	{
		float gageposX;
		float gageposY;
		int damage;
		int insdamage;
	};

	Player player1ui;
	Player player2ui;

	int gageWidth;
	int gageHeight;
	int timer;
	int comtime;

	bool gameOver;

	bool fightSound;
	bool koSound;

	int soundTime;
	int soundFrame;
	
	MCI_OPEN_PARMS mciOpenParam_pkSound;
	MCI_PLAY_PARMS mciPlayParam_pkSound;
	DWORD wDeviceID_pkSound;

	Character* player1;
	Character* player2;

	HFONT hFont, hOldFont;
	HBRUSH hBrush, hOldBrush;

	char sZtext[80];

public:
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	virtual void PrintText(HDC hdc);

	Player GetPlayer1(){ return player1ui; }
	Player GetPlayer2(){ return player2ui; }

	bool CheckGameOver();
	void SetPlayer1(Character* _character) { player1 = _character; }
	void SetPlayer2(Character* _character) { player2 = _character; }
	
	UIManager();
	~UIManager();
};

