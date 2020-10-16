#include "SieKensou.h"
#include "Image.h"
#include "macroFunction.h"


HRESULT SieKensou::Init()
{
	if (isReverse)
	{
		posX = 200;
		posY = WINSIZE_Y - 300;
	}
	else
	{
		posX = WINSIZE_X - 400;
		posY = WINSIZE_Y - 300;
	}
	
	width = 1560;
	height = 2100;
	maxFrameX=12;
	maxFrameY=14;
	skillposX = 0;
	skillposY = 0;

	img = new Image();
	img->Init("Image/Sie Kensou sprite sheet.bmp", posX, posY, width, height, maxFrameX, maxFrameY, true, RGB(255, 0, 255));

	//신경안쓰셔도됩니다
	profile = new Image();
	profile->Init("Image/kensou profile.bmp", 103, 96, true, RGB(255, 0, 255));

	

	//반전시키기위해 백버퍼를 하나 더 만듬
	midBackBuffer = new Image();
	midBackBuffer->Init(260, 300, true, RGB(255, 0, 255));

	skillBackBuffer = new Image();
	skillBackBuffer->Init(260, 300, true, RGB(255, 0, 255));

	effectBackBuffer = new Image();
	effectBackBuffer->Init(260, 300, true, RGB(255, 0, 255));

	currentframex = 0;
	currentframey = 0;
	actionframex = 0;
	actionframey = 0;
	hitframex = 0;
	hitframey = 0;
	effectframex = 0;
	effectframey = 0;
	damage=0;
	insdamage=0;
	skillspeed = 15;
	effectpos.x = -500;
	effectpos.y = -500;
	

	goFoward = false;
	goBackward = false;
	rightPunch = false;
	leftKick = false;
	isAction = false;
	//isReverse = false; 
	isDead = false;
	isWin = false;
	gameStart = false;
	keyDownCheck = false;
	keyFowardCheck = false;
	commandA = false;
	commandB = false;
	skillA = false;
	isSkill = false;
	launchSkillA = false;
	isGuard = false;
	isSkillIsHit = false;
	gameOver = false;
	skillB = false;
	launchSkillB = false;
	keyBackCheck = false;
	
	comtime = 0;
	actiontime = 0;
	hittime = 0;
	commandtime = 0;
	effecttime = 0;
	speed = 4;

	scale = 2;

	mciOpenParam_StartMostion.lpstrElementName = "Sound/Kensou/StartMostion.wav";
	mciOpenParam_Win.lpstrElementName = "Sound/Kensou/Win.wav";
	mciOpenParam_Die.lpstrElementName = "Sound/Kensou/Die.wav";

	mciOpenParam_StartMostion.lpstrDeviceType = "waveaudio";
	mciOpenParam_Win.lpstrDeviceType = "waveaudio";
	mciOpenParam_Die.lpstrDeviceType = "waveaudio";

	
	this->HitBoxInit();
	this->KeyInit();
	return S_OK;
}

void SieKensou::Release()
{
	effectBackBuffer->Release();
	delete effectBackBuffer;

	skillBackBuffer->Release();
	delete skillBackBuffer;

	midBackBuffer->Release();
	delete midBackBuffer;

	profile->Release();
	delete profile;

	img->Release();
	delete img;
}

void SieKensou::Update()
{
	if (!gameStart)
	{
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpenParam_StartMostion);
		wDeviceID_StartMostion = mciOpenParam_StartMostion.wDeviceID;
		mciSendCommand(wDeviceID_StartMostion, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParam_StartMostion);

		actionframey = STATE_MOTION;
		comtime++;
		if (comtime % 15 == 14)
		{
			comtime = 0;
			actionframex++;

			if (actionframex > 7)
			{
				actionframex = 0;
				actionframey = STATE_STANDING;
				gameStart = true;
				mciSendCommand(wDeviceID_StartMostion, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
			}
		}
	}
	else
	{
		isAction = this->CheckAction();
		
		if (damage >= 400)
		{
			isDead = true;
		}

		if (!isHit)
		{
			this->InputKey();
			
			if (!launchSkillA && !SkillOnHit &&!launchSkillB)
			{
				this->MakeSkill();
			}
			
		}

		if (currentframey == STATE_STANDING && !isAction && !isDead)
		{
			comtime++;
			if (comtime % 10 == 9)
			{
				comtime = 0;
				currentframex++;


				if (currentframex > 7)
				{
					currentframex = 0;
				}
			}
		}
		isSkill = this->CheckIsSkill();
		if (!isAction && !isSkill && !isLaunch)
		{
			if (isReverse)
			{
				direction = true;
			}

			else
			{
				direction = false;
			}
		}
		this->KeyInit();
		this->ActionUpdate();
		this->MakeHitbox();
		gameOver = this->CheckGameOver();
	
	}
	
}

