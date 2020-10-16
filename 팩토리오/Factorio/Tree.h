#pragma once
#include "GameNode.h"

class Tree : public GameNode
{
private:
	Image* grayBox;
	char strText[256];

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SelectBoxRender(HDC hdc);
	virtual void InfoRender(HDC hdc);

	bool CheckMainTp(int _x, int _y)
	{
		if ((_x == tp.x) && (_y == tp.y))
		{
			return true;
		}
		return false;
	}

	Tree(TILE_POINT _tp, int hp)
	{

		tp = _tp;
		Hp = hp;
		rect = { 32 * tp.x, 32 * (tp.y), 32 * (tp.x + 1), 32 * (tp.y + 1) };
		image = ImageManager::GetSingleton()->FindImage("tree");
		selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");

		isSelected = false;
		isSelectedClose = false;
		renderCount = 0;
		isDelete = false;

		switch (Hp)
		{
		case 1:
			frame = { 2, 0 };
			break;
		case 2:
			frame = { 3, 0 };
			break;
		case 3:
			frame = { 1, 0 };
			break;
		case 4:
			frame = { 0, 0 };
			break;
		case 5:
			frame = { 4, 0 };
			break;
		}


		grayBox = ImageManager::GetSingleton()->FindImage("grayBox");
	}
	Tree();
	virtual ~Tree();
};

