#include "EnemyManager.h"
#include "Enemy.h"
#include "Bulbasaur.h"
#include "Slowpoke.h"
#include "FireBird.h"
#include "HoOh.h"
#include "Lugia.h"
#include "Phantom.h"
#include "Golbat.h"


HRESULT EnemyManager::Init()
{
	
	if (!isInit)
	{
		vecEnemys.resize(30);
		for (int i = 0; i < vecEnemys.size(); i++)
		{
			vecEnemys[i] = new Enemy();
			vecEnemys[i]->SetAsh(ash);
			vecEnemys[i]->Init();
		}

		

		vecBulbasaurs.resize(30);
		for (int i = 0; i < vecBulbasaurs.size(); i++)
		{ 
			vecBulbasaurs[i] = new Bulbasaur();
			vecBulbasaurs[i]->SetAsh(ash);
			vecBulbasaurs[i]->Init();
		}

		vecSlowpokes.resize(30);
		for (int i = 0; i < vecSlowpokes.size(); i++)
		{
			vecSlowpokes[i] = new Slowpoke();
			vecSlowpokes[i]->SetAsh(ash);
			vecSlowpokes[i]->Init();
		}

		vecPhantom.resize(30);
		for (int i = 0; i < vecPhantom.size(); i++)
		{
			vecPhantom[i] = new Phantom();
			vecPhantom[i]->SetAsh(ash);
			vecPhantom[i]->Init();
		}
		vecGolbats.resize(30);
		for (int i = 0; i < vecGolbats.size(); i++)
		{
			vecGolbats[i] = new Golbat();
			vecGolbats[i]->SetAsh(ash);
			vecGolbats[i]->Init();
		}


		vecFireBirds.resize(1);
		vecFireBirds[0] = new FireBird();
		vecFireBirds[0]->SetAsh(ash);


		vecHoOhs.resize(1);
		vecHoOhs[0] = new HoOh();
		vecHoOhs[0]->SetAsh(ash);

		vecLugias.resize(1);
		vecLugias[0] = new Lugia();
		vecLugias[0]->SetAsh(ash);

		isFireBirdShow = false;
		isHoOhShow = false;
		isLugiaShow = false;
		enemyIndex = 0;
		bulbasaurIndex = 0;
		slowpokeIndex = 0;
		phantomIndex = 0;
		GolbatIndex = 0;
	}
	else {

		for (int i = 0; i < vecEnemys.size(); i++)
		{
			vecEnemys[i]->SetIsDie(true);
		}

		
		for (int i = 0; i < vecBulbasaurs.size(); i++)
		{
			vecBulbasaurs[i]->SetIsDie(true);
		}

		
		for (int i = 0; i < vecSlowpokes.size(); i++)
		{
			vecSlowpokes[i]->SetIsDie(true);
		}

		for (int i = 0; i < vecPhantom.size(); i++)
		{
			vecPhantom[i]->SetIsDie(true);
		}
		for (int i = 0; i < vecGolbats.size(); i++)
		{
			vecGolbats[i]->SetIsDie(true);
		}

		isDie = false;
		isFireBirdShow = false;
		isHoOhShow = false;
		isLugiaShow = false;
		enemyIndex = 0;
		bulbasaurIndex = 0;
		slowpokeIndex = 0;
		phantomIndex = 0;
		GolbatIndex = 0;
	}

	isInit = true;
	return S_OK;
}

void EnemyManager::Release()
{
	

	for (auto& it : vecEnemys)
	{
		it->Release(); //iterator가 값을 담고있는 주소니까 이 주소의 값이 에너미의 포인터다.
		SAFE_DELETE(it);
	}

	vecEnemys.clear(); //map과 똑같이 clear를 진행.

	for (auto& it : vecBulbasaurs)
	{
		it->Release(); //iterator가 값을 담고있는 주소니까 이 주소의 값이 에너미의 포인터다.
		SAFE_DELETE(it);
	}

	vecBulbasaurs.clear();
	for (auto& it : vecSlowpokes)
	{
		it->Release(); //iterator가 값을 담고있는 주소니까 이 주소의 값이 에너미의 포인터다.
		SAFE_DELETE(it);
	}

	vecSlowpokes.clear();

	for (auto& it : vecPhantom)
	{
		it->Release(); //iterator가 값을 담고있는 주소니까 이 주소의 값이 에너미의 포인터다.
		SAFE_DELETE(it);
	}

	vecPhantom.clear();
	for (auto& it : vecFireBirds)
	{
		it->Release(); //iterator가 값을 담고있는 주소니까 이 주소의 값이 에너미의 포인터다.
		SAFE_DELETE(it);
	}

	vecFireBirds.clear();
	for (auto& it : vecHoOhs)
	{
		it->Release(); //iterator가 값을 담고있는 주소니까 이 주소의 값이 에너미의 포인터다.
		SAFE_DELETE(it);
	}

	vecHoOhs.clear();

	for (auto& it : vecLugias)
	{
		it->Release(); //iterator가 값을 담고있는 주소니까 이 주소의 값이 에너미의 포인터다.
		SAFE_DELETE(it);
	}

	vecLugias.clear();



	for (auto& it : vecGolbats)
	{
		it->Release(); //iterator가 값을 담고있는 주소니까 이 주소의 값이 에너미의 포인터다.
		SAFE_DELETE(it);
	}

	vecGolbats.clear();





}

