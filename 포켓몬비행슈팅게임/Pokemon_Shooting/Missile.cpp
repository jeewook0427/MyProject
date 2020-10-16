#include "Missile.h"
#include "macroFunction.h"
#include "Enemy.h"
#include "Image.h"

HRESULT Missile::Init()
{
	//size = 21;
	//angle = PI / 2.0f;
	//speed = 400.0f;
	//isFire = false;
	//onHit = false;
	//power = 1;

	//img = new Image();
	//if (FAILED(img->Init("Image/bullet.bmp", size, size, true, RGB(255, 0, 255))))
	//{
	//	MessageBox(g_hWnd, "Image/구슬.bmp 초기화 실패", "Missile.cpp", MB_OK);
	//	return E_FAIL;
	//}

	//degree = 18;
	//missileCount = 0;
	//currMissile = 1;

	return S_OK;
}

HRESULT Missile::Init(int posX)
{
	/*pos[0].x = 0;
	pos[0].y = 0;
	size = 21;
	angle = PI / 2.0f;
	speed = 400.0f;
	isFire = false;
	adjustAngle = 0.0f;
	onHit = false;

	isPlayer = false;
	isEnemy = false;
	isBoss = false;

	target = nullptr;

	img = new Image();
	if (FAILED(img->Init("Image/bullet.bmp", size, size, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, "Image/구슬.bmp 초기화 실패", "Missile.cpp", MB_OK);
		return E_FAIL;
	}

	degree = 18;
	missileCount = 0;
	currMissile = 1;*/

	return S_OK;


}

void Missile::Release()
{
	
}

void Missile::Update()
{





}

void Missile::Render(HDC hdc)
{


}

void Missile::SetPos(FPOINT pt)
{
	for (int i = 0; i < 30; i++)
	{
		pos[i] = pt;
	}
}

Missile::Missile()
{
}


Missile::~Missile()
{
}



