#include "Game.h"
#include "Utils.h"

bool KeyState[256];

#pragma region Basic Logic
#define consoleWidth 70
#define consoleHeight 30
char messageString[1000];
float TimeToSleep; //FPS mình cần litmit
long TimeBefore;
long TimeAfter;

#pragma endregion

#pragma region Buffer
Vertex dBuf[500][500];
int currentColor = 15;
int currentKey = ' ';
int currentBack = 0;

void KhoiTaoBuffer(){
	for (int i = 0; i < consoleHeight; i++){
		for (int j = 0; j< consoleWidth; j++){
			dBuf[i][j].Key = ' ';
		}
	}

	SetColor(15); //mau chu la mau trang
	SetBackColor(0);//mau nen la mau den
	SetKey(' '); //ky tu mac dinh space
}

//nhung ham xu ly
void SetVertex(int color, int key, int dong, int cot){
	if (dong > consoleHeight - 1 || cot > consoleWidth - 1){
		return;
	}

	dBuf[dong][cot].Color = color;
	dBuf[dong][cot].Key = key;
	dBuf[dong][cot].BackColor = currentBack;
	if (dBuf[dong][cot].BackColor < 16){
		dBuf[dong][cot].BackColor = dBuf[dong][cot].BackColor << 4;
	}
}

void SetVertex(int key, int dong, int cot){
	SetVertex(currentColor, key, dong, cot);
}

void SetVertex(int dong, int cot){
	SetVertex(currentColor, currentKey, dong, cot);
}

void SetBackColor(int backColor){
	currentBack = backColor;
}

void SetColor(int color){
	currentColor = color;
}

void SetKey(char key){
	currentKey = key;
}

void DrawString(const char* str, int dong, int cot, int color){
	int lenght = strlen(str);

	for (int i = 0; i < lenght; i++){
		char drawKey = str[i];
		if (drawKey == '\n')
			drawKey = ' ';
		SetVertex(color, drawKey, dong, cot + i);
	}
}

//has color but slow
void DrawBuffer(){
	//ve dBuf ra
	for (int i = 0; i < consoleHeight; i++){
		for (int j = 0; j < consoleWidth; j++){
			//gotoXY(j, i);
			TextColor(dBuf[i][j].Color, dBuf[i][j].BackColor);
			printf("%c", dBuf[i][j].Key);
			dBuf[i][j].Key = 0; //reset buffer

			/*
			Ở hàm này -> Vẽ từng vertex
			*/
		}
		printf("\n");
	}
}

//it should have no color, beco no shader
void DrawBufferStream(){
	//ve dBuf ra
	char printBuffer[5000];
	int index = 0;
	for (int i = 0; i < consoleHeight; i++){
		for (int j = 0; j < consoleWidth; j++){
			printBuffer[index] = dBuf[i][j].Key;
			if (printBuffer[index] == 0)
				printBuffer[index] = ' ';
			index++;
			dBuf[i][j].Key = 0;
		}
		//printf("\n");
		printBuffer[index] = '\n';
		index++;
	}

	printBuffer[index] = 0;
	TextColor(14, 0);
	printf(printBuffer);
}

void HuyBuffer(){

}
#pragma endregion

#pragma region Demo Game
struct Hinh{
	char data[3][3];
	Vector2 toado;
};

Hinh hinh;
long TimeLitmit;
long ElapsedTime;
long BeginTime;

void KhoiTaoHinh(){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			hinh.data[i][j] = '*';
		}
	}
	hinh.toado.X = hinh.toado.Y = 0;

	/*
	* 0 0
	* 0 0
	* * 0
	*/

	hinh.data[0][0] = '*';
	hinh.data[1][0] = '*';
	hinh.data[2][0] = '*';
	hinh.data[2][1] = '*';
}

void UpdateHinh(){
	hinh.toado.Y++;
}

void HuyHinh(){

}
#pragma endregion

#pragma region Game Flow
void OnCreateGame(){
	for (int i = 0; i < 256; i++){
		KeyState[i] = false; // key up
	}
	srand(time(NULL));

	//set up window
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, consoleWidth * 50, consoleHeight * 20, TRUE); // 800 width, 100 height

	TimeToSleep = 1000.0f / 60; // 1/ 60 giây đó các bạn
	TimeBefore = 0;
	TimeAfter = 0;
}

void OnGameLoad(){
#pragma region Basic Logic
	//set up a new buffer with character 0
	KhoiTaoHinh();

	TimeLitmit = 500;
	ElapsedTime = 0;
	BeginTime = 0;

	KhoiTaoBuffer();
#pragma endregion
}

void InputProcess(){
	for (int i = 0; i < 256; i++){
		KeyState[i] = GetAsyncKeyState(i) & 0x8000;
		//neu keyState true: phim dang down
		//nguoc lai phim dang up
	}
}

void BeginFPSLitmit(){
	TimeBefore = clock();//lay thoi gian he thong
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
	int timeNow = clock();
	ElapsedTime += timeNow - BeginTime;
	BeginTime = timeNow;

	if (ElapsedTime >= TimeLitmit){
		UpdateHinh();
		ElapsedTime = 0;
	}

	if (KeyState['A']){
		hinh.toado.X--;
	}
	else if (KeyState['D']){
		hinh.toado.X++;
	}

	if (hinh.toado.Y > consoleHeight){
		strcpy(messageString, "Ok, da xong demo game theo kien truc!!!");
		RequestExitGame();
	}
#pragma endregion

}

void Draw(){
	clrscr();
#pragma region Basic Logic
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			SetVertex(i + 1, hinh.data[i][j], i + hinh.toado.Y, j + hinh.toado.X);
			//gotoXY(j + hinh.toado.X, i + hinh.toado.Y);
			//putc(hinh.data[i][j], stdout);
		}
		//putc('\n',stdout);
	}
	//DrawBuffer();
	DrawBufferStream();
#pragma endregion
}

void ClearBuffer(){

}

void EndFPSLitmit(){
#pragma region Basic Logic
	TimeAfter = clock(); //tinh theo ms
	float deltaTime = (TimeAfter - TimeBefore) / 1000;

	if (deltaTime < TimeToSleep){
		Sleep(TimeToSleep - deltaTime);
	}
#pragma endregion
}

void OnClosingGame(){
#pragma region Basic Logic
	system("cls");
	TextColor(15, 0);
	printf(messageString);
	printf("\n");
	printf("Release Resources... \nGame Exiting...\n");
#pragma endregion
}

#pragma endregion