#include "stdafx.h"
#include "Game.h"

int iPoint = 0;
/*Vertex buffer[maxHeight][maxWidth];*/

// void showOne(int x, int y, string _char, int _color)
// {
// 	buffer[y][x].color = _color;
// 	buffer[y][x].c = _char;
// }


bool isImpact(MyObject a, MyObject b)
{
	if (((b.y == a.y - 1) || (b.y == a.y + 1)) && ((b.x >= a.x) && (b.x <= a.x + a.s.length())))
	{
		return true;
	}
	else
		return false;
}

void onCreateGame(MyObject &a, MyObject &b, EnemyArmy &A)
{
	//Setup for new ball
	b.s = "O";
	b.y = 5;
	b.x = (maxWidth - b.s.length()) / 2;
	b.NewStt = BOTRIGHT;


	//Setup the tank
	a.s = "TTTTTTTTTT";
	a.x = (maxWidth - a.s.length()) / 2;
	a.y = maxHeight - 3;
	a.NewStt = RIGHT;
	system("COLOR 79");
}

void control(MyObject &a)
{
	if (_kbhit())
	{
		char key = _getch();
		if ((key == 'a') || (key == 'A'))
		{
			a.NewStt = LEFT;
		}
		if ((key == 'd') || (key == 'D'))
		{
			a.NewStt = RIGHT;
		}
		// 			if ((key == 'w') || (key == 'W'))
		// 			{
		// 				a.NewStt = UP;
		// 			}
		// 			if ((key == 's') || (key == 'S'))
		// 			{
		// 				a.NewStt = DOWN;
		// 			}




		
	}
}

void collisionsHandle(MyObject &a)
{
	if (a.y >= maxHeight - 2)
	{
		a.NewStt = UP;
	}
	else if (a.y <= 0)
	{
		a.NewStt = DOWN;
	}
	else if (a.x <= 0)
	{
		a.NewStt = RIGHT;
	}
	else if (a.x == maxWidth - 1 - a.s.length())
	{
		a.NewStt = LEFT;
	}



}


//something changed
void collisionsHandle(MyObject &a, MyObject&b, EnemyArmy &A)
{
	if (isImpact(a, b) == true)
	{
		if (b.OldStt == BOTLEFT){
			b.NewStt = TOPLEFT;
		}
		else
			b.NewStt = TOPRIGHT;


	}
	else if (b.y <= 0)
	{
		if (b.OldStt == TOPRIGHT){
			b.NewStt = BOTRIGHT;
		}
		else
		{
			b.NewStt = BOTLEFT;
		}
		
	}
	else if (b.x <= 0)
	{
		if (b.OldStt == TOPLEFT){
			b.NewStt = TOPRIGHT;
		}
		else
		{
			b.NewStt = BOTRIGHT;
			
		}
			
	}
	else if (b.x == maxWidth - 1 - b.s.length())
	{
		if (b.OldStt == BOTRIGHT){
			b.NewStt = BOTLEFT;
			
		}
		else
			b.NewStt = TOPLEFT;
	}
	else if (b.y <= level - 1){
		if (A.killEnemy(b.x, b.y) == true) //kill 
		{
			if (b.OldStt == TOPRIGHT){
				b.NewStt = BOTRIGHT;
			}
			else
			{
				b.NewStt = BOTLEFT;
			}
			iPoint++;
		}
		else
			return;
	}
	b.OldStt = b.NewStt;

}

void move(MyObject &a)
{
	if (a.NewStt == UP)
	{
		a.y--;
	}
	else if (a.NewStt == DOWN)
	{
		a.y++;
	}
	else if (a.NewStt == RIGHT)
	{
		a.x++;
	}
	else if (a.NewStt == LEFT)
	{
		a.x--;
	}
	else if (a.NewStt == TOPLEFT)
	{
		a.x--;
		a.y--;
	}
	else if (a.NewStt == TOPRIGHT)
	{
		a.x++;
		a.y--;
	}
	else if (a.NewStt == BOTLEFT)
	{
		a.x--;
		a.y++;
	}
	else if (a.NewStt == BOTRIGHT)
	{
		a.x++;
		a.y++;
	}
}

bool isEndGame(MyObject b, EnemyArmy A)
{
	if ((b.y >= maxHeight - 2) || (A.isClear() == true))
	{
		return true;
	}
	else
		return false;
}

void show(MyObject a)
{
	gotoXY(a.x, a.y);
	cout << a.s << endl;
// 	for (int i = a.x; i < a.x + a.s.length(); i++)
// 	{
// 		showOne(a.x, a.y, a.s, 7);
// 	}
}

void onEndGame()
{
	gotoXY((maxWidth - 15) / 2, maxHeight / 2);
	system("COLOR 7C");
	cout << "Ban da thua !!!" << endl;
	gotoXY((maxWidth - 15) / 2, maxHeight / 2 + 2);
	cout << "High score: " << iPoint << endl;
	gotoXY((maxWidth - 15) / 2, maxHeight / 2 + 4);
	// 	cout << "Nhap O de choi lai, X de thoat game " << endl;
	// 	char rkey = _getch();
	// 	if ((rkey == 'O') || (rkey == 'o'))
	// 	{
	// 		goto rstgame;
	// 	}
}


// Coordinates nextStep(MyObject a, MyObject b, EnemyArmy A)
// {
// 	MyObject tmpBall, tmpTank;
// 	EnemyArmy tmpArmy = A;
// 	tmpBall = b;
// 	tmpTank = a;
// 
// 
// 	collisionsHandle(tmpTank, tmpBall, tmpArmy);
// 	move(tmpBall);
// 	if (tmpBall.y >= maxHeight - 3)
// 	{
// 		Coordinates xytmp;
// 		xytmp.x = b.x;
// 		xytmp.y = b.y;
// 		return xytmp;
// 	}
// 	else
// 	{
// 		return nextStep(tmpTank, tmpBall,tmpArmy);
// 	}
// }


void gotoDes(MyObject &a, MyObject b)
{
	if (b.x <= a.x  + 1)
	{
		a.NewStt = LEFT;
	}
	else if (b.x >= a.x + a.s.length() - 1)
	{
		a.NewStt = RIGHT;
	}
}