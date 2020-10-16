#include "UIManager.h"
#include "macroFunction.h"
#include "pch.h"
#include "SieKensou.h"
#include "Character.h"

HRESULT UIManager::Init()
{	
	//폰트추가
	AddFontResource("Font/DungGeunMo.ttf");
	player1ui.gageposX=220;
	player1ui.gageposY=50;
	player2ui.gageposX=WINSIZE_X-630;
	player2ui.gageposY=50;
	player1ui.damage = 0;
	player2ui.damage = 0;
	player1ui.insdamage = 0;
	player2ui.insdamage = 0;
	gageWidth=400;
	gageHeight=50;

	comtime = 0;
	timer = 50;

	mciOpenParam_pkSound.lpstrElementName = "Sound/pkSound.wav";
	mciOpenParam_pkSound.lpstrDeviceType = "waveaudio";

	fightSound = false;
	koSound = false;
	
	return S_OK;
}

void UIManager::Release()
{	

	//폰트추가
	RemoveFontResource("Font/DungGeunMo.ttf");
}

void UIManager::Update()
{
	player1ui.damage = player1->GetCharInfo().Damage;
	player2ui.damage = player2->GetCharInfo().Damage;

	if (!fightSound)
	{
		PlaySoundA("Sound/fight.wav", NULL, SND_ASYNC);
		fightSound = true;
	}

	if (fightSound)
	{
		if (!koSound)
		{
			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpenParam_pkSound);
			//wDeviceID_pkSound = mciOpenParam_pkSound.wDeviceID;
			mciSendCommand(wDeviceID_pkSound, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParam_pkSound);
		}
	}
	
	comtime++;
	if (comtime == 99)
	{
		comtime = 0;
		if (gameOver)
		{
			timer = timer;

			if (!koSound)
			{
				mciSendCommand(wDeviceID_pkSound, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
				PlaySoundA("Sound/ko.wav", NULL, SND_ASYNC);
				koSound = true;
			}

		}
		else
			timer--;
		if (timer < 0)
			timer = 0;

	}

	if(player1->GetCharInfo().insDamage > 30)
	{ 

		if (comtime % 10 == 9)
		{
			if (player1->GetCharInfo().insDamage > 0)
				player1->SetPlayerInsDamage(player1->GetCharInfo().insDamage - 6);
			else
				player1->SetPlayerInsDamage(0);
		}
	}
	else
	{
		if (comtime % 10 == 9)
		{

			if (player1->GetCharInfo().insDamage > 0)
				player1->SetPlayerInsDamage(player1->GetCharInfo().insDamage - 2);
			else
				player1->SetPlayerInsDamage(0);
		}
	}

	if (player2->GetCharInfo().insDamage > 30)
	{

		if (comtime % 10 == 9)
		{
			if (player2->GetCharInfo().insDamage > 0)
				player2->SetPlayerInsDamage(player2->GetCharInfo().insDamage - 6);
			else
				player2->SetPlayerInsDamage(0);
		}
	}
	else
	{
		if (comtime % 10 == 9)
		{

			if (player2->GetCharInfo().insDamage > 0)
				player2->SetPlayerInsDamage(player2->GetCharInfo().insDamage - 2);
			else
				player2->SetPlayerInsDamage(0);
		}
	}

	player2ui.insdamage = player2->GetCharInfo().insDamage;
	player1ui.insdamage = player1->GetCharInfo().insDamage;

	if (player1ui.damage >= 400)
	{
		player1ui.damage = 400;
		player1ui.insdamage = 0;
	}
		
	if (player2ui.damage >= 400)
		
	{
		player2ui.damage = 400;
		player2ui.insdamage = 0;
	}

	gameOver = this->CheckGameOver();
	
}

void UIManager::Render(HDC hdc)
{

	//투명게이지
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, player1ui.gageposX, player1ui.gageposY, player1ui.gageposX + gageWidth, player1ui.gageposY + gageHeight);
	Rectangle(hdc, player2ui.gageposX, player2ui.gageposY, player2ui.gageposX + gageWidth, player2ui.gageposY + gageHeight);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);

	//초록색게이지
	hBrush = CreateSolidBrush(RGB(0,255,64));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, player1ui.gageposX, player1ui.gageposY, player1ui.gageposX + gageWidth-player1ui.damage, player1ui.gageposY + gageHeight);
	Rectangle(hdc, player2ui.gageposX + player2ui.damage, player2ui.gageposY, player2ui.gageposX + gageWidth , player2ui.gageposY + gageHeight);
	//Rectangle(hdc, player2ui.gageposX, player2ui.gageposY, player2ui.gageposX + gageWidth- player2ui.damage, player2ui.gageposY + gageHeight);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);


	//피 달때 게이지
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, player1ui.gageposX + gageWidth - player1ui.damage, player1ui.gageposY ,
		player1ui.gageposX + gageWidth - player1ui.damage+player1ui.insdamage, player1ui.gageposY + gageHeight);
	Rectangle(hdc, player2ui.gageposX + player2ui.damage, player2ui.gageposY,
		player2ui.gageposX + player2ui.damage - player2ui.insdamage, player2ui.gageposY + gageHeight);
	// player2ui.gageposX + gageWidth - player2ui.damage
	/*Rectangle(hdc, player2ui.gageposX + gageWidth - player2ui.damage, player2ui.gageposY,
		player2ui.gageposX + gageWidth - player2ui.damage+ player2ui.insdamage, player2ui.gageposY + gageHeight);*/
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);

	this->PrintText(hdc);

	
}

