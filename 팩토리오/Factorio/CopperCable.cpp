#include "CopperCable.h"
#include "Image.h"



HRESULT CopperCable::Init(int x, int y)
{
	pos.x = x;
	pos.y = y;
	image = ImageManager::GetSingleton()->FindImage("copper-cable-icon");
	layer = COPPERCABLE;
	isPicked = false;

	return S_OK;
}

void CopperCable::Release()
{
}

void CopperCable::Update()
{
	tp.x = (int)(pos.x / 32);
	tp.y = (int)(pos.y / 32);

	if (!isPicked)
	{
		if (tileinfo[(int)pos.y / 32][(int)pos.x / 32].obj == BASICTRANSPORTBELT || tileinfo[(int)pos.y / 32][(int)pos.x / 32].obj == BASICSPLITTER)
		{
			if (tileinfo[(int)pos.y / 32][(int)pos.x / 32].belt == BELTRIGHT)
			{
				pos.x += 40 * TimeManager::GetSingleton()->GetDeltaTime();
				if (tileinfo[(int)pos.y / 32][(int)pos.x / 32].obj != BASICSPLITTER)
					pos.y = (int)pos.y / 32 * 32 + 16;
			}

			else if (tileinfo[(int)pos.y / 32][(int)pos.x / 32].belt == BELTLEFT)
			{
				pos.x -= 40 * TimeManager::GetSingleton()->GetDeltaTime();
				if (tileinfo[(int)pos.y / 32][(int)pos.x / 32].obj != BASICSPLITTER)
					pos.y = (int)pos.y / 32 * 32 + 16;
			}

			else if (tileinfo[(int)pos.y / 32][(int)pos.x / 32].belt == BELTUP)
			{
				pos.y -= 40 * TimeManager::GetSingleton()->GetDeltaTime();
				if (tileinfo[(int)pos.y / 32][(int)pos.x / 32].obj != BASICSPLITTER)
					pos.x = (int)pos.x / 32 * 32 + 16;
			}

			else if (tileinfo[(int)pos.y / 32][(int)pos.x / 32].belt == BELTDOWN)
			{
				pos.y += 40 * TimeManager::GetSingleton()->GetDeltaTime();
				if (tileinfo[(int)pos.y / 32][(int)pos.x / 32].obj != BASICSPLITTER)
					pos.x = (int)pos.x / 32 * 32 + 16;
			}
		}
	}

	if (tileinfo[tp.y][tp.x].obj == EMPTY)
	{
		deleteTime += TimeManager::GetSingleton()->GetDeltaTime();

		if (deleteTime > 20)
		{
			isDelete = true;
		}
	}

}

void CopperCable::Render(HDC hdc)
{
	if (abs(pos.x - g_pos.x) < WINSIZE_X / 2 + 32 && abs(pos.y - g_pos.y) < WINSIZE_Y / 2 + 32)
		checkRender = true;
	else
		checkRender = false;

	if (image && checkRender)
		image->FrameRender(hdc, (pos.x - g_pos.x) + WINSIZE_X / 2, (pos.y - g_pos.y) + WINSIZE_Y / 2, 0, 0, 0.5);
}

void CopperCable::SelectBoxRender(HDC hdc)
{
}

CopperCable::CopperCable()
{
}

CopperCable::~CopperCable()
{
}
