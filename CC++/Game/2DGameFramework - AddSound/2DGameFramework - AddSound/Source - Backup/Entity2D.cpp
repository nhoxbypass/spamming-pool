#include "Entity2D.h"
#include "Global.h"
#include "DebugDefine.h"
#include "Utils.h"


float Entity2D::maxDepthOffset=1000000;

Entity2D::Entity2D()
{
	mPosition=Vector3();
	mScaleFactor=Vector3(1.0f,1.0f,1.0f);
	mRotateAngles=Vector3();
	isFlying=false;
	isMoving=false;
	//directionFly=1;
	flytime=0.0f;
	velocity=0.0f;
	eslapedtimeFly=0.0f;
	targetMove=1;
	eslapedtimeMove=0.0f;
	mModel=0;
	isCollisionable=false;
	isMoving=false;
	isFlying=false;
	isMoveUp=false;
	isMoveDown=false;
	isMoveLinear=false;
	mMoveDirect=MoveRight;

	isActiveInGame=true;
}

Entity2D::~Entity2D()
{
	if (!mModel)
		return;
	Delete(mModel);
	mShader->UnRefenrence();
	if (mShader->GetReference()<=0)
		Delete(mShader);
}

Bound Entity2D::GetBound()
{
	Bound res;
	float offsetX=mWidth;//*mScaleFactor.x/2.0f;
	float offsetY=mHeight;//*mScaleFactor.y/2.0f;
	res.topleft=Vector2(mPosition.x,mPosition.y+mHeight);
	res.topright=Vector2(mPosition.x+mWidth,mPosition.y+mHeight);
	res.bottomleft=Vector2(mPosition.x,mPosition.y);
	res.bottomright=Vector2(mPosition.x+mWidth,mPosition.y);
	mBound=res;
	return res;
}


void Entity2D::GoUp(float v)
{
	if (isMoveUp)
		return;
	isFlying=true;
	isMoveUp=true;
	isMoveDown=false;
	flytime=v/g;
	
	y0=mPosition.y;
	velocity=v;
	mMoveDirect=MoveUp;
}
void Entity2D::GoDown(float v)
{
	if (isMoveDown)
		return;
	isFlying=true;
	isMoveDown=true;
	isMoveUp=false;
	flytime=v/g;
	
	y0=mPosition.y;
	velocity=-v;
	mMoveDirect=MoveDown;
}
void Entity2D::FlipX()
{
	if (targetMove==1)
	{
		mRotateAngles.y=-PI;
		mMoveDirect=MoveLeft;
	}
	else
	{
		mRotateAngles.y=0;
		mMoveDirect=MoveRight;
	}
	targetMove=-targetMove;
}


bool Entity2D::IsPicked(Vector2 pickingPos,BaseCamera* cam)
{
	Vector3 pos=ConvertCoordinate2D3D(cam,pickingPos);
	Bound b=GetBound();
	if (b.topleft.x<=pos.x && b.topright.x>=pos.x && b.topleft.y>=pos.y && b.bottomleft.y<=pos.y)
		return true;
	return false;
}

Vector3 Entity2D::GetPosition()
{
	Vector3 pos=mPosition;
	pos.z=pos.z/maxDepthOffset;
	return pos;
}

void Entity2D::SetPosition(Vector3 value)
{
	mPosition=value;
}

void Entity2D::SetScaleFactor(Vector3 value)
{
	mScaleFactor=value;
}
void Entity2D::SetShader(Shaders* sha)
{
	mShader=sha;
	sha->Refenrence();
}

Matrix Entity2D::GetWorldMatrix()
{
	Matrix World;
	World.SetIdentity();
	//World.SetScale(10.0f);
	Matrix Scale=Matrix().SetIdentity().SetScale(mScaleFactor);
	Matrix Translate=Translate.SetIdentity();
	Translate.SetTranslation(GetPosition());
	Matrix RotationX,RotationY,RotationZ;
	RotationX.SetIdentity();
	RotationY.SetIdentity();
	RotationZ.SetIdentity();
	RotationX.SetRotationX(mRotateAngles.x);
	RotationY.SetRotationY(mRotateAngles.y);
	RotationZ.SetRotationZ(mRotateAngles.z);
	Matrix Rotation=RotationZ*RotationX*RotationY;
	return Scale*Rotation*Translate;
}

