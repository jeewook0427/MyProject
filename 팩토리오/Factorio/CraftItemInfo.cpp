#include "CraftItemInfo.h"
#include "Image.h"


void CraftWaitingQueue::PushBackQueue(ITEM_MAKE_INFO watingItem)
{
	craftWaitingQueue.push(watingItem);
	if (!watingItem.isUsed)
	{
		for (int i = 0; i < watingItem.makeNum; ++i)
		{
			PushItemName(watingItem.name);
		}
	}

	if (craftWaitingQueue.size() == 1)
		productTime = craftWaitingQueue.front().time;

	Tutorial::GetSingleton()->SucceedQuest_3();
}

void CraftWaitingQueue::Update()
{
	if (!craftWaitingQueue.empty())
	{
		productTime -= 1.0f / FPS;

		if (productTime <= 0.0f)
		{
			if (craftWaitingQueue.front().isUsed)
			{
				craftWaitingQueue.pop();
				return;
			}
			else
			{
				for (int i = 0; i < 8; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						if (inveninfo[i][j].name == craftWaitingQueue.front().name)
						{
							inveninfo[i][j].num += craftWaitingQueue.front().makeNum;

							for (int i = 0; i < craftWaitingQueue.front().makeNum; ++i)
							{
								PopItemName(craftWaitingQueue.front().name);
							}

							craftWaitingQueue.pop();
							if (!craftWaitingQueue.empty())
								productTime = craftWaitingQueue.front().time;
							return;
						}
					}
				}

				for (int i = 0; i < 8; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						if (inveninfo[i][j].name == EMPTY)
						{
							inveninfo[i][j].isStorage = true;
							inveninfo[i][j].name = craftWaitingQueue.front().name;
							inveninfo[i][j].num = craftWaitingQueue.front().makeNum;
							PopItemName(craftWaitingQueue.front().name);
							craftWaitingQueue.pop();
							if (!craftWaitingQueue.empty())
								productTime = craftWaitingQueue.front().time;
							return;
						}
					}
				}
			}
		}
	}

}

void CraftWaitingQueue::Render(HDC hdc)
{
	if (!craftWaitingQueue.empty())
	{
		Rectangle(hdc, 50, WINSIZE_Y - 50, 91, WINSIZE_Y - 9);

		craftWaitingQueue.front().img->Render(hdc, 70, WINSIZE_Y - 30);

		orangeBox->AlphaRender(hdc, 50, WINSIZE_Y - 50, 41, (int)(41.0f * productTime / craftWaitingQueue.front().time), 150);

		sprintf_s(strText, "남은 시간 : %.2f 초", productTime);
		TextOut(hdc, 100, WINSIZE_Y - 50, strText, strlen(strText));

		sprintf_s(strText, "생산 대기 : %d 개", craftWaitingQueue.size());
		TextOut(hdc, 100, WINSIZE_Y - 30, strText, strlen(strText));
	}
}

bool CraftWaitingQueue::PushItemName(Layer name)
{
	for (int i = 0; i < vecItemNameAtQueue.size(); ++i)
	{
		if (vecItemNameAtQueue[i] == EMPTY)
		{
			vecItemNameAtQueue[i] = name;
			return true;
		}
	}

	vecItemNameAtQueue.push_back(name);
	return true;

}

bool CraftWaitingQueue::PopItemName(Layer name)
{
	for (int i = 0; i < vecItemNameAtQueue.size(); ++i)
	{
		if (vecItemNameAtQueue[i] == name)
		{
			vecItemNameAtQueue[i] = EMPTY;
			return true;
		}
	}
}

/*************************************************************************************************/

void CraftSimulation::CopyInventory()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			simulationInveninfo[i][j] = inveninfo[i][j];
		}
	}

	vecItemNameAtQueue = CraftWaitingQueue::GetSingleton()->GetVecItemNameAtQueue();
	bool isBreak;

	for (int k = 0; k < vecItemNameAtQueue->size(); ++k)
	{
		isBreak = false;

		for (int i = 0; i < 8; ++i)
		{
			if (isBreak)
				break;

			for (int j = 0; j < 10; ++j)
			{
				if (simulationInveninfo[i][j].name == (*vecItemNameAtQueue)[k])
				{
					simulationInveninfo[i][j].num++;
					isBreak = true;
					break;
				}
			}

		}
		if (isBreak)
			continue;

		for (int i = 0; i < 8; ++i)
		{
			if (isBreak)
				break;

			for (int j = 0; j < 10; ++j)
			{
				if (simulationInveninfo[i][j].name == EMPTY)
				{
					simulationInveninfo[i][j].isStorage = true;
					simulationInveninfo[i][j].name = (*vecItemNameAtQueue)[k];
					simulationInveninfo[i][j].num = 1;
					isBreak = true;
					break;
				}
			}

		}
	}
}

