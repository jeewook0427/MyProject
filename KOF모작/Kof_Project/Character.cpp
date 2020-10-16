#include "Character.h"
#include "SieKensou.h"
#include "Athena.h"
#include "Kyo.h"

HRESULT Character::Init()
{
	siekensou = new SieKensou();
	if (playerNum == 1)
		siekensou->SetIsReverse(true);
	else
		siekensou->SetIsReverse(false);
	siekensou->Init();

	athena = new Athena();
	if (playerNum == 1)
		athena->SetIsReverse(true);
	else
		athena->SetIsReverse(false);
	athena->Init();

	kyo = new Kyo();
	if (playerNum == 1)
		kyo->SetIsReverse(true);
	else
		kyo->SetIsReverse(false);
	kyo->Init();

	return S_OK;
}

void Character::Release()
{
	kyo->Release();
	delete kyo;

	athena->Release();
	delete athena;

	siekensou->Release();
	delete siekensou;

	
}

void Character::Update()
{
	if (selectNum == 1)
	{
		siekensou->Update();
		charinfo.bodyPos.x = siekensou->GetHitBox().bodyPos.x;
		charinfo.bodyPos.y = siekensou->GetHitBox().bodyPos.y;
		charinfo.attackPos.x = siekensou->GetHitBox().attackPos.x;
		charinfo.attackPos.y = siekensou->GetHitBox().attackPos.y;
		charinfo.bodyWidth = siekensou->GetHitBox().bodyWidth;
		charinfo.bodyHeight = siekensou->GetHitBox().bodyHeight;
		charinfo.leftKickWidth = siekensou->GetHitBox().leftkickWidth;
		charinfo.leftKickHeight = siekensou->GetHitBox().leftkickHeight;
		charinfo.rightPunchWidth = siekensou->GetHitBox().rightpunchWidth;
		charinfo.rightPunchHeight = siekensou->GetHitBox().rightpunchHeight;
		charinfo.pos.x = siekensou->GetPosX();
		charinfo.pos.y = siekensou->GetPosY();
		charinfo.Damage = siekensou->GetDamage();
		charinfo.insDamage = siekensou->GetInsDamage();
		charinfo.isHit = siekensou->GetIsHit();
		charinfo.rightPunch = siekensou->GetRightPunch();
		charinfo.leftKick = siekensou->GetLeftKick();
		charinfo.isDead = siekensou->GetIsDead();
		charinfo.gameStart = siekensou->GetGameStart();
		charinfo.launchSkillA = siekensou->GetLaunchSkillA();
		charinfo.skillAPos.x = siekensou->GetHitBox().skillAPos.x;
		charinfo.skillAPos.y = siekensou->GetHitBox().skillAPos.y;
		charinfo.skillAWidth = siekensou->GetHitBox().skillAWidth;
		charinfo.skillAHeight = siekensou->GetHitBox().skillAHeight;
		charinfo.skillOnHit = siekensou->GetSkillOnHit();
		//여기서부터 추가
		charinfo.guardPos.x = siekensou->GetHitBox().guardPos.x;
		charinfo.guardPos.y = siekensou->GetHitBox().guardPos.y;
		charinfo.guardWidth = siekensou->GetHitBox().guardWidth;
		charinfo.guardHeight = siekensou->GetHitBox().guardHeight;
		charinfo.actionframex = siekensou->GetActionFrameX();
		charinfo.launchSkillB = siekensou->GetLaunchSkillB();
		charinfo.cantguard = false;
	}
	
	

	if (selectNum == 2)
	{
		athena->Update();
		charinfo.bodyPos.x = athena->GetHitBox().bodyPos.x;
		charinfo.bodyPos.y = athena->GetHitBox().bodyPos.y;
		charinfo.attackPos.x = athena->GetHitBox().attackPos.x;
		charinfo.attackPos.y = athena->GetHitBox().attackPos.y;
		charinfo.bodyWidth = athena->GetHitBox().bodyWidth;
		charinfo.bodyHeight = athena->GetHitBox().bodyHeight;
		charinfo.leftKickWidth = athena->GetHitBox().leftkickWidth;
		charinfo.leftKickHeight = athena->GetHitBox().leftkickHeight;
		charinfo.rightPunchWidth = athena->GetHitBox().rightpunchWidth;
		charinfo.rightPunchHeight = athena->GetHitBox().rightpunchHeight;
		charinfo.pos.x = athena->GetPosX();
		charinfo.pos.y = athena->GetPosY();
		charinfo.Damage = athena->GetDamage();
		charinfo.insDamage = athena->GetInsDamage();
		charinfo.isHit = athena->GetIsHit();
		charinfo.rightPunch = athena->GetRightPunch();
		charinfo.leftKick = athena->GetLeftKick();
		charinfo.isDead = athena->GetIsDead();
		charinfo.gameStart = athena->GetGameStart();
		charinfo.launchSkillA = athena->GetLaunchSkillA();
		charinfo.skillAPos.x = athena->GetHitBox().skillAPos.x;
		charinfo.skillAPos.y = athena->GetHitBox().skillAPos.y;
		charinfo.skillAWidth = athena->GetHitBox().skillAWidth;
		charinfo.skillAHeight = athena->GetHitBox().skillAHeight;
		charinfo.skillOnHit = athena->GetSkillOnHit();
		charinfo.guardPos.x = athena->GetHitBox().guardPos.x;
		charinfo.guardPos.y = athena->GetHitBox().guardPos.y;
		charinfo.guardWidth = athena->GetHitBox().guardWidth;
		charinfo.guardHeight = athena->GetHitBox().guardHeight;
		charinfo.actionframex = athena->GetActionFrameX();
		charinfo.launchSkillB = athena->GetLaunchSkillB(); 
		charinfo.cantguard = true;
	}

	if (selectNum == 3)
	{
		kyo->Update();
		charinfo.bodyPos.x = kyo->GetHitBox().bodyPos.x;
		charinfo.bodyPos.y = kyo->GetHitBox().bodyPos.y;
		charinfo.attackPos.x = kyo->GetHitBox().attackPos.x;
		charinfo.attackPos.y = kyo->GetHitBox().attackPos.y;
		charinfo.bodyWidth = kyo->GetHitBox().bodyWidth;
		charinfo.bodyHeight = kyo->GetHitBox().bodyHeight;
		charinfo.leftKickWidth = kyo->GetHitBox().leftkickWidth;
		charinfo.leftKickHeight = kyo->GetHitBox().leftkickHeight;
		charinfo.rightPunchWidth = kyo->GetHitBox().rightpunchWidth;
		charinfo.rightPunchHeight = kyo->GetHitBox().rightpunchHeight;
		charinfo.pos.x = kyo->GetPosX();
		charinfo.pos.y = kyo->GetPosY();
		charinfo.Damage = kyo->GetDamage();
		charinfo.insDamage = kyo->GetInsDamage();
		charinfo.isHit = kyo->GetIsHit();
		charinfo.rightPunch = kyo->GetRightPunch();
		charinfo.leftKick = kyo->GetLeftKick();
		charinfo.isDead = kyo->GetIsDead();
		charinfo.gameStart = kyo->GetGameStart();
		charinfo.launchSkillA = kyo->GetLaunchSkillA();
		charinfo.skillAPos.x = kyo->GetHitBox().skillAPos.x;
		charinfo.skillAPos.y = kyo->GetHitBox().skillAPos.y;
		charinfo.skillAWidth = kyo->GetHitBox().skillAWidth;
		charinfo.skillAHeight = kyo->GetHitBox().skillAHeight;
		charinfo.skillOnHit = kyo->GetSkillOnHit();
		charinfo.guardPos.x = kyo->GetHitBox().guardPos.x;
		charinfo.guardPos.y = kyo->GetHitBox().guardPos.y;
		charinfo.guardWidth = kyo->GetHitBox().guardWidth;
		charinfo.guardHeight = kyo->GetHitBox().guardHeight;
		charinfo.actionframex = kyo->GetActionFrameX();
		charinfo.launchSkillB = kyo->GetLaunchSkillB();
		charinfo.cantguard = false;
	}
	
}

