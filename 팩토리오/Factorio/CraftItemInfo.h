#pragma once
#include "pch.h"
#include "SingletonBase.h"

#define INFO_WIDTH 150

struct ITEM_MAKE_INFO
{
	Layer name;
	float time;
	Image* img;
	int makeNum;
	bool isUsed;
};


class CraftWaitingQueue : public SingletonBase<CraftWaitingQueue>
{
private:
	queue<ITEM_MAKE_INFO> craftWaitingQueue;
	vector<Layer> vecItemNameAtQueue;

	float productTime;

	char strText[256];

	Image* orangeBox;

public:
	void PushBackQueue(ITEM_MAKE_INFO watingItem);
	void Update();
	void Render(HDC hdc);

	bool PushItemName(Layer name);
	bool PopItemName(Layer name);

	vector<Layer>* GetVecItemNameAtQueue() { return &vecItemNameAtQueue; }
	CraftWaitingQueue()
	{
		productTime = 0.0f;
		orangeBox = ImageManager::GetSingleton()->FindImage("orangeBox");

		vecItemNameAtQueue.reserve(50);
	}
	~CraftWaitingQueue() {}
};


/*************************************************************************************************/
class CraftItemInfo;

struct SOURCE
{
	Layer sourceName;
	CraftItemInfo* pSource;
	int demendNum;
	int productNum;
};

class CraftSimulation : public SingletonBase<CraftSimulation>
{
private:
	INVENINFO simulationInveninfo[8][10];
	vector<Layer>* vecItemNameAtQueue;

public:
	void CopyInventory();
	bool UseOneItem(SOURCE* _sourceInfo);
};

/*************************************************************************************************/

class CraftItemInfo
{
protected:
	ITEM_MAKE_INFO info;

	Image* img;

	POINT room;
	RECT rc;

	int canProductNum;

	Image* grayBox;
	Image* clockIcon;
	char strText[256];

	// 시뮬레이션
	int sourceKindNum;
	SOURCE sourceInfo[10];

public:
	virtual void ProductItem();
	virtual void CheckProduct();
	virtual void Render(HDC hdc);
	virtual void InfoRender(HDC hdc) = 0;
	virtual bool SimulMakeOneProduct();

	virtual void SetIsUsed(bool _isUsed) { info.isUsed = _isUsed; }
	virtual void SetMakeNum(bool _makeNum) { info.makeNum = _makeNum; }

	CraftItemInfo();

	virtual ~CraftItemInfo() {};
};


class SteelChestCraft : public CraftItemInfo
{
private:
	Image* sourceIcon;

public:
	virtual void InfoRender(HDC hdc);

	SteelChestCraft(POINT _room);
	virtual ~SteelChestCraft() {};
};

class IronStickCraft : public CraftItemInfo
{
private:
	Image* sourceIcon;

public:
	virtual void InfoRender(HDC hdc);

	IronStickCraft(POINT _room);
	virtual ~IronStickCraft() {};
};

class IronGearWheelCraft : public CraftItemInfo
{
private:
	Image* sourceIcon;

public:
	virtual void InfoRender(HDC hdc);

	IronGearWheelCraft(POINT _room);
	virtual ~IronGearWheelCraft() {};
};

class CopperCableCraft : public CraftItemInfo
{
private:
	Image* sourceIcon;

public:
	virtual void InfoRender(HDC hdc);

	CopperCableCraft(POINT _room);
	virtual ~CopperCableCraft() {};
};

class IronAxeCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[2];

public:
	virtual void InfoRender(HDC hdc);

	IronAxeCraft(POINT _room, CraftItemInfo* _middleProduct);
	virtual ~IronAxeCraft() {};
};

class BasicTransportBeltCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[2];

public:
	virtual void InfoRender(HDC hdc);

	BasicTransportBeltCraft(POINT _room, CraftItemInfo* _middleProduct);
	virtual ~BasicTransportBeltCraft() {};
};

