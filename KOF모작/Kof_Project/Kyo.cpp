#include "Kyo.h"
#include "Image.h"
#include "macroFunction.h"

HRESULT Kyo::Init()
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
	height = 1950;
	maxFrameX = 12;
	maxFrameY = 13;
	skillposX = 0;
	skillposY = 0;
	skillpos2X = 0;
	skillpos2Y = 0;

	img = new Image();
	img->Init("Image/Kyo sprite sheet.bmp", posX, posY, width, height, maxFrameX, maxFrameY, true, RGB(255, 0, 255));

	//신경안쓰셔도됩니다
	profile = new Image();
	profile->Init("Image/kyo profile.bmp", 103, 96, true, RGB(255, 0, 255));

	//반전시키기위해 백버퍼를 하나 더 만듬
	midBackBuffer = new Image();
	midBackBuffer->Init(260, 300, true, RGB(255, 0, 255));

	skillBackBuffer = new Image();
	skillBackBuffer->Init(260, 300, true, RGB(255, 0, 255));

	skillBackBuffer2 = new Image();
	skillBackBuffer2->Init(260, 300, true, RGB(255, 0, 255));

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
	damage = 0;
	insdamage = 0;
	skillspeed = 2;
	effectpos.x = -500;
	effectpos.y = -500;

	goFoward = false;
	goBackward = false;
	rightPunch = false;
	leftKick = false;
	isAction = false;
	isDead = false;
	isWin = false;
	gameStart = false;
	keyDownCheck = false;
	keyFowardCheck = false;
	commandA = false;
	skillA = false;
	isSkill = false;
	launchSkillA = false;
	isGuard = false;
	isSkillIsHit = false;
	gameOver = false;
	skillB = false;
	launchSkillB = false;
	keyBackCheck = false;
	sitDown = false;
	commandB = false;
	direction = false;

	comtime = 0;
	hittime = 0;
	actiontime = 0;
	commandtime = 0;
	speed = 4;

	scale = 2;

	skillpos2X = 0;
	skillpos2Y = 0;
	theta[0] = 0;
	theta[1] = 0;
	skilldirect = false;

	mciOpenParam_StartMostion.lpstrElementName = "Sound/Kyo/StartMostion.wav";
	mciOpenParam_Win.lpstrElementName = "Sound/Kyo/Win.wav";
	mciOpenParam_Die.lpstrElementName = "Sound/Kyo/Die.wav";

	mciOpenParam_StartMostion.lpstrDeviceType = "waveaudio";
	mciOpenParam_Win.lpstrDeviceType = "waveaudio";
	mciOpenParam_Die.lpstrDeviceType = "waveaudio";

	this->HitBoxInit();

	return S_OK;
}

void Kyo::Release()
{
	effectBackBuffer->Release();
	delete effectBackBuffer;

	skillBackBuffer2->Release();
	delete skillBackBuffer2;

	skillBackBuffer->Release();
	delete skillBackBuffer;

	midBackBuffer->Release();
	delete midBackBuffer;

	profile->Release();
	delete profile;

	img->Release();
	delete img;
}

void Kyo::Update()
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

			if (!launchSkillA && !SkillOnHit && !launchSkillB)
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


				if (currentframex > 4)
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

