#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		//메모리해제
		Release();
		return E_FAIL;
	}

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
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	isTrans = trans;
	this->transColor = transColor;
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		//메모리해제
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char * fileName, float x, float y, int width, int height, int keyFrameX, int keyFrameY, bool trans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	//추가
	imageInfo->x = x - (width / 2);
	imageInfo->y = y - (height / 2);
	imageInfo->currentKeyFrameX = 0;
	imageInfo->currentKeyFrameY = 0;
	imageInfo->maxKeyFrameX = keyFrameX - 1;
	imageInfo->maxKeyFrameY = keyFrameY - 1;
	imageInfo->KeyFrameWidth = width / keyFrameX;
	imageInfo->KeyFrameHeight = height / keyFrameY;

	isTrans = trans;
	this->transColor = transColor;
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		//메모리해제
		Release();
		return E_FAIL;
	}

	return E_NOTIMPL;
}

HRESULT Image::Init(int width, int height, bool trans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	isTrans = trans;
	this->transColor = transColor;

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		//메모리 해제
		Release();
		return E_FAIL;
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

		delete imageInfo;
	}


}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX, destY,
			imageInfo->width,
			imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			transColor
		);
	}

	else
	{
		//메모리에 있는 데이터를 화면에 고속복사한다.
		BitBlt(hdc,					// 목적지 DC 
			destX, destY,			// 복사 시작 위치
			imageInfo->width,		// 원본에서 복사될 가로 크기
			imageInfo->height,		// 원본에서 복사될 세로 크기

			imageInfo->hMemDC,		// 원본 DC 
			0, 0,					// 원본에서 복사 시작 위치 
			SRCCOPY);				// 복사 옵션
	}


}

void Image::FrameRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, float scale)
{
	//현재 키프레임 인덱스가 최대 키프레임 인덱스보다 클 때
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
			destX, destY,
			imageInfo->KeyFrameWidth*scale,
			imageInfo->KeyFrameHeight*scale,

			imageInfo->hMemDC,
			imageInfo->KeyFrameWidth*imageInfo->currentKeyFrameX,
			imageInfo->KeyFrameHeight*imageInfo->currentKeyFrameY,
			imageInfo->KeyFrameWidth,
			imageInfo->KeyFrameHeight,
			transColor
		);
	}

	else
	{
		BitBlt(hdc,
			destX, destY,
			imageInfo->KeyFrameWidth,
			imageInfo->KeyFrameHeight,

			imageInfo->hMemDC,
			imageInfo->KeyFrameWidth*imageInfo->currentKeyFrameX, imageInfo->KeyFrameHeight*imageInfo->currentKeyFrameY,
			SRCCOPY);
	}


}
//float widthscale, float heightscale 추가
void Image::FrameMapRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, float widthscale, float heightscale)
{
	//현재 키프레임 인덱스가 최대 키프레임 인덱스보다 클 때
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
			destX, destY,
			imageInfo->KeyFrameWidth*widthscale,
			imageInfo->KeyFrameHeight*heightscale,

			imageInfo->hMemDC,
			imageInfo->KeyFrameWidth*imageInfo->currentKeyFrameX,
			imageInfo->KeyFrameHeight*imageInfo->currentKeyFrameY,
			imageInfo->KeyFrameWidth,
			imageInfo->KeyFrameHeight,
			transColor
		);
	}

	else
	{
		BitBlt(hdc,
			destX, destY,
			imageInfo->KeyFrameWidth,
			imageInfo->KeyFrameHeight,

			imageInfo->hMemDC,
			imageInfo->KeyFrameWidth*imageInfo->currentKeyFrameX, imageInfo->KeyFrameHeight*imageInfo->currentKeyFrameY,
			SRCCOPY);
	}


}

void Image::FrameRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, float scale, bool isreverse)
{
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

	if (isreverse)
	{
		GdiTransparentBlt(
			//복사
			hdc,
			destX, destY,												// 복사 시작 위치								
			imageInfo->KeyFrameWidth * scale,							// 복사한 이미지의 크기
			imageInfo->KeyFrameHeight * scale,

			//원본
			imageInfo->hMemDC,
			imageInfo->KeyFrameWidth * imageInfo->currentKeyFrameX,		// 복사가 시작되는 좌표
			imageInfo->KeyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->KeyFrameWidth,									// 원본이미지를 자른 크기
			imageInfo->KeyFrameHeight,
			transColor);


		StretchBlt(
			//복사
			hdc,
			destX + imageInfo->KeyFrameWidth * scale,
			destY,
			-imageInfo->KeyFrameWidth * scale - 1,
			imageInfo->KeyFrameHeight * scale,

			//원본
			imageInfo->hMemDC,
			imageInfo->KeyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->KeyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->KeyFrameWidth,
			imageInfo->KeyFrameHeight,
			SRCCOPY);



	}
	else
	{
		BitBlt(hdc,
			destX, destY,
			imageInfo->KeyFrameWidth,
			imageInfo->KeyFrameHeight,
			imageInfo->hMemDC,
			imageInfo->KeyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->KeyFrameHeight * imageInfo->currentKeyFrameY,
			SRCCOPY);

		StretchBlt(
			//복사
			hdc,
			destX,
			destY,
			imageInfo->KeyFrameWidth * scale,
			imageInfo->KeyFrameHeight * scale,

			//원본
			imageInfo->hMemDC,
			imageInfo->KeyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->KeyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->KeyFrameWidth,
			imageInfo->KeyFrameHeight,
			SRCCOPY);

	}
}
void Image::FrameRender(HDC hdc, int destX, int destY, int width, int height, int startX, int startY, int currentKeyFrameX, int currentKeyFrameY, int KeyFrameX, int KeyFrameY, float scale)
{
	//현재 키프레임 인덱스가 최대 키프레임 인덱스보다 클 때
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;
	imageInfo->maxKeyFrameX = KeyFrameX - 1;
	imageInfo->maxKeyFrameY = KeyFrameY - 1;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->KeyFrameWidth = width / KeyFrameX;
	imageInfo->KeyFrameHeight = height / KeyFrameY;

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
			destX, destY,
			imageInfo->KeyFrameWidth*scale,
			imageInfo->KeyFrameHeight*scale,

			imageInfo->hMemDC,
			startX + imageInfo->KeyFrameWidth*imageInfo->currentKeyFrameX,
			startY + imageInfo->KeyFrameHeight*imageInfo->currentKeyFrameY,
			imageInfo->KeyFrameWidth,
			imageInfo->KeyFrameHeight,
			transColor
		);

	}

	else
	{
		BitBlt(hdc,
			destX, destY,
			imageInfo->KeyFrameWidth,
			imageInfo->KeyFrameHeight,

			imageInfo->hMemDC,
			imageInfo->KeyFrameWidth*imageInfo->currentKeyFrameX, imageInfo->KeyFrameHeight*imageInfo->currentKeyFrameY,
			SRCCOPY);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY, float scale)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX, destY,
			imageInfo->width * scale,
			imageInfo->height * scale,

			imageInfo->hMemDC,
			0,
			0,
			imageInfo->width* scale,
			imageInfo->height* scale,
			transColor);
	}
	else
	{
		BitBlt(hdc,
			destX, destY,
			imageInfo->KeyFrameWidth,
			imageInfo->KeyFrameHeight,
			imageInfo->hMemDC,
			imageInfo->KeyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->KeyFrameHeight * imageInfo->currentKeyFrameY,
			SRCCOPY);
	}
}



Image::Image()
{
}

Image::~Image()
{
}