void EnemyManager::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown('E'))
	{
		AddEnemy(80 + (vecEnemys.size() % 5) * 100, 120 + (vecEnemys.size() / 5) * 120);
				
	}

	if (enemyIndex > 0)
	{
		itEnemys = vecEnemys.begin();
		for (int i = 0; i < enemyIndex; itEnemys++)
		{
			(*itEnemys)->Update();
			i++;
		}
	}
	if (bulbasaurIndex > 0)
	{
		itBulbasaurs = vecBulbasaurs.begin();
		for (int i = 0; i < bulbasaurIndex; itBulbasaurs++)
		{
			(*itBulbasaurs)->Update();
			i++;
		}
	}

	if (slowpokeIndex > 0)
	{
		itSlowpokes = vecSlowpokes.begin();
		for (int i = 0; i < slowpokeIndex; itSlowpokes++)
		{
			(*itSlowpokes)->Update();
			i++;
		}
	}

	if (phantomIndex > 0)
	{
		itPhantom = vecPhantom.begin();
		for (int i = 0; i < phantomIndex; itPhantom++)
		{
			(*itPhantom)->Update();
			i++;
		}
	}
	if (GolbatIndex > 0)
	{
		itGolbats = vecGolbats.begin();
		for (int i = 0; i < GolbatIndex; itGolbats++)
		{
			(*itGolbats)->Update();
			i++;
		}
	}


	if (isFireBirdShow)
	{
		for (auto& it : vecFireBirds)
		{
			it->Update();
			HP = it->GetHP();
			isDie = it->GetIsDie();
		}
	}

	if (isHoOhShow)
	{
		for (auto &it : vecHoOhs)
		{
			it->Update();
			HP = it->GetHP();
			isDie = it->GetIsDie();
		}
	}
	if (isLugiaShow)
	{
		for (auto &it : vecLugias)
		{
			it->Update();
			HP = it->GetHP();
			isDie = it->GetIsDie();
		}
	}
	for (auto& it : vecEnemys)
	{
		it->DieUpdate();
	}
	for (auto& it : vecBulbasaurs)
	{
		it->DieUpdate();
	}
	for (auto& it : vecSlowpokes)
	{
		it->DieUpdate();
	}
	for (auto& it : vecPhantom)
	{
		it->DieUpdate();
	}
	for (auto& it : vecGolbats)
	{
		it->DieUpdate();
	}


}

void EnemyManager::Render(HDC hdc)
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Render(hdc);
	}

	for (auto&it : vecGolbats)
	{
		it->Render(hdc);

	}


	for (auto&it : vecBulbasaurs)
	{
		it->Render(hdc);
	}


	for (auto&it : vecSlowpokes)
	{
		it->Render(hdc);
	}

	for (auto&it : vecPhantom)
	{
		it->Render(hdc);
	}


	for (auto&it : vecFireBirds)
	{
		it->Render(hdc);
	}


	for (auto&it : vecHoOhs)
	{
		it->Render(hdc);
	}

	for (auto&it : vecLugias)
	{
		it->Render(hdc);

	}


}

void EnemyManager::SetAsh(Ash * _ash)
{
	ash = _ash;
}

void EnemyManager::AddEnemy(float posX, float posY)
{

	vecEnemys[enemyIndex]->Init(posX, posY);
	enemyIndex++;
}

void EnemyManager::AddBulbasaur(float posX, float posY)
{
	vecBulbasaurs[bulbasaurIndex]->Init(posX, posY);
	bulbasaurIndex++;
}

void EnemyManager::AddSlowpoke(float posX, float posY)
{
	vecSlowpokes[slowpokeIndex]->Init(posX, posY);
	slowpokeIndex++;
}

void EnemyManager::AddPhantom(float posX, float posY)
{
	vecPhantom[phantomIndex]->Init(posX, posY);
	phantomIndex++;
}

void EnemyManager::AddGolbat(float posX, float posY)
{
	vecGolbats[GolbatIndex]->Init(posX, posY);
	GolbatIndex++;
}

void EnemyManager::AddFireBird(float posX, float posY)
{
	vecFireBirds[0]->Init(posX, posY);
	HP = vecFireBirds[0]->GetHP();
	isFireBirdShow = true;
}

void EnemyManager::AddHoOh(float posX, float posY)
{
	vecHoOhs[0]->Init(posX, posY);
	HP = vecHoOhs[0]->GetHP();
	isHoOhShow = true;
}

void EnemyManager::AddLugia(float posX, float posY)
{
	vecLugias[0]->Init(posX, posY);
	HP = vecLugias[0]->GetHP();
	isLugiaShow = true;
}
