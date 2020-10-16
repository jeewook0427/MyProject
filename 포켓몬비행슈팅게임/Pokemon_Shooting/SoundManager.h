#pragma once
#include "SingletonBase.h"
//#include <fmod_errors.h>
#include <string>
#include "pch.h"
#include "inc/fmod.hpp"
#pragma comment (lib,"lib/fmodex_vc.lib")
using namespace FMOD;
#define SOUNDBUFFER	10
#define EXTRACGANNELBUFFER	5
#define TOTALSOUNDBUFFER	SOUNDBUFFER*EXTRACGANNELBUFFER
class SoundManager : public SingletonBase<SoundManager>
{
private:
	FMOD::System* system;
	Sound** sound;// 이중 포인터 주의 
	FMOD::Channel**  channel;
	map<string, Sound**> mapSoundDatas;
public:
	HRESULT Init();
	void Release();
	void Update();
	void AddSound(string key, string filePath, bool isBGM = false, bool isLoop = false);
	void Play(string key, float volume = 1.0f);
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);
	SoundManager();
	~SoundManager();
};