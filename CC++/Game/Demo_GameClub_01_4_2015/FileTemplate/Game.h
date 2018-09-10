#ifndef _GAME
#define _GAME

#include "console.h"
#include <time.h>

// hàm xử lý
void OnCreateGame();
void OnGameLoad();
void OnInitScene();
void InputProcess();
void OnKeyPress(char key);
//void OnMouseDown();
//void OnMouseUp();
void BeginFPSLitmit();
void UpdateKeyBoard();
void Update();
void Draw();
void DrawBuffer();
void RequestExitGame();
void EndFPSLitmit();
void OnClosingGame();
#endif