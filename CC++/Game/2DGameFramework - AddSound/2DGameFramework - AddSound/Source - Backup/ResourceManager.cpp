#include <algorithm>
#include "ResourceManager.h"
#include "Utils.h"
#include "DebugDefine.h"
using namespace std;


ResourceManager* ResourceManager::instance=0;

ResourceManager::ResourceManager()
{
	mListTexture.empty();
	mListMesh2D.empty();
}

ResourceManager::~ResourceManager()
{
}


ResourceManager* ResourceManager::GetInstance()
{
	if (instance==0)
		instance=new ResourceManager();
	return instance;
}



int ResourceManager::Load(string path2Resource)
{
	FILE* fi;
	fi=fopen(path2Resource.c_str(),"r");
	if (fi==NULL)
		return -1;
	char buffer[MAX_LEN];

	//Pass line //Texture
	ReadLine(fi, buffer);
	while (strstr(buffer,"Mesh")==0)
	{
		ReadLine(fi, buffer);
		if (strstr(buffer,"Mesh")!=0)
			break;
		char path[MAX_LEN];
		memset(path,0,MAX_LEN);
		int iPos=0;
		iPos=ScanPath(buffer,path,iPos);
		int referenceCount=0;
		iPos=ScanNumberInt32(buffer,&referenceCount,iPos);
		if (path!=0)
		{
			Texture* texture=new Texture();
			texture->Init(path,referenceCount);
			mListTexture.push_back(texture);
		}
	}
	//Pass line //Shader
	ReadLine(fi,buffer);
	while (strstr(buffer,"End")==0)
	{
		ReadLine(fi,buffer);
		if (strstr(buffer,"End")!=0)
			break;
		Shaders* shader=new Shaders();
		char pathVertexShader[MAX_LEN];
		char pathFragmentShader[MAX_LEN];
		memset(pathVertexShader,0,MAX_LEN);
		memset(pathFragmentShader,0,MAX_LEN);
		int iPos=0;
		iPos=ScanPath(buffer,pathVertexShader,iPos);
		ReadLine(fi,buffer);
		iPos=0;
		iPos=ScanPath(buffer,pathFragmentShader,iPos);
		ReadLine(fi,buffer);
		int referenceCount=0;
		iPos=ScanNumberInt32(buffer,&referenceCount,0);
		shader->Init(pathVertexShader,pathFragmentShader,referenceCount);
		mListShader.push_back(shader);
	}
	return 0;
}

bool IsExistPath(char *path1,char *path2)
{
	return path1==path2;
}

Texture* ResourceManager::GetTexture(char* path)
{
	Texture* res=NULL;
	int n=mListTexture.size();
	if (n==0)
		return res;
	vector<Texture*>::iterator tex=find_if(mListTexture.begin(),mListTexture.end(),MatchStringTexture(string(path)));
	if (tex!=mListTexture.end())
	{
		auto index = distance(mListTexture.begin(), tex);
		return mListTexture.at(index);
	}
	return res;
}

Shaders* ResourceManager::GetShader(char* path)
{
	int n=mListTexture.size();
	if (n==0)
		return 0;
	vector<Shaders*>::iterator tex=find_if(mListShader.begin(),mListShader.end(),MatchStringShader(string(path)));
	if (tex!=mListShader.end())
	{
		auto index = distance(mListShader.begin(), tex);
		return mListShader.at(index);
	}
	return 0;
}