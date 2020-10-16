#include "Tutorial.h"
#include "Image.h"

// 퀘스트 목록
/*
	0. 맵을 확인하기
	1. 인벤토리 창 확인하기
	---
	2. 자원 채취
	---
	3. 크래프트 기능 이용
	---
	4. 채광드릴 설치
	5. 용광로 설치
	6. 툴 인벤토리 이용
	---
	7. 밸트 설치
	8. 로봇팔 설치
	---
	9. 설비아이템 수거
	10. 아이템 방향 전환
	11. 아이템 줍기
	---
	12. 화력발전소 설치
	---
	13. 전신주 설치
	---
	14. 생산시설 설치

	17. 로켓 쏘기
*/

void Tutorial::SucceedQuest_0()
{
	if (startQuest[0] && !succeedQuest[0])
	{
		succeedQuest[0] = true;

		//렌더 정보
		succeedQuest_box[0] = true;

		if (succeedQuest[1])
		{
			startQuest[2] = true;

			// 렌더 정보
			wsprintf(strText[0], "자원 채취");
			renderQBox[1] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// 헬프
			if(openBtOn)
				helpOpen = true;
			helpIndex = 1;
		}
	}
}

void Tutorial::SucceedQuest_1()
{
	if (startQuest[1] && !succeedQuest[1])
	{
		succeedQuest[1] = true;

		//렌더 정보
		succeedQuest_box[1] = true;

		if (succeedQuest[0])
		{
			startQuest[2] = true;

			// 렌더 정보
			wsprintf(strText[0], "자원 채취");
			renderQBox[1] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// 헬프
			if (openBtOn)
				helpOpen = true;
			helpIndex = 1;
		}
	}
}

void Tutorial::SucceedQuest_2()
{
	if (startQuest[2] && !succeedQuest[2])
	{
		succeedQuest[2] = true;

		startQuest[3] = true;

		//렌더 정보
		succeedQuest_box[0] = true;

		// 렌더 정보
		wsprintf(strText[0], "아이템 제작");

		for (int i = 0; i < 3; ++i)
		{
			succeedQuest_box[i] = false;
		}

		// 헬프
		if (openBtOn)
			helpOpen = true;
		helpIndex = 2;
	}
}

void Tutorial::SucceedQuest_3()
{
	if (startQuest[3] && !succeedQuest[3])
	{
		succeedQuest[3] = true;

		startQuest[4] = true;
		startQuest[5] = true;
		startQuest[6] = true;

		//렌더 정보
		succeedQuest_box[0] = true;

		// 렌더 정보
		wsprintf(strText[0], "화력 채굴기 설치");
		wsprintf(strText[1], "돌 용광로 설치");
		wsprintf(strText[2], "툴 인벤토리 이용");
		renderQBox[1] = true;
		renderQBox[2] = true;

		for (int i = 0; i < 3; ++i)
		{
			succeedQuest_box[i] = false;
		}

		// 헬프
		if (openBtOn)
			helpOpen = true;
		helpIndex = 3;
	}
}

void Tutorial::SucceedQuest_4()
{
	if (startQuest[4] && !succeedQuest[4])
	{
		succeedQuest[4] = true;

		//렌더 정보
		succeedQuest_box[0] = true;

		if (succeedQuest[5] && succeedQuest[6])
		{
			startQuest[7] = true;
			startQuest[8] = true;

			// 렌더 정보
			wsprintf(strText[0], "밸트 설치");
			wsprintf(strText[1], "화력 투입기 설치");
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// 헬프
			if (openBtOn)
				helpOpen = true;
			helpIndex = 4;
		}
	}
}

void Tutorial::SucceedQuest_5()
{
	if (startQuest[5] && !succeedQuest[5])
	{
		succeedQuest[5] = true;

		//렌더 정보
		succeedQuest_box[1] = true;

		if (succeedQuest[4] && succeedQuest[6])
		{
			startQuest[7] = true;
			startQuest[8] = true;

			// 렌더 정보
			wsprintf(strText[0], "밸트 설치");
			wsprintf(strText[1], "화력 투입기 설치");
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// 헬프
			if (openBtOn)
				helpOpen = true;
			helpIndex = 4;
		}
	}
}

void Tutorial::SucceedQuest_6()
{
	if (startQuest[6] && !succeedQuest[6])
	{
		succeedQuest[6] = true;

		//렌더 정보
		succeedQuest_box[2] = true;

		if (succeedQuest[4] && succeedQuest[5])
		{
			startQuest[7] = true;
			startQuest[8] = true;

			// 렌더 정보
			wsprintf(strText[0], "밸트 설치");
			wsprintf(strText[1], "화력 투입기 설치");
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// 헬프
			if (openBtOn)
				helpOpen = true;
			helpIndex = 4;
		}
	}
}

