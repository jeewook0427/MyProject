#include "Rocket.h"
#include "Image.h"
#include "Animation.h"

HRESULT Rocket::Init()
{
	return S_OK;
}

void Rocket::Release()
{
	if (releaseCount == 0)
	{
		SAFE_DELETE(ani);
	}

	releaseCount++;
	if (releaseCount >= 90)
	{
		releaseCount = 0;
	}
}

void Rocket::Update()
{
	if (updateCount == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (tileinfo[tp.y - i][tp.x - j].isElec)
				{
					isElec = true;
					goto skip1;
				}
					
				else
				{
					isElec = false;
				}
				
			}
		}

	skip1:

		
		vecit = (*ObjectManager::GetSingleton()->FindObjectVec()).begin();	// 확인필요
		for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
		{
			for (int k = 0; k < 10; k++)
			{
				for (int j = 0; j < 9; j++)
				{
					if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == (tp.x - j)
						&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y - k))
					{
						if (CheckCollision(rect.left + 176, rect.top + 224, 352,
							(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10) ||
							CheckCollision(rect.left + 176, rect.top + 160, 352,
							(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10))
						{
							if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONGEARWHEEL)
							{
								if (rocketMaterial[0].name == IRONGEARWHEEL)
									rocketMaterial[0].num++;
								else
								{
									rocketMaterial[0].name = IRONGEARWHEEL;
									rocketMaterial[0].num = 1;
									rocketMaterial[0].isStorage = true;
								}
								(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
								(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);

								goto skip;
							}

							else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == ELECTRONICCIRCUIT)
							{
								if (rocketMaterial[1].name == ELECTRONICCIRCUIT)
									rocketMaterial[1].num++;
								else
								{
									rocketMaterial[1].name = ELECTRONICCIRCUIT;
									rocketMaterial[1].num = 1;
									rocketMaterial[1].isStorage = true;
								}
								(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
								(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);

								goto skip;
							}

							else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == ADVANCEDCIRCUIT)
							{
								if (rocketMaterial[2].name == ADVANCEDCIRCUIT)
									rocketMaterial[2].num++;
								else
								{
									rocketMaterial[2].name = ADVANCEDCIRCUIT;
									rocketMaterial[2].num = 1;
									rocketMaterial[2].isStorage = true;
								}
								(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
								(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);

								goto skip;
							}


							else
							{
								(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
								(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);

								goto skip;
							}
						}
					}
				}
			}
			vecit++;
		}
			
	skip:

		if (KeyManager::GetSingleton()->IsOnceKeyDown('K'))
		{
			productCount+=7;
		}

		if (isElec && !gameOver)
		{
			if (rocketMaterial[0].name == IRONGEARWHEEL && rocketMaterial[1].name == ELECTRONICCIRCUIT
				&& rocketMaterial[2].name == ADVANCEDCIRCUIT && rocketMaterial[0].num >= 2)
			{
				isMaterialFilled = true;
				materialGage += 80 * TimeManager::GetSingleton()->GetDeltaTime();

				if (materialGage > 200)
				{
					rocketMaterial[0].num -= 2;
					rocketMaterial[1].num--;
					rocketMaterial[2].num--;

					if (rocketMaterial[0].num <= 0)
					{
						rocketMaterial[0].name = EMPTY;
						rocketMaterial[0].isStorage = false;
						rocketMaterial[0].num = 0;
					}

					if (rocketMaterial[1].num <= 0)
					{
						rocketMaterial[1].name = EMPTY;
						rocketMaterial[1].isStorage = false;
						rocketMaterial[1].num = 0;
					}

					if (rocketMaterial[2].num <= 0)
					{
						rocketMaterial[2].name = EMPTY;
						rocketMaterial[2].isStorage = false;
						rocketMaterial[2].num = 0;
					}

					productCount++;
					materialGage = 0;




				}
			}

			else
			{
				isMaterialFilled = false;
				materialGage = 0;
			}

			if (productCount >= 7)
			{
				productCount = 0;
				rocketAlpha += 50;
				if (rocketAlpha >= 250)
				{
					rocketAlpha = 250;

					if (tempPosY > 0)
					{
						SoundManager::GetSingleton()->Play("raiserocket", 1.0f);
					}
					tempPosY -= 20;
					if (tempPosY <= 0)
						tempPosY = 0;



					if (pos.y <= 0)
					{
						isLaunch = true;
					}


				}
			}

			if (pos.y > tempPosY)
			{
				pos.y -= 2.5*TimeManager::GetSingleton()->GetDeltaTime();
			}

			

		}


		if (isLaunch)
		{
			g_pos.x = (tp.x - 5) * 32;
			g_pos.y = (tp.y - 5) * 32;

			if ((tp.x - 5) * 32 < WINSIZE_X / 2)
			{
				g_pos.x = WINSIZE_X / 2;
			}

			else if ((tp.x - 5) * 32 > 8192 - WINSIZE_X / 2)
			{
				g_pos.x = 8192 - WINSIZE_X / 2;
			}

			if ((tp.y - 5) * 32 < WINSIZE_Y / 2)
			{
				g_pos.y = WINSIZE_Y / 2;
			}

			else if ((tp.y - 5) * 32 > 8192 - WINSIZE_Y / 2)
			{
				g_pos.y = 8192 - WINSIZE_Y / 2;
			}

			p_pos.x = (tp.x - 5) * 32;
			p_pos.y = (tp.y - 5) * 32;

			if (!soundPlay)
			{
				SoundManager::GetSingleton()->Play("launchrocket", 1.0f);
				SoundManager::GetSingleton()->Stop("BGM1");
				SoundManager::GetSingleton()->Stop("BGM2");
				SoundManager::GetSingleton()->Stop("BGM3");
				soundPlay = true;
			}
			launchTime += TimeManager::GetSingleton()->GetDeltaTime();

			if (launchTime < 9)
			{
				holeAlpha += 31.25*TimeManager::GetSingleton()->GetDeltaTime();
				if (holeAlpha >= 250)
					holeAlpha = 250;

			}

			else
			{
				if (pos.y < -30)
				{
					holeAlpha -= 60 * TimeManager::GetSingleton()->GetDeltaTime();
					if (holeAlpha <= 0)
						holeAlpha = 0;
				}

				pos.y -= 120 * TimeManager::GetSingleton()->GetDeltaTime();

				if (launchTime > 20)
				{
					gameOver = true;
					if (soundPlay)
						SoundManager::GetSingleton()->Play("gameclear", 1.0f);
				}

			}

		}

		else
		{
			soundPlay = false;
		}

		if (abs(tp.x - (int)(g_pos.x) / 32) < 40 && abs(tp.y - (int)(g_pos.y) / 32) < 30)
		{
			if (PtInRect(&rect, mousepos))
			{
				isRectRender = true;

				if (((abs(rect.left - p_pos.x) < 170 && abs(rect.top - p_pos.y) < 170) || (abs(rect.left - p_pos.x) < 170 && abs(rect.bottom - p_pos.y) < 170))
					|| ((abs(rect.right - p_pos.x) < 170 && abs(rect.top - p_pos.y) < 170) || (abs(rect.right - p_pos.x) < 170 && abs(rect.bottom - p_pos.y) < 170)))
				{
					isSelectedClose = true;
				}

				else
				{
					isSelectedClose = false;
				}

				if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON) && !ToolInvenIsOpen &&!isLaunch)
				{
					isDelete = true;
					Tutorial::GetSingleton()->SucceedQuest_9();
					AddInInventory(ROCKET, 1);

					for (int i = 0; i < 12; i++)
					{
						for (int j = 0; j < 11; j++)
						{
							tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
						}
					}

					if (checkRender)
					{
						if (!soundPlay)
						{
							SoundManager::GetSingleton()->Play("remove", 1.0f);
							soundPlay = true;

						}
					}
					else
					{
						SoundManager::GetSingleton()->Stop("remove");
						soundPlay = false;
					}

				}

			}

			else
			{
				isRectRender = false;
			}
		}
	}


	updateCount++;
	if (updateCount >= 90)
	{
		updateCount = 0;
	}
}

