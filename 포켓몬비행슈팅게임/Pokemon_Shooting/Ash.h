#pragma once
#include "GameNode.h"
#include "MissileManager.h"
class MissileManager;
class Item;
class UIManager;
class StageManager;
class Ash : public GameNode
{
private:

	Image* image;
	Image* effect;
	Image* pikachu;
	Image* pikachueffect;
	Image* lifeHead;
	Image* pikachucount;
	StageManager* stagemanager;
	UIManager* uimanager;
	float angle;
	float moveSpeed;
	float degree;
	int alpha;
	int size;
	int power;
	int life=3;

	float scale;

	int currframeY;
	int currframeX;
	int effframeY;
	int effframeX;
	int skillframeX;
	int skillframeY;
	int skillcount;

	int comtime;
	int comtime2;
	int time;
	bool isEat;
	bool isReverse;
	bool onHit;
	bool isHit;
	bool isStart;
	bool checkalpha;
	bool keyLock;
	bool debugMode;
	bool gameover;
	bool skill;
	bool isPush;
	PlayerMissileManager missileMgr;
	float frameTime;
	bool isEnding;
	int endY;

public:

	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	int GetSize() { return size; }
	void SetPower(int _power) { power = _power; }
	int GetPower() { return power; }
	void SetisHit(bool _ishit) { isHit = _ishit; }
	bool GetIsStart() { return isStart; }
	bool GetDebugMode() { return debugMode; }
	bool GetGameOver() { return gameover; }
	bool GetSkill() { return skill; }
	int GetSkillcount(){ return skillcount; }
	void SetSkillcount(int _count) { skillcount = _count; }
	MissileManager* GetMissileMgr();

	void SetUIManager(UIManager* _uimanager) { uimanager = _uimanager; }
	UIManager* GetUIManager() { return uimanager; }
	bool GetIsPush() { return isPush; }
	int GetLife() { return life; }

	void SetisEnding(bool _isEnding) { isEnding = _isEnding; }


	Ash();
	~Ash();

};

