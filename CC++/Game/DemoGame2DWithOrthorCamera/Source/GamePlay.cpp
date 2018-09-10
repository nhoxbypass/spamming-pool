#include "GamePlay.h"
#include "2DGameFramework\Utils.h"
#include "2DGameFramework\Sprite.h"
#include "2DGameFramework\ResourceManager.h"
#include "2DGameFramework\EntityFactory.h"
#include "2DGameFramework\InputHandler.h"
#include <string>

GamePlayState::GamePlayState()
{
	mName="GamePlay";
	path2Config=Global::gameResourceDir+string("Resources/GamePlay.txt");
	spawnTime = 0;
	zombies = vector<Zombie*>();
	heroes = vector<Hero*>();
}
GamePlayState::~GamePlayState()
{
	zombies.clear();
	heroes.clear();
}
void GamePlayState::Init()
{
	const char* path2Config=this->path2Config.c_str();
	FILE* pFile=fopen(path2Config,"r");
	if (pFile==NULL)
		return;
	char buffer[MAX_LEN];
	strcpy(loadName, "Nothing");
	//Pass Num of Entity
	ReadLine(pFile,buffer);
	int numEntity;
	int iPos=ScanNumberInt32(buffer,&numEntity,0);
	int iCount=0;
	//Pass Texure
	ReadLine(pFile,buffer);
	while(iCount<numEntity)
	{
		Sprite* sprite=0;

		ReadLine(pFile,buffer);
		char path[MAX_LEN];
		int t=ScanPath(buffer,path,0);
		Texture* texture=ResourceManager::GetInstance()->GetTexture(path);

		if (texture)
		{
			if (!texture->IsLoaded())
				texture->Load(Texture2D);

			//texture->Refenrence();

			//Entity Type, tự định nghĩa
			ReadLine(pFile,buffer);
#ifdef Win32
			sprite=(Sprite*)EntityFactory::CreateAEntity(buffer);
#endif
#ifdef Android
			int len=strlen(buffer);
			char*name1=new char[len];
			memcpy(name1,buffer,len);
			name1[len-1]='\0';
			string t1=string(name1);
			sprite=(Sprite*)EntityFactory::CreateAEntity(t1);
			delete[] name1;
#endif
			if (strstr(path,"sogoku")!=0)
			{
				strcpy(loadName, "sogoku");
			}
			else if (strstr(path,"zombie")!=0)
			{
				strcpy(loadName, "zombie");
			}
			else if (strstr(path,"background")!=0)
			{
				strcpy(loadName, "background");
			}
			//Frame Sprite
			ReadLine(pFile,buffer);
			int iPos=0;
			float duration=0.0f,width=0.0f,height=0.0f;
			int numSpriteX=0,numSpriteY=0,numSprite=0;
			iPos=ScanNumberFloat32(buffer,&duration,iPos);
			iPos=ScanNumberFloat32(buffer,&width,iPos);
			iPos=ScanNumberFloat32(buffer,&height,iPos);
			iPos=ScanNumberInt32(buffer,&numSpriteX,iPos);
			iPos=ScanNumberInt32(buffer,&numSpriteY,iPos);
			iPos=ScanNumberInt32(buffer,&numSprite,iPos);

			//Shader
			ReadLine(pFile,buffer);
			iPos=ScanPath(buffer,path,0);
			Shaders* shader=0;
			shader=ResourceManager::GetInstance()->GetShader(path);
			if (shader!=0)
			{
				if (shader->IsLoaded()==false)
				{
					shader->Load();
				}

				sprite->SetShader(shader);
				sprite->Init(texture,duration,width,height,numSpriteX,numSpriteY,numSprite);

				//Read number clone of sprite
				ReadLine(pFile,buffer);
				int numClone;
				ScanNumberInt32(buffer,&numClone,0);
				Sprite* prevSprite;
				for (int i=0;i<numClone;i++)
				{
					ReadLine(pFile,buffer);
					float x,y,z,flip;
					iPos=ScanNumberFloat32(buffer,&x,0);
					iPos=ScanNumberFloat32(buffer,&y,iPos);
					iPos=ScanNumberFloat32(buffer,&z,iPos);
					iPos=ScanNumberFloat32(buffer,&flip,iPos);
					Vector3 pos(x,y,z);
					if (sprite==0)
					{
						sprite=(Sprite*)prevSprite->Clone();
					}
					sprite->SetPosition(pos);	
					if (flip==1)
						sprite->FlipX();
					sprite->Play();
					mListEntity.push_back(sprite);
					if (strstr(loadName,"sogoku")!=0)
					{
						heroes.push_back((Hero*)sprite);
					}
					if (strstr(loadName,"zombie")!=0)
					{
						zombies.push_back((Zombie*)sprite);
					}
					if (strstr(loadName,"background")!=0)
					{
						/*sprite->SetPosition(ConvertCoordinate2D3D(Global::currentCamera,Vector2(0,Global::ScreenHeight)));
						float aspect=(float)(Global::ScreenHeight)/(float)(Global::ScreenWidth);
						sprite->SetScaleFactor(Vector3(3.5,2,0));*/
					}
					prevSprite=sprite;
					sprite=0;
				}
			}
		}
		//ReadLine(pFile,buffer);
		iCount++;
	}
	for (int i=0;i< zombies.size();i++){
		zombies[i]->SetUpFrame(0,0,3);
		Vector3 pos = zombies[i]->GetPosition();
		float deltaX = GetARandomNumber() % 50 * 0.13;
		zombies[i]->SetPosition(Vector3(pos.x + deltaX, pos.y, pos.z));
	}
	for (int i=0;i< heroes.size();i++){
		heroes[i]->SetUpFrame(0,0,0);
	}
}

