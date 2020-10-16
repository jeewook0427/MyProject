#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;
class Bulbasaur;
class Slowpoke;
class FireBird;
class HoOh;
class Lugia;
class Item;
class Ash;
class Phantom;
class Golbat;
class EnemyManager : public GameNode
{

private:

	int HP;
	vector<Enemy*>					vecEnemys;
	vector<Enemy*>::iterator		itEnemys;
	int enemyIndex;

	vector<Bulbasaur*>				vecBulbasaurs;
	vector<Bulbasaur*>::iterator	itBulbasaurs;
	int bulbasaurIndex;
	vector<Slowpoke*>				vecSlowpokes;
	vector<Slowpoke*>::iterator		itSlowpokes;
	int slowpokeIndex;
	vector<FireBird*>				vecFireBirds;
	vector<FireBird*>::iterator		itFireBirds;
	bool isFireBirdShow;
	vector<HoOh*>					vecHoOhs;
	vector<HoOh*>::iterator			itHoOhs;
	bool isHoOhShow;
	vector<Lugia*>					vecLugias;
	vector<Lugia*>::iterator		itLugias;
	bool isLugiaShow;

	vector<Phantom*>				vecPhantom;
	vector<Phantom*>::iterator		itPhantom;
	int phantomIndex;
	

	vector<Golbat*>					vecGolbats;
	vector<Golbat*>::iterator		itGolbats;
	int GolbatIndex;


	Item* item;
	int posX, posY;
	bool isInit;
	Ash* ash;

	bool isDie = false;


public:

	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	void SetAsh(Ash* _ash);
	void AddEnemy(float posX, float posY);


	void AddBulbasaur(float posX, float posY);
	void AddSlowpoke(float posX, float posY);
	void AddPhantom(float posX, float posY);
	void AddGolbat(float posX, float posY);
	void AddFireBird(float posX, float posY);
	void AddHoOh(float posX, float posY);
	void AddLugia(float posX, float posY);

	void SetItem(Item* _item) { item = _item; }
	int GetHP() { return HP; }
	bool GetIsDie() { return isDie; }
	//vector<Enemy*> GetVecEnemys() { return vecEnemys; }

};

