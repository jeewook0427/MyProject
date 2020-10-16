#include "BasicMiningDrill.h"
#include "Image.h"
#include "ProductCoal.h"
#include "Animation.h"

HRESULT BasicMiningDrill::Init()
{
	return E_NOTIMPL;
}

void BasicMiningDrill::Release()
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

void BasicMiningDrill::Update()
{
	if (updateCount == 0)
	{
		ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

		vecit = (*ObjectManager::GetSingleton()->FindObjectVec()).begin();
		for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int j = 0; j < 3; j++)
				{
					if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == (tp.x - j)
						&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y - k))
					{
						if (CheckCollision(rect.left + 48, rect.top + 48, 96,
							(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10))
						{
							if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
							{
								(*ObjectManager::GetSingleton()->FindObjectPool(COAL)).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
								(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);

								
							}
							goto skip1;
						}


					}
				}
			}
			vecit++;
		}
	skip1:

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
	
		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICMININGDRILL);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it2 = (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).begin(); it2 != (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).end(); it2++)
			{
				if (it2->second->GetCheckRender() && it2->second->GetIsElec())
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

		

		if (checkRender&&isElec)
		{
			if (!soundPlay)
			{
				iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICMININGDRILL);
				if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
				{
					for (it2 = (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).begin(); it2 != (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).end(); it2++)
					{
						it2->second->SetSoundPlay(true);
					}
				}
				if (isPlay)
					SoundManager::GetSingleton()->Play("electricminingdrill", 0.7f);
				soundPlay = true;

			}
		}
		else
		{
			if (!isPlay)
			{
				SoundManager::GetSingleton()->Stop("electricminingdrill");
				soundPlay = false;
			}
		}

		if (isElec)
		{		

			materialGage += 2;
			if (materialGage >= 100)
			{
				materialGage = 0;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
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
					Tutorial::GetSingleton()->SucceedQuest_9();
					AddInInventory(BASICMININGDRILL, 1);
					SoundManager::GetSingleton()->Stop("electricminingdrill");
										

					iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICMININGDRILL);
					if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
					{
						for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).end(); it++)
						{
							it->second->SetSoundPlay(false);
						}
					}
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
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

void BasicMiningDrill::Render(HDC hdc)
{
	
	if (image&& renderCount == 0)
	{

		if (abs(tp.x - (int)(g_pos.x) / 32) < 28 && abs(tp.y - (int)(g_pos.y) / 32) < 17)
			checkRender = true;
		else
			checkRender = false;


		if (isElec && checkRender)
			image->AnimationRender(hdc, (((tp.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 60,
			(((tp.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 46, ani);
		else
			image->FrameRender(hdc, (((tp.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 60,
			(((tp.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 46, 0, 0);



		if (isRectRender && checkRender)
		{
			this->SelectBoxRender(hdc);
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



			warning->AlphaRender(hdc, (((tp.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 40,
				(((tp.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 40, 0, 0, alpha, 0.7);
		}

	}


	renderCount++;

	if (renderCount >= 9)
	{
		renderCount = 0;
	}
}

void BasicMiningDrill::SelectBoxRender(HDC hdc)
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

BasicMiningDrill::BasicMiningDrill(TILE_POINT _tp, int hp)
{
	releaseCount = 0;
	tp = _tp;
	Hp = hp;
	rect = { 32 * (tp.x - 2), 32 * (tp.y - 2), 32 * (tp.x + 1), 32 * (tp.y + 1) };
	image = ImageManager::GetSingleton()->FindImage("basic-mining-drill-east");
	selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");
	invenImage = ImageManager::GetSingleton()->FindImage("objectinven");
	warning = ImageManager::GetSingleton()->FindImage("electricity-icon-yellow");

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

	alpha = 0;


	ImageManager::GetSingleton()->FindImage("mini-mining-drill-icon")->
		Render(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + 3 * tp.x, 50 + 3 * tp.y);

	ImageManager::GetSingleton()->FindImage("mini-mining-drill-icon")->
		Render(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + 3 * tp.x, 50 + 3 * tp.y);

}

BasicMiningDrill::BasicMiningDrill()
{
}

BasicMiningDrill::~BasicMiningDrill()
{
}
