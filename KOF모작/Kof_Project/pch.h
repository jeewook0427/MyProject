#pragma once

#include <Windows.h>
#include <math.h>
#include "KeyManager.h"
#pragma comment(lib,"winmm.lib")
#include <mmsystem.h>

// enum, struct, .h, #define
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

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT, *PFPOINT;

#define WINSIZE_X	768*2
#define WINSIZE_Y	240*2
#define WINSTART_X	50
#define WINSTART_Y	50

#define PI			3.141592

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;