void SieKensou::Render(HDC hdc)
{
	
	//char sZtext[60];
	if (img)
	{
		//RenderRect(hdc, hitbox.bodyPos.x, hitbox.bodyPos.y, hitbox.bodyWidth, hitbox.bodyHeight);
		//RenderRect(hdc, hitbox.legPos.x, hitbox.legPos.y, hitbox.legWidth, hitbox.legHeight);
		//RenderRect(hdc, hitbox.skillAPos.x, hitbox.skillAPos.y, hitbox.skillAWidth, hitbox.skillAHeight);
		//RenderRect(hdc, hitbox.guardPos.x, hitbox.guardPos.y, hitbox.guardWidth, hitbox.guardHeight);
		
		if (isHit && !isDead)
			img->FrameRender(midBackBuffer->GetMemDC(), 0, 0, hitframex, hitframey, 2, direction);

		else if (rightPunch || leftKick || isDead || isWin || !gameStart || isSkill || isGuard ||roll)
			img->FrameRender(midBackBuffer->GetMemDC(), 0, 0, actionframex, actionframey, 2, direction);

		else
			img->FrameRender(midBackBuffer->GetMemDC(), 0, 0, currentframex, currentframey, 2, direction);

		
			
	//여기 아래는 실험용랜더	
	}

	if ((launchSkillA||launchSkillB) &&!isDead&&!isWin&&!SkillOnHit)
		img->FrameRender(skillBackBuffer->GetMemDC(), 0, 0, skillframex, skillframey, 2, direction);

	if ((SkillOnHit|| isHit || isGuard)&& !isDead && !isWin)
	{
		img->FrameRender(effectBackBuffer->GetMemDC(), 0, 0, effectframex, effectframey, 2, direction);
	}

	if (playerNum==1)
	{
		if (profile)
		{
			profile->Render(hdc, 110, 30);
		}
	}
		
	else
	{
		if (profile)
		{
			profile->Render(hdc, WINSIZE_X - 220, 30);
		}
	}
	

	/*if (isReverse)
	{
		wsprintf(sZtext, "skillA : %d", skillB);
		TextOut(hdc, 100, 200, sZtext, strlen(sZtext));
		wsprintf(sZtext, "launchskillA : %d", launchSkillB);
		TextOut(hdc, 100, 100, sZtext, strlen(sZtext));
		wsprintf(sZtext, "islaunch : %d", isLaunch);
		TextOut(hdc, 100, 150, sZtext, strlen(sZtext));
		wsprintf(sZtext, "commandB : %d", commandB);
		TextOut(hdc, 100, 250, sZtext, strlen(sZtext)); 
		wsprintf(sZtext, "keyback : %d", keyBackCheck);
		TextOut(hdc, 100, 300, sZtext, strlen(sZtext));
	}*/
	
	//RenderRect(hdc, hitbox.attackPos.x, hitbox.attackPos.y, hitbox.rightpunchWidth, hitbox.rightpunchHeight);
		
	//RenderRect(hdc, hitbox.attackPos.x, hitbox.attackPos.y, hitbox.leftkickWidth, hitbox.leftkickHeight);
	
	//RenderRect(hdc, tempenemy.pos.x, tempenemy.pos.y, tempenemy.width, tempenemy.height);
	//RenderRect(hdc, tempenemy.enemyattackx, tempenemy.enemyattacky, tempenemy.enemywidth, tempenemy.enemyheigth);
	
	//미드 백버퍼에 캐릭터 그려놓을걸 다시 배경, UI가 다 그려진 백버퍼로 옮기기 위한 함수
	
	midBackBuffer->FrameRender(hdc, posX, posY,1);
	if ((launchSkillA || launchSkillB) && !SkillOnHit && !isDead && !isWin)
	{
		skillBackBuffer->FrameRender(hdc, skillposX, skillposY);
	}
	
	
	if ((SkillOnHit  || isGuard || (!isSkillIsHit && isHit)) && !isDead && !isWin)
	{
		
		effectBackBuffer->FrameRender(hdc, effectpos.x, effectpos.y);
		
	}
	
	
}
//키입력부분
void SieKensou::InputKey()
{
	if (!gameOver)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(key.sitDown) && !isAction && !isGuard && !launchSkillA && !launchSkillB)
		{
			if (!keyFowardCheck && !keyBackCheck && !launchSkillA &&!launchSkillB)
			{
				keyDownCheck = true;
			}

			isGuarded = false;
				
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown(key.rightPunch) && !leftKick &&!isGuard)
		{
			
			rightPunch = true;
			goFoward = false;
			goBackward = false;
			comtime = 0;
			actiontime = 0;
			currentframey = STATE_RIGHTPUNCH;
			actionframey = STATE_RIGHTPUNCH;
			
			

		}

		else if (KeyManager::GetSingleton()->IsOnceKeyDown(key.leftKick) && !rightPunch  && !isGuard)
		{

			leftKick = true;
			goFoward = false;
			goBackward = false;
			comtime = 0;
			actiontime = 0;
			currentframey = STATE_RIGHTPUNCH;
			actionframey = STATE_LEFTKICK;
		}

		else if (KeyManager::GetSingleton()->IsOnceKeyDown(key.goRight) && !isAction)
		{
			if (!isAction)
			{
				if (isReverse)
				{
					if ((keyDownCheck||keyBackCheck) && !launchSkillA && !launchSkillB)
					{
						keyFowardCheck = true;
						isGuarded = false;
					}
					
					goFoward = true;
					comtime = 0;
					currentframex = 0;
				}

				else
				{
					if (!keyFowardCheck && !launchSkillA && !launchSkillB)
					{
						keyBackCheck = true;
						isGuarded = false;
					}

					goBackward = true;
					comtime = 0;
					currentframex = 0;
										
				}

			}
		}

		else if (KeyManager::GetSingleton()->IsOnceKeyDown(key.goLeft) && !isAction)
		{
			if (!isAction)
			{
				if (isReverse)
				{
					if (!keyFowardCheck && !launchSkillA && !launchSkillB)
					{
						keyBackCheck = true;
						isGuarded = false;
					}

					goBackward = true;
					comtime = 0;
					currentframex = 0;


				}

				else
				{
					if ((keyDownCheck || keyBackCheck) && !launchSkillA && !launchSkillB)
					{
						keyFowardCheck = true;
						isGuarded = false;
					}
						
					goFoward = true;
					comtime = 0;
					currentframex = 0;
				}

			}
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown(key.goRight) && !isAction)
		{


			comtime++;

			posX += speed;
			if (posX >= WINSIZE_X - 260)
			{
				posX = WINSIZE_X - 260;
			}



			if (isReverse)
				currentframey = STATE_GOFOWARD;
			else
			{
				hitbox.guardWidth = (120 - 25)*scale;
				hitbox.guardHeight = (112 - 26)*scale; //112
				hitbox.guardPos.x = posX + 25 * scale;
				hitbox.guardPos.y = posY + 26 * scale;
				currentframey = STATE_GOBACKWARD;
			}
				
			

			if (comtime % 10 == 9)
			{
				comtime = 0;
				currentframex++;


				if (currentframex == 7)
				{
					currentframex = 0;
				}
			}
		}

		else if (KeyManager::GetSingleton()->IsStayKeyDown(key.goLeft) && !isAction)
		{

			comtime++;

			posX -= speed;
			if (posX <= 0)
			{
				posX = 0;
			}
			if (isReverse)
			{
				hitbox.guardWidth = (120 - 25)*scale;
				hitbox.guardHeight = (112 - 26)*scale;
				hitbox.guardPos.x = posX - 25 * scale + (width*scale / maxFrameX) - hitbox.guardWidth;
				hitbox.guardPos.y = posY + 26 * scale;
				currentframey = STATE_GOBACKWARD;
			}
				
			else
			{
				currentframey = STATE_GOFOWARD;
			}
				

			if (comtime % 10 == 9)
			{
				comtime = 0;
				currentframex++;


				if (currentframex == 7)
				{
					currentframex = 0;
				}
			}
		}

		else if (KeyManager::GetSingleton()->IsStayKeyDown(key.sitDown) && !launchSkillA && !launchSkillB)
		{
			comtime++;
						
			currentframey = 8;
			currentframex = 4;

			sitDown = true;

			if ((sitDown && leftKick) && !roll && !isSkill && !isLaunch)
			{
				roll = true;
				if (direction)
				{
					actionframex = 6;
				}

				else
				{
					actionframex = 8;
				}
			}

			if ((sitDown && rightPunch) && !roll && !isSkill && !isLaunch)
			{
				roll = true;
				if (direction)
				{
					actionframex = 8;
				}

				else
				{
					actionframex = 6;
				}
			}
			

		}

		if (KeyManager::GetSingleton()->IsOnceKeyUp(key.goRight) && !isAction)
		{
			HitBoxInit();

			if (isReverse)
			{
				goFoward = false;
				currentframex = 0;
				currentframey = STATE_STANDING;
				comtime = 0;
			}

			else
			{
				goBackward = false;
				currentframex = 0;
				currentframey = STATE_STANDING;
				comtime = 0;
			}

		}

		if (KeyManager::GetSingleton()->IsOnceKeyUp(key.goLeft) && !isAction)
		{
			HitBoxInit();

			if (isReverse)
			{
				goBackward = false;
				currentframex = 0;
				currentframey = STATE_STANDING;
				comtime = 0;
			}

			else
			{
				goFoward = false;
				currentframex = 0;
				currentframey = STATE_STANDING;
				comtime = 0;
			}
		}

		if (KeyManager::GetSingleton()->IsOnceKeyUp(key.sitDown))
		{
			currentframex = 0;
			currentframey = 0;
		}
	}
	

}
//동작을 하고있나 안하고있나 체크
bool SieKensou::CheckAction()
{
	

	if (rightPunch || leftKick || isHit || isDead || isSkill||isGuard)
		return true;
	else
		return false;

	
}
//공격활성화 애니메이션 함수
void SieKensou::ActionUpdate()
{
	if (!gameOver)
	{
		if (roll && !isHit &&!isSkill) //&&!isLaunch &&!commandA &&!commandB)
		{
			actionframey = 8;
			actiontime++;
		
			MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
			if (rightPunch)
			{

				posX -= 6;
				if (posX < 0)
				{
					posX = 0;
				}
				if (direction)
				{
					if (actiontime % 8 == 7)
					{
						actiontime = 0;
						actionframex--;

						if (actionframex < 6)
						{
							MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
							actionframex = 0;
							currentframex = 0;
							actionframey = STATE_STANDING;
							currentframey = STATE_STANDING;
							roll = false;
							leftKick = false;
							rightPunch = false;
						}
					}
				}

				else
				{
					if (actiontime % 10 == 9)
					{
						actiontime = 0;
						actionframex++;

						if (actionframex > 8)
						{
							MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
							actionframex = 0;
							currentframex = 0;
							actionframey = STATE_STANDING;
							currentframey = STATE_STANDING;
							roll = false;
							leftKick = false;
							rightPunch = false;
						}
					}
				}
			}
			else if (leftKick)
			{
				posX += 6;
				if (posX > WINSIZE_X - 150 * scale)
				{
					posX = WINSIZE_X - 150 * scale;
				}

				if (direction)
				{
					if (actiontime % 8 == 7)
					{
						actiontime = 0;
						actionframex++;

						if (actionframex > 8)
						{
							MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
							actionframex = 0;
							currentframex = 0;
							actionframey = STATE_STANDING;
							currentframey = STATE_STANDING;
							roll = false;
							leftKick = false;
							rightPunch = false;
						}
					}
				}

				else
				{
					if (actiontime % 10 == 9)
					{
						actiontime = 0;
						actionframex--;


						if (actionframex < 6)
						{
							MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
							actionframex = 0;
							currentframex = 0;
							actionframey = STATE_STANDING;
							currentframey = STATE_STANDING;
							roll = false;
							leftKick = false;
							rightPunch = false;
						}
					}
				}


			}



		}
		if (rightPunch && !isHit &&!skillA && !skillB &&!roll &&!commandA)
		{
			actiontime++;
			if (actiontime % 6 == 5)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex == 4)
				{
					hitbox.attackPos.x = 0;
					hitbox.attackPos.y = 0;
				}

				if (actionframex > 7)
				{
					actionframex = 0;
					currentframex = 0;
					actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					rightPunch = false;
				}
			}
		}

		if (leftKick && !isHit &&!roll)
		{
			actiontime++;
			if (actiontime % 10 == 5)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex == 5)
				{
					hitbox.attackPos.x = 0;
					hitbox.attackPos.y = 0;
				}

				if (actionframex > 9)
				{
					actionframex = 0;
					currentframex = 0;
					actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					leftKick = false;
				}
			}
		}

		if (skillA && !isHit)
		{
			actionframey = 9;
			actiontime++;
			
			hitbox.skillAPos.x = 0;
			hitbox.skillAPos.y = 0;
			hitbox.skillAWidth = 0;
			hitbox.skillAHeight = 0;

			MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
			if (isHit)
			{
				launchSkillA = false;
				SkillOnHit = false;
				skillA = false;
				commandA = false;
			}

			if (actiontime % 6 == 5)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex == 5)
				{
					if (direction)
					{
						skillposX = posX - 32 * scale - 65*scale + (width*scale / maxFrameX);
						skillposY = posY + 97 * scale - 75*scale;
						skillframex = 0;

					}

					else
					{
						skillposX = posX + 32 * scale - 65 * scale;
						skillposY = posY + 97 * scale - 75 * scale;
						skillframex = 0;
					}
					
				}
				if (actionframex > 9)
				{
					actionframex = 0;
					currentframex = 0;
					actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					rightPunch = false;
					skillA = false;
					isSkill = false;
					commandA = false;
				}
			}
		}

		if (launchSkillA)
		{
			skillframey = 10;
			skilltime++;

			if (isHit)
			{
				launchSkillA = false;
				SkillOnHit = false;
				skillA = false;
				commandA = false;
			}

			if (direction)
			{
				skillposX += skillspeed;
				if (skillposX > WINSIZE_X)
				{
					launchSkillA = false;
					SkillOnHit = false;
					skillA = false;
					commandA = false;
				}
			}
						
			else
			{
				skillposX -= skillspeed;
				if (skillposX < 0)
				{
					launchSkillA = false;
					SkillOnHit = false;
					skillA = false;
					commandA = false;
				}
			}
			
			if (isGuarded)
			{
				hitbox.skillAWidth = 0;
				hitbox.skillAHeight = 0;
				launchSkillA = false;
				commandA = false;
			}
			if (skilltime % 5 == 4)
			{
				skilltime = 0;
				skillframex++;

				
				if (skillframex > 7)
				{
					skillframex = 0;
				}
			}
		}

		if (skillB && !isHit)
		{
			actionframey = 7;
			actiontime++;

			hitbox.skillAPos.x = 0;
			hitbox.skillAPos.y = 0;
			hitbox.skillAWidth = 0;
			hitbox.skillAHeight = 0;

			
			if (isHit)
			{
				launchSkillB = false;
				SkillOnHit = false;
				skillB = false;
				commandB = false;
			}

			if (actionframex == 9)
			{
				if (actionframex == 9)
				{
					if (direction)
					{
						skillposX = posX + 50 * scale;
						skillposY = posY;
						skillframex = 0;

					}

					else
					{
						skillposX = posX - 50 * scale;
						skillposY = posY;
						skillframex = 0;
					}
				}
			}
			if (actiontime % 10 == 9)
			{
				actiontime = 0;
				actionframex++;

				

				
				if (actionframex > 11)
				{
					actionframex = 11;
					currentframex = 0;
					//actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					rightPunch = false;
					actiontime = 0;
					
				}
			}
		}

		if (launchSkillB)
		{
			skillframey = 12;
			skilltime++;
			commandB = false;
			
			if (isHit)
			{
				launchSkillB = false;
				SkillOnHit = false;
				skillB = false;
			}

			if (direction)
			{
				skillposX += 5;
				if (skillposX > WINSIZE_X)
				{
					launchSkillB = false;
					SkillOnHit = false;
					skillB = false;
					commandB = false;
				}
			}

			else
			{
				skillposX -= 5;
				if (skillposX < 0)
				{
					launchSkillB = false;
					SkillOnHit = false;
					skillB = false;
					commandB = false;
				}
			}

			if (isGuarded)
			{
				hitbox.skillAWidth = 0;
				hitbox.skillAHeight = 0;
				launchSkillB = false;
				skillB = false;
				commandB = false;
			}

			if (skilltime % 5 == 4)
			{
				skilltime = 0;
				skillframex++;


				if (skillframex > 11)
				{
					skillframex = 0;
					launchSkillB = false;
					skillB = false;
					commandB = false;
				}
			}
		}

		if (SkillOnHit && !isGuarded)
		{
			
			if (launchSkillA)
			{
				effectframex = 0;
				effectpos.x = skillposX;
				effectpos.y = WINSIZE_Y - 170*scale;
				effectframey = 11;
			}

			if (launchSkillB)
			{
				effectframex = 0;
				effectpos.x = skillposX;
				effectpos.y = WINSIZE_Y - 170 * scale;
				effectframey = 13;
			}

			launchSkillA = false;
			skillA = false;
			isSkill = false;

			hitbox.skillAPos.x = 0;
			hitbox.skillAPos.y = 0;
			hitbox.skillAWidth = 0;
			hitbox.skillAHeight = 0;

			
			if (isHit)
			{
				launchSkillA = false;
				SkillOnHit = false;
				skillA = false;
				commandA = false;
			}

			effecttime++;

			if (isHit)
			{
				launchSkillB = false;
				SkillOnHit = false;
				skillB = false;
				commandB = false;
			}

			if (effectframey == 11)
			{
				if (effecttime % 5 == 4)
				{
					effecttime = 0;
					effectframex++;


					if (effectframex > 10)
					{
						launchSkillA = false;
						SkillOnHit = false;
						commandA = false;
						skillframex = 0;
						effectframex = 0;

					}
				}
			}

			else if (effectframey == 13)
			{
				if (effecttime % 5 == 4)
				{
					effecttime = 0;
					effectframex++;


					if (effectframex > 7)
					{
						launchSkillB = false;
						SkillOnHit = false;
						commandB = false;
						skillframex = 0;
						effectframex = 0;

					}
				}
			}
			
		}

		if (isHit)
		{
			roll = false;
			isGuard = false;
			hitframey = 5;
			actionframey = STATE_STANDING;
			currentframex = 0;
			currentframey = STATE_STANDING;
			actiontime = 0;
			hittime++;
			comtime = 0;
			rightPunch = false;
			leftKick = false;

			this->HitBoxInit();

			if (isReverse)
			{
				posX -= 2;
				if (posX < 0)
				{
					posX = 0;
				}
			}
				
			
			else
			{
				posX += 2;
				if (posX > WINSIZE_X - 130 * 2)
				{
					posX = WINSIZE_X - 130 * 2;
				}

			}
				
			
						
			if (!isSkillIsHit)
			{
				if (effecttime == 0)
					effectframex = 4;
				effecttime++;
				effectframey = 5;

				if (direction)
				{
					effectpos.x = posX - 115 * scale + width * scale / maxFrameX;
					effectpos.y = posY - 10 * scale;
				}

				else
				{
					effectpos.x = posX-15*scale;
					effectpos.y = posY-10*scale;
				}

				if (hittime % 10 == 9)
				{
					effectframex++;
					if (effectframex > 8)
					{
						effectframex = 0;
					}
				}
			}
			

			if (hittime % 10 == 9)
			{
				hittime = 0;
				hitframex++;

				if (hitframex > 3)
				{
					hitframex = 0;
					hitframey = STATE_STANDING;
					currentframex = 0;
					actionframex = 0;
					actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					effecttime = 0;
					isHit = false;
					isSkillIsHit = false;
					skillA = false;
					skillB = false;
					launchSkillB = false;
				}
			}
		}

		else if (isGuard)
		{
			
			hitframey = 0;
			hitframex = 0;
			actionframey = 8;
			currentframex = 0;
			currentframey = STATE_STANDING;
			actiontime++;
			if (effecttime == 0)
				effectframex = 8;
			effecttime++;
			effectframey = 6;
			comtime = 0;
			hittime = 0;

			if (direction)
			{
				effectpos.x = posX - 115 * scale + width*scale / maxFrameX;
				effectpos.y = posY -10*scale;
			}

			else
			{
				effectpos.x = posX - 15 * scale;
				effectpos.y = posY-10*scale;
			}
			
			
			if (actiontime % 8 == 7)
			{
				effectframex++;
				
				if (effectframex > 11)
				{
					effectframex = 0;
				}
			}
			
			if (actiontime % 8 == 7)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex > 3)
				{
					actionframex = 0;
					hitframey = STATE_STANDING;
					actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					effecttime = 0;
					isGuard = false;
					isHit = false;
					goBackward = false;
				}
			}
		}

		
	}
	else
	{
		if (isDead)
		{
			hitframex = 0;
			hitframey = STATE_STANDING;
			actionframey = 6;
			currentframex = 0;
			currentframey = STATE_STANDING;
			actiontime++;

			this->HitBoxInit();

			if (actiontime % 10 == 9)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex > 7)
				{
					actionframex = 7;
					currentframex = 0;

				}
			}
		}
		
		if (isWin)
		{
			hitframex = 0;
			hitframey = STATE_STANDING;
			actionframey = 7;
			currentframex = 0;
			currentframey = STATE_STANDING;
			actiontime++;

			this->HitBoxInit();

			if (actiontime % 13 == 12)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex > 12)
				{
					actionframex = 12;
					currentframex = 0;

				}
			}
		}
	}
}
//히트박스 만드는 함수
void SieKensou::MakeHitbox()
{
	if (isHit)
		this->HitBoxInit();
	else
	{
		if (direction) // 캐릭터가 왼쪽에 있을 때 
		{
			if (rightPunch&&actionframey == 3) // 오른주먹
			{
				if (actionframex == 0)
				{
					MakeHitBoxPos(56, 63, 93, 101, 32, 102, 99, 147);
				}

				if (actionframex == 1)
				{
					MakeHitBoxPos(56, 63, 93, 101, 32, 102, 99, 147);
				}

				if (actionframex == 2)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}

				if (actionframex == 3)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);

					hitbox.attackPos.x = posX + (width*scale / maxFrameX) - 17 * scale - hitbox.rightpunchWidth;
					hitbox.attackPos.y = posY + 54*scale;
				}

				if (actionframex == 4)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}

				if (actionframex == 5)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}

				if (actionframex == 6)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}

				if (actionframex == 7)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}

				if (actionframex == 8)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}


			}
			else if (leftKick&&actionframey == 4) // 왼발
			{
				if (actionframex == 0)
				{
					MakeHitBoxPos(49, 63, 82, 102, 39, 102, 94, 147);
				}

				if (actionframex == 1)
				{
					MakeHitBoxPos(49, 63, 82, 102, 39, 102, 94, 147);
				}

				if (actionframex == 2)
				{
					MakeHitBoxPos(49, 63, 82, 102, 39, 102, 94, 147);
				}

				if (actionframex == 3)
				{
					MakeHitBoxPos(49, 63, 82, 102, 39, 102, 94, 147);
				}

				if (actionframex == 4)
				{
					MakeHitBoxPos(50, 51, 88, 149, 50, 51, 88, 149);

					hitbox.attackPos.x = posX + (width*scale / maxFrameX) - 17 *scale - hitbox.leftkickWidth;
					hitbox.attackPos.y = posY + 48 *scale;
				}

				if (actionframex == 5)
				{
					MakeHitBoxPos(33, 53, 104, 148, 33, 53, 104, 148);
				}

				if (actionframex == 6)
				{
					MakeHitBoxPos(32, 47, 94, 149, 32, 47, 94, 149);
				}

				if (actionframex == 7)
				{
					MakeHitBoxPos(39, 47, 98, 148, 39, 47, 98, 148);
				}

				if (actionframex == 8)
				{
					MakeHitBoxPos(39, 55, 89, 148, 39, 55, 89, 148);
				}

				if (actionframex == 9)
				{
					MakeHitBoxPos(39, 55, 89, 148, 39, 55, 89, 148);
				}

				if (actionframex == 10)
				{
					MakeHitBoxPos(37, 62, 106, 150, 37, 62, 106, 150);
				}

			}

			if (currentframey == 0) //숨쉬기
			{
				MakeHitBoxPos(51, 62, 103, 104, 42, 104, 112, 141);
			}

			if (currentframey == 1) //앞으로이동
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(38, 56, 102, 103, 34, 102, 100, 150);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(42, 52, 104, 103, 44, 103, 105, 150);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(49, 45, 103, 94, 56, 94, 89, 148);
				}

				if (currentframex == 3)
				{
					MakeHitBoxPos(47, 45, 103, 94, 56, 94, 94, 150);
				}

				if (currentframex == 4)
				{
					MakeHitBoxPos(43, 43, 101, 91, 48, 91, 90, 150);
				}

				if (currentframex == 5)
				{
					MakeHitBoxPos(48, 52, 104, 108, 49, 108, 100, 150);
				}

				if (currentframex == 6)
				{
					MakeHitBoxPos(50, 55, 103, 112, 44, 112, 106, 150);
				}


			}
			if (currentframey == 2) // 뒤로이동
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(43, 59, 102, 106, 38, 106, 104, 150);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(49, 57, 100, 103, 40, 103, 106, 150);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(48, 56, 100, 102, 41, 102, 98, 148);
				}

				if (currentframex == 3)
				{
					MakeHitBoxPos(51, 46, 97, 100, 48, 100, 88, 150);
				}

				if (currentframex == 4)
				{
					MakeHitBoxPos(36, 41, 88, 93, 46, 93, 77, 150);
				}

				if (currentframex == 5)
				{
					MakeHitBoxPos(39, 46, 89, 93, 44, 93, 83, 150);
				}

				if (currentframex == 6)
				{
					MakeHitBoxPos(45, 45, 97, 97, 40, 97, 97, 150);
				}

			}
			if (launchSkillA && !SkillOnHit)
			{
				hitbox.skillAPos.x = skillposX - 93 * scale + (width*scale / maxFrameX);
				hitbox.skillAPos.y = skillposY + 48 * scale;
				hitbox.skillAWidth = (93 - 37)*scale;
				hitbox.skillAHeight = (103 - 48)*scale;
			}

			if (launchSkillB && !SkillOnHit &&(skillframex > 6 && skillframex < 10))
			{
				hitbox.skillAPos.x = skillposX - 93 * scale + (width*scale / maxFrameX);
				hitbox.skillAPos.y = skillposY + 24 * scale;
				hitbox.skillAWidth = (120 - 37)*scale;
				hitbox.skillAHeight = (130 - 48)*scale;
			}
		}

		else
		{

			if (rightPunch&&actionframey == 3) // 오른주먹
			{
				if (actionframex == 0)
				{
					MakeHitBoxPos(56, 63, 93, 101, 32, 102, 99, 147);
				}

				if (actionframex == 1)
				{
					MakeHitBoxPos(56, 63, 93, 101, 32, 102, 99, 147);
				}

				if (actionframex == 2)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}

				if (actionframex == 3)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);

					hitbox.attackPos.x = posX + 17 * scale;
					hitbox.attackPos.y = posY + 54 * scale;
				}

				if (actionframex == 4)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}

				if (actionframex == 5)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}

				if (actionframex == 6)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}

				if (actionframex == 7)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}

				if (actionframex == 8)
				{
					MakeHitBoxPos(50, 61, 89, 101, 39, 101, 97, 148);
				}


			}
			else if (leftKick&&actionframey == 4) // 왼발
			{
				if (actionframex == 0)
				{
					MakeHitBoxPos(49, 63, 82, 102, 39, 102, 94, 147);
				}

				if (actionframex == 1)
				{
					MakeHitBoxPos(49, 63, 82, 102, 39, 102, 94, 147);
				}

				if (actionframex == 2)
				{
					MakeHitBoxPos(49, 63, 82, 102, 39, 102, 94, 147);
				}

				if (actionframex == 3)
				{
					MakeHitBoxPos(49, 63, 82, 102, 39, 102, 94, 147);
				}

				if (actionframex == 4)
				{
					MakeHitBoxPos(50, 51, 88, 149, 50, 51, 88, 149);

					hitbox.attackPos.x = posX + 17 * scale;
					hitbox.attackPos.y = posY + 48 * scale;
				}

				if (actionframex == 5)
				{
					MakeHitBoxPos(33, 53, 104, 148, 33, 53, 104, 148);
				}

				if (actionframex == 6)
				{
					MakeHitBoxPos(32, 47, 94, 149, 32, 47, 94, 149);
				}

				if (actionframex == 7)
				{
					MakeHitBoxPos(39, 47, 98, 148, 39, 47, 98, 148);
				}

				if (actionframex == 8)
				{
					MakeHitBoxPos(39, 55, 89, 148, 39, 55, 89, 148);
				}

				if (actionframex == 9)
				{
					MakeHitBoxPos(39, 55, 89, 148, 39, 55, 89, 148);
				}

				if (actionframex == 10)
				{
					MakeHitBoxPos(37, 62, 106, 150, 37, 62, 106, 150);
				}

			}

			if (currentframey == 0)
			{
				MakeHitBoxPos(56, 60, 101, 104, 40, 104, 112, 141);
			}

			if (currentframey == 1)
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(42, 56, 106, 103, 34, 102, 100, 150);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(48, 52, 104, 103, 44, 103, 105, 150);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(49, 45, 103, 94, 56, 94, 89, 148);
				}

				if (currentframex == 3)
				{
					MakeHitBoxPos(47, 45, 103, 94, 56, 94, 94, 150);
				}

				if (currentframex == 4)
				{
					MakeHitBoxPos(43, 43, 101, 91, 48, 91, 90, 150);
				}

				if (currentframex == 5)
				{
					MakeHitBoxPos(48, 52, 104, 108, 49, 108, 100, 150);
				}

				if (currentframex == 6)
				{
					MakeHitBoxPos(50, 55, 103, 112, 44, 112, 106, 150);
				}


			}
			if (currentframey == 2)
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(43, 59, 102, 106, 38, 106, 104, 150);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(49, 57, 100, 103, 40, 103, 106, 150);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(48, 56, 100, 102, 41, 102, 98, 148);
				}
				if (currentframex == 3)
				{
					MakeHitBoxPos(51, 46, 97, 100, 48, 100, 88, 150);
				}
				if (currentframex == 4)
				{
					MakeHitBoxPos(36, 41, 88, 93, 46, 93, 77, 150);
				}
				if (currentframex == 5)
				{
					MakeHitBoxPos(39, 46, 89, 93, 44, 93, 83, 150);
				}
				if (currentframex == 6)
				{
					MakeHitBoxPos(45, 45, 97, 97, 40, 97, 97, 150);
				}
			}

			if (launchSkillA && !SkillOnHit)
			{
				hitbox.skillAPos.x = skillposX + 37 * scale;
				hitbox.skillAPos.y = skillposY + 48 * scale;
				hitbox.skillAWidth = (93 - 36)*scale;
				hitbox.skillAHeight = (103 - 48)*scale;
			}

			if (launchSkillB && !SkillOnHit &&(skillframex>6 && skillframex <10))
			{
				hitbox.skillAPos.x = skillposX + 37 * scale;
				hitbox.skillAPos.y = skillposY + 24 * scale;
				hitbox.skillAWidth = (120 - 36)*scale;
				hitbox.skillAHeight = (130 - 48)*scale;
			}

		}
	}



}
void SieKensou::HitBoxInit()
{
	hitbox.bodyPos.x = 0;
	hitbox.bodyPos.y = 0;
	hitbox.attackPos.x = 0;
	hitbox.attackPos.y = 0;
	hitbox.skillAPos.x = 0;
	hitbox.skillAPos.y = 0;
	hitbox.guardPos.x = -300;
	hitbox.guardPos.y = -300;
	hitbox.rightpunchWidth = 40*scale;
	hitbox.rightpunchHeight = 35 * scale;
	hitbox.leftkickWidth = 50 * scale;
	hitbox.leftkickHeight = 50 * scale;
	hitbox.bodyWidth = 0;
	hitbox.bodyHeight = 0;
	hitbox.legWidth = 0;
	hitbox.legHeight = 0;
	hitbox.skillAWidth = 0;
	hitbox.skillAHeight = 0;
	hitbox.guardWidth = 0;
	hitbox.guardHeight = 0;
}

