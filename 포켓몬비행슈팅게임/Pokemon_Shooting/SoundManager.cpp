#include "SoundManager.h"
HRESULT SoundManager::Init()
{
	//���� �ý��� ����
	System_Create(&system);
	// ä�� ����
	system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);
	//����� ä�� ���� Ȯ��
	sound = new Sound*[TOTALSOUNDBUFFER];
	channel = new Channel*[TOTALSOUNDBUFFER];
	memset(sound, 0, sizeof(Sound*)*TOTALSOUNDBUFFER);// sound��( ù��° ����) ���� �ּ� ����(�ι�° ����) �ؼ� ������ ũ��( ����° ����) ��ŭ �ʱ�ȭ ��.
	memset(channel, 0, sizeof(Channel*)*TOTALSOUNDBUFFER);
	return S_OK;
}
void SoundManager::Release()
{
	SAFE_ARR_DELETE(sound);
	SAFE_ARR_DELETE(channel);
	system->close();// �����ϴ� �Լ� 
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
	//system->createSound();//�⺻������ ������ ���� ���� 
	//system->createStream();//���� ũ�Ⱑ ū ���� BGM
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
		system->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &sound[mapSoundDatas.size()]);// �߰��Ǳ� ���� ������( �ε��� ���̶� ����;) 
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