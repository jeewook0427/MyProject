#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Inventory.h"
#include "pch.h"

POINT mousepos;

HRESULT Player::Init()
{
	

	//플레이어 달리기 이미지
	playerRun = ImageManager::GetSingleton()->FindImage("playerrun");
	//플레이어 정지 이미지
	playerStop = ImageManager::GetSingleton()->FindImage("playerstop");
	//마우스커서
	mousecursor = ImageManager::GetSingleton()->FindImage("mousecursor");
	//플레이어 자원 채굴
	playerMine = ImageManager::GetSingleton()->FindImage("playermine");


	//플레이어 달리기 애니메이션
	playerRunAni = new Animation();
	playerRunAni->Init(playerRun->GetWidth(), playerRun->GetHeight(), playerRun->GetFrameWidth(), playerRun->GetFrameHeight());
	playerRunAni->SetUpdateTime(FPS/ 1.0f);
	playerRunAni->SetPlayFrame(0, 10, true, true);

	//플레이어 정지 애니메이션
	playerStopAni = new Animation();
	playerStopAni->Init(playerStop->GetWidth(), playerStop->GetHeight(), playerStop->GetFrameWidth(), playerStop->GetFrameHeight());
	playerStopAni->SetUpdateTime(FPS / 2.0f);
	playerStopAni->SetPlayFrame(44, 65, true, true);
	playerStopAni->Start();

	//플레이어 자원채굴 애니메이션
	playerMineAni = new Animation();
	playerMineAni->Init(playerMine->GetWidth(), playerMine->GetHeight(), playerMine->GetFrameWidth(), playerMine->GetFrameHeight());
	playerMineAni->SetUpdateTime(FPS /1.0f);
	playerMineAni->SetPlayFrame(0, 10, true, true);


	//인벤토리
	inventory = new Inventory();
	inventory->Init();

	//속도
	speed = 150;
	angle = 0;

	//운동상태
	isStop = true;
	isMove = false;
	isMine = false;

	//마우스
	MousePos.x = 0;
	MousePos.y = 0;

	//채굴게이지
	gage = 0;

	return S_OK;
}

void Player::Release()
{
	SAFE_DELETE(playerRunAni);
	SAFE_DELETE(playerStopAni);
	SAFE_DELETE(playerMineAni);

	inventory->Release();
	SAFE_DELETE(inventory);
}

