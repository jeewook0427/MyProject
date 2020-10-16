#pragma once
#include "GameNode.h"
class Coal : public GameNode
{
private:
	Image* grayBox;
	char strText[256];

public:
	static int totalTileNum;

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SelectBoxRender(HDC hdc);
	virtual void InfoRender(HDC hdc);

	Coal(TILE_POINT _tp, int hp)
	{
		tp = _tp;
		Hp = hp;
		rect = { 32 * tp.x, 32 * tp.y, 32 * (tp.x + 1), 32 * (tp.y + 1) };
		image = ImageManager::GetSingleton()->FindImage("coal-ore");
		selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");

		isSelected = false;
		isSelectedClose = false;

		grayBox = ImageManager::GetSingleton()->FindImage("grayBox");
	}

	Coal();
	virtual ~Coal();
};