// 필요한 재료 중 한가지 재료를 시뮬레이션인벤에서 사용(만들 수 있으면 만들어서 사용)
bool CraftSimulation::UseOneItem(SOURCE* _sourceInfo)
{
	int demendNum = _sourceInfo->demendNum;
	// 있는 재료 사용
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (simulationInveninfo[i][j].name == _sourceInfo->sourceName)
			{
				if (simulationInveninfo[i][j].num >= demendNum)
				{
					simulationInveninfo[i][j].num -= demendNum;
					demendNum = 0;

					if (simulationInveninfo[i][j].num == 0)
					{
						simulationInveninfo[i][j].isStorage = false;
						simulationInveninfo[i][j].name = EMPTY;
					}

					return true;
				}

				else
				{
					demendNum -= simulationInveninfo[i][j].num;
					simulationInveninfo[i][j].num = 0;
					simulationInveninfo[i][j].isStorage = false;
					simulationInveninfo[i][j].name = EMPTY;
				}
			}
		}
	}

	// 지금은 없지만 생산할 수 있는 종류일 때 
	if (_sourceInfo->pSource)
	{
		if (_sourceInfo->productNum == 1)
		{
			for (int i = 0; i < demendNum; ++i)
			{
				if (_sourceInfo->pSource->SimulMakeOneProduct()) {}

				else
					return false;
			}

			return true;
		}
		else if (_sourceInfo->productNum > 1)
		{
			for (int i = 0; i < (demendNum - 1) / _sourceInfo->productNum + 1; ++i)
			{
				if (_sourceInfo->pSource->SimulMakeOneProduct()) {}

				else
					return false;
			}

			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					if (simulationInveninfo[i][j].name == _sourceInfo->sourceName)
					{
						simulationInveninfo[i][j].num += (demendNum % _sourceInfo->productNum);
						return true;
					}
				}
			}

			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					if (simulationInveninfo[i][j].name == EMPTY)
					{
						simulationInveninfo[i][j].name = _sourceInfo->sourceName;
						simulationInveninfo[i][j].isStorage = true;
						simulationInveninfo[i][j].num += (demendNum % _sourceInfo->productNum);
						return true;
					}
				}
			}
		}
	}
	// 생산할 수 있는 종류가 아닐때
	else
	{
		return false;
	}
}


/*************************************************************************************************/

void CraftItemInfo::ProductItem()
{
	if (canProductNum > 0)
	{
		int demendSourceNum[10] = { 0, };
		bool isBreak;

		for (int k = 0; k < sourceKindNum; ++k)
		{
			demendSourceNum[k] = sourceInfo[k].demendNum;
		}


		for (int k = 0; k < sourceKindNum; ++k)
		{
			isBreak = false;

			for (int i = 0; i < 8; ++i)
			{
				if (isBreak)
					break;

				for (int j = 0; j < 10; ++j)
				{
					if (inveninfo[i][j].name == sourceInfo[k].sourceName)
					{
						if (inveninfo[i][j].num >= demendSourceNum[k])
						{
							inveninfo[i][j].num -= demendSourceNum[k];
							demendSourceNum[k] = 0;
							if (inveninfo[i][j].num <= 0)
							{
								inveninfo[i][j].isStorage = false;
								inveninfo[i][j].name = EMPTY;
							}

							isBreak = true;
							break;
						}

						else
						{
							demendSourceNum[k] -= inveninfo[i][j].num;
							inveninfo[i][j].num = 0;
							inveninfo[i][j].isStorage = false;
							inveninfo[i][j].name = EMPTY;
						}
					}
				}

			}
		}

		for (int k = 0; k < sourceKindNum; ++k)
		{
			if (demendSourceNum[k] > 0)
			{

				if (sourceInfo[k].productNum == 1)
				{
					sourceInfo[k].pSource->SetIsUsed(true);

					for (int i = 0; i < demendSourceNum[k]; ++i)
					{
						sourceInfo[k].pSource->ProductItem();
					}

					sourceInfo[k].pSource->SetIsUsed(false);
				}

				else if (demendSourceNum[k] % sourceInfo[k].productNum == 0)
				{
					sourceInfo[k].pSource->SetIsUsed(true);

					for (int i = 0; i < demendSourceNum[k] / sourceInfo[k].productNum; ++i)
					{
						sourceInfo[k].pSource->ProductItem();
					}

					sourceInfo[k].pSource->SetIsUsed(false);
				}

				else
				{
					sourceInfo[k].pSource->SetIsUsed(true);

					for (int i = 0; i < demendSourceNum[k] / sourceInfo[k].productNum; ++i)
					{
						sourceInfo[k].pSource->ProductItem();
					}

					sourceInfo[k].pSource->SetIsUsed(false);

					// 생산량중 일부만 필요한거
					sourceInfo[k].pSource->SetMakeNum(demendSourceNum[k] % sourceInfo[k].productNum);
					sourceInfo[k].pSource->ProductItem();
					sourceInfo[k].pSource->SetMakeNum(sourceInfo[k].productNum);
				}
			}
		}

		CraftWaitingQueue::GetSingleton()->PushBackQueue(info);
	}
}

void CraftItemInfo::CheckProduct()
{
	CraftSimulation::GetSingleton()->CopyInventory();

	canProductNum = 0;
	while (true)
	{
		if (SimulMakeOneProduct())
		{
			canProductNum++;
			if (canProductNum > 999)
				break;
		}
		else
			break;
	}
}

void CraftItemInfo::Render(HDC hdc)
{
	img->Render(hdc, rc.left + 19, rc.top + 19);

	sprintf_s(strText, "%d", canProductNum);
	TextOut(hdc, rc.left, rc.top, strText, strlen(strText));
}

bool CraftItemInfo::SimulMakeOneProduct()
{
	for (int i = 0; i < sourceKindNum; ++i)
	{
		if (CraftSimulation::GetSingleton()->UseOneItem(&sourceInfo[i])) {}
		else
			return false;
	}
	return true;
}

CraftItemInfo::CraftItemInfo()
{
	grayBox = ImageManager::GetSingleton()->FindImage("grayBox");
	clockIcon = ImageManager::GetSingleton()->FindImage("clock-icon");
};

/*****************/

void SteelChestCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH, INFO_WIDTH + 30, 200);

	wsprintf(strText, "철 상자");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "8 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	wsprintf(strText, "최대 체력: 100");
	TextOut(hdc, rc.left + 30, rc.top + 141, strText, strlen(strText));
	wsprintf(strText, "저장 용량: 32");
	TextOut(hdc, rc.left + 30, rc.top + 166, strText, strlen(strText));
}

SteelChestCraft::SteelChestCraft(POINT _room)
{
	img = ImageManager::GetSingleton()->FindImage("steel-chest-icon");
	info = { STEELCHEST, 0.5f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon = ImageManager::GetSingleton()->FindImage("iron-plate-icon");

	// source정보
	sourceKindNum = 1;
	sourceInfo[0] = { IRONPLATE, nullptr, 8, 0 };
}


/*****************/

void IronStickCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH, INFO_WIDTH - 30, 200);

	wsprintf(strText, "2 x 철 막대기");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "1 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));
}

