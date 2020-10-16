#pragma once
#include "GameNode.h"
class Image;
class Animation;
class Inventory;
class Player : public GameNode
{
	//�̹���
	Image* playerRun;
	Image* playerStop;
	Image* playerMine;
	Image* mousecursor;

	//�ִϸ��̼�
	Animation* playerRunAni;
	Animation* playerStopAni;
	Animation* playerMineAni;

	//�κ��丮
	Inventory* inventory;

	
	FPOINT MousePos;

	int angle;
	int gage;
	float speed;

	bool isStop;
	bool isMove;
	bool isMine;
public:

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void PlayerMove();
	void PlayerStop();
	void PlayerMine();
	void MouseRender(HDC hdc, HDC hdc2);
	void GageRender(HDC hdc);
	//void AddInInventory(Layer _name, int num);

	bool PlayerCollision(int posX, int posY);
	Inventory* GetInventory() { return inventory; }

	Player();
	~Player();
};

