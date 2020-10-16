// macroFunction.h
#pragma once
#include "pch.h"

inline void SetWindowSize(int x, int y, int width, int height)
{
	// 윈도우 작업영역 지정
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = width; rc.bottom = height;

	// 실제 윈도우 크기 받아온다.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 이동
	MoveWindow(g_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, true);
}

inline void RenderLine(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT GetRect(int x, int y, int size)
{
	RECT rc = { x, y, x + size, y + size };
	return rc;
}

inline RECT GetRectToCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2),
		x + (width / 2), y + (height / 2) };
	return rc;
}

inline void RenderRect(HDC hdc, int x, int y, int size)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + size, y);
	LineTo(hdc, x + size, y + size);
	LineTo(hdc, x, y + size);
	LineTo(hdc, x, y);
}

inline void RenderEllipse(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void RenderEllipseToCenter(HDC hdc, int centerX, int centerY,
	int width, int height)
{
	Ellipse(hdc, centerX - (width / 2), centerY - (height / 2),
		centerX + (width / 2), centerY + (height / 2));
}

// x, y : 시작위치
// width, height : 너비, 높이
inline void RenderRect(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// centerX, centerY : 사각형의 중점
// width, height : 너비, 높이
inline void RenderRectToCenter(HDC hdc, int centerX, int centerY,
	int width, int height)
{
	Rectangle(hdc, centerX - (width / 2), centerY - (height / 2),
		centerX + (width / 2), centerY + (height / 2));
}

// 충돌체크 함수
inline bool CheckRectCollision(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right ||
		rc1.right < rc2.left ||
		rc1.top > rc2.bottom ||
		rc1.bottom < rc2.top)
	{
		return false;
	}
	return true;
}

inline float GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float dist = sqrtf((x * x) + (y * y));

	return dist;
}

inline void AddInInventory(Layer _name, int num)
{	

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (inveninfo[i][j].name == _name && inveninfo[i][j].num <= 999)
			{
				inveninfo[i][j].num += num;
				goto skip;
			}

			//인벤터리가 비어있는 경우
			else if (inveninfo[i][j].name == EMPTY)
			{
				inveninfo[i][j].name = _name;
				inveninfo[i][j].num += num;
				inveninfo[i][j].isStorage = true;

				goto skip;
			}
		}
	}

skip:
	{}
}

inline void RoatateFunction(float _theta, float _posX, float _posY, int _width, int _height, POINT *point)
{
	POINT temppoint[3];
	float theta;

	temppoint[0].x = -_width / 2;
	temppoint[0].y = -_height / 2;
	temppoint[1].x = _width / 2;
	temppoint[1].y = -_height / 2;
	temppoint[2].x = -_width / 2;
	temppoint[2].y = _height / 2;

	theta = DEGREE_TO_RADIAN(_theta);

	for (int i = 0; i < 3; i++)
	{
		//원점이동
		point[i].x = temppoint[i].x*cosf(theta) - temppoint[i].y*sinf(theta) + _posX;
		point[i].y = temppoint[i].x*sinf(theta) + temppoint[i].y*cosf(theta) + _posY;

	}


}

inline bool CheckCollision(float x1, float y1, float size1, float x2, float y2, float size2)
{
	if (x1 + size1 / 2 < x2 - size2 / 2 || x1 - size1 / 2 > x2 + size2 / 2 || y1 - size1 / 2 > y2 + size2 / 2 || y1 + size1 / 2 < y2 - size2 / 2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

inline bool CheckCollision2(float x1, float y1, float size1, float size3, float x2, float y2, float size2, float size4)
{
	if (x1 + size1 / 2 < x2 - size2 / 2 || x1 - size1 / 2 > x2 + size2 / 2 || y1 - size3 / 2 > y2 + size4 / 2 || y1 + size3 / 2 < y2 - size4 / 2)
	{
		return false;
	}
	else
	{
		return true;
	}
}