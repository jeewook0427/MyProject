#include "Image.h"
#include "macroFunction.h"
#pragma comment (lib, "msimg32.lib")



HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBit = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	// Blend
	int maxSize = width > height ? width : height;
	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBit = CreateCompatibleBitmap(hdc, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize);
	imageInfo->hOldBit2 = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBit);

	// Rotate
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBit = CreateCompatibleBitmap(hdc, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize);
	imageInfo->hOldBit3 = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBit);


	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hBlendBit == NULL
		|| imageInfo->hRotateBit == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

HRESULT Image::Init(const DWORD resID, int width, int height, bool trans, COLORREF transColor)
{
	return E_NOTIMPL;
}

HRESULT Image::Init(const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	isTrans = trans;
	this->transColor = transColor;
	// Blend
	int maxSize = width > height ? width : height;
	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBit = CreateCompatibleBitmap(hdc, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize);
	imageInfo->hOldBit2 = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBit);

	// Rotate
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBit = CreateCompatibleBitmap(hdc, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize);
	imageInfo->hOldBit3 = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBit);


	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hBlendBit == NULL
		|| imageInfo->hRotateBit == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

HRESULT Image::Init(const char * fileName,
	float x, float y, int width, int height,
	int keyFrameX, int keyFrameY,
	bool trans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);
	imageInfo = new IMAGE_INFO;

	imageInfo->width = width;
	imageInfo->height = height;
	// 추가
	imageInfo->x = x - (width / 2);
	imageInfo->y = y - (height / 2);
	imageInfo->currentKeyFrameX = 0;
	imageInfo->currentKeyFrameY = 0;
	imageInfo->maxKeyFrameX = keyFrameX - 1;
	imageInfo->maxKeyFrameY = keyFrameY - 1;
	imageInfo->keyFrameWidth = width / keyFrameX;
	imageInfo->keyFrameHeight = height / keyFrameY;



	imageInfo->resID = 0;

	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hReverseDC = CreateCompatibleDC(hdc);

	//int maxSize = width > height ? width : height;
	int maxSize = imageInfo->keyFrameWidth > imageInfo->keyFrameHeight ?
		imageInfo->keyFrameWidth : imageInfo->keyFrameHeight;
	imageInfo->rotateMaxSize = maxSize * 4;

	rec.left = 0;
	rec.top = 0;
	rec.right = imageInfo->rotateMaxSize;
	rec.bottom = imageInfo->rotateMaxSize;

	imageInfo->hBlendBit = CreateCompatibleBitmap(hdc, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize); //WINSIZE_X, WINSIZE_Y);
	imageInfo->hRotateBit = CreateCompatibleBitmap(hdc, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize);
	imageInfo->hReverseBit = CreateCompatibleBitmap(hdc, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);

	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->hOldBit2 = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBit);
	imageInfo->hOldBit3 = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBit);
	imageInfo->hOldBit4 = (HBITMAP)SelectObject(
		imageInfo->hReverseDC, imageInfo->hReverseBit);

	imageInfo->hBrush = CreateSolidBrush(COLORREF(RGB(255, 0, 255)));
	FillRect(imageInfo->hRotateDC, &rec, imageInfo->hBrush);
	FillRect(imageInfo->hReverseDC, &rec, imageInfo->hBrush);

	isTrans = trans;
	this->transColor = transColor;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	for (int i = 0; i < 3; i++)
	{
		point[i].x = 0;
		point[i].y = 0;
	}
	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);

		SelectObject(imageInfo->hBlendDC, imageInfo->hOldBit2);
		DeleteObject(imageInfo->hBlendBit);
		DeleteDC(imageInfo->hBlendDC);

		SelectObject(imageInfo->hRotateDC, imageInfo->hOldBit3);
		DeleteObject(imageInfo->hRotateBit);
		DeleteDC(imageInfo->hRotateDC);

		DeleteObject(imageInfo->hBrush);
		delete imageInfo;
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	/*	imageInfo->hOldBit = (HBITMAP)SelectObject(
			imageInfo->hMemDC, imageInfo->hBitmap);*/

	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->width / 2), destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor
		);
	}
	else
	{
		// 메모리에 있는 데이터를 화면에 고속복사한다.
		BitBlt(hdc,				// 복사 목적지 DC
			destX, destY,		// 복사 시작 위치
			imageInfo->width,	// 원본에서 복사될 가로 크기
			imageInfo->height,	// 원본에서 복사될 세로 크기
			imageInfo->hMemDC,	// 원본 DC
			0, 0,				// 원본에서 복사 시작 위치
			SRCCOPY);			// 복사 옵션
	}


}

void Image::BgRender(HDC hdc, int destX, int  destY, bool bg)
{
	if (bg)
	{
		StretchBlt(hdc, 0, 0, imageInfo->width * 2, imageInfo->height * 2, imageInfo->hMemDC, 0, 2100 - destY,
			imageInfo->width, imageInfo->height, SRCCOPY);
	}
	else
	{
		GdiTransparentBlt(
			hdc,
			0, WINSIZE_Y - destY,
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor
		);
	}


}

void Image::FrameRender(HDC hdc, int destX, int destY,
	int currentKeyFrameX, int currentKeyFrameY, float scale/* = 1.0f*/)
{

	/*imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);*/

		// 현재 키프레임 인덱스가 최대 키프레임 인덱스보다 클 때
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;

	if (imageInfo->currentKeyFrameX > imageInfo->maxKeyFrameX)
	{
		imageInfo->currentKeyFrameX = imageInfo->maxKeyFrameX;
	}
	if (imageInfo->currentKeyFrameY > imageInfo->maxKeyFrameY)
	{
		imageInfo->currentKeyFrameY = imageInfo->maxKeyFrameY;
	}

	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth * scale,
			imageInfo->keyFrameHeight * scale,

			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			transColor
		);
	}
	else
	{
		BitBlt(hdc,
			destX, destY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			SRCCOPY);
	}



}

