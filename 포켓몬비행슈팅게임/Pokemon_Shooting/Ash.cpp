#include "Ash.h"
#include "Image.h"
#include "MissileManager.h"
#include "macroFunction.h"
#include "Item.h"
#include "StageManager.h"

HRESULT Ash::Init()
{
	image = ImageManager::GetSingleton()->AddImage("Ash", "Image/spritesheet_ash.bmp", 0, 0, 210, 273, 3, 3, true, RGB(255, 0, 255));
	effect = ImageManager::GetSingleton()->AddImage("Asheffect", "Image/asheffect.bmp", 0, 0, 30, 36, 1, 1, true, RGB(255, 0, 255));
	pikachu = ImageManager::GetSingleton()->AddImage("Pikachu", "Image/Pikachu.bmp", 0, 0, 96, 30, 3, 1, true, RGB(255, 0, 255));
	pikachueffect = ImageManager::GetSingleton()->AddImage("Pikachueffect", "Image/Electro.bmp", 0, 0, 85, 24, 1, 1, true, RGB(255, 0, 255));
	lifeHead = ImageManager::GetSingleton()->AddImage("ash_life", "Image/ash_life.bmp", 0, 0, 40, 34, 1, 1, true, RGB(255, 0, 255));
	pikachucount = ImageManager::GetSingleton()->AddImage(" PikachuCount", "Image/pikachucount.bmp", 0, 0, 40, 34, 1, 1, true, RGB(255, 0, 255));

	if (image == nullptr)
	{
		return E_FAIL;
	}

	missileMgr.SetIsPlayer(true);
	missileMgr.NewMissile();
	missileMgr.Init();
	missileMgr.SetOwner(this);
	missileMgr.SetUIManager(uimanager);

	angle = 0.0f;
	moveSpeed = 300.0f;
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y + 300;
	degree = 0;
	alpha = 255;
	power = 1;

	currframeX = 0;
	currframeY = 1;
	effframeX = 0;
	effframeY = 0;
	skillframeX = 0;
	skillframeY = 0;
	comtime = 0;
	time = 0;
	isEat = false;
	isHit = false;
	isStart = true;
	checkalpha = false;
	keyLock = true;
	debugMode = false;
	skill = false;
	skillcount = 2;

	scale = 0.5;
	size = 12 * scale;
	isPush = false;
	isReverse = false;
	isEnding = false;
	endY = WINSIZE_Y / 2;
	return S_OK;




}

void Ash::Release()
{

	missileMgr.Release();
	//delete missileMgr;
}

