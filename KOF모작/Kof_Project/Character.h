#pragma once
#include "GameNode.h"
#include "Athena.h"
#include "SieKensou.h"
#include "Kyo.h"

class SieKensou;
class Athena;
class Kyo;
class Character : public GameNode
{
	SieKensou* siekensou;
	Athena* athena;
	Kyo* kyo;
	
	struct CharacterInfo
	{
		bool cantguard;

		bool isReverse;
		bool isHit;
		bool rightPunch;
		bool leftKick;
		bool isDead;
		bool gameStart;
		bool launchSkillA;
		bool skillOnHit;
		bool launchSkillB;
		
		int Damage;
		int insDamage;
		
		FPOINT attackPos;
		FPOINT bodyPos;
		FPOINT pos;
		FPOINT skillAPos;
		FPOINT guardPos;
		
		int bodyWidth;
		int bodyHeight;
		int rightPunchWidth;
		int rightPunchHeight;
		int leftKickWidth;
		int leftKickHeight;
		int skillAWidth;
		int skillAHeight;
		int guardWidth;
		int guardHeight;
		int actionframex;
		

	};

	
	CharacterInfo charinfo;
	

	int playerNum;
	int selectNum;

public:
	virtual HRESULT Init()	override; // 문법적으로 잘못되었을 때 예외처리를 위해 필요
	virtual void Release()	override;
	virtual void Update()	override;
	virtual void Render(HDC hdc)	override;

	CharacterInfo GetCharInfo() { return charinfo; }
	SieKensou* GetSieKensou(){ return siekensou; }
	Athena* GetAthena() { return athena; }

	void SetSelectNum(int _selectnum) { selectNum = _selectnum; }
	void SetPlayerDamage(int _damage);
	void SetPlayerInsDamage(int _damage);
	void SetPlayerIsHit(bool _ishit);
	void SetPlayerNum(int playernum);
	void SetCharacterNum(int charnum) { playerNum = charnum;  }
	void SetIsWin(bool iswin);
	void SetSkillOnHit(bool skillonhit);
	void SetIsGuard(bool isguard);
	void SetIsGuarded(bool isguarded);
	void SetIsSkillisHit(bool skillishit);
	void SetIsReverse(bool isreverse);
	void SetCurrentFramex(int framex);
	void SetGameOver(bool gameover);
	
	

	
	Character();
	~Character();
};

