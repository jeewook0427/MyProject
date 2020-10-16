#pragma once
#include "GameNode.h"
class Player;
class MapManager;
class Ending;
class InGameScene : public GameNode
{
	Player* player1;
	MapManager* mapMgr;

	Image* cameraBuffer;

	Image* worldmapBuffer;
	HBRUSH grassBrush, waterBrush1, waterBrush2, bridgeBrush, coalBrush, ironBrush, copperBrush, stoneBrush;

	Ending* ending;
	bool isEnding;
	
	map<TILE_POINT, GameNode*>::iterator it;
	map<TILE_POINT, GameNode*>::iterator tempit;
	map<Layer, map<TILE_POINT, GameNode*> >::iterator iter;
	vector<GameNode*>::iterator vecit;

	int BGMIndex;
	float BGMTime;
	bool BGMPlay;

public:

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void EraseFromWorldmapBuffer(TILE_POINT _tp);
	void BGMUpdate();

	InGameScene();
	~InGameScene();
};

