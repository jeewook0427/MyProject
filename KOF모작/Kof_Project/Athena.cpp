#include "Athena.h"
#include "Image.h"
#include "macroFunction.h"
#include <math.h>

HRESULT Athena::Init()
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
	scale = 2;

	img = new Image();
	img->Init("Image/Athena sprite sheet.bmp", posX, posY, width, height, maxFrameX, maxFrameY, true, RGB(255, 0, 255));

	superskillimg = new Image();
	superskillimg->Init("Image/Athena_Superskill.bmp", posX, posY, 3600, 800, 12, 4, true, RGB(255, 0, 255));
	//신경안쓰셔도됩니다
	profile = new Image();
	profile->Init("Image/athena profile.bmp", 103, 96, true, RGB(255, 0, 255));

	//반전시키기위해 백버퍼를 하나 더 만듬
	midBackBuffer = new Image();
	midBackBuffer->Init(130*scale, 150 * scale, true, RGB(255, 0, 255));

	skillBackBuffer = new Image();
	skillBackBuffer->Init(130 * scale,  150 * scale, true, RGB(255, 0, 255));

	skillBackBuffer2 = new Image();
	skillBackBuffer2->Init(130 * scale,  150 * scale, true, RGB(255, 0, 255));

	skillBackBuffer3 = new Image();
	skillBackBuffer3->Init(300 * scale,  200 * scale, true, RGB(255, 0, 255));

	effectBackBuffer = new Image();
	effectBackBuffer->Init(130 * scale,  150 * scale, true, RGB(255, 0, 255));

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
	skillspeed = 20;
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
	effecttime = 0;
	speed = 4;

	

	skillpos2X=0;
	skillpos2Y=0;
	theta[0] = 0;
	theta[1] = 0;
	skilldirect = false;

	mciOpenParam_StartMostion.lpstrElementName = "Sound/Athena/StartMostion.wav";
	mciOpenParam_Win.lpstrElementName = "Sound/Athena/Win.wav";
	mciOpenParam_Die.lpstrElementName = "Sound/Athena/Die.wav";

	mciOpenParam_StartMostion.lpstrDeviceType = "waveaudio";
	mciOpenParam_Win.lpstrDeviceType = "waveaudio";
	mciOpenParam_Die.lpstrDeviceType = "waveaudio";

	this->HitBoxInit();

	return S_OK;
}

void Athena::Release()
{
	effectBackBuffer->Release();
	delete effectBackBuffer;

	skillBackBuffer3->Release();
	delete skillBackBuffer3;
	   
	skillBackBuffer2->Release();
	delete skillBackBuffer2;

	skillBackBuffer->Release();
	delete skillBackBuffer;

	midBackBuffer->Release();
	delete midBackBuffer;

	profile->Release();
	delete profile;

	superskillimg->Release();
	delete superskillimg;

	img->Release();
	delete img;
}

void Athena::Update()
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

			this->MakeSkill();
		}

		if (currentframey == STATE_STANDING && !isAction && !isDead &&!roll)
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