IronStickCraft::IronStickCraft(POINT _room)
{
	img = ImageManager::GetSingleton()->FindImage("iron-stick-icon");
	info = { IRONSTICK, 0.5f, img, 2, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon = ImageManager::GetSingleton()->FindImage("iron-plate-icon");

	// source정보
	sourceKindNum = 1;
	sourceInfo[0] = { IRONPLATE, nullptr, 1, 0 };
}

/*****************/

void IronGearWheelCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH, INFO_WIDTH - 30, 200);

	wsprintf(strText, "철 기어 휠");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "2 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));
}

IronGearWheelCraft::IronGearWheelCraft(POINT _room)
{
	img = ImageManager::GetSingleton()->FindImage("iron-gear-wheel-icon");
	info = { IRONGEARWHEEL, 0.5f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon = ImageManager::GetSingleton()->FindImage("iron-plate-icon");

	// source정보
	sourceKindNum = 1;
	sourceInfo[0] = { IRONPLATE, nullptr, 2, 0 };
}

/*****************/
void CopperCableCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH, INFO_WIDTH - 30, 200);

	wsprintf(strText, "2 x 구리 전선");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "2 x 구리 판");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));
}

CopperCableCraft::CopperCableCraft(POINT _room)
{
	img = ImageManager::GetSingleton()->FindImage("copper-cable-icon");
	info = { COPPERCABLE, 0.5f, img, 2, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };


	// 인포렌더 정보
	sourceIcon = ImageManager::GetSingleton()->FindImage("copper-plate-icon");

	// source정보
	sourceKindNum = 1;
	sourceInfo[0] = { COPPERPLATE, nullptr, 2, 0 };
}

/*****************/

void IronAxeCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH, INFO_WIDTH + 130, 200);

	wsprintf(strText, "철 도끼");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "2 x 철 막대기");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "3 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	wsprintf(strText, "채광 강도: 2.5");
	TextOut(hdc, rc.left + 30, rc.top + 178, strText, strlen(strText));
	wsprintf(strText, "데미지: 5 물리 피해");
	TextOut(hdc, rc.left + 30, rc.top + 203, strText, strlen(strText));
	wsprintf(strText, "내구력: 4000");
	TextOut(hdc, rc.left + 30, rc.top + 228, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 260, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 250, rc.left + 124, rc.top + 284);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 267);
	wsprintf(strText, "1");
	TextOut(hdc, rc.left + 114, rc.top + 268, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 250, rc.left + 163, rc.top + 284);
	sourceIcon[1]->Render(hdc, rc.left + 146, rc.top + 267);
	wsprintf(strText, "4");
	TextOut(hdc, rc.left + 153, rc.top + 268, strText, strlen(strText));
}


IronAxeCraft::IronAxeCraft(POINT _room, CraftItemInfo * _middleProduct)
{
	img = ImageManager::GetSingleton()->FindImage("iron-axe-icon");
	info = { IRONAXE, 0.5f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };


	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("iron-stick-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");

	// source정보
	sourceKindNum = 2;
	sourceInfo[0] = { IRONSTICK, _middleProduct, 2, 2 };
	sourceInfo[1] = { IRONPLATE, nullptr, 1, 0 };
}

/*****************/

void BasicTransportBeltCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH, INFO_WIDTH + 80, 200);

	wsprintf(strText, "2 x 운송밸트");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "1 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "1 x 철 기어 휠");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	wsprintf(strText, "최대 체력: 50");
	TextOut(hdc, rc.left + 30, rc.top + 178, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 210, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 200, rc.left + 124, rc.top + 234);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 217);
	wsprintf(strText, "1");
	TextOut(hdc, rc.left + 114, rc.top + 218, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 200, rc.left + 163, rc.top + 234);
	sourceIcon[0]->Render(hdc, rc.left + 146, rc.top + 217);
	wsprintf(strText, "3");
	TextOut(hdc, rc.left + 153, rc.top + 218, strText, strlen(strText));
}

BasicTransportBeltCraft::BasicTransportBeltCraft(POINT _room, CraftItemInfo * _middleProduct)
{
	img = ImageManager::GetSingleton()->FindImage("basic-transport-belt-icon");
	info = { BASICTRANSPORTBELT, 0.5f, img, 2, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("iron-gear-wheel-icon");

	// source정보
	sourceKindNum = 2;
	sourceInfo[0] = { IRONPLATE, nullptr, 1, 0 };
	sourceInfo[1] = { IRONGEARWHEEL, _middleProduct, 1, 1 };
}

/*****************/

void StoneFurnaceCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 20, INFO_WIDTH + 60, 200);

	wsprintf(strText, "석재 용광로");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "5 x 돌");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	wsprintf(strText, "최대 체력: 150");
	TextOut(hdc, rc.left + 30, rc.top + 141, strText, strlen(strText));
	wsprintf(strText, "에너지 소비량: 180 kW");
	TextOut(hdc, rc.left + 30, rc.top + 166, strText, strlen(strText));
	wsprintf(strText, "제작 속도: 1");
	TextOut(hdc, rc.left + 30, rc.top + 191, strText, strlen(strText));
}

StoneFurnaceCraft::StoneFurnaceCraft(POINT _room)
{
	img = ImageManager::GetSingleton()->FindImage("stone-furnace-icon");
	info = { STONEFURNACE, 0.5f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon = ImageManager::GetSingleton()->FindImage("stone-icon");

	// source정보
	sourceKindNum = 1;
	sourceInfo[0] = { STONE, nullptr, 5, 0 };
}

/*****************/

void WoodCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH, INFO_WIDTH + 10, 200);

	wsprintf(strText, "2 x 목재");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "1 x 원목");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	wsprintf(strText, "연료 량: 2.0 MJ");
	TextOut(hdc, rc.left + 30, rc.top + 141, strText, strlen(strText));

}

