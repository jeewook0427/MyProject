#pragma once
#include "GameNode.h"
#include "pch.h"

class Ash;
class Image;

class Item : public GameNode
{
private:

	Ash* ash;
	Image* candy;
	Image* beer;
	Image* buger;
	Image* cake;

	int alpha;
	int size;
	float angle;
	float speed;




	FPOINT pos;
	bool istop;
	bool isbottom;
	bool show;
	bool eat;

public:
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void SetPos(FPOINT _pos) { pos = _pos; }
	void SetShow(bool  _show) { show = _show; }
	void SetEat(bool  _eat) { eat = _eat; }
	void GetAsh(Ash* _ash) { ash = _ash; }
	int GetSize() { return size; }

	FPOINT GetPos() {
		return this->pos;
	}
	Item();
	~Item();
};

