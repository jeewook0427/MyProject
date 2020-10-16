#pragma once
#include "GameNode.h"

class TileResource : public GameNode
{
private:
	TILE_POINT tp;
	int tileRes;
	int num;
	int gauge;
	RECT rc;
	Image* tileResImg;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	TileResource(TILE_POINT _tp);
	virtual ~TileResource();
};

