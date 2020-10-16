#pragma once
#include "SingletonBase.h"
#include "pch.h"


class ObjectManager : public SingletonBase<ObjectManager>
{
	/*map<Layer, map<TILE_POINT, TileResource*>> mTileResourceContainer;
	typedef map<Layer, map<TILE_POINT, TileResource*>>::iterator TileContainerIterartor;*/

	map<Layer, map<TILE_POINT, GameNode*>> mObjectContainer;
	map<Layer, queue<GameNode*>>mObjectPool;
	map<Layer, map<TILE_POINT, GameNode*>>::iterator iter;
	map<TILE_POINT, GameNode*>::iterator it;

	vector<GameNode*> vecGameNode;

	queue<GameNode*> coal;
	queue<GameNode*> iron;
	queue<GameNode*> copper;
	queue<GameNode*> stone;
	queue<GameNode*> ironPlate;
	queue<GameNode*> copperPlate;
	queue<GameNode*> copperCable;
	queue<GameNode*> electronicCircuit;
	queue<GameNode*> advancedCircuit;
	queue<GameNode*> ironGearWheel;


	//map<Layer, vector<class GameNode*>> mObjectContainer;
	//typedef map<Layer, vector<class GameNode*>>::iterator ContainerIterartor;


public:
	void Init();
	void Release();
	void Update();
	void Render();

	GameNode* FindGameObject(Layer layer, TILE_POINT point);
	map<TILE_POINT, GameNode*> FindGameObjects(Layer layer, string name);
	const map<TILE_POINT, GameNode*>* GetObjectList(Layer layer);
	void InsertMap(Layer layer, map<TILE_POINT, GameNode*> map);
	map<TILE_POINT, GameNode*>* FindObjectMap(Layer layer);
	map<Layer, map<TILE_POINT, GameNode*>>* FindAllObject();
	void InsertVec(GameNode* gamenode);
	queue<GameNode*>* FindObjectPool(Layer prlayer);
	vector<GameNode*>* FindObjectVec();
};
