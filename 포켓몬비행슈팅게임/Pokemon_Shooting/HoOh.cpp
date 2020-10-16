#include "HoOh.h"
#include "pch.h"
#include "macroFunction.h"
#include "Image.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Ash.h"


HRESULT HoOh::Init()
{
	/*pos.x = WINSIZE_X / 2;
	pos.y = 120;
	HP = 500;
	isHit = false;
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
	MoveTime = 0*/
	return S_OK;
}



HRESULT HoOh::Init(float posX, float posY)
{
	pos.x = posX;
	pos.y = posY;
	
	HP = 500;
	isHit = false;
	ImageManager::GetSingleton()->AddImage("boss2", "Image/boss2.bmp", pos.x, pos.y, 469, 61,7 , 1, true, RGB(255, 0, 255));
	image = ImageManager::GetSingleton()->FindImage("boss2");
	gotchaball = ImageManager::GetSingleton()->AddImage("gotchaball", "Image/gotchaball.bmp", 0, 0, 16, 52, 1, 3, true, RGB(255, 0, 255));

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
	return S_OK;
}


void HoOh::Release()
{

	missileMgr.Release();

}

void HoOh::Update()
{
	frameTime += TimeManager::GetSingleton()->GetDeltaTime();
	if (HP > 0)
	{
		fireTime++;

		if (fireTime % 60 == 59)
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
			//alpha -= 5000 * TimeManager::GetSingleton()->GetDeltaTime();
			if (alpha < 0)
			{
				alpha = 0;
			}

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
		if (HP < 250)
		{
			missileMgr.SetChangeMi(true);
		}
		missileMgr.Update();
	}
	else
	{
		if (image)
		{
			if (frameTime >= 0.3f)
			{
				if (scale > 0.1f)
				{
					if (currentFrameX == 2 || currentFrameX == 5)
					{
						currentFrameX++;
						alpha = 255;
						scale += 0.7f;


					}
					if (currentFrameX == 0 || currentFrameX == 1 || currentFrameX == 3 || currentFrameX == 4 || currentFrameX == 6 )
					{
						scale -= 0.7f;
						currentFrameX++;
						alpha -= 50;
						//hasSmall = true;

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
					scale = 0.1f;
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
					//if (scale >= 0.1f)
					scale -= 0.7f;
					hasSmall = true;
				}
				frameTime = 0;
			}


			pos.x += cosf((atan2f(-(ash->GetPos().y - 50 - pos.y), (ash->GetPos().x - pos.x))))*speed* TimeManager::GetSingleton()->GetDeltaTime();
			pos.y -= sinf((atan2f(-(ash->GetPos().y - 50 - pos.y), (ash->GetPos().x - pos.x)))) * speed * TimeManager::GetSingleton()->GetDeltaTime();
		}

	
		
	}
}

void HoOh::Render(HDC hdc)
{
	char sZtext[256];
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
void HoOh::SetAsh(Ash* _ash)
{
	ash = _ash;
}
//


void HoOh::CheckCrash(bool* ishit, bool* onhit)
{
	FPOINT temppos = { -100,-100 };
	missile = missileMgr2->GetMissile();
	ownmissile = missileMgr.GetMissile();
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
			SoundManager::GetSingleton()->Play("GatchaSound", 0.5f);
			ash->SetSkillcount(ash->GetSkillcount() + 1);
			block++;
		}
	}

	if (HP > 0 )
	{
		
		for (auto it = missile.begin(); it != missile.end(); it++)
		{
			if (!(*it)->GetOnHit())
			{
				for (int i = 0; i < 1; i++)
				{
					if (size/2 + (*it)->GetSize()/2 < GetDistance(pos.x, pos.y, (*it)->GetPos()[i].x, (*it)->GetPos()[i].y))
					{
						continue;
					}

					else
					{
						HP -= 2;
						if (HP <= 0 && block == 0)
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
		if (!ash->GetDebugMode() && !ash->GetIsStart()&&!ash->GetSkill())
		{
			
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
void HoOh::Move()// 십자가 이동
{
	MoveTime += TimeManager::GetSingleton()->GetDeltaTime();
	
	if (MoveTime < 4.0f)
	{
		if (!horizonDir)
		{
			if (this->pos.x >= WINSIZE_X)
			{
				horizonDir = true;
			}
			else pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime();
		}
		else {
			if (pos.x <= WINSTART_X) horizonDir = false;
			else pos.x -= speed * TimeManager::GetSingleton()->GetDeltaTime();

		}
	}
	else
	{
		if (!verticalDir)
		{
			if (pos.y >= centerPos.y + 120)
			{
				verticalDir = true;
				MoveTime = 0;
			}
			else pos.y += speed * TimeManager::GetSingleton()->GetDeltaTime();
		}
		else {
			if (pos.y <= centerPos.y - 120)
			{ verticalDir = false;
			  MoveTime = 0;
			}
			else pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime();

		}
		
	}
}

void HoOh::Move2()
{

}


HoOh::HoOh()
{
}


HoOh::~HoOh()
{
}
