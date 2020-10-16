#pragma once
#include "GameNode.h"

class SteamEngine : public GameNode
{
private:

	HPEN hPen, hOldPen;
	Image* boiler;
	Image* pump;

	POINT tempindex;
	int tempsize[4];
	float aniCount;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SelectBoxRender(HDC hdc);



	SteamEngine(TILE_POINT _tp, int hp, int _direction);
	SteamEngine();
	virtual ~SteamEngine();
};

