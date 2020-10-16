#pragma once
#include "GameNode.h"

class CraftItemInfo;
class Image;
class Inventory : public GameNode
{
	POINT tempIndex;
	POINT selectObj;

	RECT baseRc;
	RECT quickRc;

	Image* inventory;
	Image* fastinventory;
	Image* stoneFurnace;
	Image* invenImage;
	Image* basicTransportBelt;
	Image* burnerInserter;
	Image* burnerMiningDrillEast;
	Image* rocketBase;
	Image* smallElectricPole;
	Image* blueRectangle;
	Image* basicInserter;
	Image* basicMiningDrillEast;
	Image* electricFurnace;
	Image* steamEngineIcon;
	Image* offshorePump;
	Image* boiler;
	Image* steamEngine;
	Image* assemblingMachine;
	Image* assemblinginven;
	Image* basicSplitter;

	//추가
	Image* longHandedInster;

	// 아이콘 //
	Image* icon[Layer_END];

	
	
	bool checkSelect = false;
	bool isOpen;
	bool isSelect;
	bool ToolInvenIsSelect;
	bool ToolInvenIsBackUp;
	bool isWidthReverse;
	bool isHeightReverse;
	int blockClick;

	int selectIndexX;
	int selectIndexY;
	int frameX;
	int frameY;
	int beltinfo;
	int steamEngineInfo;
	int splitterDirection;


	HBRUSH OldBrush, GrayBrush, GreenBrush, RedBrush , YellowBrush;
	INVENINFO toolInvenInfo[12][10];
	
	bool selectObjInven[7];
	//BeltInfo beltinfo;
	//INVENINFO fastinveninfo[10];

	Image* craftBtImg[4];
	int craftBtIndex;
	int craftBtState[4];
	RECT craftBtRc[4];

	CraftItemInfo* craftItemInfo[4][6][6];
	RECT craftItemRc[6][6];

public:

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void ToolInvenInit();
	void ToolInvenRelease();
	void ToolInvenUpdate();
	void ToolInvenRender(HDC hdc);

	void CraftInvenInit();
	void CraftInvenRelease();
	void CraftInvenUpdate();
	void CraftInvenRender(HDC hdc);

	void ObjectRender(HDC hdc);


	Inventory();
	~Inventory();
};

