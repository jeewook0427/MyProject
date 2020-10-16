#pragma once
#include "GameNode.h"

class ObjResource : public GameNode
{
private:
	TILE_POINT mainTp;
	Image* objResImg;
	RECT rc;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	bool CheckMainTp(int _x, int _y)
	{
		if ((_x == mainTp.x) && (_y == mainTp.y))
		{
			return true;
		}
		return false;
	}

	ObjResource(TILE_POINT _mainTp);
	virtual ~ObjResource();
};