void Player::Update()
{
	POINT playerIndex;

	if (p_pos.x < 8192 && p_pos.y < 8192)
	{
		if (tileinfo[(int)p_pos.y / 32][(int)p_pos.x / 32].obj == EMPTY)
			tileinfo[(int)p_pos.y / 32][(int)p_pos.x / 32].obj = HUMAN;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (!(i == 1 && j == 1))
					if (tileinfo[(int)p_pos.y / 32 + 1 - i][(int)p_pos.x / 32 + 1 - j].obj == HUMAN)
						tileinfo[(int)p_pos.y / 32 + 1 - i][(int)p_pos.x / 32 + 1 - j].obj = EMPTY;
			}
		}
	}
	if (!isMine&&!isLaunch)
	{
		this->PlayerMove();
		gage = 0;
	}
	   
	if (isStop)
		this->PlayerStop();

	if (inventory)
		inventory->Update();

	if (playerMineAni)
		playerMineAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

	if(!isLaunch)
		this->PlayerMine();

	mousepos.x = (g_ptMouse.x / cameraScale + (WINSIZE_X / 2 - WINSIZE_X / (2 * cameraScale))+ p_pos.x - WINSIZE_X /2);
	mousepos.y = (g_ptMouse.y / cameraScale + (WINSIZE_Y / 2 - WINSIZE_Y / (2 * cameraScale)) + p_pos.y - WINSIZE_Y /2);

	if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
	{
		Tutorial::GetSingleton()->SucceedQuest_11();
		
		vector<GameNode*>::iterator it;
		it = (*ObjectManager::GetSingleton()->FindObjectVec()).begin();
		for (int i = 0; i < (*ObjectManager::GetSingleton()->FindObjectVec()).size(); i++)
		{
			
			if ((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().x == (int)(p_pos.x)/32
				&& (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetTilePoint().y ==(int)(p_pos.y)/32)
			{
				if (CheckCollision(p_pos.x, p_pos.y, 23,
					(*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().x, (*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetPos().y, 10))
				{

					AddInInventory((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer(), 1);
					(*ObjectManager::GetSingleton()->FindObjectPool((*ObjectManager::GetSingleton()->FindObjectVec())[i]->GetLayer())).push((*ObjectManager::GetSingleton()->FindObjectVec())[i]);
					(*ObjectManager::GetSingleton()->FindObjectVec()).erase(it);

					goto skip1;


				}


			}
				
			
			it++;
		}
	skip1:
		{}


	}

	
}

void Player::Render(HDC hdc)
{
	char sZtext[256];
	map<TILE_POINT, GameNode*>::iterator it;

	if (!isLaunch)
	{
		if (playerRun && isMove && !isMine)
		{
			playerRun->AnimationRender(hdc, p_pos.x - g_pos.x + WINSIZE_X / 2, p_pos.y - g_pos.y + WINSIZE_Y / 2, playerRunAni);

			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(TREE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(TREE)).end(); it++)
			{
				it->second->Render(hdc);
			}
		}


		else if (playerStop && isStop && !isMine)
		{
			playerStop->AnimationRender(hdc, p_pos.x - g_pos.x + WINSIZE_X / 2, p_pos.y - g_pos.y + WINSIZE_Y / 2, playerStopAni);

			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(TREE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(TREE)).end(); it++)
			{
				it->second->Render(hdc);
			}
		}


		else if (isMine)
		{
			playerMine->AnimationRender(hdc, p_pos.x - g_pos.x + WINSIZE_X / 2, p_pos.y - g_pos.y + WINSIZE_Y / 2, playerMineAni);

			for (it = (*ObjectManager::GetSingleton()->FindObjectMap(TREE)).begin(); it != (*ObjectManager::GetSingleton()->FindObjectMap(TREE)).end(); it++)
			{
				it->second->Render(hdc);
			}

			this->GageRender(hdc);
		}
	}
	//this->MouseRender(hdc);
	


}

void Player::PlayerMove()
{
	//달리기 애니메이션
	if (playerRunAni && isMove)
		playerRunAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	
	//이동

	//우상
	if (KeyManager::GetSingleton()->IsStayKeyDown('D') && KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		if (!soundPlay)
		{
			SoundManager::GetSingleton()->Play("playerwalking");
			soundPlay = true;
		}

		angle = 45;
		playerRunAni->SetPlayFrame(22, 43, false, true);
		
		p_pos.x += 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(45));
		p_pos.y -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(45));
		if (p_pos.x <= 8192 - WINSIZE_X / 2 && p_pos.x >= 800)
			g_pos.x = p_pos.x;
		if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
			g_pos.y = p_pos.y;

		//화면밖으로 벗어났을 때

		if (g_pos.x > 7392)
			g_pos.x = 7392;

		if (g_pos.y < WINSIZE_Y / 2)
			g_pos.y = WINSIZE_Y/2;

		if (p_pos.x > 8192)
			p_pos.x = 8192;

		if (p_pos.y < 0)
			p_pos.y = 0;

		// 충돌처리
		if (PlayerCollision(p_pos.x - 14, p_pos.y - 14) || PlayerCollision(p_pos.x + 14, p_pos.y - 14))
		{
			if (p_pos.x <= 8192 - WINSIZE_X / 2 && p_pos.x >= 800)
				g_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(45));
			if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
				g_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(45));
			p_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(45));
			p_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(45));
		}
		// 충돌처리
		if (PlayerCollision(p_pos.x + 14, p_pos.y - 14) || PlayerCollision(p_pos.x + 14, p_pos.y + 14))
		{
			if (p_pos.x <= 8192 - WINSIZE_X / 2 && p_pos.x >= 800)
				g_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(45));
			if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
				g_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(45));
			p_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(45));
			p_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(45));
		}
	}
	//우하
	else if (KeyManager::GetSingleton()->IsStayKeyDown('D') && KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		if (!soundPlay)
		{
			SoundManager::GetSingleton()->Play("playerwalking");
			soundPlay = true;
		}

		angle = 315;
		playerRunAni->SetPlayFrame(66, 87, false, true);
		
		p_pos.x += 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(315));
		p_pos.y -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(315));
		
		if (p_pos.x <= 8192 - WINSIZE_X / 2 && p_pos.x >= 800)
			g_pos.x = p_pos.x;
		if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
			g_pos.y = p_pos.y;
		
		if (g_pos.x > 7392)
			g_pos.x = 7392;

		if (g_pos.y > 8192 - WINSIZE_Y/2)
			g_pos.y = 8192 - WINSIZE_Y / 2;

		if (p_pos.x > 8192)
			p_pos.x = 8192;

		if (p_pos.y > 8192)
			p_pos.y = 8192;

		// 충돌처리
		if (PlayerCollision(p_pos.x - 14, p_pos.y + 14) || PlayerCollision(p_pos.x + 14, p_pos.y + 14))
		{
			if (p_pos.x >= WINSIZE_X / 2 && p_pos.x <= 8192 - WINSIZE_X / 2)
				g_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(315));
			if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
				g_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(315));
			p_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(315));
			p_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(315));
		}
		// 충돌처리
		if (PlayerCollision(p_pos.x + 14, p_pos.y - 14) || PlayerCollision(p_pos.x + 14, p_pos.y + 14))
		{
			if (p_pos.x >= WINSIZE_X / 2 && p_pos.x <= 8192 - WINSIZE_X / 2)
				g_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(315));
			if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
				g_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(315));
			p_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(315));
			p_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(315));
		}
	}
	//좌상
	else if (KeyManager::GetSingleton()->IsStayKeyDown('A') && KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		if (!soundPlay)
		{
			SoundManager::GetSingleton()->Play("playerwalking");
			soundPlay = true;
		}

		angle = 135;
		playerRunAni->SetPlayFrame(154, 175, false, true);
		
		p_pos.x += 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(135));
		p_pos.y -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(135));
		if (p_pos.x >= WINSIZE_X / 2 && p_pos.x <= 8192 - WINSIZE_X / 2)
			g_pos.x = p_pos.x;
		if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
			g_pos.y = p_pos.y;
		
		if (g_pos.x < 800)
			g_pos.x = 800;

		if (g_pos.y < WINSIZE_Y / 2)
			g_pos.y = WINSIZE_Y / 2;

		if (p_pos.x < 0)
			p_pos.x = 0;

		if (p_pos.y < 0)
			p_pos.y = 0;


		// 충돌처리
		if (PlayerCollision(p_pos.x - 14, p_pos.y - 14) || PlayerCollision(p_pos.x + 14, p_pos.y - 14))
		{
			if (p_pos.x >= WINSIZE_X / 2 && p_pos.x <= 8192 - WINSIZE_X / 2)
				g_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(135));
			if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
				g_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(135));
			p_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(135));
			p_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(135));
		}
		// 충돌처리
		if (PlayerCollision(p_pos.x - 14, p_pos.y - 14) || PlayerCollision(p_pos.x - 14, p_pos.y + 14))
		{
			if (p_pos.x >= WINSIZE_X / 2 && p_pos.x <= 8192 - WINSIZE_X / 2)
				g_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(135));
			if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
				g_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(135));
			p_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(135));
			p_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(135));

		}
	}
	//좌하
	else if (KeyManager::GetSingleton()->IsStayKeyDown('A') && KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		if (!soundPlay)
		{
			SoundManager::GetSingleton()->Play("playerwalking");
			soundPlay = true;
		}

		angle = 225;
		playerRunAni->SetPlayFrame(110, 131, false, true);
	
		p_pos.x += 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(225));
		p_pos.y -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(225));

		if (p_pos.x >= WINSIZE_X / 2 && p_pos.x <= 8192 - WINSIZE_X / 2)
			g_pos.x = p_pos.x;
		if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
			g_pos.y = p_pos.y;
		
	

		if (g_pos.x < 800)
			g_pos.x = 800;

		if (g_pos.y > 8192- WINSIZE_Y / 2)
			g_pos.y = 8192 - WINSIZE_Y / 2;

		if (p_pos.x < 0)
			p_pos.x = 0;

		if (p_pos.y > 8192)
			p_pos.y = 8192;

		// 충돌처리
		if (PlayerCollision(p_pos.x - 14, p_pos.y + 14) || PlayerCollision(p_pos.x + 14, p_pos.y + 14))
		{
			if (p_pos.x >= WINSIZE_X / 2 && p_pos.x <= 8192 - WINSIZE_X / 2)
				g_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(225));
			if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
				g_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(225));
			p_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(225));
			p_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(225));
		}
		// 충돌처리
		if (PlayerCollision(p_pos.x - 14, p_pos.y - 14) || PlayerCollision(p_pos.x - 14, p_pos.y + 14))
		{
			if (p_pos.x >= WINSIZE_X / 2 && p_pos.x <= 8192 - WINSIZE_X / 2)
				g_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(225));
			if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
				g_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(225));
			p_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime()*cos(DEGREE_TO_RADIAN(225));
			p_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime()*sin(DEGREE_TO_RADIAN(225));
		}
	}
	//상
	else if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		if (!soundPlay)
		{
			SoundManager::GetSingleton()->Play("playerwalking");
			soundPlay = true;
		}

		angle = 90;
		playerRunAni->SetPlayFrame(0, 21, false, true);

		
		p_pos.y -= 150 * TimeManager::GetSingleton()->GetDeltaTime();
		
		if((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <=8192 - WINSIZE_Y/2)
			g_pos.y = p_pos.y;
		if (g_pos.y < WINSIZE_Y / 2)
			g_pos.y = WINSIZE_Y / 2;
		
		if (p_pos.y < 0)
			p_pos.y = 0;

		

		// 충돌처리
		if (PlayerCollision(p_pos.x - 14, p_pos.y - 14) || PlayerCollision(p_pos.x + 14, p_pos.y - 14))
		{
			if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
				g_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime();
			p_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime();
		}
	}
	//하
	else if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{

		if (!soundPlay)
		{
			SoundManager::GetSingleton()->Play("playerwalking");
			soundPlay = true;
		}
		angle = 270;
		playerRunAni->SetPlayFrame(88, 109, false, true);
		/*p_pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime() * cosf(DEGREE_TO_RADIAN(angle));
		p_pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime() * sinf(DEGREE_TO_RADIAN(angle));*/
		
		p_pos.y += 150 * TimeManager::GetSingleton()->GetDeltaTime();
		if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
			g_pos.y = p_pos.y;
		if (g_pos.y > 8192 - WINSIZE_Y / 2)
			g_pos.y = 8192 - WINSIZE_Y / 2;

		if (p_pos.y > 8192)
			p_pos.y = 8192;


		// 충돌처리
		if (PlayerCollision(p_pos.x - 14, p_pos.y + 14) || PlayerCollision(p_pos.x + 14, p_pos.y + 14))
		{
			if ((p_pos.y >= WINSIZE_Y / 2) && p_pos.y <= 8192 - WINSIZE_Y / 2)
				g_pos.y -= 150 * TimeManager::GetSingleton()->GetDeltaTime();
			p_pos.y -= 150 * TimeManager::GetSingleton()->GetDeltaTime();
		}
	}
	//좌
	else if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
	{
		if (!soundPlay)
		{
			SoundManager::GetSingleton()->Play("playerwalking");
			soundPlay = true;
		}
		angle = 180;
		playerRunAni->SetPlayFrame(132, 153, false, true);
		/*p_pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime() * cosf(DEGREE_TO_RADIAN(angle));
		p_pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime() * sinf(DEGREE_TO_RADIAN(angle));*/
				
		p_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime();
		
		if (p_pos.x >= WINSIZE_X/2 && p_pos.x <=8192-WINSIZE_X/2)
			g_pos.x = p_pos.x;

		if (g_pos.x < WINSIZE_X/2)
			g_pos.x = WINSIZE_X/2;

		if (p_pos.x < 0)
			p_pos.x = 0;

	

		// 충돌처리
		if (PlayerCollision(p_pos.x - 14, p_pos.y - 14) || PlayerCollision(p_pos.x - 14, p_pos.y + 14))
		{
			if (p_pos.x <= 8192 - WINSIZE_X / 2 && p_pos.x >= 800)
				g_pos.x += 150 * TimeManager::GetSingleton()->GetDeltaTime();
			p_pos.x += 150 * TimeManager::GetSingleton()->GetDeltaTime();
		}

	}
	//우
	else if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
	{

		if (!soundPlay)
		{
			SoundManager::GetSingleton()->Play("playerwalking");
			soundPlay = true;
		}
			

		angle = 0;
		playerRunAni->SetPlayFrame(44, 65, false, true);
		/*p_pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime() * cosf(DEGREE_TO_RADIAN(angle));
		p_pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime() * sinf(DEGREE_TO_RADIAN(angle));*/

		
		p_pos.x += 150 * TimeManager::GetSingleton()->GetDeltaTime();

		if (p_pos.x <= 8192 - WINSIZE_X/2 && p_pos.x >= 800)
			g_pos.x = p_pos.x;

		if (g_pos.x > 8192-WINSIZE_X/2)
			g_pos.x = 8192-WINSIZE_X/2;

		if (p_pos.x > 8192)
			p_pos.x = 8192;

		

		// 충돌처리
		if (PlayerCollision(p_pos.x + 14, p_pos.y - 14) || PlayerCollision(p_pos.x + 14, p_pos.y + 14))
		{
			if (p_pos.x <= 8192 - WINSIZE_X / 2 && p_pos.x >= 800)
				g_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime();
			p_pos.x -= 150 * TimeManager::GetSingleton()->GetDeltaTime();
		}


	}

	//멈추면 애니메이션 Stop 달리기 시작하면 Start
	//정지모션은 멈추면 Start 달리면 Stop
	if (!KeyManager::GetSingleton()->IsStayKeyDown('D') && !KeyManager::GetSingleton()->IsStayKeyDown('A') && !KeyManager::GetSingleton()->IsStayKeyDown('W')
		&& !KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		playerRunAni->Stop();

		if (!isStop)
			playerStopAni->Start();

		SoundManager::GetSingleton()->Stop("playerwalking");
		soundPlay = false;

		isStop = true;
		isMove = false;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('D') || KeyManager::GetSingleton()->IsOnceKeyDown('A') || KeyManager::GetSingleton()->IsOnceKeyDown('W')
		|| KeyManager::GetSingleton()->IsOnceKeyDown('S'))
	{
		isMove = true;
		isStop = false;

		
		playerRunAni->Start();
		playerStopAni->Stop();
	}

	if (tileinfo[(int)p_pos.y / 32][(int)p_pos.x / 32].obj == BASICTRANSPORTBELT)
	{
		if (tileinfo[(int)p_pos.y / 32][(int)p_pos.x / 32].belt == BELTRIGHT)
		{
			p_pos.x += 30 * TimeManager::GetSingleton()->GetDeltaTime();
			g_pos.x += 30 * TimeManager::GetSingleton()->GetDeltaTime();
		}

		else if (tileinfo[(int)p_pos.y / 32][(int)p_pos.x / 32].belt == BELTLEFT)
		{
			p_pos.x -= 30 * TimeManager::GetSingleton()->GetDeltaTime();
			g_pos.x -= 30 * TimeManager::GetSingleton()->GetDeltaTime();
		}

		else if (tileinfo[(int)p_pos.y / 32][(int)p_pos.x / 32].belt == BELTUP)
		{
			p_pos.y -= 30 * TimeManager::GetSingleton()->GetDeltaTime();
			g_pos.y -= 30 * TimeManager::GetSingleton()->GetDeltaTime();
		}

		else if (tileinfo[(int)p_pos.y / 32][(int)p_pos.x / 32].belt == BELTDOWN)
		{
			p_pos.y += 30 * TimeManager::GetSingleton()->GetDeltaTime();
			g_pos.y += 30 * TimeManager::GetSingleton()->GetDeltaTime();
		}
	}

}

