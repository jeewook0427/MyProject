#include "InGameScene.h"
#include "Player.h"
#include "MapManager.h"
#include "Inventory.h"
#include "Image.h"
#include "Ending.h"

HRESULT InGameScene::Init()
{
	ObjectManager::GetSingleton()->Init();
	//플레이어
	player1 = new Player();
	player1->Init();


	cameraBuffer = new Image();
	cameraBuffer->Init(WINSIZE_X, WINSIZE_Y);

	mapMgr = new MapManager();
	mapMgr->Init();

	ending = new Ending();

	isEnding = false;

	BGMIndex=0;
	BGMTime=0;
	BGMPlay = true;
	playTime = 0;
	gameOver = false;
	isLaunch = false;

	SoundManager::GetSingleton()->Play("BGM1", 1.0f);
	return S_OK;
}

void InGameScene::Release()
{
	

	cameraBuffer->Release();
	SAFE_DELETE(cameraBuffer);
	

	iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICTRANSPORTBELT);
	if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
	{
		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).end(); it++)
		{
			it->second->Release();
		}

	}

	iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STONEFURNACE);
	if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
	{
		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).end(); it++)
		{
			it->second->Release();
		}

	}

	iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(SMALLELECTRICPOLE);
	if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
	{
		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).end(); it++)
		{
			it->second->Release();
		}

	}

	iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ELECTRICFURNACE);
	if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
	{
		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).end(); it++)
		{
			it->second->Release();
		}

	}

	iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BURNERMININGDRILL);
	if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
	{
		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).end(); it++)
		{
			it->second->Release();
		}

	}

	iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ROCKET);
	if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
	{
		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).end(); it++)
		{
			it->second->Release();
		}

	}

	iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICMININGDRILL);
	if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
	{
		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).end(); it++)
		{
			it->second->Release();
		}

	}

	iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STEAMENGINE);
	if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
	{
		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).end(); it++)
		{
			it->second->Release();
		}

	}

	iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ASSEMBLINGMACHINE);
	if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
	{
		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).end(); it++)
		{
			it->second->Release();
		}

	}


	
	player1->Release();
	SAFE_DELETE(player1);

	mapMgr->Release();
	SAFE_DELETE(mapMgr);

	SAFE_DELETE(ending);
}

