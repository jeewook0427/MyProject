#include "BurnerInserter.h"
#include "Image.h"
#include "ProductIronPlate.h"


HRESULT BurnerInserter::Init()
{
	return S_OK;
}

void BurnerInserter::Release()
{
}

void BurnerInserter::Update()
{
	if (fuel.num < 2)
	{
		
		vecit = (*ObjectManager::GetSingleton()->FindObjectVec()).begin();
		for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
		{
			for (int k = -1; k < 2; k++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (abs(i) != abs(j))
					{
						if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == (tp.x - j)
							&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y - k))
						{
							if (CheckCollision(rect.left - 32 + 48, rect.top - 32 + 48, 96,
								(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10))
							{
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
								{
									if (fuel.name == COAL)
										fuel.num++;
									else
									{
										fuel.name = COAL;
										fuel.isStorage = true;
										fuel.num = 1;
									}
									(*ObjectManager::GetSingleton()->FindObjectPool(COAL)).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
									(*ObjectManager::GetSingleton()->FindObjectVec()).erase(vecit);

									goto skip;
								}


							}


						}
					}
				}
			}
			vecit++;
		}
	}
skip:


	if ((fuel.name == TREE || fuel.name == COAL) && (fuel.num > 0))
		isFuelFilled = true;
	else
		isFuelFilled = false;

	if (isFuelFilled)
	{
		fuelGage -= 0.05;
		if (fuelGage <= 0)
		{
			fuelGage = 100;
			fuel.num--;
			if (fuel.num <= 0)
			{
				fuel.name = EMPTY;
				fuel.num = 0;
				fuel.isStorage = false;
			}
		}

		if (direction == DR_UP) // 150~240
		{
			if (angle == 150)
			{
				GameNode* gamenode = nullptr;
				GameNode* temp = nullptr;

				if (tileinfo[tp.y - 1][tp.x].obj == STONEFURNACE || tileinfo[tp.y - 1][tp.x].obj == ELECTRICFURNACE)
				{
					gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y - 1][tp.x].obj)).find({ tp.x , tp.y - 1 })->second;
					if (gamenode->GetProduct()->num > 0)
					{
						if (gamenode->GetProduct()->name == IRONPLATE)
						{
							gamenode->GetProduct()->num--;
							if (gamenode->GetProduct()->num == 0)
							{
								gamenode->GetProduct()->isStorage = false;
								gamenode->GetProduct()->name = EMPTY;
							}
							temp = (*ObjectManager::GetSingleton()->FindObjectPool(IRONPLATE)).front();
							temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
							pickvec.push_back(temp);
							ObjectManager::GetSingleton()->InsertVec(temp);
							temp->SetIsPicked(true);
							(*ObjectManager::GetSingleton()->FindObjectPool(IRONPLATE)).pop();
							isPicked = true;
							if (checkRender)
								SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);
						}

						else if (gamenode->GetProduct()->name == COPPERPLATE)
						{
							gamenode->GetProduct()->num--;
							if (gamenode->GetProduct()->num == 0)
							{
								gamenode->GetProduct()->isStorage = false;
								gamenode->GetProduct()->name = EMPTY;
							}

							temp = (*ObjectManager::GetSingleton()->FindObjectPool(COPPERPLATE)).front();
							temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
							pickvec.push_back(temp);
							ObjectManager::GetSingleton()->InsertVec(temp);
							temp->SetIsPicked(true);
							(*ObjectManager::GetSingleton()->FindObjectPool(COPPERPLATE)).pop();
							isPicked = true;
							if (checkRender)
								SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);
						}
					}

				}

				else if (tileinfo[tp.y - 1][tp.x].obj == ASSEMBLINGMACHINE)
				{
					gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y - 1][tp.x].obj)).find({ tp.x , tp.y - 1 })->second;
					if (gamenode->GetProduct()->name == IRONGEARWHEEL)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}
						temp = (*ObjectManager::GetSingleton()->FindObjectPool(IRONGEARWHEEL)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(IRONGEARWHEEL)).pop();
						isPicked = true;
						if (checkRender)
							SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);
					}

					else if (gamenode->GetProduct()->name == COPPERCABLE)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(COPPERCABLE)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(COPPERCABLE)).pop();
						isPicked = true;
						if (checkRender)
							SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);
					}

					else if (gamenode->GetProduct()->name == ELECTRONICCIRCUIT)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(ELECTRONICCIRCUIT)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(ELECTRONICCIRCUIT)).pop();
						isPicked = true;
						if (checkRender)
							SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);
					}

					else if (gamenode->GetProduct()->name == ADVANCEDCIRCUIT)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(ADVANCEDCIRCUIT)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(ADVANCEDCIRCUIT)).pop();
						isPicked = true;
						if (checkRender)
							SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);
					}

				}



			}

			if (angle > 140 && angle < 170 && !isPicked)
			{
				GameNode* gamenode;
				bool checkResource = false;
				for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
				{
					if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == tp.x
						&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y - 1))
					{
						if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
						{
							if (tileinfo[tp.y + 1][tp.x].obj == STONEFURNACE || tileinfo[tp.y + 1][tp.x].obj == ELECTRICFURNACE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y + 1][tp.x].obj)).find({ tp.x , tp.y + 1 })->second;
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
								{
									if (gamenode->GetFuel()->num > 7 && gamenode->GetFuel()->name == COAL)
										checkResource = false;
									else
										checkResource = true;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRON)
								{
									if (gamenode->GetMeterial()->num > 7 && gamenode->GetMeterial()->name == IRON)
										checkResource = false;
									else
										checkResource = true;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPER)
								{
									if (gamenode->GetMeterial()->num > 7 && gamenode->GetMeterial()->name == COPPER)
										checkResource = false;
									else
										checkResource = true;
								}

							}

							else if (tileinfo[tp.y + 1][tp.x].obj == BURNERMININGDRILL)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).find({ tp.x , tp.y + 1 })->second;
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
								{
									if (gamenode->GetFuel()->num > 7 && gamenode->GetFuel()->name == COAL)
										checkResource = false;
									else
										checkResource = true;
								}
								


							}

							else if (tileinfo[tp.y + 1][tp.x].obj == ASSEMBLINGMACHINE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y + 1][tp.x].obj)).find({ tp.x , tp.y + 1 })->second;
								if (gamenode->GetLayer() == IRONGEARWHEEL)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == IRONPLATE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == COPPERCABLE)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERPLATE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == ELECTRONICCIRCUIT)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == IRONPLATE)
											checkResource = false;
										else
											checkResource = true;
									}

									else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERCABLE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERCABLE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == ADVANCEDCIRCUIT)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == ELECTRONICCIRCUIT)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == ELECTRONICCIRCUIT)
											checkResource = false;
										else
											checkResource = true;
									}

									else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERCABLE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERCABLE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

							}

							else if (tileinfo[tp.y + 1][tp.x].obj == STEAMENGINE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y + 1][tp.x].obj)).find({ tp.x , tp.y + 1 })->second;
							
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
								{
									if (gamenode->GetFuel()->num > 20 && gamenode->GetFuel()->name == COAL)
										checkResource = false;
									else
										checkResource = true;
								}
								
							}

							else
							{
								checkResource = true;
							}

							if (checkResource)
							{
								if (CheckCollision(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2, handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2, 15,
									(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10))
								{
									(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetIsPicked(true);
									pickvec.push_back((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
									isPicked = true;
									if (checkRender)
										SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);
									goto skippick1;
								}
							}
						}

					}
				}
			}

		skippick1:



			if (isPicked)
			{
				for (int j = 0; j < pickvec.size(); j++)
				{
					pickvec[j]->SetPos({ (float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2),(float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2) });
					/*if (pickvec[j]->GetIsDelete())
					{
						pickvec.erase(it);
					}*/

				}
				angle += 3.0f;
				if (angle > 330)
				{

					isPicked = false;
					for (int j = 0; j < pickvec.size(); j++)
					{
						pickvec[j]->SetIsPicked(false);

					}
					pickvec.clear();


				}

			}

			else
			{
				if (angle > 360)
					angle = 0;

				angle += 3.0f;
				if (angle > 150 && angle < 330)
				{
					angle = 150;
				}
			}
		}

		else if (direction == DR_DOWN) //330~60
		{
			if (angle == 330)
			{
				GameNode* gamenode = nullptr;
				GameNode* temp = nullptr;

				if (tileinfo[tp.y + 1][tp.x].obj == STONEFURNACE || tileinfo[tp.y + 1][tp.x].obj == ELECTRICFURNACE)
				{
					gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y + 1][tp.x].obj)).find({ tp.x , tp.y + 1 })->second;
					if (gamenode->GetProduct()->num > 0)
					{
						if (gamenode->GetProduct()->name == IRONPLATE)
						{
							gamenode->GetProduct()->num--;
							if (gamenode->GetProduct()->num == 0)
							{
								gamenode->GetProduct()->isStorage = false;
								gamenode->GetProduct()->name = EMPTY;
							}
							temp = (*ObjectManager::GetSingleton()->FindObjectPool(IRONPLATE)).front();
							temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
							pickvec.push_back(temp);
							ObjectManager::GetSingleton()->InsertVec(temp);
							temp->SetIsPicked(true);
							(*ObjectManager::GetSingleton()->FindObjectPool(IRONPLATE)).pop();
							isPicked = true;

						}

						else if (gamenode->GetProduct()->name == COPPERPLATE)
						{
							gamenode->GetProduct()->num--;
							if (gamenode->GetProduct()->num == 0)
							{
								gamenode->GetProduct()->isStorage = false;
								gamenode->GetProduct()->name = EMPTY;
							}

							temp = (*ObjectManager::GetSingleton()->FindObjectPool(COPPERPLATE)).front();
							temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
							pickvec.push_back(temp);
							ObjectManager::GetSingleton()->InsertVec(temp);
							temp->SetIsPicked(true);
							(*ObjectManager::GetSingleton()->FindObjectPool(COPPERPLATE)).pop();
							isPicked = true;
						}
					}

				}

				else if (tileinfo[tp.y + 1][tp.x].obj == ASSEMBLINGMACHINE)
				{
					gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y + 1][tp.x].obj)).find({ tp.x , tp.y + 1 })->second;
					if (gamenode->GetProduct()->name == IRONGEARWHEEL)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}
						temp = (*ObjectManager::GetSingleton()->FindObjectPool(IRONGEARWHEEL)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(IRONGEARWHEEL)).pop();
						isPicked = true;
					}

					else if (gamenode->GetProduct()->name == COPPERCABLE)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(COPPERCABLE)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(COPPERCABLE)).pop();
						isPicked = true;
					}

					else if (gamenode->GetProduct()->name == ELECTRONICCIRCUIT)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(ELECTRONICCIRCUIT)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(ELECTRONICCIRCUIT)).pop();
						isPicked = true;
					}

					else if (gamenode->GetProduct()->name == ADVANCEDCIRCUIT)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(ADVANCEDCIRCUIT)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(ADVANCEDCIRCUIT)).pop();
						isPicked = true;
					}



				}
				if (isPicked)
					if (checkRender)
						SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);

			}

			if (angle > 320 && angle < 350)
			{
				GameNode* gamenode;
				bool checkResource = false;

				for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
				{
					if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == tp.x
						&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y + 1))
					{
						if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
						{
							if (tileinfo[tp.y - 1][tp.x].obj == STONEFURNACE || tileinfo[tp.y - 1][tp.x].obj == ELECTRICFURNACE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y - 1][tp.x].obj)).find({ tp.x , tp.y - 1 })->second;
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
								{
									if (gamenode->GetFuel()->num > 7 && gamenode->GetFuel()->name == COAL)
										checkResource = false;
									else
										checkResource = true;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRON)
								{
									if (gamenode->GetMeterial()->num > 7 && gamenode->GetMeterial()->name == IRON)
										checkResource = false;
									else
										checkResource = true;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPER)
								{
									if (gamenode->GetMeterial()->num > 7 && gamenode->GetMeterial()->name == COPPER)
										checkResource = false;
									else
										checkResource = true;
								}

							}

							else if (tileinfo[tp.y - 1][tp.x].obj == BURNERMININGDRILL)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).find({ tp.x , tp.y - 1 })->second;
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
								{
									if (gamenode->GetFuel()->num > 7 && gamenode->GetFuel()->name == COAL)
										checkResource = false;
									else
										checkResource = true;
								}


							}

							else if (tileinfo[tp.y - 1][tp.x].obj == ASSEMBLINGMACHINE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y - 1][tp.x].obj)).find({ tp.x , tp.y - 1 })->second;
								if (gamenode->GetLayer() == IRONGEARWHEEL)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == IRONPLATE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == COPPERCABLE)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERPLATE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == ELECTRONICCIRCUIT)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == IRONPLATE)
											checkResource = false;
										else
											checkResource = true;
									}

									else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERCABLE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERCABLE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == ADVANCEDCIRCUIT)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == ELECTRONICCIRCUIT)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == ELECTRONICCIRCUIT)
											checkResource = false;
										else
											checkResource = true;
									}

									else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERCABLE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERCABLE)
											checkResource = false;
										else
											checkResource = true;
									}


								}



							}
							else if (tileinfo[tp.y - 1][tp.x].obj == STEAMENGINE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y - 1][tp.x].obj)).find({ tp.x , tp.y - 1 })->second;
								
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
								{
									if (gamenode->GetFuel()->num > 20 && gamenode->GetFuel()->name == COAL)
										checkResource = false;
									else
										checkResource = true;
								}
								
							}
							else
							{
								checkResource = true;
							}

							if (checkResource)
							{
								if (CheckCollision(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2, handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2, 15,
									(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10))
								{
									(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetIsPicked(true);
									pickvec.push_back((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
									isPicked = true;
									if (checkRender)
										SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);
									goto skippick2;
								}
							}
						}


					}
				}
			}
		skippick2:



			if (isPicked)
			{
				for (int j = 0; j < pickvec.size(); j++)
				{
					pickvec[j]->SetPos({ (float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2),(float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2) });
					/*if (pickvec[j]->GetIsDelete())
					{
						pickvec.erase(it);
					}*/

				}
				angle += 4.0f;
				if (angle > 360)
					angle = 0;

				if (angle > 150 && angle < 200)
				{

					isPicked = false;
					for (int j = 0; j < pickvec.size(); j++)
					{
						pickvec[j]->SetIsPicked(false);

					}
					pickvec.clear();
				}


			}

			else
			{
				angle += 4.0f;
				if (angle > 330)
				{
					angle = 330;
				}
			}
		}

		else if (direction == DR_RIGHT)// 240~330
		{
			if (angle == 240)
			{
				GameNode* gamenode = nullptr;
				GameNode* temp = nullptr;

				if (tileinfo[tp.y][tp.x + 1].obj == STONEFURNACE || tileinfo[tp.y][tp.x + 1].obj == ELECTRICFURNACE)
				{
					gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y][tp.x + 1].obj)).find({ tp.x + 1 , tp.y })->second;
					if (gamenode->GetProduct()->num > 0)
					{
						if (gamenode->GetProduct()->name == IRONPLATE)
						{
							gamenode->GetProduct()->num--;
							if (gamenode->GetProduct()->num == 0)
							{
								gamenode->GetProduct()->isStorage = false;
								gamenode->GetProduct()->name = EMPTY;
							}
							temp = (*ObjectManager::GetSingleton()->FindObjectPool(IRONPLATE)).front();
							temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
							pickvec.push_back(temp);
							ObjectManager::GetSingleton()->InsertVec(temp);
							temp->SetIsPicked(true);
							(*ObjectManager::GetSingleton()->FindObjectPool(IRONPLATE)).pop();
							isPicked = true;
						}

						else if (gamenode->GetProduct()->name == COPPERPLATE)
						{
							gamenode->GetProduct()->num--;
							if (gamenode->GetProduct()->num == 0)
							{
								gamenode->GetProduct()->isStorage = false;
								gamenode->GetProduct()->name = EMPTY;
							}

							temp = (*ObjectManager::GetSingleton()->FindObjectPool(COPPERPLATE)).front();
							temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
							pickvec.push_back(temp);
							ObjectManager::GetSingleton()->InsertVec(temp);
							temp->SetIsPicked(true);
							(*ObjectManager::GetSingleton()->FindObjectPool(COPPERPLATE)).pop();
							isPicked = true;
						}
					}

				}

				else if (tileinfo[tp.y][tp.x + 1].obj == ASSEMBLINGMACHINE)
				{
					gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y][tp.x + 1].obj)).find({ tp.x + 1 , tp.y })->second;
					if (gamenode->GetProduct()->name == IRONGEARWHEEL)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}
						temp = (*ObjectManager::GetSingleton()->FindObjectPool(IRONGEARWHEEL)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(IRONGEARWHEEL)).pop();
						isPicked = true;
					}

					else if (gamenode->GetProduct()->name == COPPERCABLE)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(COPPERCABLE)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(COPPERCABLE)).pop();
						isPicked = true;
					}

					else if (gamenode->GetProduct()->name == ELECTRONICCIRCUIT)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(ELECTRONICCIRCUIT)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(ELECTRONICCIRCUIT)).pop();
						isPicked = true;
					}

					else if (gamenode->GetProduct()->name == ADVANCEDCIRCUIT)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(ADVANCEDCIRCUIT)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(ADVANCEDCIRCUIT)).pop();
						isPicked = true;
					}

				}

				if (isPicked)
					if (checkRender)
						SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);



			}

			if (angle > 230 && angle < 260)
			{
				GameNode* gamenode;
				bool checkResource = false;

				for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
				{
					if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
					{
						if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == tp.x + 1
							&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y))
						{
							if (tileinfo[tp.y][tp.x - 1].obj == STONEFURNACE || tileinfo[tp.y][tp.x - 1].obj == ELECTRICFURNACE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y][tp.x - 1].obj)).find({ tp.x - 1 , tp.y })->second;
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
								{
									if (gamenode->GetFuel()->num > 7)
										checkResource = false;
									else
										checkResource = true;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRON)
								{
									if (gamenode->GetMeterial()->num > 7 && gamenode->GetMeterial()->name == IRON)
										checkResource = false;
									else
										checkResource = true;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPER)
								{
									if (gamenode->GetMeterial()->num > 7 && gamenode->GetMeterial()->name == COPPER)
										checkResource = false;
									else
										checkResource = true;
								}

							}

							else if (tileinfo[tp.y][tp.x - 1].obj == BURNERMININGDRILL)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).find({ tp.x - 1 , tp.y })->second;
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
								{
									if (gamenode->GetFuel()->num > 7)
										checkResource = false;
									else
										checkResource = true;
								}


							}

							else if (tileinfo[tp.y][tp.x - 1].obj == ASSEMBLINGMACHINE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y][tp.x - 1].obj)).find({ tp.x - 1 , tp.y })->second;
								if (gamenode->GetLayer() == IRONGEARWHEEL)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == IRONPLATE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == COPPERCABLE)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERPLATE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == ELECTRONICCIRCUIT)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == IRONPLATE)
											checkResource = false;
										else
											checkResource = true;
									}

									else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERCABLE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERCABLE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == ADVANCEDCIRCUIT)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == ELECTRONICCIRCUIT)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == ELECTRONICCIRCUIT)
											checkResource = false;
										else
											checkResource = true;
									}

									else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERCABLE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERCABLE)
											checkResource = false;
										else
											checkResource = true;
									}
								}


							}

							else if (tileinfo[tp.y][tp.x - 1].obj == STEAMENGINE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).find({ tp.x - 1 , tp.y })->second;
								
								if (gamenode->GetFuel()->num > 20 && gamenode->GetFuel()->name == COAL)
									checkResource = false;
								else
									checkResource = true;
								


							}

							else
							{
								checkResource = true;
							}

							if (checkResource)
							{
								if (CheckCollision(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2, handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2, 15,
									(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10))
								{
									(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetIsPicked(true);
									pickvec.push_back((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
									isPicked = true;
									if (checkRender)
										SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);
									goto pickskip3;
								}
							}
						}


					}
				}
			}

		pickskip3:



			if (isPicked)
			{
				for (int j = 0; j < pickvec.size(); j++)
				{
					pickvec[j]->SetPos({ (float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2),(float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2) });
					/*if (pickvec[j]->GetIsDelete())
					{
						pickvec.erase(it);
					}*/

				}
				angle += 4.0f;

				if (angle > 360)
					angle = 0;

				if (angle > 60 && angle < 200)
				{
					isPicked = false;
					for (int j = 0; j < pickvec.size(); j++)
					{
						pickvec[j]->SetIsPicked(false);

					}
					pickvec.clear();
				}


			}

			else
			{
				angle += 4.0f;
				if (angle > 240)
				{
					angle = 240;
				}

			}
		}

		if (direction == DR_LEFT)//60~150
		{
			if (angle == 60)
			{
				GameNode* gamenode = nullptr;
				GameNode* temp = nullptr;

				if (tileinfo[tp.y][tp.x - 1].obj == STONEFURNACE || tileinfo[tp.y][tp.x - 1].obj == ELECTRICFURNACE)
				{
					gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y][tp.x - 1].obj)).find({ tp.x - 1 , tp.y })->second;
					if (gamenode->GetProduct()->num > 0)
					{
						if (gamenode->GetProduct()->name == IRONPLATE)
						{
							gamenode->GetProduct()->num--;
							if (gamenode->GetProduct()->num == 0)
							{
								gamenode->GetProduct()->isStorage = false;
								gamenode->GetProduct()->name = EMPTY;
							}
							temp = (*ObjectManager::GetSingleton()->FindObjectPool(IRONPLATE)).front();
							temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
							pickvec.push_back(temp);
							ObjectManager::GetSingleton()->InsertVec(temp);
							temp->SetIsPicked(true);
							(*ObjectManager::GetSingleton()->FindObjectPool(IRONPLATE)).pop();
							isPicked = true;
						}

						else if (gamenode->GetProduct()->name == COPPERPLATE)
						{
							gamenode->GetProduct()->num--;
							if (gamenode->GetProduct()->num == 0)
							{
								gamenode->GetProduct()->isStorage = false;
								gamenode->GetProduct()->name = EMPTY;
							}

							temp = (*ObjectManager::GetSingleton()->FindObjectPool(COPPERPLATE)).front();
							temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
							pickvec.push_back(temp);
							ObjectManager::GetSingleton()->InsertVec(temp);
							temp->SetIsPicked(true);
							(*ObjectManager::GetSingleton()->FindObjectPool(COPPERPLATE)).pop();
							isPicked = true;
						}
					}

				}

				else if (tileinfo[tp.y][tp.x - 1].obj == ASSEMBLINGMACHINE)
				{
					gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y][tp.x - 1].obj)).find({ tp.x - 1 , tp.y })->second;
					if (gamenode->GetProduct()->name == IRONGEARWHEEL)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}
						temp = (*ObjectManager::GetSingleton()->FindObjectPool(IRONGEARWHEEL)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(IRONGEARWHEEL)).pop();
						isPicked = true;
					}

					else if (gamenode->GetProduct()->name == COPPERCABLE)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(COPPERCABLE)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(COPPERCABLE)).pop();
						isPicked = true;
					}

					else if (gamenode->GetProduct()->name == ELECTRONICCIRCUIT)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(ELECTRONICCIRCUIT)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(ELECTRONICCIRCUIT)).pop();
						isPicked = true;
					}

					else if (gamenode->GetProduct()->name == ADVANCEDCIRCUIT)
					{
						gamenode->GetProduct()->num--;
						if (gamenode->GetProduct()->num == 0)
						{
							gamenode->GetProduct()->isStorage = false;
							gamenode->GetProduct()->name = EMPTY;
						}

						temp = (*ObjectManager::GetSingleton()->FindObjectPool(ADVANCEDCIRCUIT)).front();
						temp->Init((float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2), (float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2));
						pickvec.push_back(temp);
						ObjectManager::GetSingleton()->InsertVec(temp);
						temp->SetIsPicked(true);
						(*ObjectManager::GetSingleton()->FindObjectPool(ADVANCEDCIRCUIT)).pop();
						isPicked = true;
					}



				}

				if (isPicked)
					if (checkRender)
						SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);

			}

			if (angle > 50 && angle < 80)
			{
				GameNode* gamenode;
				bool checkResource = false;

				for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
				{
					if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == tp.x - 1
						&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y == (tp.y))
					{
						if (!(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetIsPicked())
						{
							if (tileinfo[tp.y][tp.x + 1].obj == STONEFURNACE || tileinfo[tp.y][tp.x + 1].obj == ELECTRICFURNACE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y][tp.x + 1].obj)).find({ tp.x + 1 , tp.y })->second;
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
								{
									if (gamenode->GetFuel()->num > 7 && gamenode->GetFuel()->name == COAL)
										checkResource = false;
									else
										checkResource = true;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRON)
								{
									if (gamenode->GetMeterial()->num > 7 && gamenode->GetMeterial()->name == IRON)
										checkResource = false;
									else
										checkResource = true;
								}

								else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPER)
								{
									if (gamenode->GetMeterial()->num > 7 && gamenode->GetMeterial()->name == COPPER)
										checkResource = false;
									else
										checkResource = true;
								}

							}

							else if (tileinfo[tp.y][tp.x + 1].obj == BURNERMININGDRILL)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(BURNERMININGDRILL)).find({ tp.x + 1 , tp.y })->second;
								if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COAL)
								{
									if (gamenode->GetFuel()->num > 7 && gamenode->GetFuel()->name == COAL)
										checkResource = false;
									else
										checkResource = true;
								}


							}

							else if (tileinfo[tp.y][tp.x + 1].obj == ASSEMBLINGMACHINE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(tileinfo[tp.y][tp.x + 1].obj)).find({ tp.x + 1 , tp.y })->second;
								if (gamenode->GetLayer() == IRONGEARWHEEL)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == IRONPLATE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == COPPERCABLE)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERPLATE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == ELECTRONICCIRCUIT)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == IRONPLATE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == IRONPLATE)
											checkResource = false;
										else
											checkResource = true;
									}

									else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERCABLE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERCABLE)
											checkResource = false;
										else
											checkResource = true;
									}
								}

								else if (gamenode->GetLayer() == ADVANCEDCIRCUIT)
								{
									if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == ELECTRONICCIRCUIT)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == ELECTRONICCIRCUIT)
											checkResource = false;
										else
											checkResource = true;
									}

									else if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer() == COPPERCABLE)
									{
										if (gamenode->GetAssemMeterial()[0].num > 7 && gamenode->GetAssemMeterial()[0].name == COPPERCABLE)
											checkResource = false;
										else
											checkResource = true;
									}
								}
								else
								{
									checkResource = true;
								}


							}

							else if (tileinfo[tp.y][tp.x + 1].obj == STEAMENGINE)
							{
								gamenode = (*ObjectManager::GetSingleton()->FindObjectMap(STEAMENGINE)).find({ tp.x + 1 , tp.y })->second;
							
								if (gamenode->GetFuel()->num > 20 && gamenode->GetFuel()->name == COAL)
									checkResource = false;
								else
									checkResource = true;
								


							}

							else
							{
								checkResource = true;
							}

							if (checkResource)
							{
								if (CheckCollision(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2, handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2, 15,
									(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10))
								{
									(*ObjectManager::GetSingleton()->FindObjectVec())[i]->SetIsPicked(true);
									pickvec.push_back((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
									isPicked = true;
									if (checkRender)
										SoundManager::GetSingleton()->Play("basicinserterworking", 1.0f);
									goto skippick4;
								}
							}
						}


					}
				}
			}

		skippick4:



			if (isPicked)
			{
				for (int j = 0; j < pickvec.size(); j++)
				{
					pickvec[j]->SetPos({ (float)(handRect.left + 7.5 + g_pos.x - WINSIZE_X / 2),(float)(handRect.top + 7.5 + g_pos.y - WINSIZE_Y / 2) });
					/*if (pickvec[j]->GetIsDelete())
					{
						pickvec.erase(it);
					}*/

				}
				angle += 4.0f;
				if (angle > 240)
				{
					isPicked = false;
					for (int j = 0; j < pickvec.size(); j++)
					{
						pickvec[j]->SetIsPicked(false);

					}
					pickvec.clear();
				}

			}

			else
			{
				angle += 4.0f;

				if (angle > 360)
					angle = 0;

				if (angle > 60 && angle < 240)
				{
					angle = 60;
				}
			}
		}

		
		
	}

	else
	{
		fuelGage = 100;
		//materialGage = 0;
	}

	if (abs(tp.x - (int)(g_pos.x) / 32) < 27 && abs(tp.y - (int)(g_pos.y) / 32) < 16)
	{
		if (PtInRect(&rect, mousepos))
		{
			isRectRender = true;

			if (((abs(rect.left - p_pos.x) < 64 && abs(rect.top - p_pos.y) < 64) || (abs(rect.left - p_pos.x) < 64 && abs(rect.bottom - p_pos.y) < 64))
				|| ((abs(rect.right - p_pos.x) < 64 && abs(rect.top - p_pos.y) < 64) || (abs(rect.right - p_pos.x) < 64 && abs(rect.bottom - p_pos.y) < 64)))
			{
				isSelectedClose = true;
			}

			else
			{
				isSelectedClose = false;
			}

			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON) && !ToolInvenIsOpen)
			{
				isDelete = true;
				Tutorial::GetSingleton()->SucceedQuest_9();
				AddInInventory(BURNERINSERTER, 1);

				for (int i = 0; i < 1; i++)
				{
					for (int j = 0; j < 1; j++)
					{
						tileinfo[tp.y - i][tp.x - j].obj = EMPTY;
					}
				}

				if (checkRender)
				{
					if (!soundPlay)
					{
						SoundManager::GetSingleton()->Play("remove", 2.0f);
						soundPlay = true;

					}
				}
				else
				{
					SoundManager::GetSingleton()->Stop("remove");
					soundPlay = false;
				}

			}
			
			if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
			{
				direction++;
				if (direction == DR_END)
				{
					direction = DR_UP;
				}

				frame.x = direction;
			}


		}

		else
		{
			isRectRender = false;
		}

		// ÆÈ ¹æÇâÁ¶Àý

		if (angle >= 360.0f)
		{
			angle -= 360.0f;
		}

		if (angle != handBaseAngle_InDr[direction])
		{
			angle += 2.0f;
		}

		if (handAngle >= 360.0f)
		{
			handAngle -= 360.0f;
		}

		if (handAngle != handOpenAngle_InDr[direction])
		{
			handAngle += 3.0f;
		}

	}

	basepoint = { ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32 / 2 ,
			((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16 };

	basearmpoint = { (float)(((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32 / 2 + 20 * cosf(DEGREE_TO_RADIAN((angle + 90)))),
		(float)(((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 13 + 20 * sinf(DEGREE_TO_RADIAN((angle + 90)))) };


	handRect = GetRectToCenter(basearmpoint.x + 26 * cosf(DEGREE_TO_RADIAN((angle + 150))), basearmpoint.y + 26 * sinf(DEGREE_TO_RADIAN((angle + 150))), 15, 15);

}

void BurnerInserter::Render(HDC hdc)
{

	if (abs(tp.x - (int)(g_pos.x) / 32) < 26 && abs(tp.y - (int)(g_pos.y) / 32) < 15)
		checkRender = true;
	else
		checkRender = false;

	if (image&&checkRender)
	{
		

		image->FrameRender(hdc, basepoint.x, basepoint.y, frame.x, frame.y);

		handBaseImage->AlphaRender(hdc, basepoint.x + 10 * cosf(DEGREE_TO_RADIAN((angle + 90))),
			basepoint.y + 10 * sinf(DEGREE_TO_RADIAN((angle + 90))) - 3, 0, 0, 150, 1, angle);

		handOpenImage->AlphaRender(hdc, basearmpoint.x + 13 * cosf(DEGREE_TO_RADIAN((angle + 150))),
			basearmpoint.y + 13 * sinf(DEGREE_TO_RADIAN((angle + 150))), 0, 0, 150, 1, angle + 240);

		if (!isFuelFilled)
		{
			if (checkAlpha)
			{
				alpha += 10;
				if (alpha >= 255)
				{
					checkAlpha = false;
					alpha = 255;
				}

			}

			else
			{
				alpha -= 10;
				if (alpha <= 0)
				{
					checkAlpha = true;
					alpha = 0;
				}
			}



			warning->AlphaRender(hdc, basepoint.x, basepoint.y, 0, 0, alpha, 0.5);
		}




		if (isRectRender)
		{
			this->SelectBoxRender(hdc);
		}
	}


}

void BurnerInserter::SelectBoxRender(HDC hdc)
{
	if (!isSelectedClose)
	{
		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8 * scale,
			rect.top - g_pos.y + WINSIZE_Y / 2 + 8 * scale, 2, 0, scale);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8 * scale,
			rect.top - g_pos.y + WINSIZE_Y / 2 + 8 * scale, 3, 0, scale);

		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8 * scale,
			rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8 * scale, 2, 1, scale);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8 * scale,
			rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8 * scale, 3, 1, scale);
	}

	else
	{
		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8 * scale,
			rect.top - g_pos.y + WINSIZE_Y / 2 + 8 * scale, 0, 0, scale);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8 * scale,
			rect.top - g_pos.y + WINSIZE_Y / 2 + 8 * scale, 1, 0, scale);

		selectBox->FrameRender(hdc, rect.left - g_pos.x + WINSIZE_X / 2 + 8 * scale,
			rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8 * scale, 0, 1, scale);

		selectBox->FrameRender(hdc, rect.right - g_pos.x + WINSIZE_X / 2 - 8 * scale,
			rect.bottom - g_pos.y + WINSIZE_Y / 2 - 8 * scale, 1, 1, scale);
	}
}



