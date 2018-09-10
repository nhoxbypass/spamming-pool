#include "EntityFactory.h"
#include "Sprite.h"
#include "Utils.h"


map<string,Entity2D*> EntityFactory::mRegisteredEntityMap=map<string,Entity2D*>();
bool EntityFactory::isInit=false;

void EntityFactory::InitEntity()
{
	if (isInit)
		return;
	RegisterEntity("Sprite",new Sprite());
	isInit=true;
}

void EntityFactory::RegisterEntity(string name,Entity2D* ent)
{
	if (mRegisteredEntityMap.count(name)<1)
		mRegisteredEntityMap[name]=ent;
}

void EntityFactory::RegisterEntity(char* name,Entity2D* ent)
{
	if (mRegisteredEntityMap.count(string(name))<1)
		mRegisteredEntityMap[string(name)]=ent;
}

Entity2D* EntityFactory::CreateAEntity(char *name)
{
	string sName=string(name);
	if (mRegisteredEntityMap.count(sName)<1)
		return 0;
	Entity2D* temp=mRegisteredEntityMap[sName];
	return temp->Create();
}

Entity2D* EntityFactory::CreateAEntity(string name)
{
	if (mRegisteredEntityMap.count(name)<1)
		return 0;
	Entity2D* temp=mRegisteredEntityMap[string(name)];
	return temp->Create();
}

void EntityFactory::Close()
{
	for (auto&x:mRegisteredEntityMap)
	{
		Delete(x.second);
	}
}