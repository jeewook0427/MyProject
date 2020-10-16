#include "MainGame.h"
#include "macroFunction.h"
#include "Missile.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "StageManager.h"
#include "Image.h"
#include "Ash.h"
#include "Item.h"


HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	// backBuffer
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimeManager::GetSingleton()->Init();
	SoundManager::GetSingleton()->Init();

	

	
	intro = ImageManager::GetSingleton()->AddImage("intro", "Image/intro.bmp", 0, 0, 23000, 450, 46, 1, true, RGB(255, 0, 255));
	gameover = ImageManager::GetSingleton()->AddImage("gameover", "Image/gameover.bmp", 600, 100, true, RGB(255, 0, 255));
	ash = new Ash();


	// 利
	enemyMgr = new EnemyManager();
	enemyMgr->SetAsh(ash);
	enemyMgr->Init(); //扁夯利栏肺 10付府 积己
	stageMgr= new StageManager();
	stageMgr->SetEnemyMrg(enemyMgr);
	stageMgr->Init();
	ash->SetUIManager(stageMgr->GetUIManager());
	ash->Init();
	stageMgr->SetPlayer(ash);

	ImageManager::GetSingleton()->AddImage("BG", "Image/background.bmp", WINSIZE_X, WINSIZE_Y);
	bg = ImageManager::GetSingleton()->FindImage("BG");


	SoundManager::GetSingleton()->AddSound("BGM", "Sound/BGM.mp3", true, true);
	SoundManager::GetSingleton()->AddSound("BULLET", "Sound/bullet.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("EXPLOSION", "Sound/Explosion_effect.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("EAT", "Sound/EAT.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("GatchaSound", "Sound/Gatcha.mp3", false, false);	
	SoundManager::GetSingleton()->AddSound("HoOhDIE", "Sound/Laser_Gun.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("Intro", "Sound/Intro.mp3", true, true);
	SoundManager::GetSingleton()->AddSound("Boss", "Sound/BossBattle.mp3", true, true);
	bgcount = 1;


	isInit = true;

	return S_OK;
}

void MainGame::Release()
{
	ash->Release();
	delete ash;

	
	enemyMgr->Release();
	SAFE_DELETE(enemyMgr);
	stageMgr->Release();
	SAFE_DELETE(stageMgr);
	

	SoundManager::GetSingleton()->Release();

	TimeManager::GetSingleton()->Release();
	TimeManager::GetSingleton()->ReleaseSingleton();

	ImageManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->ReleaseSingleton();
	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();


	backBuffer->Release();
	delete backBuffer;

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SoundManager::GetSingleton()->Update();

	if (isStart)
	{
		if (enemyMgr)
		{
			enemyMgr->Update();
		}

		if (ash)
		{
			ash->Update();
		}

		if (stageMgr)
		{
			stageMgr->Update();
			
		}
		
		

		if (bgcount == 0)
		{
			SoundManager::GetSingleton()->Stop("Boss");
			SoundManager::GetSingleton()->Stop("Intro");
			SoundManager::GetSingleton()->Play("BGM", 0.8f);
			bgcount++;
		}
		if (bgcount == 1)
		{
			if (stageMgr->GetBgCount() == 2)
				bgcount = 2;
		}
		if (bgcount == 2)
		{
			SoundManager::GetSingleton()->Stop("BGM");
			SoundManager::GetSingleton()->Play("Boss", 0.8f);
			bgcount++;
		}
		if (bgcount == 3)
		{
			if (stageMgr->GetBgCount() == 0)
				bgcount = 0;
		}

	}
	else
	{
		if (intro)
		{
			introTime += TimeManager::GetSingleton()->GetDeltaTime();
			if (introTime > 0.15)
			{
				if (introFramX == 0 ||
					introFramX == 10 ||
					introFramX == 22 ||
					introFramX == 33 ||
					introFramX == 45)
				{
					if (introTime > 0.3)
					{
						introFramX++;
						introTime = 0;
					}
				}
				else
				{
					if (introFramX >= 45)
					{
						introFramX = 0;
					}
					else introFramX++;

					introTime = 0;
				}
			}
			if (bgcount == 1)
			{
				SoundManager::GetSingleton()->Play("Intro", 0.8f);
				bgcount = 0;
			}
			if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_SPACE))
			{
				isStart = true;
			
			}
		}
	}


	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	if (isStart)

	{
		if (stageMgr)
		{
			stageMgr->Render(backBuffer->GetMemDC());
		}
		if (enemyMgr)
		{
			enemyMgr->Render(backBuffer->GetMemDC());
		}

		if (ash)
		{
			if (ash->GetGameOver())
				gameover->Render(backBuffer->GetMemDC(), 300, 300);

			ash->Render(backBuffer->GetMemDC());
		}

	}
	else
	{
		if (intro)
		{
			intro->FrameRender(backBuffer->GetMemDC(), 250, 350, introFramX, 0, 1.2f);
		}

	}



	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		if (isInit)
			this->Update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		//if (isInit)
		//	this->Render(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			//tank->Fire();
			break;
		case VK_LEFT:
			//tank->SetBarrelAngle(tank->GetBarrelAngle() + (PI / 180 * 1));
			break;
		case VK_RIGHT:
			//tank->SetBarrelAngle(tank->GetBarrelAngle() - (PI / 180 * 1));
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}


//bool MainGame::CheckCollision(Missile * m1, Missile * m2)
//{
//	float halfSize1 = m1->GetSize() / 2;
//	float halfSize2 = m2->GetSize() / 2;
//	FPOINT pos1 = m1->GetPos();
//	FPOINT pos2 = m2->GetPos();
//
//	if ((halfSize1 + halfSize2) >=
//		GetDistance(pos1.x, pos1.y, pos2.x, pos2.y))
//	{
//		return true;
//	}
//
//	return false;
//}

MainGame::MainGame()
	: isInit(false)
{
}


MainGame::~MainGame()
{
}