void Tutorial::SucceedQuest_7()
{
	if (startQuest[7] && !succeedQuest[7])
	{
		succeedQuest[7] = true;

		//렌더 정보
		succeedQuest_box[0] = true;

		if (succeedQuest[8])
		{
			startQuest[9] = true;
			startQuest[10] = true;
			startQuest[11] = true;

			// 렌더 정보
			wsprintf(strText[0], "설비 아이템 수거");
			wsprintf(strText[1], "설비 아이템 방향 전환");
			wsprintf(strText[2], "아이템 줍기");
			renderQBox[2] = true;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// 헬프
			if (openBtOn)
				helpOpen = true;
			helpIndex = 5;
		}
	}
}

void Tutorial::SucceedQuest_8()
{
	if (startQuest[8] && !succeedQuest[8])
	{
		succeedQuest[8] = true;

		//렌더 정보
		succeedQuest_box[1] = true;

		if (succeedQuest[7])
		{
			startQuest[9] = true;
			startQuest[10] = true;
			startQuest[11] = true;

			// 렌더 정보
			wsprintf(strText[0], "설비 아이템 수거");
			wsprintf(strText[1], "설비 아이템 방향 전환");
			wsprintf(strText[2], "아이템 줍기");
			renderQBox[2] = true;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// 헬프
			if (openBtOn)
				helpOpen = true;
			helpIndex = 5;
		}
	}
}

void Tutorial::SucceedQuest_9()
{
	if (startQuest[9] && !succeedQuest[9])
	{
		succeedQuest[9] = true;
		//AddInInventory(ROCKET, 1);
		//렌더 정보
		succeedQuest_box[0] = true;

		if (succeedQuest[10] && succeedQuest[11])
		{
			startQuest[12] = true;

			// 렌더 정보
			wsprintf(strText[0], "화력 발전소 건설");
			renderQBox[1] = false;
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// 헬프
			if (openBtOn)
				helpOpen = true;
			helpIndex = 6;
		}
	}
}

void Tutorial::SucceedQuest_10()
{
	if (startQuest[10] && !succeedQuest[10])
	{
		succeedQuest[10] = true;

		//렌더 정보
		succeedQuest_box[1] = true;

		if (succeedQuest[9] && succeedQuest[11])
		{
			startQuest[12] = true;

			// 렌더 정보
			wsprintf(strText[0], "화력 발전소 건설");
			renderQBox[1] = false;
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// 헬프
			if (openBtOn)
				helpOpen = true;
			helpIndex = 6;
		}
	}
}

void Tutorial::SucceedQuest_11()
{
	if (startQuest[11] && !succeedQuest[11])
	{
		succeedQuest[11] = true;

		//렌더 정보
		succeedQuest_box[2] = true;

		if (succeedQuest[9] && succeedQuest[10])
		{
			startQuest[12] = true;

			// 렌더 정보
			wsprintf(strText[0], "화력 발전소 건설");
			renderQBox[1] = false;
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// 헬프
			if (openBtOn)
				helpOpen = true;
			helpIndex = 6;
		}
	}
}

void Tutorial::SucceedQuest_12()
{
	if (startQuest[12] && !succeedQuest[12])
	{
		succeedQuest[12] = true;

		startQuest[13] = true;

		//렌더 정보
		succeedQuest_box[0] = true;

		// 렌더 정보
		wsprintf(strText[0], "소형 전신주 설치");

		for (int i = 0; i < 3; ++i)
		{
			succeedQuest_box[i] = false;
		}

		// 헬프
		if (openBtOn)
			helpOpen = true;
		helpIndex = 7;
	}
}

void Tutorial::SucceedQuest_13()
{
	if (startQuest[13] && !succeedQuest[13])
	{
		succeedQuest[13] = true;

		startQuest[14] = true;

		//렌더 정보
		succeedQuest_box[0] = true;

		// 렌더 정보
		wsprintf(strText[0], "생산 시설 설치");

		for (int i = 0; i < 3; ++i)
		{
			succeedQuest_box[i] = false;
		}

		// 헬프
		if (openBtOn)
			helpOpen = true;
		helpIndex = 8;
	}
}

void Tutorial::SucceedQuest_14()
{
	if (startQuest[14] && !succeedQuest[14])
	{
		succeedQuest[14] = true;

		//렌더 정보
		succeedQuest_box[0] = true;

		// 보상 로켓

		// 렌더 정보
		wsprintf(strText[0], "로켓 발사");

		for (int i = 0; i < 3; ++i)
		{
			succeedQuest_box[i] = false;
		}

		// 헬프
		if (openBtOn)
			helpOpen = true;
		helpIndex = 9;
	}
}

