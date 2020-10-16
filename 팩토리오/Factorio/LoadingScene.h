#pragma once
#include "GameNode.h"

class Image;
class LoadingScene : public GameNode
{
private:
	Image* logo;

	HBRUSH hBrush, hOldBrush;
	HFONT hFont, hOldFont;
	FONT font;

public:

	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	LoadingScene();
	virtual ~LoadingScene();
};