void InGameScene::Update()
{
	this->BGMUpdate();
	if(!gameOver)
		playTime += TimeManager::GetSingleton()->GetDeltaTime();

	if (KeyManager::GetSingleton()->IsOnceKeyDown('M') && !isEnding)
	{
		Tutorial::GetSingleton()->SucceedQuest_0();
				
		if (mapMgr->GetWorldmapOn())
			mapMgr->SetWorldmapOn(false);
		else
			mapMgr->SetWorldmapOn(true);
	}

	if (gameOver)
	{
		isEnding = true;
	}
	
	if (isLaunch)
	{
		ToolInvenIsOpen = false;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q') && !isEnding)
	{
		Tutorial::GetSingleton()->SetHelpOpen();
	}

	if (!mapMgr->GetWorldmapOn() && !isEnding)
	{
		Tutorial::GetSingleton()->Update();

		if (player1)
			player1->Update();

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STONEFURNACE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).end(); ++it)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);


					for (int i = 0; i < 2; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							temp = { TP.x - j, TP.y - i };

							tempit = (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).find(temp);
							if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).end())
							{

								(*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).erase(temp);
							}

							EraseFromWorldmapBuffer(temp);

						}
					}

					//map<TILE_POINT, GameNode*> tempmap = *ObjectManager::GetSingleton()->GetObjectList(STONEFURNACE);
					break;
				}

			}

		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICTRANSPORTBELT);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);

					for (int i = 0; i < 1; i++)
					{
						for (int j = 0; j < 1; j++)
						{
							temp = { TP.x - j, TP.y - i };
							tempit = (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).find(temp);
							if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).end())
							{

								(*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).erase(temp);
							}

							EraseFromWorldmapBuffer(temp);

						}
					}
					//map<TILE_POINT, GameNode*> tempmap = *ObjectManager::GetSingleton()->GetObjectList(STONEFURNACE);
					break;
				}


			}

		}


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BURNERINSERTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERINSERTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BURNERINSERTER)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);


					temp = { TP.x, TP.y };
					tempit = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERINSERTER)).find(temp);
					if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(BURNERINSERTER)).end())
					{

						(*ObjectManager::GetSingleton()->FindObjectMap(BURNERINSERTER)).erase(temp);
					}

					EraseFromWorldmapBuffer(temp);
					//map<TILE_POINT, GameNode*> tempmap = *ObjectManager::GetSingleton()->GetObjectList(STONEFURNACE);
					break;
				}
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BURNERMININGDRILL);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);

					for (int i = 0; i < 2; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							temp = { TP.x - j, TP.y - i };
							tempit = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).find(temp);
							if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).end())
							{

								(*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).erase(temp);
							}

							EraseFromWorldmapBuffer(temp);

						}
					}
					//map<TILE_POINT, GameNode*> tempmap = *ObjectManager::GetSingleton()->GetObjectList(STONEFURNACE);
					break;
				}


			}

		}


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(SMALLELECTRICPOLE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);


					temp = { TP.x, TP.y };
					tempit = (*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).find(temp);
					if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).end())
					{

						(*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).erase(temp);
					}

					EraseFromWorldmapBuffer(temp);
					//map<TILE_POINT, GameNode*> tempmap = *ObjectManager::GetSingleton()->GetObjectList(STONEFURNACE);
					break;
				}
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ELECTRICFURNACE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);


					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							temp = { TP.x - j, TP.y - i };
							tempit = (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).find(temp);
							if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).end())
							{

								(*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).erase(temp);
							}

							EraseFromWorldmapBuffer(temp);
						}
					}
					break;
				}



			}

		}


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICINSERTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICINSERTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICINSERTER)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);


					temp = { TP.x, TP.y };
					tempit = (*ObjectManager::GetSingleton()->FindObjectMap(BASICINSERTER)).find(temp);
					if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(BASICINSERTER)).end())
					{

						(*ObjectManager::GetSingleton()->FindObjectMap(BASICINSERTER)).erase(temp);
					}

					EraseFromWorldmapBuffer(temp);

					//map<TILE_POINT, GameNode*> tempmap = *ObjectManager::GetSingleton()->GetObjectList(STONEFURNACE);
					break;
				}
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICMININGDRILL);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);


					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							temp = { TP.x - j, TP.y - i };
							tempit = (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).find(temp);
							if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).end())
							{

								(*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).erase(temp);
							}

							EraseFromWorldmapBuffer(temp);
						}
					}
					//map<TILE_POINT, GameNode*> tempmap = *ObjectManager::GetSingleton()->GetObjectList(STONEFURNACE);
					break;
				}


			}
		}


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STEAMENGINE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					int tempdirection;
					POINT tempindex;
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;


					tempdirection = it->second->GetDirection();
					tp = it->second->GetTilePoint();

					SAFE_DELETE(it->second);

					if (tempdirection == 0)
					{
						tempindex.y = 3;
						tempindex.x = 9;
					}

					else if (tempdirection == 1)
					{
						tempindex.y = 3;
						tempindex.x = 8;
					}
					else if (tempdirection == 2)
					{
						tempindex.y = 9;
						tempindex.x = 3;
					}
					else if (tempdirection == 3)
					{
						tempindex.y = 9;
						tempindex.x = 3;
					}


					for (int i = 0; i < tempindex.y; i++)
					{
						for (int j = 0; j < tempindex.x; j++)
						{
							temp = { TP.x - j, TP.y - i };

							tempit = (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).find(temp);
							if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).end())
							{

								(*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).erase(temp);
							}

							EraseFromWorldmapBuffer(temp);
						}
					}

					break;
				}

			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(WOODENCHEST);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(WOODENCHEST)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(WOODENCHEST)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);

					temp = { TP.x, TP.y };
					tempit = (*ObjectManager::GetSingleton()->FindObjectMap(WOODENCHEST)).find(temp);
					if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(WOODENCHEST)).end())
					{

						(*ObjectManager::GetSingleton()->FindObjectMap(WOODENCHEST)).erase(temp);
					}

					EraseFromWorldmapBuffer(temp);
					//map<TILE_POINT, GameNode*> tempmap = *ObjectManager::GetSingleton()->GetObjectList(STONEFURNACE);
					break;
				}
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STEELCHEST);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STEELCHEST)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STEELCHEST)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);

					temp = { TP.x, TP.y };
					tempit = (*ObjectManager::GetSingleton()->FindObjectMap(STEELCHEST)).find(temp);
					if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(STEELCHEST)).end())
					{

						(*ObjectManager::GetSingleton()->FindObjectMap(STEELCHEST)).erase(temp);
					}

					EraseFromWorldmapBuffer(temp);
					//map<TILE_POINT, GameNode*> tempmap = *ObjectManager::GetSingleton()->GetObjectList(STONEFURNACE);
					break;
				}
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ASSEMBLINGMACHINE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).end(); it++)
			{

				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							temp = { TP.x - j, TP.y - i };
							tempit = (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).find(temp);
							if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).end())
							{

								(*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).erase(temp);
							}

							EraseFromWorldmapBuffer(temp);
						}
					}
					//map<TILE_POINT, GameNode*> tempmap = *ObjectManager::GetSingleton()->GetObjectList(STONEFURNACE);
					break;
				}



			}
		}


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICSPLITTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					int tempdirection;
					POINT tempindex;
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;


					tempdirection = it->second->GetDirection();
					tp = it->second->GetTilePoint();

					SAFE_DELETE(it->second);

					if (tempdirection == 0)
					{
						tempindex.y = 2;
						tempindex.x = 1;
					}

					else if (tempdirection == 1)
					{
						tempindex.y = 2;
						tempindex.x = 1;
					}
					else if (tempdirection == 2)
					{
						tempindex.y = 1;
						tempindex.x = 2;
					}
					else if (tempdirection == 3)
					{
						tempindex.y = 1;
						tempindex.x = 2;
					}


					for (int i = 0; i < tempindex.y; i++)
					{
						for (int j = 0; j < tempindex.x; j++)
						{
							temp = { TP.x - j, TP.y - i };
							tempit = (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).find(temp);
							if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).end())
							{

								(*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).erase(temp);
							}

							EraseFromWorldmapBuffer(temp);
						}
					}

					break;
				}

			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(LONGHANDEDINSERTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(LONGHANDEDINSERTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(LONGHANDEDINSERTER)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);

					temp = { TP.x, TP.y };
					tempit = (*ObjectManager::GetSingleton()->FindObjectMap(LONGHANDEDINSERTER)).find(temp);
					if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(LONGHANDEDINSERTER)).end())
					{

						(*ObjectManager::GetSingleton()->FindObjectMap(LONGHANDEDINSERTER)).erase(temp);
					}

					EraseFromWorldmapBuffer(temp);

					break;
				}
			}
		}


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ROCKET);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).end(); it++)
			{
				it->second->Update();

				if (it->second->GetIsDelete())
				{
					TILE_POINT TP = it->second->GetTilePoint();
					TILE_POINT temp;
					SAFE_DELETE(it->second);
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							temp = { TP.x - j, TP.y - i };
							tempit = (*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).find(temp);
							if (tempit != (*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).end())
							{

								(*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).erase(temp);
							}

							EraseFromWorldmapBuffer(temp);

						}
					}

					break;
				}


			}
		}

		for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size();)
		{
			(*ObjectManager::GetSingleton()->FindObjectVec())[i]->Update();
			if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsDelete())
			{
				(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
				(*ObjectManager::GetSingleton()->FindObjectVec()).erase((*ObjectManager::GetSingleton()->FindObjectVec()).begin() + i);
				//it--;
			}
			else
			{
				i++;
			}

		}

		//mapMgr->Update();
	}

	else if (isEnding)
	{
		ending->Update();
	}

	
}

