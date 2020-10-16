#pragma once
#include "GameNode.h"

class ProductCopper : public GameNode
{
private:


public:
	virtual HRESULT Init(int x, int y);

	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SelectBoxRender(HDC hdc);


	ProductCopper();
	virtual ~ProductCopper();
};

