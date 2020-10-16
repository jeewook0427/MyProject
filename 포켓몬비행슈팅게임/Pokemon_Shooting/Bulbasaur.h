
#pragma once
#include "GameNode.h"
#include "MissileManager.h"

class Image;
class MissileManager;
class Ash;
class Missile;
class Bulbasaur : public GameNode
{
private:

	// 200518 Enemy¼öÁ¤
	Image* image;
	//FPOINT pos;

	int currentFrameX, currentFrameY;
	int updateCount;

	int size;
	int width, height;
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
	int HP;

	BulbasaurMissileManager missileMgr;
	MissileManager* missileMgr2;
	Ash* ash;

	vector<Missile*> ownmissile;
	vector<Missile*>::iterator itwonmissile;

	vector<Missile*> missile;
	vector<Missile*>::iterator itmissile;

	int soundcount;

	bool isDie;
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

	void SetAsh(Ash* _ash);

	void CheckCrash(bool* ishit, bool* onhit);
	void SetIsDie(bool _isDie) { isDie = _isDie; }

	void Move();


	Bulbasaur();
	~Bulbasaur();
};

