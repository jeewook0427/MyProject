#include "MissileManager.h"
#include "Missile.h"
#include "Enemy.h"
#include "Ash.h"
#include "UIManager.h"


void MissileManager::NewMissile()
{
	Missile* tempmissile;

	vecMissiles.reserve(150); // vecMissiles.size() resize할 때만 가능.

	for (int i = 0; i < 150; i++)
	{
		tempmissile = CreateMissile();
		tempmissile->Init();
		stMissiles.push(tempmissile);

	}
}

HRESULT MissileManager::Init()
{
	angle = 0;
	power = 1;
	missiledirection = false;
	return S_OK;
}

void MissileManager::Release()
{
	for (auto& it : vecMissiles)
	{
		it->Release();
		SAFE_DELETE(it);
	}

	vecMissiles.clear();
}

void MissileManager::Update()
{

}

void MissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}
}

bool MissileManager::Fire()
{

	return true;

}

void MissileManager::SetDegree(int _degree)
{
	for (int i = 0; i < vecMissiles.size(); i++)
	{
		vecMissiles[i]->SetDgree(vecMissiles[i]->GetDgree() + _degree);


	}
}

bool MissileManager::CheckOut(int missilenum, bool topcheck)
{
	bool check1 = false, check2 = false, check3 = false, check4 = false;

	for (int i = 0; i < missilenum; i++)
	{
		
		if ((*itMissiles)->GetPos()[i].y > WINSIZE_Y)
		{
			check1 = true;
		}
						

		if ((*itMissiles)->GetPos()[i].x > WINSIZE_X)
		{
			check2 = true;
		}
		if ((*itMissiles)->GetPos()[i].x < 0)
		{
			check3 = true;
		}

		if (topcheck)
		{
			if ((*itMissiles)->GetPos()[i].y < 0)
			{
				check4 = true;
			}
		}
		
		else
		{
			check4 = true;
		}
	}

	if (check1 && check2 && check3 && check4)
	{
		return true;
	}

	else
	{
		return false;
	}
	

}

Missile * BulbasaurMissileManager::CreateMissile()
{
	return new BulbasaurMissile;
}

void BulbasaurMissileManager::Update()
{
	if (vecMissiles.size() > 0)
	{
		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
		{
			if ((*itMissiles)->GetOnHit())
			{
				(*itMissiles)->SetOnHit(false);
				(*itMissiles)->SetIsFire(false);
				stMissiles.push(*itMissiles);
				itMissiles = vecMissiles.erase(itMissiles);
				itMissiles = vecMissiles.end();
				onHit = false;
				break;
			}

			else
			{
				if (this->CheckOut(3,false))
				{
					(*itMissiles)->SetIsFire(false);
					stMissiles.push(*itMissiles);
					itMissiles = vecMissiles.erase(itMissiles);
					itMissiles = vecMissiles.end();
					break;

				}

				if (itMissiles == vecMissiles.end())
				{
					break;
				}
			}
		}
	}

	
	for (auto& it : vecMissiles)
	{
		it->Update();
	}
}

bool BulbasaurMissileManager::Fire()
{
	vecMissiles.push_back(stMissiles.top());
	stMissiles.pop();

	for (auto& it : vecMissiles)
	{
		if (it->GetIsFire())
		{
			continue;
		}
		it->SetIsFire(true);
		it->SetAngle((DEGREE_TO_RADIAN(240)));
		it->SetPos(owner->GetPos());


		return true;
	}

	return false;
}

void BulbasaurMissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}
}



BulbasaurMissileManager::BulbasaurMissileManager()
{
}

BulbasaurMissileManager::~BulbasaurMissileManager()
{
}

Missile * PlayerMissileManager::CreateMissile()
{
	return new PlayerMissile;
}


