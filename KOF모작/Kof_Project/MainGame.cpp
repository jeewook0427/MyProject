#include "MainGame.h"
#include "macroFunction.h"
#include "Image.h"
#include "BackGround.h"
#include "UIManager.h"
#include "BattleManager.h"
#include "Character.h"
#include "SieKensou.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	// backBuffer
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	background = new BackGround();
	background->Init();

	player1 = new Character();
	player1->SetCharacterNum(1);
	
	player1->Init();

	player2 = new Character();
	player2->SetCharacterNum(2);
	
	player2->Init();

	uimanager = new UIManager();
	uimanager->Init();

	battlemanager = new BattleManager();
	battlemanager->Init();

	battlemanager->SetPlayer1(player1);
	battlemanager->SetPlayer2(player2);
	uimanager->SetPlayer1(player1);
	uimanager->SetPlayer2(player2);

	player1select.x = 475-60;
	player1select.y = 300;
	player2select.x = 950-60;
	player2select.y = 370;

	gameProcess = 0;
	KeyInit();
	PlaySoundA("Sound/startSound.wav", NULL, SND_ASYNC);

	mciOpenParam_selectBGM.lpstrElementName = "Sound/selectBGM.wav";
	mciOpenParam_selectBGM.lpstrDeviceType = "waveaudio";
	
	isInit = true;

	return S_OK;
}

void MainGame::Release()

{
	battlemanager->Release();
	delete battlemanager;

	uimanager->Release();
	delete uimanager;
	
	player2->Release();
	delete player2;
	
	player1->Release();
	delete player1;

	background->Release();
	delete background;
	
	KillTimer(g_hWnd, 0);

	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	backBuffer->Release();
	delete backBuffer;
}

void MainGame::Update()
{
	this->KeyInput();
	
	if (background)
	{
		background->Update();
	}

	
	if (gameProcess == 1)
	{
		this->CheckSelect();
	}
		
	
	if (gameProcess == 2)
	{
		if (battlemanager)
		{
			battlemanager->Update();
		}
		
		if (player1)
		{
			player1->Update();
		}

		if (player2)
		{
			player2->Update();
		}

		if (player1->GetCharInfo().gameStart && player2->GetCharInfo().gameStart)
		{
			if (uimanager)
			{
				uimanager->Update();
			}
		}
		
	}
	

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	if (background)
	{
		background->Render(backBuffer->GetMemDC());
	}

	if (gameProcess == 2)
	{
		if (player1)
		{
			player1->Render(backBuffer->GetMemDC());
		}

		if (player2)
		{
			player2->Render(backBuffer->GetMemDC());
		}

		if (player1->GetCharInfo().gameStart && player2->GetCharInfo().gameStart)
		{
			if(uimanager)
				uimanager->Render(backBuffer->GetMemDC());
		}
		
	}
	
	
	/*if (player1->GetSieKensou())
	{
		player1->GetSieKensou()->Render(backBuffer->GetMemDC());
	}
	
	if (player2->GetAthena())
	{
		player2->GetAthena()->Render(backBuffer->GetMemDC());
	}*/
	
	this->TextPrint(backBuffer->GetMemDC());
	
	
	
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

		if (isInit)
			this->Render(hdc);

		/*if (player1)
		{
			wsprintf(sZtext, "player1  : %d", player1->GetSieKensou()->GetDamage());
			TextOut(hdc, 50, 200, sZtext, strlen(sZtext));
			wsprintf(sZtext, "player2  : %d", player2->GetSieKensou()->GetDamage());
			TextOut(hdc, 50, 400, sZtext, strlen(sZtext));
		}*/
		
	

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

		//if (CheckRectCollision(rc[BOX_First], rc[BOX_Second]))
		//{
		//	currentBox = (BOX)((currentBox + 1) % BOX_End);

		//	int setX = rc[currentBox].left + (150 / 2) - (50 / 2);
		//	int setY = rc[currentBox].top + 50;
		//	rcIn = GetRect(setX, setY, 50);
		//}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

float MainGame::GetAngle(float x1, float y1, float x2, float y2)
{
	return atan2((y2 - y1), (x2 - x1));
}

float MainGame::GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float dist = sqrtf((x * x) + (y * y));

	return dist;
}

