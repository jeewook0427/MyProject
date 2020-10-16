#pragma once
#include "GameNode.h"

class BurnerMiningDrill : public GameNode
{
private:
	GameNode* passObj;

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

	BurnerMiningDrill(TILE_POINT _tp, int hp);

	BurnerMiningDrill();
	virtual ~BurnerMiningDrill();
};

