#ifndef _MAIN
#define _MAIN

#include "Game.h"

//biến cho biết game sẽ kết thúc
bool isGameExit = false;

int main(){
	//mới vô game
	OnCreateGame();
	
	//Game bắt đầu load
	OnGameLoad();

	while (!isGameExit){
		//bắt đầu giới hạn game fps
		BeginFPSLitmit();
		//giả sử có 1 game scene thì int game scene có thể bỏ qua

		//xử lý input như bàn phím, chuột
		InputProcess();

		//update game
		Update();

		//Render game
		Draw();

		//giới hạn tốc độ game
		EndFPSLitmit();
	}

	//game sắp kết thúc
	//yêu cầu giải phóng resource
	OnClosingGame();
	_getch();
	return 0;
}

void RequestExitGame(){
	isGameExit = true;
}

#endif