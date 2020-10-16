#include "Ending.h"
#include "Image.h"
#include "GameNode.h"

void Ending::Update()
{
	if (PtInRect(&replayBtRc, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			replayBtState = BUTTON_STATE::DOWN;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON) && replayBtState == BUTTON_STATE::DOWN)
		{
			replayBtState = BUTTON_STATE::UP;

			
			SoundManager::GetSingleton()->Stop("stonefurnace");
			SoundManager::GetSingleton()->Stop("playerwalking");
			SoundManager::GetSingleton()->Stop("playermine");
			SoundManager::GetSingleton()->Stop("basictransportbelt");
			SoundManager::GetSingleton()->Stop("steamengine");
			SoundManager::GetSingleton()->Stop("electricminingdrill");
			SoundManager::GetSingleton()->Stop("burnerminingdrill");
			SoundManager::GetSingleton()->Stop("assemblingmachine");
			SoundManager::GetSingleton()->Stop("electricfurnace");
			SoundManager::GetSingleton()->Stop("playerminewood");


			Tutorial::GetSingleton()->ReleaseSingleton();
			ObjectManager::GetSingleton()->Release();
			ObjectManager::GetSingleton()->ReleaseSingleton();

			SceneManager::GetSingleton()->ChangeScene("titleScene");
		}
	}
	else
	{
		replayBtState = BUTTON_STATE::NONE;
	}

	if (PtInRect(&quitBtRc, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			quitBtState = BUTTON_STATE::DOWN;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON) && quitBtState == BUTTON_STATE::DOWN)
		{
			quitBtState = BUTTON_STATE::UP;

			PostQuitMessage(0);
		}
	}
	else
	{
		quitBtState = BUTTON_STATE::NONE;
	}
}

void Ending::Render(HDC hdc)
{
	if (isRender)
	{
		map<Layer, map<TILE_POINT, GameNode*> >::iterator iter;
		int num = 0;

		greenBox->AlphaRender(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, 100);
		isRender = false;

		endingMenu->AlphaRender(hdc, 600, 98, 400, 700, 200);
		sprintf_s(strText, "플레이 시간 :  %d 분 %d 초", (int)playTime/60, (int)playTime - (int)playTime/60 * 60);
		TextOut(hdc, 620, 180, strText, strlen(strText));

		sprintf_s(strText, "설비 목록: ");
		TextOut(hdc, 620, 220, strText, strlen(strText));

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(WOODENCHEST);
		map<TILE_POINT, GameNode*>::iterator it;


		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(WOODENCHEST)).size();
		else
			num = 0;
		sprintf_s(strText, "나무 상자: %d", num);
		TextOut(hdc, 640, 250, strText, strlen(strText));

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STEELCHEST);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(STEELCHEST)).size();
		else
			num = 0;
		sprintf_s(strText, "철 상자: %d", num);
		TextOut(hdc, 640, 280, strText, strlen(strText));


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICTRANSPORTBELT);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).size();
		else
			num = 0;
		sprintf_s(strText, "운송 밸트: %d", num);
		TextOut(hdc, 640, 310, strText, strlen(strText));


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICSPLITTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).size() / 2;
		else
			num = 0;
		sprintf_s(strText, "분배기: %d", num);
		TextOut(hdc, 640, 340, strText, strlen(strText));


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BURNERINSERTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERINSERTER)).size();
		else
			num = 0;
		sprintf_s(strText, "화력 투입기: %d", num);
		TextOut(hdc, 640, 370, strText, strlen(strText));

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICINSERTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(BASICINSERTER)).size();
		else
			num = 0;
		sprintf_s(strText, "투입기: %d", num);
		TextOut(hdc, 640, 400, strText, strlen(strText));

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(LONGHANDEDINSERTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(LONGHANDEDINSERTER)).size();
		else
			num = 0;
		sprintf_s(strText, "긴 팔 투입기: %d", num);
		TextOut(hdc, 640, 430, strText, strlen(strText));


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(SMALLELECTRICPOLE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).size();
		else
			num = 0;
		sprintf_s(strText, "소형 전신주: %d", num);
		TextOut(hdc, 640, 460, strText, strlen(strText));

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STEAMENGINE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			int num0 = 0;
			int num1 = 0;
			int num2 = 0;
			int num3 = 0;

			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).begin();
				it != (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).end(); it++)
			{
				if (it->second->GetDirection() == 0)
				{
					++num0;
				}

				else if (it->second->GetDirection() == 1)
				{
					++num1;
				}

				else if (it->second->GetDirection() == 2)
				{
					++num2;
				}

				else if (it->second->GetDirection() == 3)
				{
					++num3;
				}
			}

			num = num0 / 24 + num1 / 24 + num2 / 27 + num3 / 21;
		}
		else
			num = 0;
		sprintf_s(strText, "증기 발전기: %d", num);
		TextOut(hdc, 640, 490, strText, strlen(strText));


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BURNERMININGDRILL);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).size() / 4;
		else
			num = 0;
		sprintf_s(strText, "화력 채광 드릴: %d", num);
		TextOut(hdc, 640, 520, strText, strlen(strText));


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICMININGDRILL);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).size() / 9;
		else
			num = 0;
		sprintf_s(strText, "전기 채광 드릴: %d", num);
		TextOut(hdc, 640, 550, strText, strlen(strText));


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STONEFURNACE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).size() / 4;
		else
			num = 0;
		sprintf_s(strText, "석재 용광로: %d", num);
		TextOut(hdc, 640, 580, strText, strlen(strText));


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ELECTRICFURNACE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).size() / 9;
		else
			num = 0;
		sprintf_s(strText, "전기 용광로: %d", num);
		TextOut(hdc, 640, 610, strText, strlen(strText));


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ASSEMBLINGMACHINE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).size() / 9;
		else
			num = 0;
		sprintf_s(strText, "생산 설비: %d", num);
		TextOut(hdc, 640, 640, strText, strlen(strText));

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ROCKET);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
			num = (*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).size() / 90;
		else
			num = 0;
		sprintf_s(strText, "로켓: %d", num);
		TextOut(hdc, 640, 670, strText, strlen(strText));

	}

	if (replayBtState == BUTTON_STATE::UP)
		replayBtImg->FrameRender(hdc, replayBtRc.left + 50, replayBtRc.top + 25, 0, 1);
	else
		replayBtImg->FrameRender(hdc, replayBtRc.left + 50, replayBtRc.top + 25, 0, 0);

	if (quitBtState == BUTTON_STATE::UP)
		quitBtImg->FrameRender(hdc, quitBtRc.left + 50, quitBtRc.top + 25, 0, 1);
	else
		quitBtImg->FrameRender(hdc, quitBtRc.left + 50, quitBtRc.top + 25, 0, 0);
}

Ending::Ending()
{
	isRender = true;
	greenBox = ImageManager::GetSingleton()->FindImage("greenBox");
	endingMenu = ImageManager::GetSingleton()->FindImage("endingMenu");

	replayBtImg = ImageManager::GetSingleton()->FindImage("replayBt");
	quitBtImg = ImageManager::GetSingleton()->FindImage("quitBt");

	replayBtRc = { 685, 723, 785, 773 };
	quitBtRc = { 815, 723, 915, 773 };
}

Ending::~Ending()
{

}
