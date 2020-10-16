#include "Lugia.h"
#include "pch.h"
#include "macroFunction.h"

#include "Image.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Ash.h"



HRESULT Lugia::Init()
{
	/*HP = 500;
	isHit = false;
	pos.x = WINSIZE_X / 2;
	pos.y = 120;

	currentFrameX = currentFrameY = 0;
	updateCount = 0;

	speed = 1.0f;
	angle = PI;
	size = 40;

	fireDelay = rand() % 200 + 300;
	fireCount = 0;
	alpha = 255;
	frameTime = 0;
	soundcount = 0;
	touchCount = 0;
	moveAngle = 0;
	centerPos = this->pos;
	MoveTime = 0;*/
	return S_OK;
}



HRESULT Lugia::Init(float posX, float posY)
{
	HP = 500;
	isHit = false;
	pos.x = WINSIZE_X /2 ;
	pos.y = 120;


	ImageManager::GetSingleton()->AddImage("boss1", "Image/boss1.bmp", pos.x, pos.y, 520, 65, 8, 1, true, RGB(255, 0, 255));
	image = ImageManager::GetSingleton()->FindImage("boss1");
	gotchaball = ImageManager::GetSingleton()->AddImage("gotchaball", "Image/gotchaball.bmp", 0, 0, 16, 52, 1, 3, true, RGB(255, 0, 255));

	missileMgr.NewMissile();
	missileMgr.Init();
	missileMgr.SetIsEnemy(true);
	missileMgr.SetOwner(this);
	ownmissile = missileMgr.GetMissile();

	currentFrameX = currentFrameY = 0;
	updateCount = 0;

	speed = 80.0f;
	angle = PI / 4;
	size = 40;
	degree = 0;
	block = 0;

	fireDelay = rand() % 200 + 300;
	fireCount = 0;

	width = 53;
	height = 32;
	alpha = 255;

	fireTime = 0;
	missileMgr2 = ash->GetMissileMgr();
	missile = missileMgr2->GetMissile();

	soundcount = 0;


	frameTime = 0;
	soundcount = 0;
	touchCount = 0;
	moveAngle = 0;
	centerPos = this->pos;
	MoveTime = 0;
	scale = 3.0f;
	isDie = false;
	isgotcha = false;
	gotchatime = 0;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			diepos[i][j] = { 0,0 };
		}
	}


	return S_OK;
}


void Lugia::Release()
{

	missileMgr.Release();

}

void Lugia::Update()
{
	frameTime += TimeManager::GetSingleton()->GetDeltaTime();
	if (HP > 0)
	{
		fireTime++;

		if (fireTime % 10 == 9)
		{
			soundcount = 0;
		}
		if (HP>250 && fireTime % 5 == 4)
		{
			missileMgr.Fire();

		}
		if (fireTime % 15 == 14 && HP <= 250)
		{
			missileMgr.Fire();
			missileMgr.SetAnlge(RADIAN_TO_DEGREE(atan2f(-(ash->GetPos().y - pos.y), (ash->GetPos().x - pos.x))));
		}
		if (!isHit)
		{
			this->CheckCrash(&isHit, &onHit);
		}

		if (image)
		{
			frameTime += TimeManager::GetSingleton()->GetDeltaTime();
			if (frameTime >= 0.2f)
			{
				currentFrameX++;
				frameTime = 0;
			}

			if (currentFrameX > image->GetMaxKeyFrameX())
			{
				currentFrameX = 0;
			}
			Move();

			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					diepos[i][j].x = pos.x + i * 22 - 100;
					diepos[i][j].y = pos.y + j * 22 - 100;
				}
			}

		}

		if (isHit)
		{			

			if (soundcount == 0)
			{
				SoundManager::GetSingleton()->Play("EXPLOSION");
				soundcount++;
			}
			
			isHit = false;

		}

		if (HP < 250)
		{
			missileMgr.SetChangeMi(true);
		}

		missileMgr.Update();
	}
	else
	{
		gotchatime++;
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				diepos[i][j].x += 200 * cosf(atan2(-(ash->GetPos().y -50 - diepos[i][j].y), ash->GetPos().x - diepos[i][j].x)) * TimeManager::GetSingleton()->GetDeltaTime();
				diepos[i][j].y -= 200 * sinf(atan2(-(ash->GetPos().y - 50 - diepos[i][j].y), ash->GetPos().x- diepos[i][j].x))* TimeManager::GetSingleton()->GetDeltaTime();

			}
		}

		if ((diepos[0][0].y < (ash->GetPos().y - 40) && diepos[0][0].y > (ash->GetPos().y - 60)) && (diepos[0][15].y < (ash->GetPos().y - 40) && diepos[0][15].y >(ash->GetPos().y - 60))
			&& (diepos[15][0].y < (ash->GetPos().y - 40) && diepos[15][0].y >(ash->GetPos().y - 60)) && (diepos[15][15].y < (ash->GetPos().y - 40) && diepos[15][15].y >(ash->GetPos().y - 60)))
		
		{
			if (gotchatime % 10 == 9)
			{
				currentFrameY --;
				gotchatime = 0;

				if (currentFrameY < 0)
				{
					isDie = true;
				}
			}


			
			
		}

		else
		{
			currentFrameY = 2;
		}
		
	}


			
		
	
}

