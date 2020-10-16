#pragma once
#include "GameNode.h"
class CopperOre : public GameNode
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

	CopperOre(TILE_POINT _tp, int hp)
	{
		tp = _tp;
		Hp = hp;
		rect = { 32 * tp.x, 32 * tp.y, 32 * (tp.x + 1), 32 * (tp.y + 1) };
		image = ImageManager::GetSingleton()->FindImage("copper-ore");
		selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");

		isSelected = false;
		isSelectedClose = false;

		grayBox = ImageManager::GetSingleton()->FindImage("grayBox");
	}

	CopperOre();
	virtual ~CopperOre();
};