HRESULT PlayerMissile::Init()
{
	size = 21;
	angle = PI / 2.0f;
	speed = 600.0f;
	isFire = false;
	onHit = false;
	power = 1;
	currframex = 3;
	currframey = 0;
	blockscore = 0;

	effect = false;
	ImageManager::GetSingleton()->AddImage("Monsterball", "Image/monsterball.bmp", 0, 0, 192, 52, 12, 3, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("Monsterball");

	ImageManager::GetSingleton()->AddImage("Boss Hit Effects 1", "Image/hiteffect.bmp", 0, 0, 35, 33, 1, 1, true, RGB(255, 0, 255));
	effimg = ImageManager::GetSingleton()->FindImage("Boss Hit Effects 1");

	degree = 18;
	missileCount = 0;
	currMissile = 1;

	return S_OK;
}

void PlayerMissile::Update()
{
	if (isFire&!onHit)
	{
		if (power >= 1)
		{
			pos[0].x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
			pos[0].y -= speed * sinf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
			missileCount = 1;
			currframex = 2;
			if (power >= 2)
			{
				currframex = 3;
			}
			if (power >= 3)
			{
				currframex = 10;
			}
			if (power >= 4)
			{
				currframex = 6;
			}
			
		}
		
		
		
	}

	if (onHit||effect)
	{
		isFire = false;
		effect = true;
		missileCount++;
		blockscore = 1;
		if (missileCount % 5 == 4)
		{
			
			effect = false;
			missileCount = 0;
			
		}

	}

}

void PlayerMissile::Render(HDC hdc)
{
	if (isFire)
	{
		if (img)
		{
			for (int i = 0; i < 1; i++)
			{
				img->AlphaRender(hdc, pos[0].x, pos[0].y, currframex, currframey, 255, 2.0f);
			}
						
			
		}
		
	}

	if (effect)
	{
		if (effimg)
		{
			effimg->AlphaRender(hdc, pos[0].x, pos[0].y, 0, 0, 255, 1.5f);
		}
	}
}

PlayerMissile::PlayerMissile()
{


}


PlayerMissile::~PlayerMissile()
{
}

HRESULT BulbasaurMissile::Init()
{
	for (int i = 0; i < 3; i++)
	{
		pos[i].x = -50;
		pos[i].y = -50;
	}
	size = 21;
	angle = PI / 2.0f;
	speed = 400.0f;
	isFire = false;
	onHit = false;

	
	ImageManager::GetSingleton()->AddImage("EnemyMissile", "Image/bullet.bmp", size, size, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("EnemyMissile");

	degree = 18;
	missileCount = 0;
	currMissile = 1;

	return S_OK;
}

void BulbasaurMissile::Update()
{
	degree = 30;
	if (isFire)
	{
		for (int i = 0; i < 3; i++)
		{
			pos[i].x += speed * cosf(angle + (i*DEGREE_TO_RADIAN(degree)))* TimeManager::GetSingleton()->GetDeltaTime();
			pos[i].y -= speed * sinf(DEGREE_TO_RADIAN(270))* TimeManager::GetSingleton()->GetDeltaTime();
		}


	}
	if (!isFire)
	{
		currMissile = 1;
	}

}

void BulbasaurMissile::Render(HDC hdc)
{
	if (isFire)
	{
		for (int i = 0; i < 3; i++)
		{
			img->Render(hdc, pos[i].x, pos[i].y);
		}
	}


}

BulbasaurMissile::BulbasaurMissile()
{
}

BulbasaurMissile::~BulbasaurMissile()
{
}


HRESULT SlowpokeMissile::Init()
{
	pos[0].x = -50;
	pos[0].y = -50;
	size = 21;
	angle = PI / 2.0f;
	speed = 400.0f;
	isFire = false;
	onHit = false;

	ImageManager::GetSingleton()->AddImage("EnemyMissile", "Image/bullet.bmp", size, size, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("EnemyMissile");

	degree = 18;
	missileCount = 0;
	currMissile = 1;

	return S_OK;
}

void SlowpokeMissile::Update()
{
	if (isFire)
	{
		for (int i = 0; i < 1; i++)
		{
			pos[i].x += speed * cosf(angle)* TimeManager::GetSingleton()->GetDeltaTime();
			pos[i].y -= speed * sinf(angle)* TimeManager::GetSingleton()->GetDeltaTime();
		}


		for (int i = 0; i < 1; i++)
		{
			if (pos[i].y > WINSIZE_Y || pos[i].x <0 || pos[i].x > WINSIZE_X || pos[i].y < 0)
			{
				isFire = false;

			}
		}

	}


}

void SlowpokeMissile::Render(HDC hdc)
{
	for (int i = 0; i < 1; i++)
	{
		img->Render(hdc, pos[i].x, pos[i].y);

	}
}

SlowpokeMissile::SlowpokeMissile()
{
}

SlowpokeMissile::~SlowpokeMissile()
{
}


HRESULT DarkpetMissile::Init()
{
	pos[0].x = -50;
	pos[0].y = -50;
	size = 21*2;
	angle = PI / 2.0f;
	speed = 400.0f;
	isFire = false;
	onHit = false;

	ImageManager::GetSingleton()->AddImage("BigEnemyMissile", "Image/bullet.bmp", size, size, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("BigEnemyMissile");

	degree = 18;
	missileCount = 0;
	currMissile = 1;

	return S_OK;
}

void DarkpetMissile::Update()
{
	if (isFire)
	{
		for (int i = 0; i < 1; i++)
		{
			pos[i].x += speed * cosf(angle)* TimeManager::GetSingleton()->GetDeltaTime();
			pos[i].y -= speed * sinf(angle)* TimeManager::GetSingleton()->GetDeltaTime();
		}

	}
	if (!isFire)
	{
		currMissile = 1;
	}
}

void DarkpetMissile::Render(HDC hdc)
{
	for (int i = 0; i < 1; i++)
	{
		img->Render(hdc, pos[i].x, pos[i].y);

	}
}

DarkpetMissile::DarkpetMissile()
{
}

DarkpetMissile::~DarkpetMissile()
{
}

HRESULT LugiaMissile::Init()
{
	size = 21;
	angle = PI / 2.0f;
	speed = 400.0f;
	isFire = false;
	onHit = false;

	/*ImageManager::GetSingleton()->AddImage("EnemyMissile", "Image/bullet.bmp", size, size, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("EnemyMissile");*/

	ImageManager::GetSingleton()->AddImage("LugiaBullet", "Image/LugiaBullet.bmp", size, size, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("LugiaBullet");

	degree = 18;
	missileCount = 0;
	currMissile = 1;

	return S_OK;
}

void LugiaMissile::Update()
{
	if (isFire)
	{
		if (ChangeMi)
		{
			for (int i = 0; i < 5; i++)
			{
				pos[i].x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
				pos[i].y -= speed * sinf(DEGREE_TO_RADIAN(270)) * TimeManager::GetSingleton()->GetDeltaTime();
				
				if (count % 2 == 0)
				{
					if (i > 0)
					{
						pos[i].x = i * 150 - 95;
						pos[i].y -= (speed - 300) * sinf(DEGREE_TO_RADIAN(270)) * TimeManager::GetSingleton()->GetDeltaTime();
					}
				}
				
				else
				{
					if (i > 0)
					{
						pos[i].x = i * 150-20;
						pos[i].y -= (speed-300) * sinf(DEGREE_TO_RADIAN(270)) * TimeManager::GetSingleton()->GetDeltaTime();
					}
				}

			}
			
		}
		else
		{
			for (int i = 0; i < 1; i++)
			{
				pos[i].x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
				pos[i].y -= speed * sinf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
			}
		}

	}

	else
	{
		missileCount = 0;
	}
}

void LugiaMissile::Render(HDC hdc)
{
	if (isFire)
	{
		
		if (ChangeMi)
		{
			for (int i = 0; i < 5; i++)
			{
				img->Render(hdc, pos[i].x, pos[i].y);
			}
		}

		else
		{
			for (int i = 0; i < 1; i++)
			{
				img->Render(hdc, pos[i].x, pos[i].y);
			}
		}

	}
}

LugiaMissile::LugiaMissile()
{
}

LugiaMissile::~LugiaMissile()
{
}

HRESULT HoOhMissile::Init()
{
	size = 21;
	angle = PI / 2.0f;
	speed = 400.0f;
	isFire = false;
	onHit = false;

	ImageManager::GetSingleton()->AddImage("HoOhMissile", "Image/HoOhBullet.bmp", 24, 24, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("HoOhMissile");

	degree = 18;
	missileCount = 0;
	currMissile = 1;

	return S_OK;
}

void HoOhMissile::Update()
{
	if (isFire)
	{
		if (ChangeMi)
		{
			for (int i = 0; i < 20; i++)
			{
				if (i < 10)
				{
					pos[i].x += speed * cosf(angle + (i * DEGREE_TO_RADIAN(degree))) * TimeManager::GetSingleton()->GetDeltaTime();
					pos[i].y -= speed * sinf(angle + (i * DEGREE_TO_RADIAN(degree))) * TimeManager::GetSingleton()->GetDeltaTime();
				}

				else
				{
					pos[i].x += speed * cosf(angle - (i * DEGREE_TO_RADIAN(degree))) * TimeManager::GetSingleton()->GetDeltaTime();
					pos[i].y -= speed * sinf(angle - (i * DEGREE_TO_RADIAN(degree))) * TimeManager::GetSingleton()->GetDeltaTime();
				}
			}
		}
		else
		{
			speed = 200;

			for (int i = 0; i < 21; i++)
			{
				if (i < 7)
				{
					pos[i].x += (speed)* cosf(DEGREE_TO_RADIAN(degree - 70 + (i * 10))) * TimeManager::GetSingleton()->GetDeltaTime();
					pos[i].y -= speed * sinf(DEGREE_TO_RADIAN(280)) * TimeManager::GetSingleton()->GetDeltaTime();
				}
				else if (i < 14)
				{
					pos[i].x += (speed)* cosf(DEGREE_TO_RADIAN(degree - 105 + ((i - 7) * 6))) * TimeManager::GetSingleton()->GetDeltaTime();
					pos[i].y -= speed * sinf(DEGREE_TO_RADIAN(240)) * TimeManager::GetSingleton()->GetDeltaTime();
				}
				else
				{
					pos[i].x += (speed)* cosf(DEGREE_TO_RADIAN(degree - 120 + ((i - 14) * 4))) * TimeManager::GetSingleton()->GetDeltaTime();
					pos[i].y -= speed * sinf(DEGREE_TO_RADIAN(230)) * TimeManager::GetSingleton()->GetDeltaTime();
				}
				/*	else
					{
						pos[i].x += (speed ) * cosf(DEGREE_TO_RADIAN(degree - 130 + ((i-21) *3))) * TimeManager::GetSingleton()->GetDeltaTime() ;
						pos[i].y -= speed * sinf(DEGREE_TO_RADIAN(225)) * TimeManager::GetSingleton()->GetDeltaTime();
					}*/

			}
		}

	}

	else
	{
		missileCount = 0;
		currMissile = 1;
	}
}

void HoOhMissile::Render(HDC hdc)
{
	if (isFire)
	{
		missileCount++;
		if (ChangeMi)
		{
			if (missileCount % 4 == 3)
			{
				missileCount = 0;
				currMissile++;

				if (currMissile > 20)
				{
					currMissile = 20;
				}

			}
		}
		else
		{
			missileCount = 0;
			currMissile++;

			if (currMissile > 21)
			{
				currMissile = 21;
			}
		}

		for (int i = 0; i < currMissile; i++)
		{
			img->Render(hdc, pos[i].x, pos[i].y);
		}

	}
}

HoOhMissile::HoOhMissile()
{
}

HoOhMissile::~HoOhMissile()
{
}

HRESULT FireBirdMissile::Init()
{
	size = 21;
	angle = PI / 2.0f;
	speed = 400.0f;
	isFire = false;
	onHit = false;

	ImageManager::GetSingleton()->AddImage("fireMissile", "Image/FireBirdBullet.bmp",0,0, 215, 24,9 ,1 , true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("fireMissile");

	degree = 18;
	missileCount = 0;
	currMissile = 1;
	currframex = 8;
	currframey = 0;
	currTime = 0;

	return S_OK;
}

void FireBirdMissile::Update()
{
	if (isFire)
	{
		if (ChangeMi)
			for (int i = 0; i < 20; i++)
			{

				pos[i].x += speed * cosf(angle + (i * DEGREE_TO_RADIAN(degree))) * TimeManager::GetSingleton()->GetDeltaTime();
				pos[i].y -= speed * sinf(angle + (i * DEGREE_TO_RADIAN(degree))) * TimeManager::GetSingleton()->GetDeltaTime();
			}

		else
		{
			for (int i = 0; i < 20; i++)
			{
				if (i < 5 || (i >= 10 && i < 15))
				{
					pos[i].x += speed * cosf((angle * 10) + (i * DEGREE_TO_RADIAN(degree)) + 190) * TimeManager::GetSingleton()->GetDeltaTime();
					pos[i].y -= speed * sinf((angle * 10) + (i * DEGREE_TO_RADIAN(degree)) + 190) * TimeManager::GetSingleton()->GetDeltaTime();
				}

				else
				{
					pos[i].x += speed * cosf((angle * 10) + i * DEGREE_TO_RADIAN(degree)) * TimeManager::GetSingleton()->GetDeltaTime();
					pos[i].y -= speed * sinf((angle * 10) + i * DEGREE_TO_RADIAN(degree)) * TimeManager::GetSingleton()->GetDeltaTime();
				}

			}
		}
	}
	
	currTime++;
	if (currTime % 10 == 9)
	{
		currTime = 0;

		currframex--;
		if (currframex < 0)
		{
			currframex = 0;
		}
	}
}

void FireBirdMissile::Render(HDC hdc)
{
	if (isFire)
	{
		missileCount++;

		if (missileCount % 3 == 2)
		{
			missileCount = 0;
			currMissile++;

			if (currMissile > 20)
			{
				currMissile = 20;
				missileCount = 0;
			}
		}

		else
		{
			missileCount = 0;
			currMissile++;

			if (currMissile > 20)
			{
				currMissile = 20;
			}
		}


		for (int i = 0; i < currMissile; i++)
		{
			img->AlphaRender(hdc, pos[i].x, pos[i].y, currframex, currframey, 255, 1.5f);
		}

	}


}

FireBirdMissile::FireBirdMissile()
{
}

FireBirdMissile::~FireBirdMissile()
{
}

HRESULT PhantomMissile::Init()
{
	for (int i = 0; i < 4; i++)
	{
		pos[i].x = -50;
		pos[i].y = -50;
	}
	size = 21;
	angle = PI / 2.0f;
	speed = 400.0f;
	isFire = false;
	onHit = false;

	ImageManager::GetSingleton()->AddImage("EnemyMissile", "Image/bullet.bmp", size, size, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("EnemyMissile");

	degree = 18;
	missileCount = 0;
	currMissile = 1;

	return S_OK;
}

void PhantomMissile::Update()
{
	float tempdegree;
	if (isFire)
	{
		for (int i = 0; i < 4; i++)
		{
			tempdegree = 270 - 45 + 90 * i;
			pos[i].x += speed * cosf(DEGREE_TO_RADIAN(tempdegree))* TimeManager::GetSingleton()->GetDeltaTime();
			pos[i].y -= speed * sinf(DEGREE_TO_RADIAN(tempdegree))* TimeManager::GetSingleton()->GetDeltaTime();
		}

	}
	
}

void PhantomMissile::Render(HDC hdc)
{
	for (int i = 0; i < 4; i++)
	{
		img->Render(hdc, pos[i].x, pos[i].y);

	}
}

PhantomMissile::PhantomMissile()
{
}

PhantomMissile::~PhantomMissile()
{
}
