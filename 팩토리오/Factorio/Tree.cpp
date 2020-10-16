#include "Tree.h"
#include "Image.h"

HRESULT Tree::Init()
{
	return S_OK;
}

void Tree::Release()
{
}

void Tree::Update()
{
}

void Tree::Render(HDC hdc)
{
	if (renderCount == 0)
	{
		if (Hp == 0 && !isDelete)
		{
			tileinfo[tp.y][tp.x].obj = EMPTY;
			isDelete = true;
		}

		if (Hp > 0)
		{
			if (abs(tp.x - (int)(g_pos.x) / 32) < 30 && abs(tp.y - (int)(g_pos.y) / 32) < 18)
				checkRender = true;
			else
				checkRender = false;
		}

	}
	if (image && checkRender&&renderCount == 0 && Hp > 0)
		image->FrameRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32,
		((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 32, frame.x, frame.y);


	renderCount++;

	if (renderCount >= 2)
		renderCount = 0;



	//Rectangle(hdc, rect.left - g_pos.x + WINSIZE_X / 2, rect.top - g_pos.y + WINSIZE_Y / 2, rect.right - g_pos.x + WINSIZE_X / 2, rect.bottom - g_pos.y + WINSIZE_Y / 2);
}

void Tree::SelectBoxRender(HDC hdc)
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

void Tree::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, 1385, 275, 210, 221, 200);

	//Rectangle(hdc, 1400, 290, 1538, 428);
	image->FrameRender(hdc, 1469, 359, frame.x, frame.y);

	wsprintf(strText, "나무");
	TextOut(hdc, 1400, 436, strText, strlen(strText));
	wsprintf(strText, "수량: %d", Hp);
	TextOut(hdc, 1400, 461, strText, strlen(strText));

}

Tree::Tree()
{

}

Tree::~Tree()
{
}
