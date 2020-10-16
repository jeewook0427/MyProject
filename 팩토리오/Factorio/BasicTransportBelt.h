#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Image.h"
class BasicTransportBelt : public GameNode
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

	BasicTransportBelt(TILE_POINT _tp, int hp, int direction)
	{
		isPlay = false;
		Tutorial::GetSingleton()->SucceedQuest_7();

		tp = _tp;
		Hp = hp;
		rect = { 32 * (tp.x), 32 * (tp.y), 32 * (tp.x + 1), 32 * (tp.y + 1) };
		image = ImageManager::GetSingleton()->FindImage("basic-transport-belt");
		selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");
		//invenImage = ImageManager::GetSingleton()->FindImage("objectinven");
		scale = 1;

		isSelected = false;
		isSelectedClose = false;
		isRectRender = false;
		isWidthReverse = false;
		isHeightReverse = false;

		ani = new Animation();
		ani->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
		ani->SetUpdateTime(FPS);
		

		if (direction == 0 || direction == 1)
		{
			ani->SetPlayFrame(0, 15, false, true);
			if (direction==1)
				isWidthReverse = true;
		}

		else if (direction == 2 || direction == 3)
		{
			ani->SetPlayFrame(16, 31, false, true);
			if (direction == 3)
				isHeightReverse = true;
			
		}

		ani->Start();

		ImageManager::GetSingleton()->FindImage("mini-transport-belt-icon")->
			Render(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + (int)(3 * tp.x + 1.5), 50 + (int)(3 * tp.y + 1.5));

		Tutorial::GetSingleton()->SucceedQuest_7();
	}
	BasicTransportBelt();
	virtual ~BasicTransportBelt();
};

