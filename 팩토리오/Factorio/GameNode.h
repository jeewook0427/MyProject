#pragma once
#include "pch.h"

class Image;
class Animation;
class GameNode
{
protected:

	vector<GameNode*>::iterator vecit;
	map<TILE_POINT, GameNode*>::iterator it2;
	map<Layer, map<TILE_POINT, GameNode*> >::iterator iter;

	map<TILE_POINT, GameNode*>::iterator it;

	INVENINFO storage[10];

	Animation* ani;
	//이미지
	Image* image;
	Image* selectBox;
	Image* invenImage;
	Image* effectimg;
	Image* warning;

	TILE_POINT tp;
	POINT frame;
	FPOINT pos;
	RECT rect;
	Layer layer;

	int direction;
	int Hp;
	int renderCount;
	int updateCount;
	int releaseCount;
	int elecNum;
	int alpha;

	float deleteTime;
	float fuelGage;
	float materialGage;
	float scale;

	bool isSelected;
	bool isSelectedClose;
	bool checkRender;
	bool isRectRender;
	bool isDelete;
	//bool isInvenOpen;

	//추가
	bool isFuelFilled;
	bool isMaterialFilled;
	bool isWidthReverse;
	bool isHeightReverse;
	bool isPicked;
	bool isElec;
	bool checkAlpha;
	bool soundPlay;
	bool isPlay;
	

	INVENINFO fuel;
	INVENINFO material;
	INVENINFO product;
	INVENINFO assemMaterial[2];
	INVENINFO rocketMaterial[3];

	GameNode* steam;


public:
	virtual HRESULT Init();
	virtual HRESULT Init(int x, int y);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void RocketRender(HDC hdc);

	virtual void SelectBoxRender(HDC hdc);
	virtual void SetIsSelected(bool _isselected) { isSelected = _isselected; }
	virtual void SetIsSelectedClose(bool _isselectedclose) { isSelectedClose = _isselectedclose; }

	Layer GetLayer() { return layer; }
	RECT GetRect() { return rect; }
	FPOINT GetPos() { return pos; }
	void SetPos(FPOINT _pos) { pos = _pos; }
	void SetHp(int hp) { Hp = hp; }
	void MinusHp() { Hp--; }
	void SetIsPicked(bool ispicked) { isPicked = ispicked; }
	void SetLayer(Layer _layer) { layer = _layer; }
	void SetSoundPlay(bool soundplay) { soundPlay = soundplay; }

	bool GetSelectedClose() { return isSelectedClose; }
	bool GetIsPicked() { return isPicked; }
	bool GetIsElec() { return isElec; }
	bool GetisFuelFilled(){ return isFuelFilled; }
	bool GetisMaterialFilled() { return isMaterialFilled; }
	bool GetCheckRender() { return checkRender; }
	bool GetSoundPlay() { return soundPlay; }
	

	int GetHp() { return Hp; }
	int GetDirection() { return direction; }
	int GetElecNum() { return elecNum; }
	void SetDirection(int _direction) { direction = _direction; }
	void SetSteam(GameNode* _steam) { steam = _steam; }

	TILE_POINT GetTilePoint() { return tp; }
	bool GetIsDelete() { return isDelete; }
	float GetFuelGage() { return fuelGage; }
	float GetMaterialGage() { return materialGage; }

	INVENINFO* GetFuel() { return &fuel; }
	INVENINFO* GetMeterial() { return &material; }
	INVENINFO* GetProduct() { return &product; }
	INVENINFO* GetBoxInfo() { return storage; }
	INVENINFO* GetAssemMeterial() { return assemMaterial; }
	INVENINFO* GetRocketMaterial() { return rocketMaterial; }
	GameNode* GetSteamEngine() { return steam; }

	virtual void InfoRender(HDC hdc) {}

	GameNode();
	virtual ~GameNode();
};

