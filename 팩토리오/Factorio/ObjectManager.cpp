#include "ObjectManager.h"
#include "GameNode.h"
#include "ProductCoal.h"
#include "ProductCopper.h"
#include "ProductIron.h"
#include "ProductIronPlate.h"
#include "ProductCopperPlate.h"
#include "ElectricCircuit.h"
#include "AdvancedCircuit.h"
#include "CopperCable.h"
#include "IronGearWheel.h"
#include "ProductStone.h"

void ObjectManager::Init()
{
	for (int i = 0; i < 4000; i++)
	{
		coal.push(new ProductCoal());
	}

	mObjectPool.insert(make_pair(COAL, coal));


	for (int i = 0; i < 4000; i++)
	{
		iron.push(new ProductIron());
	}

	mObjectPool.insert(make_pair(IRON, iron));

	for (int i = 0; i < 4000; i++)
	{
		copper.push(new ProductCopper());
	}

	mObjectPool.insert(make_pair(COPPER, copper));

	for (int i = 0; i < 4000; i++)
	{
		ironPlate.push(new ProductIronPlate());
	}

	mObjectPool.insert(make_pair(IRONPLATE, ironPlate));

	for (int i = 0; i < 4000; i++)
	{
		copperPlate.push(new ProductCopperPlate());
	}

	mObjectPool.insert(make_pair(COPPERPLATE, copperPlate));

	for (int i = 0; i < 4000; i++)
	{
		electronicCircuit.push(new ElectricCircuit());
	}

	mObjectPool.insert(make_pair(ELECTRONICCIRCUIT, electronicCircuit));

	for (int i = 0; i < 4000; i++)
	{
		advancedCircuit.push(new AdvancedCircuit());
	}

	mObjectPool.insert(make_pair(ADVANCEDCIRCUIT, advancedCircuit));

	for (int i = 0; i < 4000; i++)
	{
		copperCable.push(new CopperCable());
	}

	mObjectPool.insert(make_pair(COPPERCABLE, copperCable));

	for (int i = 0; i < 4000; i++)
	{
		ironGearWheel.push(new IronGearWheel());
	}

	mObjectPool.insert(make_pair(IRONGEARWHEEL, ironGearWheel));

	for (int i = 0; i < 4000; i++)
	{
		stone.push(new ProductStone());
	}

	mObjectPool.insert(make_pair(STONE, stone));


}

