#include "BasicSplitter.h"
#include "Image.h"

HRESULT BasicSplitter::Init()
{
	return S_OK;
}

void BasicSplitter::Release()
{
	if (releaseCount == 0)
	{
		SAFE_DELETE(ani);
	}

	releaseCount++;
	if (releaseCount >= 2)
	{
		releaseCount = 0;
	}
}

void BasicSplitter::Update()
{
	if (updateCount == 0)
	{
		ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

		
	
		for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
		{
			if (direction == 0 || direction == 1) // 오른쪽, 왼쪽
			{
				for (int k = 0; k < 2; k++)
				{
					for (int j = 0; j < 1; j++)
					{
						if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == (tp.x)
							&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y - k))

						{

							if (CheckCollision2(rect.left + 16, rect.top + 32, 32,64,
								(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 15,15))
							{
								if (split)
								{
									if (direction == 0)
										(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetPos({ (float)(rect.right + 1),
											(float)(rect.bottom - 16) });

									else
										(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetPos({ (float)(rect.left - 1),
											(float)(rect.bottom - 16) });
									split = false;
								}

								else
								{
									if (direction == 0)
										(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetPos({ (float)(rect.right + 1),
											(float)(rect.top + 16) });

									else
										(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetPos({ (float)(rect.left - 1),
											(float)(rect.top + 16) });

									split = true;
								}

								goto skip1;

							}

						}
					}
				}

			}

			else if (direction == 2 || direction == 3) // 위, 아래
			{
				for (int k = 0; k < 1; k++)
				{
					for (int j = 0; j < 2; j++)
					{
						if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == (tp.x - j)
							&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y)
							)
						{

							if (CheckCollision2(rect.left + 32, rect.top + 16, 64, 32,
								(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 15,15))
							{
								if (split)
								{
									if (direction == 2)
										(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetPos({ float(rect.left + 16),
											(float)(rect.top - 1) });
									else
										(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetPos({ float(rect.left + 16),
											(float)(rect.bottom + 1) });
									split = false;
								}

								else
								{
									if (direction == 2)
										(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetPos({ float(rect.right - 16),
											(float)(rect.top - 1) });
									else
										(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetPos({ float(rect.right - 16),
											(float)(rect.bottom + 1) });
									split = true;
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

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICTRANSPORTBELT);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).end(); it++)
			{
				if (it->second->GetCheckRender())
				{
					isPlay = true;
					soundPlay = it->second->GetSoundPlay();
					goto skip2;
				}

				else
				{
					isPlay = false;
				}

			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICSPLITTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).end(); it++)
			{
				if (it->second->GetCheckRender())
				{
					isPlay = true;
					soundPlay = it->second->GetSoundPlay();
					goto skip2;
				}

				else
				{
					isPlay = false;
				}

			}
		}

	skip2:

		if (checkRender)
		{
			if (!soundPlay)
			{
				iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICTRANSPORTBELT);
				if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
				{
					for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).end(); it++)
					{
						it->second->SetSoundPlay(true);

					}
				}

				iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICSPLITTER);
				if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
				{
					for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).end(); it++)
					{
						it->second->SetSoundPlay(true);

					}
				}

				if (isPlay)
					SoundManager::GetSingleton()->Play("basictransportbelt", 1.0f);

				soundPlay = true;

			}
		}
		if (!checkRender)
		{
			if (!isPlay)
			{
				SoundManager::GetSingleton()->Stop("basictransportbelt");
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
					AddInInventory(BASICSPLITTER, 1);

				
					SoundManager::GetSingleton()->Stop("basictransportbelt");
					iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICSPLITTER);
					if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
					{
						for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).end(); it++)
						{
							it->second->SetSoundPlay(false);
						}
					}

					SoundManager::GetSingleton()->Stop("basictransportbelt");
					iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICTRANSPORTBELT);
					if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
					{
						for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).end(); it++)
						{
							it->second->SetSoundPlay(false);
						}
					}
					
					if (direction == 0)
					{
						for (int i = 0; i < 2; i++)
						{
							for (int j = 0; j < 1; j++)
							{
								tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
							}
						}
					}

					else if (direction == 1)
					{
						for (int i = 0; i < 2; i++)
						{
							for (int j = 0; j < 1; j++)
							{
								tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
							}
						}
					}
					else if (direction == 2)
					{
						for (int i = 0; i < 1; i++)
						{
							for (int j = 0; j < 2; j++)
							{
								tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
							}
						}
					}
					else if (direction == 3)
					{
						for (int i = 0; i < 1; i++)
						{
							for (int j = 0; j < 2; j++)
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
		}
	
	}

	

	updateCount++;
	if (updateCount >= 2)
	{
		updateCount = 0;
	}
}

void BasicSplitter::Render(HDC hdc)
{
	if (renderCount == 0)
	{
		if (abs(tp.x - (int)(g_pos.x) / 32) < 28 && abs(tp.y - (int)(g_pos.y) / 32) < 17)
			checkRender = true;
		else
			checkRender = false;

		if (image && checkRender)
		{
			if (direction == 0)
				image->ReverseAniRender(hdc, (((tp.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 16,
				(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32, false, false, ani);

			else if (direction == 1)
				image->ReverseAniRender(hdc, (((tp.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 16,
				(((tp.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32, false, false, ani);

			else if (direction == 2)
				image->ReverseAniRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 38,
				(((tp.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, false, false, ani);

			else if (direction == 3)
				image->ReverseAniRender(hdc, (((tp.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 38,
				(((tp.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, false, false, ani);


			if (isRectRender)
			{
				this->SelectBoxRender(hdc);
			}
		}
	}

	renderCount++;
	if (renderCount >= 2)
	{
		renderCount = 0;
	}

	//Rectangle(hdc, rect.left - g_pos.x + WINSIZE_X / 2, rect.top - g_pos.y + WINSIZE_Y / 2, rect.right - g_pos.x + WINSIZE_X / 2, rect.bottom - g_pos.y + WINSIZE_Y / 2);
}

void BasicSplitter::SelectBoxRender(HDC hdc)
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

BasicSplitter::BasicSplitter()
{

}

BasicSplitter::~BasicSplitter()
{
}
