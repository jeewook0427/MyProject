#include "MapManager.h"
#include "Image.h"
#include "Tree.h"
#include "Coal.h"
#include "Iron.h"
#include "Stone.h"
#include "CopperOre.h"
#include "ObjResource.h"
#include "TileResource.h"


TILE_INFO tileinfo[256][256];

HRESULT MapManager::Init()
{
	totalWaterNum = 0;
	Coal::totalTileNum = 0;
	Iron::totalTileNum = 0;
	CopperOre::totalTileNum = 0;
	Stone::totalTileNum = 0;

	worldmapBuffer = ImageManager::GetSingleton()->FindImage("worldmapBuffer");
	minimapOn = true;
	worldmapOn = false;

	int count = 0;
	

	grassImg = ImageManager::GetSingleton()->FindImage("grass");
	sandImg = ImageManager::GetSingleton()->FindImage("sand");
	dirtDarkImg = ImageManager::GetSingleton()->FindImage("dirt-dark");
	waterImg = ImageManager::GetSingleton()->FindImage("water");
	bridgeImg = ImageManager::GetSingleton()->FindImage("bridge");


	SceneManager::loadingPercent = 10;

	SetRandTerrain();
	SceneManager::loadingPercent = 20;
	//SetWorldmapBase();

	SetRandTile();
	SetRandObjRes(500);
	SceneManager::loadingPercent = 90;

	g_pos.x = 3200;
	g_pos.y = 3200;
	
	//플레이어 초기위치
	p_pos.x = 3200;
	p_pos.y = 3200;
		
	while (tileinfo[(int)p_pos.y / 32][(int)p_pos.x / 32].terrain == TR_WATER)
	{
		g_pos.x += 32.0f;
		g_pos.y += 32.0f;
		p_pos.x += 32.0f;
		p_pos.y += 32.0f;
		
	}

	// 월드맵을 다 그리고 난 후 브러시 삭제(grassBrush 빼고)
	DeleteObject(waterBrush1);
	DeleteObject(waterBrush2);
	DeleteObject(bridgeBrush);
	DeleteObject(coalBrush);
	DeleteObject(ironBrush);
	DeleteObject(copperBrush);
	DeleteObject(stoneBrush);
	DeleteObject(treeBrush);
	DeleteObject(playerBrush);

	return S_OK;
}

void MapManager::Release()
{
}

void MapManager::Update()
{

}