void Lugia::Render(HDC hdc)
{
	if (HP > 0)
	{

		if (image)
		{
			image->AlphaRender(hdc, pos.x, pos.y, currentFrameX, currentFrameY, alpha, 3, degree, false);
		}


		if (!ash->GetSkill())
		{
			missileMgr.Render(hdc);
		}
	}
	else
	{
		if (image && !isDie)
		{
			
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					image->LugiaDeathRender(hdc, diepos[i][j].x, diepos[i][j].y, i, j, 3.0f);
					gotchaball->AlphaRender(hdc, ash->GetPos().x, ash->GetPos().y-50, 0, currentFrameY, 255, 4.4f, degree, false);
				}
			}

			
		}
	}
}
void Lugia::SetAsh(Ash* _ash)
{
	ash = _ash;
}

void Lugia::CheckCrash(bool* ishit, bool* onhit)
{
	FPOINT temppos = { -100,-100 };
	if (ash->GetSkill())
	{
		for (auto it = ownmissile.begin(); it != ownmissile.end(); it++)
		{
			(*it)->SetIsFire(false);
			(*it)->SetPos(temppos);
		}

		*ishit = true;
		HP -= 3;
		if (HP <= 0 && block==0)
		{
			SoundManager::GetSingleton()->Play("GatchaSound");
			ash->SetSkillcount(ash->GetSkillcount() + 1);
			block++;
		}
	}
	if (HP > 0  )
	{
		missile = missileMgr2->GetMissile();
		for (auto it = missile.begin(); it != missile.end(); it++)
		{
			for (int i = 0; i < 1; i++)
			{
				if (size/2 + (*it)->GetSize()/2 < GetDistance(pos.x, pos.y, (*it)->GetPos()[i].x, (*it)->GetPos()[i].y))
				{
					continue;
				}

				else
				{
					if (!(*it)->GetOnHit())
					{
						HP -= 2;
						if (HP <= 0 && block==0)
						{
							SoundManager::GetSingleton()->Play("GatchaSound");
							ash->SetSkillcount(ash->GetSkillcount() + 1);
							block++;
						}
						(*it)->SetOnHit(true);
						*ishit = true;
					}
				}
			}

		}

		if (!ash->GetDebugMode() && !ash->GetIsStart() && !ash->GetSkill())
		{
			ownmissile = missileMgr.GetMissile();
			for (auto it = ownmissile.begin(); it != ownmissile.end(); it++)
			{
				for (int i = 0; i < 5; i++)
				{
					if (ash->GetSize()/2 + (*it)->GetSize()/2 < GetDistance(ash->GetPos().x, ash->GetPos().y, (*it)->GetPos()[i].x, (*it)->GetPos()[i].y))
					{
						continue;
					}


					else
					{
						(*it)->SetOnHit(true);
						*onhit = true;
						missileMgr.SetOnHit(true);
						ash->SetisHit(true);
						break;
					}
				}

			}
		}

		



	}
}
void Lugia::Move()// 동그라미 이동
{
	
	moveAngle++;
	
	if (moveAngle <= 360)
	{
		pos.x = centerPos.x + 100 * cosf(DEGREE_TO_RADIAN(moveAngle));
		pos.y = centerPos.y - 100 * sinf(DEGREE_TO_RADIAN(moveAngle));
		if (pos.x <= 100 ) { horizonDir = false; verticalDir = false; }
		else if (pos.x >= WINSIZE_X - 100 ) { horizonDir = true; verticalDir = true; }

	}
	else
	{
	
		MoveTime += TimeManager::GetSingleton()->GetDeltaTime();
		if (MoveTime < 1.5f)
		{

			if (!horizonDir && !verticalDir)
			{
				pos.x += (speed)* TimeManager::GetSingleton()->GetDeltaTime();
				centerPos.x = pos.x - 100 * cosf(DEGREE_TO_RADIAN(0));
				centerPos.y = pos.y + 100 * sinf(DEGREE_TO_RADIAN(0));
			}
			else
			{
				pos.x -= (speed)* TimeManager::GetSingleton()->GetDeltaTime();
				centerPos.x = pos.x - 100 * cosf(DEGREE_TO_RADIAN(0));
				centerPos.y = pos.y + 100 * sinf(DEGREE_TO_RADIAN(0));
			}
		}
		else
		{
			moveAngle = 0;
			MoveTime = 0;
		}
	
	}
}


Lugia::Lugia()
{
}


Lugia::~Lugia()
{
}