void Kyo::Render(HDC hdc)
{
	if (img)
	{
		//RenderRect(hdc, hitbox.skillAPos.x, hitbox.skillAPos.y, hitbox.skillAWidth, hitbox.skillAHeight);
		//RenderRect(hdc, hitbox.bodyPos.x, hitbox.bodyPos.y, hitbox.bodyWidth, hitbox.bodyHeight);
		//RenderRect(hdc, hitbox.legPos.x, hitbox.legPos.y, hitbox.legWidth, hitbox.legHeight);

		if (isHit && !isDead)
			img->FrameRender(midBackBuffer->GetMemDC(), 0, 0, hitframex, hitframey, 2, direction);

		else if (rightPunch || leftKick || isDead || isWin || !gameStart || isSkill || isGuard || roll)
			img->FrameRender(midBackBuffer->GetMemDC(), 0, 0, actionframex, actionframey, 2, direction);

		else
			img->FrameRender(midBackBuffer->GetMemDC(), 0, 0, currentframex, currentframey, 2, direction);

		

		//여기 아래는 실험용랜더	
	}
	if ((launchSkillA || launchSkillB) && !isDead && !isWin)
	{
		img->FrameRender(skillBackBuffer->GetMemDC(), 0, 0, skillframex, skillframey, 2, direction);
		img->FrameRender(skillBackBuffer2->GetMemDC(), 0, 0, skillframex, skillframe2y, 2, direction);
	}

	if ((SkillOnHit || isHit || isGuard) && !isDead && !isWin)
	{
		img->FrameRender(effectBackBuffer->GetMemDC(), 0, 0, effectframex, effectframey, 2, direction);
	}

	if (playerNum == 1)
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




	//RenderRect(hdc, hitbox.attackPos.x, hitbox.attackPos.y, hitbox.rightpunchWidth, hitbox.rightpunchHeight);

	//RenderRect(hdc, hitbox.attackPos.x, hitbox.attackPos.y, hitbox.leftkickWidth, hitbox.leftkickHeight);

	//RenderRect(hdc, tempenemy.pos.x, tempenemy.pos.y, tempenemy.width, tempenemy.height);
	//RenderRect(hdc, tempenemy.enemyattackx, tempenemy.enemyattacky, tempenemy.enemywidth, tempenemy.enemyheigth);

	//미드 백버퍼에 캐릭터 그려놓을걸 다시 배경, UI가 다 그려진 백버퍼로 옮기기 위한 함수
	midBackBuffer->FrameRender(hdc, posX, posY);
	if ((launchSkillA || launchSkillB) && !isDead && !isWin)
	{
		skillBackBuffer->FrameRender(hdc, skillposX, skillposY);
		if(launchSkillA)
			skillBackBuffer2->FrameRender(hdc, skillpos2X, skillpos2Y);
	}

	if ((SkillOnHit || isGuard || (!isSkillIsHit && isHit)) && !isDead && !isWin)
	{

		
		effectBackBuffer->FrameRender(hdc, effectpos.x, effectpos.y);


	}


}
//키입력부분
void Kyo::InputKey()
{
	if (!gameOver)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(key.sitDown) && !isAction)
		{
			if (!keyFowardCheck)
			{
				keyDownCheck = true;
			}

			isGuarded = false;
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown(key.rightPunch) && !leftKick)
		{
			rightPunch = true;
			goFoward = false;
			goBackward = false;
			comtime = 0;
			actiontime = 0;
			currentframey = STATE_RIGHTPUNCH;
			actionframey = STATE_RIGHTPUNCH;

		}

		else if (KeyManager::GetSingleton()->IsOnceKeyDown(key.leftKick) && !rightPunch)
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
					if ((keyDownCheck || keyBackCheck) && !launchSkillA && !launchSkillB)
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

			if (isReverse)
			{
				if (comtime % 10 == 9)
				{
					comtime = 0;
					currentframex++;


					if (currentframex == 4)
					{
						currentframex = 0;
					}
				}
			}

			else
			{
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

			if (isReverse)
			{
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

			else
			{
				if (comtime % 10 == 9)
				{
					comtime = 0;
					currentframex++;


					if (currentframex == 4)
					{
						currentframex = 0;
					}
				}
			}
			
		}

		else if (KeyManager::GetSingleton()->IsStayKeyDown(key.sitDown))
		{
			comtime++;


			currentframey = 8;
			currentframex = 4;

			sitDown = true;

			if ((sitDown && leftKick) && !roll &&!isSkill &&!isLaunch)
			{
				roll = true;
				if (direction)
				{
					actionframex = 5;
				}

				else
				{
					actionframex = 9;
				}
			}

			if ((sitDown && rightPunch) && !roll && !isSkill && !isLaunch)
			{
				roll = true;
				if (direction)
				{
					actionframex = 9;
				}
				
				else
				{
					actionframex = 5;
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
bool Kyo::CheckAction()
{


	if (rightPunch || leftKick || isHit || isDead || isSkill || isGuard)
		return true;
	else
		return false;


}
//공격활성화 애니메이션 함수
void Kyo::ActionUpdate()
{
	if (!isDead&&!isWin )
	{
		if (roll && !isHit && !isSkill && !isLaunch && !commandA && !commandB)
		{
			actionframey = 8;
			actiontime++;

			MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
			
			if (rightPunch && !commandA && !commandB)
			{
								
				posX -= 6;
				if (posX < 0)
				{
					posX = 0;
				}
				if (direction)
				{
					if (actiontime % 10 == 9)
					{
						actiontime = 0;
						actionframex--;

						if (actionframex < 5)
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
					posX = WINSIZE_X-150*scale;
				}
				
				if (direction)
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

				else
				{
					if (actiontime % 10 == 9)
					{
						actiontime = 0;
						actionframex--;


						if (actionframex < 5)
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

		if (rightPunch && !isHit && !skillA && !isGuard && !skillB && !roll&&!commandA &&!commandB)
		{
			actiontime++;
			if (actiontime % 10 == 6)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex == 3)
				{
					hitbox.attackPos.x = 0;
					hitbox.attackPos.y = 0;
				}

				if (actionframex > 4)
				{
					actionframex = 0;
					currentframex = 0;
					actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					rightPunch = false;
				}
			}
		}

		if (leftKick && !isHit && !isGuard && !roll )
		{
			actiontime++;
			if (actiontime % 10 == 6)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex == 4)
				{
					hitbox.attackPos.x = 0;
					hitbox.attackPos.y = 0;
				}

				if (actionframex > 5)
				{
					actionframex = 0;
					currentframex = 0;
					actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					leftKick = false;
				}
			}
		}
		if (skillA && !isHit && !isGuard)
		{
			actionframey = 9;
			actiontime++;
			//MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
			
			hitbox.attackPos.x = 0;
			hitbox.attackPos.y = 0;
			
			if (isHit)
			{
				launchSkillA = false;
				SkillOnHit = false;
				skillA = false;
				commandA = false;
			}
			if (direction)
				posX+=skillspeed;
			else
				posX-= skillspeed;
			
			
			
			if (actionframex <= 5)
			{
				if (actiontime % 4 == 3)
				{
					actiontime = 0;
					actionframex++;

					if (actionframex == 5)
					{
						if (direction)
						{
							skillposX = posX + 30 * scale;
							skillposY = posY;
							skillpos2X = posX - 40 * scale;
							skillpos2Y = posY - 30 * scale;
						}

						else
						{
							skillposX = posX - 30 * scale;
							skillposY = posY;
							skillpos2X = posX + 40 * scale;
							skillpos2Y = posY - 30 * scale;
						}

					}
				}
			}
			
			else if (actionframex > 5)
			{
				if (actiontime % 8 == 7)
				{
					actionframex++;
					if (actionframex > 11)
					{
						actionframex = 0;
						currentframex = 0;
						actionframey = STATE_STANDING;
						currentframey = STATE_STANDING;
						rightPunch = false;
						skillA = false;
						isSkill = false;
						launchSkillA = false;
						commandA = false;
					}
				}

			}
				
			
		}

		if (launchSkillA)
		{
			skillframey = 10;
			skillframe2y = 12;
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
				skillpos2X += skillspeed;
			}
				
			else
			{
				skillposX -= skillspeed;
				skillpos2X -= skillspeed;
			}
			
			if (isGuarded)
			{
				hitbox.skillAWidth = 0;
				hitbox.skillAHeight = 0;
				//launchSkillA = false;
				commandA = false;
			}

			if (skilltime % 5 == 4)
			{
				skilltime = 0;
				skillframex++;


				if (skillframex > 11)
				{
					skillframex = 5;
				}
			}
		}

		if (skillB && !isHit)
		{
			actionframey = 4;
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


			if (actionframex == 6)
			{

				if (direction)
				{
					skillposX = posX + 50 * scale;
					skillposY = posY;
					skillframex = 6;

				}

				else
				{
					skillposX = posX - 50 * scale;
					skillposY = posY;
					skillframex = 6;
				}

			}

			if (actiontime % 8 == 7)
			{
				actiontime = 0;
				actionframex++;


				if (actionframex > 11)
				{
					actionframex = 0;
					currentframex = 0;
					//actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					rightPunch = false;
					actiontime = 0;
					skillB = false;
					commandB = false;
					

				}
			}
		}

		if (launchSkillB)
		{
			skillframey = 3;
			skilltime++;
			

			if (isHit)
			{
				launchSkillB = false;
				SkillOnHit = false;
				skillB = false;
				commandB = false;
			}

			if (direction)
			{
				skillposX += 12;
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
				skillposX -= 12;
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

			if (skilltime % 7 == 6)
			{
				skilltime = 0;
				skillframex++;


				if (skillframex > 9)
				{
					skillframex = 5;
					
				}
			}
		}

		if (SkillOnHit && !isGuarded && !isGuard)
		{
		
			if (launchSkillB)
			{
				effectframex = 0;
				effectpos.x = skillposX;
				effectpos.y = WINSIZE_Y - 170 * scale;
				effectframey = 13;
			}
			
			
			launchSkillB = false;
			commandB = false;
			skillB = false;
			effectframey = 11;
			hitbox.skillAPos.x = 0;
			hitbox.skillAPos.y = 0;
			hitbox.skillAWidth = 0;
			hitbox.skillAHeight = 0;
			effecttime++;
			MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
			
			if (direction)
			{
				effectpos.x = skillposX;
				effectpos.y = posY - 30*scale;
			}

			else
			{
				effectpos.x = skillposX-20*scale;
				effectpos.y = posY - 30 * scale;
			}

			if (isHit)
			{
				launchSkillA = false;
				SkillOnHit = false;
				skillA = false;
				commandA = false;
			}

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


					if (effectframex > 11)
					{
						launchSkillA = false;
						SkillOnHit = false;
						effectframex = 0;
						launchSkillB = false;
						SkillOnHit = false;
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
			skillA = false;
			launchSkillA = false;
			launchSkillB = false;
			skillB = false;
			commandB = false;
			hitframey = 5;
			actionframey = 0;
			currentframex = 0;
			currentframey = 0;
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
					effectpos.x = posX - 15 * scale;
					effectpos.y = posY - 10 * scale;
				}

				if (hittime % 12 == 11)
				{
					effectframex++;
					if (effectframex > 7)
					{
						effectframex = 0;
					}
				}
			}

			if (hittime % 12 == 11)
			{
				hittime = 0;
				hitframex++;

				if (hitframex > 2)
				{
					hitframex = 0;
					hitframey = 0;
					effecttime = 0;
					currentframex = 0;
					actionframex = 0;
					actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					isHit = false;
					isSkillIsHit = false;
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
				effectpos.x = posX - 115 * scale + width * scale / maxFrameX;
				effectpos.y = posY - 10 * scale;
			}

			else
			{
				effectpos.x = posX - 15 * scale;
				effectpos.y = posY - 10 * scale;
			}


			if (actiontime % 7 == 6)
			{
				effectframex++;

				if (effectframex > 11)
				{
					effectframex = 8;
				}
			}

			if (actiontime % 7 == 6)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex > 2)
				{
					actionframex = 0;
					hitframey = STATE_STANDING;
					actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					effectframex = 0;
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
void Kyo::MakeHitbox()
{
	if (isHit)
		this->HitBoxInit();
	else
	{
		if (direction) // 캐릭터가 왼쪽에 있을 때 
		{
			if (rightPunch&&actionframex == 2&&!commandA&&!skillA) // 오른주먹
			{
				hitbox.attackPos.x = posX + (width*scale / maxFrameX) - (10 * scale)-hitbox.rightpunchWidth;
				hitbox.attackPos.y = posY + 17 * scale;
			}

			else if (leftKick&&actionframex == 3) // 왼발
			{
				hitbox.attackPos.x = posX + (width*scale / maxFrameX)  - hitbox.leftkickWidth+10*scale;
				hitbox.attackPos.y = posY + 60 * scale;

			}

			if (currentframey == 0) //숨쉬기
			{
				MakeHitBoxPos(47, 39, 94, 92, 45, 94, 93, 149);
			}

			if (currentframey == 1) //앞으로이동
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(44, 36, 80, 90, 46, 87, 81, 140);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(44, 36, 80, 90, 51, 75, 77, 134);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(44, 36, 80, 90, 51, 75, 77, 134);
				}

				if (currentframex == 3)
				{
					MakeHitBoxPos(44, 36, 80, 90, 46, 87, 81, 140);
				}


			}
			if (currentframey == 2) // 뒤로이동
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}

				if (currentframex == 3)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}

				if (currentframex == 4)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}

				if (currentframex == 5)
				{
					MakeHitBoxPos(53, 20, 87, 72, 58, 72, 86, 141);
				}

				if (currentframex == 6)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}

			}

			if (launchSkillA && !SkillOnHit && actionframex == 5)
			{
				hitbox.skillAWidth = (125 - 20)*scale;
				hitbox.skillAHeight = (150 - 0)*scale;
				hitbox.skillAPos.x = posX + width * scale / maxFrameX - hitbox.skillAWidth;;
				hitbox.skillAPos.y = posY + 23 * scale;
			}

			if (launchSkillB && !SkillOnHit)
			{
				hitbox.skillAWidth = (125 - 20)*scale;
				hitbox.skillAHeight = (150)*scale;
				hitbox.skillAPos.x = skillposX + width * scale / maxFrameX - hitbox.skillAWidth;;
				hitbox.skillAPos.y = skillposY +50 ;
			}
		}

		

		else
		{

			if (rightPunch&&actionframex == 2 && !commandA && !skillA)
			{
				hitbox.attackPos.x = posX + 10 * scale;
				hitbox.attackPos.y = posY + 17 * scale;

			}

			else if (leftKick&&actionframex == 3)
			{
				hitbox.attackPos.x = posX ;
				hitbox.attackPos.y = posY + 60 * scale;

			}

			if (currentframey == 0) //숨쉬기
			{
				MakeHitBoxPos(47, 39, 94, 92, 45, 94, 93, 149);
			}

			if (currentframey == 1)
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(44, 36, 80, 90, 46, 87, 81, 140);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(44, 36, 80, 90, 51, 75, 77, 134);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(44, 36, 80, 90, 51, 75, 77, 134);
				}

				if (currentframex == 3)
				{
					MakeHitBoxPos(44, 36, 80, 90, 46, 87, 81, 140);
				}


			}
			if (currentframey == 2)
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}

				if (currentframex == 3)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}

				if (currentframex == 4)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}

				if (currentframex == 5)
				{
					MakeHitBoxPos(53, 20, 87, 72, 58, 72, 86, 141);
				}

				if (currentframex == 6)
				{
					MakeHitBoxPos(51, 32, 93, 88, 47, 89, 90, 148);
				}
			}
			
			if (launchSkillA && !SkillOnHit && actionframex == 5)
			{
				hitbox.skillAWidth = (125 - 20)*scale;
				hitbox.skillAHeight = (150 - 0)*scale;
				hitbox.skillAPos.x = posX;
				hitbox.skillAPos.y = posY + 23 * scale;
			}
			if (launchSkillB && !SkillOnHit)
			{
				hitbox.skillAWidth = (125 - 20)*scale;
				hitbox.skillAHeight = (150)*scale;
				hitbox.skillAPos.x = skillposX + width * scale / maxFrameX - hitbox.skillAWidth;;
				hitbox.skillAPos.y = skillposY +50 ;
			}
		}	

		
	}



}
void Kyo::HitBoxInit()
{
	hitbox.bodyPos.x = 0;
	hitbox.bodyPos.y = 0;
	hitbox.attackPos.x = 0;
	hitbox.attackPos.y = 0;
	hitbox.skillAPos.x = 0;
	hitbox.skillAPos.y = 0;
	hitbox.guardPos.x = -300;
	hitbox.guardPos.y = -300;
	hitbox.rightpunchWidth = 45 * scale;
	hitbox.rightpunchHeight = 50 * scale;
	hitbox.leftkickWidth = 55 * scale;
	hitbox.leftkickHeight = 25 * scale;
	hitbox.bodyWidth = 0;
	hitbox.bodyHeight = 0;
	hitbox.legWidth = 0;
	hitbox.legHeight = 0;
	hitbox.skillAWidth = 0;
	hitbox.skillAHeight = 0;
	hitbox.guardWidth = 0;
	hitbox.guardHeight = 0;
}