void Athena::Render(HDC hdc)
{
	if (img)
	{
		//RenderRect(hdc, hitbox.skillAPos.x, hitbox.skillAPos.y, hitbox.skillAWidth, hitbox.skillAHeight);
		//RenderRect(hdc, hitbox.bodyPos.x, hitbox.bodyPos.y, hitbox.bodyWidth, hitbox.bodyHeight);
		//RenderRect(hdc, hitbox.legPos.x, hitbox.legPos.y, hitbox.legWidth, hitbox.legHeight);

		if (isHit&&!isDead)
			img->FrameRender(midBackBuffer->GetMemDC(), 0, 0, hitframex, hitframey, 2, direction);

		else if (rightPunch || leftKick || isDead || isWin || !gameStart || isSkill || isGuard || roll)
			img->FrameRender(midBackBuffer->GetMemDC(), 0, 0, actionframex, actionframey, 2, direction);

		else
			img->FrameRender(midBackBuffer->GetMemDC(), 0, 0, currentframex, currentframey, 2, direction);

		
	}

	if ((launchSkillA) && !isDead && !isWin)
	{
		img->FrameRender(skillBackBuffer->GetMemDC(), 0, 0, skillframex, skillframey, 2, direction);
		img->FrameRender(skillBackBuffer2->GetMemDC(), 0, 0, skillframex, skillframey, 2, direction);
	}

	else if ((launchSkillB) && !isDead && !isWin && !SkillOnHit)
	{
		superskillimg->FrameRender(skillBackBuffer3->GetMemDC(), 0, 0, skillframex, skillframey, 2, direction);
	}

	if ((SkillOnHit || isHit || isGuard) && !isDead && !isWin)
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




	//RenderRect(hdc, hitbox.attackPos.x, hitbox.attackPos.y, hitbox.rightpunchWidth, hitbox.rightpunchHeight);

	//RenderRect(hdc, hitbox.attackPos.x, hitbox.attackPos.y, hitbox.leftkickWidth, hitbox.leftkickHeight);

	//RenderRect(hdc, tempenemy.pos.x, tempenemy.pos.y, tempenemy.width, tempenemy.height);
	//RenderRect(hdc, tempenemy.enemyattackx, tempenemy.enemyattacky, tempenemy.enemywidth, tempenemy.enemyheigth);

	//미드 백버퍼에 캐릭터 그려놓을걸 다시 배경, UI가 다 그려진 백버퍼로 옮기기 위한 함수
	midBackBuffer->FrameRender(hdc, posX, posY);
	if ((launchSkillA ) && !isDead && !isWin)
	{
		skillBackBuffer->FrameRender(hdc, skillposX, skillposY);
		skillBackBuffer2->FrameRender(hdc, skillpos2X, skillpos2Y);
	}

	if ((SkillOnHit || isGuard || (!isSkillIsHit && isHit)) && !isDead && !isWin)
	{
		
		effectBackBuffer->FrameRender(hdc, effectpos.x, effectpos.y);
		
					
	}

	if ((launchSkillB) && !isDead && !isWin && !SkillOnHit)
	{
		skillBackBuffer3->FrameRender(hdc, skillposX, skillposY);
	}



}
//키입력부분
void Athena::InputKey()
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


					if (currentframex == 12)
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


					if (currentframex == 12)
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

			if ((sitDown && leftKick) && !roll &&!isLaunch &&!isSkill)
			{
				roll = true;
				if (direction)
				{
					actionframex = 5;
				}

				else
				{
					actionframex = 11;
				}
			}

			if ((sitDown && rightPunch) && !roll && !isLaunch &&!isSkill)
			{
				roll = true;
				if (direction)
				{
					actionframex = 11;
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
bool Athena::CheckAction()
{


	if (rightPunch || leftKick || isHit || isDead || isSkill || isGuard)
		return true;
	else
		return false;


}
//공격활성화 애니메이션 함수
void Athena::ActionUpdate()
{
	if (!isDead&&!isWin)
	{
		if (roll && !isHit &&!isSkill &&!isLaunch)
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
					if (actiontime % 5 == 4)
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
					if (actiontime % 5 == 4)
					{
						actiontime = 0;
						actionframex++;

						if (actionframex > 11)
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
					if (actiontime % 5 == 4)
					{
						actiontime = 0;
						actionframex++;

						if (actionframex > 11)
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
					if (actiontime % 5 == 4)
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
		if (rightPunch && !isHit && !skillA &&!isGuard && !skillB && !roll)
		{
			actiontime++;
			if (actiontime % 7 == 6)
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
					rightPunch = false;
				}
			}
		}

		if (leftKick && !isHit && !isGuard && !roll)
		{
			actiontime++;
			if (actiontime % 7 == 6)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex == 5)
				{
					hitbox.attackPos.x = 0;
					hitbox.attackPos.y = 0;
				}

				if (actionframex > 6)
				{
					actionframex = 0;
					currentframex = 0;
					actionframey = STATE_STANDING;
					currentframey = STATE_STANDING;
					leftKick = false;
				}
			}
		}
		if (skillA && !isHit &&!isGuard)
		{
			actionframey = 9;
			actiontime++;
			
			MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
			
			if (actionframex == 0)
			{
				
				skillposX = posX + 30* scale - 65 * scale;
				skillposY = posY + 10 * scale - 127 * scale;

				skillpos2X = posX + 30 * scale - 65 * scale + 90*scale;
				skillpos2Y = posY + 10 * scale - 127 * scale;
				
				theta[0] = atan2(-90 * scale, 60 * scale);
				theta[1] = atan2(-90 * scale, -60 * scale);
				skillframex = 0;
				
			}

			if (isHit)
			{
				launchSkillA = false;
				SkillOnHit = false;
				skillA = false;
				commandA = false;
			}

			if (actiontime % 6== 5)
			{
				actiontime = 0;
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

		if (launchSkillA)
		{
			skillframey = 10;
			skilltime++;
			MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
			
			

			if (skillposX > posX + 30 * scale - 65 * scale + 90 * scale)
			{
				skilldirect = true;
			}

			else if (skillposX < posX + 30 * scale - 65 * scale)
			{
				skilldirect = false;
			}
			
			if (isHit)
			{
				launchSkillA = false;
				SkillOnHit = false;
				skillA = false;
				commandA = false;
			}

			if (!skilldirect)
			{
				skillposX += skillspeed * cos(theta[0]);
				skillposY -= skillspeed * sin(theta[0]);
				skillpos2X += skillspeed * cos(theta[1]);
				skillpos2Y -= skillspeed * sin(theta[1]);
			}
			
			else
			{
				skillposX -= skillspeed * cos(theta[0]);
				skillposY += skillspeed * sin(theta[0]);
				skillpos2X -= skillspeed * cos(theta[1]);
				skillpos2Y += skillspeed * sin(theta[1]);
			}
			
			if (isGuarded)
			{
				hitbox.skillAWidth = 0;
				hitbox.skillAHeight = 0;
				launchSkillA = false;
				skillA = false;
				commandA = false;
			}
			
			if (skilltime % 3 == 2)
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
			actionframey = 12;
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


			if (actionframex == 0)
			{

				if (direction)
				{
					skillposX = posX - 85* scale;
					skillposY = posY - 40 * scale;
					skillframex = 0;
					skillframey = 0;

				}

				else
				{
					skillposX = posX - 90 * scale;
					skillposY = posY -40*scale;
					skillframex = 0;
					skillframey = 0;
				}

			}

			if (actiontime % 24 == 23)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex > 3)
				{
					if (actiontime % 17 == 16)
					{
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

				
			}
		}

		if (launchSkillB &&!isHit)
		{			
			skilltime++;
			
			if (isHit)
			{
				launchSkillB = false;
				SkillOnHit = false;
				skillB = false;
				commandB = false;
			}
						
			if (isGuarded)
			{
				hitbox.skillAWidth = 0;
				hitbox.skillAHeight = 0;
				launchSkillB = false;
				skillB = false;
				commandB = false;
			}
			if ((skillframey == 0 || (skillframey == 1 && skillframex <= 5)))
			{
				if (skilltime % 4 == 3)
				{
					skilltime = 0;
					skillframex++;

					if (skillframex > 11)
					{
						skillframex = 0;
						skillframey++;

					}
				}
			}

			else
			{
				if (skilltime % 7 == 6)
				{
					skilltime = 0;
					skillframex++;

					if (skillframex > 11)
					{
						skillframex = 0;
						skillframey++;

					}
					
					if (skillframey == 3 && skillframex > 4)
					{
						launchSkillB = false;
						SkillOnHit = false;
						skillB = false;
						commandB = false;
						
					}

					if ((skillframey == 1 && skillframex >= 10) || (skillframey == 2 && skillframex < 10))
					{
						skillposY-=30;
					}

					else if ((skillframey == 2 && skillframex >= 10) || (skillframey > 2))
					{
						skillposY +=50;
						if (direction)
						{
							skillposX += 50;
						}
						
						else
						{
							skillposX -= 50;
						}
					}

				}

				
			}
			
			
		}

		if (SkillOnHit && !isGuarded &&!isGuard)
		{
			
			effectframey = 11;
			hitbox.skillAPos.x = 0;
			hitbox.skillAPos.y = 0;
			hitbox.skillAWidth = 0;
			hitbox.skillAHeight = 0;
			effecttime++;
			
			MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);

				
			if (skillframey == 3)
			{
				if (direction)
				{
					effectpos.x = skillposX;
					effectpos.y = posY;
				}

				else
				{
					effectpos.x = skillposX + 30 * scale;
					effectpos.y = posY;
				}
			}

			else
			{
				if (direction)
				{
					effectpos.x = posX + 50 * scale;
					effectpos.y = posY;
				}

				else
				{
					effectpos.x = posX - 30 * scale;
					effectpos.y = posY;
				}
			}
			

			if (isHit)
			{
				launchSkillA = false;
				SkillOnHit = false;
				skillA = false;
				commandA = false;
				rightPunch = false;

				launchSkillB = false;
				SkillOnHit = false;
				skillB = false;
				commandB = false;
			}
			

			if (effecttime % 5 == 4)
			{
				effecttime = 0;
				effectframex++;


				if (effectframex > 9)
				{
					launchSkillA = false;
					SkillOnHit = false;
					launchSkillB = false;
					skillB = false;
					commandB = false;
					effectframex = 0;

				}
			}
		}
		if (isHit)
		{
			isGuard = false;
			hitframey = 5;
			actionframey = 0;
			currentframex = 0;
			currentframey = 0;
			actiontime = 0;
			hittime++;
			comtime = 0;
			rightPunch = false;
			leftKick = false;
			launchSkillB = false;
			skillB = false;
			commandB = false;

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
					effectframex = 5;
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
					if (effectframex > 8)
					{
						effectframex = 5;
					}
				}
			}

			if (hittime % 12 == 11)
			{
				hittime = 0;
				hitframex++;

				if (hitframex > 3)
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
				effectframex = 5;
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

				if (effectframex > 8)
				{
					effectframex = 0;
				}
			}

			if (actiontime % 7 == 6)
			{
				actiontime = 0;
				actionframex++;

				if (actionframex > 3)
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

				if (actionframex > 3)
				{
					actionframex = 3;
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
void Athena::MakeHitbox()
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
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
				}

				if (actionframex == 1)
				{
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
				}

				if (actionframex == 2)
				{
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
				}

				if (actionframex == 3)
				{
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
					hitbox.attackPos.x = posX + (width*scale / maxFrameX) - (17 * scale) - hitbox.rightpunchWidth;
					hitbox.attackPos.y = posY + 67 * scale;
				}

				if (actionframex == 4)
				{
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
				}

				if (actionframex == 5)
				{
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
				}

			}

			else if (leftKick&&actionframey == 4) // 왼발
			{
				if (actionframex == 0)
				{
					MakeHitBoxPos(43, 55, 85, 147, 43, 55, 85, 147);
				}

				if (actionframex == 1)
				{
					MakeHitBoxPos(43, 55, 85, 147, 43, 55, 85, 147);
				}

				if (actionframex == 2)
				{
					MakeHitBoxPos(46, 38, 89, 137, 46, 38, 89, 137);
				}

				if (actionframex == 3)
				{
					MakeHitBoxPos(48, 53, 115, 137, 48, 53, 115, 137);
				}

				if (actionframex == 4)
				{
					MakeHitBoxPos(46, 57, 88, 148, 46, 57, 88, 148);
					hitbox.attackPos.x = posX + (width*scale / maxFrameX) - (15 * scale) - hitbox.leftkickWidth;
					hitbox.attackPos.y = posY + 75 * scale;
				}

				if (actionframex == 5)
				{
					MakeHitBoxPos(46, 57, 88, 148, 46, 57, 88, 148);
				}

				if (actionframex == 6)
				{
					MakeHitBoxPos(46, 57, 88, 148, 46, 57, 88, 148);
				}
			}

			if (currentframey == 0) //숨쉬기
			{
				MakeHitBoxPos(54, 53, 99, 91, 45, 91, 102, 147);
			}

			if (currentframey == 1) //앞으로이동
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(51, 48, 81, 84, 50, 84, 83, 146);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(45, 48, 87, 87, 42, 87, 90, 146);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(45, 47, 87, 86, 43, 86, 92, 145);
				}

				if (currentframex == 3)
				{
					MakeHitBoxPos(45, 47, 87, 86, 43, 86, 92, 145);
				}

				if (currentframex == 4)
				{
					MakeHitBoxPos(45, 47, 87, 86, 43, 86, 92, 145);
				}

				if (currentframex == 5)
				{
					MakeHitBoxPos(45, 47, 87, 86, 43, 86, 92, 145);
				}

				if (currentframex == 6)
				{
					MakeHitBoxPos(48, 48, 75, 85, 45, 85, 84, 147);
				}

				if (currentframex == 7)
				{
					MakeHitBoxPos(48, 48, 75, 85, 45, 85, 84, 147);
				}

				if (currentframex == 8)
				{
					MakeHitBoxPos(48, 48, 75, 85, 45, 85, 84, 147);
				}

				if (currentframex == 9)
				{
					MakeHitBoxPos(43, 50, 87, 87, 39, 87, 92, 146);
				}

				if (currentframex == 10)
				{
					MakeHitBoxPos(43, 50, 87, 87, 39, 87, 92, 146);
				}

				if (currentframex == 11)
				{
					MakeHitBoxPos(43, 50, 87, 87, 39, 87, 92, 146);
				}

				if (currentframex == 12)
				{
					MakeHitBoxPos(48, 48, 75, 85, 45, 85, 84, 147);
				}


			}
			if (currentframey == 2) // 뒤로이동
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(56, 48, 93, 84, 47, 84, 93, 141);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(56, 48, 93, 84, 45, 84, 93, 141);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(56, 48, 93, 84, 43, 84, 93, 141);
				}

				if (currentframex == 3)
				{
					MakeHitBoxPos(56, 48, 93, 84, 40, 84, 93, 141);
				}

				if (currentframex == 4)
				{
					MakeHitBoxPos(56, 48, 93, 84, 41, 84, 93, 141);
				}

				if (currentframex == 5)
				{
					MakeHitBoxPos(56, 48, 93, 84, 43, 84, 93, 141);
				}

				if (currentframex == 6)
				{
					MakeHitBoxPos(56, 48, 93, 84, 44, 84, 93, 141);
				}

				if (currentframex == 7)
				{
					MakeHitBoxPos(56, 48, 93, 84, 45, 84, 93, 141);
				}

				if (currentframex == 8)
				{
					MakeHitBoxPos(56, 48, 93, 84, 47, 84, 93, 141);
				}

			}

			if (launchSkillA && !SkillOnHit)
			{
				hitbox.skillAWidth = (125 - 5)*scale;
				hitbox.skillAHeight = (150 - 23)*scale;
				hitbox.skillAPos.x = posX - 5 * scale + width * scale / maxFrameX - hitbox.skillAWidth;;
				hitbox.skillAPos.y = posY + 23 * scale;

				MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
			}

			if (launchSkillB && !SkillOnHit)
			{
				
				if ((skillframey == 2 && skillframex > 9) || (skillframey == 3))
				{
					hitbox.skillAWidth = (261 - 50)*scale;
					hitbox.skillAHeight = (204 - 2)*scale;
					hitbox.skillAPos.x = skillposX - 60 * scale + width * scale / maxFrameX ;
					hitbox.skillAPos.y = skillposY + 2 * scale;

					MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
					
				}
				
			}
		}

		else
		{

			if (rightPunch&&actionframey == 3) // 오른주먹
			{
				if (actionframex == 0)
				{
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
				}

				if (actionframex == 1)
				{
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
				}

				if (actionframex == 2)
				{
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
				}

				if (actionframex == 3)
				{
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
					hitbox.attackPos.x = posX + (17 * scale);
					hitbox.attackPos.y = posY + 67 * scale;
				}

				if (actionframex == 4)
				{
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
				}

				if (actionframex == 5)
				{
					MakeHitBoxPos(46, 54, 86, 145, 46, 54, 86, 145);
				}

			}

			else if (leftKick&&actionframey == 4) // 왼발
			{
				if (actionframex == 0)
				{
					MakeHitBoxPos(43, 55, 85, 147, 43, 55, 85, 147);
				}

				if (actionframex == 1)
				{
					MakeHitBoxPos(43, 55, 85, 147, 43, 55, 85, 147);
				}

				if (actionframex == 2)
				{
					MakeHitBoxPos(46, 38, 89, 137, 46, 38, 89, 137);
				}

				if (actionframex == 3)
				{
					MakeHitBoxPos(48, 53, 115, 137, 48, 53, 115, 137);
				}

				if (actionframex == 4)
				{
					MakeHitBoxPos(46, 57, 88, 148, 46, 57, 88, 148);
					hitbox.attackPos.x = posX +(15 * scale);
					hitbox.attackPos.y = posY + 75 * scale;
				}

				if (actionframex == 5)
				{
					MakeHitBoxPos(46, 57, 88, 148, 46, 57, 88, 148);
				}

				if (actionframex == 6)
				{
					MakeHitBoxPos(46, 57, 88, 148, 46, 57, 88, 148);
				}
			}

			if (currentframey == 0)
			{
				MakeHitBoxPos(54, 53, 99, 91, 45, 91, 102, 147);
			}

			if (currentframey == 1)
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(51, 48, 81, 84, 50, 84, 83, 146);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(45, 48, 87, 87, 42, 87, 90, 146);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(45, 47, 87, 86, 43, 86, 92, 145);
				}

				if (currentframex == 3)
				{
					MakeHitBoxPos(45, 47, 87, 86, 43, 86, 92, 145);
				}

				if (currentframex == 4)
				{
					MakeHitBoxPos(45, 47, 87, 86, 43, 86, 92, 145);
				}

				if (currentframex == 5)
				{
					MakeHitBoxPos(45, 47, 87, 86, 43, 86, 92, 145);
				}

				if (currentframex == 6)
				{
					MakeHitBoxPos(48, 48, 75, 85, 45, 85, 84, 147);
				}

				if (currentframex == 7)
				{
					MakeHitBoxPos(48, 48, 75, 85, 45, 85, 84, 147);
				}

				if (currentframex == 8)
				{
					MakeHitBoxPos(48, 48, 75, 85, 45, 85, 84, 147);
				}

				if (currentframex == 9)
				{
					MakeHitBoxPos(43, 50, 87, 87, 39, 87, 92, 146);
				}

				if (currentframex == 10)
				{
					MakeHitBoxPos(43, 50, 87, 87, 39, 87, 92, 146);
				}

				if (currentframex == 11)
				{
					MakeHitBoxPos(43, 50, 87, 87, 39, 87, 92, 146);
				}

				if (currentframex == 12)
				{
					MakeHitBoxPos(48, 48, 75, 85, 45, 85, 84, 147);
				}


			}
			if (currentframey == 2)
			{
				if (currentframex == 0)
				{
					MakeHitBoxPos(56, 48, 93, 84, 47, 84, 93, 141);
				}

				if (currentframex == 1)
				{
					MakeHitBoxPos(56, 48, 93, 84, 45, 84, 93, 141);
				}

				if (currentframex == 2)
				{
					MakeHitBoxPos(56, 48, 93, 84, 43, 84, 93, 141);
				}

				if (currentframex == 3)
				{
					MakeHitBoxPos(56, 48, 93, 84, 40, 84, 93, 141);
				}

				if (currentframex == 4)
				{
					MakeHitBoxPos(56, 48, 93, 84, 41, 84, 93, 141);
				}

				if (currentframex == 5)
				{
					MakeHitBoxPos(56, 48, 93, 84, 43, 84, 93, 141);
				}

				if (currentframex == 6)
				{
					MakeHitBoxPos(56, 48, 93, 84, 44, 84, 93, 141);
				}

				if (currentframex == 7)
				{
					MakeHitBoxPos(56, 48, 93, 84, 45, 84, 93, 141);
				}

				if (currentframex == 8)
				{
					MakeHitBoxPos(56, 48, 93, 84, 47, 84, 93, 141);
				}
			}

			if (launchSkillA && !SkillOnHit)
			{
				hitbox.skillAWidth = (125 - 5)*scale;
				hitbox.skillAHeight = (150 - 23)*scale;
				hitbox.skillAPos.x = posX + 5 * scale;
				hitbox.skillAPos.y = posY + 23 * scale;
				MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
			}

			if (launchSkillB && !SkillOnHit)
			{
			
				if ((skillframey == 2 && skillframex > 9) || (skillframey == 3))
				{

					hitbox.skillAWidth = (261 - 34)*scale;
					hitbox.skillAHeight = (204 - 2)*scale;
					hitbox.skillAPos.x = skillposX + 34;
					hitbox.skillAPos.y = skillposY + 2 * scale;

					MakeHitBoxPos(0, 0, 0, 0, 0, 0, 0, 0);
				}
			}

		}
	}



}

