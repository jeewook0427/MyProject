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

	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

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

