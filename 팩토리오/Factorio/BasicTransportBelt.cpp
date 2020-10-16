#include "BasicTransportBelt.h"
#include "Image.h"

HRESULT BasicTransportBelt::Init()
{
	return S_OK;
}

void BasicTransportBelt::Release()
{
	SAFE_DELETE(ani);
}

void BasicTransportBelt::Update()
{
	ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

	
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

			if(isPlay)
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
				AddInInventory(BASICTRANSPORTBELT, 1);
				SoundManager::GetSingleton()->Stop("basictransportbelt");

				iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICTRANSPORTBELT);
				if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
				{
					for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).end(); it++)
					{
						it->second->SetSoundPlay(false);
					}
				}

				iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICSPLITTER);
				if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
				{
					for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).end(); it++)
					{
						it->second->SetSoundPlay(false);
					}
				}

				soundPlay = false;

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

void BasicTransportBelt::Render(HDC hdc)
{

	if (image)
	{
		if (abs(tp.x - (int)(g_pos.x) / 32) < 27 && abs(tp.y - (int)(g_pos.y) / 32) < 16)
			checkRender = true;
		else
			checkRender = false;

		if(checkRender)
			image->ReverseAniRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)+ 16,
				((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32)+16, isWidthReverse, isHeightReverse, ani);

		if (isRectRender && checkRender)
		{
			this->SelectBoxRender(hdc);
		}
	}


}

void BasicTransportBelt::SelectBoxRender(HDC hdc)
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

BasicTransportBelt::BasicTransportBelt()
{

}

BasicTransportBelt::~BasicTransportBelt()
{
}
