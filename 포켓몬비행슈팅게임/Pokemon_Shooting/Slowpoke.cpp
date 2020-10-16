#include "Slowpoke.h"
#include "pch.h"
#include "macroFunction.h"
#include "Image.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Ash.h"



HRESULT Slowpoke::Init()
{
	isDie = true;
	isHit = false;

	pos.x = -200;
	pos.y = -200;

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
	MoveTime = 0;

	missileMgr.SetCharacter(ash);
	return S_OK;
}

HRESULT Slowpoke::Init(float posX, float posY)
{
	isDie = false;
	isHit = false;

	pos.x = posX;
	pos.y = posY;

	ImageManager::GetSingleton()->AddImage("야도란", "Image/야도란.bmp", pos.x, pos.y, 99, 21, 3, 1, true, RGB(255, 0, 255));
	image = ImageManager::GetSingleton()->FindImage("야도란");


	missileMgr.NewMissile();
	missileMgr.Init();
	missileMgr.SetIsEnemy(true);
	missileMgr.SetOwner(this);
	ownmissile = missileMgr.GetMissile();

	currentFrameX = currentFrameY = 0;
	updateCount = 0;

	speed = 120.0f;
	angle = PI / 4;
	size = 40;
	degree = 0;

	fireDelay = rand() % 200 + 300;
	fireCount = 0;

	width = 53;
	height = 32;
	alpha = 255;
	fireTime = 0;

	missileMgr2 = ash->GetMissileMgr();
	missile = missileMgr2->GetMissile();

	soundcount = 0;
	HP = 3;

	frameTime = 0;
	soundcount = 0;
	touchCount = 0;
	moveAngle = 0;
	centerPos = this->pos;

	MoveTime = 0;
	if (pos.x < WINSIZE_X / 2) horizonDir = false;
	else  horizonDir = true;
	return S_OK;
}

void Slowpoke::Release()
{
	missileMgr.Release();
}

void Slowpoke::Update()
{
	if (!isDie)
	{
		if (HP>0)
		{
			fireTime++;

			if (fireTime % 30 == 29)
			{
				missileMgr.SetAnlge(RADIAN_TO_DEGREE(atan2f(-(ash->GetPos().y - pos.y), (ash->GetPos().x - pos.x))));
				missileMgr.Fire();
				
			}
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

		if (HP<=0)
		{
			if (pos.x < WINSIZE_X / 2)
			{
				pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime() * cosf(angle + PI / 2);
				pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime() * sinf(angle + PI / 2);
				degree -= 1080 * TimeManager::GetSingleton()->GetDeltaTime();

			}

			else if (pos.x == WINSIZE_X / 2)
			{
				pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime() * cosf(angle + PI / 4);
				pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime() * sinf(angle + PI / 4);
				degree -= 1080 * TimeManager::GetSingleton()->GetDeltaTime();
			}
			else
			{
				pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime() * cosf(angle);
				pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime() * sinf(angle);
				degree += 1080 * TimeManager::GetSingleton()->GetDeltaTime();

			}

			alpha -= 500 * TimeManager::GetSingleton()->GetDeltaTime();
			if (alpha < 0)
			{
				alpha = 0;
				isDie = true;
			}

			if (soundcount == 0)
			{
				SoundManager::GetSingleton()->Play("EXPLOSION");
				soundcount++;
			}


		}

		else
		{
			soundcount = 0;
		}

		missileMgr.Update();
	}

	this->CheckCrash(&isHit, &onHit);
}

void Slowpoke::Render(HDC hdc)
{
	if (!isDie)
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
		missileMgr.Render(hdc);
	}

}
void Slowpoke::DieUpdate()
{
	if (isDie)
	{
		missileMgr.Update();
	}
}

void Slowpoke::SetAsh(Ash* _ash)
{
	ash = _ash;
}

void Slowpoke::CheckCrash(bool* ishit, bool* onhit)
{
	FPOINT temppos = { -100, -100 };
	if (ash->GetSkill())
	{
		for (auto it = ownmissile.begin(); it != ownmissile.end(); it++)
		{
			(*it)->SetIsFire(false);
			(*it)->SetPos(temppos);
		}
		HP = 0;
		*ishit = true;
	}

	else if (HP>0)
	{
		missile = missileMgr2->GetMissile();
		for (auto it = missile.begin(); it != missile.end(); it++)
		{
			for (int i = 0; i < 1; i++)
			{
				if (size / 2 + (*it)->GetSize() / 2 < GetDistance(pos.x, pos.y, (*it)->GetPos()[i].x, (*it)->GetPos()[i].y))
				{
					continue;
				}

				else
				{
					if (!(*it)->GetOnHit())
					{
						HP -= 1;
						(*it)->SetOnHit(true);
						//*ishit = true;
					}
				}
			}

		}





	}

	if (!ash->GetDebugMode() && !ash->GetIsStart())
	{
		ownmissile = missileMgr.GetMissile();
		for (auto it = ownmissile.begin(); it != ownmissile.end(); it++)
		{
			for (int i = 0; i < 1; i++)
			{
				if (ash->GetSize() / 2 + (*it)->GetSize() / 2 < GetDistance(ash->GetPos().x, ash->GetPos().y, (*it)->GetPos()[i].x, (*it)->GetPos()[i].y))
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
void Slowpoke::Move()
{
	switch (touchCount)
	{
	case 0:
		if (!horizonDir)
		{
			if (this->pos.x >= WINSIZE_X)
			{
				horizonDir = true;
				touchCount++;
			}
			else pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime();
		}
		else {
			if (pos.x <= WINSTART_X)
			{
				horizonDir = false;
				touchCount++;
			}
			else pos.x -= speed * TimeManager::GetSingleton()->GetDeltaTime();

		}
		break;

	case 1:
		if (!(pos.y >= centerPos.y + 400))//
		{
			pos.y += speed * TimeManager::GetSingleton()->GetDeltaTime();
			if (!horizonDir)
			{
				if (this->pos.x >= WINSIZE_X)
				{
					horizonDir = true;
					touchCount++;
				}
				else pos.x += (speed * 3)* TimeManager::GetSingleton()->GetDeltaTime();

			}
			else
			{
				if (pos.x <= WINSTART_X)
				{
					horizonDir = false;
					touchCount++;
				}
				else pos.x -= (speed * 3)* TimeManager::GetSingleton()->GetDeltaTime();
			}
		}
		else
		{
			touchCount++;
			if (!horizonDir)horizonDir = true;
			else horizonDir = false;
		}
		break;
	case 2:
		if (!horizonDir) pos.x += (speed) * TimeManager::GetSingleton()->GetDeltaTime();
		else  pos.x -= (speed ) * TimeManager::GetSingleton()->GetDeltaTime();

		break;
	default:
		break;
	}

}


Slowpoke::Slowpoke()
{
}


Slowpoke::~Slowpoke()
{
}
