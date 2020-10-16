#pragma once
#include "GameNode.h"

class AssemblingMachine : public GameNode
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void SelectBoxRender(HDC hdc);



	AssemblingMachine(TILE_POINT _tp, int hp);

	AssemblingMachine();
	virtual ~AssemblingMachine();
};