void Athena::HitBoxInit()
{
	hitbox.bodyPos.x = 0;
	hitbox.bodyPos.y = 0;
	hitbox.attackPos.x = 0;
	hitbox.attackPos.y = 0;
	hitbox.skillAPos.x = 0;
	hitbox.skillAPos.y = 0;
	hitbox.guardPos.x = -300;
	hitbox.guardPos.y = -300;
	hitbox.rightpunchWidth = 40 * scale;
	hitbox.rightpunchHeight = 35 * scale;
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

void Athena::KeyInit()
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
void Athena::MakeSkill()
{
	if (!launchSkillA)
	{
		this->CheckSkill(keyDownCheck, keyFowardCheck, commandA, rightPunch, skillA);	//처음키 , 다음키, 뱡향키 2개눌렀을때 불값 , 액션키, 저장스킬
	}

	if (!launchSkillA&&skillA&&actionframex == 0)
		launchSkillA = true;

	if (!launchSkillB)
	{
		this->CheckSkill(keyBackCheck, keyFowardCheck, commandB, rightPunch, skillB);							//처음키 , 다음키, 뱡향키 2개눌렀을때 불값 , 액션키, 저장스킬
		if (skillB)
			actionframex = 0;
	}


	if (!launchSkillB&&skillB&&actionframex == 0)
	{
		launchSkillB = true;
	}

	isLaunch = this->CheckIsLaunch();
}
bool Athena::CheckGameOver()
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
void Athena::MakeHitBoxPos(float bodyx1, float bodyy1, float bodyx2, float bodyy2, float legx1, float legy1, float legx2, float legy2)
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
bool Athena::CheckCommand(bool &firstkey, bool &secondkey, bool commnad)
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

bool Athena::MakeCommand(bool movecommand, bool actioncommnad)
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

void Athena::CommandTimeCheck(bool & command)
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

void Athena::CheckSkill(bool & firstkey, bool & secondky, bool & command, bool & actioncommand, bool&skillcommand)
{
	CommandTimeCheck(secondky);
	if (!command)
		command = this->CheckCommand(firstkey, secondky, command);
	if (command)
		CommandTimeCheck(command);
	if (!skillcommand)
		skillcommand = this->MakeCommand(command, actioncommand);
}

bool Athena::CheckIsLaunch()
{
	if (launchSkillA || launchSkillB)
		return true;
	else
		return false;
}

bool Athena::CheckIsSkill()
{
	if (skillA || skillB)
		return true;
	else
		return false;
}

Athena::Athena()
{
}

Athena::~Athena()
{
}
