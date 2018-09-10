#include "Game.h"
#include "Utils.h"

bool KeyState[256];

#pragma region Basic Logic
#define consoleWidth 70
#define consoleHeight 30
float ThoiGianSleep;
float beforeTime;
float afterTime;
char messageString[1000];
#pragma endregion

#pragma region Buffer
Vertex dBuf[500][500];
int currentColor = 15;
int currentKey = ' ';
int currentBack = 0;

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
			dBuf[i][j].Key = 0;
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
	TextColor(15, 0);
	printf(printBuffer);
}
#pragma endregion

#pragma region Car Game
GameScene PreviousScene;
GameScene CurrentScene;
GameScene NextScene;

#pragma region Menu Scene
int iChoose; //ma lenh nguoi dung chon
struct MenuItem{
	int ForeGround;//text color
	int BackGround;//mau nen
	char Content[500];//Noi dung
	Vector2 Position;//Vi tri
	Vector2 Size;//Kich thuoc - X là Width, Y là Height
};

int nItem;
MenuItem *menuItem;

void LoadMenuScene(){
	iChoose = 0;
	nItem = 2;
	menuItem = new MenuItem[nItem];
	//item 0 : Play
	//item 1 : exit
	for (int i = 0; i < nItem; i++){
		menuItem[i].BackGround = 15;
		menuItem[i].ForeGround = 0;

		_itoa(i + 1, menuItem[i].Content, 10);
		strcat(menuItem[i].Content, ". ");

		menuItem[i].Size.X = 15;
		menuItem[i].Size.Y = 5;

		menuItem[i].Position.X = 10;
		menuItem[i].Position.Y = 10 + i * (menuItem[i].Size.Y + 1);
	}

	strcat(menuItem[0].Content, "PLAY");
	strcat(menuItem[1].Content, "EXIT");
}

void UpdateMenuScene(){
	//update keyboard
	if (KeyState[VK_UP] && iChoose > 0)
		iChoose--;
	else if (KeyState[VK_DOWN] && iChoose < nItem - 1)
		iChoose++;

	if (KeyState[VK_RETURN]){
		switch (iChoose)
		{
		case 0:
			NextScene = GameScene::Playing;
			break;
		case 1:
			strcpy(messageString, "Hen gap lai. An enter de thoat");
			RequestExitGame();
			break;
		default:
			break;
		}
	}
}

void DrawMenuScene(){
	for (int i = 0; i < nItem; i++){
		//draw here
		if (iChoose == i){
			//item nay dang duoc chon thi set mau nen la mau vang va mau text la xanh duong
			SetColor(ColorCode_Blue);
			SetBackColor(ColorCode_Yellow);
		}
		else{
			//khong duoc chon thi nen trang, mau den
			SetColor(ColorCode_Back);
			SetBackColor(ColorCode_White);
		}

		int index = 0;
		int len = strlen(menuItem[i].Content);

		int leftAlign = menuItem[i].Size.X / 2 - len / 2;
		int centerAlign = menuItem[i].Size.Y / 2;

		for (int row = 0; row < menuItem[i].Size.Y; row++){
			for (int col = 0; col < menuItem[i].Size.X; col++){
				char dKey = ' ';
				
				//neu khong phai la dong in chu thi in ky tu trang
				//neu la dong in chu thi kiem tra in chu roi in ku tu trang hai ben
				if (row == centerAlign && col >= leftAlign && col < leftAlign + len){
					//ve ky tu cua chuoi
					dKey = menuItem[i].Content[index];
					index++;
				}

				SetVertex(dKey, menuItem[i].Position.Y + row, menuItem[i].Position.X + col);
			}

		}
	}

	SetColor(15);
	SetBackColor(0);

	DrawString(" CCCC     AA     RRRRRR ", 0, 10, 15);
	DrawString("CC      AA  AA   RR   RR", 1, 10, 15);
	DrawString("CC     AAAAAAAA  RRRRRR ", 2, 10, 15);
	DrawString("CC     AA    AA  RR  RR ", 3, 10, 15);
	DrawString(" CCCC  AA    AA  RR   RR", 4, 10, 15);
}

void ReleaseMenuScene(){
	delete[] menuItem;
}
#pragma endregion

#pragma region Playing State
Xe xe;
VatCan vc;
char map[consoleHeight][25];
int ma;
int lanxe = 0;
float sleepTime;
float carPrevTime;
float carNextTime;

void KhoiTao()
{
	xe.diem = 0;
	xe.td.Y = roadHeight - 2;
	xe.td.X = roadWidth / 2;


	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
		xe.hd.data[i][j] = ' ';


	xe.hd.data[0][0] = xe.hd.data[0][2] = xe.hd.data[2][0] = xe.hd.data[2][2] = 'o';	// bánh xe
	xe.hd.data[0][1] = '^'; // đầu xe
	xe.hd.data[1][0] = xe.hd.data[1][2] = '|'; // thân xe
	xe.hd.data[1][1] = '-';


	vc.td.X = 5;
	vc.td.Y = 5;

	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
		vc.hd.data[i][j] = 174;

	sleepTime = 270;
	carPrevTime = 0;
	carNextTime = 0;
}

void LoadPlayingScene(){
	for (int i = 0; i < 25; ++i) {
		for (int j = 0; j < 25; ++j) {
			map[i][j] = ' ';
		}
	}
	KhoiTao();
}

void DieuKhienXe()
{
	if (KeyState['A'] && xe.td.X > 2)
		xe.td.X--;
	else if (KeyState['D'] && xe.td.X < roadWidth - 2)
		xe.td.X++;
}

void CapNhapXe(){
	//nothing
}

