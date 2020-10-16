#include "SteamEngine.h"
#include "Image.h"

HRESULT SteamEngine::Init()
{
	return S_OK;
}

void SteamEngine::Release()
{
	if (releaseCount == 0)
	{
		SAFE_DELETE(ani);
	}

	releaseCount++;
	if (direction == 0)
	{
		if (releaseCount >= 24)
		{
			releaseCount = 0;
		}
	}

	else if (direction == 1)
	{
		if (releaseCount >= 24)
		{
			releaseCount = 0;
		}
	}

	else if (direction == 2)
	{
		if (releaseCount >= 27)
		{
			releaseCount = 0;
		}
	}

	else if (direction == 3)
	{
		if (releaseCount >= 21)
		{
			releaseCount = 0;
		}
	}

}

void SteamEngine::Update()
{
	if (updateCount == 0)
	{
		vecit = (*ObjectManager::GetSingleton()->FindObjectVec()).begin();	// 확인필요
		for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
		{
			for (int k = 0; k < tempindex.y; k++)
			{
				for (int j = 0; j < tempindex.x; j++)
				{
					if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == (tp.x - j)
						&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y - k))
					{
						if (CheckCollision2(rect.left + tempsize[0], rect.top + tempsize[1], tempsize[2], tempsize[3],
							(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10, 10))

						{
							if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
							{
								if (fuel.name == COAL)
									fuel.num++;
								else
								{
									fuel.name = COAL;
									fuel.num = 1;
									fuel.isStorage = true;
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


		if ((fuel.name == TREE || fuel.name == COAL) && (fuel.num > 0))
			isFuelFilled = true;
		else
			isFuelFilled = false;



		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STEAMENGINE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it2 = (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).begin(); it2 != (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).end(); it2++)
			{
				if (it2->second->GetCheckRender() && it2->second->GetisFuelFilled())
				{
					isPlay = true;
					soundPlay = it2->second->GetSoundPlay();
					break;
				}

				else
				{
					isPlay = false;
				}

			}
		}

		if (checkRender && isFuelFilled)
		{
			if (!soundPlay)
			{


				iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STEAMENGINE);
				if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
				{
					for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).end(); it++)
					{
						it->second->SetSoundPlay(true);
					}
				}
				if (isPlay)
					SoundManager::GetSingleton()->Play("steamengine", 1.0f);
				soundPlay = true;

			}
		}
		else
		{
			if (!isPlay)
			{
				SoundManager::GetSingleton()->Stop("steamengine");
				soundPlay = false;
			}
		}

		if (isFuelFilled)
		{
			isElec = true;
			elecNum = 0;
			fuelGage -= 0.5;
			if (fuelGage <= 0)
			{
				fuelGage = 100;
				fuel.num--;
				if (fuel.num <= 0)
				{
					fuel.name = EMPTY;
					fuel.num = 0;
					fuel.isStorage = false;
				}
			}
			if (direction == 0)
			{
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (!(tileinfo[tp.y + 2 - i][tp.x - j].isElec))
							tileinfo[tp.y + 2 - i][tp.x - j].isElec = true;
					}
				}
			}

			else if (direction == 1)
			{
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (!(tileinfo[tp.y + 2 - i][tp.x + 2 - j].isElec))
							tileinfo[tp.y + 2 - i][tp.x + 2 - j].isElec = true;
					}
				}
			}

			else if (direction == 2)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						if (!(tileinfo[tp.y + 2 - i][tp.x + 2 - j].isElec))
							tileinfo[tp.y + 2 - i][tp.x + 2 - j].isElec = true;
					}
				}
			}

			else if (direction == 3)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						if (!(tileinfo[tp.y - i][tp.x + 2 - j].isElec))
							tileinfo[tp.y - i][tp.x + 2 - j].isElec = true;
					}
				}
			}
		}

		else
		{

			isElec = false;
			elecNum = 1;
			if (direction == 0)
			{
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						tileinfo[tp.y + 2 - i][tp.x - j].isElec = false;
					}
				}
			}

			else if (direction == 1)
			{
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						tileinfo[tp.y + 2 - i][tp.x + 2 - j].isElec = false;
					}
				}
			}

			else if (direction == 2)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						tileinfo[tp.y + 2 - i][tp.x + 2 - j].isElec = false;
					}
				}
			}

			else if (direction == 3)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						tileinfo[tp.y - i][tp.x + 2 - j].isElec = false;
					}
				}
			}
		}


		if (abs(tp.x - (int)(g_pos.x) / 32) < 37 && abs(tp.y - (int)(g_pos.y) / 32) < 26)
		{
			if (PtInRect(&rect, mousepos))
			{
				isRectRender = true;

				if (((abs(rect.left - p_pos.x) < 128 && abs(rect.top - p_pos.y) < 128) || (abs(rect.left - p_pos.x) < 128 && abs(rect.bottom - p_pos.y) < 128))
					|| ((abs(rect.right - p_pos.x) < 128 && abs(rect.top - p_pos.y) < 128) || (abs(rect.right - p_pos.x) < 128 && abs(rect.bottom - p_pos.y) < 128)))
				{
					isSelectedClose = true;
				}

				else
				{
					isSelectedClose = false;
				}


				if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON) && !ToolInvenIsOpen)
				{
					isDelete = true;
					AddInInventory(STEAMENGINE, 1);
					Tutorial::GetSingleton()->SucceedQuest_9();
					SoundManager::GetSingleton()->Stop("steamengine");


					iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STEAMENGINE);
					if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
					{
						for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).end(); it++)
						{
							it->second->SetSoundPlay(false);
						}
					}

					if (direction == 0)
					{

						for (int i = 0; i < 6; i++)
						{
							for (int j = 0; j < 10; j++)
							{
								tileinfo[tp.y + 2 - i][tp.x - j].isElec = false;
							}
						}


						for (int i = 0; i < 3; i++)
						{
							for (int j = 0; j < 9; j++)
							{
								tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
							}
						}


					}

					else if (direction == 1)
					{
						for (int i = 0; i < 6; i++)
						{
							for (int j = 0; j < 10; j++)
							{
								tileinfo[tp.y + 2 - i][tp.x + 2 - j].isElec = false;
							}
						}

						for (int i = 0; i < 3; i++)
						{
							for (int j = 0; j < 8; j++)
							{
								tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
							}
						}
					}

					else if (direction == 2)
					{

						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 6; j++)
							{
								tileinfo[tp.y + 2 - i][tp.x + 2 - j].isElec = false;
							}
						}


						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 3; j++)
							{
								tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
							}
						}
					}

					else if (direction == 3)
					{
						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 6; j++)
							{
								tileinfo[tp.y - i][tp.x + 2 - j].isElec = false;
							}
						}

						for (int i = 0; i < 9; i++)
						{
							for (int j = 0; j < 3; j++)
							{
								tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
							}
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

			// 팔 방향조절


		}


	}


	updateCount++;
	if (direction == 0)
	{
		if (updateCount >= 24)
		{
			updateCount = 0;
		}
	}

	else if (direction == 1)
	{
		if (updateCount >= 24)
		{
			updateCount = 0;
		}
	}

	else if (direction == 2)
	{
		if (updateCount >= 27)
		{
			updateCount = 0;
		}
	}

	else if (direction == 3)
	{
		if (updateCount >= 21)
		{
			updateCount = 0;
		}
	}
}