void UIManager::PrintText(HDC hdc)
{
	FONT text;
	
	//글꼴설정
	strcpy_s(text.lfFaceName, "둥근모꼴");
	text.lfHeight = 80;
	hFont = CreateFontIndirect((LOGFONTA*)&text);
	hOldFont = (HFONT)SelectObject(hdc, hFont);

	if (timer > 9)
	{
		wsprintf(sZtext, "%d", timer);
	}
	
	else
	{
		wsprintf(sZtext, "0%d", timer);
	}
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkMode(hdc, TRANSPARENT);
	for (int i=0; i < 5; i++)
	{
		for (int j=0; j < 5; j++)
		{
			TextOut(hdc, WINSIZE_X / 2 - 50 - i, 35 - j, sZtext, strlen(sZtext));
			TextOut(hdc, WINSIZE_X / 2 - 50 + i, 35 + j, sZtext, strlen(sZtext));
		}
	}
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, WINSIZE_X / 2 - 50, 35, sZtext, strlen(sZtext));
	
	
	if (gameOver&&timer == 0)
	{
		wsprintf(sZtext, "TIME OVER");
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				TextOut(hdc, WINSIZE_X / 2 - 200 - i, WINSIZE_Y / 2 - 50 - j, sZtext, strlen(sZtext));
				TextOut(hdc, WINSIZE_X / 2 - 200 + i, WINSIZE_Y / 2 - 50 + j, sZtext, strlen(sZtext));
			}
		}

		SetTextColor(hdc, RGB(128, 0, 255));
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 50, sZtext, strlen(sZtext));

		if (player1->GetCharInfo().Damage < player2->GetCharInfo().Damage)
		{
			wsprintf(sZtext, "PLAYER1 WIN");
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkMode(hdc, TRANSPARENT);
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					TextOut(hdc, WINSIZE_X / 2 - 230 - i, WINSIZE_Y / 2 + 50 - j, sZtext, strlen(sZtext));
					TextOut(hdc, WINSIZE_X / 2 - 230 + i, WINSIZE_Y / 2 + 50 + j, sZtext, strlen(sZtext));
				}
			}

			SetTextColor(hdc, RGB(128, 0, 255));
			SetBkMode(hdc, TRANSPARENT);
			TextOut(hdc, WINSIZE_X / 2 - 230, WINSIZE_Y / 2 +50, sZtext, strlen(sZtext));
			player2->SetGameOver(true);
			player1->SetGameOver(true);
			player1->SetIsWin(true);
		}

		else if (player1->GetCharInfo().Damage > player2->GetCharInfo().Damage)
		{
			
			wsprintf(sZtext, "PLAYER2 WIN");
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkMode(hdc, TRANSPARENT);
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					TextOut(hdc, WINSIZE_X / 2 - 230 - i, WINSIZE_Y / 2 + 50 - j, sZtext, strlen(sZtext));
					TextOut(hdc, WINSIZE_X / 2 - 230 + i, WINSIZE_Y / 2 + 50 + j, sZtext, strlen(sZtext));
				}
			}

			SetTextColor(hdc, RGB(128, 0, 255));
			SetBkMode(hdc, TRANSPARENT);
			TextOut(hdc, WINSIZE_X / 2 - 230, WINSIZE_Y / 2 + 50, sZtext, strlen(sZtext));
			player1->SetGameOver(true);
			player2->SetGameOver(true);
			player2->SetIsWin(true);
		}

		else if (player1->GetCharInfo().Damage == player2->GetCharInfo().Damage)
		{
			wsprintf(sZtext, "DRAW");
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkMode(hdc, TRANSPARENT);
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					TextOut(hdc, WINSIZE_X / 2 - 102 - i, WINSIZE_Y / 2 + 50 - j, sZtext, strlen(sZtext));
					TextOut(hdc, WINSIZE_X / 2 - 102 + i, WINSIZE_Y / 2 + 50 + j, sZtext, strlen(sZtext));
				}
			}

			SetTextColor(hdc, RGB(128, 0, 255));
			SetBkMode(hdc, TRANSPARENT);
			TextOut(hdc, WINSIZE_X / 2 - 102, WINSIZE_Y / 2 + 50, sZtext, strlen(sZtext));

			player1->SetGameOver(true);
			player2->SetGameOver(true);
		}
	}
	
	else if (gameOver)
	{
		wsprintf(sZtext, "K     O");
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				TextOut(hdc, WINSIZE_X / 2 - 150 - i, WINSIZE_Y / 2 - 50 - j, sZtext, strlen(sZtext));
				TextOut(hdc, WINSIZE_X / 2 - 150 + i, WINSIZE_Y / 2 - 50 + j, sZtext, strlen(sZtext));
			}
		}

		SetTextColor(hdc, RGB(0, 0, 255));
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, WINSIZE_X / 2 - 150, WINSIZE_Y / 2 - 50, sZtext, strlen(sZtext));
	}
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
	
	
	/*hFont = CreateFontIndirect((LOGFONTA*)&text);
	hOldFont = (HFONT)SelectObject(hdc, hFont);

	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, WINSIZE_X/2 - 50, 35, sZtext, strlen(sZtext));*/
	
	
		
	
}

bool UIManager::CheckGameOver()
{
	if (player1->GetCharInfo().isDead || player2->GetCharInfo().isDead || timer<=0)
	{
		return true;
	}

	else
	{
		return false;
	}

}

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}
