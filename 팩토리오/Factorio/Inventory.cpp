#include "Inventory.h"
#include "Image.h"
#include "StoneFernace.h"
#include "BasicTransportBelt.h"
#include "BurnerInserter.h"
#include "BurnerMiningDrill.h"
#include "Rocket.h"
#include "CraftItemInfo.h"
#include "SmallElecTricPole.h"
#include "SteamEngine.h"
#include "ElectricFurnace.h"
#include "BasicMiningDrill.h"
#include "BasicInserter.h"
#include "WoodBox.h"
#include "AssemblingMachine.h"
#include "BasicSplitter.h"
#include "LongHandedInserter.h"
#include "SteelBox.h"

INVENINFO inveninfo[9][10];
bool ToolInvenIsOpen;

HRESULT Inventory::Init()
{
	beltinfo = 0;
	splitterDirection = 0;
	
	isWidthReverse = false;
	isHeightReverse = false;
	//좌표
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y / 2;

	//베이스 RECT
	baseRc = GetRectToCenter(pos.x, pos.y, 857, 422);
	quickRc = GetRectToCenter(pos.x, WINSIZE_Y - 29, 500, 63);

	//기본 베이스 이미지
	inventory = ImageManager::GetSingleton()->FindImage("inventory");
	fastinventory = ImageManager::GetSingleton()->FindImage("fastinventory");
	blueRectangle = ImageManager::GetSingleton()->FindImage("blue-rectangle");

	// 이미지
	stoneFurnace = ImageManager::GetSingleton()->FindImage("stone-furnace");
	basicTransportBelt = ImageManager::GetSingleton()->FindImage("basic-transport-belt");
	burnerInserter = ImageManager::GetSingleton()->FindImage("burner-inserter-platform");
	burnerMiningDrillEast = ImageManager::GetSingleton()->FindImage("burner-mining-drill-east");
	rocketBase = ImageManager::GetSingleton()->FindImage("rocket-base");
	smallElectricPole = ImageManager::GetSingleton()->FindImage("small-electric-pole");
	basicInserter = ImageManager::GetSingleton()->FindImage("basic-inserter-platform");
	basicMiningDrillEast = ImageManager::GetSingleton()->FindImage("basic-mining-drill-east");
	electricFurnace = ImageManager::GetSingleton()->FindImage("electric-furnace");
	assemblingMachine = ImageManager::GetSingleton()->FindImage("assembling-machine");
	basicSplitter = ImageManager::GetSingleton()->FindImage("basic-splitter-east");
	steamEngine = ImageManager::GetSingleton()->FindImage("steam-engine-horizontal");
	steamEngineIcon = ImageManager::GetSingleton()->FindImage("steam-engine-icon");
	boiler = ImageManager::GetSingleton()->FindImage("boiler-left"); 
	offshorePump = ImageManager::GetSingleton()->FindImage("offshore-pump");
	assemblinginven = ImageManager::GetSingleton()->FindImage("assemblinginven"); 
	longHandedInster = ImageManager::GetSingleton()->FindImage("long-handed-inserter-platform");

	steamEngineInfo = 0;

	// 아이콘
	icon[COAL] = ImageManager::GetSingleton()->FindImage("coal-icon");
	icon[IRON] = ImageManager::GetSingleton()->FindImage("iron-icon");
	icon[COPPER] = ImageManager::GetSingleton()->FindImage("copper-icon");
	icon[TREE] = ImageManager::GetSingleton()->FindImage("raw-wood-icon");
	icon[STONE] = ImageManager::GetSingleton()->FindImage("stone-icon");
	icon[BURNERINSERTER] = ImageManager::GetSingleton()->FindImage("burner-inserter-icon");
	icon[BURNERMININGDRILL] = ImageManager::GetSingleton()->FindImage("burner-mining-drill-icon");
	icon[BASICTRANSPORTBELT] = ImageManager::GetSingleton()->FindImage("basic-transport-belt-icon");
	icon[STONEFURNACE] = ImageManager::GetSingleton()->FindImage("stone-furnace-icon");
	icon[IRONAXE] = ImageManager::GetSingleton()->FindImage("iron-axe-icon");
	icon[IRONGEARWHEEL] = ImageManager::GetSingleton()->FindImage("iron-gear-wheel-icon");
	icon[IRONPLATE] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");
	icon[STEELCHEST] = ImageManager::GetSingleton()->FindImage("steel-chest-icon");
	icon[WOODENCHEST] = ImageManager::GetSingleton()->FindImage("wooden-chest-icon");
	icon[COPPERPLATE] = ImageManager::GetSingleton()->FindImage("copper-plate-icon");
	icon[ELECTRONICCIRCUIT] = ImageManager::GetSingleton()->FindImage("electronic-circuit-icon");
	icon[IRONSTICK] = ImageManager::GetSingleton()->FindImage("iron-stick-icon");
	icon[COPPERCABLE] = ImageManager::GetSingleton()->FindImage("copper-cable-icon");
	icon[WOOD] = ImageManager::GetSingleton()->FindImage("wood-icon");
	icon[ROCKET] = ImageManager::GetSingleton()->FindImage("rocket-icon");
	icon[SMALLELECTRICPOLE] = ImageManager::GetSingleton()->FindImage("small-electric-pole-icon");
	icon[ELECTRICFURNACE] = ImageManager::GetSingleton()->FindImage("electric-furnace-icon");
	icon[BASICINSERTER] = ImageManager::GetSingleton()->FindImage("basic-inserter-icon");
	icon[BASICMININGDRILL] = ImageManager::GetSingleton()->FindImage("basic-mining-drill-icon");
	icon[STEAMENGINE] = ImageManager::GetSingleton()->FindImage("steam-engine-icon");
	icon[ASSEMBLINGMACHINE] = ImageManager::GetSingleton()->FindImage("assembling-machine-icon");
	icon[WOODENCHEST] = ImageManager::GetSingleton()->FindImage("wooden-chest-icon");
	icon[ADVANCEDCIRCUIT] = ImageManager::GetSingleton()->FindImage("advanced-circuit-icon");
	icon[BASICSPLITTER] = ImageManager::GetSingleton()->FindImage("basic-splitter-icon");
	icon[LONGHANDEDINSERTER] = ImageManager::GetSingleton()->FindImage("long-handed-inserter-icon");

	//열기닫기
	isOpen = false;
	isSelect = false;
	
	selectIndexX = 0;
	selectIndexY = 0;

	tempIndex.x = 0;
	tempIndex.y = 0;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//inveninfo[i][j].rc = { (int)(pos.x - 419 + 41*j),(int)(pos.y - 167 + 41*i), (int)(pos.x - 419 + 41*j) + 38,(int)(pos.y - 167 + 41*i) + 38 };
			inveninfo[i][j].rc = { (int)(pos.x - 416 + 41 * j),(int)(pos.y - 164 + 41 * i), (int)(pos.x - 416 + 41 * j) + 39,(int)(pos.y - 164 + 41 * i) + 39 };
			inveninfo[i][j].num = 0;
			inveninfo[i][j].isStorage = false;
			inveninfo[i][j].name = EMPTY;
			inveninfo[i][j].isSelected = false;
			if (i == 8)
			{
				inveninfo[i][j].rc = { (int)(pos.x - 210 + j * 38),WINSIZE_Y - 48, (int)(pos.x - 210 + j * 38) + 38,WINSIZE_Y - 48 + 38 };\
				if(j>=5)
					inveninfo[i][j].rc={ (int)(pos.x - 170 + j * 38), WINSIZE_Y - 48, (int)(pos.x - 170 + j * 38) + 38, WINSIZE_Y - 48 + 38 };
			}
		}
	}

	/*inveninfo[0][0].num = 2;
	inveninfo[0][0].name = STONEFURNACE;
	inveninfo[0][0].isStorage = true;

	inveninfo[0][1].num = 2;
	inveninfo[0][1].name = BURNERMININGDRILL;
	inveninfo[0][1].isStorage = true;

	inveninfo[0][2].num = 2;
	inveninfo[0][2].name = BURNERINSERTER;
	inveninfo[0][2].isStorage = true;

	inveninfo[0][3].num = 50;
	inveninfo[0][3].name = STONE;
	inveninfo[0][3].isStorage = true;

	inveninfo[0][4].num = 30;
	inveninfo[0][4].name = IRON;
	inveninfo[0][4].isStorage = true;

	inveninfo[0][5].num = 30;
	inveninfo[0][5].name = COPPER;
	inveninfo[0][5].isStorage = true;

	inveninfo[0][6].num = 30;
	inveninfo[0][6].name = COAL;
	inveninfo[0][6].isStorage = true;
*/



	inveninfo[0][0].num = 100;
	inveninfo[0][0].name = COAL;
	inveninfo[0][0].isStorage = true;

	inveninfo[1][0].num = 500;
	inveninfo[1][0].name = IRONPLATE;
	inveninfo[1][0].isStorage = true;

	inveninfo[2][0].num = 500;
	inveninfo[2][0].name = COPPERPLATE;
	inveninfo[2][0].isStorage = true;
	
	inveninfo[2][1].num = 500;
	inveninfo[2][1].name = BASICSPLITTER;
	inveninfo[2][1].isStorage = true;

	inveninfo[5][5].num = 30;
	inveninfo[5][5].name = COAL;
	inveninfo[5][5].isStorage = true;

	inveninfo[8][0].num = 40;
	inveninfo[8][0].name = COAL;
	inveninfo[8][0].isStorage = true;

	inveninfo[6][5].num = 500;
	inveninfo[6][5].name = STONE;
	inveninfo[6][5].isStorage = true;

	inveninfo[3][2].num = 10;
	inveninfo[3][2].name = STONEFURNACE;
	inveninfo[3][2].isStorage = true;

	inveninfo[3][3].num = 20;
	inveninfo[3][3].name = IRON;
	inveninfo[3][3].isStorage = true;

	inveninfo[3][4].num = 20;
	inveninfo[3][4].name = WOOD;
	inveninfo[3][4].isStorage = true;

	inveninfo[3][5].num = 20;
	inveninfo[3][5].name = BASICTRANSPORTBELT;
	inveninfo[3][5].isStorage = true;

	inveninfo[4][2].num = 10;
	inveninfo[4][2].name = BURNERINSERTER;
	inveninfo[4][2].isStorage = true;

	inveninfo[5][2].num = 10;
	inveninfo[5][2].name = BURNERMININGDRILL;
	inveninfo[5][2].isStorage = true;
	
	inveninfo[5][3].num = 1;
	inveninfo[5][3].name = ROCKET;
	inveninfo[5][3].isStorage = true;

	inveninfo[0][1].num = 20;
	inveninfo[0][1].name = SMALLELECTRICPOLE;
	inveninfo[0][1].isStorage = true;
	
	inveninfo[0][3].num = 10;
	inveninfo[0][3].name = ELECTRICFURNACE;
	inveninfo[0][3].isStorage = true;

	inveninfo[0][4].num = 10;
	inveninfo[0][4].name = BASICINSERTER;
	inveninfo[0][4].isStorage = true;

	inveninfo[0][5].num = 10;
	inveninfo[0][5].name = BASICMININGDRILL;
	inveninfo[0][5].isStorage = true;

	inveninfo[0][6].num = 10;
	inveninfo[0][6].name = STEAMENGINE;
	inveninfo[0][6].isStorage = true;

	inveninfo[3][6].num = 20;
	inveninfo[3][6].name = ASSEMBLINGMACHINE;
	inveninfo[3][6].isStorage = true;

	inveninfo[3][7].num = 20;
	inveninfo[3][7].name = LONGHANDEDINSERTER;
	inveninfo[3][7].isStorage = true;

	inveninfo[6][0].num = 100;
	inveninfo[6][0].name = ELECTRONICCIRCUIT;
	inveninfo[6][0].isStorage = true;

	inveninfo[6][1].num = 100;
	inveninfo[6][1].name = ADVANCEDCIRCUIT;
	inveninfo[6][1].isStorage = true;
	//ToolInven

	GrayBrush = CreateSolidBrush(RGB(86, 84, 84));
	RedBrush = CreateSolidBrush(RGB(200, 50, 50));
	GreenBrush = CreateSolidBrush(RGB(50, 200, 50));
	YellowBrush = CreateSolidBrush(RGB(187, 187, 0));
	
	OldBrush = (HBRUSH)SelectObject(GetDC(g_hWnd), GrayBrush);
	ToolInvenInit();
	CraftInvenInit();

	return S_OK;  
}

void Inventory::Release()
{
	SelectObject(GetDC(g_hWnd), OldBrush);
	DeleteObject(OldBrush);
	DeleteObject(GrayBrush);
	DeleteObject(RedBrush);
	DeleteObject(GreenBrush);

	for (int k = 0; k < 4; ++k)
	{
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 6; ++j)
			{
				SAFE_DELETE(craftItemInfo[k][i][j]);
			}
		}
	}
}