void SieKensou::KeyInit()
{
	if (playerNum==1)
	{
		key.goRight = 0x4A; // J
		key.goLeft = 0x47; // G
		key.leftKick = 0x53; // S
		key.rightPunch = 0x41; //A
		key.sitDown = 0x48; // H
	}

	else
	{
		key.goRight = VK_RIGHT; 
		key.goLeft = VK_LEFT; 
		key.leftKick = 0xBF; // ?
		key.rightPunch = 0xBE; // .
		key.sitDown = VK_DOWN;
	}
}

void SieKensou::MakeSkill()
{
	if (!launchSkillA)
	{
		this->CheckSkill(keyDownCheck, keyFowardCheck, commandA, rightPunch, skillA);	//처음키 , 다음키, 뱡향키 2개눌렀을때 불값 , 액션키, 저장스킬
	}

	if (!launchSkillA&&skillA&&actionframex == 5)
		launchSkillA = true;

	if (!launchSkillB)
	{
		this->CheckSkill(keyBackCheck, keyFowardCheck, commandB, rightPunch, skillB);							//처음키 , 다음키, 뱡향키 2개눌렀을때 불값 , 액션키, 저장스킬
		if (skillB)
			actionframex = 9;
	}

	
	if (!launchSkillB&&skillB)
	{
		launchSkillB = true;
	}
	
	isLaunch = this->CheckIsLaunch();
}

