#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Image.h"
class BasicSplitter : public GameNode
{
private:

	bool split;


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

	BasicSplitter(TILE_POINT _tp, int hp, int _direction)
	{
		releaseCount = 0;
		tp = _tp;
		Hp = hp;

		selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");
		//invenImage = ImageManager::GetSingleton()->FindImage("objectinven");
		scale = 1;

		isSelected = false;
		isSelectedClose = false;
		isRectRender = false;
		isWidthReverse = false;
		isHeightReverse = false;

		split = false;
		direction = _direction;
		if (_direction == 0)
		{
			image = ImageManager::GetSingleton()->FindImage("basic-splitter-east");
			rect = { 32 * (tp.x), 32 * (tp.y - 1), 32 * (tp.x + 1), 32 * (tp.y + 1) };

			ImageManager::GetSingleton()->FindImage("mini-splitter-icon")->
				FrameRender(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + 3 * tp.x, 50 + 3 * tp.y, 0, 0);
		}
		else if (_direction == 1)
		{
			image = ImageManager::GetSingleton()->FindImage("basic-splitter-west");
			rect = { 32 * (tp.x), 32 * (tp.y - 1), 32 * (tp.x + 1), 32 * (tp.y + 1) };

			ImageManager::GetSingleton()->FindImage("mini-splitter-icon")->
				FrameRender(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + 3 * tp.x, 50 + 3 * tp.y, 2, 0);
		}
		else if (_direction == 2)
		{
			image = ImageManager::GetSingleton()->FindImage("basic-splitter-north");
			rect = { 32 * (tp.x - 1), 32 * (tp.y), 32 * (tp.x + 1), 32 * (tp.y + 1) };

			ImageManager::GetSingleton()->FindImage("mini-splitter-icon")->
				FrameRender(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + 3 * tp.x, 50 + 3 * tp.y, 1, 0);
		}
		else
		{
			image = ImageManager::GetSingleton()->FindImage("basic-splitter-south");
			rect = { 32 * (tp.x - 1), 32 * (tp.y), 32 * (tp.x + 1), 32 * (tp.y + 1) };

			ImageManager::GetSingleton()->FindImage("mini-splitter-icon")->
				FrameRender(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + 3 * tp.x, 50 + 3 * tp.y, 3, 0);
		}

		ani = new Animation();
		ani->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
		ani->SetUpdateTime(FPS);
		ani->SetPlayFrame(false, true);
		ani->Start();
	}
	BasicSplitter();
	virtual ~BasicSplitter();
};

