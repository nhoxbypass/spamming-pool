#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "Game.h"
#include "console.h"


// CONTROL ----------------------------------------------------------------

// hàm này dùng để nhận phím từ người chơi và di chuyển player
// các phím mũi tên di chuyển (lên, xuống, trái, phải)...
void controlInputKey (sPLAYER &player, const sGAMEMAP &GameMap)
{
	int key = inputKey();

	int y = player.td.y;
	int x = player.td.x;

	int mWidth = GameMap.width;
	int mHeight = GameMap.height;

	switch (key)
	{
	case key_Up:
		{
			if (y > 0  &&  GameMap.data[y-1][x] == mData_blank)
				player.td.y--;

			break;
		}

	case key_Down:
		{
			if (player.td.y < mHeight-1  &&  GameMap.data[y+1][x] == mData_blank)
				player.td.y++;

			break;
		}

	case key_Left:
		{
			if (player.td.x > 0  &&  GameMap.data[y][x-1] == mData_blank)
				player.td.x--;

			break;
		}

	case key_Right:
		{
			if (player.td.x < mWidth-1  &&  GameMap.data[y][x+1] == mData_blank)
				player.td.x++;

			break;
		}
	}
}


// hàm này dùng để di chuyển ngẫu nhiên những con quái vật
void EnemyMove (sArrENEMY &arrEnemy, int MapWidth, int MapHeight)
{
	static int tick = 0;
	tick = (tick + 1) % 2;

	//if (tick == 0)
	//	return;

	// cứ 2 nhịp game thì quái vật mới di chuyển 1 lần

	for (int i = 0; i < arrEnemy.n; i++)
	{
		int moveDirection = rand() % 5;
		// moveDirection = 0 tức là không di chuyển

		switch (moveDirection)
		{
		case 1: // move left
			if (arrEnemy.data[i].td.x > 0)
				arrEnemy.data[i].td.x--;

			break;

		case 2: // move right
			if (arrEnemy.data[i].td.x < MapWidth-1)
				arrEnemy.data[i].td.x++;

			break;

		case 3: // move up
			if (arrEnemy.data[i].td.y > 0)
				arrEnemy.data[i].td.y--;

			break;

		case 4: // move down
			if (arrEnemy.data[i].td.y < MapHeight-1)
				arrEnemy.data[i].td.y++;

			break;
		}
	}
}


// hàm này để xử lý các tình huống như quái vật chạm vào player, game over, ăn vàng chiến thắng....
// trả về 0 nếu nếu game bình thường
// trả về 1 nếu chiến thắng
// trả về -1 nếu thua
int controlEvent (sPLAYER &player, const sArrENEMY &arrEnemy, const sGOLD &gold)
{
	int y = player.td.y;
	int x = player.td.x;
	
	int ey = 0, ex = 0;	// tọa độ quái vật


	if (player.immuneTick < 1) // nếu như tình trạng miễn dịch của player không còn thì mới xem xét va chạm với quái vật
	{
		for (int i = 0; i < arrEnemy.n; i++)
		{
			ey = arrEnemy.data[i].td.y;
			ex = arrEnemy.data[i].td.x;

			if (y == ey && x == ex)		// va chạm với quái vật, bị quái vật hấp diêm
			{
				player.immuneTick = 10;	// miễn dịch 10 nhịp game

				player.HP = player.HP - 25;

				if (player.HP < 1)
				{
					player.life--;
					player.HP = 100;
				}

				break;
			}
		}
	}
	else
	{
		player.immuneTick--;
	}


	// thua game
	if (player.life < 1)
	{
		player.HP = 0;
		return -1;
	}


	if (y == gold.td.y && x == gold.td.x)	// ăn vàng, win
		return 1;

	return 0;
}