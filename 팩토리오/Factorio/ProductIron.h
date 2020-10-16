#pragma once
#include "GameNode.h"

class ProductIron : public GameNode
{
private:


public:
	virtual HRESULT Init(int x, int y);

	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SelectBoxRender(HDC hdc);


	ProductIron();
	virtual ~ProductIron();
};

