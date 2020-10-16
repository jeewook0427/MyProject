#pragma once
#include "pch.h"

class Animation;
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
		HBITMAP	hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		int		width;		// �̹��� ���� ũ��
		int		height;		// �̹��� ���� ũ��
		BYTE	loadType;	// �ε� Ÿ��

		HDC		hBlendDC;		// �׸��⸦ �ְ��ϴ� �ڵ�(�޸� ����)
		HBITMAP	hBlendBitmap;	// �̹��� ����
		HBITMAP hBlendOldBit;	// ���� �̹��� ����

		HDC		hRotateDC;		// �׸��⸦ �ְ��ϴ� �ڵ�(�޸� ����)
		HBITMAP	hRotateBitmap;	// �̹��� ����
		HBITMAP hRotateOldBit;	// ���� �̹��� ����

		HDC		hReverseDC;		// �׸��⸦ �ְ��ϴ� �ڵ�(�޸� ����)
		HBITMAP	hReverseBitmap;	// �̹��� ����
		HBITMAP hReverseOldBit;	// ���� �̹��� ����

		int		rotateMaxSize;

		float	x;					// ��� ��ġ ��ǥ
		float	y;					// ��� ��ġ ��ǥ
		int		currentKeyFrameX;	// ���� Ű������ �ε���
		int		currentKeyFrameY;
		int		maxKeyFrameX;		// �ִ� Ű������ ��
		int		maxKeyFrameY;
		int		keyFrameWidth;		// Ű������ �� ũ��
		int		keyFrameHeight;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
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

			rotateMaxSize = 0;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;	// �̹������� ����ü ������
	char* fileName;			// ���� ��� + �̸�
	bool isTrans;			// ����ȭ ����
	COLORREF transColor;	// ����ȭ�� ��

	POINT point[3];
	BLENDFUNCTION	blendFunc;

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
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void Render(HDC hdc, int destX, int destY, int width, int height);
	void FrameRender(HDC hdc, int destX, int destY,
		int currentKeyFrameX, int currentKeyFrameY, float scale = 1.0f);

	// ���� ����
	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int width, int height, BYTE alpha);
	void FrameAlphaRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, BYTE alpha, bool iswidthreverse=false, bool isheightreverse=false);
	void FrameAlphaRenderAni(HDC hdc, int destX, int destY, int sourX, int sourY, BYTE alpha, bool iswidthreverse = false, bool isheightreverse = false);
	void RocketAlphaRender(HDC hdc, int destX, int destY, float posy, int length, BYTE alpha);
	// ȸ��
	void RotateRender(HDC hdc, double dblAngle,
		int destX, int destY, double dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);

	void FreeAxisRotateRender(HDC hdc, double dblAngle,
		int destX, int destY, int xAxis, int yAxis, double dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);

	// ȸ�� & ����
	void RotateAlphaRender(HDC hdc, double dblAngle,
		int destX, int destY, BYTE alpha = 255, double dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);

	// �ִϸ��̼�
	void AnimationRender(HDC hdc, int destX, int destY, Animation* ani);
	void ReverseAniRender(HDC hdc, int destX, int destY, bool iswidthreverse, bool isheightreverse, Animation* ani);
	void AlphaRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, BYTE alpha, float scale, float degree);
	void AlphaRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, BYTE alpha, float scale);

	//ī�޶�
	void CamaraRender(HDC hdc, float gposX, float gposY, float pposX, float pposY, int width, int height, float scale);
	HDC GetMemDC() { return imageInfo->hMemDC; }

	int GetMaxKeyFrameX() { return imageInfo->maxKeyFrameX; }
	int GetMaxKeyFrameY() { return imageInfo->maxKeyFrameY; }

	int GetWidth() { return imageInfo->width; }
	int GetHeight() { return imageInfo->height; }

	int GetFrameWidth() { return imageInfo->keyFrameWidth; }
	int GetFrameHeight() { return imageInfo->keyFrameHeight; }


	Image();
	~Image();
};