void PlayerMissileManager::Update()
{
	if (vecMissiles.size() > 0)
	{
		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
		{
			if ((*itMissiles)->GetOnHit() && (*itMissiles)->GetBlockScore() == 0)
			{
				uimanager->SetScore(uimanager->GetSocre() + 30);

			}
		}

		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
		{
			if (!(*itMissiles)->GetEffect()&& !(*itMissiles)->GetIsFire())
			{
				(*itMissiles)->SetOnHit(false);
				stMissiles.push(*itMissiles);
				itMissiles = vecMissiles.erase(itMissiles);
				itMissiles = vecMissiles.end();
				onHit = false;
				break;
			}


			for (int i = 0; i < 1; i++)
			{
				if ((*itMissiles)->GetPos()[i].y < 0)
				{
					(*itMissiles)->SetIsFire(false);
					stMissiles.push(*itMissiles);
					itMissiles = vecMissiles.erase(itMissiles);
					itMissiles = vecMissiles.end();
					break;

				}


			}

			if (itMissiles == vecMissiles.end())
			{
				break;
			}

		}
	}


	for (auto& it : vecMissiles)
	{
		it->Update();
	}
}

bool PlayerMissileManager::Fire()
{
	if (power >= 1)
	{
		vecMissiles.push_back(stMissiles.top());
		stMissiles.pop();

		for (auto& it : vecMissiles)
		{
			if (it->GetIsFire())
			{
				continue;
			}
			it->Init();
			it->SetPower(power);
			it->SetIsFire(true);
			it->SetAngle((angle));
			it->SetPos2(owner->GetPos());


			break;
		}
	}
	
	if (power >= 2)
	{
		vecMissiles.push_back(stMissiles.top());
		stMissiles.pop();

		for (auto& it : vecMissiles)
		{
			if (it->GetIsFire())
			{
				continue;
			}
			it->Init();
			it->SetPower(power);
			it->SetIsFire(true);
			it->SetAngle(angle);
			it->SetPos2({ owner->GetPos().x + 15, owner->GetPos().y +10});


			break;
		}

		vecMissiles.push_back(stMissiles.top());
		stMissiles.pop();

		for (auto& it : vecMissiles)
		{
			if (it->GetIsFire())
			{
				continue;
			}
			it->Init();
			it->SetPower(power);
			it->SetIsFire(true);
			it->SetAngle(angle);
			it->SetPos2({ owner->GetPos().x - 15, owner->GetPos().y +10 });


			break;
		}

	}

	if (power >= 3)
	{
		vecMissiles.push_back(stMissiles.top());
		stMissiles.pop();

		for (auto& it : vecMissiles)
		{
			if (it->GetIsFire())
			{
				continue;
			}
			it->Init();
			it->SetPower(power);
			it->SetIsFire(true);
			it->SetAngle(DEGREE_TO_RADIAN(120));
			it->SetPos2(owner->GetPos());


			break;
		}

		vecMissiles.push_back(stMissiles.top());
		stMissiles.pop();

		for (auto& it : vecMissiles)
		{
			if (it->GetIsFire())
			{
				continue;
			}
			it->Init();
			it->SetPower(power);
			it->SetIsFire(true);
			it->SetAngle(DEGREE_TO_RADIAN(60));
			it->SetPos2(owner->GetPos());


			break;
		}

	}
	
	if (power >= 4)
	{
		vecMissiles.push_back(stMissiles.top());
		stMissiles.pop();

		for (auto& it : vecMissiles)
		{
			if (it->GetIsFire())
			{
				continue;
			}
			it->Init();
			it->SetPower(power);
			it->SetIsFire(true);
			it->SetAngle(angle);
			it->SetPos2({ owner->GetPos().x -30, owner->GetPos().y+20 });


			break;
		}

		vecMissiles.push_back(stMissiles.top());
		stMissiles.pop();

		for (auto& it : vecMissiles)
		{
			if (it->GetIsFire())
			{
				continue;
			}
			it->Init();
			it->SetPower(power);
			it->SetIsFire(true);
			it->SetAngle(angle);
			it->SetPos2({ owner->GetPos().x + 30, owner->GetPos().y +20});


			return true;
		}

	}
	return false;
}

void PlayerMissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}
}


PlayerMissileManager::PlayerMissileManager()
{
}

PlayerMissileManager::~PlayerMissileManager()
{
}

Missile * DarkpetMissileManager::CreateMissile()
{
	return new DarkpetMissile;
}

void DarkpetMissileManager::Update()
{
	if (vecMissiles.size() > 0)
	{
		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
		{
			if ((*itMissiles)->GetOnHit())
			{
				(*itMissiles)->SetOnHit(false);
				(*itMissiles)->SetIsFire(false);
				stMissiles.push(*itMissiles);
				itMissiles = vecMissiles.erase(itMissiles);
				itMissiles = vecMissiles.end();
				onHit = false;
				break;
			}

			else
			{
				for (int i = 0; i < 1; i++)
				{
					if ((*itMissiles)->GetPos()[i].y > WINSIZE_Y)
					{
						(*itMissiles)->SetIsFire(false);
						stMissiles.push(*itMissiles);
						itMissiles = vecMissiles.erase(itMissiles);
						itMissiles = vecMissiles.end();
						break;

					}

				}

				if (itMissiles == vecMissiles.end())
				{
					break;
				}
			}
		}
	}


	for (auto& it : vecMissiles)
	{
		it->Update();
	}
}

bool DarkpetMissileManager::Fire()
{
	vecMissiles.push_back(stMissiles.top());
	stMissiles.pop();

	for (auto& it : vecMissiles)
	{
		if (it->GetIsFire())
		{
			angle += 0.5;
			continue;
		}
		it->SetIsFire(true);
		it->SetAngle((DEGREE_TO_RADIAN(270)));
		it->SetPos(owner->GetPos());


		return true;
	}

	return false;
}

void DarkpetMissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}
}

DarkpetMissileManager::DarkpetMissileManager()
{
}

DarkpetMissileManager::~DarkpetMissileManager()
{
}

Missile * SlowpokeMissileManager::CreateMissile()
{
	return new SlowpokeMissile;
}

void SlowpokeMissileManager::Update()
{
	if (vecMissiles.size() > 0)
	{
		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
		{
			if ((*itMissiles)->GetOnHit())
			{
				(*itMissiles)->SetOnHit(false);
				(*itMissiles)->SetIsFire(false);
				stMissiles.push(*itMissiles);
				itMissiles = vecMissiles.erase(itMissiles);
				itMissiles = vecMissiles.end();
				onHit = false;
				break;
			}
			
			else
			{
				for (int i = 0; i < 1; i++)
				{
					if ((*itMissiles)->GetPos()[i].y > WINSIZE_Y || (*itMissiles)->GetPos()[i].y <0
						|| (*itMissiles)->GetPos()[i].x > WINSIZE_X || (*itMissiles)->GetPos()[i].x < 0)
					{
						(*itMissiles)->SetIsFire(false);
						stMissiles.push(*itMissiles);
						itMissiles = vecMissiles.erase(itMissiles);
						itMissiles = vecMissiles.end();
						break;

					}

				}

				if (itMissiles == vecMissiles.end())
				{
					break;
				}
			}
		}
	}
	

	for (auto& it : vecMissiles)
	{
		it->Update();
	}
}

bool SlowpokeMissileManager::Fire()
{
	float tempangle;
	vecMissiles.push_back(stMissiles.top());
	stMissiles.pop();

	for (auto& it : vecMissiles)
	{
		if (it->GetIsFire())
		{
			continue;
		}

		it->SetIsFire(true);
		it->SetAngle((DEGREE_TO_RADIAN(angle)));
		it->SetPos(owner->GetPos());


		return true;
	}

	return false;
}

void SlowpokeMissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}
}

SlowpokeMissileManager::SlowpokeMissileManager()
{
}

