#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Image.h"
class SteelBox : public GameNode
{
private:



public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SelectBoxRender(HDC hdc);
	void AddBox(Layer _name, int num);

	SteelBox(TILE_POINT _tp, int hp)
	{
		tp = _tp;
		Hp = hp;
		rect = { 32 * (tp.x), 32 * (tp.y), 32 * (tp.x + 1), 32 * (tp.y + 1) };
		image = ImageManager::GetSingleton()->FindImage("steel-chest-icon");
		selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");
		//invenImage = ImageManager::GetSingleton()->FindImage("objectinven");
		scale = 1;

		isSelected = false;
		isSelectedClose = false;
		isRectRender = false;
		isWidthReverse = false;
		isHeightReverse = false;
		

		for (int i = 0; i < 10; i++)
		{
			storage[i].isSelected = false;
			storage[i].isStorage = false;
			storage[i].name = EMPTY;
			storage[i].num = 0;
			storage[i].rc = { 0 };
		}

		ImageManager::GetSingleton()->FindImage("mini-steel-chest-icon")->
			Render(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + (int)(3 * tp.x + 1.5), 50 + (int)(3 * tp.y + 1.5));
	}
	SteelBox();
	virtual ~SteelBox();
};