void Player::PlayerStop()
{
	if (playerStopAni)
		playerStopAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());

	//우
	if (angle == 0)
	{
		playerStopAni->SetPlayFrame(44, 65, false, true);
	}
	//우상
	else if (angle == 45)
	{
		playerStopAni->SetPlayFrame(22, 43, false, true);
	}
	//상
	else if (angle == 90)
	{
		playerStopAni->SetPlayFrame(0, 21, false, true);
	}
	//좌상
	else if (angle == 135)
	{
		playerStopAni->SetPlayFrame(154, 175, false, true);
	}
	//좌
	else if (angle == 180)
	{
		playerStopAni->SetPlayFrame(132, 153, false, true);
	}
	//좌하
	else if (angle == 225)
	{
		playerStopAni->SetPlayFrame(110, 131, false, true);
	}
	//하
	else if (angle == 270)
	{
		playerStopAni->SetPlayFrame(88, 109, false, true);
	}
	//우하
	else if (angle == 315)
	{
		playerStopAni->SetPlayFrame(66, 87, false, true);
	}



}

void Player::PlayerMine()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON))
	{
		for (int i = ((int)p_pos.y) / 32 - 5; i < ((int)p_pos.y) / 32 + 5; i++)
		{
			for (int j = ((int)p_pos.x) / 32 - 5; j < ((int)p_pos.x) / 32 + 5; j++)
			{
				if (PtInRect(&tileinfo[i][j].rcTile, mousepos))
				{

					if (tileinfo[i][j].obj == EMPTY || tileinfo[i][j].obj == TREE)
					{
						if (tileinfo[i][j].obj == TREE)
						{
							if ((*ObjectManager::GetSingleton()->FindObjectMap(TREE)).find({ j,i })->second->GetSelectedClose())
							{
								if (!isMove)
								{
									if (!isMine)
									{
										playerMineAni->Start();
										playerStopAni->Stop();
										playerRunAni->Stop();
										SoundManager::GetSingleton()->Play("playerminewood",0.5f);
									}

									isMine = true;
									gage += 6;
									if (gage > 600)
									{
										AddInInventory(TREE, 1);

										Tutorial::GetSingleton()->SucceedQuest_2();

										if (tileinfo[i][j].obj == TREE)
											(*ObjectManager::GetSingleton()->FindObjectMap(TREE)).find({ j,i })->second->MinusHp();

										if (tileinfo[i + 1][j].obj == TREE)
											(*ObjectManager::GetSingleton()->FindObjectMap(TREE)).find({ j,i + 1 })->second->MinusHp();

										if (tileinfo[i + 2][j].obj == TREE)
											(*ObjectManager::GetSingleton()->FindObjectMap(TREE)).find({ j,i + 2 })->second->MinusHp();
										gage = 0;
									}

								}
							}

						}

						else if (tileinfo[i][j].res == COAL)
						{
							if ((*ObjectManager::GetSingleton()->FindObjectMap(COAL)).find({ j,i })->second->GetSelectedClose())
							{
								if (!isMove)
								{
									if (!isMine)
									{
										playerMineAni->Start();
										playerStopAni->Stop();
										playerRunAni->Stop();
										SoundManager::GetSingleton()->Play("playermine",0.5f);
									}

									isMine = true;
									gage += 6;
									if (gage > 600)
									{
										AddInInventory(COAL, 1);

										Tutorial::GetSingleton()->SucceedQuest_2();

										(*ObjectManager::GetSingleton()->FindObjectMap(COAL)).find({ j,i })->second->MinusHp();

										gage = 0;
									}

								}
							}
						}

						else if (tileinfo[i][j].res == IRON)
						{
							if ((*ObjectManager::GetSingleton()->FindObjectMap(IRON)).find({ j,i })->second->GetSelectedClose())
							{
								if (!isMove)
								{
									if (!isMine)
									{
										playerMineAni->Start();
										playerStopAni->Stop();
										playerRunAni->Stop();
										SoundManager::GetSingleton()->Play("playermine",0.5f);
									}

									isMine = true;
									gage += 6;
									if (gage > 600)
									{
										AddInInventory(IRON, 1);

										Tutorial::GetSingleton()->SucceedQuest_2();

										(*ObjectManager::GetSingleton()->FindObjectMap(IRON)).find({ j,i })->second->MinusHp();
										gage = 0;
									}

								}
							}

						}

						else if (tileinfo[i][j].res == COPPER)
						{
							if ((*ObjectManager::GetSingleton()->FindObjectMap(COPPER)).find({ j,i })->second->GetSelectedClose())
							{
								if (!isMove)
								{
									if (!isMine)
									{
										playerMineAni->Start();
										playerStopAni->Stop();
										playerRunAni->Stop();
										SoundManager::GetSingleton()->Play("playermine",0.5f);
									}

									isMine = true;
									gage += 6;
									if (gage > 600)
									{
										AddInInventory(COPPER, 1);

										Tutorial::GetSingleton()->SucceedQuest_2();

										(*ObjectManager::GetSingleton()->FindObjectMap(COPPER)).find({ j,i })->second->MinusHp();
										gage = 0;
									}

								}
							}

						}

						else if (tileinfo[i][j].res == STONE)
						{
							if ((*ObjectManager::GetSingleton()->FindObjectMap(STONE)).find({ j,i })->second->GetSelectedClose())
							{
								if (!isMove)
								{
									if (!isMine)
									{
										playerMineAni->Start();
										playerStopAni->Stop();
										playerRunAni->Stop();
										SoundManager::GetSingleton()->Play("playermine",0.5f);
									}

									isMine = true;
									gage += 6;
									if (gage > 600)
									{
										AddInInventory(STONE, 1);

										Tutorial::GetSingleton()->SucceedQuest_2();

										(*ObjectManager::GetSingleton()->FindObjectMap(STONE)).find({ j,i })->second->MinusHp();
										gage = 0;
									}

								}
							}

						}
					}
					
				}
			}
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RBUTTON))
	{
		isMine = false;
		playerMineAni->Stop();
		SoundManager::GetSingleton()->Stop("playermine");
		SoundManager::GetSingleton()->Stop("playerminewood");
		
	}



	if (isMine)
	{
		int tempangle;
		tempangle = RADIAN_TO_DEGREE((atan2(-(g_ptMouse.y + g_pos.y - WINSIZE_Y / 2 - p_pos.y), g_ptMouse.x + g_pos.x - WINSIZE_X / 2 - p_pos.x)));
		if (tempangle < 0)
		{
			tempangle = 360 + tempangle;
		}

		if (tempangle >= 292.5 && tempangle < 337.5)
			angle = 315;
		if (tempangle >= 247.5 && tempangle < 292.5)
			angle = 270;
		if (tempangle >= 202.5 && tempangle < 247.5)
			angle = 225;
		if (tempangle >= 147.5 && tempangle < 202.5)
			angle = 180;
		if (tempangle >= 112.5 && tempangle < 147.5)
			angle = 135;
		if (tempangle >= 67.5 && tempangle < 112.5)
			angle = 90;
		if (tempangle >= 22.5 && tempangle < 67.5)
			angle = 45;
		if (tempangle >= 337.5 || tempangle < 22.5)
			angle = 0;


		//우	
		if (angle == 0)
		{
			playerMineAni->SetPlayFrame(28, 41, false, true);
		}
		//우상
		else if (angle == 45)
		{
			playerMineAni->SetPlayFrame(14, 27, false, true);
		}
		//상
		else if (angle == 90)
		{
			playerMineAni->SetPlayFrame(0, 13, false, true);
		}
		//좌상
		else if (angle == 135)
		{
			playerMineAni->SetPlayFrame(98, 111, false, true);
		}
		//좌
		else if (angle == 180)
		{
			playerMineAni->SetPlayFrame(84, 97, false, true);
		}
		//좌하
		else if (angle == 225)
		{
			playerMineAni->SetPlayFrame(70, 83, false, true);
		}
		//하
		else if (angle == 270)
		{
			playerMineAni->SetPlayFrame(56, 69, false, true);
		}
		//우하
		else if (angle == 315)
		{
			playerMineAni->SetPlayFrame(42, 55, false, true);
		}

	}

}

