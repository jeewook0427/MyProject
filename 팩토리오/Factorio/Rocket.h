#pragma once
#include "GameNode.h"

class Image;
class Rocket : public GameNode
{
private:

	Image* rocketShadow;
	Image* rocket;
	Image* rocketFlame;
	Image* rocketDoorBack;
	Image* rocketDoorFront;
	Image* rocketHoleLight;
	Image* rocketEffect;
	Image* rocketHoleBase;
	Image* rocketSiloFront;
		
	float launchTime;

	int productCount;
	int rocketAlpha;
	float holeAlpha;
	
	
	float tempPosY;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SelectBoxRender(HDC hdc);
	virtual void RocketRender(HDC hdc);

	Rocket(TILE_POINT _tp, int hp);
	
	
	Rocket();
	virtual ~Rocket();
};