WoodCraft::WoodCraft(POINT _room)
{
	img = ImageManager::GetSingleton()->FindImage("wood-icon");
	info = { WOOD, 0.5f, img, 2, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon = ImageManager::GetSingleton()->FindImage("wood-icon");

	// source정보
	sourceKindNum = 1;
	sourceInfo[0] = { TREE, nullptr, 1, 0 };
}


/*****************/

void WoodenChestCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH, INFO_WIDTH + 100, 200);

	wsprintf(strText, "나무 상자");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "4 x 목재");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	wsprintf(strText, "최대 체력: 50");
	TextOut(hdc, rc.left + 30, rc.top + 141, strText, strlen(strText));
	wsprintf(strText, "저장 용량: 16");
	TextOut(hdc, rc.left + 30, rc.top + 166, strText, strlen(strText));
	wsprintf(strText, "연료량: 4.0 MJ");
	TextOut(hdc, rc.left + 30, rc.top + 191, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 223, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 213, rc.left + 124, rc.top + 247);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 230);
	wsprintf(strText, "1.5");
	TextOut(hdc, rc.left + 102, rc.top + 231, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 213, rc.left + 163, rc.top + 247);
	sourceIcon[1]->Render(hdc, rc.left + 146, rc.top + 230);
	wsprintf(strText, "2");
	TextOut(hdc, rc.left + 153, rc.top + 231, strText, strlen(strText));
}

WoodenChestCraft::WoodenChestCraft(POINT _room, CraftItemInfo * _middleProduct)
{
	img = ImageManager::GetSingleton()->FindImage("wooden-chest-icon");
	info = { WOODENCHEST, 0.5f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("wood-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("raw-wood-icon");

	// source정보
	sourceKindNum = 1;
	sourceInfo[0] = { WOOD, _middleProduct, 4, 2 };
}


/*****************/

void BurnerInserterCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 20, INFO_WIDTH + 100, 200);

	wsprintf(strText, "화력 투입기");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "1 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "1 x 철 기어 휠");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	wsprintf(strText, "최대 체력: 40");
	TextOut(hdc, rc.left + 30, rc.top + 178, strText, strlen(strText));
	wsprintf(strText, "에너지 소비량: 188 kW");
	TextOut(hdc, rc.left + 30, rc.top + 203, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 235, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 225, rc.left + 124, rc.top + 259);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 242);
	wsprintf(strText, "1");
	TextOut(hdc, rc.left + 114, rc.top + 243, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 225, rc.left + 163, rc.top + 259);
	sourceIcon[0]->Render(hdc, rc.left + 146, rc.top + 242);
	wsprintf(strText, "3");
	TextOut(hdc, rc.left + 153, rc.top + 243, strText, strlen(strText));
}

BurnerInserterCraft::BurnerInserterCraft(POINT _room, CraftItemInfo * _middleProduct)
{
	img = ImageManager::GetSingleton()->FindImage("burner-inserter-icon");
	info = { BURNERINSERTER, 0.5f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };


	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("iron-gear-wheel-icon");

	// source정보
	sourceKindNum = 2;
	sourceInfo[0] = { IRONPLATE, nullptr, 1, 0 };
	sourceInfo[1] = { IRONGEARWHEEL, _middleProduct, 1, 1 };
}

/*****************/

void ElectronicCircuitCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 40, INFO_WIDTH + 60, 200);

	wsprintf(strText, "전자 회로");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "1 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "3 x 구리 전선");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 185, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 175, rc.left + 124, rc.top + 209);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 192);
	wsprintf(strText, "1.3");
	TextOut(hdc, rc.left + 102, rc.top + 193, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 175, rc.left + 163, rc.top + 209);
	sourceIcon[0]->Render(hdc, rc.left + 146, rc.top + 192);
	wsprintf(strText, "1");
	TextOut(hdc, rc.left + 153, rc.top + 193, strText, strlen(strText));

	Rectangle(hdc, rc.left + 168, rc.top + 175, rc.left + 202, rc.top + 209);
	sourceIcon[2]->Render(hdc, rc.left + 185, rc.top + 192);
	wsprintf(strText, "1.5");
	TextOut(hdc, rc.left + 180, rc.top + 193, strText, strlen(strText));
}

ElectronicCircuitCraft::ElectronicCircuitCraft(POINT _room, CraftItemInfo * _middleProduct)
{
	img = ImageManager::GetSingleton()->FindImage("electronic-circuit-icon");
	info = { ELECTRONICCIRCUIT, 0.5f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("copper-cable-icon");
	sourceIcon[2] = ImageManager::GetSingleton()->FindImage("copper-plate-icon");

	// source정보
	sourceKindNum = 2;
	sourceInfo[0] = { IRONPLATE, nullptr, 1, 0 };
	sourceInfo[1] = { COPPERCABLE, _middleProduct, 3, 2 };
}

/*****************/

void BurnerMiningDrillCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 40, INFO_WIDTH + 220, 200);

	wsprintf(strText, "화력 채광 드릴");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "2");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "3 x 철 기어 휠");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "1 x 석재 용광로");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 171, rc.left + 64, rc.top + 205);
	sourceIcon[2]->Render(hdc, rc.left + 47, rc.top + 188);
	wsprintf(strText, "3 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 180, strText, strlen(strText));

	wsprintf(strText, "채광 강도: 2.5");
	TextOut(hdc, rc.left + 30, rc.top + 215, strText, strlen(strText));
	wsprintf(strText, "채광 속도: 0.35");
	TextOut(hdc, rc.left + 30, rc.top + 240, strText, strlen(strText));
	wsprintf(strText, "채광 영역: 2X2");
	TextOut(hdc, rc.left + 30, rc.top + 265, strText, strlen(strText));
	wsprintf(strText, "최대 체력: 100");
	TextOut(hdc, rc.left + 30, rc.top + 290, strText, strlen(strText));
	wsprintf(strText, "에너지 소비량: 300 kW");
	TextOut(hdc, rc.left + 30, rc.top + 315, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 347, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 337, rc.left + 124, rc.top + 371);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 354);
	wsprintf(strText, "4");
	TextOut(hdc, rc.left + 114, rc.top + 355, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 337, rc.left + 163, rc.top + 371);
	sourceIcon[3]->Render(hdc, rc.left + 146, rc.top + 354);
	wsprintf(strText, "5");
	TextOut(hdc, rc.left + 153, rc.top + 355, strText, strlen(strText));

	Rectangle(hdc, rc.left + 168, rc.top + 337, rc.left + 202, rc.top + 371);
	sourceIcon[2]->Render(hdc, rc.left + 185, rc.top + 354);
	wsprintf(strText, "9");
	TextOut(hdc, rc.left + 192, rc.top + 355, strText, strlen(strText));
}