void SteamEngine::Render(HDC hdc)
{
	if (renderCount == 0)
	{

		if (Hp == 0)
		{
			tileinfo[tp.y][tp.x].obj = EMPTY;
		}

		if (Hp > 0)
		{

			if (abs(tp.x - (int)(g_pos.x) / 32) < 36 && abs(tp.y - (int)(g_pos.y) / 32) < 25)
				checkRender = true;
			else
				checkRender = false;
		}
	}

	if (image && checkRender && Hp > 0 && renderCount == 0)
	{
		if (isFuelFilled)
		{
			aniCount += TimeManager::GetSingleton()->GetDeltaTime();
			if (aniCount > 0.1)
			{
				aniCount = 0;
				frame.x++;

				if (frame.x > 7)
				{
					frame.x = 0;
					frame.y++;

					if (frame.y > 3)
					{
						frame.y = 0;
					}
				}

			}
		}

		else
		{
			frame.x = 0;
			frame.y = 0;
			aniCount = 0;
		}

		if (direction == 0)
		{
			pump->FrameAlphaRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 10,
				(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 1, 0, 250);

			boiler->FrameAlphaRender(hdc, (((tp.x - 3) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 16,
				(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 250);

			image->FrameAlphaRender(hdc, (((tp.x - 7) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 10,
				(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, frame.x, frame.y, 250, true, false);
		}

		else if (direction == 1)
		{
			pump->FrameAlphaRender(hdc, (((tp.x - 5) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 10,
				(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 26, 3, 0, 250);

			boiler->FrameAlphaRender(hdc, (((tp.x - 5) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 10,
				(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 26, 0, 0, 250, true, false);

			image->FrameAlphaRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 20,
				(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, frame.x, frame.y, 250, false, false);
		}

		else if (direction == 2)
		{

			pump->FrameAlphaRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 35,
				(((tp.y - 6) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 14, 0, 0, 250);

			image->FrameAlphaRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 30,
				(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 20, frame.x, frame.y, 250, false, true);

			boiler->FrameAlphaRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 5,
				(((tp.y - 5) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 12, 0, 0, 250, false, true);
		}

		else if (direction == 3)
		{

			pump->FrameAlphaRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 50,
				(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 26, 2, 0, 250);


			image->FrameAlphaRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 45,
				(((tp.y - 5) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32), frame.x, frame.y, 250, false, false);

			boiler->FrameAlphaRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 20,
				(((tp.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32), 0, 0, 250, false, false);
		}

		if (!isFuelFilled)
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



			if (direction == 0)
			{
				warning->AlphaRender(hdc, (((tp.x - 7) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 45,
					(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, alpha, 1);
			}

			else if (direction == 1)
			{

				warning->AlphaRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32),
					(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, alpha, 1);
			}

			else if (direction == 2)
			{
				warning->AlphaRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 10,
					(((tp.y - 6) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 70, 0, 0, alpha, 1);
			}

			else if (direction == 3)
			{

				warning->AlphaRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 45,
					(((tp.y - 5) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32), 0, 0, alpha, 1);
			}


		}

	}




	if (isRectRender)
	{
		this->SelectBoxRender(hdc);
	}

	renderCount++;

	if (direction == 0)
	{
		if (renderCount >= 24)
		{
			renderCount = 0;
		}
	}

	else if (direction == 1)
	{
		if (renderCount >= 24)
		{
			renderCount = 0;
		}
	}

	else if (direction == 2)
	{
		if (renderCount >= 27)
		{
			renderCount = 0;
		}
	}

	else if (direction == 3)
	{
		if (renderCount >= 21)
		{
			renderCount = 0;
		}
	}



	//Rectangle(hdc, rect.left - g_pos.x + WINSIZE_X / 2, rect.top - g_pos.y + WINSIZE_Y / 2, rect.right - g_pos.x + WINSIZE_X / 2, rect.bottom - g_pos.y + WINSIZE_Y / 2);
}

void SteamEngine::SelectBoxRender(HDC hdc)
{
	if (!isSelectedClose)
	{
		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8,
			rect.top - g_pos.y + WINSIZE_Y / 2 + 8, 2, 0);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8,
			rect.top - g_pos.y + WINSIZE_Y / 2 + 8, 3, 0);

		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8,
			rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8, 2, 1);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8,
			rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8, 3, 1);
	}

	else
	{
		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8, rect.top - g_pos.y + WINSIZE_Y / 2 + 8,
			0, 0);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8, rect.top - g_pos.y + WINSIZE_Y / 2 + 8,
			1, 0);

		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8, rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8,
			0, 1);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8, rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8,
			1, 1);
	}
}

SteamEngine::SteamEngine(TILE_POINT _tp, int hp, int _direction)
{
	releaseCount = 0;
	direction = _direction;
	tp = _tp;
	Hp = hp;

	selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");
	pump = ImageManager::GetSingleton()->FindImage("offshore-pump");
	warning = ImageManager::GetSingleton()->FindImage("fuel-icon-red");

	alpha = 0;

	isSelected = false;
	isSelectedClose = false;
	renderCount = 0;
	isElec = false;

	frame.x = 0;
	frame.y = 0;

	fuel.name = COAL;
	fuel.num = 10;
	fuel.isStorage = true;

	pos.x = ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 15;
	pos.y = ((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 65;

	hPen = CreatePen(PS_SOLID, 3, RGB(193, 141, 3));
	hOldPen = (HPEN)SelectObject(GetDC(g_hWnd), hPen);

	if (direction == 0)
	{
		rect = { 32 * (tp.x - 7) - 30, 32 * (tp.y - 1) - 10, 32 * (tp.x + 1) - 30, 32 * (tp.y + 1) - 10 };
		image = ImageManager::GetSingleton()->FindImage("steam-engine-horizontal");
		boiler = ImageManager::GetSingleton()->FindImage("boiler-left");
		tempindex.x = 9;
		tempindex.y = 3;
		tempsize[0] = tempindex.x * 32 / 2;
		tempsize[1] = tempindex.y * 32 / 2;
		tempsize[2] = tempindex.x * 32;
		tempsize[3] = tempindex.y * 32;
	}

	else if (direction == 1)
	{
		rect = { 32 * (tp.x - 7), 32 * (tp.y - 1), 32 * (tp.x + 1), 32 * (tp.y + 1) };
		image = ImageManager::GetSingleton()->FindImage("steam-engine-horizontal");
		boiler = ImageManager::GetSingleton()->FindImage("boiler-left");
		tempindex.x = 8;
		tempindex.y = 3;
		tempsize[0] = tempindex.x * 32 / 2;
		tempsize[1] = tempindex.y * 32 / 2;
		tempsize[2] = tempindex.x * 32;
		tempsize[3] = tempindex.y * 32;
	}

	else if (direction == 2)
	{
		rect = { 32 * (tp.x - 1) - 30, 32 * (tp.y - 7), 32 * (tp.x + 1) - 30, 32 * (tp.y + 1) };
		image = ImageManager::GetSingleton()->FindImage("steam-engine-vertical");
		boiler = ImageManager::GetSingleton()->FindImage("boiler-down");
		tempindex.x = 3;
		tempindex.y = 9;
		tempsize[0] = tempindex.x * 32 / 2;
		tempsize[1] = tempindex.y * 32 / 2;
		tempsize[2] = tempindex.x * 32;
		tempsize[3] = tempindex.y * 32;
	}

	else
	{
		rect = { 32 * (tp.x - 1) - 10, 32 * (tp.y - 7) - 20, 32 * (tp.x + 1) - 10, 32 * (tp.y + 1) - 20 };
		image = ImageManager::GetSingleton()->FindImage("steam-engine-vertical");
		boiler = ImageManager::GetSingleton()->FindImage("boiler-down");
		tempindex.x = 3;
		tempindex.y = 9;
		tempsize[0] = tempindex.x * 32 / 2;
		tempsize[1] = tempindex.y * 32 / 2;
		tempsize[2] = tempindex.x * 32;
		tempsize[3] = tempindex.y * 32;
	}

	Tutorial::GetSingleton()->SucceedQuest_12();

}

SteamEngine::SteamEngine()
{

}

SteamEngine::~SteamEngine()
{
}
