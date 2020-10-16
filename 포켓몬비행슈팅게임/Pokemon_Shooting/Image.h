#pragma once
#include "pch.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,
		FILE,
		EMPTY,
		END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;		// ���ҽ��� ������ ���̵�
		HDC		hMemDC;		// �׸��⸦ �ְ��ϴ� �ڵ�(�޸� ����)
		HDC		hBlendDC;
		HDC		hRotateDC;
		HDC		hReverseDC;

		HBRUSH hBrush;

		HBITMAP hBlendBit;
		HBITMAP	hBitmap;// �̹��� ����
		HBITMAP hRotateBit;
		HBITMAP hReverseBit;

		HBITMAP hOldBit;
		HBITMAP hOldBit2;// ���� �̹��� ����
		HBITMAP hOldBit3;
		HBITMAP hOldBit4;

		int		width;		// �̹��� ���� ũ��
		int		height;		// �̹��� ���� ũ��
		BYTE	loadType;	// �ε� Ÿ��

		float	x;					// ��� ��ġ ��ǥ
		float	y;					// ��� ��ġ ��ǥ
		int		currentKeyFrameX;	// ���� Ű������ �ε���
		int		currentKeyFrameY;
		int		maxKeyFrameX;		// �ִ� Ű������ ��
		int		maxKeyFrameY;
		int		keyFrameWidth;		// Ű������ �� ũ��
		int		keyFrameHeight;
		int		rotateMaxSize;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			hBlendDC = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			x = 0.0f;
			y = 0.0f;
			currentKeyFrameX = 0;
			currentKeyFrameY = 0;
			maxKeyFrameX = 0;
			maxKeyFrameY = 0;
			keyFrameWidth = 0;
			keyFrameHeight = 0;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;	// �̹������� ����ü ������
	char* fileName;			// ���� ��� + �̸�
	bool isTrans;			// ����ȭ ����
	COLORREF transColor;	// ����ȭ�� ��

	BLENDFUNCTION blendFunc;

	POINT point[3];
	RECT rec;

public:
	// �� ��Ʈ�� �̹����� �����.
	HRESULT Init(int width, int height);

	// ���ҽ��κ��� �����͸� �о �����.
	HRESULT Init(const DWORD resID, int width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �����͸� �о �����.
	HRESULT Init(const char* fileName, int width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// �̹��� + Ű������ �ʱ�ȭ
	HRESULT Init(const char* fileName, float x, float y,
		int width, int height,
		int keyFrameX, int keyFrameY,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// �޸� ����
	void Release();

	void Render(HDC hdc, int destX, int destY);
	void BgRender(HDC hdc, int destX, int destY, bool bg = true);
	void FrameRender(HDC hdc, int destX, int destY,
		int currentKeyFrameX, int currentKeyFrameY, float scale = 1.0f);

	// ���ķ���
	void AlphaRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, BYTE alpha = 255, float scale = 1.0f, float degree = 0.0f, bool isreverse = false);
	void LugiaDeathRender(HDC hdc, float destX, float destY, int widthpos, int heightpos, float scale = 1.0f);
	HDC GetMemDC() { return imageInfo->hMemDC; }

	int GetMaxKeyFrameX() { return imageInfo->maxKeyFrameX; }
	int GetMaxKeyFrameY() { return imageInfo->maxKeyFrameY; }


	Image();
	~Image();
};

