#include "ElectricFurnace.h"

HRESULT ElectricFurnace::Init()
{
	return E_NOTIMPL;
}

void ElectricFurnace::Release()
{
	if (releaseCount == 0)
	{
		SAFE_DELETE(ani);
	}

	releaseCount++;
	if (releaseCount >= 9)
	{
		releaseCount = 0;
	}
}

void ElectricFurnace::Update()
{
	if (updateCount == 0)
	{
		ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

		//tileinfo[tp.y][tp.x].isElec = true;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (tileinfo[tp.y - i][tp.x - j].isElec)
				{
					isElec = true;
					goto skip0;
				}

				isElec = false;

			}
		}

	skip0:

		if ((material.name == IRON || material.name == COPPER) && (material.num > 0))
			isMaterialFilled = true;

		else
			isMaterialFilled = false;

		
		vecit = (*ObjectManager::GetSingleton()->FindObjectVec()).begin();	// 확인필요
		for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int j = 0; j < 3; j++)
				{
					if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == (tp.x - j)
						&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y - k))
					{
						if (CheckCollision(rect.left + 48, rect.top + 48, 96,	// 확인필요
							(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10))
						{
							if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRON)
							{
								if (material.name == IRON)
									material.num++;
								else
								{
									material.name = IRON;
									material.num = 1;
									material.isStorage = true;
								}
								(*ObjectManager::GetSingleton()->FindObjectPool(IRON)).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
								(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);

								goto skip;
							}

							else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPER)
							{
								if (material.name == COPPER)
									material.num++;
								else
								{
									material.name = COPPER;
									material.num = 1;
									material.isStorage = true;
								}
								(*ObjectManager::GetSingleton()->FindObjectPool(COPPER)).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
								(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);

								goto skip;
							}

							else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONPLATE)
							{
								if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
								{
									if (product.name == IRONPLATE)
										product.num++;
									else
									{
										product.name = IRONPLATE;
										product.num = 1;
										product.isStorage = true;
									}
									(*ObjectManager::GetSingleton()->FindObjectPool(IRONPLATE)).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
									(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);

									goto skip;
								}
							}


							else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERPLATE)
							{
								if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
								{
									if (product.name == COPPERPLATE)
										product.num++;
									else
									{
										product.name = COPPERPLATE;
										product.num = 1;
										product.isStorage = true;
									}
									(*ObjectManager::GetSingleton()->FindObjectPool(COPPERPLATE)).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
									(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);

									goto skip;
								}
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

		

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ELECTRICFURNACE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it2 = (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).begin(); it2 != (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).end(); it2++)
			{
				if (it2->second->GetCheckRender() && it2->second->GetIsElec() && it2->second->GetisMaterialFilled())
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
		if (checkRender && isElec && isMaterialFilled)
		{
			if (!soundPlay)
			{
				

				iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ELECTRICFURNACE);
				if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
				{
					for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).end(); it++)
					{
						it->second->SetSoundPlay(true);
					}
				}

				if (isPlay)
					SoundManager::GetSingleton()->Play("electricfurnace", 0.7f);
				soundPlay = true;

			}
		}
		else
		{
			if (!isPlay)
			{
				SoundManager::GetSingleton()->Stop("electricfurnace");
				soundPlay = false;
			}
		}

		if (isElec && isMaterialFilled)
		{
			materialGage += 45*TimeManager::GetSingleton()->GetDeltaTime();
			if (materialGage >= 100)
			{
				if (material.name == IRON)
				{

					if (product.name == IRONPLATE)
					{
						product.num++;
					}
					else
					{
						product.name = IRONPLATE;
						product.num = 1;
						product.isStorage = true;
					}


				}

				if (material.name == COPPER)
				{

					if (product.name == COPPERPLATE)
					{
						product.num++;
					}
					else
					{
						product.name = COPPERPLATE;
						product.num = 1;
						product.isStorage = true;
					}


				}
				materialGage = 0;
				material.num--;
				if (material.num <= 0)
				{
					material.name = EMPTY;
					material.num = 0;
					material.isStorage = false;
				}
			}

		}

		else
		{
			materialGage = 0;
			
		}

		if (abs(tp.x - (int)(g_pos.x) / 32) < 27 && abs(tp.y - (int)(g_pos.y) / 32) < 16)
		{
			if (PtInRect(&rect, mousepos))
			{
				isRectRender = true;

				if (((abs(rect.left - p_pos.x) < 64 && abs(rect.top - p_pos.y) < 64) || (abs(rect.left - p_pos.x) < 64 && abs(rect.bottom - p_pos.y) < 64))
					|| ((abs(rect.right - p_pos.x) < 64 && abs(rect.top - p_pos.y) < 64) || (abs(rect.right - p_pos.x) < 64 && abs(rect.bottom - p_pos.y) < 64)))
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
					Tutorial::GetSingleton()->SucceedQuest_9();
					AddInInventory(ELECTRICFURNACE, 1);

					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
						}
					}
					

					iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICMININGDRILL);
					if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
					{
						for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).end(); it++)
						{
							it->second->SetSoundPlay(false);
						}
					}
					
					SoundManager::GetSingleton()->Play("remove", 1.0f);
						

						
					
					

				}


			}

			else
			{
				isRectRender = false;
			}
		}
	}


	updateCount++;
	if (updateCount >= 9)
	{
		updateCount = 0;
	}
}

void ElectricFurnace::Render(HDC hdc)
{
	if (image  && renderCount == 0)
	{
		image->FrameRender(hdc, (((tp.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48,
			(((tp.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 48, frame.x, frame.y);

		if (abs(tp.x - (int)(g_pos.x) / 32) < 26 && abs(tp.y - (int)(g_pos.y) / 32) < 15)
			checkRender = true;
		else
			checkRender = false;

		if (isRectRender)
		{
			this->SelectBoxRender(hdc);
		}

		if (isElec && isMaterialFilled && checkRender)
		{
			effectimg->AnimationRender(hdc, (((tp.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48,
				(((tp.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 78, ani);
		}

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



			warning->AlphaRender(hdc, (((tp.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48,
				(((tp.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 48, 0, 0, alpha, 0.7);
		}

	}


	renderCount++;

	if (renderCount >= 9)
	{
		renderCount = 0;
	}
}

void ElectricFurnace::SelectBoxRender(HDC hdc)
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
