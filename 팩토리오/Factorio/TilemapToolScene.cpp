#include "TilemapToolScene.h"
#include "Image.h"
#include "macroFunction.h"

HRESULT TilemapToolScene::Init()
{
	sampleTileImage = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/maptiles.bmp", 0, 0, 640, 288, SAMPLE_TERRAIN_X, SAMPLE_TERRAIN_Y);

	isDownSampleArea = false;

	rcSave = GetRectToCenter(WINSIZE_X - sampleTileImage->GetWidth(), 660, 120, 80);

	rcLoad = GetRectToCenter(WINSIZE_X - sampleTileImage->GetWidth() + 140, 660, 120, 80);

	//선택한 타일 초기화
	selectTileInfo.frameX = 0;
	selectTileInfo.frameY = 0;

	selectTileInfos[0].frameX = 0;
	selectTileInfos[0].frameY = 0;
	selectTileInfos[1].frameX = 0;
	selectTileInfos[1].frameY = 0;

	isDragFilled = false;

	dragSizeX = 0;
	dragSizeY = 0;
	minX = 0; maxX = 0; minY = 0; maxY = 0;

	//오른쪽에 샘플 타일의 RECT를 설정한다.
	for (int i = 0; i < SAMPLE_TERRAIN_Y; i++)
	{
		for (int j = 0; j < SAMPLE_TERRAIN_X; j++)
		{
			sampleTileInfo[i * SAMPLE_TERRAIN_X + j].frameX = j;
			sampleTileInfo[i * SAMPLE_TERRAIN_X + j].frameY = i;

			SetRect(&sampleTileInfo[i * SAMPLE_TERRAIN_X + j].rcTile,
				WINSIZE_X - sampleTileImage->GetWidth() + j * TILESIZE, i * TILESIZE,
				WINSIZE_X - sampleTileImage->GetWidth() + j * TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
		}
	}

	//왼쪽에 메인 타일의 RECT를 설정한다.
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			SetRect(&tileInfo[i*TILE_X + j].rcTile, j * TILESIZE, i * TILESIZE, j * TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
		}
	}

	//왼쪽에 그려질 내용을 초기화 한다.(기본적으로 잔디로 설정)
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		tileInfo[i].frameX = 3;
		tileInfo[i].frameY = 0;
		
	}

	return S_OK;
}

void TilemapToolScene::Release()
{
}