BurnerMiningDrillCraft::BurnerMiningDrillCraft(POINT _room, CraftItemInfo* _middleProduct1, CraftItemInfo* _middleProduct2)
{
	img = ImageManager::GetSingleton()->FindImage("burner-mining-drill-icon");
	info = { BURNERMININGDRILL, 2.0f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("iron-gear-wheel-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("stone-furnace-icon");
	sourceIcon[2] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");
	sourceIcon[3] = ImageManager::GetSingleton()->FindImage("stone-icon");

	// source정보
	sourceKindNum = 3;
	sourceInfo[0] = { IRONGEARWHEEL, _middleProduct1, 3, 1 };
	sourceInfo[1] = { STONEFURNACE, _middleProduct2, 1, 1 };
	sourceInfo[2] = { IRONPLATE, nullptr, 3, 0 };
}

/*****************/

void SmallElectricPoleCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 40, INFO_WIDTH + 160, 200);

	wsprintf(strText, "2 x 소형 전신주");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "2 x 목재");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "2 x 구리 전선");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	wsprintf(strText, "와이어 거리: 7.5");
	TextOut(hdc, rc.left + 30, rc.top + 178, strText, strlen(strText));
	wsprintf(strText, "공급 영역: 5X5");
	TextOut(hdc, rc.left + 30, rc.top + 203, strText, strlen(strText));
	wsprintf(strText, "최대 체력: 35");
	TextOut(hdc, rc.left + 30, rc.top + 228, strText, strlen(strText));
	wsprintf(strText, "연료 량: 4.0 MJ");
	TextOut(hdc, rc.left + 30, rc.top + 253, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 285, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 275, rc.left + 124, rc.top + 309);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 292);
	wsprintf(strText, "1.5");
	TextOut(hdc, rc.left + 102, rc.top + 293, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 275, rc.left + 163, rc.top + 309);
	sourceIcon[2]->Render(hdc, rc.left + 146, rc.top + 292);
	wsprintf(strText, "1");
	TextOut(hdc, rc.left + 153, rc.top + 293, strText, strlen(strText));

	Rectangle(hdc, rc.left + 168, rc.top + 275, rc.left + 202, rc.top + 309);
	sourceIcon[3]->Render(hdc, rc.left + 185, rc.top + 292);
	wsprintf(strText, "1");
	TextOut(hdc, rc.left + 192, rc.top + 293, strText, strlen(strText));
}

SmallElectricPoleCraft::SmallElectricPoleCraft(POINT _room, CraftItemInfo * _middleProduct1, CraftItemInfo * _middleProduct2)
{
	img = ImageManager::GetSingleton()->FindImage("small-electric-pole-icon");
	info = { SMALLELECTRICPOLE, 0.5f, img, 2, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("wood-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("copper-cable-icon");
	sourceIcon[2] = ImageManager::GetSingleton()->FindImage("raw-wood-icon");
	sourceIcon[3] = ImageManager::GetSingleton()->FindImage("copper-plate-icon");

	// source정보
	sourceKindNum = 2;
	sourceInfo[0] = { WOOD, _middleProduct1, 2, 2 };
	sourceInfo[1] = { COPPERCABLE, _middleProduct2, 2, 2 };
}

/*****************/

void BasicInserterCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 40, INFO_WIDTH + 150, 200);

	wsprintf(strText, "투입기");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "1 x 전자회로");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "1 x 철 기어 휠");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 171, rc.left + 64, rc.top + 205);
	sourceIcon[2]->Render(hdc, rc.left + 47, rc.top + 188);
	wsprintf(strText, "1 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 180, strText, strlen(strText));

	wsprintf(strText, "최대 체력: 40");
	TextOut(hdc, rc.left + 30, rc.top + 215, strText, strlen(strText));
	wsprintf(strText, "에너지 소비량: 13 kW");
	TextOut(hdc, rc.left + 30, rc.top + 240, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 272, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 262, rc.left + 124, rc.top + 296);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 279);
	wsprintf(strText, "2.3");
	TextOut(hdc, rc.left + 102, rc.top + 280, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 262, rc.left + 163, rc.top + 296);
	sourceIcon[2]->Render(hdc, rc.left + 146, rc.top + 279);
	wsprintf(strText, "4");
	TextOut(hdc, rc.left + 153, rc.top + 280, strText, strlen(strText));

	Rectangle(hdc, rc.left + 168, rc.top + 262, rc.left + 202, rc.top + 296);
	sourceIcon[3]->Render(hdc, rc.left + 185, rc.top + 279);
	wsprintf(strText, "1.5");
	TextOut(hdc, rc.left + 180, rc.top + 280, strText, strlen(strText));
}