void Entity2D::update(float deltatime)
{
	if (!isActiveInGame)
		return;
	if (isMoveUp)
	{
		eslapedtimeFly+=deltatime*2.0f;
		mPosition.y=-0.5f*g*eslapedtimeFly*eslapedtimeFly + velocity*eslapedtimeFly +y0;
		float v=velocity+g*eslapedtimeFly;
		if (eslapedtimeFly>=flytime)
		{
			//isMoveUp=false;
			//isMoveDown=true;
			//y0=mPosition.y;
			//velocity=velocity;
			//eslapedtimeFly=0.0f;
			mMoveDirect=MoveDown;
		}
		/*else 
			mMoveDirect=MoveUp;*/
		/*if (mPosition.y<=y0)
		{
			isFlying=false;
			eslapedtimeFly=0.0f;
			mPosition.y=y0;
		}		*/
	}
	else if (isMoveDown)
	{
		//eslapedtimeFly+=deltatime;
		//mPosition.y=-0.5f*g*eslapedtimeFly*eslapedtimeFly + velocity*eslapedtimeFly +y0;
	}
	if (isMoving && !isMoveLinear)
	{
		eslapedtimeMove+=deltatime;
		//mPosition.x=targetMove*movingSpeed*eslapedtimeMove +x0;
		mPosition.x= targetMove*movingSpeed*eslapedtimeMove + -targetMove*0.5f*giatoc*eslapedtimeMove*eslapedtimeMove +x0;
		float v=targetMove*movingSpeed+-targetMove*giatoc*eslapedtimeMove;
		if ((v<=0.0f && targetMove==1) || (v>=0.0f && targetMove==-1))
		{
			isMoving=false;
			eslapedtimeMove=0;
		}

		/*if (abs(mPosition.x-x0)>=movingOffset)
		{
			eslapedtimeMove=0.0f;
			isMoving=false;
		}*/
	}
}

void Entity2D::SetMoveDirect(MoveDirect moveDir)
{
	mMoveDirect=moveDir;
	/*if (moveDir==MoveNone)
	{
		isFlying=false;
		isMoveUp=false;
		isMoveDown=false;
		isMoveLinear=false;
		isMoving=false;
		eslapedtimeFly=0.0f;
		eslapedtimeMove=0.0f;
		return;
	}
	
	if (moveDir==MoveLeft)
	{
		MoveBackward(this->movingSpeed);
		return;
	}

	if (moveDir==MoveRight)
	{
		MoveForward(this->movingSpeed);
		return;
	}

	if (moveDir==MoveDown)
	{
		GoDown(velocity);
		return;
	}

	if (moveDir==MoveUp)
	{
		GoUp(velocity);
		return;
	}*/
}

void Entity2D::MoveForward(float speed)
{
	/*if (targetMove==-1)
		FlipX();*/
	//
	movingOffset=2.0f;
	movingSpeed=speed;
	movetime=movingOffset/speed;
	isMoving=true;
	isMoveLinear=false;
	x0=mPosition.x;
	eslapedtimeMove=0;
}

void Entity2D::MoveLinearUp(float offset)
{
	mPosition.y+=offset;
	isMoveLinear=true;
	isMoving=true;
	mMoveDirect=MoveUp;
}

void Entity2D::MoveLinearDown(float offset)
{
	mPosition.y-=offset;
	isMoveLinear=true;
	isMoving=true;
	mMoveDirect=MoveDown;
}

void Entity2D::MoveLinearForward(float offset)
{
	/*if (targetMove==-1)
		FlipX();*/
	mPosition.x+=offset;
	isMoveLinear=true;
	isMoving=true;
	mMoveDirect=MoveRight;
}

void Entity2D::MoveLinearBackward(float offset)
{
	/*if (targetMove==1)
		FlipX();*/
	mPosition.x-=offset;
	isMoveLinear=true;
	isMoving=true;
	mMoveDirect=MoveLeft;
}

void Entity2D::MoveBackward(float speed)
{
	/*if (targetMove==1)
		FlipX();*/
	movingOffset=0.5f;
	movingSpeed=speed;
	movetime=movingOffset/speed;
	isMoving=true;
	isMoveLinear=false;
	x0=mPosition.x;
	eslapedtimeMove=0;
}

vector<Entity2D*> Entity2D::entityAround(float nearX,float nearY,vector<Entity2D*> totalEntity)
{
	float xmin=mPosition.x-nearX;
	float xmax=mPosition.x+nearX;
	float ymin=mPosition.y-nearY;
	float ymax=mPosition.y+nearY;
	Bound mRect=GetBound();
	vector<Entity2D*> res;
	res.clear();
	int n=totalEntity.size();
	if (nearX==0)
	{
		if (mMoveDirect==MoveUp)
		{
			ymin=mPosition.y;
		}
		else if (mMoveDirect==MoveDown)
		{
			ymin=mPosition.y-0.5f;
			ymax=mPosition.y;
		}
		for (int i=0;i<n;i++)
		{
			Vector3 pos=totalEntity[i]->mPosition;
			if (
				totalEntity[i]->mPosition.y>=ymin && totalEntity[i]->mPosition.y<=ymax &&
				totalEntity[i]!=this&&
				totalEntity[i]->IsActiveInGame()&&
				pos.x>=mPosition.x && pos.x<mPosition.x+mWidth)
			{
				res.push_back(totalEntity[i]);
			}
		}
	}
	else if (nearY==0)
	{
		if (mMoveDirect==MoveRight)
		{
			xmin=mPosition.x;
		}
		else if (mMoveDirect==MoveLeft)
		{
			xmin=mPosition.x-0.5f;
			xmax=mPosition.x;
		}
		for (int i=0;i<n;i++)
		{
			Vector3 pos=totalEntity[i]->mPosition;
			if (totalEntity[i]->mPosition.x>=xmin && totalEntity[i]->mPosition.x<=xmax &&
				totalEntity[i]!=this&&
				totalEntity[i]->IsActiveInGame()&&
				pos.y>=mPosition.y && pos.y<mPosition.y+mHeight)
			{
				res.push_back(totalEntity[i]);
			}
		}
	}
	else
	{
		for (int i=0;i<n;i++)
		{
			Vector3 pos=totalEntity[i]->mPosition;
			if (totalEntity[i]->mPosition.x>=xmin && totalEntity[i]->mPosition.x<=xmax &&
				totalEntity[i]->mPosition.y>=ymin && totalEntity[i]->mPosition.y<=ymax &&
				totalEntity[i]!=this&&
				totalEntity[i]->IsActiveInGame())
			{
				res.push_back(totalEntity[i]);
			}
		}
	}
	return res;
}

