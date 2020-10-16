#include "Golbat.h"
#include "pch.h"
#include "macroFunction.h"
#include "Enemy.h"
#include "Image.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Ash.h"


HRESULT Golbat::Init()
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
	return S_OK;
}

HRESULT Golbat::Init(float posX, float posY)
{
	isDie = false;
	isHit = false;

	pos.x = posX;
	pos.y = posY;

	ImageManager::GetSingleton()->AddImage("°ñ¹î", "Image/bat.bmp", pos.x, pos.y, 58, 22, 2, 1, true, RGB(255, 0, 255));
	image = ImageManager::GetSingleton()->FindImage("°ñ¹î");


	

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
	return S_OK;
}

void Golbat::Release()
{
	
}

void Golbat::Update()
{


	if (!isDie)
	{

		fireTime++;

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

			onHit = CheckCirCollision(ash->GetPos(), ash->GetSize(), this->GetPos(), size);
			if (onHit)
			{
				isDie = true;
				if (!ash->GetDebugMode()) ash->SetisHit(true);
			}
		}

		if (isHit)
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

			if (alpha <= 0)
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

	}

	this->CheckCrash(&isHit, &onHit);
}

void Golbat::DieUpdate()
{

	if (isDie)
	{
		alpha = 0;
	}
}

void Golbat::Render(HDC hdc)
{
	if (!isDie)
	{
		if (image)
		{
			image->AlphaRender(hdc, pos.x, pos.y, currentFrameX, currentFrameY, alpha, 3, degree, false);
		}

		if (!ash->GetSkill())
		{

		}
	}
	else
	{

	}
}

void Golbat::SetAsh(Ash * _ash)
{
	ash = _ash;
}

void Golbat::CheckCrash(bool * ishit, bool * onhit)
{
	FPOINT temppos = { -100, -100 };
	if (ash->GetSkill())
	{
		for (auto it = ownmissile.begin(); it != ownmissile.end(); it++)
		{
			(*it)->SetIsFire(false);
			(*it)->SetPos(temppos);
		}
		*ishit = true;
	}

	else if (!isHit)
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
					(*it)->SetOnHit(true);
					*ishit = true;
					break;
				}
			}

		}





	}

	if (!ash->GetDebugMode() && !ash->GetIsStart())
	{
		//ownmissile = missileMgr.GetMissile();
		for (auto it = ownmissile.begin(); it != ownmissile.end(); it++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (ash->GetSize() / 2 + (*it)->GetSize() / 2 < GetDistance(ash->GetPos().x, ash->GetPos().y, (*it)->GetPos()[i].x, (*it)->GetPos()[i].y))
				{
					continue;
				}


				else
				{
					(*it)->SetOnHit(true);
					*onhit = true;
					//missileMgr.SetOnHit(true);
					ash->SetisHit(true);
					break;
				}
			}

		}
	}


}

void Golbat::Move()
{
	if (ash->GetIsStart())
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
		pos.x += cosf(atan2f(-(ash->GetPos().y - pos.y), (ash->GetPos().x - pos.x)))*speed* TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= sinf(atan2f(-(ash->GetPos().y - pos.y), (ash->GetPos().x - pos.x))) * speed * TimeManager::GetSingleton()->GetDeltaTime();
	}



}

Golbat::Golbat()
{
}

Golbat::~Golbat()
{
}
