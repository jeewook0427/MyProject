#include "Stage.h"
#include "Image.h"
#include "EnemyManager.h"
#include "UIManager.h"
#include "Ash.h"
HRESULT Stage::Init()
{
	return S_OK;
}

HRESULT Stage::Init(float posX, float posY)
{
	return S_OK;
}

HRESULT Stage::Init(string stageFileName, bool _isCurrStage)
{
	currPosY = 0;
	isCurrStage = _isCurrStage;
	ImageManager::GetSingleton()->AddImage(stageFileName, stageFileName.c_str(), 0, 0, 300, 2550, 1, 1, true, RGB(255, 0, 255));
	image = ImageManager::GetSingleton()->FindImage(stageFileName);
	framrTime = 0;
	enemyTime = 0;
	HP = 500;
	life = 3;
	isclear = false;
	return S_OK;
}

void Stage::Release()
{
	hpBar->Release();
}

void Stage::Update()
{

	if (image)
	{
		if (isCurrStage)
		{
			framrTime += TimeManager::GetSingleton()->GetDeltaTime();
			if (!(player->GetIsPush())) enemyTime += TimeManager::GetSingleton()->GetDeltaTime();
			//맵이동
			if (framrTime >= 0.0f)
			{
				if (currPosY >= 2100)
				{
					currPosY = 0;
				}
				if (isCurrStage) { currPosY++; }
				framrTime = 0;
			}
			for (int k = 0; k < 9; k++)
			{
				// 몬스터 출력 
				if (enemyTime > enemyWaveSet[k][0] && enemyWave == k)
				{

					for (int i = 0; i < enemyWaveSet[k][1]; i++)
					{
						switch (enemyWaveSet[k][2])
						{
						case 1:
							enemyMrg->AddSlowpoke(enemyWaveSet[k][3] + i *enemyWaveSet[k][5], enemyWaveSet[k][4] +i* enemyWaveSet[k][6]);
							break;
						case 2:
							enemyMrg->AddBulbasaur(enemyWaveSet[k][3] + i * enemyWaveSet[k][5], enemyWaveSet[k][4] + i * enemyWaveSet[k][6]);
							break;
						case 3:
							enemyMrg->AddEnemy(enemyWaveSet[k][3] + i * enemyWaveSet[k][5], enemyWaveSet[k][4] + i * enemyWaveSet[k][6]);
							break;
						case 4:
							enemyMrg->AddPhantom(enemyWaveSet[k][3] + i * enemyWaveSet[k][5], enemyWaveSet[k][4] + i * enemyWaveSet[k][6]);
							break;
						case 5:
							enemyMrg->AddGolbat(enemyWaveSet[k][3] + i * enemyWaveSet[k][5], enemyWaveSet[k][4] + i * enemyWaveSet[k][6]);
							break;
						default:
							break;
						}
					}
					enemyWave++;
				}
			}
			if (enemyTime > enemyWaveSet[9][0] && enemyWave == 9)
			{
				enemyWave++;
				life = player->GetLife();
				switch (enemyWaveSet[9][2])
				{
				case 1:
					enemyMrg->AddHoOh(enemyWaveSet[9][3], enemyWaveSet[9][4]);
					break;
				case 2:
					enemyMrg->AddLugia(enemyWaveSet[9][3], enemyWaveSet[9][4]);
					break;
				case 3:
					enemyMrg->AddFireBird(enemyWaveSet[9][3], enemyWaveSet[9][4]);
					break;
				default:
					break;
				}


			}

			if (enemyWave == 10)
			{
				bgCount = 2;
				currPosY += 2;
				HP = enemyMrg->GetHP();
				hpBar->SetHp(enemyMrg->GetHP());

				if (life > player->GetLife())
				{
					for (int i = 0; i < 3; i++)
					{
						enemyMrg->AddEnemy(100 + (i*(rand() % 40 + 50)), 200 + (i*(rand() % 70 + 70)));
					}
					life = player->GetLife();
				}
				if (enemyMrg->GetIsDie())
				{
					isclear = true;
				}
			}
			else bgCount = 0;
			hpBar->SetEnemyWave(enemyWave);
		}
	}

}

void Stage::Render(HDC hdc)
{
	if (image)
	{
		if (isCurrStage)
		{
			image->BgRender(hdc, 0, currPosY);

			
		}
	}

	if (hpBar)
	{
		hpBar->Render(hdc);
	}
}
void Stage::SetEnemyWaveSet(int _enemySet1[], int _enemySet2[], int _enemySet3[], int _enemySet4[], int _enemySet5[],
	int _enemySet6[], int _enemySet7[], int _enemySet8[], int _enemySet9[], int _enemySet10[])
{
	enemyWaveSet[0] = _enemySet1;
	enemyWaveSet[1] = _enemySet2;
	enemyWaveSet[2] = _enemySet3;
	enemyWaveSet[3] = _enemySet4;
	enemyWaveSet[4] = _enemySet5;
	enemyWaveSet[5] = _enemySet6;
	enemyWaveSet[6] = _enemySet7;
	enemyWaveSet[7] = _enemySet8;
	enemyWaveSet[8] = _enemySet9;
	enemyWaveSet[9] = _enemySet10;

}

Stage::Stage()
{
}

Stage::~Stage()
{
}
