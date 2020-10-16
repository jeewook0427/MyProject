#include "Tutorial.h"
#include "Image.h"

// ����Ʈ ���
/*
	0. ���� Ȯ���ϱ�
	1. �κ��丮 â Ȯ���ϱ�
	---
	2. �ڿ� ä��
	---
	3. ũ����Ʈ ��� �̿�
	---
	4. ä���帱 ��ġ
	5. �뱤�� ��ġ
	6. �� �κ��丮 �̿�
	---
	7. ��Ʈ ��ġ
	8. �κ��� ��ġ
	---
	9. ��������� ����
	10. ������ ���� ��ȯ
	11. ������ �ݱ�
	---
	12. ȭ�¹����� ��ġ
	---
	13. ������ ��ġ
	---
	14. ����ü� ��ġ

	17. ���� ���
*/

void Tutorial::SucceedQuest_0()
{
	if (startQuest[0] && !succeedQuest[0])
	{
		succeedQuest[0] = true;

		//���� ����
		succeedQuest_box[0] = true;

		if (succeedQuest[1])
		{
			startQuest[2] = true;

			// ���� ����
			wsprintf(strText[0], "�ڿ� ä��");
			renderQBox[1] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// ����
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

		//���� ����
		succeedQuest_box[1] = true;

		if (succeedQuest[0])
		{
			startQuest[2] = true;

			// ���� ����
			wsprintf(strText[0], "�ڿ� ä��");
			renderQBox[1] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// ����
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

		//���� ����
		succeedQuest_box[0] = true;

		// ���� ����
		wsprintf(strText[0], "������ ����");

		for (int i = 0; i < 3; ++i)
		{
			succeedQuest_box[i] = false;
		}

		// ����
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

		//���� ����
		succeedQuest_box[0] = true;

		// ���� ����
		wsprintf(strText[0], "ȭ�� ä���� ��ġ");
		wsprintf(strText[1], "�� �뱤�� ��ġ");
		wsprintf(strText[2], "�� �κ��丮 �̿�");
		renderQBox[1] = true;
		renderQBox[2] = true;

		for (int i = 0; i < 3; ++i)
		{
			succeedQuest_box[i] = false;
		}

		// ����
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

		//���� ����
		succeedQuest_box[0] = true;

		if (succeedQuest[5] && succeedQuest[6])
		{
			startQuest[7] = true;
			startQuest[8] = true;

			// ���� ����
			wsprintf(strText[0], "��Ʈ ��ġ");
			wsprintf(strText[1], "ȭ�� ���Ա� ��ġ");
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// ����
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

		//���� ����
		succeedQuest_box[1] = true;

		if (succeedQuest[4] && succeedQuest[6])
		{
			startQuest[7] = true;
			startQuest[8] = true;

			// ���� ����
			wsprintf(strText[0], "��Ʈ ��ġ");
			wsprintf(strText[1], "ȭ�� ���Ա� ��ġ");
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// ����
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

		//���� ����
		succeedQuest_box[2] = true;

		if (succeedQuest[4] && succeedQuest[5])
		{
			startQuest[7] = true;
			startQuest[8] = true;

			// ���� ����
			wsprintf(strText[0], "��Ʈ ��ġ");
			wsprintf(strText[1], "ȭ�� ���Ա� ��ġ");
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// ����
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

		//���� ����
		succeedQuest_box[0] = true;

		if (succeedQuest[8])
		{
			startQuest[9] = true;
			startQuest[10] = true;
			startQuest[11] = true;

			// ���� ����
			wsprintf(strText[0], "���� ������ ����");
			wsprintf(strText[1], "���� ������ ���� ��ȯ");
			wsprintf(strText[2], "������ �ݱ�");
			renderQBox[2] = true;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// ����
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

		//���� ����
		succeedQuest_box[1] = true;

		if (succeedQuest[7])
		{
			startQuest[9] = true;
			startQuest[10] = true;
			startQuest[11] = true;

			// ���� ����
			wsprintf(strText[0], "���� ������ ����");
			wsprintf(strText[1], "���� ������ ���� ��ȯ");
			wsprintf(strText[2], "������ �ݱ�");
			renderQBox[2] = true;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// ����
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
		//���� ����
		succeedQuest_box[0] = true;

		if (succeedQuest[10] && succeedQuest[11])
		{
			startQuest[12] = true;

			// ���� ����
			wsprintf(strText[0], "ȭ�� ������ �Ǽ�");
			renderQBox[1] = false;
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// ����
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

		//���� ����
		succeedQuest_box[1] = true;

		if (succeedQuest[9] && succeedQuest[11])
		{
			startQuest[12] = true;

			// ���� ����
			wsprintf(strText[0], "ȭ�� ������ �Ǽ�");
			renderQBox[1] = false;
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// ����
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

		//���� ����
		succeedQuest_box[2] = true;

		if (succeedQuest[9] && succeedQuest[10])
		{
			startQuest[12] = true;

			// ���� ����
			wsprintf(strText[0], "ȭ�� ������ �Ǽ�");
			renderQBox[1] = false;
			renderQBox[2] = false;

			for (int i = 0; i < 3; ++i)
			{
				succeedQuest_box[i] = false;
			}

			// ����
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

		//���� ����
		succeedQuest_box[0] = true;

		// ���� ����
		wsprintf(strText[0], "���� ������ ��ġ");

		for (int i = 0; i < 3; ++i)
		{
			succeedQuest_box[i] = false;
		}

		// ����
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

		//���� ����
		succeedQuest_box[0] = true;

		// ���� ����
		wsprintf(strText[0], "���� �ü� ��ġ");

		for (int i = 0; i < 3; ++i)
		{
			succeedQuest_box[i] = false;
		}

		// ����
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

		//���� ����
		succeedQuest_box[0] = true;

		// ���� ����

		// ���� ����
		wsprintf(strText[0], "���� �߻�");

		for (int i = 0; i < 3; ++i)
		{
			succeedQuest_box[i] = false;
		}

		// ����
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

	//wsprintf(helpText, "HELPâ�� ������");
	//TextOut(hdc, 1460, 15, helpText, strlen(helpText));
	//wsprintf(helpText, "'Q'Ű�� ��������.");
	//TextOut(hdc, 1460, 40, helpText, strlen(helpText));


	if (helpOpen)
	{
		grayBox->AlphaRender(hdc, helpBox.left, helpBox.top, 500, 500, 150);

		switch (helpIndex)
		{
		case 0:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left  + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELPâ�� �����Ϸ��� 'Q'Ű�� ��������.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "�κ��丮â Ȯ��: 'E'");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));
			wsprintf(helpText, "������ ������ 'CTRL'Ű�� ���� �� ������");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 140, helpText, strlen(helpText));
			wsprintf(helpText, "�������� ������ ���� �� �ֽ��ϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 170, helpText, strlen(helpText));

			wsprintf(helpText, "�� Ȯ�� : 'M'");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 210, helpText, strlen(helpText));

			break;

		case 1:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELPâ�� �����Ϸ��� 'Q'Ű�� ��������.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "�ڿ� ä��: �ڿ��� ���콺�� �ø� �� ��Ŭ��");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			break;

		case 2:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELPâ�� �����Ϸ��� 'Q'Ű�� ��������.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "������ ����: �κ��丮�� �� ���� ������ ũ����Ʈâ����");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));
			wsprintf(helpText, "������ �������� ���� ����");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 140, helpText, strlen(helpText));

			wsprintf(helpText, "�߰� ����ǰ�� ���� ��� �ڵ����� ���� ����˴ϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 170, helpText, strlen(helpText));
			wsprintf(helpText, "�̸� �߰� ����ǰ�� ����� �ð��� �����ϼ���.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 200, helpText, strlen(helpText));

			break;

		case 3:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELPâ�� �����Ϸ��� 'Q'Ű�� ��������.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "ȭ�� �ü����� ����� ��ź�� ������ ����մϴ�.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			wsprintf(helpText, "ȭ�� ä���帱: ȭ�� ä���帱�� ��ġ�ϼ���.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 150, helpText, strlen(helpText));
			wsprintf(helpText, "�ڿ��� �ڵ����� ä���մϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 180, helpText, strlen(helpText));


			wsprintf(helpText, "���� �뱤��: ����뱤�θ� ��ġ�ϼ���.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 220, helpText, strlen(helpText));
			wsprintf(helpText, "������ ö�� �����ǰ� ö������ �����մϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 250, helpText, strlen(helpText));


			wsprintf(helpText, "�� �κ��丮: ��ġ�� �ü��� �ٰ��� Ŭ���ϸ�");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 290, helpText, strlen(helpText));
			wsprintf(helpText, "�� �κ��丮�� �� �� �ֽ��ϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 320, helpText, strlen(helpText));
			wsprintf(helpText, "-�� ���: ���� ĭ");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 350, helpText, strlen(helpText));
			wsprintf(helpText, "-�� �ϴ�: ��� ĭ");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 380, helpText, strlen(helpText));
			wsprintf(helpText, "-�� ���: ����ǰ ĭ");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 410, helpText, strlen(helpText));

			break;

		case 4:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELPâ�� �����Ϸ��� 'Q'Ű�� ��������.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "��� ��Ʈ: ��� ��Ʈ�� ��ġ�ϼ���.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));
			
			wsprintf(helpText, "ȭ�� ���Ա�: ȭ�� ���Ա⸦ ��ġ�ϼ���");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 150, helpText, strlen(helpText));
			wsprintf(helpText, "-���� �ű��: ");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 180, helpText, strlen(helpText));
			wsprintf(helpText, "���� ������ �� ���� ���� ������ ������");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 210, helpText, strlen(helpText));
			wsprintf(helpText, "�ݴ� �������� �ű�ϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 240, helpText, strlen(helpText));

			wsprintf(helpText, "-���� ����: ");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 270, helpText, strlen(helpText));
			wsprintf(helpText, "�ű� �ڸ��� �ü��� ������ ���Ե˴ϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 300, helpText, strlen(helpText));
			wsprintf(helpText, "������ ���ᳪ ��ᰡ �ƴϸ� ���Ե��� �ʰ�");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 330, helpText, strlen(helpText));
			wsprintf(helpText, "�ٴڿ� �������� �����ϼ���.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 360, helpText, strlen(helpText));

			wsprintf(helpText, "-���� ������: ");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 390, helpText, strlen(helpText));
			wsprintf(helpText, "ȸ�� ��ġ�� �ü��� ������ ����ǰ�� �����ϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 420, helpText, strlen(helpText));

			break;

		case 5:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELPâ�� �����Ϸ��� 'Q'Ű�� ��������.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "��������� ����: �ü��� ���콺�� �ø� �� ��Ŭ��");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			wsprintf(helpText, "������ ���� ��ȯ: ������ ���� ���� 'R' Ű");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 150, helpText, strlen(helpText));

			wsprintf(helpText, "������ �ݱ�: ������ ������ 'Z' Ű");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 190, helpText, strlen(helpText));


			break;

		case 6:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELPâ�� �����Ϸ��� 'Q'Ű�� ��������.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "ȭ�� ������: ���⸦ �����մϴ�.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			wsprintf(helpText, "�������� �Ǽ� �� �� �ֽ��ϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 140, helpText, strlen(helpText));

			wsprintf(helpText, "����! ȭ�� �����Ҵ� ��ź, ���� ���Ḧ �־�� �۵��մϴ�.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 170, helpText, strlen(helpText));

			break;

		case 7:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELPâ�� �����Ϸ��� 'Q'Ű�� ��������.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "������: ���⸦ ����ɴϴ�.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			wsprintf(helpText, "������ �������� ���Ⱑ �帣�� ������");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 140, helpText, strlen(helpText));
			wsprintf(helpText, "������ ���� ��ü�� ���⸦ �۶߸��ϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 170, helpText, strlen(helpText));
		
			wsprintf(helpText, "���� �ü����� ���� ���� �ȿ���");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 210, helpText, strlen(helpText));
			wsprintf(helpText, "���⸦ ����� �����˴ϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 240, helpText, strlen(helpText));

			break;

		case 8:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELPâ�� �����Ϸ��� 'Q'Ű�� ��������.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "���� �ü�: ������ ��ǰ�� �ڵ����� �����մϴ�.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));


			break;

		case 9:
			wsprintf(helpText, "HELP");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 50, helpText, strlen(helpText));
			wsprintf(helpText, "HELPâ�� �����Ϸ��� 'Q'Ű�� ��������.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 70, helpText, strlen(helpText));

			wsprintf(helpText, "��! �ڵ�ȭ ���� Ʃ�丮���� �������ϴ�.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 110, helpText, strlen(helpText));

			wsprintf(helpText, "���Ϲ߻�밡 ���޵Ǿ����ϴ�.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 140, helpText, strlen(helpText));

			wsprintf(helpText, "������ ����� �༺�� Ż���ϼ���.");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 170, helpText, strlen(helpText));

			wsprintf(helpText, "TIP �й��: ȸ�� ������ ������");
			TextOut(hdc, helpBox.left + 50, helpBox.top + 200, helpText, strlen(helpText));
			wsprintf(helpText, "�ݴ� ���⿡ �� ������ ������ ���� �����ϴ�.");
			TextOut(hdc, helpBox.left + 130, helpBox.top + 230, helpText, strlen(helpText));
			
			break;
		}


		grayBox->Render(hdc, openBtRc.left + 50, openBtRc.top + 25, 100, 50);

		wsprintf(helpText, "�ڵ� OPEN");
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

	wsprintf(strText[0], "���� Ȯ���ϱ�");
	wsprintf(strText[1], "�κ��丮â Ȯ���ϱ�");
	
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
