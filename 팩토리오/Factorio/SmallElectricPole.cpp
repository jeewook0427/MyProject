#include "SmallElecTricPole.h"
#include "SteamEngine.h"
#include "Image.h"

HRESULT SmallElecTricPole::Init()
{
	return S_OK;
}

void SmallElecTricPole::Release()
{
	SelectObject(GetDC(g_hWnd), hOldPen);
	DeleteObject(hOldPen);
	DeleteObject(hPen);
	DeleteObject(hPen2);
}

void SmallElecTricPole::Update()
{
	if (updateCount == 0)
	{
		isElec = false;
		steam = nullptr;
		
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (tileinfo[tp.y + 4 - i][tp.x + 4 - j].obj == STEAMENGINE)
				{
					if (ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)->find({ tp.x + 4 - j ,tp.y + 4 - i })->second->GetIsElec())
					{
						steam = ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)->find({ tp.x + 4 - j ,tp.y + 4 - i })->second;
						goto skip;
					}
					
					else
					{
						steam = nullptr;
					}
				}
				else if (tileinfo[tp.y + 4 - i][tp.x + 4 - j].obj == SMALLELECTRICPOLE)
				{
					if (!(i == 4 && j == 4))
					{
						if (ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y + 4 - i][tp.x + 4 - j].obj)->find({ tp.x + 4 - j ,tp.y + 4 - i })->second->GetSteamEngine()!=nullptr)
						{							
							steam = ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y + 4 - i][tp.x + 4 - j].obj)->find({ tp.x + 4 - j ,tp.y + 4 - i })->second->GetSteamEngine();
							if (steam->GetElecNum() == 0)
							{
								goto skip;
							}

							else
							{
								steam = nullptr;
							}
							
						}

						else
						{
							steam = nullptr;
						}
					}
					

					
				}

				
								
			}
		}

		
		
	skip:

		if (steam)
			isElec = true;

		else
			isElec = false;
			

		if (isElec)
		{
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					tileinfo[tp.y + 3 - i][tp.x + 3 - j].isElec = true;
				}
			}
		}

		else
		{
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					tileinfo[tp.y + 3 - i][tp.x + 3 - j].isElec = false;
				}
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
					AddInInventory(SMALLELECTRICPOLE, 1);
					Tutorial::GetSingleton()->SucceedQuest_9();

					for (int i = 0; i < 1; i++)
					{
						for (int j = 0; j < 1; j++)
						{
							tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
						}
					}

					for (int i = 0; i < 7; i++)
					{
						for (int j = 0; j < 7; j++)
						{
							tileinfo[tp.y + 3 - i][tp.x + 3 - j].isElec = false;
						}
					}
					
					iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(SMALLELECTRICPOLE);
					if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
					{
						for (it = (*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).end(); it++)
						{
							it->second->SetSteam(nullptr);
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

			// ÆÈ ¹æÇâÁ¶Àý


		}


	}
	

	
}

void SmallElecTricPole::Render(HDC hdc)
{
	if (Hp == 0)
	{
		tileinfo[tp.y][tp.x].obj = EMPTY;
	}

	if (Hp > 0)
	{
		if (abs(tp.x - (int)(g_pos.x) / 32) < 37 && abs(tp.y - (int)(g_pos.y) / 32) < 25)
			checkRender = true;
		else
			checkRender = false;
	}

	

	if (isElec)
	{
		rendTime++;
		if (rendTime > 10)
			rendTime = 0;

	}
	else
		rendTime = 0;
	

	if (checkRender)
	{
		pos.x = ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 15;
		pos.y = ((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 65;

		GameNode* temp;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (tileinfo[tp.y + 4 - i][tp.x + 4 - j].obj == SMALLELECTRICPOLE)
				{
					if (!(i == 4 && j == 4))
					{
						if (isElec)
						{
							if (rendTime % 10 < 5)
								SelectObject(hdc, hPen);

							else
								SelectObject(hdc, hPen2);
						}
						else
						{
							SelectObject(hdc, hPen);
						}

						temp = ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)->find({ tp.x + 4 - j, tp.y + 4 - i })->second;
						MoveToEx(hdc, pos.x, pos.y, NULL);
						LineTo(hdc, temp->GetPos().x, temp->GetPos().y);
						SelectObject(hdc, hOldPen);
					
					}

				}
			}
		}
	}


	if (image && checkRender && Hp > 0)
		image->FrameRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 45,
		((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 20, frame.x, frame.y);



	if (isRectRender)
	{
		this->SelectBoxRender(hdc);
	}


	

	//Rectangle(hdc, rect.left - g_pos.x + WINSIZE_X / 2, rect.top - g_pos.y + WINSIZE_Y / 2, rect.right - g_pos.x + WINSIZE_X / 2, rect.bottom - g_pos.y + WINSIZE_Y / 2);
}

void SmallElecTricPole::SelectBoxRender(HDC hdc)
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

SmallElecTricPole::SmallElecTricPole(TILE_POINT _tp, int hp)
{

	tp = _tp;
	Hp = hp;
	rect = { 32 * tp.x, 32 * (tp.y), 32 * (tp.x + 1), 32 * (tp.y + 1) };
	image = ImageManager::GetSingleton()->FindImage("small-electric-pole");
	selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");

	isSelected = false;
	isSelectedClose = false;
	renderCount = 0;

	frame.x = 3;
	frame.y = 0;

	pos.x = ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 15;
	pos.y = ((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 65;

	hPen = CreatePen(PS_SOLID, 3, RGB(193, 141, 3));
	hPen2 = CreatePen(PS_SOLID, 3, RGB(236, 236, 0));
	hOldPen = (HPEN)SelectObject(GetDC(g_hWnd), hPen);
	rendTime = 0;

	for (int i = 0; i < 5; i++)
	{
		if (Hp == i)
		{
			frame = { 0,i };
		}
	}

	steam = nullptr;

	ImageManager::GetSingleton()->FindImage("mini-electric-pole-icon")->
		Render(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + (int)(3 * tp.x + 1.5), 50 + (int)(3 * tp.y + 1.5));

	Tutorial::GetSingleton()->SucceedQuest_13();

}

SmallElecTricPole::SmallElecTricPole()
{

}

SmallElecTricPole::~SmallElecTricPole()
{
}
