#pragma once
#include "pch.h"
#include "GameNode.h"

class Enemy;
class Image;
class Missile : public GameNode
{
protected:
	FPOINT pos[30];

	int size;
	float angle;
	float speed;
	bool isFire;
	float adjustAngle;
	int missileCount;
	int currMissile;
	int degree;
	int power;
	int currTime;
	int count;

	int currframex, currframey;

	Enemy* target;
	Image* img;
	Image* effimg;
	int timer;
	int blockscore;

	bool isPlayer = false;
	bool isEnemy = false;
	bool effect;
	bool isBoss;
	bool onHit;
	bool ChangeMi = false;

public:
	virtual HRESULT Init() = 0;
	HRESULT Init(int posX);
	virtual void Release();
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	void SetTarget(Enemy* enemy) { target = enemy; }
	void SetPos(FPOINT pt);
	void SetPos2(FPOINT pt) { pos[0] = pt; }

	void SetIsPlayer(bool _player) { isPlayer = _player; }
	void SetIsEnemy(bool _enemy) { isEnemy = _enemy; }

	FPOINT* GetPos() { return pos; }

	void SetIsFire(bool b) { isFire = b; }
	bool GetIsFire() { return isFire; }
	void SetAngle(float angle) { this->angle = angle; }
	float GetSize() { return size; }
	void SetSpeed(float _speed) { speed = _speed; }
	void SetOnHit(bool onhit) { onHit = onhit; }
	void SetDgree(int _degree) { degree = _degree; }
	bool GetOnHit() { return onHit; }
	int GetDgree() { return degree; }
	void SetPower(int _power) { power = _power; }
	void SetCurrMissile(int _currmissile) {currMissile = _currmissile; }
	int GetBlockScore() { return blockscore; }
	void Setcount(int _count) { count = _count; }
	bool GetEffect() { return effect; }

	void SetChangeMi(bool _ChangeMi) { ChangeMi = _ChangeMi; }
	Missile();
	virtual ~Missile();
};

class PlayerMissile : public Missile
{
public:
	
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	PlayerMissile();
	virtual ~PlayerMissile();
};

class BulbasaurMissile : public Missile
{
public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	BulbasaurMissile();
	virtual ~BulbasaurMissile();
};

class SlowpokeMissile : public Missile // 순수 가상함수만 있는 상태론 안된다. 오버라이딩해야함 
{
public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	SlowpokeMissile();
	virtual ~SlowpokeMissile();
};

class DarkpetMissile : public Missile // 순수 가상함수만 있는 상태론 안된다. 오버라이딩해야함 
{
public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	DarkpetMissile();
	virtual ~DarkpetMissile();
};


class LugiaMissile : public Missile // 순수 가상함수만 있는 상태론 안된다. 오버라이딩해야함 
{
public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	LugiaMissile();
	virtual ~LugiaMissile();
};

class HoOhMissile : public Missile // 순수 가상함수만 있는 상태론 안된다. 오버라이딩해야함 
{
public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	HoOhMissile();
	virtual ~HoOhMissile();
};

class FireBirdMissile : public Missile // 순수 가상함수만 있는 상태론 안된다. 오버라이딩해야함 
{
public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	FireBirdMissile();
	virtual ~FireBirdMissile();
};

class PhantomMissile : public Missile // 순수 가상함수만 있는 상태론 안된다. 오버라이딩해야함 
{
public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	PhantomMissile();
	virtual ~PhantomMissile();
};

