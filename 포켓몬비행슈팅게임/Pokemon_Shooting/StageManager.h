#pragma once
#include "pch.h"
#include <fstream>
#include <iostream>
#include "GameNode.h"
class Image;
class Stage;
class EnemyManager;
class UIManager;
class Ash;
class StageManager : public GameNode
{
private:

	vector<Stage*> vecStage;
	//vector<Missile*>::iterator itMissiles;
	Ash* player;
	GameNode*	owner;
	bool isEnding;
	
	int currStageNum;
	int fireCount;
	int fireDelay;
	float angle;
	EnemyManager* enemyMrg;
	UIManager* hpBar;
	float enemyTime;
	int maxStageNum;
	
	string* stageFileName;

	int** enemyWaveSet1;
	int** enemyWaveSet2;
	int** enemyWaveSet3;
	int** enemyWaveSet4;
	int** enemyWaveSet5;
	int** enemyWaveSet6;
	int** enemyWaveSet7;
	int** enemyWaveSet8;
	int** enemyWaveSet9;
	int** enemyWaveSet10;

	Image* gotcha;
	Image* lifeIcon;
	Image* gotchaball;
	Image* ending;
	int endingY;
	float gotchaTime;
	int gatchaAlpha;
	int gotchaballY = 0;
	int bgCount = 0;
	float scoreTime;
	int clearScore;
	bool caculScore; 


public:

	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	//bool Fire();

	void SetOwner(GameNode* gameNode) { owner = gameNode; }
	void SetAnlge(float _angle) { angle = _angle; }

	vector<Stage*> GetStage() { return  vecStage; }
	int GetBgCount() { return bgCount; }

	void SetHpBar(UIManager* _hpBar) { hpBar = _hpBar; }
	void SetEnemyMrg(EnemyManager* _enemyMrg) { enemyMrg = _enemyMrg; }

	void ReadFileInt(string fileName);
	UIManager* GetUIManager() { return hpBar; }


	void SetPlayer(Ash* _player) { player = _player; }
	Ash* GetPlayer() { return player; }

};

