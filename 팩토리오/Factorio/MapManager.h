#pragma once
#include "pch.h"

class ObjResource;
class TileResource;
class MapManager
{
private:
	HBRUSH grassBrush, waterBrush1, waterBrush2, bridgeBrush, coalBrush, ironBrush, copperBrush, stoneBrush, treeBrush, playerBrush;
	RECT tempRc;
	Image* logo;
	Image* grayBox;

	Image* waterImg;
	Image* bridgeImg;
	Image* grassImg;
	Image* sandImg;
	Image* dirtDarkImg;

	map<TILE_POINT, GameNode*> mapTileCoalDatas;
	map<TILE_POINT, GameNode*> mapTileIronDatas;
	map<TILE_POINT, GameNode*> mapTileCopperDatas;
	map<TILE_POINT, GameNode*> mapTileStoneDatas;
	map<TILE_POINT, GameNode*>::iterator mapTileIter;

	map<TILE_POINT, GameNode*> mapObjResDatas;
	map<TILE_POINT, GameNode*>::iterator mapObjIter;

	int valArr[256][256] = { 0, };
	FPOINT pos;

	FPOINT mapPos;
	Image* worldmapBuffer;
	bool worldmapOn;
	bool minimapOn;

	int totalWaterNum;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetRandTerrain();
	void SetRandTile();
	void SetRandObjRes(int Num);

	GameNode* FindTileRes(TILE_POINT tp, int _res);
	void DeleteTileRes(TILE_POINT tp);

	GameNode* FindObjRes(TILE_POINT tp);
	void DeleteObjRes(TILE_POINT tp);
	void DeleteAll();

	void FloodFill_Tl(int x, int y, int baseValue, int _tileRes);
	bool FloodFill_Water(int x, int y, int baseValue);
	void OrganizeWaterFrame();
	void SetBridge();

	void RenderMinimap(HDC hdc);
	void SetWorldmapBase();
	void SetWorldmapTileRes(TILE_POINT tp, int _tileRes);
	void RenderWorldmap(HDC hdc);

	bool GetWorldmapOn() { return worldmapOn; }
	void SetWorldmapOn(bool _worldmapOn) { worldmapOn = _worldmapOn; }

	MapManager();
	~MapManager();
};

