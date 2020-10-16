#pragma once
#include "GameNode.h"
class BurnerInserter : public GameNode
{
private:
	float angle; 

	vector<GameNode*> pickvec;
	Image* handBaseImage;
	Image* handClosedImage;
	Image* handOpenImage;
	const float handBaseAngle_InDr[4] = { 150.0f, 240.0f, 330.0f, 60.0f };//{ 180.0f, 300.0f, 0.0f, 60.0f };
	const float handOpenAngle_InDr[4] = { 180.0f, 240.0f, 0.0f, 120.0f };
	float handAngle;
	
	RECT handRect;
	FPOINT basepoint, basearmpoint;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SelectBoxRender(HDC hdc);
	

	BurnerInserter(TILE_POINT _tp, int hp);
	BurnerInserter();
	virtual ~BurnerInserter();
};

