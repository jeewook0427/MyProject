#include "Image.h"
#include "Animation.h"

#pragma comment (lib, "msimg32.lib")


HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	// Blend
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBlendOldBit = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// Rotate
	int maxSize = width > height ? width : height;
	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBitmap = CreateCompatibleBitmap(hdc, maxSize * 2, maxSize * 2);
	imageInfo->hRotateOldBit = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBitmap);

	//Reverse

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hBlendBitmap == NULL
		|| imageInfo->hRotateBitmap == NULL)
	{
		// �޸� ����
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
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBlendOldBit = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// Rotate
	int maxSize = width > height ? width : height;
	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBitmap = CreateCompatibleBitmap(hdc, maxSize * 2, maxSize * 2);
	imageInfo->hRotateOldBit = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hBlendBitmap == NULL
		|| imageInfo->hRotateBitmap == NULL)
	{
		// �޸� ����
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
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	// �߰�
	imageInfo->x = x - (width / 2);
	imageInfo->y = y - (height / 2);
	imageInfo->currentKeyFrameX = 0;
	imageInfo->currentKeyFrameY = 0;
	imageInfo->maxKeyFrameX = keyFrameX - 1;
	imageInfo->maxKeyFrameY = keyFrameY - 1;
	imageInfo->keyFrameWidth = width / keyFrameX;
	imageInfo->keyFrameHeight = height / keyFrameY;

	isTrans = trans;
	this->transColor = transColor;

	// Blend
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBlendOldBit = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// Rotate
	int maxSize = width > height ? width : height;
	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBitmap = CreateCompatibleBitmap(hdc, maxSize * 2, maxSize * 2);
	imageInfo->hRotateOldBit = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hBlendBitmap == NULL
		|| imageInfo->hRotateBitmap == NULL)
	{
		// �޸� ����
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);

		// Blend
		SelectObject(imageInfo->hBlendDC, imageInfo->hBlendOldBit);
		DeleteObject(imageInfo->hBlendBitmap);
		DeleteDC(imageInfo->hBlendDC);

		// Rotate
		SelectObject(imageInfo->hRotateDC, imageInfo->hRotateOldBit);
		DeleteObject(imageInfo->hRotateBitmap);
		DeleteDC(imageInfo->hRotateDC);

		delete imageInfo;
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor
		);
	}
	else
	{
		// �޸𸮿� �ִ� �����͸� ȭ�鿡 ��Ӻ����Ѵ�.
		BitBlt(hdc,				// ���� ������ DC
			destX, destY,		// ���� ���� ��ġ
			imageInfo->width,	// �������� ����� ���� ũ��
			imageInfo->height,	// �������� ����� ���� ũ��
			imageInfo->hMemDC,	// ���� DC
			0, 0,				// �������� ���� ���� ��ġ
			SRCCOPY);			// ���� �ɼ�
	}

}

void Image::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),
			sourWidth, sourHeight,

			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight,
			transColor
		);
	}
	else
	{
		// �޸𸮿� �ִ� �����͸� ȭ�鿡 ��Ӻ����Ѵ�.
		BitBlt(hdc,							// ���� ������ DC
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),		// ���� ���� ��ġ
			sourWidth,						// �������� ����� ���� ũ��
			sourHeight,						// �������� ����� ���� ũ��
			imageInfo->hMemDC,				// ���� DC
			sourX, sourY,					// �������� ���� ���� ��ġ
			SRCCOPY);						// ���� �ɼ�
	}
}

void Image::Render(HDC hdc, int destX, int destY, int width, int height)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - width / 2,
			destY - height / 2,
			width, height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor
		);
	}
	else
	{
		StretchBlt(hdc,
			destX - width / 2,
			destY - height / 2,
			width, height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height,
			SRCCOPY);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY,
	int currentKeyFrameX, int currentKeyFrameY, float scale/* = 1.0f*/)
{
	// ���� Ű������ �ε����� �ִ� Ű������ �ε������� Ŭ ��
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
			destX - (imageInfo->keyFrameWidth / 2)*scale,
			destY - (imageInfo->keyFrameHeight / 2)*scale,
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
			destX - (imageInfo->keyFrameWidth / 2), destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			SRCCOPY);
	}

}

