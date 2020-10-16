#include "AssemblingMachine.h"
#include "Image.h"
#include "Animation.h"

HRESULT AssemblingMachine::Init()
{
	return S_OK;
}

void AssemblingMachine::Release()
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


void AssemblingMachine::Update()
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
							if (layer == IRONGEARWHEEL)
							{
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONPLATE)
								{
									if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
									{
										if (assemMaterial[0].name == (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())
											assemMaterial[0].num++;
										else
										{
											assemMaterial[0].name = (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer();
											assemMaterial[0].isStorage = true;
											assemMaterial[0].num = 1;
										}
										(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
										(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									}

									goto skip1;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONGEARWHEEL)
								{
									if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
									{
										if (product.name == (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())
											product.num++;
										else
										{
											product.name = (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer();
											product.isStorage = true;
											product.num = 1;
										}
										(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
										(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									}
									goto skip1;
								}

								else
								{
									(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
									(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									goto skip1;
								}
							}

							else if (layer == COPPERCABLE)
							{
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERPLATE)
								{
									if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
									{
										if (assemMaterial[0].name == (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())
											assemMaterial[0].num++;
										else
										{
											assemMaterial[0].name = (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer();
											assemMaterial[0].isStorage = true;
											assemMaterial[0].num = 1;
										}
										(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
										(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									}
									goto skip1;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERCABLE)
								{
									if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
									{
										if (product.name == (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())
											product.num++;
										else
										{
											product.name = (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer();
											product.isStorage = true;
											product.num = 1;
										}
										(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
										(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									}
									goto skip1;
								}

								else
								{
									(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
									(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									goto skip1;
								}
							}

							else if (layer == ELECTRONICCIRCUIT)
							{
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONPLATE)
								{
									if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
									{
										if (assemMaterial[0].name == (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())
											assemMaterial[0].num++;
										else
										{
											assemMaterial[0].name = (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer();
											assemMaterial[0].isStorage = true;
											assemMaterial[0].num = 1;
										}
										(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
										(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									}
									goto skip1;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERCABLE)
								{
									if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
									{
										if (assemMaterial[1].name == (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())
											assemMaterial[1].num++;
										else
										{
											assemMaterial[1].name = (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer();
											assemMaterial[1].isStorage = true;
											assemMaterial[1].num = 1;
										}
										(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
										(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									}
									goto skip1;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == ELECTRONICCIRCUIT)
								{
									if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
									{
										if (product.name == (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())
											product.num++;
										else
										{
											product.name = (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer();
											product.isStorage = true;
											product.num = 1;
										}
										(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
										(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									}
									goto skip1;
								}

								else
								{
									(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
									(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									goto skip1;
								}
							}

							else if (layer == ADVANCEDCIRCUIT)
							{
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == ELECTRONICCIRCUIT)
								{
									if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
									{
										if (assemMaterial[0].name == (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())
											assemMaterial[0].num++;
										else
										{
											assemMaterial[0].name = (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer();
											assemMaterial[0].isStorage = true;
											assemMaterial[0].num = 1;
										}
										(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
										(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									}
									goto skip1;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERCABLE)
								{
									if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
									{
										if (assemMaterial[1].name == (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())
											assemMaterial[1].num++;
										else
										{
											assemMaterial[1].name = (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer();
											assemMaterial[1].isStorage = true;
											assemMaterial[1].num = 1;
										}
										(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
										(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									}
									goto skip1;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == ADVANCEDCIRCUIT)
								{
									if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
									{
										if (product.name == (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())
											product.num++;
										else
										{
											product.name = (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer();
											product.isStorage = true;
											product.num = 1;
										}
										(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
										(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									}
									goto skip1;
								}

								else
								{
									(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
									(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);
									goto skip1;
								}
							}


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

		

		
		

		
		if (isElec)
		{			
			if (layer == IRONGEARWHEEL)
			{
				assemMaterial[1].name = EMPTY;
				assemMaterial[1].num = 0;
				assemMaterial[1].isStorage = false;

				if (assemMaterial[0].name == IRONPLATE)
				{
					isMaterialFilled = true;
					materialGage++;
					if (materialGage > 100)
					{
						materialGage = 0;
						assemMaterial[0].num--;

						if (assemMaterial[0].num <= 0)
						{
							assemMaterial[0].name = EMPTY;
							assemMaterial[0].isStorage = false;
							assemMaterial[0].num = 0;
						}

						if (product.name == layer)
						{
							product.num++;
						}

						else
						{
							product.isStorage = true;
							product.name = layer;
							product.num = 1;
						}
					}
				}

				else
				{
					isMaterialFilled = false;
					materialGage = 0;
				}
			}

			else if (layer == COPPERCABLE)
			{
				assemMaterial[1].name = EMPTY;
				assemMaterial[1].num = 0;
				assemMaterial[1].isStorage = false;

				if (assemMaterial[0].name == COPPERPLATE)
				{
					isMaterialFilled = true;
					materialGage++;


					if (materialGage > 100)
					{
						assemMaterial[0].num--;

						if (assemMaterial[0].num <= 0)
						{
							assemMaterial[0].name = EMPTY;
							assemMaterial[0].isStorage = false;
							assemMaterial[0].num = 0;
						}

						materialGage = 0;
						if (product.name == layer)
						{
							product.num++;
						}

						else
						{
							product.isStorage = true;
							product.name = layer;
							product.num = 1;
						}
					}
				}

				else
				{
					isMaterialFilled = false;
					materialGage = 0;
				}
			}

			else if (layer == ELECTRONICCIRCUIT)
			{
				if (assemMaterial[0].name == IRONPLATE && assemMaterial[1].name == COPPERCABLE)
				{
					isMaterialFilled = true;
					materialGage += 0.8;


					if (materialGage > 100)
					{
						assemMaterial[0].num--;
						assemMaterial[1].num--;

						if (assemMaterial[0].num <= 0)
						{
							assemMaterial[0].name = EMPTY;
							assemMaterial[0].isStorage = false;
							assemMaterial[0].num = 0;
						}

						if (assemMaterial[1].num <= 0)
						{
							assemMaterial[1].name = EMPTY;
							assemMaterial[1].isStorage = false;
							assemMaterial[1].num = 0;
						}

						materialGage = 0;
						if (product.name == layer)
						{
							product.num++;
						}

						else
						{
							product.isStorage = true;
							product.name = layer;
							product.num = 1;
						}
					}
				}

				else
				{
					isMaterialFilled = false;
					materialGage = 0;
				}
			}

			else if (layer == ADVANCEDCIRCUIT)
			{
				if (assemMaterial[0].name == ELECTRONICCIRCUIT && assemMaterial[1].name == COPPERCABLE)
				{
					isMaterialFilled = true;
					materialGage += 0.5;

					if (materialGage > 100)
					{
						assemMaterial[0].num--;
						assemMaterial[1].num--;

						if (assemMaterial[0].num <= 0)
						{
							assemMaterial[0].name = EMPTY;
							assemMaterial[0].isStorage = false;
							assemMaterial[0].num = 0;
						}

						if (assemMaterial[1].num <= 0)
						{
							assemMaterial[1].name = EMPTY;
							assemMaterial[1].isStorage = false;
							assemMaterial[1].num = 0;
						}

						materialGage = 0;
						if (product.name == layer)
						{
							product.num++;
						}

						else
						{
							product.isStorage = true;
							product.name = layer;
							product.num = 1;
						}
					}
				}

				else
				{
					isMaterialFilled = false;
					materialGage = 0;
				}
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ASSEMBLINGMACHINE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it2 = (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).begin(); it2 != (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).end(); it2++)
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

				for (int i = 0; i < 8; i++)
				{
					it2++;
				}

			}
		}

		if (checkRender&&isElec&&isMaterialFilled)
		{
			if (!soundPlay)
			{
				iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ASSEMBLINGMACHINE);
				if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
				{
					for (it2 = (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).begin(); it2 != (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).end(); it2++)
					{
						it2->second->SetSoundPlay(true);
					}
				}
				if (isPlay)
					SoundManager::GetSingleton()->Play("assemblingmachine", 1.0f);
				soundPlay = true;
			}

		}
		else
		{
			if (!isPlay)
			{
				SoundManager::GetSingleton()->Stop("assemblingmachine");
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
					AddInInventory(ASSEMBLINGMACHINE, 1);
					Tutorial::GetSingleton()->SucceedQuest_9();
					SoundManager::GetSingleton()->Stop("assemblingmachine");
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
						}
					}

					
					iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ASSEMBLINGMACHINE);
					if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
					{
						for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).end(); it++)
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

void AssemblingMachine::Render(HDC hdc)
{
	

	if (image && renderCount == 0)
	{
		if (abs(tp.x - (int)(g_pos.x) / 32) < 26 && abs(tp.y - (int)(g_pos.y) / 32) < 15)
			checkRender = true;
		else
			checkRender = false;

		if (checkRender)
		{
			if (isMaterialFilled && isElec)
				image->AnimationRender(hdc, (((tp.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 56,
				(((tp.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 40, ani);
			else
				image->FrameRender(hdc, (((tp.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 56,
				(((tp.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 40, frame.x, frame.y);
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

			warning->AlphaRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) - 12,
				((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 24, 0, 0, alpha, 0.8);
		}

		if (isRectRender && checkRender)
		{
			this->SelectBoxRender(hdc);
		}
	}



	renderCount++;

	if (renderCount >= 9)
	{
		renderCount = 0;
	}
}

void AssemblingMachine::SelectBoxRender(HDC hdc)
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

AssemblingMachine::AssemblingMachine(TILE_POINT _tp, int hp)
{
	releaseCount = 0;
	tp = _tp;
	Hp = hp;
	rect = { 32 * (tp.x - 2) - 2, 32 * (tp.y - 2), 32 * (tp.x + 1) - 2, 32 * (tp.y + 1) };
	image = ImageManager::GetSingleton()->FindImage("assembling-machine");
	selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");
	warning = ImageManager::GetSingleton()->FindImage("electricity-icon-yellow");

	assemMaterial[0].isStorage = false;
	assemMaterial[0].name = EMPTY;
	assemMaterial[0].num = 0;
	assemMaterial[1].isStorage = false;
	assemMaterial[1].name = EMPTY;
	assemMaterial[1].num = 0;

	materialGage = 0;

	product.isStorage = false;
	product.name = EMPTY;
	product.num = 0;

	alpha = 0;
	layer = IRONGEARWHEEL;

	isSelected = false;
	isSelectedClose = false;
	isRectRender = false;

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

	ImageManager::GetSingleton()->FindImage("mini-assembling-machine-icon")->
		Render(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + (int)(3 * tp.x - 1.5), 50 + (int)(3 * tp.y - 1.5));

	Tutorial::GetSingleton()->SucceedQuest_14();
}

AssemblingMachine::AssemblingMachine()
{

}

AssemblingMachine::~AssemblingMachine()
{
}
