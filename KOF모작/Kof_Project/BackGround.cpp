#include "BackGround.h"
#include "Image.h"
//#include "SieKensou.h"
//#include "Athena.h"

// image.h  void FrameMapRender ¿¡  widthscale,heightscale Ãß°¡
// image.cpp void Image::FrameMapRender 


HRESULT BackGround::Init()
{
	posX = 0;
	posY = 0;
	mapSelectNum = 0;
	currentframeX = 0;
	currentframeY = 0;
	comTime = 0;
	scale = 1;
	gameProcess = 0;
	widthscale = 2.2f;
	heightscale = 2.2f;

	startScreen = new Image();
	selectScreen = new Image();
	selectBackground = new Image();
	img = new Image();

	startScreen->Init("Image/Background/startScreen.bmp", posX, posY, 768, 240, 1, 1, true, RGB(255, 0, 255));
	selectBackground->Init("Image/Background/select_background.bmp", posX, posY, 768, 240, 1, 1, true);

	selectScreen->Init("Image/Background/select_character.bmp", posX, posY, 1125, 380, 3, 1, false, RGB(255, 255, 255));

	srand(time(NULL));
	mapSelectNum = (rand() % 6);


	if (mapSelectNum == 0)
	{
		img->Init("Image/Background/seoul.bmp", posX, posY, 6144, 220, 8, 1, true, RGB(255, 0, 255));
		widthscale = 2.0f;
	}
	else if (mapSelectNum == 1)
	{
		img->Init("Image/Background/sign.bmp", posX, posY, 6016, 224, 8, 1, true, RGB(255, 0, 255));
	}
	else if (mapSelectNum == 2)
	{
		img->Init("Image/Background/suwon.bmp", posX, posY, 6016, 224, 8, 1, true, RGB(255, 0, 255));
	}
	else if (mapSelectNum == 3)
	{
		img->Init("Image/Background/monacoGP.bmp", posX, posY, 6016, 256, 8, 1, true, RGB(255, 0, 255));
	}
	else if (mapSelectNum == 4)
	{
		img->Init("Image/Background/neogeo.bmp", posX, posY, 6016, 224, 8, 1, true, RGB(255, 0, 255));
	}
	else
	{
		img->Init("Image/Background/realto.bmp", posX, posY, 6016, 224, 8, 1, true, RGB(255, 0, 255));
	}






	return S_OK;
}

void BackGround::Release()
{
	img->Release();
	delete img;

	selectScreen->Release();
	delete selectScreen;

	startScreen->Release();
	delete startScreen;
}

void BackGround::Update()
{

	if (img)
	{
		comTime++;

		if (comTime == 10)
		{
			comTime = 0;
			currentframeX++;

			if (currentframeX > img->GetmaxKeyFrameX())
			{
				currentframeX = 0;
				//currentframeY++;
			}

			if (currentframeX == 7)//&& currentframeY == 1
			{
				currentframeX = 0;
				//currentframeY = 0;
			}
		}
	}

}

void BackGround::Render(HDC hdc)
{


	if (gameProcess == 0)
	{
		if (startScreen)
		{
			startScreen->FrameRender(hdc, 0, 0, 0, 0, 2);
		}
	}


	if (gameProcess == 1)
	{
		if (selectBackground)
		{
			selectBackground->FrameRender(hdc, 0, 0, 0, 0, 2);
		}

		if (selectScreen)
		{
			selectScreen->FrameRender(hdc, 100, 50, 0, 0, 1);
			selectScreen->FrameRender(hdc, 575, 50, 1, 0, 1);
			selectScreen->FrameRender(hdc, 1050, 50, 2, 0, 1);
		}
	}

	else if (gameProcess == 2)
	{
		if (img)
		{
			img->FrameMapRender(hdc, posX, posY, currentframeX, currentframeY, widthscale, heightscale);
			//img->FrameRender(hdc, posX, posY, currentframeX, currentframeY, 2.2);
		}
	}







}

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}
