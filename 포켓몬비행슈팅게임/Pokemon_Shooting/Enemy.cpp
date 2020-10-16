#include "pch.h"
#include "macroFunction.h"
#include "Enemy.h"
#include "Image.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Ash.h"
#include "Item.h"
#include "UIManager.h"


HRESULT Enemy::Init()
{
	isDie = true;
	isHit = false;

	pos.x = -200;
	pos.y = -200;
	item = new Item();
	currentFrameX = currentFrameY = 0;
	updateCount = 0;

	speed = 1.0f;
	angle = PI;
	size = 40;

	HP = 3;
	fireDelay = rand() % 200 + 300;
	fireCount = 0;
	alpha = 255;
	frameTime = 0;
	soundcount = 0;
	touchCount = 0;
	moveAngle = 0;
	centerPos = this->pos;
	return S_OK;
}



HRESULT Enemy::Init(float posX, float posY)
{
	isDie = false;
	isHit = false;

	pos.x = posX;
	pos.y = posY;

	HP = 3;

	horizonDir = false;
	verticalDir  = false;

	
	item->Init();

	ImageManager::GetSingleton()->AddImage("ÂÌ3", "Image/ÂÌ3.bmp", pos.x, pos.y, 66, 21, 3, 1, true, RGB(255, 0, 255));
	image = ImageManager::GetSingleton()->FindImage("ÂÌ3");

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

	
	missileMgr2 = ash->GetMissileMgr();
	missile = missileMgr2->GetMissile();

	frameTime = 0;
	soundcount = 0;
	touchCount = 0;
	moveAngle = 0;
	centerPos = this->pos;
	MoveTime = 0;
	soundcount = 0;
	isEat = false;
	return S_OK;
}


void Enemy::Release()
{

	item->Release();
	delete item;


}