void Inventory::Update()
{
	CraftWaitingQueue::GetSingleton()->Update();

	/*POINT mousePos;
	mousePos.x = g_ptMouse.x + g_pos.x - WINSIZE_X / 2;
	mousePos.y = g_ptMouse.y + g_pos.y - WINSIZE_Y / 2;*/

	ToolInvenUpdate();

	if (KeyManager::GetSingleton()->IsOnceKeyDown('E') && !ToolInvenIsOpen && !isLaunch)
	{
		Tutorial::GetSingleton()->SucceedQuest_1();

		isOpen = !isOpen;
		if (!isOpen) 
			SoundManager::GetSingleton()->Play("invenclose", 0.3f);
		else 
			SoundManager::GetSingleton()->Play("invenopen", 0.3f);

		if (isOpen)
		{
			for (int k = 0; k < 4; ++k)
			{
				for (int i = 0; i < 6; ++i)
				{
					for (int j = 0; j < 6; ++j)
					{
						if (craftItemInfo[k][i][j])
						{
							craftItemInfo[k][i][j]->CheckProduct();
						}
					}
				}
			}
		}
	}
	
	else if (KeyManager::GetSingleton()->IsOnceKeyUp('E') && ToolInvenIsOpen)
	{
		ToolInvenIsOpen = !ToolInvenIsOpen;
		SoundManager::GetSingleton()->Play("invenclose", 0.3f);
		
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				inveninfo[i][j].isStorage = toolInvenInfo[i][j].isStorage;
				inveninfo[i][j].name = toolInvenInfo[i][j].name;
				inveninfo[i][j].num = toolInvenInfo[i][j].num;
			}
		}

		for (int i = 9; i < 12; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				toolInvenInfo[i][j].isStorage = false;
				toolInvenInfo[i][j].name = EMPTY;
				toolInvenInfo[i][j].num = 0;
			}
		}

		ToolInvenIsBackUp = false;
	}

	if (ToolInvenIsOpen)
	{
		isOpen = false;
	}
	if (!ToolInvenIsOpen)
	{
		if(isOpen)
			CraftInvenUpdate();

		if (isSelect)
		{
			for (int i = ((int)(g_pos.y - WINSIZE_Y / 2) / 32); i < ((int)(g_pos.y - WINSIZE_Y / 2) / 32) + 30; ++i)
			{
				for (int j = ((int)(g_pos.x - 800) / 32); j < ((int)(g_pos.x - 800) / 32) + 52; ++j)
				{
					if (PtInRect(&tileinfo[i][j].rcTile, mousepos))
					{
						tempIndex.x = j;
						tempIndex.y = i;
					}
				}
			}
		}
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			map<Layer, map<TILE_POINT, GameNode*>>::iterator it;
			GameNode* tempnode = nullptr;
			TILE_POINT temppoint;
			POINT tilesize = { 0,0 };


			if (isSelect)
			{
				bool isClear = false;
				if ((isOpen && !(PtInRect(&baseRc, g_ptMouse) || PtInRect(&quickRc, g_ptMouse))) && !ToolInvenIsOpen
					|| (!isOpen && !PtInRect(&quickRc, g_ptMouse)) && !ToolInvenIsOpen)
				{
					if (inveninfo[selectIndexY][selectIndexX].isSelected) //&& inveninfo[selectIndexY][selectIndexX].name == STONEFURNACE)
					{
						if (inveninfo[selectIndexY][selectIndexX].name == STONEFURNACE)
						{
							tilesize.x = 2;
							tilesize.y = 2;
							
							
						}
						else if (inveninfo[selectIndexY][selectIndexX].name == BASICTRANSPORTBELT)
						{
							tilesize.x = 1;
							tilesize.y = 1;
							
							
						}

						
						else if (inveninfo[selectIndexY][selectIndexX].name == BURNERINSERTER)
						{
							tilesize.x = 1;
							tilesize.y = 1;
							
							
						}

						else if (inveninfo[selectIndexY][selectIndexX].name == BURNERMININGDRILL)
						{
							tilesize.x = 2;
							tilesize.y = 2;
							
							
						}

						else if (inveninfo[selectIndexY][selectIndexX].name == ROCKET)
						{
							tilesize.x = 9;
							tilesize.y = 10;
							
						}

						else if (inveninfo[selectIndexY][selectIndexX].name == SMALLELECTRICPOLE)
						{
							tilesize.x = 1;
							tilesize.y = 1;
							
							
						}

						else if (inveninfo[selectIndexY][selectIndexX].name == BASICINSERTER)
						{
							tilesize.x = 1;
							tilesize.y = 1;
							
							
						}


						else if (inveninfo[selectIndexY][selectIndexX].name == ELECTRICFURNACE)
						{
							tilesize.x = 3;
							tilesize.y = 3;
							
							
						}

						else if (inveninfo[selectIndexY][selectIndexX].name == BASICMININGDRILL)
						{
							tilesize.x = 3;
							tilesize.y = 3;
							
							
						}

						else if (inveninfo[selectIndexY][selectIndexX].name == WOODENCHEST)
						{
							tilesize.x = 1;
							tilesize.y = 1;
							
						}

						else if (inveninfo[selectIndexY][selectIndexX].name == STEELCHEST)
						{
							tilesize.x = 1;
							tilesize.y = 1;

						}

						else if (inveninfo[selectIndexY][selectIndexX].name == ASSEMBLINGMACHINE)
						{
							tilesize.x = 3;
							tilesize.y = 3;
							
						}

						// 추가한곳 // 
						else if (inveninfo[selectIndexY][selectIndexX].name == STEAMENGINE)
						{
							if (steamEngineInfo == 0)
							{
								tilesize.x = 9;
								tilesize.y = 3;
							}

							else if (steamEngineInfo == 1)
							{
								tilesize.x = 8;
								tilesize.y = 3;
							}

							else if (steamEngineInfo == 2)
							{
								tilesize.x = 3;
								tilesize.y = 9;
							}

							else
							{
								tilesize.x = 3;
								tilesize.y = 9;
							}
							
							
							

						}

						else if (inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER)
						{
							if (splitterDirection == 0)
							{
								tilesize.x = 1;
								tilesize.y = 2;
							}

							else if (splitterDirection == 1)
							{
								tilesize.x = 1;
								tilesize.y = 2;
							}

							else if (splitterDirection == 2)
							{
								tilesize.x = 2;
								tilesize.y = 1;
							}

							else
							{
								tilesize.x = 2;
								tilesize.y = 1;
							}

						

						}

						else if (inveninfo[selectIndexY][selectIndexX].name == LONGHANDEDINSERTER)
						{
							tilesize.x = 1;
							tilesize.y = 1;
							

						}

						for (int i = 0; i < tilesize.y; i++)
						{
							for (int j = 0; j < tilesize.x; j++)
							{
								if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY)
								{
									isClear = false;
									goto skip;
								}

								else
								{
									isClear = true;
								}
							}
						}

						
						if (inveninfo[selectIndexY][selectIndexX].name == BURNERMININGDRILL 
							|| inveninfo[selectIndexY][selectIndexX].name == BASICMININGDRILL)
						{
							for (int i = 0; i < tilesize.y; i++)
							{
								for (int j = 0; j < tilesize.x; j++)
								{
									if (tileinfo[tempIndex.y - i][tempIndex.x - j].res != EMPTY)
										goto skip;
								}
							}

							isClear = false;
						}
						// 추가한곳 // 
						if (inveninfo[selectIndexY][selectIndexX].name == STEAMENGINE)
						{
							if (steamEngineInfo == 0)
							{								
								if (tileinfo[tempIndex.y][tempIndex.x-1].terrain == TR_WATER && tileinfo[tempIndex.y][tempIndex.x-2].terrain != TR_WATER)
									goto skip;
								
							}

							else if (steamEngineInfo == 1)
							{

								if (tileinfo[tempIndex.y+1][tempIndex.x - 6].terrain == TR_WATER && tileinfo[tempIndex.y+1][tempIndex.x-5].terrain != TR_WATER)
									goto skip;

							}

							else if (steamEngineInfo == 2)
							{
								if (tileinfo[tempIndex.y - 5][tempIndex.x].terrain == TR_WATER && tileinfo[tempIndex.y-4][tempIndex.x].terrain != TR_WATER)
									goto skip;
							}

							else
							{
								if (tileinfo[tempIndex.y][tempIndex.x].terrain == TR_WATER && tileinfo[tempIndex.y-1][tempIndex.x].terrain != TR_WATER)
									goto skip;

							}
							

							isClear = false;
						}

					skip:
						
						

						// 오브젝트가 없어서 건설이 가능
						if (isClear)
						{
							//임시수정
							if (inveninfo[selectIndexY][selectIndexX].name == STONEFURNACE)
							{

								tempnode = new StoneFernace({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100);

							}
							else if (inveninfo[selectIndexY][selectIndexX].name == BASICTRANSPORTBELT)
							{

								tempnode = new BasicTransportBelt({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100, beltinfo);

							}


							else if (inveninfo[selectIndexY][selectIndexX].name == BURNERINSERTER)
							{

								tempnode = new BurnerInserter({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100);

							}

							else if (inveninfo[selectIndexY][selectIndexX].name == BURNERMININGDRILL)
							{

								tempnode = new BurnerMiningDrill({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100);

							}

							else if (inveninfo[selectIndexY][selectIndexX].name == ROCKET)
							{

								tempnode = new Rocket({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100);
							}

							else if (inveninfo[selectIndexY][selectIndexX].name == SMALLELECTRICPOLE)
							{

								tempnode = new SmallElecTricPole({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100);

							}

							else if (inveninfo[selectIndexY][selectIndexX].name == BASICINSERTER)
							{

								tempnode = new BasicInserter({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100);

							}


							else if (inveninfo[selectIndexY][selectIndexX].name == ELECTRICFURNACE)
							{

								tempnode = new ElectricFurnace({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100);

							}

							else if (inveninfo[selectIndexY][selectIndexX].name == BASICMININGDRILL)
							{

								tempnode = new BasicMiningDrill({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100);

							}

							else if (inveninfo[selectIndexY][selectIndexX].name == WOODENCHEST)
							{

								tempnode = new WoodBox({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100);
							}

							else if (inveninfo[selectIndexY][selectIndexX].name == ASSEMBLINGMACHINE)
							{

								tempnode = new AssemblingMachine({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100);
							}

							// 추가한곳 // 
							else if (inveninfo[selectIndexY][selectIndexX].name == STEAMENGINE)
							{


								tempnode = new SteamEngine({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100, steamEngineInfo);


							}

							else if (inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER)
							{

								tempnode = new BasicSplitter({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100, splitterDirection);

							}

							else if (inveninfo[selectIndexY][selectIndexX].name == LONGHANDEDINSERTER)
							{
								tempnode = new LongHandedInserter({ (int)(mousepos.x) / 32,
												(int)(mousepos.y) / 32 }, 100);

							}

							else if (inveninfo[selectIndexY][selectIndexX].name == STEELCHEST)
							{
							tempnode = new SteelBox({ (int)(mousepos.x) / 32,
											(int)(mousepos.y) / 32 }, 100);

							}

							it = (*ObjectManager::GetSingleton()->FindAllObject()).find(inveninfo[selectIndexY][selectIndexX].name);
							
							if (it != (*ObjectManager::GetSingleton()->FindAllObject()).end())
							{
								for (int i = 0; i < tilesize.y; i++)
								{
									for (int j = 0; j < tilesize.x; j++)
									{
										
										temppoint = { (int)(mousepos.x) / 32 - j
										, (int)(mousepos.y) / 32 - i };
										(*ObjectManager::GetSingleton()->FindObjectMap(inveninfo[selectIndexY][selectIndexX].name)).insert(make_pair(temppoint, tempnode));
										tileinfo[(int)(mousepos.y) / 32 - i][(int)(mousepos.x) / 32 - j].obj = inveninfo[selectIndexY][selectIndexX].name;


										if (inveninfo[selectIndexY][selectIndexX].name == BASICTRANSPORTBELT || inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER)
										{
											if (beltinfo == 0 || (inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER && splitterDirection == 0))
												tileinfo[(int)(mousepos.y) / 32 - i][(int)(mousepos.x) / 32 - j].belt = BELTRIGHT;
											else if (beltinfo == 1 || (inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER && splitterDirection == 1))
												tileinfo[(int)(mousepos.y) / 32 - i][(int)(mousepos.x) / 32 - j].belt = BELTLEFT;
											else if (beltinfo == 2 || (inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER && splitterDirection == 2))
												tileinfo[(int)(mousepos.y) / 32 - i][(int)(mousepos.x) / 32 - j].belt = BELTUP;
											else if (beltinfo == 3 || (inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER && splitterDirection == 3))
												tileinfo[(int)(mousepos.y) / 32 - i][(int)(mousepos.x) / 32 - j].belt = BELTDOWN;
											else if (beltinfo == 4)
												tileinfo[(int)(g_ptMouse.y + g_pos.y - WINSIZE_Y / 2) / 32 - i][(int)(g_ptMouse.x + g_pos.x - WINSIZE_X / 2) / 32 - j].belt = BELTLEFTUP;
											else if (beltinfo == 5)
												tileinfo[(int)(g_ptMouse.y + g_pos.y - WINSIZE_Y / 2) / 32 - i][(int)(g_ptMouse.x + g_pos.x - WINSIZE_X / 2) / 32 - j].belt = BELTRIGHTDOWN;
											else if (beltinfo == 6)
												tileinfo[(int)(g_ptMouse.y + g_pos.y - WINSIZE_Y / 2) / 32 - i][(int)(g_ptMouse.x + g_pos.x - WINSIZE_X / 2) / 32 - j].belt = BELTRIGHTDOWN;
											else if (beltinfo == 7)
												tileinfo[(int)(g_ptMouse.y + g_pos.y - WINSIZE_Y / 2) / 32 - i][(int)(g_ptMouse.x + g_pos.x - WINSIZE_X / 2) / 32 - j].belt = BELTRIGHTDOWN;


										}
										
									}
								}

								SoundManager::GetSingleton()->Play("build");
								
							}

							else
							{
								map<TILE_POINT, GameNode*> tempmap;

							

								for (int i = 0; i < tilesize.y; i++)
								{
									for (int j = 0; j < tilesize.x; j++)
									{
									
										temppoint = { (int)(mousepos.x) / 32 - j
										, (int)(mousepos.y) / 32 - i };
										tempmap.insert(make_pair(temppoint, tempnode));
										tileinfo[(int)(mousepos.y) / 32 - i][(int)(mousepos.x) / 32 - j].obj = inveninfo[selectIndexY][selectIndexX].name;

										if (inveninfo[selectIndexY][selectIndexX].name == BASICTRANSPORTBELT || inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER)
										{
											if (beltinfo == 0 || (inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER && splitterDirection == 0))
												tileinfo[(int)(mousepos.y) / 32 - i][(int)(mousepos.x) / 32 - j].belt = BELTRIGHT;
											else if (beltinfo == 1 || (inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER && splitterDirection == 1))
												tileinfo[(int)(mousepos.y) / 32 - i][(int)(mousepos.x) / 32 - j].belt = BELTLEFT;
											else if (beltinfo == 2 || (inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER && splitterDirection == 2))
												tileinfo[(int)(mousepos.y) / 32 - i][(int)(mousepos.x) / 32 - j].belt = BELTUP;
											else if (beltinfo == 3 || (inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER && splitterDirection == 3))
												tileinfo[(int)(mousepos.y) / 32 - i][(int)(mousepos.x) / 32 - j].belt = BELTDOWN;
											else if (beltinfo == 4)
												tileinfo[(int)(g_ptMouse.y + g_pos.y - WINSIZE_Y / 2) / 32 - i][(int)(g_ptMouse.x + g_pos.x - WINSIZE_X / 2) / 32 - j].belt = BELTLEFTUP;
											else if (beltinfo == 5)
												tileinfo[(int)(g_ptMouse.y + g_pos.y - WINSIZE_Y / 2) / 32 - i][(int)(g_ptMouse.x + g_pos.x - WINSIZE_X / 2) / 32 - j].belt = BELTRIGHTDOWN;
											else if (beltinfo == 6)
												tileinfo[(int)(g_ptMouse.y + g_pos.y - WINSIZE_Y / 2) / 32 - i][(int)(g_ptMouse.x + g_pos.x - WINSIZE_X / 2) / 32 - j].belt = BELTRIGHTDOWN;
											else if (beltinfo == 7)
												tileinfo[(int)(g_ptMouse.y + g_pos.y - WINSIZE_Y / 2) / 32 - i][(int)(g_ptMouse.x + g_pos.x - WINSIZE_X / 2) / 32 - j].belt = BELTRIGHTDOWN;


											/*beltinfo = 0;
											frameX = 0;
											frameY = 0;*/

										}
										

										

									}

								}
								ObjectManager::GetSingleton()->InsertMap(inveninfo[selectIndexY][selectIndexX].name, tempmap);
								SoundManager::GetSingleton()->Play("build");

							}

							inveninfo[selectIndexY][selectIndexX].num--;
							if (inveninfo[selectIndexY][selectIndexX].num <= 0)
							{
								inveninfo[selectIndexY][selectIndexX].isSelected = false;
								inveninfo[selectIndexY][selectIndexX].isStorage = false;
								inveninfo[selectIndexY][selectIndexX].name = EMPTY;
								isSelect = false;

							}


						}
					}

				}
			}


			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (isOpen || i == 8)
					{
						if (PtInRect(&inveninfo[i][j].rc, g_ptMouse))
						{
							
							if (!inveninfo[i][j].isSelected && !isSelect && inveninfo[i][j].name != EMPTY)
							{
								inveninfo[i][j].isSelected = true;
								selectIndexX = j;
								selectIndexY = i;
								isSelect = true;

							}

							else if (isSelect)
							{
								if (KeyManager::GetSingleton()->IsStayKeyDown(VK_CONTROL))
								{
									if (!inveninfo[i][j].isStorage)
									{
										if (inveninfo[selectIndexY][selectIndexX].num != 1)
										{
											if (inveninfo[selectIndexY][selectIndexX].num % 2 == 0)
											{
												inveninfo[i][j].isStorage = true;
												inveninfo[i][j].name = inveninfo[selectIndexY][selectIndexX].name;
												inveninfo[i][j].num = inveninfo[selectIndexY][selectIndexX].num / 2;
												inveninfo[selectIndexY][selectIndexX].num = inveninfo[selectIndexY][selectIndexX].num / 2;
												inveninfo[selectIndexY][selectIndexX].isSelected = false;

											}
											else
											{
												inveninfo[i][j].isStorage = true;
												inveninfo[i][j].name = inveninfo[selectIndexY][selectIndexX].name;
												inveninfo[i][j].num = inveninfo[selectIndexY][selectIndexX].num / 2 + 1;
												inveninfo[selectIndexY][selectIndexX].num = inveninfo[selectIndexY][selectIndexX].num / 2;
												inveninfo[selectIndexY][selectIndexX].isSelected = false;

											}

											isSelect = false;
										}

										else
										{
											inveninfo[i][j].isStorage = true;
											inveninfo[i][j].name = inveninfo[selectIndexY][selectIndexX].name;
											inveninfo[i][j].num = inveninfo[selectIndexY][selectIndexX].num;
											inveninfo[selectIndexY][selectIndexX].name = EMPTY;
											inveninfo[selectIndexY][selectIndexX].num = 0;
											inveninfo[selectIndexY][selectIndexX].isSelected = false;
											inveninfo[selectIndexY][selectIndexX].isStorage = false;
											isSelect = false;
										}
									}
									else if (i == selectIndexY && j == selectIndexX)
									{
										isSelect = false;
										inveninfo[selectIndexY][selectIndexX].isSelected = false;
									}

									else if (inveninfo[i][j].isStorage && inveninfo[i][j].name == inveninfo[selectIndexY][selectIndexX].name)
									{
										int tempnum;
										if (inveninfo[selectIndexY][selectIndexX].num != 1)
										{
											
											if (inveninfo[selectIndexY][selectIndexX].num % 2 == 0)
											{
												inveninfo[i][j].num = inveninfo[i][j].num + inveninfo[selectIndexY][selectIndexX].num / 2;
												if (inveninfo[i][j].num > 999)
												{
													tempnum = inveninfo[i][j].num - 999;
													inveninfo[selectIndexY][selectIndexX].num = tempnum + inveninfo[selectIndexY][selectIndexX].num / 2;
													inveninfo[i][j].num = 999;
													inveninfo[selectIndexY][selectIndexX].isSelected = false;

												}

												else
												{
													inveninfo[selectIndexY][selectIndexX].num = inveninfo[selectIndexY][selectIndexX].num / 2;
													inveninfo[selectIndexY][selectIndexX].isSelected = false;
												}

											}

											else
											{
												inveninfo[i][j].num = inveninfo[i][j].num + inveninfo[selectIndexY][selectIndexX].num / 2 + 1;
												if (inveninfo[i][j].num > 999)
												{
													tempnum = inveninfo[i][j].num - 999;
													inveninfo[selectIndexY][selectIndexX].num = tempnum + inveninfo[selectIndexY][selectIndexX].num / 2;
													inveninfo[i][j].num = 999;
													inveninfo[selectIndexY][selectIndexX].isSelected = false;

												}

												else
												{
													inveninfo[selectIndexY][selectIndexX].num = inveninfo[selectIndexY][selectIndexX].num / 2;
													inveninfo[selectIndexY][selectIndexX].isSelected = false;
												}

											}

											isSelect = false;
										}

										else
										{											
											inveninfo[i][j].num = inveninfo[i][j].num + inveninfo[selectIndexY][selectIndexX].num;
											if (inveninfo[i][j].num > 999)
											{
												tempnum = inveninfo[i][j].num - 999;
												inveninfo[selectIndexY][selectIndexX].num = tempnum;
												inveninfo[i][j].num = 999;
												inveninfo[selectIndexY][selectIndexX].isSelected = false;

											}

											else
											{
												inveninfo[selectIndexY][selectIndexX].name = EMPTY;
												inveninfo[selectIndexY][selectIndexX].num = 0;
												inveninfo[selectIndexY][selectIndexX].isSelected = false;
												inveninfo[selectIndexY][selectIndexX].isStorage = false;
											}

											isSelect = false;
										}

									}

									
	
									else
									{
										INVENINFO tempinveninfo;

										tempinveninfo.name = inveninfo[i][j].name;
										tempinveninfo.num = inveninfo[i][j].num;

										inveninfo[i][j].name = inveninfo[selectIndexY][selectIndexX].name;
										inveninfo[i][j].num = inveninfo[selectIndexY][selectIndexX].num;

										inveninfo[selectIndexY][selectIndexX].name = tempinveninfo.name;
										inveninfo[selectIndexY][selectIndexX].num = tempinveninfo.num;
										inveninfo[selectIndexY][selectIndexX].isSelected = false;

										isSelect = false;
									}
								}

								else
								{
									if (!inveninfo[i][j].isStorage)
									{
										inveninfo[i][j].isStorage = true;
										inveninfo[i][j].name = inveninfo[selectIndexY][selectIndexX].name;
										inveninfo[i][j].num = inveninfo[selectIndexY][selectIndexX].num;
										inveninfo[selectIndexY][selectIndexX].name = EMPTY;
										inveninfo[selectIndexY][selectIndexX].num = 0;
										inveninfo[selectIndexY][selectIndexX].isSelected = false;
										inveninfo[selectIndexY][selectIndexX].isStorage = false;
										isSelect = false;

									}
									
									else if (i == selectIndexY && j == selectIndexX)
									{
										isSelect = false;
										inveninfo[selectIndexY][selectIndexX].isSelected = false;
									}

									else if (inveninfo[i][j].isStorage && inveninfo[i][j].name == inveninfo[selectIndexY][selectIndexX].name)
									{
										int tempnum;
										inveninfo[i][j].num = inveninfo[i][j].num + inveninfo[selectIndexY][selectIndexX].num;
										if (inveninfo[i][j].num > 999)
										{
											tempnum = inveninfo[i][j].num - 999;
											inveninfo[selectIndexY][selectIndexX].num = tempnum;
											inveninfo[i][j].num = 999;
											inveninfo[selectIndexY][selectIndexX].isSelected = false;

										}

										else
										{
											inveninfo[selectIndexY][selectIndexX].name = EMPTY;
											inveninfo[selectIndexY][selectIndexX].num = 0;
											inveninfo[selectIndexY][selectIndexX].isSelected = false;
											inveninfo[selectIndexY][selectIndexX].isStorage = false;
										}

										isSelect = false;

									}


									else
									{
										INVENINFO tempinveninfo;

										tempinveninfo.name = inveninfo[i][j].name;
										tempinveninfo.num = inveninfo[i][j].num;

										inveninfo[i][j].name = inveninfo[selectIndexY][selectIndexX].name;
										inveninfo[i][j].num = inveninfo[selectIndexY][selectIndexX].num;

										inveninfo[selectIndexY][selectIndexX].name = tempinveninfo.name;
										inveninfo[selectIndexY][selectIndexX].num = tempinveninfo.num;
										inveninfo[selectIndexY][selectIndexX].isSelected = false;

										isSelect = false;
									}
								}
							}
							
							
						}
					}

				}
			}


		}
	}


}

void Inventory::Render(HDC hdc)
{
	FPOINT correctionPos;
	
	CraftWaitingQueue::GetSingleton()->Render(hdc);

	correctionPos.x = (g_pos.x - (int)g_pos.x / 32 * 32);
	correctionPos.y = (g_pos.y - (int)g_pos.y / 32 * 32);

	char sZtext[256];


	SetTextColor(hdc, RGB(255, 255, 255));
	for (int i = 0; i < 10; i++)
	{
		Rectangle(hdc, inveninfo[8][i].rc.left, inveninfo[8][i].rc.top, inveninfo[8][i].rc.right, inveninfo[8][i].rc.bottom);
	}

	if (fastinventory)
		fastinventory->AlphaRender(hdc, quickRc.left + 500/2, quickRc.top + 63/2, 150);

	if (inventory && isOpen)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				Rectangle(hdc, inveninfo[i][j].rc.left, inveninfo[i][j].rc.top, inveninfo[i][j].rc.right, inveninfo[i][j].rc.bottom);
				
			}
		}

		inventory->AlphaRender(hdc, baseRc.left + 857/2, baseRc.top + 422/2, 150);

		CraftInvenRender(hdc);

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 10; j++)
			{				

				if (inveninfo[i][j].isStorage)
				{			
					if (!inveninfo[i][j].isSelected)
					{
						if (icon[inveninfo[i][j].name])
							icon[inveninfo[i][j].name]->FrameRender(hdc, inveninfo[i][j].rc.left + 39 / 2, inveninfo[i][j].rc.top + 39 / 2, 0, 0);
						wsprintf(sZtext, "%d", inveninfo[i][j].num);
						TextOut(hdc, inveninfo[i][j].rc.left + 39 / 2, inveninfo[i][j].rc.top + 39 / 2, sZtext, strlen(sZtext));
					}
				}
				
			}
		}
				

		
		
	}
	(HBRUSH)SelectObject(hdc, OldBrush);
	
	
	for (int i = 0; i < 10; i++)
	{
		if (inveninfo[8][i].isStorage)
		{
			if (!inveninfo[8][i].isSelected)
			{
				if (icon[inveninfo[8][i].name])
					icon[inveninfo[8][i].name]->FrameRender(hdc, inveninfo[8][i].rc.left + 39 / 2, inveninfo[8][i].rc.top + 39 / 2, 0, 0);
				wsprintf(sZtext, "%d", inveninfo[8][i].num);
				TextOut(hdc, inveninfo[8][i].rc.left + 39 / 2, inveninfo[8][i].rc.top + 39 / 2, sZtext, strlen(sZtext));
			}
		}
	}
	if (isSelect)

	{	//추우우우우우우가아아아아아아아
		if ((isOpen && !(PtInRect(&baseRc, g_ptMouse) || PtInRect(&quickRc, g_ptMouse))) && !ToolInvenIsOpen
			|| (!isOpen &&  !PtInRect(&quickRc, g_ptMouse)) && !ToolInvenIsOpen)
		{

			if (inveninfo[selectIndexY][selectIndexX].name == COAL)
				icon[COAL]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);

			else if (inveninfo[selectIndexY][selectIndexX].name == COPPER)
				icon[COPPER]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);

			else if (inveninfo[selectIndexY][selectIndexX].name == TREE)
				icon[TREE]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);

			else if (inveninfo[selectIndexY][selectIndexX].name == IRON)
				icon[IRON]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);

			else if (inveninfo[selectIndexY][selectIndexX].name == IRONPLATE)
				icon[IRONPLATE]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);

			else if (inveninfo[selectIndexY][selectIndexX].name == COPPERPLATE)
				icon[COPPERPLATE]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);

			else if (inveninfo[selectIndexY][selectIndexX].name == IRONGEARWHEEL)
				icon[COPPERPLATE]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);

			else if (inveninfo[selectIndexY][selectIndexX].name == COPPERCABLE)
				icon[COPPERCABLE]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);

			else if (inveninfo[selectIndexY][selectIndexX].name == ADVANCEDCIRCUIT)
				icon[ADVANCEDCIRCUIT]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);

			else if (inveninfo[selectIndexY][selectIndexX].name == ELECTRONICCIRCUIT)
				icon[ELECTRONICCIRCUIT]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);

			else if (inveninfo[selectIndexY][selectIndexX].name == IRONSTICK)
				icon[IRONSTICK]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);

			else if (inveninfo[selectIndexY][selectIndexX].name == WOOD)
				icon[WOOD]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);
						

			wsprintf(sZtext, "%d", inveninfo[selectIndexY][selectIndexX].num);
			TextOut(hdc, g_ptMouse.x, g_ptMouse.y, sZtext, strlen(sZtext));
		}

		//추우우우우우우가아아아아아아아
		else
		{
			if (!ToolInvenIsOpen)
			{
				if (icon[inveninfo[selectIndexY][selectIndexX].name])
					icon[inveninfo[selectIndexY][selectIndexX].name]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);
				wsprintf(sZtext, "%d", inveninfo[selectIndexY][selectIndexX].num);
				TextOut(hdc, g_ptMouse.x, g_ptMouse.y, sZtext, strlen(sZtext));
			}
		}
		
		
				
	}

	/*sprintf_s(sZtext, "x: %d y: %d", g_ptMouse.x, g_ptMouse.y);
	TextOut(hdc, 200, 200, sZtext, strlen(sZtext));*/

	
	
	ToolInvenRender(hdc);

	SelectObject(hdc, OldBrush);
	
}