void MapManager::Render(HDC hdc)
{	

	for (int i = ((int)(g_pos.y - WINSIZE_Y / 2) / 32); i < ((int)(g_pos.y - WINSIZE_Y / 2) / 32) + 32; ++i)
	{
		for (int j = ((int)(g_pos.x - 800) / 32); j < ((int)(g_pos.x - 800) / 32) + 53; ++j)
		{
			mapPos.x = ((j - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 16;
			mapPos.y = ((i - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16;
			if (i <= 256 && j <= 256)
			{
				if (tileinfo[i][j].terrain == TR_GRASS)
				{
					grassImg->FrameRender(hdc, mapPos.x, mapPos.y,
						tileinfo[i][j].frameX, tileinfo[i][j].frameY);
				}

				else if (tileinfo[i][j].terrain == TR_WATER) // || tileinfo[i][j].terrain == TR_BRIDGE)
				{
					waterImg->FrameRender(hdc, mapPos.x, mapPos.y,
						tileinfo[i][j].frameX, tileinfo[i][j].frameY);

				}

				else if (tileinfo[i][j].terrain == TR_BRIDGE)
				{
					bridgeImg->FrameRender(hdc, mapPos.x, mapPos.y,
						0, 0);
				}
			}

		}
	}
}

void MapManager::SetRandTerrain()
{
	srand(time(NULL));

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			tileinfo[i][j].terrain = TR_GRASS;
			tileinfo[i][j].frameX = rand() % 8;
			if (rand() % 3 == 0)
				tileinfo[i][j].frameY = rand() % 16;
			else
				tileinfo[i][j].frameY = rand() % 4;
			tileinfo[i][j].obj = EMPTY;
			tileinfo[i][j].res = EMPTY;
			tileinfo[i][j].rcTile = { j * 32, i * 32, j * 32 + 32,i * 32 + 32 };
			tileinfo[i][j].isElec = false;

			if (j <= 20 || j >= 236)
			{
				tileinfo[i][j].obj = FORBIDDEN;
			}

			if (i <= 20 || i >= 236)
			{
				tileinfo[i][j].obj = FORBIDDEN;
			}
		}
	}

}

void MapManager::SetRandTile()
{
	srand(time(NULL));
	memset(valArr, 0, sizeof(int) * 256 * 256);	// 나중에 다시 확인
	TILE_POINT randP;
	int angle = 0;
	int randVal = 0;

	for (int k = 0; k < 500; k++)
	{
		if (k < 30)
		{
			randP = { rand() % 80, rand() % 80 };
			angle = (rand() % 80) + 50;
		}
		else if (k < 40)
		{
			randP = { rand() % 80, rand() % 256 };
			angle = (rand() % 140) + 20;
		}
		else if (k < 50)
		{
			randP = { rand() % 100 + 50, rand() % 80 };
			angle = 90;
		}
		else
		{
			randP = { rand() % 256, rand() % 256 };
			angle = (rand() % 140) + 20;
		}

		randVal = rand() % 2;

		for (int i = 0; i < 256; i++)
		{
			for (int j = 0; j < 256; j++)
			{
				if (randP.y > i)
				{
					if (DEGREE_TO_RADIAN(angle) <= atan2(i - randP.y, j - randP.x))
					{
						if (randVal == 0)
						{
							valArr[i][j] += 7;
						}
						else
						{
							valArr[i][j] -= 3;
						}
					}
				}

				else
				{
					if (DEGREE_TO_RADIAN(angle) >= atan2(i - randP.y, j - randP.x))
					{
						if (randVal == 0)
						{
							valArr[i][j] += 8;
						}
						else
						{
							valArr[i][j] -= 2;

						}
					}
				}

			}
		}
		SceneManager::loadingPercent = 20 + k / 10;
	}


	// flood fill
	TILE_POINT index;
	TILE_POINT index2 = { 0, 0 };
	index = { rand() % 2 * 110 + 70, rand() % 2 * 110 + 70 };
	FloodFill_Water(index.x, index.y, valArr[index.y][index.x]);

	if (totalWaterNum < 800)
	{
		do
		{
			index2 = { rand() % 2 * 110 + 70, rand() % 2 * 110 + 70 };
		} while (index.x == index2.x && index.y == index2.y);

		FloodFill_Water(index2.x, index2.y, valArr[index2.y][index2.x]);
	}

	OrganizeWaterFrame();

	SetBridge();

	SetWorldmapBase();

	// TileRes

	while (Coal::totalTileNum < 500)
	{
		index = { (rand() % 21) * 10 + 30, (rand() % 21) * 10 + 30 };

		if (tileinfo[index.y][index.x].terrain == TR_WATER ||
			tileinfo[index.y][index.x].terrain == TR_BRIDGE ||
			tileinfo[index.y][index.x].res != TR_EMPTY)
		{
			continue;
		}

		FloodFill_Tl(index.x, index.y, valArr[index.y][index.x], COAL);
	}

	while (Iron::totalTileNum < 500)
	{
		index = { (rand() % 21) * 10 + 30, (rand() % 21) * 10 + 30 };

		if (tileinfo[index.y][index.x].terrain == TR_WATER ||
			tileinfo[index.y][index.x].terrain == TR_BRIDGE ||
			tileinfo[index.y][index.x].res != TR_EMPTY)
		{
			continue;
		}

		FloodFill_Tl(index.x, index.y, valArr[index.y][index.x], IRON);
	}

	while (CopperOre::totalTileNum < 400)
	{
		index = { (rand() % 21) * 10 + 30, (rand() % 21) * 10 + 30 };

		if (tileinfo[index.y][index.x].terrain == TR_WATER ||
			tileinfo[index.y][index.x].terrain == TR_BRIDGE ||
			tileinfo[index.y][index.x].res != TR_EMPTY)
		{
			continue;
		}

		FloodFill_Tl(index.x, index.y, valArr[index.y][index.x], COPPER);
	}

	while (Stone::totalTileNum < 300)
	{
		index = { (rand() % 21) * 10 + 30, (rand() % 21) * 10 + 30 };

		if (tileinfo[index.y][index.x].terrain == TR_WATER ||
			tileinfo[index.y][index.x].terrain == TR_BRIDGE ||
			tileinfo[index.y][index.x].res != TR_EMPTY)
		{
			continue;
		}

		FloodFill_Tl(index.x, index.y, valArr[index.y][index.x], STONE);
	}

	SceneManager::loadingPercent = 80;

	ObjectManager::GetSingleton()->InsertMap(COAL, mapTileCoalDatas);
	ObjectManager::GetSingleton()->InsertMap(IRON, mapTileIronDatas);
	ObjectManager::GetSingleton()->InsertMap(COPPER, mapTileCopperDatas);
	ObjectManager::GetSingleton()->InsertMap(STONE, mapTileStoneDatas);
	mapTileCoalDatas.clear();
	mapTileIronDatas.clear();
	mapTileCopperDatas.clear();
	mapTileStoneDatas.clear();
}

void MapManager::SetRandObjRes(int Num)
{
	int x, y;
	map<TILE_POINT, GameNode*> tempmap;
	TILE_POINT tp1, tp2;

	for (int i = 0; i < Num; ++i)
	{
		x = rand() % 256;
		y = rand() % 256;
		tp1.x = x;
		tp1.y = y;
		tp2.x = tp1.x;
		tp2.y = tp1.y + 1;

		if (FindObjRes(tp1) || FindObjRes(tp2) || tileinfo[y][x].terrain != TR_GRASS)
		{
			--i;
			continue;
		}

		else
		{

			GameNode* obj = new Tree(tp1, rand() % 5 + 1);
			mapObjResDatas.insert(make_pair(tp1, obj));
			mapObjResDatas.insert(make_pair(tp2, obj));
			tileinfo[y][x].obj = TREE;
		}


	}

	ObjectManager::GetSingleton()->InsertMap(TREE, mapObjResDatas);
	mapObjResDatas.clear();
}

GameNode * MapManager::FindTileRes(TILE_POINT tp, int _res)
{
	if (_res == COAL)
	{
		mapTileIter = mapTileCoalDatas.find(tp);
		if (mapTileIter != mapTileCoalDatas.end())
		{
			return mapTileIter->second;
		}

		return nullptr;
	}

	else if (_res == IRON)
	{
		mapTileIter = mapTileIronDatas.find(tp);
		if (mapTileIter != mapTileIronDatas.end())
		{
			return mapTileIter->second;
		}

		return nullptr;
	}

	else if (_res == COPPER)
	{
		mapTileIter = mapTileCopperDatas.find(tp);
		if (mapTileIter != mapTileCopperDatas.end())
		{
			return mapTileIter->second;
		}

		return nullptr;
	}

	else if (_res == STONE)
	{
		mapTileIter = mapTileStoneDatas.find(tp);
		if (mapTileIter != mapTileStoneDatas.end())
		{
			return mapTileIter->second;
		}

		return nullptr;
	}
}

/**************확인 필요***********/
void MapManager::DeleteTileRes(TILE_POINT tp)
{
	mapTileIter = mapTileCoalDatas.find(tp);
	if (mapTileIter != mapTileCoalDatas.end())
	{
		//(iter->second)->Release();
		SAFE_DELETE((mapTileIter->second));

		mapTileCoalDatas.erase(mapTileIter);
	}
}

GameNode * MapManager::FindObjRes(TILE_POINT tp)
{
	mapObjIter = mapObjResDatas.find(tp);
	if (mapObjIter != mapObjResDatas.end())
	{
		return mapObjIter->second;
	}

	return nullptr;

}

void MapManager::DeleteObjRes(TILE_POINT tp)
{
	mapObjIter = mapObjResDatas.find(tp);
	if (mapObjIter != mapObjResDatas.end())
	{
		SAFE_DELETE((mapObjIter->second));

		mapObjResDatas.erase(mapObjIter);
	}
}

void MapManager::DeleteAll()
{

	for (mapObjResDatas.begin(); mapObjIter != mapObjResDatas.end(); /*iter++*/)
	{
		if (mapObjIter->second != nullptr)
		{
			SAFE_DELETE((mapObjIter->second));

			mapObjIter = mapObjResDatas.erase(mapObjIter);
		}
		else
		{
			mapObjIter++;
		}
	}

	mapObjResDatas.clear();

	for (mapTileIter = mapTileCoalDatas.begin(); mapTileIter != mapTileCoalDatas.end(); /*iter++*/)
	{
		if (mapTileIter->second != nullptr)
		{
			SAFE_DELETE((mapTileIter->second));

			mapTileIter = mapTileCoalDatas.erase(mapTileIter);
		}
		else
		{
			mapTileIter++;
		}
	}

	mapTileCoalDatas.clear();

	for (mapTileIter = mapTileIronDatas.begin(); mapTileIter != mapTileIronDatas.end(); /*iter++*/)
	{
		if (mapTileIter->second != nullptr)
		{

			SAFE_DELETE((mapTileIter->second));

			mapTileIter = mapTileIronDatas.erase(mapTileIter);
		}
		else
		{
			mapTileIter++;
		}
	}

	mapTileIronDatas.clear();
}


void MapManager::FloodFill_Tl(int x, int y, int baseValue, int _tileRes)
{

	GameNode* tile;

	// 예외처리
	if (tileinfo[y][x].terrain == TR_WATER ||
		tileinfo[y][x].terrain == TR_BRIDGE ||
		tileinfo[y][x].res != TR_EMPTY)
	{
		tile = nullptr;
	}

	else if (abs(valArr[y][x] - baseValue) < 4)
	{
		TILE_POINT _tp = { x, y };

		if (_tileRes == COAL)
		{
			tileinfo[y][x].res = COAL;
			tile = new Coal(_tp, (rand() % 11 + 2) * 100);
			mapTileCoalDatas.insert(make_pair(_tp, tile));
			SetWorldmapTileRes(_tp, COAL);
			Coal::totalTileNum++;
		}

		else if (_tileRes == IRON)
		{
			tileinfo[y][x].res = IRON;
			tile = new Iron(_tp, (rand() % 11 + 2) * 100);
			mapTileIronDatas.insert(make_pair(_tp, tile));
			SetWorldmapTileRes(_tp, IRON);
			Iron::totalTileNum++;
		}

		else if (_tileRes == COPPER)
		{
			tileinfo[y][x].res = COPPER;
			tile = new CopperOre(_tp, (rand() % 11 + 2) * 100);
			mapTileCopperDatas.insert(make_pair(_tp, tile));
			SetWorldmapTileRes(_tp, COPPER);
			CopperOre::totalTileNum++;
		}

		else if (_tileRes == STONE)
		{
			tileinfo[y][x].res = STONE;
			tile = new Stone(_tp, (rand() % 11 + 2) * 100);
			mapTileStoneDatas.insert(make_pair(_tp, tile));
			SetWorldmapTileRes(_tp, STONE);
			Stone::totalTileNum++;
		}

		else
		{
			tile = nullptr;
		}


		if (x < 255)
			FloodFill_Tl(x + 1, y, baseValue, _tileRes);
		if (y < 255)
			FloodFill_Tl(x, y + 1, baseValue, _tileRes);
		if (x > 0)
			FloodFill_Tl(x - 1, y, baseValue, _tileRes);
		if (y > 0)
			FloodFill_Tl(x, y - 1, baseValue, _tileRes);
	}
}

bool MapManager::FloodFill_Water(int x, int y, int baseValue)
{
	if (abs(valArr[y][x] - baseValue) < 15 && tileinfo[y][x].terrain != TR_WATER)
	{
		tileinfo[y][x].terrain = TR_WATER;
		totalWaterNum++;

		tileinfo[y][x].frameX = rand() % 8;
		tileinfo[y][x].frameY = 0;

		if (x < 255)
		{
			if (!FloodFill_Water(x + 1, y, baseValue))
			{
				// 오른쪽에 물이 없을 때
				tileinfo[y][x].frameY = 7;
			}
		}
		if (x > 0)
		{
			if (!FloodFill_Water(x - 1, y, baseValue))
			{
				// 왼쪽에 물이 없을 때
				tileinfo[y][x].frameY = 5;
			}
		}
		if (y < 255)
		{
			if (!FloodFill_Water(x, y + 1, baseValue))
			{
				// 아래쪽에 물이 없을 때
				if (tileinfo[y][x].frameY == 7)
				{
					tileinfo[y][x].frameY = 11;
				}
				else if (tileinfo[y][x].frameY == 5)
				{
					tileinfo[y][x].frameY = 8;
				}
				else
				{
					tileinfo[y][x].frameY = 4;
				}
			}
		}
		if (y > 0)
		{
			if (!FloodFill_Water(x, y - 1, baseValue))
			{
				// 위쪽에 물이 없을 때
				if (tileinfo[y][x].frameY == 7)
				{
					tileinfo[y][x].frameY = 10;
				}
				else if (tileinfo[y][x].frameY == 5)
				{
					tileinfo[y][x].frameY = 9;
				}
				else
				{
					tileinfo[y][x].frameY = 6;
				}
			}
		}

		return true;
	}
	else if (tileinfo[y][x].terrain == TR_WATER)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MapManager::OrganizeWaterFrame()
{
	int x = 0, y = 0;

	for (int i = 0; i < 256; ++i)
	{
		for (int j = 0; j < 256; ++j)
		{
			if (tileinfo[i][j].terrain == TR_WATER)
			{
				if (tileinfo[i][j - 1].terrain != TR_WATER && tileinfo[i][j + 1].terrain != TR_WATER
					&& tileinfo[i - 1][j].terrain != TR_WATER && tileinfo[i + 1][j].terrain != TR_WATER)
				{
					tileinfo[i][j].terrain == TR_GRASS;
				}

				/////////////////

				else if (tileinfo[i][j - 1].terrain != TR_WATER && tileinfo[i][j + 1].terrain != TR_WATER
					&& tileinfo[i + 1][j].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 18;
				}

				else if (tileinfo[i][j - 1].terrain != TR_WATER
					&& tileinfo[i - 1][j].terrain != TR_WATER && tileinfo[i + 1][j].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 19;
				}

				else if (tileinfo[i][j - 1].terrain != TR_WATER && tileinfo[i][j + 1].terrain != TR_WATER
					&& tileinfo[i + 1][j].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 20;
				}

				else if (tileinfo[i][j + 1].terrain != TR_WATER
					&& tileinfo[i - 1][j].terrain != TR_WATER && tileinfo[i + 1][j].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 21;
				}

				///////////////

				else if (tileinfo[i - 1][j].terrain != TR_WATER && tileinfo[i + 1][j].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 16;
				}

				else if (tileinfo[i][j - 1].terrain != TR_WATER && tileinfo[i][j + 1].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 17;
				}

				/////////////


				else if (tileinfo[i][j - 1].terrain != TR_WATER && tileinfo[i + 1][j].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 8;

				}
				else if (tileinfo[i][j - 1].terrain != TR_WATER && tileinfo[i - 1][j].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 9;
				}
				else if (tileinfo[i - 1][j].terrain != TR_WATER && tileinfo[i][j + 1].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 10;

				}
				else if (tileinfo[i][j + 1].terrain != TR_WATER && tileinfo[i + 1][j].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 11;
				}

				/////////////


				else if (tileinfo[i + 1][j].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 4;

				}
				else if (tileinfo[i][j - 1].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 5;
				}
				else if (tileinfo[i - 1][j].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 6;

				}
				else if (tileinfo[i][j + 1].terrain != TR_WATER)
				{
					tileinfo[i][j].frameY = 7;
				}

				/////

				else if ((tileinfo[i][j - 1].frameY == 17 || tileinfo[i][j - 1].frameY == 19)
					&& (tileinfo[i][j + 1].frameY == 16 || tileinfo[i][j + 1].frameY == 21)
					&& (tileinfo[i - 1][j].frameY == 17 || tileinfo[i - 1][j].frameY == 20)
					&& (tileinfo[i + 1][j].frameY == 16 || tileinfo[i + 1][j].frameY == 18))
				{
					tileinfo[i][j].frameY = 32;
				}

				/////

				else if ((tileinfo[i][j - 1].frameY == 17 || tileinfo[i][j - 1].frameY == 19)
					&& (tileinfo[i][j + 1].frameY == 4 || tileinfo[i][j + 1].frameY == 11)
					&& (tileinfo[i - 1][j].frameY == 5 || tileinfo[i - 1][j].frameY == 9)
					&& (tileinfo[i + 1][j].frameY == 16 || tileinfo[i + 1][j].frameY == 18))
				{
					tileinfo[i][j].frameY = 28;
				}

				else if ((tileinfo[i][j - 1].frameY == 17 || tileinfo[i][j - 1].frameY == 19)
					&& (tileinfo[i][j + 1].frameY == 6 || tileinfo[i][j + 1].frameY == 10)
					&& (tileinfo[i - 1][j].frameY == 17 || tileinfo[i - 1][j].frameY == 20)
					&& (tileinfo[i + 1][j].frameY == 5 || tileinfo[i + 1][j].frameY == 8))
				{
					tileinfo[i][j].frameY = 29;
				}

				else if ((tileinfo[i][j - 1].frameY == 6 || tileinfo[i][j - 1].frameY == 9)
					&& (tileinfo[i][j + 1].frameY == 16 || tileinfo[i][j + 1].frameY == 21)
					&& (tileinfo[i - 1][j].frameY == 17 || tileinfo[i - 1][j].frameY == 20)
					&& (tileinfo[i + 1][j].frameY == 7 || tileinfo[i + 1][j].frameY == 11))
				{
					tileinfo[i][j].frameY = 30;
				}


				else if ((tileinfo[i][j - 1].frameY == 4 || tileinfo[i][j - 1].frameY == 8)
					&& (tileinfo[i][j + 1].frameY == 16 || tileinfo[i][j + 1].frameY == 21)
					&& (tileinfo[i - 1][j].frameY == 7 || tileinfo[i - 1][j].frameY == 10)
					&& (tileinfo[i + 1][j].frameY == 16 || tileinfo[i + 1][j].frameY == 18))
				{
					tileinfo[i][j].frameY = 31;
				}

				///////////////////////////

				else if ((tileinfo[i][j - 1].frameY == 4 || tileinfo[i][j - 1].frameY == 8)
					&& (tileinfo[i][j + 1].frameY == 4 || tileinfo[i][j + 1].frameY == 11)
					&& (tileinfo[i + 1][j].frameY == 16 || tileinfo[i + 1][j].frameY == 18))
				{
					tileinfo[i][j].frameY = 22;
				}

				else if ((tileinfo[i][j - 1].frameY == 17 || tileinfo[i][j - 1].frameY == 19)
					&& (tileinfo[i - 1][j].frameY == 5 || tileinfo[i - 1][j].frameY == 9)
					&& (tileinfo[i + 1][j].frameY == 5 || tileinfo[i + 1][j].frameY == 8))
				{
					tileinfo[i][j].frameY = 23;
				}

				else if ((tileinfo[i][j - 1].frameY == 6 || tileinfo[i][j - 1].frameY == 9)
					&& (tileinfo[i][j + 1].frameY == 6 || tileinfo[i][j + 1].frameY == 10)
					&& (tileinfo[i - 1][j].frameY == 17 || tileinfo[i - 1][j].frameY == 20))
				{
					tileinfo[i][j].frameY = 24;
				}


				else if ((tileinfo[i][j + 1].frameY == 16 || tileinfo[i][j + 1].frameY == 21)
					&& (tileinfo[i - 1][j].frameY == 7 || tileinfo[i - 1][j].frameY == 10)
					&& (tileinfo[i + 1][j].frameY == 7 || tileinfo[i + 1][j].frameY == 11))
				{
					tileinfo[i][j].frameY = 25;
				}

				///////////////

				else if ((tileinfo[i][j - 1].frameY == 4 || tileinfo[i][j - 1].frameY == 8)
					&& (tileinfo[i][j + 1].frameY == 6 || tileinfo[i][j + 1].frameY == 10)
					&& (tileinfo[i - 1][j].frameY == 7 || tileinfo[i - 1][j].frameY == 10)
					&& (tileinfo[i + 1][j].frameY == 5 || tileinfo[i + 1][j].frameY == 8))
				{
					tileinfo[i][j].frameY = 26;
				}

				else if ((tileinfo[i][j - 1].frameY == 6 || tileinfo[i][j - 1].frameY == 9)
					&& (tileinfo[i][j + 1].frameY == 4 || tileinfo[i][j + 1].frameY == 11)
					&& (tileinfo[i - 1][j].frameY == 5 || tileinfo[i - 1][j].frameY == 9)
					&& (tileinfo[i + 1][j].frameY == 7 || tileinfo[i + 1][j].frameY == 11))
				{
					tileinfo[i][j].frameY = 27;
				}

				//////////////////////////

				else if ((tileinfo[i + 1][j].frameY == 5 || tileinfo[i + 1][j].frameY == 8)
					&& (tileinfo[i][j - 1].frameY == 4 || tileinfo[i][j - 1].frameY == 8))
				{
					tileinfo[i][j].frameY = 12;
				}
				else if ((tileinfo[i - 1][j].frameY == 5 || tileinfo[i - 1][j].frameY == 9)
					&& (tileinfo[i][j - 1].frameY == 6 || tileinfo[i][j - 1].frameY == 9))
				{
					tileinfo[i][j].frameY = 13;
				}

				else if ((tileinfo[i - 1][j].frameY == 7 || tileinfo[i - 1][j].frameY == 10)
					&& (tileinfo[i][j + 1].frameY == 6 || tileinfo[i][j + 1].frameY == 10))
				{
					tileinfo[i][j].frameY = 14;
				}
				else if ((tileinfo[i + 1][j].frameY == 7 || tileinfo[i + 1][j].frameY == 11)
					&& (tileinfo[i][j + 1].frameY == 4 || tileinfo[i][j + 1].frameY == 11))
				{
					tileinfo[i][j].frameY = 15;
				}
			}
		}
	}
}


void MapManager::SetBridge()
{
	for (int i = 0; i < 256; ++i)
	{
		if (tileinfo[i][60].terrain == TR_WATER)
		{
			tileinfo[i][59].terrain = TR_BRIDGE;
			tileinfo[i][60].terrain = TR_BRIDGE;
			tileinfo[i][61].terrain = TR_BRIDGE;
		}

		if (tileinfo[i][180].terrain == TR_WATER)
		{
			tileinfo[i][179].terrain = TR_BRIDGE;
			tileinfo[i][180].terrain = TR_BRIDGE;
			tileinfo[i][181].terrain = TR_BRIDGE;
		}
	}
}

void MapManager::RenderMinimap(HDC hdc)
{
	if (minimapOn)
	{
		grayBox->Render(hdc, 1490, 170, 210, 210);
		worldmapBuffer->Render(hdc, 1490, 170, 400 + 3 * ((int)p_pos.x / 32) - 100, 50 + 3 * ((int)p_pos.y / 32) - 100, 200, 200);
		tempRc = { 1485, 165, 1495, 175};
		FillRect(hdc, &tempRc, playerBrush);
	}
}

void MapManager::SetWorldmapBase()
{
	PatBlt(worldmapBuffer->GetMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	tempRc = { 400 + 3, 50, 400 + 3 * 256, 50 + 3 * 256 };
	FillRect(worldmapBuffer->GetMemDC(), &tempRc, grassBrush);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (tileinfo[i][j].terrain == TR_WATER)
			{
				tempRc = { 400 + 3 * j, 50 + 3 * i, 400 + 3 * j + 3, 50 + 3 * i + 3 };
				if (tileinfo[i][j].frameY < 4)
					FillRect(worldmapBuffer->GetMemDC(), &tempRc, waterBrush1);
				else
					FillRect(worldmapBuffer->GetMemDC(), &tempRc, waterBrush2);
			}

			else if (tileinfo[i][j].terrain == TR_BRIDGE)
			{
				tempRc = { 400 + 3 * j, 50 + 3 * i, 400 + 3 * j + 3, 50 + 3 * i + 3 };
				FillRect(worldmapBuffer->GetMemDC(), &tempRc, bridgeBrush);
			}
		}
	}

}

void MapManager::SetWorldmapTileRes(TILE_POINT tp, int _tileRes)
{
	tempRc = { 400 + 3 * tp.x, 50 + 3 * tp.y, 400 + 3 * tp.x + 3, 50 + 3 * tp.y + 3 };
	switch (_tileRes)
	{
	case(COAL):
		FillRect(worldmapBuffer->GetMemDC(), &tempRc, coalBrush);
		break;
	case(IRON):
		FillRect(worldmapBuffer->GetMemDC(), &tempRc, ironBrush);
		break;
	case(COPPER):
		FillRect(worldmapBuffer->GetMemDC(), &tempRc, copperBrush);
		break;
	case(STONE):
		FillRect(worldmapBuffer->GetMemDC(), &tempRc, stoneBrush);
		break;
	}
}

void MapManager::RenderWorldmap(HDC hdc)
{
	worldmapBuffer->Render(hdc, 0, 0);

	// 플레이어
	tempRc = { 400 + 3 * ((int)p_pos.x / 32) - 5, 50 + 3 * ((int)p_pos.y / 32) - 5, 400 + 3 * ((int)p_pos.x / 32) + 3 + 5, 50 + 3 * ((int)p_pos.y / 32) + 3 + 5 };
	FillRect(hdc, &tempRc, playerBrush);

	logo->Render(hdc, 150, 80, logo->GetWidth() / 3, logo->GetHeight() / 3);

}


MapManager::MapManager()
{
	logo = ImageManager::GetSingleton()->FindImage("loadingLogo");
	grayBox = ImageManager::GetSingleton()->FindImage("grayBox");

	grassBrush = CreateSolidBrush(RGB(61, 61, 17));
	waterBrush1 = CreateSolidBrush(RGB(23, 71, 87));
	waterBrush2 = CreateSolidBrush(RGB(23, 90, 106));
	bridgeBrush = CreateSolidBrush(RGB(62, 40, 13));
	coalBrush = CreateSolidBrush(RGB(0, 0, 0));
	ironBrush = CreateSolidBrush(RGB(84, 105, 107));
	copperBrush = CreateSolidBrush(RGB(203, 97, 53));
	stoneBrush = CreateSolidBrush(RGB(120, 113, 79));
	treeBrush = CreateSolidBrush(RGB(56, 67, 28));
	playerBrush = CreateSolidBrush(RGB(209, 153, 85));
}

MapManager::~MapManager()
{
	DeleteObject(grassBrush);
}
