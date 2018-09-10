#pragma once
#include <vector>
#include "../Utilities/utilities.h"
#include "Model2D.h"
#include "Global.h"
using namespace std;

class Entity2D;
struct Bound
{
	Vector2 topleft;
	Vector2 topright;
	Vector2 bottomleft;
	Vector2 bottomright;
	float Width()
	{
		return (topright.x-topleft.x);
	}
	float Height()
	{
		return (topleft.y-bottomleft.y);
	}

	void Draw(float depth)
	{
		GLuint vbo;
		glGenBuffers(1,&vbo);
		Vertex verticesData[6];
		//mNumVertices=6;
		float x=0,y=0,z=0;
		verticesData[0].position=Vector3(topleft.x,topleft.y,depth);
		verticesData[1].position=Vector3(bottomleft.x,bottomleft.y,depth);
		verticesData[2].position= Vector3(bottomright.x,bottomright.y,depth);

		verticesData[3].position = Vector3(topleft.x,topleft.y,depth);
		verticesData[4].position = Vector3(bottomright.x,bottomright.y,depth);
		verticesData[5].position = Vector3(topright.x,topright.y,depth);

		/*float width=Width();
		float height=Height();
		verticesData[0].position.x = 0.0f;  verticesData[0].position.y = height;  verticesData[0].position.z = z;
		verticesData[1].position.x = 0.0f;  verticesData[1].position.y = 0.0f;  verticesData[1].position.z = z;
		verticesData[2].position.x = width;  verticesData[2].position.y = 0.0f;  verticesData[2].position.z = z;

		verticesData[3].position.x = 0.0f;  verticesData[3].position.y = height;  verticesData[3].position.z = z;
		verticesData[4].position.x = width;  verticesData[4].position.y =0.0f;  verticesData[4].position.z = z;
		verticesData[5].position.x = width;  verticesData[5].position.y = height;  verticesData[5].position.z = z;*/

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
		if (Global::BoundShader->a_positon != -1)
		{
			glEnableVertexAttribArray(Global::BoundShader->a_positon);
			glVertexAttribPointer(Global::BoundShader->a_positon, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0);
		}
		glDrawArrays(GL_LINE_LOOP,0,6);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1,&vbo);
	}

};

enum CollisDirection
{
	CollisNone,
	CollisTop,
	CollisLeft,
	CollisBottom,
	CollisRight
};
enum MoveDirect
{
	MoveNone,
	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight
};
class Entity2D
{
protected:
	Vector3 mPosition;
	Vector3 mRotateAngles;
	Vector3 mScaleFactor;
	Shaders* mShader;
	Model2D* mModel;
	Bound mBound;
	int targetMove;
	float mWidth;
	float mHeight;
	bool isActiveInGame;
//Physic
	float velocity;
	float flytime;
	float eslapedtimeFly;
	bool isFlying;
	float y0;
	bool isCollisionable;
//Moving
	float eslapedtimeMove;
	float movingSpeed;
	float movingOffset;
	float movetime;
	bool isMoving;
	bool isMoveLinear;
	bool isMoveUp;
	bool isMoveDown;
	MoveDirect mMoveDirect;
	float x0;
public:
	static float maxDepthOffset;
	Entity2D();
	virtual~Entity2D();
	Vector3 GetPosition();
	Vector3 GetRotateAngles();
	Vector3 GetScaleFactor();
	virtual Bound GetBound();
	int GetTargetMove(){return targetMove;}
	void SetPosition(Vector3);
	void SetRotateAngles(Vector3);
	void SetScaleFactor(Vector3);
	void SetShader(Shaders*);
	void SetIsActiveInGame(bool isActive){isActiveInGame=isActive;}

	void FlipX();
	
	Matrix GetWorldMatrix();

	void GoUp(float v);
	void GoDown(float v);
	void MoveForward(float speed);
	void MoveLinearUp(float offset);
	void MoveLinearDown(float offset);
	void MoveLinearForward(float offset);
	void MoveLinearBackward(float offset);
	void MoveBackward(float speed);

	bool IsPicked(Vector2 pickingPos,BaseCamera*);
	bool IsActiveInGame(){return isActiveInGame;}
	bool IsFlying(){return isFlying;}
	MoveDirect GetMoveDirect(){return mMoveDirect;}
	void SetMoveDirect(MoveDirect move);
	bool IsMoving(){return isMoving;}

	void SetCanCollisionable(bool value){isCollisionable=value;}
	bool IsCollisionable(){return isCollisionable;}
	vector<Entity2D*> entityAround(float nearX,float nearY, vector<Entity2D*> totalEntity);
	virtual CollisDirection CollisWith(Entity2D*);
	Matrix GetMVP();

	
	virtual void update(float);
	virtual void draw()=0;
	void drawBound();

	virtual Entity2D* Create()=0;
	virtual Entity2D* Clone()=0;
};