void Player::MouseRender(HDC hdc, HDC hdc2)
{
	map<TILE_POINT, GameNode*>::iterator it;
	map<Layer, map<TILE_POINT, GameNode*>> ::iterator iter;


	TILE_POINT temppoint;
	for (int i = ((int)g_pos.y - WINSIZE_Y / 2) / 32; i < ((int)g_pos.y - WINSIZE_Y / 2) / 32 + 29; i++)
	{
		for (int j = ((int)g_pos.x - WINSIZE_X / 2) / 32; j < ((int)g_pos.x - WINSIZE_X / 2) / 32 + 51; j++)
		{
			temppoint = { j,i };
			if (PtInRect(&tileinfo[i][j].rcTile, mousepos))
			{
				if (tileinfo[i][j].obj == EMPTY || tileinfo[i][j].obj == TREE)
				{
					if (tileinfo[i][j].obj == TREE || tileinfo[i + 1][j].obj == TREE)
					{
						if (tileinfo[i + 1][j].obj == TREE)
							temppoint = { j, i + 1 };

						it = (*ObjectManager::GetSingleton()->FindObjectMap(TREE)).find(temppoint);
						if (it != (*ObjectManager::GetSingleton()->FindObjectMap(TREE)).end())
						{
							if (tileinfo[i + 1][j].obj == TREE)
							{
								if (abs((i + 1) * 32 - p_pos.y) <= 32 * 3 && abs(j * 32 - p_pos.x) <= 32 * 3)
									it->second->SetIsSelectedClose(true);
								else
									it->second->SetIsSelectedClose(false);
							}

							else
							{
								if (abs(i * 32 - p_pos.y) <= 32 * 3 && abs(j * 32 - p_pos.x) <= 32 * 3)
									it->second->SetIsSelectedClose(true);
								else
									it->second->SetIsSelectedClose(false);
							}
							it->second->SelectBoxRender(hdc2);
							it->second->InfoRender(hdc);

						}

					}


					else if (tileinfo[i][j].res == COAL)
					{
						it = (*ObjectManager::GetSingleton()->FindObjectMap(COAL)).find(temppoint);
						if (it != (*ObjectManager::GetSingleton()->FindObjectMap(COAL)).end())
						{
							if (abs(i * 32 - p_pos.y) <= 32 * 3 && abs(j * 32 - p_pos.x) <= 32 * 3)
								it->second->SetIsSelectedClose(true);
							else
								it->second->SetIsSelectedClose(false);
							it->second->SelectBoxRender(hdc2);
							it->second->InfoRender(hdc);

						}


					}

					else if (tileinfo[i][j].res == IRON)
					{
						it = (*ObjectManager::GetSingleton()->FindObjectMap(IRON)).find(temppoint);
						if (it != (*ObjectManager::GetSingleton()->FindObjectMap(IRON)).end())
						{
							if (abs(i * 32 - p_pos.y) <= 32 * 3 && abs(j * 32 - p_pos.x) <= 32 * 3)
								it->second->SetIsSelectedClose(true);
							else
								it->second->SetIsSelectedClose(false);
							it->second->SelectBoxRender(hdc2);
							it->second->InfoRender(hdc);

						}


					}

					else if (tileinfo[i][j].res == COPPER)
					{
						it = (*ObjectManager::GetSingleton()->FindObjectMap(COPPER)).find(temppoint);
						if (it != (*ObjectManager::GetSingleton()->FindObjectMap(COPPER)).end())
						{
							if (abs(i * 32 - p_pos.y) <= 32 * 3 && abs(j * 32 - p_pos.x) <= 32 * 3)
								it->second->SetIsSelectedClose(true);
							else
								it->second->SetIsSelectedClose(false);
							it->second->SelectBoxRender(hdc2);
							it->second->InfoRender(hdc);

						}


					}

					else if (tileinfo[i][j].res == STONE)
					{
						it = (*ObjectManager::GetSingleton()->FindObjectMap(STONE)).find(temppoint);
						if (it != (*ObjectManager::GetSingleton()->FindObjectMap(STONE)).end())
						{
							if (abs(i * 32 - p_pos.y) <= 32 * 3 && abs(j * 32 - p_pos.x) <= 32 * 3)
								it->second->SetIsSelectedClose(true);
							else
								it->second->SetIsSelectedClose(false);
							it->second->SelectBoxRender(hdc2);
							it->second->InfoRender(hdc);

						}


					}
				}
			}


		}
	}
}

void Player::GageRender(HDC hdc)
{
	RECT gageRect;
	gageRect = GetRectToCenter(WINSIZE_X / 2, WINSIZE_Y - 200, 600, 20);

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(174, 90, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Rectangle(hdc, gageRect.left, gageRect.top, gageRect.left + gage, gageRect.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Rectangle(hdc, gageRect.left, gageRect.top, gageRect.right, gageRect.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

bool Player::PlayerCollision(int posX, int posY)
{
	TILE_POINT tp = { posX / 32, posY / 32 };

	if (tileinfo[tp.y][tp.x].terrain == TR_WATER)
	{
		return true;
	}

	if (tileinfo[tp.y][tp.x].obj != EMPTY && tileinfo[tp.y][tp.x].obj != BASICTRANSPORTBELT
		&& tileinfo[tp.y][tp.x].obj != HUMAN && tileinfo[tp.y][tp.x].obj != FORBIDDEN)
	{
		return true;
	}

	return false;

}

Player::Player()
{
}

Player::~Player()
{
}