CollisDirection Entity2D::CollisWith(Entity2D* ent)
{
	if (!this->isCollisionable || !ent->isCollisionable)
		return CollisNone;
	if ( this==ent)
		return CollisNone;
	/*Bound rec1=GetBound();
	Bound rec2=ent->GetBound();
	Bound rec;
	Vector2 topleft;
	Vector2 topright;
	Vector2 bottomleft;
	Vector2 bottomright;
	topleft.x=min(rec1.topleft.x,rec2.topleft.x);
	topleft.y=max(rec1.topleft.y,rec2.topleft.y);
	topright.x=max(rec1.topright.x,rec2.topright.x);
	topright.y=topleft.y;

	bottomleft.x=topleft.x;
	bottomleft.y=min(rec1.bottomleft.y,rec2.bottomleft.y);
	bottomright.x=topright.x;
	bottomright.y=bottomleft.y;

	rec.topleft=topleft;
	rec.topright=topright;
	rec.bottomleft=bottomleft;
	rec.bottomright=bottomright;*/
	Matrix MVP, world;
	MVP.SetIdentity();
	world.SetIdentity();
	world = GetWorldMatrix();
	MVP = world*Global::currentCamera->ViewMatrix() * Global::currentCamera->projection;

	Bound rec1=GetBound();
	Bound rec2=ent->GetBound();
	float xmin=rec2.topleft.x;
	float xmax=rec2.topright.x;
	float ymin=rec2.bottomleft.y;
	float ymax=rec2.topleft.y;

	bool sumWidthCondition=false;
	bool sumHeightCondition=false;

	if (ent->GetPosition().y>mPosition.y)
	{
		sumHeightCondition=(ymax-rec1.bottomleft.y<=rec1.Height()+rec2.Height());
	}
	else
	{
		sumHeightCondition=(rec1.topleft.y-ymin<=rec1.Height()+rec2.Height());
	}

	if (ent->GetPosition().x>mPosition.x)
	{
		sumWidthCondition=(xmax-rec1.topleft.x<=rec1.Width()+rec2.Width());
	}
	else
	{
		sumWidthCondition=(rec1.topright.x-xmin<=rec1.Width()+rec2.Width());
	}


	bool collised= ((rec1.topleft.x<=xmax) && (xmin<=rec1.topright.x)&&
		(rec1.topleft.y>=ymin) && (ymax>=rec1.bottomleft.y)) && sumWidthCondition && sumHeightCondition;

	if (collised)
	{
		//printf("Collision A\n");
		//if (rec1.bottomleft.y<=rec2.topleft.y )
		if (rec1.topleft.y>=rec2.topleft.y && rec1.bottomleft.y<=rec2.topleft.y)
			return CollisBottom;
		if (rec1.topleft.y>=rec2.bottomleft.y && rec1.bottomleft.y<=rec2.bottomleft.y)
 			return CollisTop;
		if (rec1.topright.x>=rec2.topleft.x)
			return CollisRight;
		if (rec1.topleft.x<=rec2.topright.x)
			return CollisLeft;
	}
	
	return CollisNone;
}

void Entity2D::drawBound()
{
	glUseProgram(Global::BoundShader->program);
	Matrix MVP, world;
	MVP.SetIdentity();
	world.SetIdentity();
	//world = GetWorldMatrix();
	MVP = world*Global::currentCamera->ViewMatrix() * Global::currentCamera->projection;
	if (Global::BoundShader->u_MatrixMVP != -1)	// Send MVP
		glUniformMatrix4fv(Global::BoundShader->u_MatrixMVP, 1, GL_FALSE, (float*)&MVP);
	GetBound().Draw();
}


Matrix Entity2D::GetMVP()
{
	Matrix MVP, world;
	MVP.SetIdentity();
	world.SetIdentity();
	world = GetWorldMatrix();
	MVP = world*Global::currentCamera->ViewMatrix() * Global::currentCamera->projection;
	return MVP;
}