BurnerInserter::BurnerInserter(TILE_POINT _tp, int hp)
{
	tp = _tp;
	Hp = hp;
	rect = { 32 * tp.x, 32 * tp.y, 32 * (tp.x + 1), 32 * (tp.y + 1) };

	image = ImageManager::GetSingleton()->FindImage("burner-inserter-platform");
	handBaseImage = ImageManager::GetSingleton()->FindImage("burner-inserter-hand-base");
	handClosedImage = ImageManager::GetSingleton()->FindImage("burner-inserter-hand-closed");
	handOpenImage = ImageManager::GetSingleton()->FindImage("burner-inserter-hand-open");
	selectBox = ImageManager::GetSingleton()->FindImage("mousecursor");
	invenImage = ImageManager::GetSingleton()->FindImage("objectinven");
	warning = ImageManager::GetSingleton()->FindImage("fuel-icon-red");

	isSelected = false;
	isSelectedClose = false;
	isRectRender = false;
	//isInvenOpen = false;

	scale = 1.0f;
	renderCount = 0;
	updateCount = 0;

	direction = DR_UP;
	frame.x = 0;	frame.y = 0;
	angle = 180.0f;
	handAngle = 180.0f;

	alpha = 0;

	basepoint = { ((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32 / 2 ,
			((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 16 };

	basearmpoint = { (float)(((tp.x - (int)(g_pos.x - 800) / 32)) * 32 - (g_pos.x - (int)g_pos.x / 32 * 32) + 32 / 2 + 20 * cosf(DEGREE_TO_RADIAN((angle + 90)))),
		(float)(((tp.y - (int)(g_pos.y - WINSIZE_Y / 2) / 32)) * 32 - (g_pos.y - (int)g_pos.y / 32 * 32) + 13 + 20 * sinf(DEGREE_TO_RADIAN((angle + 90)))) };


	handRect = GetRectToCenter(basearmpoint.x + 26 * cosf(DEGREE_TO_RADIAN((angle + 150))), basearmpoint.y + 26 * sinf(DEGREE_TO_RADIAN((angle + 150))), 15, 15);


	ImageManager::GetSingleton()->FindImage("mini-inserter-icon")->
		Render(ImageManager::GetSingleton()->FindImage("worldmapBuffer")->GetMemDC(), 400 + (int)(3 * tp.x + 1.5), 50 + (int)(3 * tp.y + 1.5));

	Tutorial::GetSingleton()->SucceedQuest_8();

}

BurnerInserter::BurnerInserter()
{
}

BurnerInserter::~BurnerInserter()
{
}
