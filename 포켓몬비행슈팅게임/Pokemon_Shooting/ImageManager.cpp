#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{

	return S_OK;
}

void ImageManager::Release()
{
	DeleteAll();
}

Image* ImageManager::AddImage(string strKey, int width, int height)
{
	Image* image = FindImage(strKey);

	if (image)	return image; //찾는 이미지가 있으면 return.

	image = new Image(); //없으면 새로 동적할당.

	if (FAILED(image->Init(width, height)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}

	mapImageDatas.insert(make_pair(strKey, image)); //맵에 쌍으로 처리해서 저장한다.

	return image;
}

Image* ImageManager::AddImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor)
{
	Image* image = FindImage(strKey);

	if (image)	return image; //찾는 이미지가 있으면 return.

	image = new Image(); //없으면 새로 동적할당.


	if (FAILED(image->Init(fileName, width, height, trans, transColor)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}


	mapImageDatas.insert(make_pair(strKey, image)); //맵에 쌍으로 처리해서 저장한다.

	return image;
}

Image* ImageManager::AddImage(string strKey, const char* fileName, float x, float y, int width, int height, int keyFrameX, int keyFrameY, bool trans, COLORREF transColor)
{
	Image* image = FindImage(strKey);

	if (image)	return image; //찾는 이미지가 있으면 return.

	image = new Image(); //없으면 새로 동적할당.

	if (FAILED(image->Init(fileName, x, y, width, height, keyFrameX, keyFrameY, trans, transColor)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}
	mapImageDatas.insert(make_pair(strKey, image));

	return image;
}

Image* ImageManager::FindImage(string strKey)
{
	//mapImageDatas.find가 iterator형으로 반환해서 그 자료형으로 받아줘야한다.
	map<string, Image*>::iterator iter = mapImageDatas.find(strKey);
	if (iter != mapImageDatas.end()) // 키와 밸류가 안들어있는 그냥 의미상의 마지막 주소가 나온다.	
	{
		return iter->second;	//트리구조로 되어있기 때문에 정렬이 되어 있어서 검색이 빠르다.
	}

	return nullptr;
}

void ImageManager::DeleteImage(string strKey)
{
	map<string, Image*>::iterator iter = mapImageDatas.find(strKey);
	if (iter != mapImageDatas.end()) // 키와 밸류가 안들어있는 그냥 의미상의 마지막 주소가 나온다.	
									 // iter == mapImageDatas.end() --> 같은 경우는 우리가 키로 찾는 iterator가 없다는 말이다.
	{
		(iter->second)->Release();
		SAFE_DELETE((iter->second));

		mapImageDatas.erase(iter);
	}
}

void ImageManager::DeleteAll()
{
	map<string, Image*>::iterator iter;

	for (iter = mapImageDatas.begin(); iter != mapImageDatas.end(); /*iter++*/) //가장 처음 요소가 들어있는 주소를 반환하는 함수
	{
		if (iter->second != nullptr)
		{
			// second(value)를 메모리 해제
			(iter->second)->Release();
			SAFE_DELETE(iter->second);

			// key, value (pair)를 메모리 해제
			iter = mapImageDatas.erase(iter); //삭제하는 요소의 다음 요소를 자동으로 반환한다. iter가 받아주면 ++할 필요가 없어진다.
		}
		else
		{
			iter++;
		}
	}

	// 맵을 메모리 해제
	mapImageDatas.clear(); //완전 초기화를 진행한다.
}