void GamePlayState::Mouse(MouseData mouse, bool bIsDown)
{
	if (mouse.isDown)
	{
		Hero* ad=heroes[0];
		
		if (ad->IsPicked(mouse.position,Global::currentCamera))
			ad->SetShowBoundEnable(true);
		else
			ad->SetShowBoundEnable(false);
		
	}
	if (mouse.type==MouseType::Right && mouse.isDown)
	{
		Hero* ad=heroes[0];
		if (ad->IsPicked(mouse.position,Global::currentCamera))
			ad->SetIsActiveInGame(!ad->IsActiveInGame());
	}
}
void GamePlayState::Key(unsigned char key, bool bIsPressed)
{
	Vector3 pos;
	switch(key)
	{ 
	case 'K':
		Global::currentCamera->MoveForward(0.1f);
		break;
	case 'M':
		Global::currentCamera->MoveBackward(0.1f);
		break;
	case 'A':
		Global::currentCamera->MoveLeft(0.1f);
		break;
	case 'D':
		Global::currentCamera->MoveRight(0.1f);
	break;
	case 'U':
		pos=Global::currentCamera->GetPosition();
		Global::currentCamera->SetPosition(Vector3(pos.x,pos.y+0.1f,pos.z));
		break;
	case 'V':
		 pos=Global::currentCamera->GetPosition();
		Global::currentCamera->SetPosition(Vector3(pos.x,pos.y-0.1f,pos.z));
		break;
	}
}

void GamePlayState::onTouch(int id,float x,float y)
{
	if (id==Action::DOWN)
	{
			Hero* ad=heroes[0];
			if (ad->IsPicked(Vector2(x,y),Global::currentCamera))
				ad->SetShowBoundEnable(true);
			else
				ad->SetShowBoundEnable(false);
	}
}

int t=0;
float ftime;
void GamePlayState::Update(float deltatime)
{
	State::Update(deltatime);

	for (int j=0;j< heroes.size();j++){
		heroes[j]->Fight(false);
	}
	for (int i=0;i< zombies.size();i++){
		if (!zombies[i]->IsActiveInGame()){continue;}
		for (int j=0;j< heroes.size();j++){
			if (CheckCollision(heroes[j]->GetBound(), zombies[i]->GetBound())){
				heroes[j]->Fight(true);
				zombies[i]->Hurt(heroes[j]->getStrenght());
				break;
			}
		}
		
		zombies[i]->MoveLinearBackward(0.04f);
	}
	for (int j=0;j< heroes.size();j++){
		heroes[j]->UpdateFighting(deltatime);
	}
}

void GamePlayState::Draw()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);
	State::Draw();
}

bool GamePlayState::CheckCollision(Bound b1, Bound b2){
	if ((b1.topright.x >= b2.topleft.x) && (b1.topright.y == b2.topleft.y))
	{
		return true;
	}
	return false;
}