void Enemy::Update()
{
	/*if (!isEat&&isDie)
	{
		isEat = CheckCirCollision(ash->GetPos() , size, item->GetPos(), item->GetSize());
		if (isEat)
		{			
			SoundManager::GetSingleton()->Play("EAT", 0.8f);
			item->SetPos(this->pos);
			item->SetShow(false);
			ash->SetPower(ash->GetPower() + 1);
		}
	}*/
	if (!isDie)
	{
		MoveTime+= TimeManager::GetSingleton()->GetDeltaTime();
		if (HP>0)
		{
			fireTime++;

			if (fireTime % 60 == 30)
			{
				missileMgr.Fire();

			}
		}

		
		if (HP <= 0)
		{
			item->SetPos(this->pos);
			item->SetShow(true);
		}
		if (!isHit)
		{
			this->CheckCrash(&isHit, &onHit);
			//isHit = false;
			
		}


		if (image)
		{
			frameTime += TimeManager::GetSingleton()->GetDeltaTime();
			if (frameTime >= 0.3f)
			{
				currentFrameX++;
				frameTime = 0;
			}

			if (currentFrameX > image->GetMaxKeyFrameX())
			{
				currentFrameX = 0;
			}
			//Move1();
			Move5();

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
	if (item)
	{
		item->Update();
	}
	

}
void Enemy::DieUpdate()
{
	if (isDie&&!isEat)
	{
		if (item)
		{
			item->Update();
			isEat = CheckCirCollision(ash->GetPos(), size, item->GetPos(), item->GetSize());
			if (isEat)
			{
				SoundManager::GetSingleton()->Play("EAT", 0.8f);
				item->SetPos(this->pos);
				item->SetShow(false);
				if (ash->GetPower() < 4)
				{
					ash->SetPower(ash->GetPower() + 1);
				}
				else
				{
					ash->GetUIManager()->SetScore(ash->GetUIManager()->GetSocre() + 100);
				}
			}

		}
		
	}

	if (isDie)
	{
		missileMgr.Update();
	}
}
void Enemy::Render(HDC hdc)
{
	if (!isDie)
	{
		if (image)
		{
			image->AlphaRender(hdc, pos.x, pos.y, currentFrameX, currentFrameY, alpha, 3.0f, degree, false);
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

	if (item)
	{
		item->Render(hdc);
	}
}
void Enemy::Move1()
{
	if (!horizonDir)
	{
		if (this->pos.x >= WINSIZE_X)
		{
			horizonDir = true;
		}
		else pos.x+= speed * TimeManager::GetSingleton()->GetDeltaTime();
	}
	else { 
		if (pos.x <= WINSTART_X) horizonDir = false;
		else pos.x-= speed * TimeManager::GetSingleton()->GetDeltaTime();
		
	}

}
void Enemy::Move2()
{

	if (!verticalDir)
	{
		if (this->pos.y >= WINSIZE_Y/2)
		{
			verticalDir = true;
		}
		else pos.y+= speed * TimeManager::GetSingleton()->GetDeltaTime();
	}
	else {
		if (pos.y <= WINSTART_Y) verticalDir = false;
		else pos.y-= speed * TimeManager::GetSingleton()->GetDeltaTime();

	}
}
void Enemy::Move3()
{
	if (!(pos.y >= WINSIZE_Y / 2))
	{
		pos.y++;

		if (!horizonDir)
		{
			if (this->pos.x >= WINSIZE_X)
			{
				horizonDir = true;
			}
			else pos.x+= speed * TimeManager::GetSingleton()->GetDeltaTime();

		}
		else {
			if (pos.x <= WINSTART_X) horizonDir = false;
			else pos.x-= speed * TimeManager::GetSingleton()->GetDeltaTime();

		}
	}

}
void Enemy::Move4()// Z ÀÚ ÀÌµ¿ ÀÌµ¿
{				  
	
	switch (touchCount)
	{
	case 0 :
		if (!horizonDir)
		{
			if (this->pos.x >= WINSIZE_X)
			{
				horizonDir = true;
				touchCount++;
			}
			else pos.x+= speed * TimeManager::GetSingleton()->GetDeltaTime();
		}
		else {
			if (pos.x <= WINSTART_X)
			{
				horizonDir = false;
				touchCount++;
			}
			else pos.x-= speed * TimeManager::GetSingleton()->GetDeltaTime();

		}
		break;

	case 1:
		if (!(pos.y >= WINSIZE_Y / 2))
		{
			pos.y+= speed * TimeManager::GetSingleton()->GetDeltaTime();
			if (!horizonDir)
			{
				if (this->pos.x >= WINSIZE_X)
				{
					horizonDir = true;
					touchCount++;
				}
				else pos.x+= (speed * 3)* TimeManager::GetSingleton()->GetDeltaTime();

			}
			else
			{
				if (pos.x <= WINSTART_X)
				{
					horizonDir = false;
					touchCount++;
				}
				else pos.x-= (speed * 3)* TimeManager::GetSingleton()->GetDeltaTime();
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
		if (!horizonDir) pos.x+= (speed*3) * TimeManager::GetSingleton()->GetDeltaTime();
		else  pos.x-= (speed * 3) * TimeManager::GetSingleton()->GetDeltaTime();
		
		break;
	default:
		break;
	}
	

	
}				   
void Enemy::Move5()// µ¿±×¶ó¹Ì ÀÌµ¿
{	
	int angle;

	if (pos.x >= WINSIZE_X)
	{
		horizonDir = true;
	}

	else if(pos.x <= 0)
	{
		horizonDir = false;
	}

	if (horizonDir)
	{
		angle = 225;
	}

	else
	{
		angle = 315;
	}
	if(MoveTime < 3.0f)
	{
		
		pos.x += speed * cosf(DEGREE_TO_RADIAN(angle))* TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(DEGREE_TO_RADIAN(270))* TimeManager::GetSingleton()->GetDeltaTime();
			
		
	}

	else if (MoveTime >= 3.0f && MoveTime <=15.0f)
	{
		if (horizonDir)
		{
			if (pos.y != 40)
			{
				pos.x += speed * cosf(DEGREE_TO_RADIAN((angle - 90))) * TimeManager::GetSingleton()->GetDeltaTime();
				pos.y -= speed * sinf(DEGREE_TO_RADIAN((90)))* TimeManager::GetSingleton()->GetDeltaTime();
				
				if (pos.y < 40)
				{
					pos.y = 40;
				}
			}
			
		}

		else
		{
			if (pos.y != 40)
			{
				pos.x += speed * cosf(DEGREE_TO_RADIAN((angle + 90)))* TimeManager::GetSingleton()->GetDeltaTime();
				pos.y -= speed * sinf(DEGREE_TO_RADIAN((90)))* TimeManager::GetSingleton()->GetDeltaTime();

				if (pos.y < 40)
				{
					pos.y = 40;
				}
			}
			
		}
		
	}

	else
	{
		pos.y -= speed * sinf(DEGREE_TO_RADIAN((270)))* TimeManager::GetSingleton()->GetDeltaTime();
	}
	
}				   

void Enemy::SetAsh(Ash* _ash)
{
	ash = _ash;
}

void Enemy::CheckCrash(bool* ishit, bool* onhit)
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
		HP = 0;
	}

	else if(HP>0)
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

					
					//break;
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


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
