#include "State.h"
#include "Utils.h"
#include "DebugDefine.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Global.h"
#include "SoundManager.h"

State::State()
{
	mListEntity.clear();
	mListSoundName.clear();
	mName="";
	isRelease=false;
	isInit=false;
}

State::~State()
{
	int n=mListEntity.size();
	for (int i=0;i<n;++i)
	{
		Delete(mListEntity[i]);
	}
	mListEntity.clear();
}


void State::Update(float deltatime)
{
	int n=mListEntity.size();
	mListEntityInView.clear();
	for (int i=0;i<n;i++)
	{
		mListEntity[i]->update(deltatime);
		//printf("Finish update entity %d \n",i);
		if (IsInCameraView(mListEntity[i]))
		{
			mListEntityInView.push_back(mListEntity[i]);
		}
	}
}

void State::Draw()
{
	
	int n=mListEntityInView.size();
	for (int i=0;i<n;i++)
	{
		mListEntityInView[i]->draw();
	}
	/*int n=mListEntity.size();
	for (int i=0;i<n;i++)
	{
		mListEntity[i]->draw();
	}*/
}

void State::LoadSound()
{
	const char* path2Sound=this->path2SoundList.c_str();
	FILE* pFile=fopen(path2Sound,"r");
	if (pFile==0)
		return;
	char buffer[MAX_LEN];
	SoundManager* sound=SoundManager::getInstance();
	if (!sound)
		return;
	while(strstr(buffer,"End")==0)
	{
		ReadLine(pFile,buffer);
		if (strstr(buffer,"//End")!=0)
			return;
		char path[MAX_LEN];
		int t=ScanPath(buffer,path,0);
		char soundPath[MAX_LEN];
		strcpy(soundPath,Global::gameResourceDir.c_str());
		strcat(soundPath,path);
		if (strstr(soundPath,"wav"))
		{
			sound->LoadWAV(soundPath);
		}
		else if (strstr(soundPath,"ogg"))
		{
			sound->LoadOGG(soundPath);
		}
		mListSoundName.push_back(string(soundPath));
	}
}

void State::PauseAllSound()
{
	int n=mListSoundName.size();
	SoundManager*sound=SoundManager::getInstance();
	for (int i=0;i<n;i++)
		sound->Pause(mListSoundName[i]);
}

