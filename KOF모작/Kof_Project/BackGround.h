#pragma once
#include "GameNode.h"
#include <cstdlib>//
#include <ctime>//

class Image;
//class Athena;
//class SieKensou;
class BackGround : public GameNode
{
	float posX;
	float posY;

	int currentframeX, currentframeY;
	int comTime;
	int gameProcess;
	int mapSelectNum;
	float scale;
	float widthscale;//
	float heightscale;//

	Image* img;
	Image* startScreen;
	Image* selectScreen;
	Image* selectBackground;


	//SieKensou* siekensou;
	//Athena* athena;


public:
	virtual HRESULT Init()	override; // 문법적으로 잘못되었을 때 예외처리를 위해 필요
	virtual void Release()	override;
	virtual void Update()	override;
	virtual void Render(HDC hdc)	override;

	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }
	void SetScale(float _scale) { scale = _scale; }
	void SetGameProcess(int process) { gameProcess = process; }
	void SetMapSelectNum(int _selectnum) { mapSelectNum = _selectnum; }//

	BackGround();
	~BackGround();
};