void Inventory::ToolInvenInit()
{
	invenImage = ImageManager::GetSingleton()->FindImage("objectinven");
	ToolInvenIsOpen = false;
	ToolInvenIsSelect = false;
	ToolInvenIsBackUp = false;

	for (int i = 0; i < 7; i++)
	{
		selectObjInven[i] = false;
	}

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//inveninfo[i][j].rc = { (int)(pos.x - 419 + 41*j),(int)(pos.y - 167 + 41*i), (int)(pos.x - 419 + 41*j) + 38,(int)(pos.y - 167 + 41*i) + 38 };
			toolInvenInfo[i][j].rc = { (int)(pos.x - 210 + 41 * j),(int)(pos.y - 40 + 41 * i), (int)(pos.x - 210 + 41 * j) + 39,(int)(pos.y - 40 + 41 * i) + 39 };
			toolInvenInfo[i][j].num = 0;
			toolInvenInfo[i][j].isStorage = false;
			toolInvenInfo[i][j].name = EMPTY;
			toolInvenInfo[i][j].isSelected = false;
			if (i == 8)
			{
				toolInvenInfo[i][j].rc = { (int)(pos.x - 210 + j * 38),WINSIZE_Y - 48, (int)(pos.x - 210 + j * 38) + 38,WINSIZE_Y - 48 + 38 };
				if (j >= 5)
					toolInvenInfo[i][j].rc = { (int)(pos.x - 170 + j * 38), WINSIZE_Y - 48, (int)(pos.x - 170 + j * 38) + 38, WINSIZE_Y - 48 + 38 };
			}

			if (i == 9)
			{
				toolInvenInfo[9][0].rc = { (int)(pos.x - 230),(int)(pos.y - 270), (int)(pos.x - 230) + 128,(int)(pos.y - 270) + 128 };
				toolInvenInfo[9][1].rc = { (int)(pos.x - 40),(int)(pos.y - 260), (int)(pos.x - 40) + 39,(int)(pos.y - 260) + 39 };
				toolInvenInfo[9][2].rc = { (int)(pos.x + 128),(int)(pos.y - 260), (int)(pos.x + 128) + 39,(int)(pos.y - 260) + 39 };
				toolInvenInfo[9][3].rc = { (int)(pos.x - 40),(int)(pos.y - 190), (int)(pos.x - 40) + 39,(int)(pos.y - 190) + 39 };
				toolInvenInfo[9][4].rc = { (int)(pos.x + 128),(int)(pos.y - 190), (int)(pos.x + 128) + 39,(int)(pos.y - 190) + 39 };

			}

			if (i == 10)
			{

				toolInvenInfo[10][j].rc = { (int)(pos.x - 80 + 41 * j + 9),(int)(pos.y - 270), (int)(pos.x - 80 + 41 * j + 9) + 39,(int)(pos.y - 270) + 39 };

				if (j > 4)
				{
					toolInvenInfo[10][j].rc = { (int)(pos.x - 80 + 41 * (j - 5) + 9),(int)(pos.y - 230), (int)(pos.x - 80 + 41 * (j - 5) + 9) + 39,(int)(pos.y - 230) + 39 };
				}

			}

			if (i == 11)
			{
				toolInvenInfo[11][j].rc = { (int)(pos.x + 245 + 41 * j + 9),(int)(pos.y - 230), (int)(pos.x + 245 + 41 * j + 9) + 39,(int)(pos.y - 230) + 39 };
				if (j > 3 && j<6)
					toolInvenInfo[11][j].rc = { (int)(pos.x - 80 + 41 * (j - 4) + 9),(int)(pos.y - 260), (int)(pos.x - 80 + 41 * (j - 4) + 9) + 39,(int)(pos.y - 260) + 39 };
				if (j == 6)
					toolInvenInfo[11][j].rc = { (int)(pos.x + 128),(int)(pos.y - 190), (int)(pos.x + 128) + 39,(int)(pos.y - 190) + 39 };

				if(j>6)
					toolInvenInfo[11][j].rc = { (int)(pos.x - 180 + 41 * (j - 4) + 9),(int)(pos.y - 260), (int)(pos.x - 180 + 41 * (j - 4) + 9) + 39,(int)(pos.y - 260) + 39 };


			}


		}
	}

}