void InGameScene::Render(HDC hdc)
{	

	
	if (!mapMgr->GetWorldmapOn() && !isEnding)
	{

		if (mapMgr)
			mapMgr->Render(cameraBuffer->GetMemDC());
			   
		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(COAL)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(COAL)).end(); it++)
		{
			it->second->Render(cameraBuffer->GetMemDC());
		}

		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(IRON)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(IRON)).end(); it++)
		{
			it->second->Render(cameraBuffer->GetMemDC());
		}

		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(COPPER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(COPPER)).end(); it++)
		{
			it->second->Render(cameraBuffer->GetMemDC());
		}

		for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STONE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STONE)).end(); it++)
		{
			it->second->Render(cameraBuffer->GetMemDC());
		}
				

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STEAMENGINE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STONEFURNACE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STONEFURNACE)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}
				

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICTRANSPORTBELT);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICTRANSPORTBELT)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}

		// 추가한곳 //
		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BURNERMININGDRILL);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}


		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICMININGDRILL);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICMININGDRILL)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ELECTRICFURNACE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ELECTRICFURNACE)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
				
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ROCKET);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}

		for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
		{
			(*ObjectManager::GetSingleton()->FindObjectVec())[i]->Render(cameraBuffer->GetMemDC());
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(WOODENCHEST);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(WOODENCHEST)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(WOODENCHEST)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ASSEMBLINGMACHINE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICINSERTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICINSERTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICINSERTER)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BURNERINSERTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERINSERTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BURNERINSERTER)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(LONGHANDEDINSERTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(LONGHANDEDINSERTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(LONGHANDEDINSERTER)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}

		if (player1)
			player1->Render(cameraBuffer->GetMemDC());

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(BASICSPLITTER);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(BASICSPLITTER)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}
		
		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(SMALLELECTRICPOLE);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(SMALLELECTRICPOLE)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(STEELCHEST);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(STEELCHEST)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(STEELCHEST)).end(); it++)
			{
				it->second->Render(cameraBuffer->GetMemDC());
			}
		}

		if (player1)
		{
			player1->GetInventory()->ObjectRender(cameraBuffer->GetMemDC());
			player1->MouseRender(NULL, cameraBuffer->GetMemDC());
		}

		iter = (*ObjectManager::GetSingleton()->FindAllObject()).find(ROCKET);
		if (iter != (*ObjectManager::GetSingleton()->FindAllObject()).end())
		{
			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(ROCKET)).end(); it++)
			{
				it->second->RocketRender(cameraBuffer->GetMemDC());
			}
		}
		
		cameraBuffer->CamaraRender(hdc, g_pos.x, g_pos.y, p_pos.x, p_pos.y, WINSIZE_X, WINSIZE_Y, cameraScale);

		if (player1)
		{
			player1->GetInventory()->Render(hdc);
			player1->MouseRender(hdc, NULL);
		}
			

		Tutorial::GetSingleton()->Render(hdc);
		Tutorial::GetSingleton()->HelpRender(hdc);

		mapMgr->RenderMinimap(hdc);

	}

	else if (mapMgr->GetWorldmapOn())
	{
		mapMgr->RenderWorldmap(hdc);
	}
	
	else
	{
		ending->Render(hdc);
	}
	
	//cameraBuffer->Render(hdc, 0,0);

}