void Image::AlphaRender(HDC hdc, BYTE alpha)
{
	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			hdc, 0, 0, SRCCOPY);
		// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			transColor);
		// 3. blend DC�� ������ ������ DC�� ����
		AlphaBlend(hdc, 0, 0, imageInfo->width, imageInfo->height,
			imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
	else
	{
		AlphaBlend(hdc, 0, 0, imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
}

void Image::FrameAlphaRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, BYTE alpha, bool iswidthreverse, bool isheightreverse)
{
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;
	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans && iswidthreverse && isheightreverse)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2), SRCCOPY);

		// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hMemDC, imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			transColor);


		// 3. blend DC�� ������ ������ DC�� ����
		StretchBlt(imageInfo->hRotateDC, 0 + imageInfo->keyFrameWidth,
			0 + imageInfo->keyFrameHeight, -imageInfo->keyFrameWidth, -imageInfo->keyFrameHeight, imageInfo->hBlendDC,
			0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, SRCCOPY);

		AlphaBlend(hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hRotateDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			blendFunc);
	}

	else if (isTrans && isheightreverse)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		StretchBlt(imageInfo->hBlendDC, 0,
			0 + imageInfo->keyFrameHeight - 1, imageInfo->keyFrameWidth, -imageInfo->keyFrameHeight, hdc,
			destX - (imageInfo->keyFrameWidth / 2), destY - (imageInfo->keyFrameHeight / 2), imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, SRCCOPY);

		// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hMemDC, imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			transColor);


		// 3. blend DC�� ������ ������ DC�� ����


		StretchBlt(imageInfo->hRotateDC, 0,
			0 + imageInfo->keyFrameHeight - 1, imageInfo->keyFrameWidth, -imageInfo->keyFrameHeight, imageInfo->hBlendDC,
			0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, SRCCOPY);

		AlphaBlend(hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hRotateDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			blendFunc);
	}

	else if (isTrans && iswidthreverse)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		/*BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2), SRCCOPY);*/

		StretchBlt(imageInfo->hBlendDC, 0 + imageInfo->keyFrameWidth - 1,
			0, -imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, hdc,
			destX - (imageInfo->keyFrameWidth / 2), destY - (imageInfo->keyFrameHeight / 2), imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, SRCCOPY);

		// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hMemDC, imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			transColor);


		// 3. blend DC�� ������ ������ DC�� ����
		StretchBlt(imageInfo->hRotateDC, 0 + imageInfo->keyFrameWidth - 1,
			0, -imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, imageInfo->hBlendDC,
			0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, SRCCOPY);

		AlphaBlend(hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hRotateDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			blendFunc);
	}

	else if (isTrans)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2), SRCCOPY);

		// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hMemDC, imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			transColor);


		// 3. blend DC�� ������ ������ DC�� ����
		AlphaBlend(hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hBlendDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			blendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hMemDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			blendFunc);
	}
}
void Image::AlphaRender(HDC hdc, int destX, int destY, int width, int height, BYTE alpha)
{
	// ����
	blendFunc.SourceConstantAlpha = alpha;

	//if (isTrans)
	//{
	//	// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
	//	BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
	//		hdc,
	//		destX - (imageInfo->width / 2),
	//		destY - (imageInfo->height / 2), SRCCOPY);
	//	// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
	//	GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
	//		imageInfo->width, imageInfo->height,
	//		imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
	//		transColor);
	//	// 3. blend DC�� ������ ������ DC�� ����
	//	AlphaBlend(hdc,
	//		destX - (imageInfo->width / 2),
	//		destY - (imageInfo->height / 2),
	//		imageInfo->width, imageInfo->height,
	//		imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
	//		blendFunc);
	//}
	//else
	//{
	AlphaBlend(hdc,
		destX,
		destY,
		width, height,
		imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
		blendFunc);
	//}
}
void Image::FrameAlphaRenderAni(HDC hdc, int destX, int destY, int sourX, int sourY, BYTE alpha, bool iswidthreverse, bool isheightreverse)
{

	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans && iswidthreverse && isheightreverse)
	{
		BitBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, imageInfo->hMemDC, sourX,
			sourY, SRCCOPY);

		// 3. blend DC�� ������ ������ DC�� ����
		StretchBlt(imageInfo->hRotateDC, imageInfo->keyFrameWidth - 1, imageInfo->keyFrameHeight - 1, -imageInfo->keyFrameWidth, -imageInfo->keyFrameHeight, imageInfo->hBlendDC,
			0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, SRCCOPY);

		GdiTransparentBlt(hdc, destX - (imageInfo->keyFrameWidth / 2), destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hRotateDC, 0,
			0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			transColor);
	}

	else if (isTrans && isheightreverse)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		/*BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2), SRCCOPY);*/

			// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		BitBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, imageInfo->hMemDC, sourX,
			sourY, SRCCOPY);

		// 3. blend DC�� ������ ������ DC�� ����
		StretchBlt(imageInfo->hRotateDC, 0, imageInfo->keyFrameHeight - 1, imageInfo->keyFrameWidth, -imageInfo->keyFrameHeight, imageInfo->hBlendDC,
			0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, SRCCOPY);

		GdiTransparentBlt(hdc, destX - (imageInfo->keyFrameWidth / 2), destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hRotateDC, 0,
			0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			transColor);


		/*AlphaBlend(hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hRotateDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			blendFunc);*/
	}

	else if (isTrans && iswidthreverse)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		/*BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2), SRCCOPY);*/

			// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
			/*PatBlt(imageInfo->hBlendDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, RGB(255, 0, 255));

			GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
				imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
				imageInfo->hMemDC, sourX,
				sourY, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
				transColor);*/

		BitBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, imageInfo->hMemDC, sourX,
			sourY, SRCCOPY);

		// 3. blend DC�� ������ ������ DC�� ����
		StretchBlt(imageInfo->hRotateDC, 0 + imageInfo->keyFrameWidth - 1, 0, -imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, imageInfo->hBlendDC,
			0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, SRCCOPY);

		GdiTransparentBlt(hdc, destX - (imageInfo->keyFrameWidth / 2), destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hRotateDC, 0,
			0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			transColor);

		/*AlphaBlend(hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hRotateDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			blendFunc);*/
	}

	else if (isTrans)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
	/*	BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2), SRCCOPY);*/

			// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(hdc, destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hMemDC, sourX,
			sourY, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			transColor);


		//// 3. blend DC�� ������ ������ DC�� ����
		//AlphaBlend(hdc,
		//	destX - (imageInfo->keyFrameWidth / 2),
		//	destY - (imageInfo->keyFrameHeight / 2),
		//	imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
		//	imageInfo->hBlendDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
		//	blendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			imageInfo->hMemDC, 0, 0, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2), SRCCOPY);
		// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			transColor);
		// 3. blend DC�� ������ ������ DC�� ����
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
}

