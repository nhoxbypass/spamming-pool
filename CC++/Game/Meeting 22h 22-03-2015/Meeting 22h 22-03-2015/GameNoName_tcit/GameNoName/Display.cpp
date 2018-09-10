#include <stdio.h>
#include "Game.h"
#include "console.h"

// DISPLAY ---------------------------------------------------------------


// hiển thị bản đồ
void displayMap (const sGAMEMAP &GameMap)
{
	for (int i = 0; i < GameMap.height; i++)
	{
		for (int j = 0; j < GameMap.width; j++)
			putc(GameMap.data[i][j], stdout);

		putc ('\n', stdout);
	}
}


// hiển thị bản đồ, player, quái vật, tình trạng game
void displayGame (const sGAMEMAP &GameMap, const sPLAYER &player, const sArrENEMY &arrEnemy, const sGOLD &gold)
{
	clrscr();	// xóa màn hình

	// hiển thị bản đồ
	TextColor (default_ColorCode);
	gotoXY (0, 0);
	displayMap (GameMap);


	// hiển thị gold
	TextColor (ColorCode_Yellow);		// đổi sang màu vàng
	gotoXY (gold.td.x, gold.td.y);
	putc (mData_gold, stdout);


	// hiển thị vị trí player
	TextColor (ColorCode_Cyan);			// đổi sang màu xanh nước biển
	gotoXY (player.td.x, player.td.y);
	putc (mData_player, stdout);


	// hiển thị vị trí các con quái vật
	TextColor (ColorCode_Red);			// đổi sang màu đỏ
	for (int i = 0; i < arrEnemy.n; i++)
	{
		gotoXY (arrEnemy.data[i].td.x, arrEnemy.data[i].td.y);
		putc (mData_enemy, stdout);
	}


	TextColor (default_ColorCode);

	// in ra cái khung bao bọc bản đồ cho đẹp
	for (int i = 0; i < GameMap.height; i++)
	{
		gotoXY (GameMap.width, i);
		printf ("%c", 179);
	}

	for (int i = 0; i < GameMap.width; i++)
	{
		gotoXY (i, GameMap.height);
		printf ("%c", 196);
	}

	gotoXY (GameMap.width, GameMap.height);
	printf ("%c", 217);
	//-------------------------------


	// hiển thị tình trạng game
	gotoXY (50, 1);
	printf ("HP  : %d", player.HP);
	gotoXY (50, 2);
	printf ("Life: %d", player.life);
}