BasicInserterCraft::BasicInserterCraft(POINT _room, CraftItemInfo * _middleProduct1, CraftItemInfo * _middleProduct2)
{
	img = ImageManager::GetSingleton()->FindImage("basic-inserter-icon");
	info = { BASICINSERTER, 1.0f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("electronic-circuit-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("iron-gear-wheel-icon");
	sourceIcon[2] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");
	sourceIcon[3] = ImageManager::GetSingleton()->FindImage("copper-plate-icon");

	// source정보
	sourceKindNum = 3;
	sourceInfo[0] = { ELECTRONICCIRCUIT, _middleProduct1, 1, 1 };
	sourceInfo[1] = { IRONGEARWHEEL, _middleProduct2, 1, 1 };
	sourceInfo[2] = { IRONPLATE, nullptr, 1, 0 };
}

/*****************/

void BasicMiningDrillCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 40, INFO_WIDTH + 220, 200);

	wsprintf(strText, "전기 채광 드릴");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "2");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "3 x 전자회로");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "5 x 철 기어 휠");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 171, rc.left + 64, rc.top + 205);
	sourceIcon[2]->Render(hdc, rc.left + 47, rc.top + 188);
	wsprintf(strText, "10 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 180, strText, strlen(strText));

	wsprintf(strText, "채광 강도: 3");
	TextOut(hdc, rc.left + 30, rc.top + 215, strText, strlen(strText));
	wsprintf(strText, "채광 속도: 0.5");
	TextOut(hdc, rc.left + 30, rc.top + 240, strText, strlen(strText));
	wsprintf(strText, "채광 영역: 3X3");
	TextOut(hdc, rc.left + 30, rc.top + 265, strText, strlen(strText));
	wsprintf(strText, "최대 체력: 300");
	TextOut(hdc, rc.left + 30, rc.top + 290, strText, strlen(strText));
	wsprintf(strText, "에너지 소비량: 90 kW");
	TextOut(hdc, rc.left + 30, rc.top + 315, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 347, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 337, rc.left + 124, rc.top + 371);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 354);
	wsprintf(strText, "8.3");
	TextOut(hdc, rc.left + 102, rc.top + 355, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 337, rc.left + 163, rc.top + 371);
	sourceIcon[2]->Render(hdc, rc.left + 146, rc.top + 354);
	wsprintf(strText, "23");
	TextOut(hdc, rc.left + 153, rc.top + 355, strText, strlen(strText));

	Rectangle(hdc, rc.left + 168, rc.top + 337, rc.left + 202, rc.top + 371);
	sourceIcon[3]->Render(hdc, rc.left + 185, rc.top + 354);
	wsprintf(strText, "4.5");
	TextOut(hdc, rc.left + 180, rc.top + 355, strText, strlen(strText));
}

BasicMiningDrillCraft::BasicMiningDrillCraft(POINT _room, CraftItemInfo* _middleProduct1, CraftItemInfo* _middleProduct2)
{
	img = ImageManager::GetSingleton()->FindImage("basic-mining-drill-icon");
	info = { BASICMININGDRILL, 4.0f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("electronic-circuit-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("iron-gear-wheel-icon");
	sourceIcon[2] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");
	sourceIcon[3] = ImageManager::GetSingleton()->FindImage("copper-plate-icon");

	// source정보
	sourceKindNum = 3;
	sourceInfo[0] = { ELECTRONICCIRCUIT, _middleProduct1, 3, 1 };
	sourceInfo[1] = { IRONGEARWHEEL, _middleProduct2, 5, 1 };
	sourceInfo[2] = { IRONPLATE, nullptr, 10, 0 };
}

/*****************/

void ElectricFurnaceCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 80, INFO_WIDTH + 170, 200);

	wsprintf(strText, "전기 용광로");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "1");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "10 x 철 막대기");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "10 x 전자 회로");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 171, rc.left + 64, rc.top + 205);
	sourceIcon[2]->Render(hdc, rc.left + 47, rc.top + 188);
	wsprintf(strText, "20 x 돌");
	TextOut(hdc, rc.left + 70, rc.top + 180, strText, strlen(strText));

	wsprintf(strText, "최대 체력: 300");
	TextOut(hdc, rc.left + 30, rc.top + 215, strText, strlen(strText));
	wsprintf(strText, "에너지 소비량: 360 kW");
	TextOut(hdc, rc.left + 30, rc.top + 240, strText, strlen(strText));
	wsprintf(strText, "제작 속도: 2");
	TextOut(hdc, rc.left + 30, rc.top + 265, strText, strlen(strText));


	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 297, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 287, rc.left + 124, rc.top + 321);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 304);
	wsprintf(strText, "7");
	TextOut(hdc, rc.left + 114, rc.top + 305, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 287, rc.left + 163, rc.top + 321);
	sourceIcon[3]->Render(hdc, rc.left + 146, rc.top + 304);
	wsprintf(strText, "5");
	TextOut(hdc, rc.left + 153, rc.top + 305, strText, strlen(strText));

	Rectangle(hdc, rc.left + 168, rc.top + 287, rc.left + 202, rc.top + 321);
	sourceIcon[1]->Render(hdc, rc.left + 185, rc.top + 304);
	wsprintf(strText, "5");
	TextOut(hdc, rc.left + 190, rc.top + 305, strText, strlen(strText));

	Rectangle(hdc, rc.left + 207, rc.top + 287, rc.left + 241, rc.top + 321);
	sourceIcon[2]->Render(hdc, rc.left + 224, rc.top + 304);
	wsprintf(strText, "20");
	TextOut(hdc, rc.left + 222, rc.top + 305, strText, strlen(strText));
}