void Image::RocketAlphaRender(HDC hdc, int destX, int destY, float posy, int length, BYTE alpha)
{
	float posY;
	if (posy > length)
		posY = length;

	else
		posY = posy;
	
	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2), SRCCOPY);
		// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->width, imageInfo->height- length + posY,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height- length + posY,
			transColor);
		// 3. blend DC�� ������ ������ DC�� ����
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height- length + posY,
			imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height- length + posY,
			blendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
}


void Image::RotateRender(HDC hdc, double dblAngle,
	int destX, int destY, double dblSizeRatio/* = 1*/,
	HBITMAP hMaskBmp/* = NULL*/, int ixMask/* = 0*/, int iyMask/* = 0*/)
{
	int i;
	POINT apt[3] = { 0 };
	double dblWidth = (double)imageInfo->width * dblSizeRatio;
	double dblHeight = (double)imageInfo->height * dblSizeRatio;
	double ixRotate = (int)((double)(imageInfo->width / 2)*dblSizeRatio); // ũ�Ⱑ ���ϴ� �� ���
	double iyRotate = (int)((double)(imageInfo->height / 2)*dblSizeRatio);
	double dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
	dblRadian = dblAngle * PI / 180.0f;
	cosVal = cos(dblRadian), sinVal = sin(dblRadian);

	// 1. ȸ������ �������� �����ǥ�� ���ϰ�
	// 2. ȸ���� ��ġ��ǥ(�����ǥ)�� ���� ��
	// 3. ���� ���� ������ ��ǥ�� ����.
	for (i = 0; i < 3; i++)
	{
		if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  ������ �κ�
		else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up ������ �κ�
		else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low ������ �κ�
		dblxDest = dblx * cosVal - dbly * sinVal;
		dblyDest = dblx * sinVal + dbly * cosVal;
		dblxDest += ixRotate, dblyDest += iyRotate;
		apt[i].x = destX - (long)ixRotate + (long)dblxDest;
		apt[i].y = destY - (long)iyRotate + (long)dblyDest;
	}

	PlgBlt(hdc, apt, imageInfo->hMemDC, 0, 0,
		imageInfo->width, imageInfo->height, hMaskBmp, ixMask, iyMask);
}