void Ash::Update()
{	
	if (isStart)
	{
		if(pos.y > (WINSIZE_Y - 120))
			pos.y -= moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();
		isHit = false;

		if (pos.y <= (WINSIZE_Y - 120))
		{
			keyLock = false;
			comtime++;

			if (!checkalpha)
			{
				alpha -= 10;
				if (alpha <= 0)
				{
					alpha = 0;
					checkalpha = true;
				}
			}

			else
			{
				alpha += 10;

				if (alpha >= 255)
				{
					alpha = 255;
					checkalpha = false;
				}
			}

			if (comtime % 240 == 239)
			{
				isPush = false;
				isStart = false;
				alpha = 255;
				comtime = 0;
			}

		}


	}
	   	 
	if (isHit)
	{
		isPush = true;
		comtime++;
		if (comtime % 10 == 9)
		{
			alpha -= 20;
			if (alpha < 0)
			{
				alpha = 0;
			}
			effframeX++;
			if (effframeX == 11)
			{
				effframeY++;
				effframeX = 0;

			}

			if (effframeY == 1 && effframeX == 5)
			{
				effframeX = 0;
				effframeY = 0;
				life--;
				
				if (life < 0)
				{
					life = 0;
				}
				if (life == 0)
				{
					gameover = true;
				}
				comtime = 0;

				if (!gameover)
				{
					this->Init();
				}
				
			}
		}
	}

	comtime2++;
	frameTime += TimeManager::GetSingleton()->GetDeltaTime();
	if (frameTime >= 0.2f)
	{
		currframeX++;

		if (currframeX == 2) currframeX = 0;
		frameTime = 0;
	}

	if (!keyLock && !isHit && !gameover && !isEnding)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			pos.x -= moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();
			currframeY = 2;
			if (pos.x < size)
				pos.x = size;

			if (frameTime >= 0.2f)
			{
				currframeX++;
				if (currframeX == 2) currframeX = 0;
				frameTime = 0;
			}

		}

		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
		{
			pos.x += moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();
			if (pos.x > WINSIZE_X - size)
				pos.x = WINSIZE_X - size;
			isReverse = true;
			currframeY = 2;
			if (frameTime >= 0.2f)
			{
				currframeX++;
				if (currframeX == 2) currframeX = 0;
				frameTime = 0;
			}

		}

		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
		{

			pos.y -= moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();
			if (pos.y < size)
				pos.y = 0 + size;
			currframeY = 1;
			if (frameTime >= 0.2f)
			{
				currframeX++;
				if (currframeX == 2) currframeX = 0;
				frameTime = 0;
			}
		}

		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
		{
			pos.y += moveSpeed * TimeManager::GetSingleton()->GetDeltaTime();
			if (pos.y > WINSIZE_Y - size*2)
				pos.y = WINSIZE_Y - size*2;
			currframeY = 0;
			if (frameTime >= 0.2f)
			{
				currframeX++;
				if (currframeX == 2) currframeX = 0;
				frameTime = 0;
			}
		}

		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
		{
			currframeY = 1;
			isReverse = false;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_UP))
		{
			currframeY = 1;


		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT))
		{
			currframeY = 1;
			frameTime = 0;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_DOWN))
		{
			currframeY = 1;
			frameTime = 0;
		}

		else if (KeyManager::GetSingleton()->IsOnceKeyDown(0x4F)) //O
		{
			debugMode = true;
			
		}

		
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(0x58) &&skillcount > 0 && !skill) //X
		{
			skill = true;
			skillcount--;
		}

		else if (KeyManager::GetSingleton()->IsOnceKeyDown('S') ) 
		{
		
			skillcount++;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('L') ) 
		{

			life++;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('P') ) 
		{

			power++;
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown(0x5A) && time == 0)
		{
			missileMgr.Fire();
			SoundManager::GetSingleton()->Play("BULLET", 0.1f);
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown(0x5A) && time == 0)
		{
			missileMgr.Fire();
			SoundManager::GetSingleton()->Play("BULLET", 0.1f);
		}
	}





	float angle;
	angle = 90 - degree;

	missileMgr.SetPower(power);
	missileMgr.Update();
	missileMgr.SetAnlge(DEGREE_TO_RADIAN(angle));


	time++;
	if (time == 10)
	{
		time = 0;
	}



	if (skill)
	{
		comtime++;
		if (comtime % 15 == 14)
		{
			skillframeX++;
			if (skillframeX > 2)
			{
				comtime = 0;
				skillframeX = 0;
				skill = false;
			}
		}
	}

	if (isEnding)
	{

		endY -= 1;
		pos.x = WINSIZE_X / 2;
		pos.y = endY;

		if (pos.y <= 0)
		{
			alpha = 0;
		}
	}
}

void Ash::Render(HDC hdc)
{
	if (image && !isHit)
	{
		//image->Render(hdc, pos.x, pos.y);
		image->AlphaRender(hdc, pos.x, pos.y, currframeX, currframeY, alpha, scale, degree, isReverse);
	}
	if (!isEnding)
	{
		if (isHit)
		{
			effect->AlphaRender(hdc, pos.x, pos.y, 0, 0, alpha, 1.0f, degree, isReverse);
		}

		if (skill)
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					pikachueffect->AlphaRender(hdc, 100 + j * 120, 100 + i * 150, 0, 0, 255, 1, i * 50);
				}

			}
			pikachu->AlphaRender(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, skillframeX, skillframeY, 255, 4.0f);
		}

		missileMgr.Render(hdc);

		for (int i = 1; i <= life; i++)
		{
			lifeHead->Render(hdc, 30 + ((i - 1) * 40), 770);
		}

		for (int i = 1; i <= skillcount; i++)
		{
			pikachucount->Render(hdc, 30 + ((i - 1) * 40), 720);
		}
	}
}

MissileManager * Ash::GetMissileMgr()
{
	return &missileMgr;
}

Ash::Ash()
{
}

Ash::~Ash()
{
}
