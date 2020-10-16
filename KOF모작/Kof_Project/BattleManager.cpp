#include "BattleManager.h"
#include "Character.h"


HRESULT BattleManager::Init()
{
	player1onHit=false;
	player2onHit=false;
	player1skillHit =false;
	player2skillHit =false;
	player1guard=false;
	player2guard=false;
	comtime = 0;
	count = 0;
	scale = 2;
	return S_OK;
}

void BattleManager::Release()
{
	
}

void BattleManager::Update()
{
	
		
	player1skillHit = this->CheckPlayer1SkillHit();
	player2skillHit = this->CheckPlayer2SkillHit();
	player1guard = this->CheckPlayer1Guard();
	player2guard = this->CheckPlayer2Guard();
	player1onHit = this->CheckPlayer1OnHit();
	player2onHit = this->CheckPlayer2OnHit();
	
	if (player1guard)
	{
		player1->SetIsGuard(true);
		player2->SetIsGuarded(true);
	}

	if (player2guard)
	{
		player2->SetIsGuard(true);
		player1->SetIsGuarded(true);
	}
	
	if (player1skillHit && !player2guard)
	{
		if (count == 0)
		{
			player2->SetPlayerDamage(player2->GetCharInfo().Damage + 50);
			player2->SetPlayerInsDamage(player2->GetCharInfo().insDamage +50 );
			count++;
			if (player1->GetCharInfo().launchSkillB && player1->GetCharInfo().cantguard)
			{
				player2->SetPlayerDamage(player2->GetCharInfo().Damage + 160);
				player2->SetPlayerInsDamage(player2->GetCharInfo().insDamage + 160);
			}
		}

		
		player2->SetPlayerIsHit(true);
		player2->SetIsSkillisHit(true);
		player1->SetSkillOnHit(true);
	}

	if (player2skillHit && !player1guard)
	{
		if (count == 0)
		{
			player1->SetPlayerDamage(player1->GetCharInfo().Damage + 50);
			player1->SetPlayerInsDamage(player1->GetCharInfo().insDamage + 50);
			count++;
			if (player2->GetCharInfo().launchSkillB && player2->GetCharInfo().cantguard)
			{
				player1->SetPlayerDamage(player1->GetCharInfo().Damage + 160);
				player1->SetPlayerInsDamage(player1->GetCharInfo().insDamage + 160);
			}
		}
		
		player1->SetPlayerIsHit(true);
		player1->SetIsSkillisHit(true);
		player2->SetSkillOnHit(true);
		
		
	}
	if (player1onHit && !player2guard)
	{
		if (count == 0)
		{
			player2->SetPlayerDamage(player2->GetCharInfo().Damage + 15);
			player2->SetPlayerInsDamage(player2->GetCharInfo().insDamage + 15);
			count++;
		}
		
		
		player2->SetPlayerIsHit(true);
	}

	
	if (player2onHit && !player1guard)
	{
		if (count == 0)
		{
			player1->SetPlayerDamage(player1->GetCharInfo().Damage + 15);
			player1->SetPlayerInsDamage(player1->GetCharInfo().insDamage + 15);
			count++;
		}
		
		//count++;
		
		player1->SetPlayerIsHit(true);

	}
	
	if (!player1onHit && !player2onHit && !player1skillHit && !player2skillHit)
	{
		count = 0;
	}

	if (player1->GetCharInfo().Damage >= 400)
	{
		player2->SetIsWin(true);
	}

	if (player2->GetCharInfo().Damage >= 400)
	{
		player1->SetIsWin(true);
	}
	
	if (abs((player1->GetCharInfo().pos.x + 65 * scale )- (player2->GetCharInfo().pos.x + 65 * scale)) < 20)
	{
		player1->SetCurrentFramex(0);
		player2->SetCurrentFramex(0);
	}

	if (player1->GetCharInfo().pos.x + 65 * scale < player2->GetCharInfo().pos.x + 65 * scale)
	{
		player1->SetIsReverse(true);
		player2->SetIsReverse(false);
		
	}

	else if ((player1->GetCharInfo().pos.x + 65 * scale > player2->GetCharInfo().pos.x + 65 * scale))
	{
		player1->SetIsReverse(false);
		player2->SetIsReverse(true);
		
	}

	

	
}

void BattleManager::Render(HDC hdc)
{
}