void MainGame::KeyInput()
{
	if (gameProcess == 0)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
			PlaySoundA(0, 0, 0); // 게임시작시 나온 BGM 종료

			// Select창 BGM
			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpenParam_selectBGM);
			wDeviceID_selectBGM = mciOpenParam_selectBGM.wDeviceID;
			mciSendCommand(wDeviceID_selectBGM, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParam_selectBGM);

			gameProcess = 1;
			background->SetGameProcess(1);
		}
	}
		

	if (gameProcess == 1)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(key.player1left) && !isPlayer1Select)
		{
			player1select.x -= 475;
			if (player1select.x < 475 - 60)
			{
				player1select.x = 475 - 60;
			}

		}

		else if (KeyManager::GetSingleton()->IsOnceKeyDown(key.player1right) && !isPlayer1Select)
		{
			player1select.x += 475;
			if (player1select.x > 1425 - 60)
			{
				player1select.x = 1425 - 60;
			}
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown(key.player2left) && !isPlayer2Select)
		{
			player2select.x -= 475;
			if (player2select.x < 475 - 60)
			{
				player2select.x = 475 - 60;
			}
		}

		else if (KeyManager::GetSingleton()->IsOnceKeyDown(key.player2right) && !isPlayer2Select)
		{
			player2select.x += 475;
			if (player2select.x > 1425 - 60)
			{
				player2select.x = 1425 - 60;
			}
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown(key.player1select))
		{
			isPlayer1Select = true;
			PlaySoundA("Sound/selectComplete.wav", NULL, SND_ASYNC);
			if (player1select.x == 475 - 60)
			{
				player1->SetSelectNum(1);
				player1->SetPlayerNum(1);
			}

			if (player1select.x == 475 * 2 - 60)
			{
				player1->SetSelectNum(2);
				player1->SetPlayerNum(1);
			}


			if (player1select.x == 475 * 3 - 60)
			{
				player1->SetSelectNum(3);
				player1->SetPlayerNum(1);
			}
		}

		else if (KeyManager::GetSingleton()->IsOnceKeyDown(key.player2select))
		{
			isPlayer2Select = true;
			PlaySoundA("Sound/selectComplete.wav", NULL, SND_ASYNC);
			if (player2select.x == 475 - 60)
			{
				player2->SetSelectNum(1);
				player2->SetPlayerNum(2);
			}

			if (player2select.x == 475 * 2 - 60)
			{
				player2->SetSelectNum(2);
				player2->SetPlayerNum(2);
			}


			if (player2select.x == 475 * 3 - 60)
			{
				player2->SetSelectNum(3);
				player2->SetPlayerNum(2);
			}
		}
	}
	
}

void MainGame::KeyInit()
{
	
	key.player1right = 0x4A; // J
	key.player1left = 0x47; // G
	key.player1select = 0x41; // A
	key.player2right = VK_RIGHT; 
	key.player2left = VK_LEFT; 
	key.player2select = 0XBE; // .

	
}

void MainGame::CheckSelect()
{
	if (isPlayer1Select && isPlayer2Select)
	{
		mciSendCommand(wDeviceID_selectBGM, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		gameProcess = 2;
		background->SetGameProcess(2);
	}
		
}

void MainGame::TextPrint(HDC hdc)
{
	if (gameProcess == 1)
	{
		FONT text;

		//글꼴설정
		strcpy_s(text.lfFaceName, "둥근모꼴");
		text.lfHeight = 60;
		HFONT hFont = CreateFontIndirect((LOGFONTA*)&text);
		HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		wsprintf(sZtext, "P1");
		TextOut(hdc, player1select.x, player1select.y, sZtext, strlen(sZtext));
		SetTextColor(hdc, RGB(0, 0, 255));
		SetBkMode(hdc, TRANSPARENT);
		wsprintf(sZtext, "P2");
		TextOut(hdc, player2select.x, player2select.y, sZtext, strlen(sZtext));

		SelectObject(hdc, hOldFont);
		DeleteObject(hFont);
	}
	
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
