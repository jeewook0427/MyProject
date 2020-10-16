#pragma once
#include "GameNode.h"
#include "Image.h"
#include "Animation.h"

class ElectricFurnace: public GameNode
{
private:
	
	
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SelectBoxRender(HDC hdc);

	bool CheckMainTp(int _x, int _y)
	{
		if ((_x == tp.x) && (_y == tp.y))
		{
			return true;
		}
		return false;
	}

	ElectricFurnace(TILE_POINT _tp, int hp)
	{
		releaseCount = 0;
		tp = _tp;
		Hp = hp;
		rect = { 32 * (tp.x - 2), 32 * (tp.y - 2), 32 * (tp.x + 1), 32 * (tp.y + 1) };
		image = ImageManager::GetSingleton()->FindImage("electric-furnace");
		selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");
		invenImage = ImageManager::GetSingleton()->FindImage("objectinven");
		effectimg = ImageManager::GetSingleton()->FindImage("stone-furnace-fire");
		warning = ImageManager::GetSingleton()->FindImage("electricity-icon-yellow");

		isSelected = false;
		isSelectedClose = false;
		isRectRender = false;

		scale = 2.0f;
		renderCount = 0;
		updateCount = 0;

		isElec = false;

		material.isStorage = false;
		material.name = EMPTY;
		material.num = 0;

		product.isStorage = false;
		product.name = EMPTY;
		product.num = 0;

		fuelGage = 100;
		materialGage = 0;

		ani = new Animation();
		ani->Init(effectimg->GetWidth(), effectimg->GetHeight(), effectimg->GetFrameWidth(), effectimg->GetFrameHeight());
		ani->SetUpdateTime(FPS / 2);
		ani->SetPlayFrame(0, 2, false, true);
		ani->Start();

		ImageManager::GetSingleton()->FindImage("mini-furnace-icon")->
			Render(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + 3 * tp.x, 50 + 3 * tp.y);

	}
	ElectricFurnace() {};
	virtual ~ElectricFurnace() {};

};