void Inventory::ToolInvenRelease()
{
}

void Inventory::ToolInvenUpdate()
{	
	if (!ToolInvenIsOpen && !isOpen && !isSelect)
	{
		
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			for (int i = ((int)g_pos.y) / 32 - 14; i < ((int)g_pos.y) / 32 + 14; i++)
			{
				for (int j = ((int)g_pos.x) / 32 - 25; j < ((int)g_pos.x) / 32 + 25; j++)
				{
					if (PtInRect(&tileinfo[i][j].rcTile, mousepos))
					{
						if (tileinfo[i][j].obj != EMPTY && tileinfo[i][j].obj != TREE && tileinfo[i][j].obj != BASICTRANSPORTBELT && tileinfo[i][j].obj != HUMAN
							&& tileinfo[i][j].obj != FORBIDDEN)
						{
							if ((*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[i][j].obj)).find({ j,i })->second->GetSelectedClose())
							{
								if (tileinfo[i][j].obj == EMPTY || tileinfo[i][j].obj == TREE || tileinfo[i][j].obj == BASICTRANSPORTBELT || tileinfo[i][j].obj == HUMAN)
								{
									for (int k = 0; k < 5; k++)
										selectObjInven[k] = false;
								}
								else
								{
									ToolInvenIsOpen = true;
									SoundManager::GetSingleton()->Play("invenopen", 0.3f);
									blockClick = 0;
									Tutorial::GetSingleton()->SucceedQuest_6();

									selectObjInven[0] = true;

									switch (tileinfo[i][j].obj)
									{
									case(STONEFURNACE):
										selectObjInven[1] = true; selectObjInven[2] = false; selectObjInven[3] = true; selectObjInven[4] = true;
										selectObjInven[5] = false; selectObjInven[6] = false;
										break;
									case(BURNERINSERTER):	case(BURNERMININGDRILL): case(STEAMENGINE):
										selectObjInven[1] = true; selectObjInven[2] = false; selectObjInven[3] = false; selectObjInven[4] = false;
										selectObjInven[5] = false; selectObjInven[6] = false;
										break;
									case(ELECTRICFURNACE):
										selectObjInven[1] = false; selectObjInven[2] = false; selectObjInven[3] = true; selectObjInven[4] = true;
										selectObjInven[5] = false; selectObjInven[6] = false;
										break;
									case(BASICINSERTER): case(BASICMININGDRILL):
										selectObjInven[1] = false; selectObjInven[2] = false; selectObjInven[3] = false; selectObjInven[4] = false;
										selectObjInven[5] = false; selectObjInven[6] = false;
										break;

									case(WOODENCHEST):
										selectObjInven[1] = false; selectObjInven[2] = false; selectObjInven[3] = false; selectObjInven[4] = false;
										selectObjInven[5] = true; selectObjInven[6] = false;
										break;

									case(ASSEMBLINGMACHINE):
										selectObjInven[1] = false; selectObjInven[2] = false; selectObjInven[3] = false; selectObjInven[4] = false;
										selectObjInven[5] = false; selectObjInven[6] = false;
										break;

									case(ROCKET):
										selectObjInven[1] = false; selectObjInven[2] = false; selectObjInven[3] = false; selectObjInven[4] = false;
										selectObjInven[5] = false; selectObjInven[6] = false;
										break;

									case(STEELCHEST):
										selectObjInven[1] = false; selectObjInven[2] = false; selectObjInven[3] = false; selectObjInven[4] = false;
										selectObjInven[5] = false; selectObjInven[6] = true;
										break;
									}
								}

								selectObj.x = j;
								selectObj.y = i;

								goto skip;
							}
						}
					}
				}
				
			}
		}
	}
