#include "Stone.h"
#include "Image.h"

int Stone::totalTileNum = 0;

HRESULT Stone::Init()
{
	return S_OK;
}

void Stone::Release()
{
}

void Stone::Update()
{

}

void Stone::Render(HDC hdc)
{
	if (Hp > 900)
	{
		frame = { 0,0 };
	}
	if (Hp > 700)
	{
		frame = { 0,2 };
	}
	if (Hp > 500)
	{
		frame = { 0,4 };
	}
	if (Hp <= 500)
	{
		frame = { 0,5 };
	}
	if (abs(tp.x - (int)(g_pos.x) / 32) < 26 && abs(tp.y - (int)(g_pos.y) / 32) < 15)
		checkRender = true;
	else
		checkRender = false;

	if (image && checkRender)
	{
		image->FrameRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 16,
			((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, frame.x, frame.y);
	}
}

void Stone::SelectBoxRender(HDC hdc)
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

void Stone::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, 1385, 275, 210, 125, 200);

	//Rectangle(hdc, 1400, 290, 1442, 332);
	image->FrameRender(hdc, 1421, 311, frame.x, frame.y);

	wsprintf(strText, "µ¹");
	TextOut(hdc, 1400, 340, strText, strlen(strText));
	wsprintf(strText, "¼ö·®: %d", Hp);
	TextOut(hdc, 1400, 365, strText, strlen(strText));

}

Stone::Stone()
{
}

Stone::~Stone()
{
}
