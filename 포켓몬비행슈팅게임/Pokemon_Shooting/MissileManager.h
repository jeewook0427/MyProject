#pragma once
#include "GameNode.h"
#include <stack>

class Missile;
class Enemy;
class Ash;
class UIManager;
class MissileManager : public GameNode
{
private:


protected:

	vector<Missile*> vecMissiles;
	vector<Missile*>::iterator itMissiles;

	stack<Missile*> stMissiles;

	GameNode*	owner;
	UIManager* uimanager;
	Ash* ash;

	int fireCount;
	int fireDelay;
	float angle;

	bool isPlayer = false;
	bool isEnemy = false;
	bool isBoss = false;
	bool onHit = false;
	bool missiledirection;
	bool ChangeMi = false;
	bool effect=false;

	int power;

public:

	void NewMissile();
	virtual Missile* CreateMissile() = 0;
	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	void Release();		// 메모리 해제
	virtual void Update() = 0;		// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc) = 0;	// 프레임 단위 출력 (이미지, 텍스트 등)

	virtual bool Fire() = 0;

	void SetIsPlayer(bool _player) { isPlayer = _player; }
	void SetIsEnemy(bool _enemy) { isEnemy = _enemy; }

	void SetOwner(GameNode* gameNode) { owner = gameNode; }
	void SetAnlge(float _angle) { angle = _angle; }
	void SetDegree(int _degree);
	void SetOnHit(bool onhit) { onHit = onhit; }
	void SetCharacter(Ash* _ash) { ash = _ash; }
	bool CheckOut(int missilenum, bool topcheck);
	void SetPower(int _power) { power = _power; }
	void SetUIManager(UIManager* _uimanager) { uimanager = _uimanager; }
	void SetChangeMi(bool _ChangeMi) { ChangeMi = _ChangeMi; }

	vector<Missile*> GetMissile() { return  vecMissiles; }

};

class BulbasaurMissileManager : public MissileManager
{
public:

	virtual Missile* CreateMissile();
	virtual void Update();
	virtual bool Fire();
	void Render(HDC hdc);


	BulbasaurMissileManager();
	virtual~BulbasaurMissileManager();
};


class PlayerMissileManager : public MissileManager
{
	
public:

	virtual Missile* CreateMissile();
	virtual void Update();
	virtual bool Fire();
	void Render(HDC hdc);



	PlayerMissileManager();
	virtual~PlayerMissileManager();
};

class DarkpetMissileManager : public MissileManager
{
public:

	virtual Missile* CreateMissile();
	virtual void Update();
	virtual bool Fire();
	void Render(HDC hdc);



	DarkpetMissileManager();
	virtual~DarkpetMissileManager();
};

class SlowpokeMissileManager : public MissileManager
{
public:

	virtual Missile* CreateMissile();
	virtual void Update();
	virtual bool Fire();
	void Render(HDC hdc);



	SlowpokeMissileManager();
	virtual~SlowpokeMissileManager();
};

class LugiaMissileManager : public MissileManager
{
	int count=0;
public:

	virtual Missile* CreateMissile();
	virtual void Update();
	virtual bool Fire();
	void Render(HDC hdc);



	LugiaMissileManager();
	virtual~LugiaMissileManager();
};


class HoohMissileManager : public MissileManager
{
public:

	virtual Missile* CreateMissile();
	virtual void Update();
	virtual bool Fire();
	void Render(HDC hdc);



	HoohMissileManager();
	virtual~HoohMissileManager();
};


class FireBirdMissileManager : public MissileManager
{
public:

	virtual Missile* CreateMissile();
	virtual void Update();
	virtual bool Fire();
	void Render(HDC hdc);



	FireBirdMissileManager();
	virtual~FireBirdMissileManager();
};

class PhantomMissileManager : public MissileManager
{
public:

	virtual Missile* CreateMissile();
	virtual void Update();
	virtual bool Fire();
	void Render(HDC hdc);



	PhantomMissileManager();
	virtual~PhantomMissileManager();
};