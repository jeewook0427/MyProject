#pragma once

#include <Windows.h>
#include <math.h>
#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <queue>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "Tutorial.h"

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



enum TERRAIN
{
	TR_EMPTY, TR_WATER, TR_BRIDGE, TR_GRASS, TR_END

};

enum Layer
{
	EMPTY, TREE, FORBIDDEN, COAL, IRON, COPPER, STONE, WOOD,HUMAN,
	STONEFURNACE, BASICTRANSPORTBELT, BURNERINSERTER, BURNERMININGDRILL, IRONPLATE, COPPERPLATE, STEELCHEST,
	IRONSTICK, IRONGEARWHEEL, COPPERCABLE, IRONAXE, WOODENCHEST, ELECTRONICCIRCUIT, ROCKET, SMALLELECTRICPOLE,
	STEAMENGINE, ELECTRICFURNACE, BASICINSERTER, BASICMININGDRILL, ASSEMBLINGMACHINE, ADVANCEDCIRCUIT, BASICSPLITTER
	,LONGHANDEDINSERTER,Layer_END
};


enum BeltInfo
{
	BELTRIGHT, BELTLEFT, BELTUP, BELTDOWN, BELTLEFTUP, BELTLFETDOWN, BELTRIGHTUP, BELTRIGHTDOWN
};

enum DIRECTION	/* 경고!! 순서 절대 바꾸지 마시오. */
{
	DR_UP, DR_RIGHT, DR_DOWN, DR_LEFT, DR_END
};


enum BUTTON_STATE
{
	NONE,
	UP,
	DOWN
};
typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT, *PFPOINT;

typedef struct tagArguments
{
	const char* sceneName;
	const char* loadingName;

} ARGUMENT_INFO;

typedef struct InventoryInfo
{
	bool isStorage;
	bool isSelected;
	Layer name;
	int num;
	RECT rc;

}INVENINFO;

typedef struct tagTile
{
	TERRAIN terrain;
	Layer obj;
	Layer res;
	RECT rcTile;
	int frameX;
	int frameY;
	BeltInfo belt;
	bool isElec;


}TILE_INFO;

typedef struct tagTilePoint
{
	int x;
	int y;

	bool operator < (const tagTilePoint& com) const
	{
		if (x != com.x)
		{
			return x < com.x;
		}
		return y < com.y;
	}
}TILE_POINT;

#define FPS				30.0f
#define WINSIZE_X		1600
#define WINSIZE_Y		896
#define WINSTART_X		50
#define WINSTART_Y		50
#define TILE_SIZE_X		32
#define TILE_SIZE_Y		32

#define PLAYSIZE_X		640
#define BORDER_GIRTH	30

#define PI			3.141592

#define SAFE_DELETE(p)		{ if (p) { delete p; p = NULL; }}
#define SAFE_ARR_DELETE(p)	{ if (p) { delete [] p; p = NULL; }}

#define DEGREE_TO_RADIAN(x)	( x * PI / 180 )
#define RADIAN_TO_DEGREE(x) (int)( x * 180 / PI )

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

extern FPOINT g_pos;
extern TILE_INFO tileinfo[256][256];
extern INVENINFO inveninfo[9][10];
extern POINT mousepos;
extern bool gameOver;
extern FPOINT p_pos;
extern float cameraScale;
extern bool ToolInvenIsOpen;
extern bool isLaunch;
extern float playTime;

#include "macroFunction.h"
#include "ObjectManager.h"