skip:
	if (ToolInvenIsOpen)
	{	
		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			if (!ToolInvenIsBackUp)
			{
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						toolInvenInfo[i][j].isStorage = inveninfo[i][j].isStorage;
						toolInvenInfo[i][j].name = inveninfo[i][j].name;
						toolInvenInfo[i][j].num = inveninfo[i][j].num;
					}
				}
				toolInvenInfo[9][1].name = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetFuel()->name;
				toolInvenInfo[9][1].num = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetFuel()->num;
				toolInvenInfo[9][1].isStorage = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetFuel()->isStorage;

				toolInvenInfo[9][3].name = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetMeterial()->name;
				toolInvenInfo[9][3].num = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetMeterial()->num;
				toolInvenInfo[9][3].isStorage = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetMeterial()->isStorage;

				toolInvenInfo[9][4].name = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetProduct()->name;
				toolInvenInfo[9][4].num = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetProduct()->num;
				toolInvenInfo[9][4].isStorage = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetProduct()->isStorage;

				ToolInvenIsBackUp = true;
			}

			
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (tileinfo[selectObj.y][selectObj.x].obj == ASSEMBLINGMACHINE)
					{
						if (i == 11 && j >= 0 && j <= 3)
							if (PtInRect(&toolInvenInfo[i][j].rc, g_ptMouse))
							{
								if (j == 0)
									(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
									find({ selectObj.x ,selectObj.y })->second->SetLayer(IRONGEARWHEEL);

								else if (j == 1)
									(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
									find({ selectObj.x ,selectObj.y })->second->SetLayer(COPPERCABLE);

								else if (j == 2)
									(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
									find({ selectObj.x ,selectObj.y })->second->SetLayer(ELECTRONICCIRCUIT);

								else if (j == 3)
									(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
									find({ selectObj.x ,selectObj.y })->second->SetLayer(ADVANCEDCIRCUIT);
							}
					}
					checkSelect = false;
					if (tileinfo[selectObj.y][selectObj.x].obj == STONEFURNACE)
					{
						if (!(i == 9 && (j == 0 || j == 2)) && !(i >= 10))
						{
							checkSelect = true;
						}
							
						else
						{
							checkSelect = false;
						}
							

					}
					else if (tileinfo[selectObj.y][selectObj.x].obj == BURNERMININGDRILL)
					{
						if (!(i == 9 && (j == 0 || j == 2 || j == 3 || j == 4)) && !(i >= 10))
							checkSelect = true;
						else
							checkSelect = false;

					}

					else if (tileinfo[selectObj.y][selectObj.x].obj == BURNERINSERTER)
					{
						if (!(i == 9 && (j == 0 || j == 2 || j == 3 || j == 4)) && !(i >= 10))
							checkSelect = true;
						else
							checkSelect = false;

					}

					else if (tileinfo[selectObj.y][selectObj.x].obj == STEAMENGINE)
					{
						if (!(i == 9 && (j == 0 || j == 2 || j == 3 || j == 4)) && !(i >= 10))
							checkSelect = true;
						else
							checkSelect = false;

					}

					else if (tileinfo[selectObj.y][selectObj.x].obj == BASICINSERTER)
					{
						if (!(i == 9) && !(i >= 10))
							checkSelect = true;
						else
							checkSelect = false;

					}

					else if (tileinfo[selectObj.y][selectObj.x].obj == ELECTRICFURNACE)
					{
						if (!(i == 9 && (j == 0 || j == 1 || j == 2)) && !(i >= 10))
							checkSelect = true;
						else
							checkSelect = false;

					}

					else if (tileinfo[selectObj.y][selectObj.x].obj == BASICMININGDRILL)
					{
						if (!(i == 9) && !(i >= 10) && !(i == 11))
							checkSelect = true;
						else
							checkSelect = false;
					}

					else if (tileinfo[selectObj.y][selectObj.x].obj == WOODENCHEST)
					{
						if (!(i == 9) && !(i == 10 && j >= 5) && !(i == 11))
							checkSelect = true;
						else
							checkSelect = false;
					}

					else if (tileinfo[selectObj.y][selectObj.x].obj == STEELCHEST)
					{
						if (!(i == 9)  && !(i == 11))
							checkSelect = true;
						else
							checkSelect = false;
					}

					else if (tileinfo[selectObj.y][selectObj.x].obj == ASSEMBLINGMACHINE)
					{
						if ((*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
							find({ selectObj.x ,selectObj.y })->second->GetLayer()==IRONGEARWHEEL)
						{
							if ((i != 9) && !(i == 10) && !(i == 11 && j <= 3) && !(i == 11 && j >= 7) && !(i == 11 && j == 5))
								checkSelect = true;
							else
								checkSelect = false;
						}

						else if ((*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).find({ selectObj.x,selectObj.y })->second->GetLayer() == COPPERCABLE)
						{
							if ((i != 9) && !(i == 10) && !(i == 11 && j <= 3) && !(i == 11 && j >= 7) && !(i == 11 && j == 5))
								checkSelect = true;
							else
								checkSelect = false;
						}

						else if ((*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).find({ selectObj.x,selectObj.y })->second->GetLayer() == ELECTRONICCIRCUIT)
						{
							if ((i != 9) && !(i == 10) && !(i == 11 && j <= 3) && !(i == 11 && j >= 7))
								checkSelect = true;
							else
								checkSelect = false;
						}
						else if ((*ObjectManager::GetSingleton()->FindObjectMap(ASSEMBLINGMACHINE)).find({ selectObj.x,selectObj.y })->second->GetLayer() == ADVANCEDCIRCUIT)
						{
							if ((i != 9) && !(i == 10) && !(i == 11 && j <= 3) && !(i == 11 && j >= 7))
								checkSelect = true;
							else
								checkSelect = false;
						}
						
					}

					else if (tileinfo[selectObj.y][selectObj.x].obj == ROCKET)
					{
						if (!(i == 9) && !(i == 10) && !(i == 11 && j < 7))
							checkSelect = true;
						else
							checkSelect = false;
					}

					if (checkSelect && blockClick==6)
					{

						if (PtInRect(&toolInvenInfo[i][j].rc, g_ptMouse))
						{
							if (!toolInvenInfo[i][j].isSelected && !isSelect && toolInvenInfo[i][j].name != EMPTY)
							{
								toolInvenInfo[i][j].isSelected = true;
								selectIndexX = j;
								selectIndexY = i;
								isSelect = true;
							}

							else if (isSelect)
							{
								if (!toolInvenInfo[i][j].isStorage)
								{
									if (KeyManager::GetSingleton()->IsStayKeyDown(VK_CONTROL))
									{
										if (toolInvenInfo[selectIndexY][selectIndexX].num % 2 == 0)
										{
											if (toolInvenInfo[selectIndexY][selectIndexX].num == 1)
											{
												toolInvenInfo[i][j].isStorage = true;
												toolInvenInfo[i][j].name = toolInvenInfo[selectIndexY][selectIndexX].name;
												toolInvenInfo[i][j].num = toolInvenInfo[selectIndexY][selectIndexX].num;
												toolInvenInfo[selectIndexY][selectIndexX].name = EMPTY;
												toolInvenInfo[selectIndexY][selectIndexX].num = 0;
												toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;
												toolInvenInfo[selectIndexY][selectIndexX].isStorage = false;
												
											}

											else
											{
												toolInvenInfo[i][j].isStorage = true;
												toolInvenInfo[i][j].name = toolInvenInfo[selectIndexY][selectIndexX].name;
												toolInvenInfo[i][j].num = toolInvenInfo[selectIndexY][selectIndexX].num / 2;
												toolInvenInfo[selectIndexY][selectIndexX].num = toolInvenInfo[selectIndexY][selectIndexX].num / 2;
												toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;
											}

										}
										else
										{
											if (toolInvenInfo[selectIndexY][selectIndexX].num == 1)
											{
												toolInvenInfo[i][j].isStorage = true;
												toolInvenInfo[i][j].name = toolInvenInfo[selectIndexY][selectIndexX].name;
												toolInvenInfo[i][j].num = toolInvenInfo[selectIndexY][selectIndexX].num;
												toolInvenInfo[selectIndexY][selectIndexX].name = EMPTY;
												toolInvenInfo[selectIndexY][selectIndexX].num = 0;
												toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;
												toolInvenInfo[selectIndexY][selectIndexX].isStorage = false;
												isSelect = false;
												
											}

											else
											{
												toolInvenInfo[i][j].isStorage = true;
												toolInvenInfo[i][j].name = toolInvenInfo[selectIndexY][selectIndexX].name;
												toolInvenInfo[i][j].num = toolInvenInfo[selectIndexY][selectIndexX].num / 2 + 1;
												toolInvenInfo[selectIndexY][selectIndexX].num = toolInvenInfo[selectIndexY][selectIndexX].num / 2;
												toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;
											}

										}

										isSelect = false;
									}

									else
									{
										toolInvenInfo[i][j].isStorage = true;
										toolInvenInfo[i][j].name = toolInvenInfo[selectIndexY][selectIndexX].name;
										toolInvenInfo[i][j].num = toolInvenInfo[selectIndexY][selectIndexX].num;
										toolInvenInfo[selectIndexY][selectIndexX].name = EMPTY;
										toolInvenInfo[selectIndexY][selectIndexX].num = 0;
										toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;
										toolInvenInfo[selectIndexY][selectIndexX].isStorage = false;
										isSelect = false;
									}
									

									if ((j == 1 && i == 9) || (selectIndexX == 1 && selectIndexY == 9))
									{
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetFuel()->name = toolInvenInfo[9][1].name;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetFuel()->num = toolInvenInfo[9][1].num;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetFuel()->isStorage = toolInvenInfo[9][1].isStorage;
									}


									else if ((j == 3 && i == 9) || (selectIndexX == 3 && selectIndexY == 9))
									{
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetMeterial()->name = toolInvenInfo[9][3].name;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetMeterial()->num = toolInvenInfo[9][3].num;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetMeterial()->isStorage = toolInvenInfo[9][3].isStorage;

									}

									else if ((j == 4 && i == 9) || (selectIndexX == 4 && selectIndexY == 9))
									{
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetProduct()->name = toolInvenInfo[9][4].name;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetProduct()->num = toolInvenInfo[9][4].num;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetProduct()->isStorage = toolInvenInfo[9][4].isStorage;

									}

									if (tileinfo[selectObj.y][selectObj.x].obj == WOODENCHEST)
									{
										for (int i = 0; i < 5; i++)
										{
											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].name = toolInvenInfo[10][i].name;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].num = toolInvenInfo[10][i].num;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].isStorage = toolInvenInfo[10][i].isStorage;
										}
									}

									else if (tileinfo[selectObj.y][selectObj.x].obj == STEELCHEST)
									{
										for (int i = 0; i < 10; i++)
										{
											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].name = toolInvenInfo[10][i].name;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].num = toolInvenInfo[10][i].num;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].isStorage = toolInvenInfo[10][i].isStorage;
										}
									}

									else if (tileinfo[selectObj.y][selectObj.x].obj == ASSEMBLINGMACHINE)
									{
										for (int i = 4; i < 7; i++)
										{
											if (i != 6)
											{
												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].name = toolInvenInfo[11][i].name;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].num = toolInvenInfo[11][i].num;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].isStorage = toolInvenInfo[11][i].isStorage;
											}

											else
											{
												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetProduct()->name = toolInvenInfo[11][i].name;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetProduct()->num = toolInvenInfo[11][i].num;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetProduct()->isStorage = toolInvenInfo[11][i].isStorage;
											}
										}
									}

									else if (tileinfo[selectObj.y][selectObj.x].obj == ROCKET)
									{
										for (int i = 7; i < 10; i++)
										{

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].name = toolInvenInfo[11][i].name;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].num = toolInvenInfo[11][i].num;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].isStorage = toolInvenInfo[11][i].isStorage;

										}
									}

								}
								else if (i == selectIndexY && j == selectIndexX)
								{
									isSelect = false;
									toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;
								}

								else if (toolInvenInfo[i][j].isStorage && toolInvenInfo[i][j].name == toolInvenInfo[selectIndexY][selectIndexX].name)
								{
									int tempnum;
									if (KeyManager::GetSingleton()->IsStayKeyDown(VK_CONTROL))
									{
										if (toolInvenInfo[selectIndexY][selectIndexX].num != 1)
										{
											if (toolInvenInfo[selectIndexY][selectIndexX].num % 2 == 0)
											{
												toolInvenInfo[i][j].num = toolInvenInfo[i][j].num + toolInvenInfo[selectIndexY][selectIndexX].num / 2;
												if (toolInvenInfo[i][j].num > 999)
												{
													tempnum = toolInvenInfo[i][j].num - 999;
													toolInvenInfo[selectIndexY][selectIndexX].num = tempnum + toolInvenInfo[selectIndexY][selectIndexX].num / 2;
													toolInvenInfo[i][j].num = 999;
													toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;

												}

												else
												{
													toolInvenInfo[selectIndexY][selectIndexX].num = toolInvenInfo[selectIndexY][selectIndexX].num / 2;
													toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;
												}


											}

											else
											{
												toolInvenInfo[i][j].num = toolInvenInfo[i][j].num + toolInvenInfo[selectIndexY][selectIndexX].num / 2 + 1;
												if (toolInvenInfo[i][j].num > 999)
												{
													tempnum = toolInvenInfo[i][j].num - 999;
													toolInvenInfo[selectIndexY][selectIndexX].num = tempnum + toolInvenInfo[selectIndexY][selectIndexX].num / 2;
													toolInvenInfo[i][j].num = 999;
													toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;

												}

												else
												{
													toolInvenInfo[selectIndexY][selectIndexX].num = toolInvenInfo[selectIndexY][selectIndexX].num / 2;
													toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;
												}

											}
											isSelect = false;
										}
										else
										{
											toolInvenInfo[i][j].num = toolInvenInfo[i][j].num + toolInvenInfo[selectIndexY][selectIndexX].num;
											if (toolInvenInfo[i][j].num > 999)
											{
												tempnum = toolInvenInfo[i][j].num - 999;
												toolInvenInfo[selectIndexY][selectIndexX].num = tempnum;
												toolInvenInfo[i][j].num = 999;
												toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;

											}

											else
											{
												toolInvenInfo[selectIndexY][selectIndexX].name = EMPTY;
												toolInvenInfo[selectIndexY][selectIndexX].num = 0;
												toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;
												toolInvenInfo[selectIndexY][selectIndexX].isStorage = false;
											}

											isSelect = false;
										}
									}


									else
									{

										toolInvenInfo[i][j].num = toolInvenInfo[i][j].num + toolInvenInfo[selectIndexY][selectIndexX].num;
										if (toolInvenInfo[i][j].num > 999)
										{
											tempnum = toolInvenInfo[i][j].num - 999;
											toolInvenInfo[selectIndexY][selectIndexX].num = tempnum;
											toolInvenInfo[i][j].num = 999;
											toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;

										}

										else
										{
											toolInvenInfo[selectIndexY][selectIndexX].name = EMPTY;
											toolInvenInfo[selectIndexY][selectIndexX].num = 0;
											toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;
											toolInvenInfo[selectIndexY][selectIndexX].isStorage = false;
										}

										isSelect = false;
									}

									if ((j == 1 && i == 9) || (selectIndexX == 1 && selectIndexY == 9))
									{
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetFuel()->name = toolInvenInfo[9][1].name;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetFuel()->num = toolInvenInfo[9][1].num;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetFuel()->isStorage = toolInvenInfo[9][1].isStorage;
									}

									else if ((j == 3 && i == 9) || (selectIndexX == 3 && selectIndexY == 9))
									{
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetMeterial()->name = toolInvenInfo[9][3].name;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetMeterial()->num = toolInvenInfo[9][3].num;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetMeterial()->isStorage = toolInvenInfo[9][3].isStorage;

									}

									else if ((j == 4 && i == 9) || (selectIndexX == 4 && selectIndexY == 9))
									{
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetProduct()->name = toolInvenInfo[9][4].name;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetProduct()->num = toolInvenInfo[9][4].num;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetProduct()->isStorage = toolInvenInfo[9][4].isStorage;

									}

									if (tileinfo[selectObj.y][selectObj.x].obj == WOODENCHEST)
									{
										for (int i = 0; i < 5; i++)
										{
											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].name = toolInvenInfo[10][i].name;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].num = toolInvenInfo[10][i].num;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].isStorage = toolInvenInfo[10][i].isStorage;
										}
									}

									else if (tileinfo[selectObj.y][selectObj.x].obj == STEELCHEST)
									{
										for (int i = 0; i < 10; i++)
										{
											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].name = toolInvenInfo[10][i].name;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].num = toolInvenInfo[10][i].num;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].isStorage = toolInvenInfo[10][i].isStorage;
										}
									}
									else if (tileinfo[selectObj.y][selectObj.x].obj == ASSEMBLINGMACHINE)
									{
										for (int i = 4; i < 7; i++)
										{
											if (i != 6)
											{
												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].name = toolInvenInfo[11][i].name;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].num = toolInvenInfo[11][i].num;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].isStorage = toolInvenInfo[11][i].isStorage;
											}

											else
											{
												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetProduct()->name = toolInvenInfo[11][i].name;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetProduct()->num = toolInvenInfo[11][i].num;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetProduct()->isStorage = toolInvenInfo[11][i].isStorage;
											}
										}
									}

									else if (tileinfo[selectObj.y][selectObj.x].obj == ROCKET)
									{
										for (int i = 7; i < 10; i++)
										{
											
											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].name = toolInvenInfo[11][i].name;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].num = toolInvenInfo[11][i].num;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].isStorage = toolInvenInfo[11][i].isStorage;
											
										}
									}


								}

								
								
								else
								{
									INVENINFO tempinveninfo;

									tempinveninfo.name = toolInvenInfo[i][j].name;
									tempinveninfo.num = toolInvenInfo[i][j].num;

									toolInvenInfo[i][j].name = toolInvenInfo[selectIndexY][selectIndexX].name;
									toolInvenInfo[i][j].num = toolInvenInfo[selectIndexY][selectIndexX].num;

									toolInvenInfo[selectIndexY][selectIndexX].name = tempinveninfo.name;
									toolInvenInfo[selectIndexY][selectIndexX].num = tempinveninfo.num;
									toolInvenInfo[selectIndexY][selectIndexX].isSelected = false;

									isSelect = false;

									if ((j == 1 && i == 9) || (selectIndexX == 1 && selectIndexY == 9))
									{
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetFuel()->name = toolInvenInfo[9][1].name;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetFuel()->num = toolInvenInfo[9][1].num;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetFuel()->isStorage = toolInvenInfo[9][1].isStorage;
									}

									else if ((j == 3 && i == 9) || (selectIndexX == 3 && selectIndexY == 9))
									{
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetMeterial()->name = toolInvenInfo[9][3].name;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetMeterial()->num = toolInvenInfo[9][3].num;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetMeterial()->isStorage = toolInvenInfo[9][3].isStorage;

									}

									else if ((j == 4 && i == 9) || (selectIndexX == 4 && selectIndexY == 9))
									{
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetProduct()->name = toolInvenInfo[9][4].name;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetProduct()->num = toolInvenInfo[9][4].num;
										(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
											find({ selectObj.x ,selectObj.y })->second->GetProduct()->isStorage = toolInvenInfo[9][4].isStorage;

									}

									if (tileinfo[selectObj.y][selectObj.x].obj == WOODENCHEST)
									{
										for (int i = 0; i < 5; i++)
										{
											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].name = toolInvenInfo[10][i].name;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].num = toolInvenInfo[10][i].num;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].isStorage = toolInvenInfo[10][i].isStorage;
										}
									}

									else if (tileinfo[selectObj.y][selectObj.x].obj == STEELCHEST)
									{
										for (int i = 0; i < 10; i++)
										{
											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].name = toolInvenInfo[10][i].name;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].num = toolInvenInfo[10][i].num;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].isStorage = toolInvenInfo[10][i].isStorage;
										}
									}
									else if (tileinfo[selectObj.y][selectObj.x].obj == ASSEMBLINGMACHINE)
									{
										for (int i = 4; i < 7; i++)
										{
											if (i != 6)
											{
												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].name = toolInvenInfo[11][i].name;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].num = toolInvenInfo[11][i].num;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].isStorage = toolInvenInfo[11][i].isStorage;
											}

											else
											{
												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetProduct()->name = toolInvenInfo[11][i].name;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetProduct()->num = toolInvenInfo[11][i].num;

												(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
													find({ selectObj.x ,selectObj.y })->second->GetProduct()->isStorage = toolInvenInfo[11][i].isStorage;
											}
										}
									}

									else if (tileinfo[selectObj.y][selectObj.x].obj == ROCKET)
									{
										for (int i = 7; i < 10; i++)
										{
											
											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].name = toolInvenInfo[11][i].name;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].num = toolInvenInfo[11][i].num;

											(*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
												find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].isStorage = toolInvenInfo[11][i].isStorage;
											
										}
									}

									
								}
							}
						}

					}
				}

			}
		}
	}

	blockClick++;
	if (blockClick >= 6)
		blockClick = 6;

	if (ToolInvenIsOpen)
	{
		if (tileinfo[selectObj.y][selectObj.x].obj != WOODENCHEST && tileinfo[selectObj.y][selectObj.x].obj != STEELCHEST
			&& tileinfo[selectObj.y][selectObj.x].obj != ASSEMBLINGMACHINE && tileinfo[selectObj.y][selectObj.x].obj != ROCKET)
		{
			toolInvenInfo[9][1].name = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
				find({ selectObj.x ,selectObj.y })->second->GetFuel()->name;
			toolInvenInfo[9][1].num = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
				find({ selectObj.x ,selectObj.y })->second->GetFuel()->num;
			toolInvenInfo[9][1].isStorage = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
				find({ selectObj.x ,selectObj.y })->second->GetFuel()->isStorage;

			toolInvenInfo[9][3].name = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
				find({ selectObj.x ,selectObj.y })->second->GetMeterial()->name;
			toolInvenInfo[9][3].num = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
				find({ selectObj.x ,selectObj.y })->second->GetMeterial()->num;
			toolInvenInfo[9][3].isStorage = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
				find({ selectObj.x ,selectObj.y })->second->GetMeterial()->isStorage;

			toolInvenInfo[9][4].name = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
				find({ selectObj.x ,selectObj.y })->second->GetProduct()->name;
			toolInvenInfo[9][4].num = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
				find({ selectObj.x ,selectObj.y })->second->GetProduct()->num;
			toolInvenInfo[9][4].isStorage = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
				find({ selectObj.x ,selectObj.y })->second->GetProduct()->isStorage;
		}

		if (tileinfo[selectObj.y][selectObj.x].obj == WOODENCHEST)
		{
			for (int i = 0; i < 5; i++)
			{
				toolInvenInfo[10][i].name = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].name;

				toolInvenInfo[10][i].num = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].num;

				toolInvenInfo[10][i].isStorage = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].isStorage;
			}
		}

		else if (tileinfo[selectObj.y][selectObj.x].obj == STEELCHEST)
		{
			for (int i = 0; i < 10; i++)
			{
				toolInvenInfo[10][i].name = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].name;

				toolInvenInfo[10][i].num = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].num;

				toolInvenInfo[10][i].isStorage = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetBoxInfo()[i].isStorage;
			}
		}

		if (tileinfo[selectObj.y][selectObj.x].obj == ASSEMBLINGMACHINE)
		{
			for (int i = 4; i < 7; i++)
			{
				if (i != 6)
				{
					toolInvenInfo[11][i].name = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
						find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].name;

					toolInvenInfo[11][i].num = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
						find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].num;

					toolInvenInfo[11][i].isStorage = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
						find({ selectObj.x ,selectObj.y })->second->GetAssemMeterial()[abs(4 - i)].isStorage;
				}

				else
				{
					toolInvenInfo[11][i].name = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
						find({ selectObj.x ,selectObj.y })->second->GetProduct()->name;

					toolInvenInfo[11][i].num = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
						find({ selectObj.x ,selectObj.y })->second->GetProduct()->num;

					toolInvenInfo[11][i].isStorage = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
						find({ selectObj.x ,selectObj.y })->second->GetProduct()->isStorage;
				}
			}
		}

		if (tileinfo[selectObj.y][selectObj.x].obj == ROCKET)
		{
			for (int i = 7; i < 10; i++)
			{
				
				
				toolInvenInfo[11][i].name = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].name;

				toolInvenInfo[11][i].num = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].num;

				toolInvenInfo[11][i].isStorage = (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetRocketMaterial()[i - 7].isStorage;
				
			}
		}
	}

}