void ObjectManager::Release()
{
	map<TILE_POINT, GameNode*> tempmap;
	TILE_POINT tp;
	TILE_POINT temp;
	POINT tempindex;
	int tempdirection;
	for (iter = mObjectContainer.begin(); iter != mObjectContainer.end(); iter++)
	{
		//tempmap = iter->second;
		for (it = iter->second.begin(); it != iter->second.end(); it++)
		{
			if (iter->first == STONEFURNACE)
			{
				tp = it->second->GetTilePoint();
				delete(it->second);

				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						temp = { tp.x - i, tp.y - j };
						iter->second.erase(temp);

					}
				}
				it = iter->second.begin();
				if (iter->second.size() == 0)
					break;
			}

			if (iter->first == BASICTRANSPORTBELT)
			{
				SAFE_DELETE(it->second);
			}

			// 추가한곳 //
			else if (iter->first == BURNERINSERTER)
			{
				SAFE_DELETE(it->second);
			}

			if (iter->first == BURNERMININGDRILL)
			{
				tp = it->second->GetTilePoint();
				delete(it->second);

				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 2; j++)
					{
						temp = { tp.x - i, tp.y - j };
						iter->second.erase(temp);

					}
				}
				it = iter->second.begin();
				if (iter->second.size() == 0)
					break;
			}

			else if (iter->first == TREE)
			{
				SAFE_DELETE(it->second);
				it++;
			}

			else if (iter->first == COAL)
			{
				SAFE_DELETE(it->second);

			}

			else if (iter->first == IRON)
			{
				SAFE_DELETE(it->second);

			}

			else if (iter->first == COPPER)
			{
				SAFE_DELETE(it->second);

			}

			else if (iter->first == ROCKET)
			{
				tp = it->second->GetTilePoint();
				delete(it->second);

				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						temp = { tp.x - i, tp.y - j };
						iter->second.erase(temp);

					}
				}
				it = iter->second.begin();
				if (iter->second.size() == 0)
					break;

			}



			else if (iter->first == SMALLELECTRICPOLE)
			{
				SAFE_DELETE(it->second);

			}

			else if (iter->first == STEAMENGINE)
			{
				tempdirection = it->second->GetDirection();
				tp = it->second->GetTilePoint();

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

				delete(it->second);

				for (int i = 0; i < tempindex.x; i++)
				{
					for (int j = 0; j < tempindex.y; j++)
					{
						temp = { tp.x - i, tp.y - j };
						iter->second.erase(temp);

					}
				}

				it = iter->second.begin();
				if (iter->second.size() == 0)
					break;

			}

			if (iter->first == BASICMININGDRILL)
			{
				tp = it->second->GetTilePoint();
				delete(it->second);

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						temp = { tp.x - i, tp.y - j };
						iter->second.erase(temp);

					}
				}
				it = iter->second.begin();
				if (iter->second.size() == 0)
					break;
			}

			if (iter->first == ELECTRICFURNACE)
			{
				tp = it->second->GetTilePoint();
				delete(it->second);

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						temp = { tp.x - i, tp.y - j };
						iter->second.erase(temp);

					}
				}
				it = iter->second.begin();
				if (iter->second.size() == 0)
					break;
			}

			else if (iter->first == BASICINSERTER)
			{
				SAFE_DELETE(it->second);
			}

			else if (iter->first == WOODENCHEST)
			{
				SAFE_DELETE(it->second);
			}

			else if (iter->first == STEELCHEST)
			{
				SAFE_DELETE(it->second);
			}

			else if (iter->first == ASSEMBLINGMACHINE)
			{
				tp = it->second->GetTilePoint();
				delete(it->second);

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						temp = { tp.x - i, tp.y - j };
						iter->second.erase(temp);

					}
				}
				it = iter->second.begin();
				if (iter->second.size() == 0)
					break;
			}

			else if (iter->first == BASICSPLITTER)
			{
				tempdirection = it->second->GetDirection();
				tp = it->second->GetTilePoint();

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

				delete(it->second);

				for (int i = 0; i < tempindex.x; i++)
				{
					for (int j = 0; j < tempindex.y; j++)
					{
						temp = { tp.x - i, tp.y - j };
						iter->second.erase(temp);

					}
				}

				it = iter->second.begin();
				if (iter->second.size() == 0)
					break;

			}

			else if (iter->first == LONGHANDEDINSERTER)
			{
				SAFE_DELETE(it->second);
			}

		}


		iter->second.clear();
	}

	while (coal.size() != 0)
	{
		SAFE_DELETE(coal.front());
		coal.pop();
	}

	while (iron.size() != 0)
	{
		SAFE_DELETE(iron.front());
		iron.pop();
	}

	while (copper.size() != 0)
	{
		SAFE_DELETE(copper.front());
		copper.pop();
	}

	while (ironPlate.size() != 0)
	{
		SAFE_DELETE(ironPlate.front());
		ironPlate.pop();
	}

	while (copperPlate.size() != 0)
	{
		SAFE_DELETE(copperPlate.front());
		copperPlate.pop();
	}

	while (electronicCircuit.size() != 0)
	{
		SAFE_DELETE(electronicCircuit.front());
		electronicCircuit.pop();
	}

	while (advancedCircuit.size() != 0)
	{
		SAFE_DELETE(advancedCircuit.front());
		advancedCircuit.pop();
	}

	while (copperCable.size() != 0)
	{
		SAFE_DELETE(copperCable.front());
		copperCable.pop();
	}

	while (stone.size() != 0)
	{
		SAFE_DELETE(stone.front());
		stone.pop();
	}

	for (int i = 0; i > vecGameNode.size(); i++)
	{
		SAFE_DELETE(vecGameNode[i]);
	}
	vecGameNode.clear();
	mObjectContainer.clear();
}

void ObjectManager::Update()
{
}

void ObjectManager::Render()
{
}

GameNode * ObjectManager::FindGameObject(Layer layer, TILE_POINT point)
{
	return mObjectContainer.find(layer)->second.find(point)->second;
}

map<TILE_POINT, GameNode*> ObjectManager::FindGameObjects(Layer layer, string name)
{
	return mObjectContainer.find(layer)->second;
}

const map<TILE_POINT, GameNode*>* ObjectManager::GetObjectList(Layer layer)
{
	return &mObjectContainer.find(layer)->second;
}

void ObjectManager::InsertMap(Layer layer, map<TILE_POINT, GameNode*> map)
{
	mObjectContainer.insert(make_pair(layer, map));
}

map<TILE_POINT, GameNode*>* ObjectManager::FindObjectMap(Layer layer)
{
	return &mObjectContainer.find(layer)->second;
}

map<Layer, map<TILE_POINT, GameNode*>>* ObjectManager::FindAllObject()
{
	return &mObjectContainer;
}

void ObjectManager::InsertVec(GameNode * gamenode)
{
	vecGameNode.push_back(gamenode);
}

queue<GameNode*>* ObjectManager::FindObjectPool(Layer prlayer)
{
	return &mObjectPool.find(prlayer)->second;
}

vector<GameNode*>* ObjectManager::FindObjectVec()
{
	return &vecGameNode;
}