SlowpokeMissileManager::~SlowpokeMissileManager()
{
}

Missile * LugiaMissileManager::CreateMissile()
{
	return new LugiaMissile;
}

void LugiaMissileManager::Update()
{
	if (vecMissiles.size() > 0)
	{
		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
		{
			if ((*itMissiles)->GetOnHit())
			{
				(*itMissiles)->SetOnHit(false);
				(*itMissiles)->SetIsFire(false);
				stMissiles.push(*itMissiles);
				itMissiles = vecMissiles.erase(itMissiles);
				itMissiles = vecMissiles.end();
				onHit = false;
				break;
			}

			else
			{

				for (int i = 0; i < 5; i++)
				{
					if ((*itMissiles)->GetPos()[i].y > WINSIZE_Y || (*itMissiles)->GetPos()[i].y <0 || (*itMissiles)->GetPos()[i].x > WINSIZE_X 
						|| (*itMissiles)->GetPos()[i].x <0)
					
					{
						(*itMissiles)->SetIsFire(false);
						stMissiles.push(*itMissiles);
						itMissiles = vecMissiles.erase(itMissiles);
						itMissiles = vecMissiles.end();
						break;

					}

				}
							   
				if (itMissiles == vecMissiles.end())
				{
					break;
				}
			}
		}
	}
	
	for (auto& it : vecMissiles)
	{
		it->Update();
	}
}

bool LugiaMissileManager::Fire()
{
	
	vecMissiles.push_back(stMissiles.top());
	stMissiles.pop();

	for (auto& it : vecMissiles)
	{
		if (it->GetIsFire())
		{
			if (it->GetIsFire())
			{
				if (ChangeMi)
				{
					it->SetAngle((DEGREE_TO_RADIAN(270)));
				}

				if (missiledirection && !ChangeMi)
				{
					angle += 2;
				}
				else if (!missiledirection && !ChangeMi)
				{
					angle -= 2;
				}

				if (angle >= 30 && !ChangeMi)
				{
					missiledirection = false;
				}

				else if (angle <= -30 && !ChangeMi)
				{
					missiledirection = true;
				}

				continue;
			}
		}
		count++;
		it->SetIsFire(true);
		it->SetAngle((DEGREE_TO_RADIAN(angle+270)));
		it->SetPos({ 0,0 });
		it->SetPos2(owner->GetPos());
		it->Setcount(count);
		it->SetChangeMi(ChangeMi);	

		return true;
	}

	return false;
}

void LugiaMissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}
}

LugiaMissileManager::LugiaMissileManager()
{
}

LugiaMissileManager::~LugiaMissileManager()
{
}

Missile * HoohMissileManager::CreateMissile()
{
	return new HoOhMissile;
}

void HoohMissileManager::Update()
{
	if (vecMissiles.size() > 0)
	{
		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
		{
			if ((*itMissiles)->GetOnHit())
			{
				(*itMissiles)->SetOnHit(false);
				(*itMissiles)->SetIsFire(false);
				stMissiles.push(*itMissiles);
				itMissiles = vecMissiles.erase(itMissiles);
				itMissiles = vecMissiles.end();
				onHit = false;
				break;
			}

			else
			{
				if (this->CheckOut(20,false))
				{
					(*itMissiles)->SetIsFire(false);
					(*itMissiles)->SetCurrMissile(1);
					stMissiles.push(*itMissiles);
					itMissiles = vecMissiles.erase(itMissiles);
					itMissiles = vecMissiles.end();
					break;

				}

				if (itMissiles == vecMissiles.end())
				{
					break;
				}
			}
		}
	}

	
	for (auto& it : vecMissiles)
	{
		it->Update();
	}
}

bool HoohMissileManager::Fire()
{
	vecMissiles.push_back(stMissiles.top());
	stMissiles.pop();

	for (auto& it : vecMissiles)
	{
		if (it->GetIsFire())
		{
			continue;
		}
		it->SetIsFire(true);
		it->SetAngle((DEGREE_TO_RADIAN(180)));
		it->SetPos(owner->GetPos());
		it->SetChangeMi(ChangeMi);

		return true;
	}

	return false;
}

void HoohMissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}
}

HoohMissileManager::HoohMissileManager()
{
}

HoohMissileManager::~HoohMissileManager()
{
}


Missile * FireBirdMissileManager::CreateMissile()
{
	return new FireBirdMissile;
}

void FireBirdMissileManager::Update()
{
	if (vecMissiles.size() > 0)
	{
		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
		{
			if ((*itMissiles)->GetOnHit())
			{
				(*itMissiles)->SetOnHit(false);
				(*itMissiles)->SetIsFire(false);
				stMissiles.push(*itMissiles);
				itMissiles = vecMissiles.erase(itMissiles);
				itMissiles = vecMissiles.end();
				onHit = false;
				break;
			}

			else
			{
				if (this->CheckOut(20,true))
				{
					(*itMissiles)->SetIsFire(false);
					(*itMissiles)->SetCurrMissile(1);
					stMissiles.push(*itMissiles);
					itMissiles = vecMissiles.erase(itMissiles);
					itMissiles = vecMissiles.end();
					break;

				}

				if (itMissiles == vecMissiles.end())
				{
					break;
				}
			}
		}
	}
	
	for (auto& it : vecMissiles)
	{
		it->Update();
	}
}

bool FireBirdMissileManager::Fire()
{
	vecMissiles.push_back(stMissiles.top());
	stMissiles.pop();

	for (auto& it : vecMissiles)
	{
		if (it->GetIsFire())
		{
			angle += 1;
			continue;
		}
		it->SetIsFire(true);
		it->SetAngle((DEGREE_TO_RADIAN(angle)));
		it->SetPos(owner->GetPos());
		it->SetChangeMi(ChangeMi);

		return true;
	}

	return false;
}

void FireBirdMissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}
}

FireBirdMissileManager::FireBirdMissileManager()
{
}

FireBirdMissileManager::~FireBirdMissileManager()
{
}

Missile * PhantomMissileManager::CreateMissile()
{
	return new PhantomMissile;
}

void PhantomMissileManager::Update()
{
	if (vecMissiles.size() > 0)
	{
		for (itMissiles = vecMissiles.begin(); itMissiles != vecMissiles.end(); itMissiles++)
		{
			if ((*itMissiles)->GetOnHit())
			{
				(*itMissiles)->SetOnHit(false);
				(*itMissiles)->SetIsFire(false);
				stMissiles.push(*itMissiles);
				itMissiles = vecMissiles.erase(itMissiles);
				itMissiles = vecMissiles.end();
				onHit = false;
				break;
			}

			else
			{
				
				if (this->CheckOut(4, true))
				{
					(*itMissiles)->SetIsFire(false);
					stMissiles.push(*itMissiles);
					itMissiles = vecMissiles.erase(itMissiles);
					itMissiles = vecMissiles.end();
					break;

				}

				

				if (itMissiles == vecMissiles.end())
				{
					break;
				}
			}
		}
	}


	for (auto& it : vecMissiles)
	{
		it->Update();
	}
}

bool PhantomMissileManager::Fire()
{
	
	vecMissiles.push_back(stMissiles.top());
	stMissiles.pop();

	for (auto& it : vecMissiles)
	{
		if (it->GetIsFire())
		{
			continue;
		}

		it->SetIsFire(true);
		it->SetAngle((DEGREE_TO_RADIAN(angle)));
		it->SetPos(owner->GetPos());


		return true;
	}

	return false;
}

void PhantomMissileManager::Render(HDC hdc)
{
	for (auto& it : vecMissiles)
	{
		it->Render(hdc);
	}
}

PhantomMissileManager::PhantomMissileManager()
{
}

PhantomMissileManager::~PhantomMissileManager()
{
}