void Tutorial::Update()
{
	if (helpOpen)
	{
		if (PtInRect(&openBtRc, g_ptMouse))
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
			{
				openBtOn = !openBtOn;
			}
		}
	}
}

void Tutorial::Render(HDC hdc)
{
	for (int i = 0; i < 3; ++i)
	{
		if (renderQBox[i])
		{
			if (!succeedQuest_box[i])
			{
				grayBox->AlphaRender(hdc, renderPos[i].x, renderPos[i].y, Q_WIDTH, Q_HEIGHT, 150);
			}
			else
			{
				greenBox->AlphaRender(hdc, renderPos[i].x, renderPos[i].y, Q_WIDTH, Q_HEIGHT, 150);
			}

			TextOut(hdc, renderPos[i].x + 10, renderPos[i].y + 20, strText[i], strlen(strText[i]));
		}
	}

}


void Tutorial::HelpRender(HDC hdc)
{

	//grayBox->AlphaRender(hdc, 1385, 0, 210, 170, 200);

	//wsprintf(helpText, "HELP창을 열려면");
	//TextOut(hdc, 1460, 15, helpText, strlen(helpText));
	//wsprintf(helpText, "'Q'키를 누르세요.");
	//TextOut(hdc, 1460, 40, helpText, strlen(helpText));


	if (helpOpen)
	{
		grayBox->AlphaRender(hdc, helpBox.left, helpBox.top, 500, 500, 150);

		switch (helpIndex)
		{
		case 0:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left  + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELP창을 종료하려면 'Q'키를 누르세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "인벤토리창 확인: 'E'");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));
			wsprintf(helpText, "아이템 선택후 'CTRL'키를 누른 후 놓으면");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 140, helpText, strlen(helpText));
			wsprintf(helpText, "아이템을 반으로 나눌 수 있습니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 170, helpText, strlen(helpText));

			wsprintf(helpText, "맵 확인 : 'M'");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 210, helpText, strlen(helpText));

			break;

		case 1:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELP창을 종료하려면 'Q'키를 누르세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "자원 채취: 자원에 마우스를 올린 후 우클릭");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			break;

		case 2:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELP창을 종료하려면 'Q'키를 누르세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "아이템 제작: 인벤토리를 연 다음 오른쪽 크래프트창에서");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));
			wsprintf(helpText, "아이템 아이콘을 눌러 제작");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 140, helpText, strlen(helpText));

			wsprintf(helpText, "중간 생산품이 있을 경우 자동으로 먼저 생산됩니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 170, helpText, strlen(helpText));
			wsprintf(helpText, "미리 중간 생산품을 만들어 시간을 절약하세요.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 200, helpText, strlen(helpText));

			break;

		case 3:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELP창을 종료하려면 'Q'키를 누르세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "화력 시설들은 연료로 석탄과 나무를 사용합니다.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			wsprintf(helpText, "화력 채광드릴: 화력 채광드릴을 설치하세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 150, helpText, strlen(helpText));
			wsprintf(helpText, "자원을 자동으로 채광합니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 180, helpText, strlen(helpText));


			wsprintf(helpText, "석재 용광로: 석재용광로를 설치하세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 220, helpText, strlen(helpText));
			wsprintf(helpText, "구리와 철을 구리판과 철판으로 제련합니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 250, helpText, strlen(helpText));


			wsprintf(helpText, "툴 인벤토리: 설치한 시설에 다가가 클릭하면");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 290, helpText, strlen(helpText));
			wsprintf(helpText, "툴 인벤토리를 열 수 있습니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 320, helpText, strlen(helpText));
			wsprintf(helpText, "-좌 상단: 연료 칸");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 350, helpText, strlen(helpText));
			wsprintf(helpText, "-좌 하단: 재료 칸");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 380, helpText, strlen(helpText));
			wsprintf(helpText, "-우 상단: 생산품 칸");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 410, helpText, strlen(helpText));

			break;

		case 4:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELP창을 종료하려면 'Q'키를 누르세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "운반 밸트: 운반 밸트를 설치하세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));
			
			wsprintf(helpText, "화력 투입기: 화력 투입기를 설치하세요");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 150, helpText, strlen(helpText));
			wsprintf(helpText, "-물건 옮기기: ");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 180, helpText, strlen(helpText));
			wsprintf(helpText, "정지 상태일 때 팔이 향한 방향의 물건을");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 210, helpText, strlen(helpText));
			wsprintf(helpText, "반대 방향으로 옮깁니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 240, helpText, strlen(helpText));

			wsprintf(helpText, "-물건 투입: ");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 270, helpText, strlen(helpText));
			wsprintf(helpText, "옮긴 자리에 시설이 있으면 투입됩니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 300, helpText, strlen(helpText));
			wsprintf(helpText, "적절한 연료나 재료가 아니면 투입되지 않고");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 330, helpText, strlen(helpText));
			wsprintf(helpText, "바닥에 떨어지니 주의하세요.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 360, helpText, strlen(helpText));

			wsprintf(helpText, "-물건 꺼내기: ");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 390, helpText, strlen(helpText));
			wsprintf(helpText, "회수 위치에 시설이 있으면 생산품을 꺼냅니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 420, helpText, strlen(helpText));

			break;

		case 5:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELP창을 종료하려면 'Q'키를 누르세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "설비아이템 수거: 시설에 마우스를 올린 후 우클릭");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			wsprintf(helpText, "아이템 방향 전환: 아이템 생산 전에 'R' 키");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 150, helpText, strlen(helpText));

			wsprintf(helpText, "아이템 줍기: 아이템 위에서 'Z' 키");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 190, helpText, strlen(helpText));


			break;

		case 6:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELP창을 종료하려면 'Q'키를 누르세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "화력 발전소: 전기를 생산합니다.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			wsprintf(helpText, "물가에서 건설 할 수 있습니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 140, helpText, strlen(helpText));

			wsprintf(helpText, "주의! 화력 발전소는 석탄, 나무 연료를 넣어야 작동합니다.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 170, helpText, strlen(helpText));

			break;

		case 7:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELP창을 종료하려면 'Q'키를 누르세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "전신주: 전기를 끌어옵니다.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			wsprintf(helpText, "전신주 범위내에 전기가 흐르고 있으면");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 140, helpText, strlen(helpText));
			wsprintf(helpText, "전신주 범위 전체에 전기를 퍼뜨립니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 170, helpText, strlen(helpText));
		
			wsprintf(helpText, "전기 시설들은 전기 범위 안에서");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 210, helpText, strlen(helpText));
			wsprintf(helpText, "전기를 연료로 가동됩니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 240, helpText, strlen(helpText));

			break;

		case 8:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELP창을 종료하려면 'Q'키를 누르세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "생산 시설: 선택한 물품을 자동으로 생산합니다.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));


			break;

		case 9:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELP창을 종료하려면 'Q'키를 누르세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "축! 자동화 공정 튜토리얼이 끝났습니다.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			wsprintf(helpText, "로켓발사대가 지급되었습니다.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 140, helpText, strlen(helpText));

			wsprintf(helpText, "로켓을 만들어 행성을 탈출하세요.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 170, helpText, strlen(helpText));

			wsprintf(helpText, "TIP 분배기: 회수 방향의 물건을");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 200, helpText, strlen(helpText));
			wsprintf(helpText, "반대 방향에 두 갈래로 나누어 내려 놓습니다.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 230, helpText, strlen(helpText));
			
			break;
		}


		grayBox->Render(hdc, openBtRc.left + 50, openBtRc.top + 25, 100, 50);

		wsprintf(helpText, "자동 OPEN");
		TextOut(hdc, openBtRc.left + 20, openBtRc.top + 10, helpText, strlen(helpText));

		if (openBtOn)
			wsprintf(helpText, "ON");
		else
			wsprintf(helpText, "CLOSE");
		TextOut(hdc, openBtRc.left + 20, openBtRc.top + 30, helpText, strlen(helpText));
	}
}


