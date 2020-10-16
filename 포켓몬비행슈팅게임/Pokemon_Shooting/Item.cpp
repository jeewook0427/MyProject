#include "Item.h"
#include "Image.h"
#include "macroFunction.h"

HRESULT Item::Init()
{
	pos.x = 0;
	pos.y = 0;
	angle = PI / 2.0f;
	speed = 60.0f;
	show = false;
	isbottom = false;
	istop = false;
	size = 20;

	ImageManager::GetSingleton()->AddImage("candy", "Image/candy.bmp", pos.x, pos.y, 27, 45, 1, 1, true, RGB(255, 0, 255));
	candy = ImageManager::GetSingleton()->FindImage("candy");


	return S_OK;
}

void Item::Release()
{


}

void Item::Update()
{
	if (!isbottom)
	{
		pos.y += speed * sinf(angle) *TimeManager::GetSingleton()->GetDeltaTime();
	}
	else if (istop)
	{
		pos.y += speed * sinf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
	}
	else
	{
		pos.y -= speed * sinf(angle) *TimeManager::GetSingleton()->GetDeltaTime();
	}


	if (pos.y <= 0)
	{
		istop = true;

	}
	else if (pos.y >= WINSIZE_Y)
	{
		isbottom = true;
	}


}

void Item::Render(HDC hdc)
{
	if (candy)
	{
		if (show)
		{
			candy->Render(hdc, pos.x, pos.y);
		}
			
	}
}

Item::Item()
{
}

Item::~Item()
{
}