void Inventory::ToolInvenRender(HDC hdc)
{
	
	SelectObject(hdc, GrayBrush);

	char sZtext[100];
	if (toolInvenInfo)
	{
		if (ToolInvenIsOpen)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					Rectangle(hdc, toolInvenInfo[i][j].rc.left, toolInvenInfo[i][j].rc.top, toolInvenInfo[i][j].rc.right, toolInvenInfo[i][j].rc.bottom);

				}
			}
							
			if (invenImage)
				invenImage->AlphaRender(hdc, baseRc.left + 857 / 2, baseRc.top + 422 / 2, 150);

			for (int k = 0; k < 5; k++)
			{
				if (selectObjInven[k])
				{
					Rectangle(hdc, toolInvenInfo[9][k].rc.left, toolInvenInfo[9][k].rc.top, toolInvenInfo[9][k].rc.right, toolInvenInfo[9][k].rc.bottom);
				}
			}


			for (int i = 8; i < 9; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					Rectangle(hdc, toolInvenInfo[i][j].rc.left, toolInvenInfo[i][j].rc.top, toolInvenInfo[i][j].rc.right, toolInvenInfo[i][j].rc.bottom); // ?
				}
			}

			

			switch (tileinfo[selectObj.y][selectObj.x].obj)
			{
			case(STONEFURNACE):
				stoneFurnace->FrameRender(hdc, toolInvenInfo[9][0].rc.left + 128 / 2, toolInvenInfo[9][0].rc.top + 128 / 2, 0, 0);
				break;
			case(BURNERINSERTER):
				burnerInserter->FrameRender(hdc, toolInvenInfo[9][0].rc.left + 128 / 2, toolInvenInfo[9][0].rc.top + 128 / 2, 0, 0);
				break;
			case(BURNERMININGDRILL):
				burnerMiningDrillEast->FrameRender(hdc, toolInvenInfo[9][0].rc.left + 128 / 2, toolInvenInfo[9][0].rc.top + 128 / 2, 0, 0);
				break;
			case(STEAMENGINE):
				steamEngine = ImageManager::GetSingleton()->FindImage("steam-engine-vertical");
				steamEngine->FrameRender(hdc, toolInvenInfo[9][0].rc.left + 160 / 2, toolInvenInfo[9][0].rc.top + 128 / 2, 0, 0,0.7);
				break;
			case(BASICMININGDRILL):
				basicMiningDrillEast->FrameRender(hdc, toolInvenInfo[9][0].rc.left + 128 / 2, toolInvenInfo[9][0].rc.top + 128 / 2, 0, 0);
				break;
			case(ELECTRICFURNACE):
				electricFurnace->FrameRender(hdc, toolInvenInfo[9][0].rc.left + 128 / 2, toolInvenInfo[9][0].rc.top + 128 / 2, 0, 0);
				break;
			case(BASICINSERTER):
				basicInserter->FrameRender(hdc, toolInvenInfo[9][0].rc.left + 128 / 2, toolInvenInfo[9][0].rc.top + 128 / 2, 0, 0);
				break;

			case(WOODENCHEST):
				icon[WOODENCHEST]->FrameRender(hdc, toolInvenInfo[9][0].rc.left + 128 / 2, toolInvenInfo[9][0].rc.top + 128 / 2, 0, 0, 2);
				break;

			case(STEELCHEST):
				icon[STEELCHEST]->FrameRender(hdc, toolInvenInfo[9][0].rc.left + 128 / 2, toolInvenInfo[9][0].rc.top + 128 / 2, 0, 0, 2);
				break;

			case(ASSEMBLINGMACHINE):
				icon[ASSEMBLINGMACHINE]->FrameRender(hdc, toolInvenInfo[9][0].rc.left + 128 / 2, toolInvenInfo[9][0].rc.top + 128 / 2, 0, 0, 2);


				if ((*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetLayer() == IRONGEARWHEEL)
				{
					for (int i = 0; i < 7; i++)
					{
						if (i == 0)
							SelectObject(hdc, YellowBrush);
						else
							SelectObject(hdc, GrayBrush);


						if (i != 5)
							Rectangle(hdc, toolInvenInfo[11][i].rc.left, toolInvenInfo[11][i].rc.top, toolInvenInfo[11][i].rc.right, toolInvenInfo[11][i].rc.bottom);
					}

					icon[IRONPLATE]->AlphaRender(hdc, toolInvenInfo[11][4].rc.left + 39 / 2, toolInvenInfo[11][4].rc.top + 39 / 2, 0, 0, 120, 1);
					icon[IRONGEARWHEEL]->AlphaRender(hdc, toolInvenInfo[11][6].rc.left + 39 / 2, toolInvenInfo[11][6].rc.top + 39 / 2, 0, 0, 120, 1);
				}

				else if ((*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetLayer() == COPPERCABLE)
				{
					for (int i = 0; i < 7; i++)
					{
						if (i == 1)
							SelectObject(hdc, YellowBrush);
						else
							SelectObject(hdc, GrayBrush);

						if (i != 5)
							Rectangle(hdc, toolInvenInfo[11][i].rc.left, toolInvenInfo[11][i].rc.top, toolInvenInfo[11][i].rc.right, toolInvenInfo[11][i].rc.bottom);
					}

					icon[COPPERPLATE]->AlphaRender(hdc, toolInvenInfo[11][4].rc.left + 39 / 2, toolInvenInfo[11][4].rc.top + 39 / 2, 0, 0, 120, 1);
					icon[COPPERCABLE]->AlphaRender(hdc, toolInvenInfo[11][6].rc.left + 39 / 2, toolInvenInfo[11][6].rc.top + 39 / 2, 0, 0, 120, 1);
				}

				else if ((*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetLayer() == ELECTRONICCIRCUIT)
				{
					for (int i = 0; i < 7; i++)
					{
						if (i == 2)
							SelectObject(hdc, YellowBrush);
						else
							SelectObject(hdc, GrayBrush);

						Rectangle(hdc, toolInvenInfo[11][i].rc.left, toolInvenInfo[11][i].rc.top, toolInvenInfo[11][i].rc.right, toolInvenInfo[11][i].rc.bottom);
					}

					icon[IRONPLATE]->AlphaRender(hdc, toolInvenInfo[11][4].rc.left + 39 / 2, toolInvenInfo[11][4].rc.top + 39 / 2, 0, 0, 120, 1);
					icon[COPPERCABLE]->AlphaRender(hdc, toolInvenInfo[11][5].rc.left + 39 / 2, toolInvenInfo[11][5].rc.top + 39 / 2, 0, 0, 120, 1);
					icon[ELECTRONICCIRCUIT]->AlphaRender(hdc, toolInvenInfo[11][6].rc.left + 39 / 2, toolInvenInfo[11][6].rc.top + 39 / 2, 0, 0, 120, 1);
				}

				else if ((*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetLayer() == ADVANCEDCIRCUIT)
				{
					for (int i = 0; i < 7; i++)
					{
						if (i == 3)
							SelectObject(hdc, YellowBrush);
						else
							SelectObject(hdc, GrayBrush);

						Rectangle(hdc, toolInvenInfo[11][i].rc.left, toolInvenInfo[11][i].rc.top, toolInvenInfo[11][i].rc.right, toolInvenInfo[11][i].rc.bottom);
					}

					icon[ELECTRONICCIRCUIT]->AlphaRender(hdc, toolInvenInfo[11][4].rc.left + 39 / 2, toolInvenInfo[11][4].rc.top + 39 / 2, 0, 0, 120, 1);
					icon[COPPERCABLE]->AlphaRender(hdc, toolInvenInfo[11][5].rc.left + 39 / 2, toolInvenInfo[11][5].rc.top + 39 / 2, 0, 0, 120, 1);
					icon[ADVANCEDCIRCUIT]->AlphaRender(hdc, toolInvenInfo[11][6].rc.left + 39 / 2, toolInvenInfo[11][6].rc.top + 39 / 2, 0, 0, 120, 1);
				}

				assemblinginven->AlphaRender(hdc, baseRc.left + 780, baseRc.top + 10, 150);


				Rectangle(hdc, toolInvenInfo[9][1].rc.left + 50, toolInvenInfo[9][1].rc.top + 50, toolInvenInfo[9][1].rc.left + 150, toolInvenInfo[9][1].rc.top + 60);

				SelectObject(hdc, GreenBrush);
				Rectangle(hdc, toolInvenInfo[9][1].rc.left + 50, toolInvenInfo[9][1].rc.top + 50,
					toolInvenInfo[9][1].rc.left + 50 + (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetMaterialGage(), toolInvenInfo[9][1].rc.top + 60);

				icon[IRONGEARWHEEL]->FrameRender(hdc, toolInvenInfo[11][0].rc.left + 39 / 2, toolInvenInfo[11][0].rc.top + 39 / 2, 0, 0);
				icon[COPPERCABLE]->FrameRender(hdc, toolInvenInfo[11][1].rc.left + 39 / 2, toolInvenInfo[11][1].rc.top + 39 / 2, 0, 0);
				icon[ELECTRONICCIRCUIT]->FrameRender(hdc, toolInvenInfo[11][2].rc.left + 39 / 2, toolInvenInfo[11][2].rc.top + 39 / 2, 0, 0);
				icon[ADVANCEDCIRCUIT]->FrameRender(hdc, toolInvenInfo[11][3].rc.left + 39 / 2, toolInvenInfo[11][3].rc.top + 39 / 2, 0, 0);


				break;

			case(ROCKET):
				icon[ROCKET]->FrameRender(hdc, toolInvenInfo[9][0].rc.left + 128 / 2, toolInvenInfo[9][0].rc.top + 128 / 2, 0, 0, 2);

				for (int i = 7; i < 10; i++)
				{
					Rectangle(hdc, toolInvenInfo[11][i].rc.left, toolInvenInfo[11][i].rc.top, toolInvenInfo[11][i].rc.right, toolInvenInfo[11][i].rc.bottom);
				}

				icon[IRONGEARWHEEL]->AlphaRender(hdc, toolInvenInfo[11][7].rc.left + 39 / 2, toolInvenInfo[11][7].rc.top + 39 / 2, 0, 0, 120, 1);
				icon[ELECTRONICCIRCUIT]->AlphaRender(hdc, toolInvenInfo[11][8].rc.left + 39 / 2, toolInvenInfo[11][8].rc.top + 39 / 2, 0, 0, 120, 1);
				icon[ADVANCEDCIRCUIT]->AlphaRender(hdc, toolInvenInfo[11][9].rc.left + 39 / 2, toolInvenInfo[11][9].rc.top + 39 / 2, 0, 0, 120, 1);
				
				Rectangle(hdc, toolInvenInfo[9][1].rc.left -20, toolInvenInfo[9][1].rc.top + 50, toolInvenInfo[9][1].rc.left + 180, toolInvenInfo[9][1].rc.top + 60);

				SelectObject(hdc, GreenBrush);
				Rectangle(hdc, toolInvenInfo[9][1].rc.left - 20, toolInvenInfo[9][1].rc.top + 50,
					toolInvenInfo[9][1].rc.left - 20 + (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetMaterialGage(), toolInvenInfo[9][1].rc.top + 60);
				break;
			}
		
			SelectObject(hdc, GrayBrush);

			if (selectObjInven[1])
			{
				Rectangle(hdc, toolInvenInfo[9][1].rc.left + 50, toolInvenInfo[9][1].rc.top + 20, toolInvenInfo[9][1].rc.left + 150, toolInvenInfo[9][1].rc.top + 30);
			}
			if (selectObjInven[3])
			{
				Rectangle(hdc, toolInvenInfo[9][3].rc.left + 50, toolInvenInfo[9][3].rc.top + 20, toolInvenInfo[9][3].rc.left + 150, toolInvenInfo[9][3].rc.top + 30);
			}

			

			if (selectObjInven[1])
			{
				
				SelectObject(hdc, RedBrush);

				Rectangle(hdc, toolInvenInfo[9][1].rc.left + 50, toolInvenInfo[9][1].rc.top + 20,
					toolInvenInfo[9][1].rc.left + 50 + (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetFuelGage(), toolInvenInfo[9][1].rc.top + 30);

				
			}

			if (selectObjInven[3])
			{
				SelectObject(hdc, GreenBrush);
				Rectangle(hdc, toolInvenInfo[9][3].rc.left + 50, toolInvenInfo[9][3].rc.top + 20,
					toolInvenInfo[9][3].rc.left + 50 + (*ObjectManager::GetSingleton()->GetObjectList(tileinfo[selectObj.y][selectObj.x].obj)).
					find({ selectObj.x ,selectObj.y })->second->GetMaterialGage(), toolInvenInfo[9][3].rc.top + 30);
				
			}

			if (selectObjInven[5])
			{
				for (int i = 0; i < 5; i++)
				{
					Rectangle(hdc, toolInvenInfo[10][i].rc.left, toolInvenInfo[10][i].rc.top, toolInvenInfo[10][i].rc.right, toolInvenInfo[10][i].rc.bottom);
				}
			}

			if (selectObjInven[6])
			{
				for (int i = 0; i < 10; i++)
				{
					Rectangle(hdc, toolInvenInfo[10][i].rc.left, toolInvenInfo[10][i].rc.top, toolInvenInfo[10][i].rc.right, toolInvenInfo[10][i].rc.bottom);
				}
			}

			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (toolInvenInfo[i][j].isStorage)
					{
						if (!toolInvenInfo[i][j].isSelected)
						{
							if (icon[toolInvenInfo[i][j].name])
								icon[toolInvenInfo[i][j].name]->FrameRender(hdc, toolInvenInfo[i][j].rc.left + 39 / 2, toolInvenInfo[i][j].rc.top + 39 / 2, 0, 0);
							wsprintf(sZtext, "%d", toolInvenInfo[i][j].num);
							TextOut(hdc, toolInvenInfo[i][j].rc.left + 39 / 2, toolInvenInfo[i][j].rc.top + 39 / 2, sZtext, strlen(sZtext));
						}
					}

				}
			}
			
			if (isSelect)
			{					
				if (icon[toolInvenInfo[selectIndexY][selectIndexX].name])
					icon[toolInvenInfo[selectIndexY][selectIndexX].name]->FrameRender(hdc, g_ptMouse.x, g_ptMouse.y, 0, 0);
				wsprintf(sZtext, "%d", toolInvenInfo[selectIndexY][selectIndexX].num);
				TextOut(hdc, g_ptMouse.x, g_ptMouse.y, sZtext, strlen(sZtext));	
			}
		}
	}
}


void Inventory::CraftInvenInit()
{
	craftBtImg[0] = ImageManager::GetSingleton()->FindImage("intermediate-products");
	craftBtImg[1] = ImageManager::GetSingleton()->FindImage("logistics");
	craftBtImg[2] = ImageManager::GetSingleton()->FindImage("production");
	craftBtImg[3] = ImageManager::GetSingleton()->FindImage("military");
	
	craftBtIndex = 0;
	for (int i = 0; i < 4; ++i)
	{
		craftBtState[i] = BUTTON_STATE::NONE;
		craftBtRc[i] = { 813 + 68 * i, 285, 877 + 68 * i, 349 };
	}

	/***********************/
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; ++j)
		{
			craftItemRc[i][j] = { 813 + 41 * j, 365 + 41 * i, 852 + 41 * j, 404 + 41 * i };
		}
	}

	// 추가해야 될 부분 : 여기 + 인벤토리에 들어간 후 처리
	craftItemInfo[0][0][1] = new SteelChestCraft({ 0, 1 });
	craftItemInfo[0][4][0] = new CopperCableCraft({ 4, 0 });
	craftItemInfo[2][1][0] = new IronStickCraft({ 1, 0 });
	craftItemInfo[2][1][1] = new IronGearWheelCraft({ 1, 1 });
	craftItemInfo[1][0][0] = new IronAxeCraft({ 0, 0 }, craftItemInfo[2][1][0]);
	craftItemInfo[0][1][0] = new BasicTransportBeltCraft({ 1, 0 }, craftItemInfo[2][1][1]);
	craftItemInfo[1][3][0] = new StoneFurnaceCraft({ 3, 0 });
	craftItemInfo[2][0][0] = new WoodCraft({ 0, 0 });
	craftItemInfo[0][0][0] = new WoodenChestCraft({ 0, 0 }, craftItemInfo[2][0][0]);
	craftItemInfo[0][2][0] = new BurnerInserterCraft({ 2, 0 }, craftItemInfo[2][1][1]);
	craftItemInfo[2][1][2] = new ElectronicCircuitCraft({ 1, 2 }, craftItemInfo[0][4][0]);
	craftItemInfo[1][2][0] = new BurnerMiningDrillCraft({ 2, 0 }, craftItemInfo[2][1][1], craftItemInfo[1][3][0]);
	craftItemInfo[0][3][0] = new SmallElectricPoleCraft({ 3, 0 }, craftItemInfo[2][0][0], craftItemInfo[0][4][0]);
	craftItemInfo[0][2][1] = new BasicInserterCraft({ 2, 1 }, craftItemInfo[2][1][2], craftItemInfo[2][1][1]);
	craftItemInfo[1][2][1] = new BasicMiningDrillCraft({ 2, 1 }, craftItemInfo[2][1][2], craftItemInfo[2][1][1]);
	craftItemInfo[1][3][1] = new ElectricFurnaceCraft({ 3, 1 }, craftItemInfo[2][1][0], craftItemInfo[2][1][2]);
	craftItemInfo[1][1][1] = new SteamEngineCraft({ 1, 1 }, craftItemInfo[2][1][1], craftItemInfo[1][3][0]);
	craftItemInfo[1][4][0] = new AssemblingMachineCraft({ 4, 0 }, craftItemInfo[2][1][2], craftItemInfo[2][1][1]);
	craftItemInfo[0][1][1] = new BasicSplitterCraft({ 1, 1 }, craftItemInfo[2][1][2], craftItemInfo[0][1][0]);
	craftItemInfo[0][2][2] = new LongHandedInserterCraft({ 2, 2 }, craftItemInfo[2][1][1], craftItemInfo[0][2][1]);
}