bool BattleManager::CheckPlayer1OnHit()
{
	bool p1onhit=false;
	bool body =false;
	bool leg=false;

	if (player1->GetCharInfo().rightPunch)
	{

		if (player1->GetCharInfo().attackPos.x > player2->GetCharInfo().bodyPos.x + player2->GetCharInfo().bodyWidth ||
			player1->GetCharInfo().attackPos.x + player1->GetCharInfo().rightPunchWidth< player2->GetCharInfo().bodyPos.x ||
			player1->GetCharInfo().attackPos.y > player2->GetCharInfo().bodyPos.y + player2->GetCharInfo().bodyHeight ||
			player1->GetCharInfo().attackPos.y + player1->GetCharInfo().rightPunchHeight < player2->GetCharInfo().bodyPos.y)

			body = false;

		else
			body = true;

	}

	else if (player1->GetCharInfo().leftKick)
	{


		if (player1->GetCharInfo().attackPos.x > player2->GetCharInfo().bodyPos.x + player2->GetCharInfo().bodyWidth ||
			player1->GetCharInfo().attackPos.x + player1->GetCharInfo().leftKickWidth< player2->GetCharInfo().bodyPos.x ||
			player1->GetCharInfo().attackPos.y > player2->GetCharInfo().bodyPos.y + player2->GetCharInfo().bodyHeight ||
			player1->GetCharInfo().attackPos.y + player1->GetCharInfo().leftKickHeight < player2->GetCharInfo().bodyPos.y)


			leg = false;



		else
			leg = true;
	}

	if (body || leg)

		p1onhit = true;


	else
		p1onhit = false;

	return p1onhit;
}
bool BattleManager::CheckPlayer1SkillHit()
{
	bool p1onhit = false;
	bool body = false;
	bool leg = false;

	if ((player1->GetCharInfo().launchSkillA || player1->GetCharInfo().launchSkillB) && !player1->GetCharInfo().skillOnHit )
	{

		if (player1->GetCharInfo().skillAPos.x > player2->GetCharInfo().bodyPos.x + player2->GetCharInfo().bodyWidth ||
			player1->GetCharInfo().skillAPos.x + player1->GetCharInfo().skillAWidth< player2->GetCharInfo().bodyPos.x ||
			player1->GetCharInfo().skillAPos.y > player2->GetCharInfo().bodyPos.y + player2->GetCharInfo().bodyHeight ||
			player1->GetCharInfo().skillAPos.y + player1->GetCharInfo().skillAHeight < player2->GetCharInfo().bodyPos.y)

			body = false;

		else
			body = true;

	}
	
	if (body || leg)

		p1onhit = true;


	else
		p1onhit = false;

	
	return p1onhit;
}
bool BattleManager::CheckPlayer2OnHit()
{
	bool p2onhit = false;
	bool body = false;
	bool leg = false;
	if (player2->GetCharInfo().rightPunch)
	{
		if (player2->GetCharInfo().attackPos.x > player1->GetCharInfo().bodyPos.x + player1->GetCharInfo().bodyWidth ||
			player2->GetCharInfo().attackPos.x + player2->GetCharInfo().rightPunchWidth< player1->GetCharInfo().bodyPos.x ||
			player2->GetCharInfo().attackPos.y > player1->GetCharInfo().bodyPos.y + player1->GetCharInfo().bodyHeight ||
			player2->GetCharInfo().attackPos.y + player2->GetCharInfo().rightPunchHeight < player1->GetCharInfo().bodyPos.y)
		{
			body = false;
		}

		else
		{
			body = true;
		}
	}
	if (player2->GetCharInfo().leftKick)
	{
		if (player2->GetCharInfo().attackPos.x > player1->GetCharInfo().bodyPos.x + player1->GetCharInfo().bodyWidth ||
			player2->GetCharInfo().attackPos.x + player2->GetCharInfo().leftKickWidth< player1->GetCharInfo().bodyPos.x ||
			player2->GetCharInfo().attackPos.y > player1->GetCharInfo().bodyPos.y + player1->GetCharInfo().bodyHeight ||
			player2->GetCharInfo().attackPos.y + player2->GetCharInfo().leftKickHeight < player1->GetCharInfo().bodyPos.y)

		{
			leg = false;
		}

		else
		{
			leg = true;
		}
	}

	if(body || leg)

		p2onhit = true;

	
	else
		p2onhit = false;

	

	return p2onhit;

}

bool BattleManager::CheckPlayer2SkillHit()
{
	bool p2onhit = false;
	bool body = false;
	bool leg = false;

	if ((player2->GetCharInfo().launchSkillA || player2->GetCharInfo().launchSkillB) && !player2->GetCharInfo().skillOnHit)
	{

		if (player2->GetCharInfo().skillAPos.x > player1->GetCharInfo().bodyPos.x + player1->GetCharInfo().bodyWidth ||
			player2->GetCharInfo().skillAPos.x + player2->GetCharInfo().skillAWidth< player1->GetCharInfo().bodyPos.x ||
			player2->GetCharInfo().skillAPos.y > player1->GetCharInfo().bodyPos.y + player1->GetCharInfo().bodyHeight ||
			player2->GetCharInfo().skillAPos.y + player2->GetCharInfo().skillAHeight < player1->GetCharInfo().bodyPos.y)

			body = false;

		else
			body = true;
		
	}

	if (body || leg)

		p2onhit = true;


	else
		p2onhit = false;

	
	return p2onhit;
}

