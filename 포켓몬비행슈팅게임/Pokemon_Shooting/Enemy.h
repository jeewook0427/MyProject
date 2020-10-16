#pragma once
#include "GameNode.h"
#include "MissileManager.h"

class Image;
class MissileManager;
class Ash;
class Missile;
class Item;
class UIManager;
class Enemy : public GameNode
{
private:
	bool isDie;
	// 200518 Enemy수정
	Image* image;
	//FPOINT pos;
	Item* item;

	int currentFrameX, currentFrameY;
	int updateCount;

	int size;
	int width, height;
	float angle;
	float speed;
	float degree;

	int alpha;
	
	char szText[60];

	int fireDelay;
	int fireCount;

	bool isHit;
	bool onHit;
	bool isEat;
	int fireTime = 0;
	DarkpetMissileManager missileMgr;
	MissileManager* missileMgr2;
	Ash* ash;

	vector<Missile*> ownmissile;
	vector<Missile*>::iterator itwonmissile;

	vector<Missile*> missile;
	vector<Missile*>::iterator itmissile;

	int soundcount;
	int HP;
	bool horizonDir;
	bool verticalDir;
	int touchCount = 0;
	FPOINT centerPos;
	int moveAngle;
	float frameTime; 
	float MoveTime;


public:
	virtual HRESULT Init();
	virtual HRESULT Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	void DieUpdate();
	virtual void Render(HDC hdc);


	void Move1();// 좌우 이동
	void Move2();// 위아래 이동 이동
	void Move3();// 대각선 이동
	void Move4();// Z 자 이동 이동
	void Move5();// 동그라미 이동


	void SetAsh(Ash* _ash);
	void CheckCrash(bool* ishit, bool* onhit);

	void SetItem(Item* _item) { item = _item; }
	void SetIsDie(bool _isDie) { isDie = _isDie; }
	//FPOINT GetPos() { return pos; }

	//FPOINT GetPos() { return pos; }

	Enemy();
	~Enemy();
};

