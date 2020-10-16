#pragma once
#include "GameNode.h"

class Character;
class SieKensou;
class Athena;
class BattleManager : public GameNode
{
	
	bool player1onHit;
	bool player2onHit;
	bool player1skillHit;
	bool player2skillHit;
	bool player1guard;
	bool player2guard;
	bool gameOver;
	int ishit;
	int comtime;
	int player1select;
	int player2select;
	int count;
	float scale;
	
	Character* player1;
	Character* player2;

	
public:
	virtual HRESULT Init()	override; // 문법적으로 잘못되었을 때 예외처리를 위해 필요
	virtual void Release()	override;
	virtual void Update()	override;
	virtual void Render(HDC hdc)	override;
	   
	bool CheckPlayer1OnHit();
	bool CheckPlayer2OnHit();
	bool CheckPlayer1SkillHit();
	bool CheckPlayer2SkillHit();
	bool CheckPlayer1Guard();
	bool CheckPlayer2Guard();
		
	bool Getplayer1OnHit() { return player1onHit; }
	bool Getplayer2OnHit() { return player2onHit; }
	
	void SetPlayer1(Character* _character) { player1 = _character; }
	void SetPlayer2(Character* _character) { player2 = _character; }
	void SetPlayer1Select(int _1select) { player1select = _1select; }
	void SetPlayer2Select(int _2select) { player2select = _2select; }
	
	BattleManager();
	~BattleManager();
};

