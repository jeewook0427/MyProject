#pragma once
#include "pch.h"
#include <map>

class Image;
class FlyWeight
{
private:
	Image* image;
	map<string, Image*> mapimage;

public:

	void Init();

	FlyWeight();
	~FlyWeight();
};

