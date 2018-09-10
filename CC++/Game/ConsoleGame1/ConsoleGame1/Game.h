#pragma once
#ifndef _GAME
#define _GAME

#include <string>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "console.h"
using namespace std;


#define  maxWidth 80
#define  maxHeight 25
#define  level 2


//global variable
extern int iPoint;
enum Status { UP, DOWN, LEFT, RIGHT, TOPLEFT, TOPRIGHT, BOTLEFT, BOTRIGHT, IDLE };

/*void showOne(int x, int y, string _char, int _color);*/

// struct Vertex
// {
// 	string c;
// 	int color;
// };


/*extern Vertex buffer[maxHeight][maxWidth];*/

struct Coordinates
{
	int x;
	int y;
};


//Function prototype
class MyObject
{
public:
	MyObject()
	{
		this->x = 0;
		this->y = 0;
	}
	string s;
	int x;
	int y;
	Status OldStt;
	Status NewStt;


// 	void fire(MyObject bul)
// 	{
// 		/*MyObject bul;*/
// 		bul.s = "*";
// // 		bul.x = x;
// // 		bul.y = y;
// 		
// 	}
};


class Weapon
{
	int ammor;
};


struct Enemy
{
	string s = "x";
	int x;
	int y;
	bool bKilled = false;
};


class EnemyArmy
{
public:
	Enemy A[level][maxWidth];
	EnemyArmy()
	{
		for (int i = 0; i < level; i++)
		{
			for (int j = 0; j < maxWidth - 1; j++)
			{
				A[i][j].x = j;
				A[i][j].y = i;
			}
		}
	}


	bool isClear()
	{
		for (int i = 0; i < level; i++)
		{
			for (int j = 0; j < maxWidth - 1; j++)
			{
				if (A[i][j].bKilled == false)
				{
					return false;
				}
			}
		}
		return true;
	}


	bool killEnemy(int x, int y)
	{
		if (A[y][x].bKilled == false)
		{

			A[y][x].bKilled = true;
			return true;
		}
		else{
			A[y][x].bKilled = true;
			return false;
		}
	}


	void Army()
	{
		for (int i = 0; i < level; i++)
		{
			for (int j = 0; j < maxWidth - 1; j++)
			{
				if (A[i][j].bKilled == false)
				{
					/*showOne(j, i, A[i][j].s,7);*/
					gotoXY(j, i);				
					cout << A[i][j].s;
				}
			}
		}
	}

};



bool isImpact(MyObject a, MyObject b);
void onCreateGame(MyObject &a, MyObject &b, EnemyArmy &A);
void control(MyObject &a);
void collisionsHandle(MyObject &a);
void collisionsHandle(MyObject &a, MyObject&b, EnemyArmy &A);
void move(MyObject &a);
bool isEndGame(MyObject b, EnemyArmy A);
void show(MyObject a);
void onEndGame();
/*Coordinates nextStep(MyObject a, MyObject b, EnemyArmy A);*/
void gotoDes(MyObject &a, MyObject b);

#endif