void TilemapToolScene::Update()
{
	//마우스 왼쪽 버튼을 눌렀을 때
	// 1. 샘플타일 선택 2. 메인타일 선택

	//마우스 왼쪽 버튼을 뗐을 때
	// 1. 샘플타일에서 선택 2. 메인 타일에서 선택

	//마우스가 클릭한 상태로 이동 될 때(드래그)

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{	
		if (PtInRect(&rcSave, g_ptMouse))
		{
			Save();
		}

		else if (PtInRect(&rcLoad, g_ptMouse))
		{
			Load();
		}


		for (int i = 0; i < SAMPLE_TERRAIN_X * SAMPLE_TERRAIN_Y; i++)
		{
			if (PtInRect(&sampleTileInfo[i].rcTile, g_ptMouse))
			{
				selectTileInfo.frameX = sampleTileInfo[i].frameX;
				selectTileInfo.frameY = sampleTileInfo[i].frameY;

				selectTileInfos[0].frameX = sampleTileInfo[i].frameX;
				selectTileInfos[0].frameY = sampleTileInfo[i].frameY;

				isDownSampleArea = true;
				break;
			}
		}

		if (isDragFilled) 
		{
			for (int i = 0; i < TILE_X * TILE_Y; i++)
			{
				if (PtInRect(&tileInfo[i].rcTile, g_ptMouse))
				{
					for (int y = 0; y <= dragSizeY; y++)
					{
						for (int x = 0; x <= dragSizeX; x++)
						{
							if (((i % TILE_X) + x < TILE_X) && ((i / TILE_X) + y < TILE_Y))
							{
								tileInfo[i + y * TILE_X + x].frameX = minX + x;
								tileInfo[i + y * TILE_X + x].frameY = minY + y;
							}
						}
					}
				}
			}
		}
	}

	else if (!isDownSampleArea && KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < TILE_X * TILE_Y; i++)
		{
			if (PtInRect(&tileInfo[i].rcTile, g_ptMouse))
			{
				tileInfo[i].frameX = selectTileInfo.frameX;
				tileInfo[i].frameY = selectTileInfo.frameY;
				break;
			}
		}
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{
		if (isDownSampleArea) {
			for (int i = 0; i < SAMPLE_TERRAIN_X * SAMPLE_TERRAIN_Y; i++)
			{
				if (PtInRect(&sampleTileInfo[i].rcTile, g_ptMouse))
				{
					selectTileInfos[1].frameX = sampleTileInfo[i].frameX;
					selectTileInfos[1].frameY = sampleTileInfo[i].frameY;

					//드래그 영역 값을 정렬
					minX = min(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
					maxX = max(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
					minY = min(selectTileInfos[0].frameY, selectTileInfos[1].frameY);
					maxY = max(selectTileInfos[0].frameY, selectTileInfos[1].frameY);

					dragSizeX = maxX - minX;
					dragSizeY = maxY - minY;

					isDownSampleArea = false;
					isDragFilled = true;
					
					break;
				}
			}
		}

		for (int i = 0; i < TILE_X * TILE_Y; i++)
		{
			if (PtInRect(&tileInfo[i].rcTile, g_ptMouse))
			{
				tileInfo[i].frameX = selectTileInfo.frameX;
				tileInfo[i].frameY = selectTileInfo.frameY;
				break;
			}
		}

	}

}

void TilemapToolScene::Render(HDC hdc)
{
	//바탕색 칠하기
	PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	//선택한 타일
	sampleTileImage->FrameRender(hdc, WINSIZE_X - sampleTileImage->GetWidth(), sampleTileImage->GetHeight() + 50,
		selectTileInfo.frameX, selectTileInfo.frameY);

	//드래그 선택된 샘플 타일
	for (int y = 0; y <= dragSizeY; y++)
	{
		for (int x = 0; x <= dragSizeX; x++)
		{
			sampleTileImage->FrameRender(hdc, 
				WINSIZE_X - sampleTileImage->GetWidth() + (x * TILESIZE),
				sampleTileImage->GetHeight() + 50 + (y * TILESIZE),
				minX + x, minY + y);
		}
	}

	//왼쪽 메인 타일
	for (int i = 0; i < TILE_X * TILE_Y; i++)
	{
		sampleTileImage->FrameRender(hdc,
			tileInfo[i].rcTile.left + (TILESIZE / 2), tileInfo[i].rcTile.top + (TILESIZE / 2)
			, tileInfo[i].frameX, tileInfo[i].frameY);
	}


	//오른쪽 타일맵 샘플 그리기
	sampleTileImage->Render(hdc, WINSIZE_X - sampleTileImage->GetWidth(), 0);

	//save, load Rect
	Rectangle(hdc, rcSave.left, rcSave.top, rcSave.right, rcSave.bottom);
	TextOut(hdc, rcSave.left + 20, rcSave.top + 20, "세이브", strlen("세이브"));
	Rectangle(hdc, rcLoad.left, rcLoad.top, rcLoad.right, rcLoad.bottom);
	TextOut(hdc, rcLoad.left + 20, rcLoad.top + 20, "로드", strlen("로드"));

}

void TilemapToolScene::Save()
{
	DWORD writtenByte;
	HANDLE hFile = CreateFile("Save/saveMapData.map",GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &writtenByte, NULL);
	CloseHandle(hFile);
}

void TilemapToolScene::Load()
{
	DWORD ReadByte;
	HANDLE hFile = CreateFile("Save/saveMapData.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &ReadByte, NULL);
	CloseHandle(hFile);
}

TilemapToolScene::TilemapToolScene()
{
}

TilemapToolScene::~TilemapToolScene()
{
}
