#include "BurnerMiningDrill.h"
#include "Image.h"
#include "ProductCoal.h"
#include "Animation.h"

HRESULT BurnerMiningDrill::Init()
{
	return S_OK;
}

void BurnerMiningDrill::Release()
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

void BurnerMiningDrill::Update()
{

	if (updateCount == 0)
	{
		ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
		if ((fuel.name == TREE || fuel.name == COAL) && (fuel.num > 0))
			isFuelFilled = true;
		else
			isFuelFilled = false;

		
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
							if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
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

									
								}

								goto skip1;
							}
							
						}


					}
				}
			}
			vecit++;
		}
	skip1:

		map<TILE_POINT, GameNode*>::iterator it2;
		map<Layer, map<TILE_POINT, GameNode*> >::iterator iter;

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BURNERMININGDRILL);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it2 = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).begin(); it2 != (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).end(); it2++)
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
				map<TILE_POINT, GameNode*>::iterator it;
				map<Layer, map<TILE_POINT, GameNode*> >::iterator iter;

				iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BURNERMININGDRILL);
				if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
				{
					for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).end(); it++)
					{
						it->second->SetSoundPlay(true);
					}
				}

				if (isPlay)
					SoundManager::GetSingleton()->Play("burnerminingdrill", 0.7f);
				soundPlay = true;

			}
		}
		else
		{
			if (!isPlay )
			{
				SoundManager::GetSingleton()->Stop("burnerminingdrill");
				soundPlay = false;
			}
		}

		if (isFuelFilled)
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
			materialGage += 80*TimeManager::GetSingleton()->GetDeltaTime();
			if (materialGage >= 100)
			{
				materialGage = 0;
				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						switch (tileinfo[tp.y - i][tp.x - j].res)
						{
						case(COAL):
							if (tileinfo[tp.y - 1][tp.x + 1].obj == STONEFURNACE)
							{
								passObj = ObjectManager::GetSingleton()->FindGameObject(STONEFURNACE, { tp.x + 1, tp.y - 1 });
							}
							else if (tileinfo[tp.y - 1][tp.x + 1].obj == BURNERINSERTER)
							{
								passObj = ObjectManager::GetSingleton()->FindGameObject(BURNERINSERTER, { tp.x + 1, tp.y - 1 });
							}
							else if (tileinfo[tp.y - 1][tp.x + 1].obj == BURNERMININGDRILL)
							{
								passObj = ObjectManager::GetSingleton()->FindGameObject(BURNERMININGDRILL, { tp.x + 1, tp.y - 1 });
							}
							else
							{
								passObj = nullptr;
							}


							if (passObj != nullptr)
							{
								if (passObj->GetFuel()->name != COAL)
								{
									passObj->GetFuel()->name = COAL;
									passObj->GetFuel()->num = 1;
									passObj->GetFuel()->isStorage = true;
								}
								else if (passObj->GetFuel()->name == COAL)
								{
									passObj->GetFuel()->num++;
								}


							}
							else
							{
								GameNode* temp = nullptr;

								if ((*ObjectManager::GetSingleton()->FindObjectPool(COAL)).size() != 0)
								{
									temp = (*ObjectManager::GetSingleton()->FindObjectPool(COAL)).front();
									temp->Init(((tp.x + 1) * 32 + 16), ((tp.y - 1) * 32 + 16));
									ObjectManager::GetSingleton()->InsertVec(temp);
									(*ObjectManager::GetSingleton()->FindObjectPool(COAL)).pop();
								}

							}

							(*ObjectManager::GetSingleton()->FindObjectMap(COAL)).find({ tp.x - j, tp.y - i })->second->MinusHp();
							goto skip;

							break;


						case(IRON):
							if (tileinfo[tp.y - 1][tp.x + 1].obj == STONEFURNACE)
							{
								passObj = ObjectManager::GetSingleton()->FindGameObject(STONEFURNACE, { tp.x + 1, tp.y - 1 });
							}
							else
							{
								passObj = nullptr;
							}


							if (passObj != nullptr)
							{
								if (passObj->GetMeterial()->name != IRON)
								{
									passObj->GetMeterial()->name = IRON;
									passObj->GetMeterial()->num = 1;
									passObj->GetMeterial()->isStorage = true;
								}
								else if (passObj->GetMeterial()->name == IRON)
								{
									passObj->GetMeterial()->num++;
								}

							}

							else
							{
								GameNode* temp = nullptr;

								if ((*ObjectManager::GetSingleton()->FindObjectPool(IRON)).size() != 0)
								{
									temp = (*ObjectManager::GetSingleton()->FindObjectPool(IRON)).front();
									temp->Init(((tp.x + 1) * 32 + 16), ((tp.y - 1) * 32 + 16));
									ObjectManager::GetSingleton()->InsertVec(temp);
									(*ObjectManager::GetSingleton()->FindObjectPool(IRON)).pop();
								}

							}

							(*ObjectManager::GetSingleton()->FindObjectMap(IRON)).find({ tp.x - j, tp.y - i })->second->MinusHp();
							goto skip;

							break;


						case(COPPER):
							if (tileinfo[tp.y - 1][tp.x + 1].obj == STONEFURNACE)
							{
								passObj = ObjectManager::GetSingleton()->FindGameObject(STONEFURNACE, { tp.x + 1, tp.y - 1 });
							}
							else
							{
								passObj = nullptr;
							}


							if (passObj != nullptr)
							{
								if (passObj->GetMeterial()->name != COPPER)
								{
									passObj->GetMeterial()->name = COPPER;
									passObj->GetMeterial()->num = 1;
									passObj->GetMeterial()->isStorage = true;
								}
								else if (passObj->GetMeterial()->name == COPPER)
								{
									passObj->GetMeterial()->num++;
								}

							}

							else
							{
								GameNode* temp = nullptr;

								if ((*ObjectManager::GetSingleton()->FindObjectPool(COPPER)).size() != 0)
								{
									temp = (*ObjectManager::GetSingleton()->FindObjectPool(COPPER)).front();
									temp->Init(((tp.x + 1) * 32 + 16), ((tp.y - 1) * 32 + 16));
									ObjectManager::GetSingleton()->InsertVec(temp);
									(*ObjectManager::GetSingleton()->FindObjectPool(COPPER)).pop();
								}


							}

							(*ObjectManager::GetSingleton()->FindObjectMap(COPPER)).find({ tp.x - j, tp.y - i })->second->MinusHp();
							goto skip;

							break;

						case(STONE):
							GameNode* temp = nullptr;

							if ((*ObjectManager::GetSingleton()->FindObjectPool(STONE)).size() != 0)
							{
								temp = (*ObjectManager::GetSingleton()->FindObjectPool(STONE)).front();
								temp->Init(((tp.x + 1) * 32 + 16), ((tp.y - 1) * 32 + 16));
								ObjectManager::GetSingleton()->InsertVec(temp);
								(*ObjectManager::GetSingleton()->FindObjectPool(STONE)).pop();
							}

							(*ObjectManager::GetSingleton()->FindObjectMap(STONE)).find({ tp.x - j, tp.y - i })->second->MinusHp();
							goto skip;

							break;

							

						}
					}
				}
			}




		}

		else
		{
			fuelGage = 100;
			
			//materialGage = 0;
		}

	skip:
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
					AddInInventory(BURNERMININGDRILL, 1);
					Tutorial::GetSingleton()->SucceedQuest_9();
					SoundManager::GetSingleton()->Stop("burnerminingdrill");

					iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BURNERMININGDRILL);
					if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
					{
						for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).end(); it++)
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

				
					SoundManager::GetSingleton()->Play("remove", 1.0f);

					

					

				}
				/*if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
				{
					isInvenOpen = true;

				}*/

			}

			else
			{
				isRectRender = false;
			}
		}
	}

	/*if (isInvenOpen)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('E'))
		{
			isInvenOpen = false;
		}
	}*/
	updateCount++;
	if (updateCount >= 4)
	{
		updateCount = 0;
	}
}