void InGameScene::EraseFromWorldmapBuffer(TILE_POINT _tp)
{
	RECT tempRc;

	tempRc = { 400 + 3 * (_tp.x), 50 + 3 * (_tp.y), 400 + 3 * (_tp.x) + 3, 50 + 3 * (_tp.y) + 3 };

	// 자원이 있을때
	if (tileinfo[_tp.y][(_tp.x)].res == COAL)
	{
		FillRect(worldmapBuffer->GetMemDC(), &tempRc, coalBrush);
	}
	else if (tileinfo[_tp.y][_tp.x].res == IRON)
	{
		FillRect(worldmapBuffer->GetMemDC(), &tempRc, ironBrush);
	}
	else if (tileinfo[_tp.y][_tp.x].res == COPPER)
	{
		FillRect(worldmapBuffer->GetMemDC(), &tempRc, copperBrush);
	}
	else if (tileinfo[_tp.y][_tp.x].res == STONE)
	{
		FillRect(worldmapBuffer->GetMemDC(), &tempRc, stoneBrush);
	}

	// 자원이 없을때
	else if (tileinfo[_tp.y][_tp.x].terrain == TR_GRASS)
	{
		FillRect(worldmapBuffer->GetMemDC(), &tempRc, grassBrush);
	}
	else if (tileinfo[_tp.y][_tp.x].terrain == TR_WATER)
	{
		if (tileinfo[_tp.y][_tp.x].frameY < 4)
			FillRect(worldmapBuffer->GetMemDC(), &tempRc, waterBrush1);
		else
			FillRect(worldmapBuffer->GetMemDC(), &tempRc, waterBrush2);
	}
	else if (tileinfo[_tp.y][_tp.x].terrain == TR_BRIDGE)
	{
		FillRect(worldmapBuffer->GetMemDC(), &tempRc, bridgeBrush);
	}
}