void Image::AlphaRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, BYTE alpha, float scale, float degree, bool isreverse)
{
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;

	//투명도
	blendFunc.SourceConstantAlpha = alpha;

	if (imageInfo->currentKeyFrameX > imageInfo->maxKeyFrameX)
	{
		imageInfo->currentKeyFrameX = imageInfo->maxKeyFrameX;
	}
	if (imageInfo->currentKeyFrameY > imageInfo->maxKeyFrameY)
	{
		imageInfo->currentKeyFrameY = imageInfo->maxKeyFrameY;
	}


	if (isTrans && !isreverse)
	{



		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			hdc,
			destX - (imageInfo->rotateMaxSize / 2),
			destY - (imageInfo->rotateMaxSize / 2), SRCCOPY);

		BitBlt(imageInfo->hRotateDC, 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize, hdc, destX - (imageInfo->rotateMaxSize / 2),
			destY - (imageInfo->rotateMaxSize / 2), SRCCOPY);

		RoatateFunction(degree, imageInfo->rotateMaxSize / 2, imageInfo->rotateMaxSize / 2, imageInfo->keyFrameWidth*scale, imageInfo->keyFrameHeight*scale, point);

		PlgBlt(imageInfo->hRotateDC, point, imageInfo->hMemDC,
			imageInfo->keyFrameWidth*currentKeyFrameX, imageInfo->keyFrameHeight*currentKeyFrameY,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, NULL, NULL, NULL);

		GdiTransparentBlt(
			imageInfo->hBlendDC,
			0,
			0,
			imageInfo->rotateMaxSize,
			imageInfo->rotateMaxSize,
			imageInfo->hRotateDC,
			0,
			0,
			imageInfo->rotateMaxSize,
			imageInfo->rotateMaxSize,
			transColor
		);

		AlphaBlend(hdc, destX - (imageInfo->rotateMaxSize / 2), destY - (imageInfo->rotateMaxSize / 2), imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			imageInfo->hBlendDC, 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize, blendFunc);




		// 1. 목적지 DC에 그려져 있는 내용을 blend DC에 복사
		// 2. 출력할 이미지를 blend DC에 지정한 색상을 제외해서 복사
		// 3. blend DC에 내용을 목적지 DC에 복사


	}

	else if (isTrans && isreverse)
	{
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			hdc,
			destX - (imageInfo->rotateMaxSize / 2),
			destY - (imageInfo->rotateMaxSize / 2), SRCCOPY);

		BitBlt(imageInfo->hRotateDC, 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize, hdc, destX - (imageInfo->rotateMaxSize / 2),
			destY - (imageInfo->rotateMaxSize / 2), SRCCOPY);


		RoatateFunction(degree, imageInfo->rotateMaxSize / 2, imageInfo->rotateMaxSize / 2, imageInfo->keyFrameWidth*scale, imageInfo->keyFrameHeight*scale, point);

		PlgBlt(imageInfo->hReverseDC, point, imageInfo->hMemDC,
			imageInfo->keyFrameWidth*currentKeyFrameX, imageInfo->keyFrameHeight*currentKeyFrameY,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, NULL, NULL, NULL);

		StretchBlt(imageInfo->hRotateDC, imageInfo->rotateMaxSize - 1, 0, -imageInfo->rotateMaxSize, imageInfo->rotateMaxSize, imageInfo->hReverseDC, 0, 0,
			imageInfo->rotateMaxSize, imageInfo->rotateMaxSize, SRCCOPY);

		GdiTransparentBlt(
			imageInfo->hBlendDC,
			0,
			0,
			imageInfo->rotateMaxSize,
			imageInfo->rotateMaxSize,
			imageInfo->hRotateDC,
			0,
			0,
			imageInfo->rotateMaxSize,
			imageInfo->rotateMaxSize,
			transColor
		);

		AlphaBlend(hdc, destX - (imageInfo->rotateMaxSize / 2), destY - (imageInfo->rotateMaxSize / 2), imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			imageInfo->hBlendDC, 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize, blendFunc);
	}

	else
	{
		AlphaBlend(hdc, destX - (imageInfo->width / 2), destY - (imageInfo->height / 2), imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);
	}

}

void Image::LugiaDeathRender(HDC hdc, float destX, float destY, int widthpos, int heightpos, float scale)
{

	if (imageInfo->currentKeyFrameX > imageInfo->maxKeyFrameX)
	{
		imageInfo->currentKeyFrameX = imageInfo->maxKeyFrameX;
	}
	if (imageInfo->currentKeyFrameY > imageInfo->maxKeyFrameY)
	{
		imageInfo->currentKeyFrameY = imageInfo->maxKeyFrameY;
	}


	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (2 * scale),
			destY - (2 * scale),
			4 * scale,
			4 * scale,
			imageInfo->hMemDC,
			(widthpos * 4) + 193,
			(heightpos * 4),
			4,
			4,
			transColor
		);






		// 1. 목적지 DC에 그려져 있는 내용을 blend DC에 복사
		// 2. 출력할 이미지를 blend DC에 지정한 색상을 제외해서 복사
		// 3. blend DC에 내용을 목적지 DC에 복사


	}


	else
	{
		AlphaBlend(hdc, destX - (imageInfo->width / 2), destY - (imageInfo->height / 2), imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);
	}
}

Image::Image()
{
}


Image::~Image()
{
}
