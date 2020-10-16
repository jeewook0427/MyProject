#pragma once
#include "pch.h"
class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE, // ���ҽ��� �ִ°� ������
		FILE, //�ܺ����� �ε�
		EMPTY, // ����ִ� ��Ʈ�ʰ���
		END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;		// ���ҽ��� ������ ���̵�
		HDC		hMemDC;		// �׸��⸦ �ְ��ϴ� �ڵ�(�޸𸮰���)
		HBITMAP hBitmap;	// �̹��� ����
		HBITMAP hOldBit;	// ���� �̹��� ����
		int		width;		// �̹��� ���� ũ��
		int		height;		// �̹��� ���� ũ��
		BYTE	loadType;	// �ε� Ÿ��

		float	x;					// ��� ��ġ ��ǥ
		float	y;					// ��� ��ġ ��ǥ
		int		currentKeyFrameX;	// ���� Ű������ �ε���
		int		currentKeyFrameY;
		int		maxKeyFrameX;		// �ִ� Ű������ ��
		int		maxKeyFrameY;
		float	KeyFrameWidth;		// Ű������ �� ũ��
		float	KeyFrameHeight;

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
			KeyFrameWidth = 0;
			KeyFrameHeight = 0;
		}

	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;	// �̹������� ����ü ������
	char* fileName;			// ���� ��� + �̸�
	bool isTrans;			// ����ȭ ����
	COLORREF transColor;	// ����ȭ�� ��

public:

	// �� ��Ʈ�� �̹����� �����.
	HRESULT Init(int width, int height);

	// ���ҽ��κ��� �����͸� �о �����.
	HRESULT Init(const DWORD resID, int width, int height, bool trans = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �����͸� �о �����.
	HRESULT Init(const char* fileName, int width, int height, bool trans = FALSE, COLORREF transColor = FALSE);

	// �̹��� + Ű������ �ʱ�ȭ
	HRESULT Init(const char* fileName, float x, float y,
		int width, int height,
		int keyFrameX, int keyFrameY,
		bool trans = FALSE, COLORREF transColor = FALSE);

	HRESULT Init(int width, int height, bool trans, COLORREF transColor);

	// �޸𸮸� ����
	void Release();


	// ����
	void Render(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY,
		int currentKeyFrameX, int currentKeyFrameY, float scale);

	void FrameRender(HDC hdc, int destX, int destY,
		int currentKeyFrameX, int currentKeyFrameY, float scale, bool isreverse);

	void FrameRender(HDC hdc, int destX, int destY, int width, int height, int startX,
		int startY, int currentKeyFrameX, int currentKeyFrameY, int KeyFrameX, int KeyFrameY, float scale);

	void FrameMapRender(HDC hdc, int destX, int destY, int currentKeyFrameX, int currentKeyFrameY, float widthscale, float heightscale);

	void FrameRender(HDC hdc, int destX, int destY, float scale = 1.0f);
	//
	int GetmaxKeyFrameX() { return imageInfo->maxKeyFrameX; }
	int GetmaxKeyFrameY() { return imageInfo->maxKeyFrameY; }
	HDC GetMemDC() { return imageInfo->hMemDC; }

	Image();
	~Image();
};

