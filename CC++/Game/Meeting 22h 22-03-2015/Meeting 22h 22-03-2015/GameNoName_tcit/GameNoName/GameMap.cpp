#include <stdio.h>
#include "Game.h"


// những kí tự được sử dụng trong việc đọc file input bản đồ
#define mInputData_blank		'0'
#define mInputData_wall			'1'
#define mInputData_player		'x'
#define mInputData_enemy		'e'
#define mInputData_gold			'g'


int inputMapData (char FN[], sGAMEMAP &GameMap, sPLAYER &player, sArrENEMY &arrEnemy, sGOLD &gold)
{
	FILE *f = fopen (FN, "rt");

	if (!f)
	{
		return returnedCodeError;
	}

	fscanf (f, "%d %d\n", &GameMap.width, &GameMap.height);

	for (int i = 0; i < GameMap.height; i++)
	{
		for (int j = 0; j < GameMap.width; j++)
		{
			int cell = 0;
			fscanf (f, "%c ", &cell);

			GameMap.data[i][j] = mInputData_blank;

			if (cell == mInputData_player)
			{
				player.td.y = i;
				player.td.x = j;
			}
			else if (cell == mInputData_enemy)
			{
				int nE = arrEnemy.n;
				arrEnemy.data[nE].td.y = i;
				arrEnemy.data[nE].td.x = j;

				arrEnemy.n++;
			}
			else if (cell == mInputData_gold)
			{
				gold.td.y = i;
				gold.td.x = j;
			}
			else
			{
				GameMap.data[i][j] = cell;
			}
		}
	}

	fclose (f);

	
	// chuyển những kí tự input thành kí tự hiển thị trên màn hình
	for (int i = 0; i < GameMap.height; i++)
		for (int j = 0; j < GameMap.width; j++)
		{
			switch (GameMap.data[i][j])
			{
			case mInputData_blank:
				GameMap.data[i][j] = mData_blank;
				break;

			case mInputData_wall:
				GameMap.data[i][j] = mData_wall;
				break;
			}
		}


	return returnedCodeOK;
}