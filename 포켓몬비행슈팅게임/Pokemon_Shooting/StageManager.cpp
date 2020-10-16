#include "StageManager.h"
#include "Stage.h"
#include "EnemyManager.h"
#include "UIManager.h"
#include "Image.h"
#include "Ash.h"
HRESULT StageManager::Init()
{
	
	ReadFileInt("stageinfo.txt");
	currStageNum = 0;
	vecStage.resize(maxStageNum+1); // vecMissiles.size() resize할 때만 가능.
	hpBar = new UIManager();
	hpBar->Init();
	for (int i = 0; i < vecStage.size(); i++)
	{
		vecStage[i] = new Stage();
		if(i==0) vecStage[i]->Init(stageFileName[i],true); 
		else vecStage[i]->Init(stageFileName[i], false);
		vecStage[i]->SetEnemyWaveSet(enemyWaveSet1[i], enemyWaveSet2[i], enemyWaveSet3[i], enemyWaveSet4[i], enemyWaveSet5[i],
			enemyWaveSet6[i], enemyWaveSet7[i], enemyWaveSet8[i], enemyWaveSet9[i], enemyWaveSet10[i]);
		vecStage[i]->SetEnemyMrg(enemyMrg);
		vecStage[i]->SetHpBar(hpBar);
	}
	gotcha = ImageManager::GetSingleton()->AddImage("gotcha", "Image/gotcha.bmp", 0, 0, 600, 840, 1, 1, true, RGB(255, 0, 255));
	//gotchaball = ImageManager::GetSingleton()->AddImage("gotchaball", "Image/gotchaball.bmp", 0, 0, 16, 52, 1, 3, true, RGB(255, 0, 255));
	ending = ImageManager::GetSingleton()->AddImage("ending", "Image/ending.bmp", 0, 0, 600, 900, 1, 1, true, RGB(255, 0, 255));
	gatchaAlpha = 0;
	endingY = 0;
	gotchaballY = 0;
	lifeIcon = ImageManager::GetSingleton()->AddImage("ash_life", "Image/ash_life.bmp", 0, 0, 40, 34, 1, 1, true, RGB(255, 0, 255));

	return S_OK;
}

void StageManager::Release()
{
	for (auto& it : vecStage)
	{
		it->Release();
		SAFE_DELETE(it);
	}

	for (int i = 0; i < maxStageNum + 1; ++i)
	{
		SAFE_DELETE(enemyWaveSet1[i]);
		SAFE_DELETE(enemyWaveSet2[i]);
		SAFE_DELETE(enemyWaveSet3[i]);
		SAFE_DELETE(enemyWaveSet4[i]);
		SAFE_DELETE(enemyWaveSet5[i]);
		SAFE_DELETE(enemyWaveSet6[i]);
		SAFE_DELETE(enemyWaveSet7[i]);
		SAFE_DELETE(enemyWaveSet8[i]);
		SAFE_DELETE(enemyWaveSet9[i]);
		SAFE_DELETE(enemyWaveSet10[i]);


	}
	SAFE_ARR_DELETE(enemyWaveSet1);
	SAFE_ARR_DELETE(enemyWaveSet2);
	SAFE_ARR_DELETE(enemyWaveSet3);
	SAFE_ARR_DELETE(enemyWaveSet4);
	SAFE_ARR_DELETE(enemyWaveSet5);
	SAFE_ARR_DELETE(enemyWaveSet6);
	SAFE_ARR_DELETE(enemyWaveSet7);
	SAFE_ARR_DELETE(enemyWaveSet8);
	SAFE_ARR_DELETE(enemyWaveSet9);
	SAFE_ARR_DELETE(enemyWaveSet10);



	SAFE_ARR_DELETE(stageFileName);

	vecStage.clear();
}

void StageManager::Update()
{
	vecStage[currStageNum]->SetPlayer(player);
	for (auto& it : vecStage)
	{
		it->Update();
	}
	
	if (KeyManager::GetSingleton()->IsOnceKeyDown('N') || vecStage[currStageNum]->GetIsClear())
	{

		gotchaTime += TimeManager::GetSingleton()->GetDeltaTime();
		scoreTime += TimeManager::GetSingleton()->GetDeltaTime();

		if (gotchaTime > 5.0f)
		{
			enemyMrg->Init();
			vecStage[currStageNum]->SetIsCurrStage(false);

			if (currStageNum < maxStageNum)
			{
				currStageNum++;
				caculScore = false;
			}
			else
			{
				isEnding = true;
				if (endingY < 900)
					endingY += 2;
				player->SetisEnding(true);
			}

			if (currStageNum <= maxStageNum)
			{
				hpBar->SetScore(hpBar->GetSocre() + clearScore);
				vecStage[currStageNum]->SetIsCurrStage(true);
				clearScore = 0;

			}


			if (!isEnding)
			{
				scoreTime = 0;
				gotchaTime = 0;
			}

		}
	}
	else
	{
		if (caculScore)
		{

			caculScore = false;
		}

		//hpBar->SetScore
	}



	if (!isEnding)
	{
		bgCount = vecStage[currStageNum]->GetBgCount();
	}
	else bgCount = 0;
	
}