void CapNhapVatCan(){
	vc.td.Y++;
	lanxe = (lanxe + 1) % 2;		// làn xe thay đổi liên tục giữa 0 và 1, 1 và 0, 0 và 1....
	if (vc.td.Y >= roadHeight + 1)
	{
		xe.diem++;
		vc.td.X = 2 + rand() % (roadWidth - 4);
		vc.td.Y = -2;

		//Tang toc do xe len
		if (sleepTime > 0)
			sleepTime -= 40;
		if (sleepTime < 0)
			sleepTime = 0;
	}


	// xử lý va chạm
	int KhoangCachX = abs(xe.td.X - vc.td.X);
	int KhoangCachY = abs(xe.td.Y - vc.td.Y);

	if (KhoangCachX < 3 && KhoangCachY < 3)
		ma = -1;
	else
		ma = 0;
}

void UpdatePlayingScene(){
	DieuKhienXe();

	CapNhapXe();

	carNextTime = clock();
	if (carNextTime - carPrevTime >= sleepTime){
		CapNhapVatCan();
		carPrevTime = carNextTime;
	}

	if (ma < 0){
		strcpy(messageString, "Ban thua roi. An enter de quay ve menu...");
		system("cls");
		TextColor(15, 0);
		printf(messageString);
		_getch();
		NextScene = GameScene::Menu;
	}
}

void HienThi() // hiển thị đường đua, hiển thị xe
{
	//clrscr();
	// hiển thị đường đua
	//TextColor(7);
	SetColor(7);
	for (int i = 0; i < roadHeight; i++){
		//printf("%c\n", 179);
		SetVertex(179, i, 0);
	}

	for (int i = 0; i < roadHeight; i++)
	{
		//gotoXY(roadWidth, i);
		//printf("%c", 179);
		SetVertex(179, i, roadWidth);
		if (i % 2 == lanxe)
		{
			//gotoXY(roadWidth / 2, i);
			//printf("|");
			SetVertex('|', i, roadWidth / 2);
		}
	}


	// hiển thị xe
	//TextColor(14); // màu vàng
	SetColor(14);

	for (int i = -1; i <= 1; i++){
		for (int j = -1; j <= 1; j++)
		{
			int x = xe.td.X + j;
			int y = xe.td.Y + i;

			//gotoXY(x, y);
			//printf("%c", xe.hd.data[i + 1][j + 1]);
			SetVertex(xe.hd.data[i + 1][j + 1], y, x);
		}
	}

	//TextColor(11);
	SetColor(11);
	// hiển thị vật cản
	if (vc.td.Y > 0)
	{
		for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			int x = vc.td.X + j;
			int y = vc.td.Y + i;

			if (y < roadHeight)
			{
				//gotoXY(x, y);
				//printf("%c", vc.hd.data[i + 1][j + 1]);
				SetVertex(vc.hd.data[i + 1][j + 1], y, x);
			}
		}
	}
}

void DrawPlayingScene(){
	HienThi();

	// hiển thị tình trạng game
	/*gotoXY(50, 3);
	printf("Diem: %d", xe.diem);*/
	char diem[100];
	sprintf(diem, "Diem: %d", xe.diem);
	DrawString(diem, 3, 50, 15);

}

void ReleasePlayingScene(){

}
#pragma endregion

#pragma endregion

#pragma region Read Config

void ReadMapFromTextFile(char* fileName){

}
#pragma endregion

#pragma region Game Xep hinh
struct Hinh{
	char content[3][3];
	Vector2 toado;
};
Hinh hinh;
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

	beforeTime = 0;
	afterTime = 0;
}

void OnGameLoad(){
	ThoiGianSleep = 1000.0f / 100;
#pragma region Basic Logic
	for (int i = 0; i < consoleHeight; i++){
		for (int j = 0; j < consoleWidth; j++){
			dBuf[i][j].Key = 0;
		}
	}
	ma = 0;

	CurrentScene = GameScene::None;
	NextScene = CurrentScene;
#pragma endregion
}

void InputProcess(){
	for (int i = 0; i < 256; i++){
		KeyState[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

void BeginFPSLitmit(){
	beforeTime = clock();
}

void ReleaseScene(GameScene Scene){
	switch (Scene)
	{
	case GameScene::Menu:
		ReleaseMenuScene();
		break;
	case GameScene::Playing:
		ReleasePlayingScene();
	default:
		break;
	}
}

void OnGameSceneChanging(){
	switch (CurrentScene)
	{
	case GameScene::Menu:
		LoadMenuScene();
		break;
	case GameScene::Playing:
		LoadPlayingScene();
	default:
		break;
	}
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
	if (PreviousScene != CurrentScene){
		ReleaseScene(PreviousScene);
		OnGameSceneChanging();
	}

	PreviousScene = CurrentScene;
	NextScene = CurrentScene;
	
	switch (CurrentScene)
	{
	case GameScene::None:
	case GameScene::Intro:
		NextScene = GameScene::Menu;
	case GameScene::Menu:
		UpdateMenuScene();
		break;
	case GameScene::Playing:
		UpdatePlayingScene();
	default:
		break;
	}

#pragma endregion

}

void Draw(){
	clrscr();
#pragma region Basic Logic
	switch (CurrentScene)
	{
	case GameScene::Menu:
		DrawMenuScene();
		DrawBuffer();
		break;
	case GameScene::Playing:
		DrawPlayingScene();
		//DrawBuffer();
		DrawBufferStream();
	default:
		break;
	}
#pragma endregion
	CurrentScene = NextScene;
}

void ClearBuffer(){

}

void EndFPSLitmit(){
#pragma region Basic Logic
	//Sleep(ThoiGianSleep);
	//Sleep(100);
	afterTime = clock();

	float deltaTime = (afterTime - beforeTime) / 1000;

	if (deltaTime < ThoiGianSleep){
		Sleep(ThoiGianSleep - deltaTime);
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