void Character::Render(HDC hdc)
{
	if (selectNum == 1)
	{
		siekensou->Render(hdc);
	}

	if (selectNum == 2)
	{
		athena->Render(hdc);
	}

	if (selectNum == 3)
	{
		kyo->Render(hdc);
	}
}


void Character::SetPlayerDamage(int _damage)
{
	if (selectNum==1)
	{
		siekensou->SetDamage(_damage);
	}

	if (selectNum==2)
	{
		athena->SetDamage(_damage);
	}

	if (selectNum == 3)
	{
		kyo->SetDamage(_damage);
	}
}

void Character::SetPlayerInsDamage(int _insdamage)
{
	if (selectNum == 1)
	{
		siekensou->SetInsDamage(_insdamage);
	}

	if (selectNum == 2)
	{
		athena->SetInsDamage(_insdamage);
	}

	if (selectNum == 3)
	{
		kyo->SetInsDamage(_insdamage);
	}


}

void Character::SetPlayerIsHit(bool _ishit)
{
	if (selectNum == 1)
	{
		siekensou->SetIsHit(_ishit);
	}

	if (selectNum == 2)
	{
		athena->SetIsHit(_ishit);
	}

	if (selectNum == 3)
	{
		kyo->SetIsHit(_ishit);
	}
}

