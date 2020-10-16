#include "SoundManager.h"
HRESULT SoundManager::Init()
{
	//사운드 시스템 생성
	System_Create(&system);
	// 채널 생성
	system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);
	//사운드랑 채널 동적 확보
	sound = new Sound*[TOTALSOUNDBUFFER];
	channel = new Channel*[TOTALSOUNDBUFFER];
	memset(sound, 0, sizeof(Sound*)*TOTALSOUNDBUFFER);// sound의( 첫번째 변수) 시작 주소 부터(두번째 변수) 해서 사이즈 크기( 세번째 변수) 만큼 초기화 함.
	memset(channel, 0, sizeof(Channel*)*TOTALSOUNDBUFFER);
	return S_OK;
}
void SoundManager::Release()
{
	SAFE_ARR_DELETE(sound);
	SAFE_ARR_DELETE(channel);
	system->close();// 종료하는 함수 
	system->release();
}
void SoundManager::Update()
{
	if (system)
	{
		system->update();
	}
}
void SoundManager::AddSound(string key, string filePath, bool isBGM, bool isLoop)
{
	//system->createSound();//기본적으로 루프가 적은 파일 
	//system->createStream();//파일 크기가 큰 사운드 BGM
	if (isLoop)
	{
		if (isBGM)
		{
			system->createStream(filePath.c_str(), FMOD_LOOP_NORMAL, 0, &sound[mapSoundDatas.size()]);
		}
		else
		{
			system->createSound(filePath.c_str(), FMOD_LOOP_NORMAL, 0, &sound[mapSoundDatas.size()]);
		}
	}
	else
	{
		system->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &sound[mapSoundDatas.size()]);// 추가되기 전의 사이즈( 인덱스 값이랑 같음;) 
	}
	mapSoundDatas.insert(make_pair(key, &sound[mapSoundDatas.size()]));
}
void SoundManager::Play(string key, float volume)
{
	//system->playSound(channel)
	//auto Sound1 = mapSoundDatas.find(key)->second;//*Sound1
	map<string, Sound**> ::iterator itms;
	int count = 0;
	for (itms = mapSoundDatas.begin(); itms != mapSoundDatas.end(); itms++)
	{
		count++;
		if (itms->first == key)
		{
			system->playSound(FMOD_CHANNEL_FREE, *mapSoundDatas[key], false, &channel[count]);
			channel[count]->setVolume(volume);
			break;
		}
	}
	//chnnel->setVolume(volume);
}
void SoundManager::Stop(string key)
{
	map<string, Sound**> ::iterator itms;
	int count = 0;
	for (itms = mapSoundDatas.begin(); itms != mapSoundDatas.end(); itms++)
	{
		count++;
		if (itms->first == key)
		{
			channel[count]->stop();
			break;
		}
	}
}
void SoundManager::Pause(string key)
{
	map<string, Sound**> ::iterator itms;
	int count = 0;
	for (itms = mapSoundDatas.begin(); itms != mapSoundDatas.end(); itms++)
	{
		count++;
		if (itms->first == key)
		{
			channel[count]->setPaused(true);
			break;
		}
	}
}
void SoundManager::Resume(string key)
{
	map<string, Sound**> ::iterator itms;
	int count = 0;
	for (itms = mapSoundDatas.begin(); itms != mapSoundDatas.end(); itms++)
	{
		count++;
		if (itms->first == key)
		{
			channel[count]->setPaused(false);
			break;
		}
	}
}
SoundManager::SoundManager() :system(nullptr), sound(nullptr), channel(nullptr)
{
}
SoundManager::~SoundManager()
{
}