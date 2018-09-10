#ifndef _GAME
#define _GAME

#include "console.h"
#include "Car.h"
#include "MathEx.h"
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
void ReleaseScene(GameScene);
void OnGameSceneChanging();
void UpdateKeyBoard();
void Update();
void Draw();
void DrawBuffer();
void DrawBufferStream();
void RequestExitGame();
void EndFPSLitmit();
void OnClosingGame();
#endif