void StageManager::Render(HDC hdc)
{

	for (auto& it : vecStage)
	{
		it->Render(hdc);
	}

	if (vecStage[currStageNum]->GetIsClear() && gotchaTime >= 1.5f&&
		vecStage[currStageNum]->GetIsClear() && gotchaTime <= 5.0f)
	{

		if (gotcha)
		{
			
			gatchaAlpha += 5;
			gotcha->AlphaRender(hdc, 300, 410, 0, 0, gatchaAlpha, 0.5f);
			lifeIcon->Render(hdc, 224, 630);
			
			if (gotchaTime <= 4.7f && scoreTime >= 0.01f)
			{
				if (clearScore < player->GetLife() * 1000) clearScore += 20;
				else clearScore = player->GetLife() * 1000;
			
				scoreTime = 0;
			}
			if(gotchaTime>4.7f) clearScore = player->GetLife() * 1000;
			
			hpBar->PrintClearScore(hdc, player->GetLife(), hpBar->GetSocre() + clearScore);



		}
	}
	if (isEnding)
	{
		ending->BgRender(hdc, 0, endingY, false);
		if (endingY >= 900)
			hpBar->PrintClearScore(hdc, player->GetLife(), hpBar->GetSocre() + clearScore, true);
	}

}

void StageManager::ReadFileInt(string fileName)
{
	ifstream fin;

	fin.open(fileName);


	fin >> maxStageNum;
	stageFileName = new string[maxStageNum + 1];

	for (int i = 0; i < maxStageNum + 1; ++i) {
		fin >> stageFileName[i];
	}



	enemyWaveSet1 = new int*[maxStageNum + 1];
	for (int i = 0; i < maxStageNum + 1; ++i) {
		enemyWaveSet1[i] = new int[7];
	}


	enemyWaveSet2 = new int*[maxStageNum + 1];
	for (int i = 0; i < maxStageNum + 1; ++i) {
		enemyWaveSet2[i] = new int[7];
	}

	enemyWaveSet3 = new int*[maxStageNum + 1];
	for (int i = 0; i < maxStageNum + 1; ++i) {
		enemyWaveSet3[i] = new int[7];
	}

	enemyWaveSet4 = new int*[maxStageNum + 1];
	for (int i = 0; i < maxStageNum + 1; ++i) {
		enemyWaveSet4[i] = new int[7];
	}

	enemyWaveSet5 = new int*[maxStageNum + 1];
	for (int i = 0; i < maxStageNum + 1; ++i) {
		enemyWaveSet5[i] = new int[7];
	}
	enemyWaveSet6 = new int*[maxStageNum + 1];
	for (int i = 0; i < maxStageNum + 1; ++i) {
		enemyWaveSet6[i] = new int[7];
	}


	enemyWaveSet7 = new int*[maxStageNum + 1];
	for (int i = 0; i < maxStageNum + 1; ++i) {
		enemyWaveSet7[i] = new int[7];
	}

	enemyWaveSet8 = new int*[maxStageNum + 1];
	for (int i = 0; i < maxStageNum + 1; ++i) {
		enemyWaveSet8[i] = new int[7];
	}

	enemyWaveSet9 = new int*[maxStageNum + 1];
	for (int i = 0; i < maxStageNum + 1; ++i) {
		enemyWaveSet9[i] = new int[7];
	}

	enemyWaveSet10 = new int*[maxStageNum + 1];
	for (int i = 0; i < maxStageNum + 1; ++i) {
		enemyWaveSet10[i] = new int[7];
	}




	for (int i = 0; i < maxStageNum + 1; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			fin >> enemyWaveSet1[i][j];

		}
	}
	for (int i = 0; i < maxStageNum + 1; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			fin >> enemyWaveSet2[i][j];

		}
	}
	for (int i = 0; i < maxStageNum + 1; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			fin >> enemyWaveSet3[i][j];

		}
	}
	for (int i = 0; i < maxStageNum + 1; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			fin >> enemyWaveSet4[i][j];

		}
	}
	for (int i = 0; i < maxStageNum + 1; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			fin >> enemyWaveSet5[i][j];

		}
	}

	for (int i = 0; i < maxStageNum + 1; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			fin >> enemyWaveSet6[i][j];

		}
	}
	for (int i = 0; i < maxStageNum + 1; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			fin >> enemyWaveSet7[i][j];

		}
	}
	for (int i = 0; i < maxStageNum + 1; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			fin >> enemyWaveSet8[i][j];

		}
	}
	for (int i = 0; i < maxStageNum + 1; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			fin >> enemyWaveSet9[i][j];

		}
	}
	for (int i = 0; i < maxStageNum + 1; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			fin >> enemyWaveSet10[i][j];

		}
	}


	fin.close();//오픈 후 반드시 클로즈 해주어야 메모리 누수가 안생김;


}