bool BattleManager::CheckPlayer1Guard()
{
	bool p1guard = false;
	bool punch = false;
	bool kick = false;
	bool skill = false;
	if (player2->GetCharInfo().rightPunch)
	{
		if (player2->GetCharInfo().attackPos.x > player1->GetCharInfo().guardPos.x + player1->GetCharInfo().guardWidth ||
			player2->GetCharInfo().attackPos.x + player2->GetCharInfo().rightPunchWidth< player1->GetCharInfo().guardPos.x ||
			player2->GetCharInfo().attackPos.y > player1->GetCharInfo().guardPos.y + player1->GetCharInfo().guardHeight ||
			player2->GetCharInfo().attackPos.y + player2->GetCharInfo().rightPunchHeight < player1->GetCharInfo().guardPos.y)
		{
			punch = false;
		}

		else
		{
			punch = true;
		}
	}
	if (player2->GetCharInfo().leftKick )
	{
		if (player2->GetCharInfo().attackPos.x > player1->GetCharInfo().guardPos.x + player1->GetCharInfo().guardWidth ||
			player2->GetCharInfo().attackPos.x + player2->GetCharInfo().leftKickWidth< player1->GetCharInfo().guardPos.x ||
			player2->GetCharInfo().attackPos.y > player1->GetCharInfo().guardPos.y + player1->GetCharInfo().guardHeight ||
			player2->GetCharInfo().attackPos.y + player2->GetCharInfo().leftKickHeight < player1->GetCharInfo().guardPos.y)

		{
			kick = false;
		}

		else
		{
			kick = true;
		}
	}
	if ((player2->GetCharInfo().launchSkillA || player2->GetCharInfo().launchSkillB) && !player2->GetCharInfo().skillOnHit)
	{

		if (player2->GetCharInfo().skillAPos.x > player1->GetCharInfo().guardPos.x + player1->GetCharInfo().guardWidth ||
			player2->GetCharInfo().skillAPos.x + player2->GetCharInfo().skillAWidth< player1->GetCharInfo().guardPos.x ||
			player2->GetCharInfo().skillAPos.y > player1->GetCharInfo().guardPos.y + player1->GetCharInfo().guardHeight ||
			player2->GetCharInfo().skillAPos.y + player2->GetCharInfo().skillAHeight < player1->GetCharInfo().guardPos.y)

			skill = false;

		else
			skill = true;

	}

	if (punch || kick || skill)

		p1guard = true;


	else
		p1guard = false;

	

	if (player2->GetCharInfo().launchSkillB && player2->GetCharInfo().cantguard)
	{
		p1guard = false;
	}


	return p1guard;


	
}

bool BattleManager::CheckPlayer2Guard()
{
	bool p2guard = false;
	bool punch = false;
	bool kick = false;
	bool skill = false;
	
	if (player1->GetCharInfo().rightPunch)
	{
		if (player1->GetCharInfo().attackPos.x > player2->GetCharInfo().guardPos.x + player2->GetCharInfo().guardWidth ||
			player1->GetCharInfo().attackPos.x + player1->GetCharInfo().rightPunchWidth< player2->GetCharInfo().guardPos.x ||
			player1->GetCharInfo().attackPos.y > player2->GetCharInfo().guardPos.y + player2->GetCharInfo().guardHeight ||
			player1->GetCharInfo().attackPos.y + player1->GetCharInfo().rightPunchHeight < player2->GetCharInfo().guardPos.y)
		{
			punch = false;
		}

		else
		{
			punch = true;
		}
	}
	if (player1->GetCharInfo().leftKick)
	{
		if (player1->GetCharInfo().attackPos.x > player2->GetCharInfo().guardPos.x + player2->GetCharInfo().guardWidth ||
			player1->GetCharInfo().attackPos.x + player1->GetCharInfo().leftKickWidth< player2->GetCharInfo().guardPos.x ||
			player1->GetCharInfo().attackPos.y > player2->GetCharInfo().guardPos.y + player2->GetCharInfo().guardHeight ||
			player1->GetCharInfo().attackPos.y + player1->GetCharInfo().leftKickHeight < player2->GetCharInfo().guardPos.y)

		{
			kick = false;
		}

		else
		{
			kick = true;
		}
	}
	if ((player1->GetCharInfo().launchSkillA || player1->GetCharInfo().launchSkillB) && !player1->GetCharInfo().skillOnHit)
	{

		if (player1->GetCharInfo().skillAPos.x > player2->GetCharInfo().guardPos.x + player2->GetCharInfo().guardWidth ||
			player1->GetCharInfo().skillAPos.x + player1->GetCharInfo().skillAWidth< player2->GetCharInfo().guardPos.x ||
			player1->GetCharInfo().skillAPos.y > player2->GetCharInfo().guardPos.y + player2->GetCharInfo().guardHeight ||
			player1->GetCharInfo().skillAPos.y + player1->GetCharInfo().skillAHeight < player2->GetCharInfo().guardPos.y)

			skill = false;

		else
			skill = true;

	}

	if (punch || kick || skill)

		p2guard = true;


	else
		p2guard = false;

	if (player1->GetCharInfo().launchSkillB && player1->GetCharInfo().cantguard)
	{
		p2guard = false;
	}

	return p2guard;



}






BattleManager::BattleManager()
{
}

BattleManager::~BattleManager()
{
}



