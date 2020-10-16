#pragma once
#include "pch.h"

#include "GameNode.h"
class Ash;
class UIManager;
class EnemyManager;
class Image;
class Stage : public GameNode
{
private:
	Ash* player;
	// 200518 Enemy¼öÁ¤
	Image* image;
	//FPOINT pos;

	int currentFrameX, currentFrameY;
	int updateCount;

	int size;
	int width, height;
	float angle;
	float speed;


	int alpha;

	bool isCurrStage;
	int currPosY;
	char szText[60];
	int fireDelay;
	int fireCount;
	int life;

	int soundcount;
	float framrTime; 
	UIManager* hpBar;
	EnemyManager* enemyMrg;

	float enemyTime;
	int* enemyWaveSet[10];
	int enemyWave;
	bool isclear = false;
	int HP;
	int bgCount = 0;
public:
	virtual HRESULT Init();
	virtual HRESULT Init(float posX, float posY);
	virtual HRESULT Init(string stageFileName, bool _isCurrStage);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	//void SetAsh(Ash* _ash);

	void SetIsCurrStage(bool _isCurrStage) { isCurrStage = _isCurrStage; }
	void SetEnemyWaveSet(int _enemySet1[], int _enemySet2[], int _enemySet3[], int _enemySet4[], int _enemySet5[],
		int _enemySet6[], int _enemySet7[], int _enemySet8[], int _enemySet9[], int _enemySet10[]);

	void SetEnemyMrg(EnemyManager* _enemyMrg) { enemyMrg = _enemyMrg; }
	UIManager* GetHpBar() { return hpBar; }
	void SetHpBar(UIManager* _hpBar) { hpBar = _hpBar; }
	int GetHP() { return HP; }
	bool GetIsClear() { return isclear; }
	int GetBgCount() { return bgCount; }
	void SetPlayer(Ash* _player) { player = _player; }
	Ash* GetPlayer() { return player; }

	Stage();
	~Stage();
};