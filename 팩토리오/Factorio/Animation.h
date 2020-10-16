#pragma once
#include "pch.h"

class Animation
{
protected:
	vector<POINT> vecFramelist;		// key frame ��ġ ����Ʈ
	vector<int> vecPlayList;		// �÷��� ����Ʈ

	int frameCount;					// ��ü ������ ��
	int frameWidth;					// ������ ����ũ��
	int frameHeight;				// ������ ����ũ��

	bool isLoop;					// �ݺ� �Ǵ��� ����
	int nowPlayIdx;					// ���� �÷��� ������ �ε���
	bool isPlaying;					// ���� �÷��� ������ ����

	float keyFrameUpdateTime;		// ������Ʈ ���� �ð�
	float accumulateTime;			// �����ð�

public:
	HRESULT Init(int totalWidth, int totalHeight, int frameWidthCount, int frameHeightCount);
	virtual void SetPlayFrame(bool isReverse = FALSE, bool isLoop = FALSE);
	virtual void SetPlayFrame(int startFrame, int endFrame, bool isReverse = FALSE, bool isLoop = FALSE);
	virtual void SetPlayFrame(int* arr, int arrlength, BOOL isReverse = FALSE, BOOL isLoop = FALSE);
	virtual void UpdateKeyFrame(float dt);


	void SetUpdateTime(int fps) { keyFrameUpdateTime = 1.0f / fps; }

	POINT GetFramePos() { return vecFramelist[vecPlayList[nowPlayIdx]]; }

	void Start();
	void Stop();
	void Pause();
	void Resume();

	Animation();
	virtual ~Animation();
};