void Inventory::CraftInvenRelease()
{
}

void Inventory::CraftInvenUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&craftBtRc[i], g_ptMouse))
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				craftBtState[i] = BUTTON_STATE::DOWN;
			}
			else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON) && craftBtState[i] == BUTTON_STATE::DOWN)
			{
				craftBtState[i] = BUTTON_STATE::UP;

				craftBtIndex = i;

			}
		}

		else
		{
			craftBtState[i] = BUTTON_STATE::NONE;
		}
	}

	/***********************/
	bool isFull = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (inveninfo[i][j].name != EMPTY)
			{
				isFull = true;
			}
				
			else
			{
				isFull = false;
				goto skipcraft;
			}
				
		}
	}
skipcraft:

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			if (PtInRect(&craftItemRc[i][j], g_ptMouse))
			{
				if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
				{
					if (!isFull)
					{
						if (craftItemInfo[craftBtIndex][i][j])
						{
							craftItemInfo[craftBtIndex][i][j]->ProductItem();
						}

						for (int k = 0; k < 4; ++k)
						{
							for (int _i = 0; _i < 6; ++_i)
							{
								for (int _j = 0; _j < 6; ++_j)
								{
									if (craftItemInfo[k][_i][_j])
									{
										craftItemInfo[k][_i][_j]->CheckProduct();
									}
								}
							}
						}
					}
				}
			}
		}

	}

}

void Inventory::CraftInvenRender(HDC hdc)
{

	for (int i = 0; i < 4; i++)
	{
		if (craftBtState[i] == BUTTON_STATE::DOWN)
		{
			craftBtImg[i]->FrameRender(hdc, craftBtRc[i].left + 32, craftBtRc[i].top + 32, 0, 1);
		}
		else
		{
			craftBtImg[i]->FrameRender(hdc, craftBtRc[i].left + 32, craftBtRc[i].top + 32, 0, 0);
		}
	}

	SelectObject(hdc, GrayBrush);

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; ++j)
		{
			Rectangle(hdc, craftItemRc[i][j].left, craftItemRc[i][j].top, craftItemRc[i][j].right, craftItemRc[i][j].bottom);
		}
	}

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			if (craftItemInfo[craftBtIndex][i][j])
			{
				craftItemInfo[craftBtIndex][i][j]->Render(hdc);
			}
		}
	}

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			if (craftItemInfo[craftBtIndex][i][j])
			{

				if (PtInRect(&craftItemRc[i][j], g_ptMouse))
				{
					craftItemInfo[craftBtIndex][i][j]->InfoRender(hdc);
				}
			}
		}
	}
}

