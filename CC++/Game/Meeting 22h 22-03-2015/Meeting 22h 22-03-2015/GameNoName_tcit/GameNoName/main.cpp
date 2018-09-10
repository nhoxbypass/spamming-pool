/*
Demo game đi cảnh ăn tiền đú đỡn cùng quái vật
Phiên bản: 0.2

by: Nguyễn Trung Thành (abcxyz tcIT) - Đại học Khoa học Tự nhiên TP HCM
Facebook: fb.me/abcxyztcIT
*/

/*

***Về input giá trị trong file map.txt, vui lòng xem các dòng #define trong file GameMap.cpp
_____ chỗ trống (đường đi) là '0'
_____ tường (wall)         là '1'
_____ player               là 'x'
_____ enemy                là 'e'
_____ gold                 là 'g'


***Về hiển thị giá trị ra màn hình, vui lòng xem các dòng #define trong header Game.h
_____ chỗ trống (đường đi) là khoảng trắng
_____ tường (wall)         là kí tự hình vuông đặc biệt
_____ player               là 'x'
_____ enemy                là 'o'
_____ gold                 là kí tự 'A'

*/

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>		// cần dùng cho hàm Sleep
#include "Game.h"
#include "console.h"


// khởi tạo game
void initGame (sPLAYER &player, sArrENEMY &arrEnemy, sGOLD &gold);


int main()
{
	srand(time(NULL));	// khởi tạo bộ sinh số ngẫu nhiên

	// khai báo player
	sPLAYER player;

	// khai báo danh sách quái vật
	sArrENEMY arrEnemy;

	// khai báo gold, ăn gold là thắng
	sGOLD gold;


	initGame (player, arrEnemy, gold); // khởi tạo game


	// biến này dùng để lưu giá trị trả về từ 1 hàm
	int ReturnedCode = 0;


	//--------------- nhập thông tin game từ file map.txt
	sGAMEMAP GameMap;
	ReturnedCode = inputMapData ("map_big2.txt", GameMap, player, arrEnemy, gold);

	if (ReturnedCode == returnedCodeError)
	{
		fprintf (stderr, "Error loading map data \n");
		return 1;
	}
	//-----------------------------------------------------

	displayGame (GameMap, player, arrEnemy, gold); // hiển thị game lần đầu

	int eventCode = 0;	// eventCode = -1 tức là thua, = 1 là thắng

	do
	{
		// xử lý nhập bàn phím để di chuyển player
		controlInputKey (player, GameMap);

		// xử lý các sự kiện như ăn gold, bị quái vật cắn,...
		eventCode = controlEvent (player, arrEnemy, gold);

		EnemyMove (arrEnemy, GameMap.width, GameMap.height); // quái vật di chuyển ngẫu nhiên

		displayGame (GameMap, player, arrEnemy, gold);

		gotoXY (0, 23);	// cuối mỗi nhịp game nên di chuyển con trỏ về 1 tọa độ cố định
		Sleep (150);	// 1 nhịp game có độ dài là 150 mili giây
	}
	while (eventCode == 0);


	if (eventCode == -1)
	{
		gotoXY (40, 15);
		printf ("GAME OVER !!! Press enter to exit \n");
	}
	else if (eventCode == 1)
	{
		gotoXY (40, 15);
		printf ("WIN !!! Press enter to exit \n");
	}

	gotoXY (0, 23);

	while (_getch() != 13);
	
	return 0;
}


//-----------------------------------------------------

void initGame (sPLAYER &player, sArrENEMY &arrEnemy, sGOLD &gold)
{
	player.td.y = 0;
	player.td.x = 0;

	player.HP = 100;
	player.life = 1;

	player.immuneTick = 0;

	arrEnemy.n = 0;
	
	gold.td.y = 1;
	gold.td.x = 1;
}