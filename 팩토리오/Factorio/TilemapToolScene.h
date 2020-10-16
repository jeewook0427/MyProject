#pragma once
#include "GameNode.h"
//640 * 288 (20,9) => 32*32

#define TILESIZE 32			//Ÿ�� �ϳ��� ������
#define SAMPLE_TERRAIN_X 2		//����Ÿ���� ����
#define SAMPLE_TERRAIN_Y 1		//���� Ÿ���� ����

#define TILE_X	100			//���� Ÿ���� ����
#define TILE_Y	100			//���� Ÿ���� ����


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

	//���� Ÿ���� ���� (���� ������ ����Ʈ, rect ����)
	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TERRAIN_X * SAMPLE_TERRAIN_Y];

	//���� Ÿ���� ���� (rect ����, ���� Ÿ���� ���� ������ ����Ʈ, Ÿ���� �Ӽ�)
	TILE_INFO tileInfo[TILE_X*TILE_Y];

	//���õ� Ÿ���� ���� (���� ������ ����Ʈ)
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