void InGameScene::BGMUpdate()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	{
		BGMPlay = !BGMPlay;
		
		if(BGMPlay)
		{
			if (BGMIndex == 0)
				SoundManager::GetSingleton()->Resume("BGM1");

			else if (BGMIndex == 1)
				SoundManager::GetSingleton()->Resume("BGM2");

			else if (BGMIndex == 2)
				SoundManager::GetSingleton()->Resume("BGM3");

		}
	}

	if (BGMPlay)
	{
		BGMTime += TimeManager::GetSingleton()->GetDeltaTime();
		if (BGMIndex == 0)
		{
			if (BGMTime > 300)
			{
				SoundManager::GetSingleton()->Play("BGM2", 1.0f);
				BGMTime = 0;
				BGMIndex = 1;
			}

		}

		else if (BGMIndex == 1)
		{
			if (BGMTime > 165)
			{
				SoundManager::GetSingleton()->Play("BGM3", 1.0f);
				BGMTime = 0;
				BGMIndex = 2;
			}

		}

		else if (BGMIndex == 2)
		{
			if (BGMTime > 280)
			{
				SoundManager::GetSingleton()->Play("BGM1", 1.0f);
				BGMTime = 0;
				BGMIndex = 0;
			}

		}
	}

	if (!BGMPlay)
	{
	
		if (BGMIndex == 0)
			SoundManager::GetSingleton()->Pause("BGM1");

		else if (BGMIndex == 1)
			SoundManager::GetSingleton()->Pause("BGM2");

		else if (BGMIndex == 2)
			SoundManager::GetSingleton()->Pause("BGM3");

	}

}


InGameScene::InGameScene()
{
	worldmapBuffer = ImageManager::GetSingleton()->FindImage("worldmapBuffer");

	grassBrush = CreateSolidBrush(RGB(61, 61, 17));
	waterBrush1 = CreateSolidBrush(RGB(23, 71, 87));
	waterBrush2 = CreateSolidBrush(RGB(23, 90, 106));
	bridgeBrush = CreateSolidBrush(RGB(62, 40, 13));
	coalBrush = CreateSolidBrush(RGB(0, 0, 0));
	ironBrush = CreateSolidBrush(RGB(84, 105, 107));
	copperBrush = CreateSolidBrush(RGB(203, 97, 53));
	stoneBrush = CreateSolidBrush(RGB(120, 113, 79));


}

InGameScene::~InGameScene()
{
	DeleteObject(grassBrush);
	DeleteObject(waterBrush1);
	DeleteObject(waterBrush2);
	DeleteObject(bridgeBrush);
	DeleteObject(coalBrush);
	DeleteObject(ironBrush);
	DeleteObject(copperBrush);
	DeleteObject(stoneBrush);

}