void Image::FreeAxisRotateRender(HDC hdc, double dblAngle, int destX, int destY, int xAxis, int yAxis, double dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	int i;
	POINT apt[3] = { 0 };
	double dblWidth = (double)imageInfo->width * dblSizeRatio;
	double dblHeight = (double)imageInfo->height * dblSizeRatio;
	double ixRotate = (int)((double)xAxis*dblSizeRatio); // ũ�Ⱑ ���ϴ� �� ���
	double iyRotate = (int)((double)yAxis*dblSizeRatio);
	double dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
	dblRadian = dblAngle * PI / 180.0f;
	cosVal = cos(dblRadian), sinVal = sin(dblRadian);

	// 1. ȸ������ �������� �����ǥ�� ���ϰ�
	// 2. ȸ���� ��ġ��ǥ(�����ǥ)�� ���� ��
	// 3. ���� ���� ������ ��ǥ�� ����.
	for (i = 0; i < 3; i++)
	{
		if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  ������ �κ�
		else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up ������ �κ�
		else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low ������ �κ�
		dblxDest = dblx * cosVal - dbly * sinVal;
		dblyDest = dblx * sinVal + dbly * cosVal;
		dblxDest += ixRotate, dblyDest += iyRotate;
		apt[i].x = destX - (long)ixRotate + (long)dblxDest;
		apt[i].y = destY - (long)iyRotate + (long)dblyDest;
	}


	PlgBlt(hdc, apt, imageInfo->hMemDC, 0, 0,
		imageInfo->width, imageInfo->height, hMaskBmp, ixMask, iyMask);

}

void Image::AlphaRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, BYTE alpha, float scale, float degree)
{
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;

	//����
	blendFunc.SourceConstantAlpha = alpha;

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
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			hdc,
			destX - (imageInfo->rotateMaxSize / 2),
			destY - (imageInfo->rotateMaxSize / 2), SRCCOPY);
		//BitBlt(imageInfo->hBlendDC, 0, 0, WINSIZE_X, WINSIZE_Y, hdc, 0, 0, SRCCOPY);

		BitBlt(imageInfo->hRotateDC, 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize, hdc, destX - (imageInfo->rotateMaxSize / 2),
			destY - (imageInfo->rotateMaxSize / 2), SRCCOPY);

		RoatateFunction(degree, imageInfo->rotateMaxSize / 2, imageInfo->rotateMaxSize / 2, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, point);

		PlgBlt(imageInfo->hRotateDC, point, imageInfo->hMemDC,
			imageInfo->keyFrameWidth*currentKeyFrameX, imageInfo->keyFrameHeight*currentKeyFrameY,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, NULL, NULL, NULL);

		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->rotateMaxSize / 2),
			destY - (imageInfo->rotateMaxSize / 2),
			imageInfo->rotateMaxSize,
			imageInfo->rotateMaxSize,
			imageInfo->hRotateDC,
			0,
			0,
			imageInfo->rotateMaxSize,
			imageInfo->rotateMaxSize,
			transColor
		);

		/*AlphaBlend(hdc, destX - (imageInfo->rotateMaxSize / 2), destY - (imageInfo->rotateMaxSize / 2), imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			imageInfo->hBlendDC, 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize, blendFunc);*/

			/*char sZtext[256];
			wsprintf(sZtext, "destX : %d", destX - 50);
			TextOut(hdc, 10, 70, sZtext, strlen(sZtext));
			wsprintf(sZtext, "destY : %d", destY - 50);
			TextOut(hdc, 10, 90, sZtext, strlen(sZtext));
	*/


	//AlphaBlend(hdc, destX - (imageInfo->keyFrameWidth / 2), destY - (imageInfo->keyFrameHeight / 2), imageInfo->keyFrameWidth * scale, imageInfo->keyFrameHeight * scale,
		//imageInfo->hBlendDC, destX - (imageInfo->keyFrameWidth / 2), destY - (imageInfo->keyFrameHeight / 2), imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, blendFunc);


	// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
	// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
	// 3. blend DC�� ������ ������ DC�� ����


	}

	else
	{
		AlphaBlend(hdc, destX - (imageInfo->width / 2), destY - (imageInfo->height / 2), imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);
	}

}

