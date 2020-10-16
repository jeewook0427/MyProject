

#pragma once
#include "GameNode.h"
#include "MissileManager.h"

class Image;
class MissileManager;
class Ash;
class Missile;
class Lugia : public GameNode
{
private:

	FPOINT diepos[16][16];
	// 200518 Enemy¼öÁ¤
	Image* image;
	Image* 	gotchaball;
	//FPOINT pos;
	int HP;
	int currentFrameX, currentFrameY;
	int updateCount;

	int size;
	int width, height;
	int gotchatime;
	float angle;
	float speed;
	float degree;

	int alpha;
	int block;
	int fireTime;
	bool isHit;
	bool onHit;
	

	char szText[60];

	int fireDelay;
	int fireCount;

	LugiaMissileManager missileMgr;
	MissileManager* missileMgr2;
	Ash* ash;

	vector<Missile*> ownmissile;
	vector<Missile*>::iterator itwonmissile;

	vector<Missile*> missile;
	vector<Missile*>::iterator itmissile;

	int soundcount;


	bool horizonDir;
	bool verticalDir;
	int touchCount = 0;
	FPOINT centerPos;
	int moveAngle;
	float frameTime;
	float MoveTime;
	float scale;
	bool isDie = false;
	bool isgotcha = false;


public:
	virtual HRESULT Init();
	virtual HRESULT Init(float posX, float posY);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetAsh(Ash* _ash);

	void CheckCrash(bool* ishit, bool* onhit);
	int GetHP() { return HP; }
	void Move();
	bool GetIsDie() { return isDie; }
	//FPOINT GetPos() { return pos; }

	//FPOINT GetPos() { return pos; }

	Lugia();
	~Lugia();
};

