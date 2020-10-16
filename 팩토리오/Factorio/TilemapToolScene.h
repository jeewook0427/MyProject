#pragma once
#include "GameNode.h"
//640 * 288 (20,9) => 32*32

#define TILESIZE 32			//타일 하나의 사이즈
#define SAMPLE_TERRAIN_X 2		//샘플타일의 갯수
#define SAMPLE_TERRAIN_Y 1		//샘플 타일의 갯수

#define TILE_X	100			//메인 타일의 갯수
#define TILE_Y	100			//메인 타일의 갯수


typedef struct tagSampleTile
{
	RECT rcTile;
	int frameX;
	int frameY;

}SAMPLE_TILE_INFO;

typedef struct tagTile
{
	TERRAIN terrain;
	RECT rcTile;
	int frameX;
	int frameY;

}TILE_INFO;

typedef struct tagSelectTile
{
	int frameX;
	int frameY;

}SELECT_TILE_INFO;



class TilemapToolScene : public GameNode
{
private:
	Image* sampleTileImage;

	//샘플 타일의 정보 (시작 프레임 포인트, rect 정보)
	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TERRAIN_X * SAMPLE_TERRAIN_Y];

	//메인 타일의 정보 (rect 정보, 샘플 타일의 시작 프레임 포인트, 타일의 속성)
	TILE_INFO tileInfo[TILE_X*TILE_Y];

	//선택된 타일의 정보 (시작 프레임 포인트)
	SELECT_TILE_INFO selectTileInfo;

	SELECT_TILE_INFO selectTileInfos[2];

	int minX, maxX, minY, maxY;
	int dragSizeX;
	int	dragSizeY;

	bool isDownSampleArea;
	bool isDragFilled;

	RECT rcSave;
	RECT rcLoad;


public:

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Save();
	void Load();

	TilemapToolScene();
	~TilemapToolScene();
};