void Image::AlphaRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, BYTE alpha, float scale)
{
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;

	//����
	blendFunc.SourceConstantAlpha = alpha;

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
		BitBlt(imageInfo->hRotateDC, 0, 0, imageInfo->keyFrameWidth*scale, imageInfo->keyFrameHeight*scale,
			hdc,
			destX - (imageInfo->keyFrameWidth / 2)*scale,
			destY - (imageInfo->keyFrameHeight / 2)*scale, SRCCOPY);
		//BitBlt(imageInfo->hBlendDC, 0, 0, WINSIZE_X, WINSIZE_Y, hdc, 0, 0, SRCCOPY);

		GdiTransparentBlt(
			imageInfo->hRotateDC,
			0,
			0,
			imageInfo->keyFrameWidth*scale,
			imageInfo->keyFrameHeight*scale,
			imageInfo->hMemDC,
			0,
			0,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			transColor);

		AlphaBlend(hdc, destX - (imageInfo->keyFrameWidth / 2)*scale, destY - (imageInfo->keyFrameHeight / 2)*scale, imageInfo->keyFrameWidth*scale, imageInfo->keyFrameHeight*scale,
			imageInfo->hRotateDC, 0, 0, (imageInfo->keyFrameWidth)*scale, (imageInfo->keyFrameHeight)*scale, blendFunc);




		/*char sZtext[256];
		wsprintf(sZtext, "destX : %d", destX - 50);
		TextOut(hdc, 10, 70, sZtext, strlen(sZtext));
		wsprintf(sZtext, "destY : %d", destY - 50);
		TextOut(hdc, 10, 90, sZtext, strlen(sZtext));
*/


//AlphaBlend(hdc, destX - (imageInfo->keyFrameWidth / 2), destY - (imageInfo->keyFrameHeight / 2), imageInfo->keyFrameWidth * scale, imageInfo->keyFrameHeight * scale,
	//imageInfo->hBlendDC, destX - (imageInfo->keyFrameWidth / 2), destY - (imageInfo->keyFrameHeight / 2), imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, blendFunc);


// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
// 3. blend DC�� ������ ������ DC�� ����


	}

	else
	{
		AlphaBlend(hdc, destX - (imageInfo->width / 2), destY - (imageInfo->height / 2), imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);
	}

}

void Image::CamaraRender(HDC hdc, float gposX, float gposY, float pposX, float pposY, int width, int height, float scale)
{
	PatBlt(hdc, 0, 0, width, height, BLACKNESS);

	StretchBlt(hdc, 0, 0, width, height, imageInfo->hMemDC,
		width/ 2 - width / (2 * scale) -(gposX-pposX), height / 2  - height / (2 * scale) - (gposY - pposY), width/scale, height/scale, SRCCOPY);
}

void Image::RotateAlphaRender(HDC hdc, double dblAngle, int destX, int destY, BYTE alpha, double dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2), SRCCOPY);

		// 2. �̹����� ȸ�����Ѽ� Rotate DC�� ����
		RECT rc = { 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize };
		HBRUSH hBrush = CreateSolidBrush(transColor);
		FillRect(imageInfo->hRotateDC, &rc, hBrush);
		DeleteObject(hBrush);

		RotateRender(imageInfo->hRotateDC, dblAngle,
			imageInfo->rotateMaxSize / 2, imageInfo->rotateMaxSize / 2);

		// 3. Rotate DC �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC,
			0, 0,
			imageInfo->width, imageInfo->height,

			imageInfo->hRotateDC,
			(imageInfo->rotateMaxSize / 2) - (imageInfo->width / 2),
			(imageInfo->rotateMaxSize / 2) - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			transColor);

		// 4. blend DC�� ������ ������ DC�� ����
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
}

void Image::AnimationRender(HDC hdc, int destX, int destY, Animation * ani)
{
	Render(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight);
}

void Image::ReverseAniRender(HDC hdc, int destX, int destY, bool iswidthreverse, bool isheightreverse, Animation * ani)
{
	FrameAlphaRenderAni(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, 255, iswidthreverse, isheightreverse);
}

Image::Image()
{
}


Image::~Image()
{
}