void Character::SetPlayerNum(int playernum)
{
	if (selectNum == 1)
	{
		siekensou->SetPlayerNum(playernum);
	}

	if (selectNum == 2)
	{
		athena->SetPlayerNum(playernum);
	}

	if (selectNum == 3)
	{
		kyo->SetPlayerNum(playernum);
	}
}

void Character::SetIsWin(bool iswin)
{
	if (selectNum == 1)
	{
		siekensou->SetIsWin(iswin);
	}

	if (selectNum == 2)
	{
		athena->SetIsWin(iswin);
	}

	if (selectNum == 3)
	{
		kyo->SetIsWin(iswin);
	}
}

void Character::SetSkillOnHit(bool skillonhit)
{
	if (selectNum == 1)
	{
		siekensou->SetSkillOnHit(skillonhit);
	}

	if (selectNum == 2)
	{
		athena->SetSkillOnHit(skillonhit);
	}

	if (selectNum == 3)
	{
		kyo->SetSkillOnHit(skillonhit);
	}
}

void Character::SetIsGuard(bool isguard)
{
	if (selectNum == 1)
	{
		siekensou->SetIsGard(isguard);
	}

	if (selectNum == 2)
	{
		athena->SetIsGard(isguard);
	}

	if (selectNum == 3)
	{
		kyo->SetIsGard(isguard);
	}
}

void Character::SetIsGuarded(bool isguarded)
{
	if (selectNum == 1)
	{
		siekensou->SetIsGarded(isguarded);
	}

	if (selectNum == 2)
	{
		athena->SetIsGarded(isguarded);
	}

	if (selectNum == 3)
	{
		kyo->SetIsGarded(isguarded);
	}
}

void Character::SetIsSkillisHit(bool skillishit)
{
	if (selectNum == 1)
	{
		siekensou->SetIsSkillisHit(skillishit);
	}

	if (selectNum == 2)
	{
		athena->SetIsSkillisHit(skillishit);
	}

	if (selectNum == 3)
	{
		kyo->SetIsSkillisHit(skillishit);
	}
}

void Character::SetIsReverse(bool isreverse)
{
	if (selectNum == 1)
	{
		siekensou->SetIsReverse(isreverse);
	}

	if (selectNum == 2)
	{
		athena->SetIsReverse(isreverse);
	}

	if (selectNum == 3)
	{
		kyo->SetIsReverse(isreverse);
	}
}

void Character::SetCurrentFramex(int framex)
{
	if (selectNum == 1)
	{
		siekensou->SetCurrentFrameX(framex);
	}

	if (selectNum == 2)
	{
		athena->SetCurrentFrameX(framex);
	}

	if (selectNum == 3)
	{
		kyo->SetCurrentFrameX(framex);
	}
}

void Character::SetGameOver(bool gameover)
{
	if (selectNum == 1)
	{
		siekensou->SetGameOver(gameover);
	}

	if (selectNum == 2)
	{
		athena->SetGameOver(gameover);
	}

	if (selectNum == 3)
	{
		kyo->SetGameOver(gameover);
	}
}




Character::Character()
{
}

Character::~Character()
{
}