void Inventory::ObjectRender(HDC hdc)
{

	if (isSelect)

	{	//추우우우우우우가아아아아아아아
		if ((isOpen && !(PtInRect(&baseRc, g_ptMouse) || PtInRect(&quickRc, g_ptMouse))) && !ToolInvenIsOpen
			|| (!isOpen && !PtInRect(&quickRc, g_ptMouse)) && !ToolInvenIsOpen)
		{

			//추가
			if (inveninfo[selectIndexY][selectIndexX].name == STONEFURNACE)
			{
				RECT temprc = GetRectToCenter((int)g_ptMouse.x / 32 * 32,
					(int)g_ptMouse.y / 32 * 32, 64, 64);

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)
				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY ||
							((tempIndex.y - i) == (int)g_pos.y / 32 && (tempIndex.x - j) == (int)g_pos.x / 32))
						{
							SelectObject(hdc, RedBrush);
							goto skip;
						}

						else
						{
							SelectObject(hdc, GreenBrush);
						}
					}
				}

			skip:

				Rectangle(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 64,
					(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 64);
				//stoneFurnace->AlphaRender(hdc, (int)(g_ptMouse.x+g_pos.x) / 32 * 32 + 17 / 2 - g_pos.x, ((int)g_ptMouse.y+g_pos.y) / 32 * 32 -g_pos.y,150);
				stoneFurnace->AlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 81 / 2,
					(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32, 150);
				(HBRUSH)SelectObject(hdc, OldBrush);

			}

			// 추가한곳 //
			else if (inveninfo[selectIndexY][selectIndexX].name == BURNERINSERTER)
			{

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)


				if (tileinfo[tempIndex.y][tempIndex.x].obj != EMPTY)
				{
					SelectObject(hdc, RedBrush);
				}

				else
				{
					SelectObject(hdc, GreenBrush);
				}


				Rectangle(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32,
					(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32);

				burnerInserter->FrameAlphaRender(hdc, ((tempIndex.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32 / 2,
					((tempIndex.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 150);
			}


			else if (inveninfo[selectIndexY][selectIndexX].name == BURNERMININGDRILL)
			{
				RECT temprc = GetRectToCenter((int)g_ptMouse.x / 32 * 32,
					(int)g_ptMouse.y / 32 * 32, 64, 64);

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)


				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY)
						{
							SelectObject(hdc, RedBrush);
							goto skip1;
						}

						else
						{
							SelectObject(hdc, GreenBrush);
						}

					}
				}

				// 자원이 있는 곳만 채광
				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						if (tileinfo[tempIndex.y - i][tempIndex.x - j].res != EMPTY)
						{
							goto skip1;
						}
					}
				}

				SelectObject(hdc, GrayBrush);

			skip1:


				Rectangle(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 64,
					(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 64);

				burnerMiningDrillEast->FrameAlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 81 / 2,
					(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32, 0, 0, 150);
			}

			else if (inveninfo[selectIndexY][selectIndexX].name == BASICTRANSPORTBELT)
			{
				RECT temprc = GetRectToCenter((int)g_ptMouse.x / 32 * 32,
					(int)g_ptMouse.y / 32 * 32, 32, 32);

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)
				for (int i = 0; i < 1; i++)
				{
					for (int j = 0; j < 1; j++)
					{
						if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY ||
							((tempIndex.y - i) == (int)g_pos.y / 32 && (tempIndex.x - j) == (int)g_pos.x / 32))
						{
							SelectObject(hdc, RedBrush);
							goto skip2;
						}

						else
						{
							SelectObject(hdc, GreenBrush);
						}
					}
				}

			skip2:

				Rectangle(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32,
					(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32);



				if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
				{
					
					beltinfo++;
					Tutorial::GetSingleton()->SucceedQuest_10();

				}
				if (beltinfo == 4)
				{
					beltinfo = 0;
				}
				frameX = 0;
				if (beltinfo == 0) // 오른쪽
				{
					isWidthReverse = false;
					isHeightReverse = false;
					frameY = 0;
				}

				if (beltinfo == 1) // 왼쪽
				{
					isWidthReverse = true;
					isHeightReverse = false;
				}

				else if (beltinfo == 2) // 위
				{
					isWidthReverse = false;
					isHeightReverse = false;
					frameY = 1;
				}

				else if (beltinfo == 3) // 아래
				{
					isHeightReverse = true;

				}


				basicTransportBelt->FrameAlphaRender(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32 / 2,
					(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32 / 2, frameX, frameY, 150, isWidthReverse, isHeightReverse);


			}


			else if (inveninfo[selectIndexY][selectIndexX].name == ROCKET)
			{
				RECT temprc = GetRectToCenter((int)g_ptMouse.x / 32 * 32,
					(int)g_ptMouse.y / 32 * 32, 64, 64);

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY ||
							((tempIndex.y - i) == (int)g_pos.y / 32 && (tempIndex.x - j) == (int)g_pos.x / 32))
						{
							SelectObject(hdc, RedBrush);
							goto skip3;
						}

						else
						{
							SelectObject(hdc, GreenBrush);
						}
					}
				}

			skip3:

				Rectangle(hdc, (((tempIndex.x - 9) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32
					, (((tempIndex.y - 9) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x - 9) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 320,
					(((tempIndex.y - 9) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 320);
				//stoneFurnace->AlphaRender(hdc, (int)(g_ptMouse.x+g_pos.x) / 32 * 32 + 17 / 2 - g_pos.x, ((int)g_ptMouse.y+g_pos.y) / 32 * 32 -g_pos.y,150);
				rocketBase->AlphaRender(hdc, (((tempIndex.x - 5) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48,
					(((tempIndex.y - 6) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 64, 150);
				(HBRUSH)SelectObject(hdc, OldBrush);

			}

			else if (inveninfo[selectIndexY][selectIndexX].name == SMALLELECTRICPOLE)
			{

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)


				if (tileinfo[tempIndex.y][tempIndex.x].obj != EMPTY)
				{
					SelectObject(hdc, RedBrush);
				}

				else
				{
					SelectObject(hdc, GreenBrush);
				}


				blueRectangle->FrameAlphaRender(hdc, ((tempIndex.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 16,
					((tempIndex.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 150);

				Rectangle(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32,
					(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32);



				smallElectricPole->FrameAlphaRender(hdc, ((tempIndex.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 45,
					((tempIndex.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 20, 3, 0, 150);


			}

			else if (inveninfo[selectIndexY][selectIndexX].name == BASICINSERTER)
			{

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)


				if (tileinfo[tempIndex.y][tempIndex.x].obj != EMPTY)
				{
					SelectObject(hdc, RedBrush);
				}

				else
				{
					SelectObject(hdc, GreenBrush);
				}


				Rectangle(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32,
					(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32);

				basicInserter->FrameAlphaRender(hdc, ((tempIndex.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32 / 2,
					((tempIndex.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 150);
			}

			else if (inveninfo[selectIndexY][selectIndexX].name == BASICMININGDRILL)
			{
				RECT temprc = GetRectToCenter((int)g_ptMouse.x / 32 * 32,
					(int)g_ptMouse.y / 32 * 32, 64, 64);

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)


				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY)
						{
							SelectObject(hdc, RedBrush);
							goto skip5;
						}

						else
						{
							SelectObject(hdc, GreenBrush);
						}

					}
				}

				// 자원이 있는 곳만 채광
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (tileinfo[tempIndex.y - i][tempIndex.x - j].res != EMPTY)
						{
							goto skip5;
						}
					}
				}

				SelectObject(hdc, GrayBrush);

			skip5:


				Rectangle(hdc, (((tempIndex.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 96,
					(((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 96);

				basicMiningDrillEast->FrameAlphaRender(hdc, (((tempIndex.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 60,
					(((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 46, 0, 0, 150);
			}

			else if (inveninfo[selectIndexY][selectIndexX].name == ELECTRICFURNACE)
			{
				RECT temprc = GetRectToCenter((int)g_ptMouse.x / 32 * 32,
					(int)g_ptMouse.y / 32 * 32, 64, 64);

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY ||
							((tempIndex.y - i) == (int)g_pos.y / 32 && (tempIndex.x - j) == (int)g_pos.x / 32))
						{
							SelectObject(hdc, RedBrush);
							goto skip6;
						}

						else
						{
							SelectObject(hdc, GreenBrush);
						}
					}
				}

			skip6:

				Rectangle(hdc, (((tempIndex.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 96,
					(((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 96);
				//stoneFurnace->AlphaRender(hdc, (int)(g_ptMouse.x+g_pos.x) / 32 * 32 + 17 / 2 - g_pos.x, ((int)g_ptMouse.y+g_pos.y) / 32 * 32 -g_pos.y,150);
				electricFurnace->AlphaRender(hdc, (((tempIndex.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 48,
					(((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 48, 150);
				(HBRUSH)SelectObject(hdc, OldBrush);

			}


			else if (inveninfo[selectIndexY][selectIndexX].name == STEAMENGINE)
			{
				RECT temprc = GetRectToCenter((int)g_ptMouse.x / 32 * 32,
					(int)g_ptMouse.y / 32 * 32, 64, 64);

				if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
				{
					Tutorial::GetSingleton()->SucceedQuest_10();
					steamEngineInfo++;
					if (steamEngineInfo > 3)
					{
						steamEngineInfo = 0;
					}
				}

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)

				if (steamEngineInfo == 0) // 오른쪽
				{
					steamEngine = ImageManager::GetSingleton()->FindImage("steam-engine-horizontal");
					boiler = ImageManager::GetSingleton()->FindImage("boiler-left");
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							if (tileinfo[tempIndex.y + 1 - i][tempIndex.x - j].obj != EMPTY ||
								!(tileinfo[tempIndex.y][tempIndex.x - 1].terrain == TR_WATER && tileinfo[tempIndex.y][tempIndex.x - 2].terrain != TR_WATER))
							{
								SelectObject(hdc, RedBrush);
								goto skipsteam;
							}

							else
							{
								SelectObject(hdc, GreenBrush);
							}

						}
					}

					// 자원이 있는 곳만 채광



				skipsteam:


					Rectangle(hdc, (((tempIndex.x - 8) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
						, (((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
						(((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 64,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 64);

					offshorePump->FrameAlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 10,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 1, 0, 150);

					boiler->FrameAlphaRender(hdc, (((tempIndex.x - 3) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 16,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 150);

					steamEngine->FrameAlphaRender(hdc, (((tempIndex.x - 7) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 10,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 150, true, false);
				}

				else if (steamEngineInfo == 1) // 왼쪽
				{
					steamEngine = ImageManager::GetSingleton()->FindImage("steam-engine-horizontal");
					boiler = ImageManager::GetSingleton()->FindImage("boiler-left");

					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							if (tileinfo[tempIndex.y + 1 - i][tempIndex.x - j].obj != EMPTY ||
								!(tileinfo[tempIndex.y + 1][tempIndex.x - 6].terrain == TR_WATER && tileinfo[tempIndex.y + 1][tempIndex.x - 5].terrain != TR_WATER))
							{
								SelectObject(hdc, RedBrush);
								goto skipsteam1;
							}

							else
							{
								SelectObject(hdc, GreenBrush);
							}

						}
					}

					// 자원이 있는 곳만 채광



				skipsteam1:


					Rectangle(hdc, (((tempIndex.x - 8) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
						, (((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
						(((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 64,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 64);

					offshorePump->FrameAlphaRender(hdc, (((tempIndex.x - 5) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 10,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 26, 3, 0, 150);

					boiler->FrameAlphaRender(hdc, (((tempIndex.x - 5) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 10,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 26, 0, 0, 150, true, false);

					steamEngine->FrameAlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 20,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 150, false, false);
				}

				else if (steamEngineInfo == 2) // 위
				{
					steamEngine = ImageManager::GetSingleton()->FindImage("steam-engine-vertical");
					boiler = ImageManager::GetSingleton()->FindImage("boiler-down");

					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							if (tileinfo[tempIndex.y + 1 - i][tempIndex.x - j].obj != EMPTY ||
								!(tileinfo[tempIndex.y - 5][tempIndex.x].terrain == TR_WATER && tileinfo[tempIndex.y - 4][tempIndex.x].terrain != TR_WATER))
							{
								SelectObject(hdc, RedBrush);
								goto skipsteam2;
							}

							else
							{
								SelectObject(hdc, GreenBrush);
							}

						}
					}

					// 자원이 있는 곳만 채광



				skipsteam2:


					Rectangle(hdc, (((tempIndex.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
						, (((tempIndex.y - 7) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
						(((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 64,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 64);

					offshorePump->FrameAlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 35,
						(((tempIndex.y - 6) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 12, 0, 0, 150);

					boiler->FrameAlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 5,
						(((tempIndex.y - 5) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 12, 0, 0, 150, false, true);

					steamEngine->FrameAlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 30,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) - 20, 0, 0, 150, false, true);
				}

				else if (steamEngineInfo == 3) // 아래
				{
					steamEngine = ImageManager::GetSingleton()->FindImage("steam-engine-vertical");
					boiler = ImageManager::GetSingleton()->FindImage("boiler-down");

					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							if (tileinfo[tempIndex.y + 1 - i][tempIndex.x - j].obj != EMPTY ||
								!(tileinfo[tempIndex.y][tempIndex.x].terrain == TR_WATER && tileinfo[tempIndex.y - 1][tempIndex.x].terrain != TR_WATER))
							{
								SelectObject(hdc, RedBrush);
								goto skipsteam3;
							}

							else
							{
								SelectObject(hdc, GreenBrush);
							}

						}
					}

					// 자원이 있는 곳만 채광



				skipsteam3:


					Rectangle(hdc, (((tempIndex.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
						, (((tempIndex.y - 7) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
						(((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 64,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 64);

					offshorePump->FrameAlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 50,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 26, 2, 0, 150);

					boiler->FrameAlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 20,
						(((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32), 0, 0, 150, false, false);

					steamEngine->FrameAlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 45,
						(((tempIndex.y - 5) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32), 0, 0, 150, false, false);
				}



			}


			else if (inveninfo[selectIndexY][selectIndexX].name == WOODENCHEST)
			{

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)


				if (tileinfo[tempIndex.y][tempIndex.x].obj != EMPTY)
				{
					SelectObject(hdc, RedBrush);
				}

				else
				{
					SelectObject(hdc, GreenBrush);
				}


				Rectangle(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32,
					(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32);

				icon[WOODENCHEST]->FrameAlphaRender(hdc, ((tempIndex.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32 / 2,
					((tempIndex.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 150);
			}

			else if (inveninfo[selectIndexY][selectIndexX].name == ASSEMBLINGMACHINE)
			{
				RECT temprc = GetRectToCenter((int)g_ptMouse.x / 32 * 32,
					(int)g_ptMouse.y / 32 * 32, 64, 64);

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY ||
							((tempIndex.y - i) == (int)g_pos.y / 32 && (tempIndex.x - j) == (int)g_pos.x / 32))
						{
							SelectObject(hdc, RedBrush);
							goto skipassem;
						}

						else
						{
							SelectObject(hdc, GreenBrush);
						}
					}
				}

			skipassem:

				Rectangle(hdc, (((tempIndex.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 96,
					(((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 96);
				//stoneFurnace->AlphaRender(hdc, (int)(g_ptMouse.x+g_pos.x) / 32 * 32 + 17 / 2 - g_pos.x, ((int)g_ptMouse.y+g_pos.y) / 32 * 32 -g_pos.y,150);
				assemblingMachine->AlphaRender(hdc, (((tempIndex.x - 2) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 56,
					(((tempIndex.y - 2) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 40, 0, 0, 150, 1);
				(HBRUSH)SelectObject(hdc, OldBrush);

			}

			else if (inveninfo[selectIndexY][selectIndexX].name == BASICSPLITTER)
			{
				if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
				{
					splitterDirection++;
					Tutorial::GetSingleton()->SucceedQuest_10();
					if (splitterDirection > 3)
					{
						splitterDirection = 0;
					}
				}

				// 주변에 오브젝트가 있는지 검사 (있으면 빨간색바탕 없으면 초록색바탕)

				if (splitterDirection == 0) // 오른쪽
				{
					basicSplitter = ImageManager::GetSingleton()->FindImage("basic-splitter-east");
					for (int i = 0; i < 2; i++)
					{
						for (int j = 0; j < 1; j++)
						{
							if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY ||
								(tileinfo[tempIndex.y - i][tempIndex.x - j].terrain == TR_WATER))
							{
								SelectObject(hdc, RedBrush);
								goto skipsplitter;
							}

							else
							{
								SelectObject(hdc, GreenBrush);
							}

						}
					}

					// 자원이 있는 곳만 채광



				skipsplitter:


					Rectangle(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
						, (((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
						(((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 64);

					basicSplitter->FrameAlphaRender(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 16,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32, 0, 0, 150, false, false);
				}

				else if (splitterDirection == 1) // 왼쪽
				{
					basicSplitter = ImageManager::GetSingleton()->FindImage("basic-splitter-west");

					for (int i = 0; i < 2; i++)
					{
						for (int j = 0; j < 1; j++)
						{
							if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY ||
								(tileinfo[tempIndex.y - i][tempIndex.x - j].terrain == TR_WATER))
							{
								SelectObject(hdc, RedBrush);
								goto skipsplitter1;
							}

							else
							{
								SelectObject(hdc, GreenBrush);
							}

						}
					}

					// 자원이 있는 곳만 채광



				skipsplitter1:

					Rectangle(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
						, (((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
						(((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 64);

					basicSplitter->FrameAlphaRender(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 16,
						(((tempIndex.y - 1) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32, 0, 0, 150, false, false);
				}

				else if (splitterDirection == 2) // 위
				{
					basicSplitter = ImageManager::GetSingleton()->FindImage("basic-splitter-north");

					for (int i = 0; i < 1; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY ||
								(tileinfo[tempIndex.y - i][tempIndex.x - j].terrain == TR_WATER))
							{
								SelectObject(hdc, RedBrush);
								goto skipsplitter2;
							}

							else
							{
								SelectObject(hdc, GreenBrush);
							}

						}
					}

					// 자원이 있는 곳만 채광



				skipsplitter2:


					Rectangle(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
						, (((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
						(((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 64,
						(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32);

					basicSplitter->FrameAlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 38,
						(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 150, false, false);
				}

				else if (splitterDirection == 3) // 아래
				{
					basicSplitter = ImageManager::GetSingleton()->FindImage("basic-splitter-south");

					for (int i = 0; i < 1; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							if (tileinfo[tempIndex.y - i][tempIndex.x - j].obj != EMPTY ||
								(tileinfo[tempIndex.y - i][tempIndex.x - j].terrain == TR_WATER))
							{
								SelectObject(hdc, RedBrush);
								goto skipsplitter3;
							}

							else
							{
								SelectObject(hdc, GreenBrush);
							}

						}
					}

					// 자원이 있는 곳만 채광



				skipsplitter3:


					Rectangle(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
						, (((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
						(((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 64,
						(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32);

					basicSplitter->FrameAlphaRender(hdc, (((tempIndex.x - 1) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 38,
						(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 150, false, false);
				}


			}
			else if (inveninfo[selectIndexY][selectIndexX].name == LONGHANDEDINSERTER)
			{

				if (tileinfo[tempIndex.y][tempIndex.x].obj != EMPTY)
				{
					SelectObject(hdc, RedBrush);
				}

				else
				{
					SelectObject(hdc, GreenBrush);
				}


				Rectangle(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32,
					(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32);

				longHandedInster->FrameAlphaRender(hdc, ((tempIndex.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32 / 2,
					((tempIndex.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 150);
			}


			else if (inveninfo[selectIndexY][selectIndexX].name == STEELCHEST)
			{
			
				if (tileinfo[tempIndex.y][tempIndex.x].obj != EMPTY)
				{
					SelectObject(hdc, RedBrush);
				}

				else
				{
					SelectObject(hdc, GreenBrush);
				}


				Rectangle(hdc, (((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32)
					, (((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32),
					(((tempIndex.x) - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32,
					(((tempIndex.y) - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 32);

				icon[STEELCHEST]->FrameAlphaRender(hdc, ((tempIndex.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32 / 2,
					((tempIndex.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16, 0, 0, 150);
			}
			
		}

		

		


	}
}

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}
