#pragma once

#include <Windows.h>
#include <math.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SoundManager.h"

// enum, struct, .h, #define
enum BOX
{
	BOX_First,
	BOX_Second,
	BOX_End
};

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT, *PFPOINT;

#define WINSIZE_X	600
#define WINSIZE_Y	800
#define WINSTART_X	50
#define WINSTART_Y	50

#define PI			3.141592

#define SAFE_DELETE(p) { if(p) { delete p; p = NULL; } } //delete를 하고 싶은 객체가 들어옴
#define SAFE_ARR_DELETE(p) { if(p) {delete []p; p = NULL;} }

#define DEGREE_TO_RADIAN(x) ( x * PI / 180 )
#define RADIAN_TO_DEGREE(x) ( (int)(x * 180 / PI) )

typedef struct tagLOGFONT
{
	LONG lfHeight;
	LONG lfWidth;
	LONG lfEscapement;
	LONG lfOrientation;
	LONG lfWeight;
	BYTE lfItalic;
	BYTE lfUnderline;
	BYTE lfStrikeOut;
	BYTE lfCharSet;
	BYTE lfOutPrecision;
	BYTE lfClipPrecision;
	BYTE lfQuality;
	BYTE lfPitchAndFamily;
	CHAR lfFaceName[LF_FACESIZE];

public:

	tagLOGFONT()
	{
		lfHeight = 30;
		lfWidth = 0;
		lfEscapement = 0;
		lfOrientation = 0;
		lfWeight = 0;
		lfItalic = 0;
		lfUnderline = 0;
		lfStrikeOut = 0;
		lfCharSet = HANGEUL_CHARSET;
		lfOutPrecision = 0;
		lfClipPrecision = 0;
		lfQuality = 0;
		lfPitchAndFamily = 0;

	};
	~tagLOGFONT() {};

} FONT;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;