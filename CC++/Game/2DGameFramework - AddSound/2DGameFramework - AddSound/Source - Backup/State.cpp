#include "State.h"
#include "Utils.h"
#include "DebugDefine.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Global.h"

State::State()
{
	mListEntity.clear();
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
