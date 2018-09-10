// ConsoleGame1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "console.h"
#include "Game.h"
using namespace std;







int _tmain(int argc, _TCHAR* argv[])
{
	rstgame:


	//Declare variables
	MyObject a, b;
	EnemyArmy A;
	int speed = 200;
	Coordinates tmp;
	int isPCPlay = 0;
	


	onCreateGame(a, b, A);
	cout << "Che do choi: " << endl << " 1. PC play." << endl << " 2. Tu choi." << endl;
	cin >> isPCPlay;
	


	while (isEndGame(b,A) == false)
	{
		//Show
		system("cls");
		A.Army();
		show(a);
		show(b);


		//print buffer
// 		for (int i = 0; i < maxHeight - 1; i++)
// 		{
// 			for (int j = 0; j < maxWidth; j++)
// 			{
// 				TextColor(buffer[i][j].color);
// 				cout << buffer[i][j].c;
// 				buffer[i][j].c = ' ';
// 			}
// 		}
/*		show(bul);*/
		gotoXY(maxWidth - 15, maxHeight-5);
		cout << "Diem: " << iPoint << endl;


		//Control game
		control(a);

// 		if (_kbhit())
// 		{
// 			char key = _getch();
// 			if ((key == 'k') || (key == 'K'))
// 			{
// 				MyObject* bul = new MyObject;
// 				bul->x = a.x;
// 				bul->y = a.y;
// 				bul->s = "*";
// 				bul->NewStt = UP;
// 				
// 
// 			}
// 		}
		

		//Collisions Handle
		collisionsHandle(a);
		collisionsHandle(a, b, A);
// 		if (bul->y <= level - 1){
// 			if (A.killEnemy(bul.x, bul.y) == true) //kill 
// 			{
// 				bul.s = "";
// 				iPoint++;
// 			}
// 		}
		

		//PC play
		if (isPCPlay == 1)
		{
			gotoDes(a, b);
		}
			
		
		
		//Move
		move(a);
		move(b);
		
		/*move(bul);*/


		//Set speed
		Sleep(speed);
		if (speed >= 10)
		{
			speed -= 1;
		}
	}

	
	onEndGame();
	
	system("pause");
	return 0;
}