ElectricFurnaceCraft::ElectricFurnaceCraft(POINT _room, CraftItemInfo* _middleProduct, CraftItemInfo* _middleProduct2)
{
	img = ImageManager::GetSingleton()->FindImage("electric-furnace-icon");
	info = { ELECTRICFURNACE, 1.0f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("iron-stick-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("electronic-circuit-icon");
	sourceIcon[2] = ImageManager::GetSingleton()->FindImage("stone-icon");
	sourceIcon[3] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");

	// source정보
	sourceKindNum = 3;
	sourceInfo[0] = { IRONSTICK, _middleProduct, 10, 2 };
	sourceInfo[1] = { ELECTRONICCIRCUIT, _middleProduct2, 10, 0 };
	sourceInfo[2] = { STONE, nullptr, 20, 0 };
}

/*****************/


void SteamEngineCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 40, INFO_WIDTH + 170, 200);

	wsprintf(strText, "증기 발전기");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "5 x 철 기어 휠");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "12 x 철판");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 171, rc.left + 64, rc.top + 205);
	sourceIcon[2]->Render(hdc, rc.left + 47, rc.top + 188);
	wsprintf(strText, "1 x 석재 용광로");
	TextOut(hdc, rc.left + 70, rc.top + 180, strText, strlen(strText));

	wsprintf(strText, "최대 체력: 300");
	TextOut(hdc, rc.left + 30, rc.top + 215, strText, strlen(strText));
	wsprintf(strText, "최대 파워 출력: 무한");
	TextOut(hdc, rc.left + 30, rc.top + 240, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 272, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 262, rc.left + 124, rc.top + 296);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 279);
	wsprintf(strText, "8");
	TextOut(hdc, rc.left + 114, rc.top + 280, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 262, rc.left + 163, rc.top + 296);
	sourceIcon[1]->Render(hdc, rc.left + 146, rc.top + 279);
	wsprintf(strText, "22");
	TextOut(hdc, rc.left + 145, rc.top + 280, strText, strlen(strText));

	Rectangle(hdc, rc.left + 168, rc.top + 262, rc.left + 202, rc.top + 296);
	sourceIcon[3]->Render(hdc, rc.left + 185, rc.top + 279);
	wsprintf(strText, "10");
	TextOut(hdc, rc.left + 192, rc.top + 280, strText, strlen(strText));
}

SteamEngineCraft::SteamEngineCraft(POINT _room, CraftItemInfo* _middleProduct1, CraftItemInfo* _middleProduct2)
{
	img = ImageManager::GetSingleton()->FindImage("steam-engine-icon");
	info = { STEAMENGINE, 5.0f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("iron-gear-wheel-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");
	sourceIcon[2] = ImageManager::GetSingleton()->FindImage("stone-furnace-icon");
	sourceIcon[3] = ImageManager::GetSingleton()->FindImage("stone-icon");

	// source정보
	sourceKindNum = 3;
	sourceInfo[0] = { IRONGEARWHEEL, _middleProduct1, 5, 1 };
	sourceInfo[1] = { IRONPLATE, nullptr, 12, 0 };
	sourceInfo[2] = { STONEFURNACE, _middleProduct2, 1, 1 };
}

/*****************/

void AssemblingMachineCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 230, INFO_WIDTH + 190, 200);

	wsprintf(strText, "생산 설비");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "3 x 전자회로");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "5 x 철 기어 휠");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 171, rc.left + 64, rc.top + 205);
	sourceIcon[2]->Render(hdc, rc.left + 47, rc.top + 188);
	wsprintf(strText, "9 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 180, strText, strlen(strText));

	wsprintf(strText, "2종 이하의 재료를 필요로 하는 제품을 생산합니다.");
	TextOut(hdc, rc.left + 30, rc.top + 215, strText, strlen(strText));
	wsprintf(strText, "최대 체력: 200");
	TextOut(hdc, rc.left + 30, rc.top + 240, strText, strlen(strText));
	wsprintf(strText, "에너지 소비량: 90 kW");
	TextOut(hdc, rc.left + 30, rc.top + 265, strText, strlen(strText));
	wsprintf(strText, "제작 속도: 0.5");
	TextOut(hdc, rc.left + 30, rc.top + 290, strText, strlen(strText));


	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 322, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 312, rc.left + 124, rc.top + 346);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 329);
	wsprintf(strText, "4.5");
	TextOut(hdc, rc.left + 102, rc.top + 330, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 312, rc.left + 163, rc.top + 346);
	sourceIcon[2]->Render(hdc, rc.left + 146, rc.top + 329);
	wsprintf(strText, "22");
	TextOut(hdc, rc.left + 143, rc.top + 330, strText, strlen(strText));

	Rectangle(hdc, rc.left + 168, rc.top + 312, rc.left + 202, rc.top + 346);
	sourceIcon[3]->Render(hdc, rc.left + 185, rc.top + 329);
	wsprintf(strText, "4.5");
	TextOut(hdc, rc.left + 180, rc.top + 330, strText, strlen(strText));
}

AssemblingMachineCraft::AssemblingMachineCraft(POINT _room, CraftItemInfo * _middleProduct1, CraftItemInfo * _middleProduct2)
{
	img = ImageManager::GetSingleton()->FindImage("assembling-machine-icon");
	info = { ASSEMBLINGMACHINE, 0.5f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("electronic-circuit-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("iron-gear-wheel-icon");
	sourceIcon[2] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");
	sourceIcon[3] = ImageManager::GetSingleton()->FindImage("copper-plate-icon");

	// source정보
	sourceKindNum = 3;
	sourceInfo[0] = { ELECTRONICCIRCUIT, _middleProduct1, 3, 1 };
	sourceInfo[1] = { IRONGEARWHEEL, _middleProduct2, 5, 1 };
	sourceInfo[2] = { IRONPLATE, nullptr, 9, 0 };
}

/*****************/

void BasicSplitterCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 40, INFO_WIDTH + 170, 200);

	wsprintf(strText, "분배기");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "1");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "5 x 전자 회로");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "5 x 철판");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 171, rc.left + 64, rc.top + 205);
	sourceIcon[2]->Render(hdc, rc.left + 47, rc.top + 188);
	wsprintf(strText, "4 x 운송 밸트");
	TextOut(hdc, rc.left + 70, rc.top + 180, strText, strlen(strText));

	wsprintf(strText, "운송밸트로 오는 화물을");
	TextOut(hdc, rc.left + 30, rc.top + 215, strText, strlen(strText));
	wsprintf(strText, "1:1로 분리합니다.");
	TextOut(hdc, rc.left + 30, rc.top + 240, strText, strlen(strText));
	wsprintf(strText, "최대 체력: 80");
	TextOut(hdc, rc.left + 30, rc.top + 265, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 297, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 287, rc.left + 124, rc.top + 321);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 304);
	wsprintf(strText, "11.5");
	TextOut(hdc, rc.left + 94, rc.top + 305, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 287, rc.left + 163, rc.top + 321);
	sourceIcon[1]->Render(hdc, rc.left + 146, rc.top + 304);
	wsprintf(strText, "22");
	TextOut(hdc, rc.left + 145, rc.top + 305, strText, strlen(strText));

	Rectangle(hdc, rc.left + 168, rc.top + 287, rc.left + 202, rc.top + 321);
	sourceIcon[3]->Render(hdc, rc.left + 185, rc.top + 304);
	wsprintf(strText, "7.5");
	TextOut(hdc, rc.left + 180, rc.top + 305, strText, strlen(strText));
}