class StoneFurnaceCraft : public CraftItemInfo
{
private:
	Image* sourceIcon;

public:
	virtual void InfoRender(HDC hdc);

	StoneFurnaceCraft(POINT _room);
	virtual ~StoneFurnaceCraft() {};
};

class WoodCraft : public CraftItemInfo
{
private:
	Image* sourceIcon;

public:
	virtual void InfoRender(HDC hdc);

	WoodCraft(POINT _room);
	virtual ~WoodCraft() {};
};

class WoodenChestCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[2];

public:
	virtual void InfoRender(HDC hdc);

	WoodenChestCraft(POINT _room, CraftItemInfo* _middleProduct);
	virtual ~WoodenChestCraft() {};
};

class BurnerInserterCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[2];

public:
	virtual void InfoRender(HDC hdc);

	BurnerInserterCraft(POINT _room, CraftItemInfo* _middleProduct);
	virtual ~BurnerInserterCraft() {};
};


class ElectronicCircuitCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[3];

public:
	virtual void InfoRender(HDC hdc);

	ElectronicCircuitCraft(POINT _room, CraftItemInfo* _middleProduct);
	virtual ~ElectronicCircuitCraft() {};
};

class BurnerMiningDrillCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[4];

public:
	virtual void InfoRender(HDC hdc);

	BurnerMiningDrillCraft(POINT _room, CraftItemInfo* _middleProduct1, CraftItemInfo* _middleProduct2);
	virtual ~BurnerMiningDrillCraft() {};
};

class SmallElectricPoleCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[4];

public:
	virtual void InfoRender(HDC hdc);

	SmallElectricPoleCraft(POINT _room, CraftItemInfo* _middleProduct1, CraftItemInfo* _middleProduct2);
	virtual ~SmallElectricPoleCraft() {};
};

/*****************/


class BasicInserterCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[4];

public:
	virtual void InfoRender(HDC hdc);

	BasicInserterCraft(POINT _room, CraftItemInfo* _middleProduct1, CraftItemInfo* _middleProduct2);
	virtual ~BasicInserterCraft() {};
};

class BasicMiningDrillCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[4];

public:
	virtual void InfoRender(HDC hdc);

	BasicMiningDrillCraft(POINT _room, CraftItemInfo* _middleProduct1, CraftItemInfo* _middleProduct2);
	virtual ~BasicMiningDrillCraft() {};
};

class ElectricFurnaceCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[4];

public:
	virtual void InfoRender(HDC hdc);

	ElectricFurnaceCraft(POINT _room, CraftItemInfo* _middleProduct , CraftItemInfo* _middleProduct2);
	virtual ~ElectricFurnaceCraft() {};
};


/**증기기관***************/

class SteamEngineCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[4];

public:
	virtual void InfoRender(HDC hdc);

	SteamEngineCraft(POINT _room, CraftItemInfo* _middleProduct1, CraftItemInfo* _middleProduct2);
	virtual ~SteamEngineCraft() {};
};

// 생산 설비
class AssemblingMachineCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[4];

public:
	virtual void InfoRender(HDC hdc);

	AssemblingMachineCraft(POINT _room, CraftItemInfo* _middleProduct1, CraftItemInfo* _middleProduct2);
	virtual ~AssemblingMachineCraft() {};
};

// 분배기
class BasicSplitterCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[4];

public:
	virtual void InfoRender(HDC hdc);

	BasicSplitterCraft(POINT _room, CraftItemInfo* _middleProduct1, CraftItemInfo* _middleProduct2);
	virtual ~BasicSplitterCraft() {};
};

// 긴팔 투입기
class LongHandedInserterCraft : public CraftItemInfo
{
private:
	Image* sourceIcon[4];

public:
	virtual void InfoRender(HDC hdc);

	LongHandedInserterCraft(POINT _room, CraftItemInfo* _middleProduct1, CraftItemInfo* _middleProduct2);
	virtual ~LongHandedInserterCraft() {};
};