void SieKensou::MakeHitBoxPos(float bodyx1, float bodyy1, float bodyx2, float bodyy2, float legx1, float legy1, float legx2, float legy2)
{
	if (direction)
	{
		hitbox.bodyWidth = (bodyx2 - bodyx1) * scale;
		hitbox.bodyHeight = (bodyy2 - bodyy1) * scale;
		hitbox.legWidth = (legx2 - legx1) * scale;
		hitbox.legHeight = (legy2 - legy1) * scale;
		hitbox.bodyPos.x = posX - bodyx1 * scale +(width*scale / maxFrameX) - hitbox.bodyWidth;
		hitbox.bodyPos.y = posY + bodyy1 * scale;
		hitbox.legPos.x = posX - legx1 * scale +(width*scale / maxFrameX) - hitbox.legWidth;
		hitbox.legPos.y = posY + legy1 * scale;
	}

	else
	{
		hitbox.bodyWidth = (bodyx2 - bodyx1) * scale;
		hitbox.bodyHeight = (bodyy2 - bodyy1) * scale;
		hitbox.legWidth = (legx2 - legx1) * scale;
		hitbox.legHeight = (legy2 - legy1) * scale;
		hitbox.bodyPos.x = posX + bodyx1 * scale;
		hitbox.bodyPos.y = posY + bodyy1 * scale;
		hitbox.legPos.x = posX + legx1 * scale;
		hitbox.legPos.y = posY + legy1 * scale;

	}
}
// 커맨드 함수
bool SieKensou::CheckCommand(bool &firstkey, bool &secondkey, bool commnad)
{
	bool checkcommnad=false;
	if (firstkey)
	{
		if (firstkey&&secondkey && !commnad)
		{
			commandtime = 0;
			firstkey = false;
			secondkey = false;
			checkcommnad = true;
		}

		else
		{
			commandtime++;
			if (commandtime % 20 == 19)
			{
				checkcommnad = false;
				firstkey = false;
				commandtime = 0;
			}
		}

	}

	return checkcommnad;
	
}

