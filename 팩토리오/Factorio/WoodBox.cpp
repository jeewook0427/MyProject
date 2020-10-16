#include "WoodBox.h"
#include "Image.h"

HRESULT WoodBox::Init()
{
	return S_OK;
}

void WoodBox::Release()
{

}

void WoodBox::Update()
{
	
	vecit = (*ObjectManager::GetSingleton()->FindObjectVec()).begin();
	for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
	{
		if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == (tp.x)
			&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y))
		{
			if (CheckCollision(rect.left + 16, rect.top + 16, 32,
				(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10))
			{
				AddBox((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer(), 1);

				(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
				(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);



				goto skip1;


			}

		}


		vecit++;
	}
skip1:

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
				AddInInventory(WOODENCHEST, 1);

				for (int i = 0; i < 1; i++)
				{
					for (int j = 0; j < 1; j++)
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

void WoodBox::Render(HDC hdc)
{
	if (abs(tp.x - (int)(g_pos.x) / 32) < 26 && abs(tp.y - (int)(g_pos.y) / 32) < 15)
		checkRender = true;
	else
		checkRender = false;

	if (image && checkRender)
	{
		image->FrameRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 16,
			((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0);

		if (isRectRender)
		{
			this->SelectBoxRender(hdc);
		}
	}



	//Rectangle(hdc, rect.left - g_pos.x + WINSIZE_X / 2, rect.top - g_pos.y + WINSIZE_Y / 2, rect.right - g_pos.x + WINSIZE_X / 2, rect.bottom - g_pos.y + WINSIZE_Y / 2);
}

void WoodBox::SelectBoxRender(HDC hdc)
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


void WoodBox::AddBox(Layer _name, int num)
{
	bool isExist = false;

	for (int i = 0; i < 5; i++)
	{
		if (storage[i].name == _name)
		{
			isExist = true;
		}


	}

	for (int i = 0; i < 5; i++)
	{
		if (isExist)
		{
			if (storage[i].name == _name && storage[i].num <= 999)
			{
				storage[i].num++;
				goto skip;
			}


		}

		else
		{
			if (!storage[i].isStorage)
			{
				storage[i].name = _name;
				storage[i].num += num;
				storage[i].isStorage = true;
				goto skip;
			}
		}


	}

skip:
	{}
}

WoodBox::WoodBox()
{

}

WoodBox::~WoodBox()
{
}
