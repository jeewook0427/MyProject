#include "FireBird.h"
#include "pch.h"
#include "macroFunction.h"
#include "Image.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Ash.h"


HRESULT FireBird::Init()
{
	/*isHit = false;
	pos.x = WINSIZE_X / 2;
	pos.y = 120;
	HP = 500;
	currentFrameX = currentFrameY = 0;
	updateCount = 0;

	speed = 1.0f;
	angle = PI;
	size = 40;
	scale = 3;
	hasSmall = false;

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



HRESULT FireBird::Init(float posX, float posY)
{
	isHit = false;
	HP = 500;
	pos.x = posX;
	pos.y = posY;
	   
	ImageManager::GetSingleton()->AddImage("boss3", "Image/boss3.bmp", pos.x, pos.y, 243, 68, 3, 1, true, RGB(255, 0, 255));
	image = ImageManager::GetSingleton()->FindImage("boss3");
	gotchaball = ImageManager::GetSingleton()->AddImage("gotchaball", "Image/gotchaball.bmp", 0, 0, 16, 52, 1, 3, true, RGB(255, 0, 255));

	/*ImageManager::GetSingleton()->AddImage("Boss Hit Effects 1", "Image/hiteffect.bmp", 0, 0, 35, 33, 1, 1, true, RGB(255, 0, 255));
	effimg = ImageManager::GetSingleton()->FindImage("Boss Hit Effects 1");*/

	missileMgr.NewMissile();
	missileMgr.Init();
	missileMgr.SetIsEnemy(true);
	missileMgr.SetOwner(this);
	ownmissile = missileMgr.GetMissile();

	currentFrameX = currentFrameY = 0;
	updateCount = 0;

	speed = 300.0f;
	angle = PI / 4;
	size = 40;
	degree = 0;

	fireDelay = rand() % 200 + 300;
	fireCount = 0;

	width = 53;
	height = 32;
	alpha = 255;
	block = 0;
	
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
	return S_OK;
}


void FireBird::Release()
{

	missileMgr.Release();

}

void FireBird::Update()
{
	frameTime += TimeManager::GetSingleton()->GetDeltaTime();
	if (HP > 0)
	{
		fireTime++;

		if (fireTime % 30 == 29)
		{
			missileMgr.Fire();

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

		else
		{
			soundcount = 0;
		}
		missileMgr.Update();
		if (HP < 250)
		{
			missileMgr.SetChangeMi(true);
		}
	}
	else
	{
		if (frameTime >= 0.3f)
		{
			if (scale > 0.1f)
			{
				if (currentFrameX == 2)
				{
					currentFrameX++;
					alpha = 255;


				}
				if (currentFrameX == 0 || currentFrameX == 1)
				{
					scale -= 0.7f;
					currentFrameX++;
					alpha -= 50;
					

				}
			}
			else if (scale <= 0.1f)
			{
				isgotcha = true;
			}
			if (isgotcha)
			{
				if (isgotcha&&currentFrameY == 0)
				{
					currentFrameY = 3;
				}
				currentFrameY--;
				if (currentFrameY == 0)
				{
					currentFrameY = 0;
					isgotcha = false; isDie = true;
				}
			}

			if (currentFrameX > image->GetMaxKeyFrameX())
			{
				alpha = 255;
				currentFrameX = 0;
				scale += 0.7f;
				
			}
			frameTime = 0;
		}


		pos.x += cosf((atan2f(-(ash->GetPos().y - 50 - pos.y), (ash->GetPos().x - pos.x))))*speed* TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= sinf((atan2f(-(ash->GetPos().y - 50 - pos.y), (ash->GetPos().x - pos.x)))) * speed * TimeManager::GetSingleton()->GetDeltaTime();
	}


}

void FireBird::Render(HDC hdc)
{
	if (HP > 0)
	{
		if (image)
		{
			if (MoveTime >= 3.0f)
			{
				alpha -= 50;
			}
			else
			{
				alpha = 255;
			}

			image->AlphaRender(hdc, pos.x, pos.y, currentFrameX, currentFrameY, alpha, 3, degree, false);
		}

		if (!ash->GetSkill())
		{
			missileMgr.Render(hdc);
		}
		
	}
	else
	{
		if (image)
		{
			if (!isDie)
			{
				if (scale > 0.1f)
					image->AlphaRender(hdc, pos.x, pos.y, currentFrameX, currentFrameY, alpha, scale, degree, false);

				else gotchaball->AlphaRender(hdc, pos.x, ash->GetPos().y - 50, 0, currentFrameY, 255, 4.4f, degree, false);

			}
		}
	}
}
void FireBird::SetAsh(Ash* _ash)
{
	ash = _ash;
}
//


void FireBird::CheckCrash(bool* ishit, bool* onhit)
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
			SoundManager::GetSingleton()->Play("GatchaSound",0.5f);
			ash->SetSkillcount(ash->GetSkillcount() + 1);
			block++;
		}
	}

	if (HP > 0  )
	{
		if (!(MoveTime < 4 && MoveTime >3))
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
							if (HP <= 0&&block==0)
							{
								SoundManager::GetSingleton()->Play("GatchaSound", 0.5f);
								ash->SetSkillcount(ash->GetSkillcount() + 1);
								block++;
							}
							(*it)->SetOnHit(true);
							*ishit = true;
						}
						
					}
				}

			}
		}
		

		if (!ash->GetDebugMode()&&!ash->GetSkill() && !ash->GetIsStart())
		{
			ownmissile = missileMgr.GetMissile();
			for (auto it = ownmissile.begin(); it != ownmissile.end(); it++)
			{
				for (int i = 0; i < 20; i++)
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

void FireBird::Move()
{
	MoveTime += TimeManager::GetSingleton()->GetDeltaTime();
	
	if (HP < 250)
	{
		if (horizonDir)
		{
			pos.x-= 150 * TimeManager::GetSingleton()->GetDeltaTime();
			

			if (pos.x < 50)
			{
				pos.x = 50;
	
			}
			else
			{
				pos.y += 50 * TimeManager::GetSingleton()->GetDeltaTime();
			}
		}
		else
		{
			pos.x += 150 * TimeManager::GetSingleton()->GetDeltaTime();
			
			if (pos.x > WINSIZE_X - 50)
			{
				pos.x = WINSIZE_X - 50;
			}
			else
			{
				pos.y += 50 * TimeManager::GetSingleton()->GetDeltaTime();
			}
		}
		
	}
	
	if (MoveTime > 4.0f)
	{
		pos.x = rand() % 300 + 100;
		pos.y = rand() % 300 + 100;

		if (pos.x > WINSIZE_X / 2)
		{
			horizonDir = true;
		}
		else
		{
			horizonDir = false;
		}
		MoveTime = 0;
	}
}

void FireBird::Move2()
{

}

FireBird::FireBird()
{
}


FireBird::~FireBird()
{
}
