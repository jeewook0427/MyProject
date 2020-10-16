#include "StoneFernace.h"
#include "Image.h"

HRESULT StoneFernace::Init()
{
	return S_OK;
}

void StoneFernace::Release()
{
	if (releaseCount == 0)
	{
		SAFE_DELETE(ani);
	}

	releaseCount++;
	if (releaseCount >= 4)
	{
		releaseCount = 0;
	}
}

void StoneFernace::Update()
{
	if (updateCount == 0)
	{
		ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

		if ((fuel.name == TREE || fuel.name == COAL) && (fuel.name > 0))
			isFuelFilled = true;
		else
			isFuelFilled = false;

		if ((material.name == IRON || material.name == COPPER) && (material.num > 0))
			isMaterialFilled = true;

		else
			isMaterialFilled = false;

		//테스트용	

		
		vecit = (*ObjectManager::GetSingleton()->FindObjectVec()).begin();
		for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
		{
			for (int k = 0; k < 2; k++)
			{
				for (int j = 0; j < 2; j++)
				{
					if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == (tp.x - j)
						&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y - k))
					{
						if (CheckCollision(rect.left + 32, rect.top + 32, 64,
							(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10))
						{
							if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
							{
								if (fuel.name == COAL)
									fuel.num++;
								else
								{
									fuel.name = COAL;
									fuel.isStorage = true;
									fuel.num = 1;
								}
								(*ObjectManager::GetSingleton()->FindObjectPool(COAL)).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
								(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);

								goto skip;
							}

							else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRON)
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

		if (isFuelFilled && isMaterialFilled)
		{
			

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
			materialGage += 0.5;
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
			fuelGage = 100;
			materialGage = 0;
			
		}


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STONEFURNACE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it2 = (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).begin(); it2 != (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).end(); it2++)
			{
				if (it2->second->GetCheckRender() && it2->second->GetisFuelFilled() && it2->second->GetisMaterialFilled())
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

		if (checkRender&&isFuelFilled && isMaterialFilled)
		{
			if (!soundPlay)
			{
			
			
				iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STONEFURNACE);
				if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
				{
					for (it2 = (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).begin(); it2 != (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).end(); it2++)
					{
						it2->second->SetSoundPlay(true);
					}
				}
				if (isPlay)
					SoundManager::GetSingleton()->Play("stonefurnace", 1.0f);
				soundPlay = true;

			}
		}
		else
		{

			if (!isPlay)
			{
				SoundManager::GetSingleton()->Stop("stonefurnace");
				soundPlay = false;
			}
			
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
					AddInInventory(STONEFURNACE, 1);
					SoundManager::GetSingleton()->Stop("stonefurnace");
					
					map<TILE_POINT, GameNode*>::iterator it;
					map<Layer, map<TILE_POINT, GameNode*> >::iterator iter;

					iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STONEFURNACE);
					if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
					{
						for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).end(); it++)
						{
							it->second->SetSoundPlay(false);
						}
					}

					for (int i = 0; i < 2; i++)
					{
						for (int j = 0; j < 2; j++)
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
	if (updateCount >= 4)
	{
		updateCount = 0;
	}
}

void StoneFernace::Render(HDC hdc)
{


	if (abs(tp.x - (int)(g_pos.x) / 32) < 26 && abs(tp.y - (int)(g_pos.y) / 32) < 15)
		checkRender = true;
	else
		checkRender = false;

	if (image && checkRender && renderCount == 0)
	{
		image->FrameRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) - 32 + 81 / 2,
			((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 32 + 32, frame.x, frame.y);

		if (isRectRender)
		{
			this->SelectBoxRender(hdc);
		}

		if (isFuelFilled && isMaterialFilled)
		{
			effectimg->AnimationRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) - 32 + 26,
				((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 32 + 49, ani);
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



			warning->AlphaRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32),
				((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 32 + 32, 0, 0, alpha, 0.5);
		}
	}


	renderCount++;

	if (renderCount >= 4)
	{
		renderCount = 0;
	}


	//Rectangle(hdc, rect.left - g_pos.x + WINSIZE_X / 2, rect.top - g_pos.y + WINSIZE_Y / 2, rect.right - g_pos.x + WINSIZE_X / 2, rect.bottom - g_pos.y + WINSIZE_Y / 2);
}

void StoneFernace::SelectBoxRender(HDC hdc)
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

StoneFernace::StoneFernace()
{

}

StoneFernace::~StoneFernace()
{
}
