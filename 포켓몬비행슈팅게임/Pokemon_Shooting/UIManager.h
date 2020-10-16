#pragma once
#include "GameNode.h"
#include "pch.h"

class Image;
class UIManager
{
private:
	int HP;
	int posX;
	int posY;
	int enemyWave;
	int score;

	HFONT hFont, hOldFont;
	HBRUSH hBrush, hOldBrush;
	Image* BHP;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetHp(int _hp) { HP = _hp; }
	int GetHp() { return HP; }
	int GetSocre() { return score; }

	void PrintText(HDC hdc);
	void PrintClearScore(HDC hdc, int Life, int _score, bool ending = false);
	void PrintHPbar(HDC hdc);
	void SetEnemyWave(int _enemywave) { enemyWave = _enemywave; }
	void SetScore(int _score) { score = _score; }

	UIManager();
	~UIManager();
};

