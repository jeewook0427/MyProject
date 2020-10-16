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
	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

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