bool SieKensou::MakeCommand(bool movecommand, bool actioncommnad)
{
	if (movecommand && actioncommnad)
	{
		return true;
	}

	else
	{
		return false;
	}
}

void SieKensou::CommandTimeCheck(bool & command)
{
	if (command)
	{
		commandtime++;
		if (commandtime % 20 == 19)
		{
			commandtime = 0;
			command = false;
		}
	}
}

void SieKensou::CheckSkill(bool & firstkey, bool & secondky, bool & command, bool & actioncommand, bool&skillcommand)
{
	CommandTimeCheck(secondky);
	if (!command)
		command = this->CheckCommand(firstkey, secondky, command);
	if (command)
		CommandTimeCheck(command);
	if (!skillcommand)
		skillcommand = this->MakeCommand(command, actioncommand);
}

bool SieKensou::CheckIsLaunch()
{
	if (launchSkillA || launchSkillB)
		return true;
	else
		return false;
}

bool SieKensou::CheckIsSkill()
{
	if (skillA || skillB)
		return true;
	else
		return false;
}

bool SieKensou::CheckGameOver()
{
	if (isDead || isWin)
	{
		if (isWin)
		{
			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpenParam_Win);
			wDeviceID_Win = mciOpenParam_Win.wDeviceID;
			mciSendCommand(wDeviceID_Win, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParam_Win);
		}
		else if (isDead)
		{
			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpenParam_Die);
			wDeviceID_Die = mciOpenParam_Die.wDeviceID;
			mciSendCommand(wDeviceID_Die, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParam_Die);
		}

		return true;
	}
	else
		return false;
}

SieKensou:: SieKensou()
{
}

SieKensou::~SieKensou()
{
}