void Kyo::KeyInit()
{
	if (playerNum == 1)
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
void Kyo::MakeSkill()
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
			actionframex = 6;
	}


	if (!launchSkillB&&skillB)
	{
		launchSkillB = true;
	}

	isLaunch = this->CheckIsLaunch();
}
bool Kyo::CheckGameOver()
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
void Kyo::MakeHitBoxPos(float bodyx1, float bodyy1, float bodyx2, float bodyy2, float legx1, float legy1, float legx2, float legy2)
{
	if (direction)
	{
		hitbox.bodyWidth = (bodyx2 - bodyx1) * scale;
		hitbox.bodyHeight = (bodyy2 - bodyy1) * scale;
		hitbox.legWidth = (legx2 - legx1) * scale;
		hitbox.legHeight = (legy2 - legy1) * scale;
		hitbox.bodyPos.x = posX - bodyx1 * scale + (width*scale / maxFrameX) - hitbox.bodyWidth;
		hitbox.bodyPos.y = posY + bodyy1 * scale;
		hitbox.legPos.x = posX - legx1 * scale + (width*scale / maxFrameX) - hitbox.legWidth;
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
bool Kyo::CheckCommand(bool &firstkey, bool &secondkey, bool commnad)
{
	bool checkcommnad = false;
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

bool Kyo::MakeCommand(bool movecommand, bool actioncommnad)
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

void Kyo::CommandTimeCheck(bool & command)
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

void Kyo::CheckSkill(bool & firstkey, bool & secondky, bool & command, bool & actioncommand, bool&skillcommand)
{
	CommandTimeCheck(secondky);
	if (!command)
		command = this->CheckCommand(firstkey, secondky, command);
	if (command)
		CommandTimeCheck(command);
	if (!skillcommand)
		skillcommand = this->MakeCommand(command, actioncommand);
}

bool Kyo::CheckIsLaunch()
{
	if (launchSkillA || launchSkillB)
		return true;
	else
		return false;
}

bool Kyo::CheckIsSkill()
{
	if (skillA || skillB)
		return true;
	else
		return false;
}


Kyo::Kyo()
{
}

Kyo::~Kyo()
{
}
