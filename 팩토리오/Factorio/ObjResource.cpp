#include "ObjResource.h"
#include "Image.h"

HRESULT ObjResource::Init()
{
	objResImg = ImageManager::GetSingleton()->FindImage("tree1");
	rc = { 32 * mainTp.x, 32 * (mainTp.y - 1), 32 * (mainTp.x + 1), 32 * (mainTp.y + 1) };
	return S_OK;
}

void ObjResource::Release()
{
}

void ObjResource::Update()
{
}

void ObjResource::Render(HDC hdc)
{
	objResImg->FrameRender(hdc, ((mainTp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) - 32,
		((mainTp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 32 * 2, 0, 0);

}

ObjResource::ObjResource(TILE_POINT _mainTp)
{
	mainTp = _mainTp;
}

ObjResource::~ObjResource()
{
}
