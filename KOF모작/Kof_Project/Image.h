#pragma once
#include "pch.h"
class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE, // 리소스에 있는거 가져옴
		FILE, //외부파일 로드
		EMPTY, // 비어있는 비트맵공간
		END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;		// 리소스의 고유한 아이디
		HDC		hMemDC;		// 그리기를 주관하는 핸들(메모리관리)
		HBITMAP hBitmap;	// 이미지 정보
		HBITMAP hOldBit;	// 기존 이미지 정보
		int		width;		// 이미지 가로 크기
		int		height;		// 이미지 세로 크기
		BYTE	loadType;	// 로드 타입

		float	x;					// 출력 위치 좌표
		float	y;					// 출력 위치 좌표
		int		currentKeyFrameX;	// 현재 키프레임 인덱스
		int		currentKeyFrameY;
		int		maxKeyFrameX;		// 최대 키프레임 수
		int		maxKeyFrameY;
		float	KeyFrameWidth;		// 키프레임 당 크기
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
	IMAGE_INFO* imageInfo;	// 이미지정보 구조체 포인터
	char* fileName;			// 파일 경로 + 이름
	bool isTrans;			// 투명화 여부
	COLORREF transColor;	// 투명화할 색

public:

	// 빈 비트맵 이미지를 만든다.
	HRESULT Init(int width, int height);

	// 리소스로부터 데이터를 읽어서 만든다.
	HRESULT Init(const DWORD resID, int width, int height, bool trans = FALSE, COLORREF transColor = FALSE);

	// 파일로부터 데이터를 읽어서 만든다.
	HRESULT Init(const char* fileName, int width, int height, bool trans = FALSE, COLORREF transColor = FALSE);

	// 이미지 + 키프레임 초기화
	HRESULT Init(const char* fileName, float x, float y,
		int width, int height,
		int keyFrameX, int keyFrameY,
		bool trans = FALSE, COLORREF transColor = FALSE);

	HRESULT Init(int width, int height, bool trans, COLORREF transColor);

	// 메모리를 해제
	void Release();


	// 렌더
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

