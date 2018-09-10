#include "Game.h"
#include "Utils.h"

bool KeyState[256];

#pragma region Maps
struct Vertex{
	int Color;
	char Key;  //texture - hinh
};

Vertex dBuf[500][500];
int currentColor = 15;
int currentKey = ' ';

void AddVertex(int color, int key, int dong, int cot){
	dBuf[dong][cot].Color = color;
	dBuf[dong][cot].Key = key;
}

void AddVertex(int key, int dong, int cot){
	dBuf[dong][cot].Color = currentColor;
	dBuf[dong][cot].Key = key;
}

void AddVertex(int dong, int cot){
	dBuf[dong][cot].Color = currentColor;
	dBuf[dong][cot].Key = currentKey;
}

void SetColor(int color){
	currentColor = color;
}

struct Map{
	//vat can
	int wall[100][100];
	//so cot
	int col;
	//so dong
	int row;
};
Map maps;
#pragma endregion

#pragma region Basic Logic
#define consoleWidth 25
#define consoleHeight 25

enum TrangThai { UP, DOWN, LEFT, RIGHT };

struct ToaDo
{
	int y, x;
};


struct Snake
{
	ToaDo dot[30];	// dot[0] là đầu con rắn
	int n;
	TrangThai tt;
};


struct HoaQua
{
	ToaDo a;
};

Snake snake;
HoaQua hoaqua;
int ThoiGianSleep;

int GameOver(Snake snake)
{
	if (maps.wall[snake.dot[0].y][snake.dot[0].x])
		return 1;

	for (int i = 1; i < snake.n; i++)
	if (snake.dot[0].x == snake.dot[i].x &&
		snake.dot[0].y == snake.dot[i].y)
		return 1;

	// riêng vụ rắn tự cắn mình thì các bạn tự làm, rất là dễ
	return 0;
}

// trả về 1 nếu có ăn, trả về 0 nếu không ăn
int RanAn_HoaQua(Snake snake, HoaQua hoaqua)
{
	if (snake.dot[0].x == hoaqua.a.x &&
		snake.dot[0].y == hoaqua.a.y)

		return 1;

	return 0;
}

// nếu con rắn ăn thì mới gọi hàm này
void TaoHoaQua(HoaQua &hoaqua)
{
	do{
		hoaqua.a.y = rand() % maps.row;
		hoaqua.a.x = rand() % maps.col;
	} while (maps.wall[hoaqua.a.y][hoaqua.a.x]);
}

void TangDoDai(Snake &snake)
{
	for (int i = snake.n; i > 0; i--)
		snake.dot[i] = snake.dot[i - 1];

	snake.n++;

	if (snake.tt == UP)
		snake.dot[0].y--;
	else if (snake.tt == DOWN)
		snake.dot[0].y++;
	else if (snake.tt == LEFT)
		snake.dot[0].x--;
	else if (snake.tt == RIGHT)
		snake.dot[0].x++;
}
#pragma endregion

#pragma region Read Config
char messageString[1000];

void ReadMapFromTextFile(char* fileName){
	//doc file config
	FILE* file = fopen(fileName, "rt");

	//neu khong ton tai file thi bao loi va thoat ra
	if (!file){
		strcpy(messageString, "Error: Cannot open Config file!!");
		RequestExitGame();
		return;
	}

	char buffer[512];
	//doc so dong, so cot
	//so dong
	fgets(buffer, 512, file);
	ScanNumberInt32(buffer, &maps.row, 0);
	//so cot
	fgets(buffer, 512, file);
	ScanNumberInt32(buffer, &maps.col, 0);
	//doc col dong, moi dong luu thanh row so
	for (int i = 0; i < maps.row; i++){
		//doc tung dong
		fgets(buffer, 512, file);
		int iPos = 0;
		for (int j = 0; j < maps.col; j++){
			iPos = ScanNumberInt32(buffer, &maps.wall[i][j], iPos);
		}
	}

	//doc vi tri xuat phat cua con ran
	//so dong
	fgets(buffer, 512, file);
	ScanNumberInt32(buffer, &snake.dot[0].y, 0);
	//so cot
	fgets(buffer, 512, file);
	ScanNumberInt32(buffer, &snake.dot[0].x, 0);

	fclose(file);
}
#pragma endregion

#pragma region Game Xep hinh
struct Hinh{
	char hinh[3][3];
	ToaDo toado;
};
Hinh hinh;
#pragma endregion

void OnCreateGame(){
	for (int i = 0; i < 256; i++){
		KeyState[i] = false; // key up
	}
	srand(time(NULL));
}

void OnGameLoad(){
#pragma region Basic Logic
	hinh.hinh[0][0] = '*';
	hinh.hinh[1][0] = '*';
	hinh.hinh[2][0] = '*';
	hinh.hinh[2][1] = '*';
	hinh.toado.x = hinh.toado.y = 0;
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 40; j++){
			dBuf[i][j].Key = 0;
		}
	}

	ThoiGianSleep = 100;
#pragma endregion
}

void InputProcess(){
	for (int i = 0; i < 256; i++){
		KeyState[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

void BeginFPSLitmit(){

}

void UpdateKeyBoard(){
	if (KeyState[VK_ESCAPE]){
		//nếu nhấn phím escapse thì thoát
		RequestExitGame();
	}

#pragma region Basic Logic
	
#pragma endregion
}

void Update(){
	//Update keyboard
	UpdateKeyBoard();
#pragma region Basic Logic
	if (KeyState['S'] == true || KeyState['s'] == true){
		
	}
	else if (KeyState['A'] == true || KeyState['a'] == true){
		hinh.toado.x--;
	}
	else if (KeyState['D'] == true || KeyState['d'] == true){
		hinh.toado.x++;
	}
	else if (KeyState['W'] == true || KeyState['w'] == true){
		
	}
	
	hinh.toado.y++;
#pragma endregion

}

void Draw(){
	clrscr();
#pragma region Basic Logic
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j ++){
			AddVertex(12, hinh.hinh[i][j], j + hinh.toado.x, i + hinh.toado.y);
		}
	}
#pragma endregion

	DrawBuffer();
}

void DrawBuffer(){
	//ve dBuf ra
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 40; j++){
			//gotoXY(j, i);
			TextColor(dBuf[j][i].Color);
			printf("%c", dBuf[j][i].Key);
			dBuf[j][i].Key = 0;
		}
		printf("\n");
	}
}

void ClearBuffer(){

}

void EndFPSLitmit(){
#pragma region Basic Logic
	Sleep(ThoiGianSleep);
#pragma endregion
}

void OnClosingGame(){
#pragma region Basic Logic
	//clrscr();
	gotoXY(0, 0);
	printf(messageString);
	printf("\n");
	printf("Release Resources... \nGame Exiting...\n");
#pragma endregion
}