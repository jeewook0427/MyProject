
#pragma once
#include "GameNode.h"
#include "MissileManager.h"

class Image;
class MissileManager;
class Ash;
class Missile;
class HoOh : public GameNode
{
private:

	int HP;
	// 200518 Enemy¼öÁ¤
	Image* image;
	Image* 	gotchaball;

	//FPOINT pos;

	int currentFrameX, currentFrameY;
	int updateCount;

	int bosswidth;
	int bossheight;
	bool die;
	bool smaller;
	int size;
	int width, height;
	int block;
	float angle;
	float speed;
	float degree;

	int alpha;

	int fireTime;
	bool isHit;
	bool onHit;

	char szText[60];

	int fireDelay;
	int fireCount;

	HoohMissileManager missileMgr;
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
	bool hasSmall;
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
	void Move2();
	bool GetIsDie() { return isDie; }
	//FPOINT GetPos() { return pos; }

	//FPOINT GetPos() { return pos; }

	HoOh();
	~HoOh();
};

