#include "TileResource.h"
#include "Image.h"
HRESULT TileResource::Init()
{
	tileResImg = ImageManager::GetSingleton()->FindImage("coal");
	rc = { 32 * tp.x, 32 * tp.y, 32 * (tp.x + 1), 32 * (tp.y + 1) };

	return S_OK;
}

void TileResource::Release()
{
}

void TileResource::Update()
{
}

void TileResource::Render(HDC hdc)
{
	tileResImg->FrameRender(hdc, ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32),
		((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32), 0, 0);
}

TileResource::TileResource(TILE_POINT _tp)
{
	tp = _tp;
}

TileResource::~TileResource()
{
}