BasicSplitterCraft::BasicSplitterCraft(POINT _room, CraftItemInfo * _middleProduct1, CraftItemInfo * _middleProduct2)
{
	img = ImageManager::GetSingleton()->FindImage("basic-splitter-icon");
	info = { BASICSPLITTER, 1.0f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("electronic-circuit-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");
	sourceIcon[2] = ImageManager::GetSingleton()->FindImage("basic-transport-belt-icon");
	sourceIcon[3] = ImageManager::GetSingleton()->FindImage("copper-plate-icon");

	// source정보
	sourceKindNum = 3;
	sourceInfo[0] = { ELECTRONICCIRCUIT, _middleProduct1, 5, 1 };
	sourceInfo[1] = { IRONPLATE, nullptr, 5, 0 };
	sourceInfo[2] = { BASICTRANSPORTBELT, _middleProduct2, 4, 2 };
}


/*****************/

void LongHandedInserterCraft::InfoRender(HDC hdc)
{
	grayBox->AlphaRender(hdc, rc.left + 20, rc.top + 20, INFO_WIDTH + 40, INFO_WIDTH + 150, 200);

	wsprintf(strText, "긴 팔 투입기");
	TextOut(hdc, rc.left + 30, rc.top + 35, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 60, rc.left + 64, rc.top + 94);
	clockIcon->Render(hdc, rc.left + 47, rc.top + 77);
	wsprintf(strText, "0.5");
	TextOut(hdc, rc.left + 70, rc.top + 69, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 97, rc.left + 64, rc.top + 131);
	sourceIcon[0]->Render(hdc, rc.left + 47, rc.top + 114);
	wsprintf(strText, "1 x 철 기어 휠");
	TextOut(hdc, rc.left + 70, rc.top + 106, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 134, rc.left + 64, rc.top + 168);
	sourceIcon[1]->Render(hdc, rc.left + 47, rc.top + 151);
	wsprintf(strText, "1 x 철 판");
	TextOut(hdc, rc.left + 70, rc.top + 143, strText, strlen(strText));

	Rectangle(hdc, rc.left + 30, rc.top + 171, rc.left + 64, rc.top + 205);
	sourceIcon[2]->Render(hdc, rc.left + 47, rc.top + 188);
	wsprintf(strText, "1 x 투입기");
	TextOut(hdc, rc.left + 70, rc.top + 180, strText, strlen(strText));

	wsprintf(strText, "최대 체력: 40");
	TextOut(hdc, rc.left + 30, rc.top + 215, strText, strlen(strText));
	wsprintf(strText, "에너지 소비량: 20 kW");
	TextOut(hdc, rc.left + 30, rc.top + 240, strText, strlen(strText));

	wsprintf(strText, "총 재료:");
	TextOut(hdc, rc.left + 30, rc.top + 272, strText, strlen(strText));

	Rectangle(hdc, rc.left + 90, rc.top + 262, rc.left + 124, rc.top + 296);
	clockIcon->Render(hdc, rc.left + 107, rc.top + 279);
	wsprintf(strText, "2.8");
	TextOut(hdc, rc.left + 102, rc.top + 280, strText, strlen(strText));

	Rectangle(hdc, rc.left + 129, rc.top + 262, rc.left + 163, rc.top + 296);
	sourceIcon[1]->Render(hdc, rc.left + 146, rc.top + 279);
	wsprintf(strText, "7");
	TextOut(hdc, rc.left + 153, rc.top + 280, strText, strlen(strText));

	Rectangle(hdc, rc.left + 168, rc.top + 262, rc.left + 202, rc.top + 296);
	sourceIcon[3]->Render(hdc, rc.left + 185, rc.top + 279);
	wsprintf(strText, "1.5");
	TextOut(hdc, rc.left + 180, rc.top + 280, strText, strlen(strText));
}

LongHandedInserterCraft::LongHandedInserterCraft(POINT _room, CraftItemInfo * _middleProduct1, CraftItemInfo * _middleProduct2)
{
	img = ImageManager::GetSingleton()->FindImage("long-handed-inserter-icon");
	info = { LONGHANDEDINSERTER, 0.5f, img, 1, false };

	room = _room;
	rc = { 813 + 41 * _room.y, 365 + 41 * _room.x, 852 + 41 * _room.y, 404 + 41 * _room.x };

	// 인포렌더 정보
	sourceIcon[0] = ImageManager::GetSingleton()->FindImage("iron-gear-wheel-icon");
	sourceIcon[1] = ImageManager::GetSingleton()->FindImage("iron-plate-icon");
	sourceIcon[2] = ImageManager::GetSingleton()->FindImage("basic-inserter-icon");
	sourceIcon[3] = ImageManager::GetSingleton()->FindImage("copper-plate-icon");

	// source정보
	sourceKindNum = 3;
	sourceInfo[0] = { IRONGEARWHEEL, _middleProduct1, 1, 1 };
	sourceInfo[1] = { IRONPLATE, nullptr, 1, 0 };
	sourceInfo[2] = { BASICINSERTER, _middleProduct2, 1, 1 };
}