void BurnerMiningDrill::Render(HDC hdc)
{
	

	if (image && renderCount == 0)
	{

		if (abs(tp.x - (int)(g_pos.x) / 32) < 26 && abs(tp.y - (int)(g_pos.y) / 32) < 15)
			checkRender = true;
		else
			checkRender = false;

		if (checkRender)
		{
			if (isFuelFilled)
				image->AnimationRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) - 32 + 81 / 2,
				((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 32 + 32, ani);
			else
				image->FrameRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) - 32 + 81 / 2,
				((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 32 + 32, frame.x, frame.y);
		}

		if (checkRender)
		{
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



				warning->AlphaRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) - 32 + 81 / 2,
					((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 32 + 32, 0, 0, alpha, 0.5);
			}
		}

		if (isRectRender && checkRender)
		{
			this->SelectBoxRender(hdc);
		}
	}

	/*if (isInvenOpen)
	{
		invenImage->AlphaRender(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, 150);
	}*/


	renderCount++;

	if (renderCount >= 4)
	{
		renderCount = 0;
	}
}

void BurnerMiningDrill::SelectBoxRender(HDC hdc)
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

BurnerMiningDrill::BurnerMiningDrill(TILE_POINT _tp, int hp)
{
	Tutorial::GetSingleton()->SucceedQuest_4();

	releaseCount = 0;
	tp = _tp;
	Hp = hp;
	rect = { 32 * (tp.x - 1), 32 * (tp.y - 1), 32 * (tp.x + 1), 32 * (tp.y + 1) };
	image = ImageManager::GetSingleton()->FindImage("burner-mining-drill-east");
	selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");
	invenImage = ImageManager::GetSingleton()->FindImage("objectinven");
	warning = ImageManager::GetSingleton()->FindImage("fuel-icon-red");

	alpha = 0;

	isSelected = false;
	isSelectedClose = false;
	isRectRender = false;
	//isInvenOpen = false;

	scale = 2.0f;
	renderCount = 0;
	updateCount = 0;

	direction = DR_UP;
	frame.x = 0;	frame.y = 0;

	ani = new Animation();
	ani->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	ani->SetUpdateTime(FPS / 2);
	ani->SetPlayFrame(false, true);
	ani->Start();

	ImageManager::GetSingleton()->FindImage("mini-mining-drill-icon")->
		Render(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + 3 * tp.x, 50 + 3 * tp.y);

	Tutorial::GetSingleton()->SucceedQuest_4();
}

BurnerMiningDrill::BurnerMiningDrill()
{

}

BurnerMiningDrill::~BurnerMiningDrill()
{
}