Tutorial::Tutorial()
{
	startQuest[0] = true;
	startQuest[1] = true;

	for (int i = 2; i < Q_NUM; ++i)
	{
		startQuest[i] = false;
		succeedQuest[i] = false;
	}


	grayBox = ImageManager::GetSingleton()->FindImage("grayBox");
	greenBox = ImageManager::GetSingleton()->FindImage("greenBox");


	renderPos[0] = { Q_START_X, Q_START_Y };
	renderPos[1] = { Q_START_X, Q_START_Y - Q_HEIGHT + 1};
	renderPos[2] = { Q_START_X, Q_START_Y - Q_HEIGHT - Q_HEIGHT + 2};

	renderQBox[0] = true;	renderQBox[1] = true;	renderQBox[2] = false;

	wsprintf(strText[0], "맵을 확인하기");
	wsprintf(strText[1], "인벤토리창 확인하기");
	
	for (int i = 0; i < 3; ++i)
	{
		succeedQuest_box[i] = false;
	}

	helpIndex = 0;
	helpOpen = true;
	helpBox = { WINSIZE_X / 2 - 250, 200, WINSIZE_X / 2 + 250, 700 };

	openBtOn = true;
	openBtRc = { WINSIZE_X / 2 + 150, 200, WINSIZE_X / 2 + 250, 250 };
};
