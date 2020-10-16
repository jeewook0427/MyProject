#pragma once
#include "GameNode.h"

class SteamEngine;
class SmallElecTricPole : public GameNode
{
private:

	HPEN hPen, hOldPen, hPen2;
	int rendTime;


	

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SelectBoxRender(HDC hdc);


	
	SmallElecTricPole(TILE_POINT _tp, int hp);
	SmallElecTricPole();
	virtual ~SmallElecTricPole();
};