void Rocket::Render(HDC hdc)
{
	if (renderCount == 0)
	{
		if (abs(tp.x - (int)(g_pos.x) / 32) < 40 && abs(tp.y - (int)(g_pos.y) / 32) < 30)
			checkRender = true;
		else
			checkRender = false;

		ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	}


	if (image && checkRender && renderCount == 0)
	{
		
		
		rocketShadow->FrameAlphaRender(hdc, ((tp.x - 5 - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 96,
			((tp.y - 5 - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 62, frame.x, frame.y, 110, false, false);

		if (rocketAlpha == 0)
		{
			rocketDoorBack->FrameRender(hdc, ((tp.x - 5 - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48,
				((tp.y - 5 - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 92, frame.x, frame.y);

			rocketDoorFront->FrameRender(hdc, ((tp.x - 5 - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48,
				((tp.y - 5 - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 92, frame.x, frame.y);
		}

		else if (rocketAlpha > 0)
		{
			rocketHoleBase->FrameRender(hdc, ((tp.x - 5 - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48,
				((tp.y - 5 - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 92, frame.x, frame.y);

			rocketHoleLight->AlphaRender(hdc, ((tp.x - 5 - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48,
				((tp.y - 5 - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 92, holeAlpha);
		}
	

		image->FrameRender(hdc, ((tp.x - 5 - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48,
			((tp.y - 5 - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32, frame.x, frame.y);



		if (pos.y >= -50)
			rocket->RocketAlphaRender(hdc, ((tp.x - 5 - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48 + pos.x,
			((tp.y - 5 - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + pos.y + 95, -pos.y, 70, rocketAlpha);

		rocketSiloFront->FrameRender(hdc, ((tp.x - 5 - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48,
			((tp.y - 5 - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 144, frame.x, frame.y);



		if (!isElec && checkRender)
		{
			if (checkAlpha)
			{
				alpha += 10;
				if (alpha >= 255)
				{
					checkAlpha = false;
					alpha = 255;
				}

			}

			else
			{
				alpha -= 10;
				if (alpha <= 0)
				{
					checkAlpha = true;
					alpha = 0;
				}
			}



			warning->AlphaRender(hdc, ((tp.x - 5 - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 50,
				((tp.y - 5 - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 62, 0, 0, alpha, 1);
		}


		if (isRectRender)
		{
			this->SelectBoxRender(hdc);
		}


	}


	renderCount++;

	if (renderCount >= 90)
	{
		renderCount = 0;
	}



}

void Rocket::SelectBoxRender(HDC hdc)
{
	if (!isSelectedClose)
	{
		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8 * scale,
			rect.top - g_pos.y + WINSIZE_Y / 2 + 8 * scale, 2, 0, scale);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8 * scale,
			rect.top - g_pos.y + WINSIZE_Y / 2 + 8 * scale, 3, 0, scale);

		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8 * scale,
			rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8 * scale, 2, 1, scale);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8 * scale,
			rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8 * scale, 3, 1, scale);
	}

	else
	{
		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8 * scale,
			rect.top - g_pos.y + WINSIZE_Y / 2 + 8 * scale, 0, 0, scale);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8 * scale,
			rect.top - g_pos.y + WINSIZE_Y / 2 + 8 * scale, 1, 0, scale);

		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8 * scale,
			rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8 * scale, 0, 1, scale);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8 * scale,
			rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8 * scale, 1, 1, scale);
	}
}

void Rocket::RocketRender(HDC hdc)
{
	if (renderCount == 0)
	{
		if (pos.y < -50)
		{
			effectimg->AnimationRender(hdc, ((tp.x - 5 - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48 + pos.x,
				((tp.y - 5 - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 95 + pos.y + 150, ani);


			rocket->RocketAlphaRender(hdc, ((tp.x - 5 - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48 + pos.x,
				((tp.y - 5 - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + pos.y + 95, -pos.y, 70, rocketAlpha);
		}
	}

	renderCount++;

	if (renderCount >= 90)
	{
		renderCount = 0;
	}
}

Rocket::Rocket(TILE_POINT _tp, int hp)
{
	releaseCount = 0;
	tp = _tp;
	Hp = hp;
	rect = { 32 * (tp.x - 8), 32 * (tp.y - 9), 32 * (tp.x + 1), 32 * (tp.y + 1) };
	image = ImageManager::GetSingleton()->FindImage("rocket-base");
	rocketShadow = ImageManager::GetSingleton()->FindImage("rocket-base-shadow");
	rocket = ImageManager::GetSingleton()->FindImage("rocket");
	rocketDoorBack = ImageManager::GetSingleton()->FindImage("rocket-door-back");
	rocketDoorFront = ImageManager::GetSingleton()->FindImage("rocket-door-front");
	selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");
	effectimg = ImageManager::GetSingleton()->FindImage("rocket-jet-flame");
	rocketHoleLight = ImageManager::GetSingleton()->FindImage("rocket-hole-light");
	rocketEffect = ImageManager::GetSingleton()->FindImage("rocket-effect");
	rocketHoleBase = ImageManager::GetSingleton()->FindImage("rocket-hole");
	rocketSiloFront = ImageManager::GetSingleton()->FindImage("rocket-silo-front");
	warning = ImageManager::GetSingleton()->FindImage("electricity-icon-yellow");

	pos.x = 0;
	pos.y = 80;


	isSelected = false;
	isSelectedClose = false;
	isRectRender = false;

	rocketAlpha = 0;
	productCount = 0;
	tempPosY = 80;
	isLaunch = false;
	soundPlay = false;
	launchTime = 0;
	holeAlpha = 0;

	scale = 2.0f;
	renderCount = 0;
	updateCount = 0;

	for (int i = 0; i < 3; i++)
	{
		rocketMaterial[i].name = EMPTY;
		rocketMaterial[i].num = 0;
		rocketMaterial[i].isStorage = false;
		rocketMaterial[i].isSelected = false;
		rocketMaterial[i].rc = { 0 };
	}

	ani = new Animation();
	ani->Init(effectimg->GetWidth(), effectimg->GetHeight(), effectimg->GetFrameWidth(), effectimg->GetFrameHeight());
	ani->SetUpdateTime(FPS / 2);
	ani->SetPlayFrame(0, 2, false, true);
	ani->Start();

	ImageManager::GetSingleton()->FindImage("mini-rocket-icon")->
		Render(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + (int)(3 * tp.x - 16.5), 50 + (int)(3 * tp.y - 13.5));
}

Rocket::Rocket()
{

}

Rocket::~Rocket()
{
}
