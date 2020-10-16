#pragma once
#include "pch.h"
#include "SingletonBase.h"

//#include <map> //0번에 에네미의 이미지, 1번에 플레이어에 대한 이미지 ... 이렇게 많아지면 구분하기 힘들어진다.
//따라서 map이라는 것을 사용해 Enemy라는 이름으로 이미지를 저장하고, Player라는 이름으로 player이미지를 저장하고...
//프로그래머가 구분하기쉽게 키워드를 매칭하고 싶을 때 사용하는 자료구조. -> key와 value(메모리에 저장할 데이터)로 저장한다.
//#include <string> //key의 타입

class Image;
class ImageManager : public SingletonBase<ImageManager>
{
private:
	//맵의 key의 타입은 string이고 value 타입은 *이다.,
	map<string, Image*> mapImageDatas;

public:
	HRESULT Init();
	void Release();

	Image* AddImage(string strKey, int width, int height);

	//파일에서 추가
	Image* AddImage(string strKey, const char* fileName, int width, int height, bool trans = FALSE, COLORREF transColor = FALSE);

	//애니메이션 구조포함해서 추가
	Image* AddImage(string strKey, const char* fileName, float x, float y, int width, int height,
		int keyFrameX, int keyFrameY,
		bool trans = FALSE, COLORREF transColor = FALSE);

	Image* FindImage(string strKey);

	void DeleteImage(string strKey);
	void DeleteAll();

};

