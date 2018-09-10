// GuessTheFlag.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GuessTheFlag.h"
#include <commctrl.h>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

using namespace std;

#define MAX_LOADSTRING 100
#define MAX_BUFFER_SIZE	255
#define DEFAULT_ANSWER_WIDTH 180
#define DEFAULT_ANSWER_HEIGHT 100
#define NUMBER_OF_FLAG 223
#define LIMIT_TIME	10

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HINSTANCE g_hInstance;
int defaultX = 50, defaultY = 30; //Default coord
HWND hTitle, hClock, hScore, hQuestion, hAnswerA, hAnswerB, hAnswerC, hAnswerD;
HWND g_hWnd; //Main hWnd
vector<wstring> pathList;
vector<wstring> nameList;
WCHAR curPath[255], flagImagePath[255];
int correctAnswerPos;
int totalScore;
int remainingTime;
bool isPlaying = false;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void readPathFromFile(string path); //Read list path from text File
void readNameFromFile(string path);	//Read list name from text File
void loadRandomQuestion();	//Load new question
HBITMAP getImageAt(int position, int type);	//Get image at position
HWND getAnswerWindowAt(int pos);	//Get HWND window at position
void CALLBACK tickTimerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);
WCHAR* convertTimeToCountDown(int remainTime);
void calcScore(int number);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GUESSTHEFLAG, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUESSTHEFLAG));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUESSTHEFLAG));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_BTNFACE+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GUESSTHEFLAG);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowEx(0, szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
	   CW_USEDEFAULT, CW_USEDEFAULT, 510, 680, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
	{
					  
					  readNameFromFile("names.txt");
					  readPathFromFile("path.txt");

					  
					  g_hWnd = hWnd;


					 
					  INITCOMMONCONTROLSEX icc;
					  icc.dwSize = sizeof(icc);
					  icc.dwICC = ICC_WIN95_CLASSES;
					  InitCommonControlsEx(&icc);

					  // Lấy font hệ thống
					  HFONT hFont = CreateFont(60, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Fixedsys");

					  hClock = CreateWindowEx(0, L"STATIC", L"00:00", WS_CHILD | WS_VISIBLE | SS_LEFT, defaultX, defaultY + 40, 200, 60, hWnd, NULL, hInst, NULL);
					  SendMessage(hClock, WM_SETFONT, WPARAM(hFont), TRUE);

					  hFont = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

					  hTitle = CreateWindowEx(0, L"STATIC", L"GUESS THE FLAG", WS_CHILD | WS_VISIBLE | SS_LEFT, defaultX, defaultY, 200, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTitle, WM_SETFONT, WPARAM(hFont), TRUE);

					  hScore = CreateWindowEx(0, L"STATIC", L"0", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER | ES_CENTER, defaultX + 210, defaultY, 170, 100, hWnd, NULL, hInst, NULL);
					  hFont = CreateFont(90, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
					  SendMessage(hScore, WM_SETFONT, WPARAM(hFont), TRUE);


					  hFont = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
					  //Question fragment
					  hQuestion = CreateWindowEx(0, L"BUTTON", L"PRESS TO PLAY!", WS_CHILD | WS_VISIBLE, defaultX, defaultY + 130, DEFAULT_ANSWER_WIDTH + 200, DEFAULT_ANSWER_HEIGHT + 100, hWnd, (HMENU)IDC_QUESTION, hInst, NULL);
					  SendMessage(hQuestion, WM_SETFONT, WPARAM(hFont), TRUE);
					  
					  
					 
					  hAnswerA = CreateWindowEx(0, L"BUTTON", L"PEN", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, defaultX, defaultY + 350, DEFAULT_ANSWER_WIDTH, DEFAULT_ANSWER_HEIGHT, hWnd, (HMENU)IDC_ANSWER_A_BUTTON, hInst, NULL);
					  SendMessage(hAnswerA, WM_SETFONT, WPARAM(hFont), TRUE);

					  hAnswerB = CreateWindowEx(0, L"BUTTON", L"PINEAPPLE", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, defaultX + 200, defaultY + 350, DEFAULT_ANSWER_WIDTH, DEFAULT_ANSWER_HEIGHT, hWnd, (HMENU)IDC_ANSWER_B_BUTTON, hInst, NULL);
					  SendMessage(hAnswerB, WM_SETFONT, WPARAM(hFont), TRUE);


					  hAnswerC = CreateWindowEx(0, L"BUTTON", L"APPLE", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, defaultX, defaultY + 460, DEFAULT_ANSWER_WIDTH, DEFAULT_ANSWER_HEIGHT, hWnd, (HMENU)IDC_ANSWER_C_BUTTON, hInst, NULL);
					  SendMessage(hAnswerC, WM_SETFONT, WPARAM(hFont), TRUE);

					  hAnswerD = CreateWindowEx(0, L"BUTTON", L"PEN", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, defaultX + 200, defaultY + 460, DEFAULT_ANSWER_WIDTH, DEFAULT_ANSWER_HEIGHT, hWnd, (HMENU)IDC_ANSWER_D_BUTTON, hInst, NULL);
					  SendMessage(hAnswerD, WM_SETFONT, WPARAM(hFont), TRUE);
	}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_QUESTION:
			if (isPlaying == false) //Press to play
			{
				isPlaying = true;
				loadRandomQuestion();
				SetTimer(hWnd, IDT_TIMER_SECOND, 1000, (TIMERPROC)tickTimerProc);
				remainingTime = 10;
				totalScore = 0;
			}
			else
			{
				//Playing
				//Do nothing
			}
			break;
		case IDC_ANSWER_A_BUTTON:
			if (isPlaying == true)
			{
				if (correctAnswerPos == 0)
				{
					calcScore(remainingTime);
					//MessageBox(hWnd, L"Đúng", L"Congratulation", MB_OK | MB_ICONINFORMATION);
					loadRandomQuestion();
				}
				else
				{
					//MessageBox(hWnd, L"Sai", L"Congratulation", MB_OK | MB_ICONERROR);
					calcScore(remainingTime - 10);
				}
			}
			else
			{
				//Not playing
			}
			break;
		case IDC_ANSWER_B_BUTTON:
			if (isPlaying == true)
			{
				if (correctAnswerPos == 1)
				{
					calcScore(remainingTime);
					//MessageBox(hWnd, L"Đúng", L"Congratulation", MB_OK | MB_ICONINFORMATION);
					loadRandomQuestion();
				}
				else
				{
					//MessageBox(hWnd, L"Sai", L"Congratulation", MB_OK | MB_ICONERROR);
					calcScore(remainingTime - 10);
				}
			}
			else
			{
				//Not playing
			}
			break;
		case IDC_ANSWER_C_BUTTON:
			if (isPlaying == true)
			{
				if (correctAnswerPos == 2)
				{
					calcScore(remainingTime);
					//MessageBox(hWnd, L"Đúng", L"Congratulation", MB_OK | MB_ICONINFORMATION);
					loadRandomQuestion();
				}
				else
				{
					//MessageBox(hWnd, L"Sai", L"Congratulation", MB_OK | MB_ICONERROR);
					calcScore(remainingTime - 10);
				}
			}
			else
			{
				//Not playing
			}
			break;
		case IDC_ANSWER_D_BUTTON:
			if (isPlaying == true)
			{
				if (correctAnswerPos == 3)
				{
					calcScore(remainingTime);
					//MessageBox(hWnd, L"Đúng", L"Congratulation", MB_OK | MB_ICONINFORMATION);
					loadRandomQuestion();
				}
				else
				{
					//MessageBox(hWnd, L"Sai", L"Congratulation", MB_OK | MB_ICONERROR);
					calcScore(remainingTime - 10);
				}
			}
			else
			{
				//Not playing
			}
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void readPathFromFile(string path)
{
	wfstream inFile;
	wstring tmp;

	inFile.open(path, ios::in);

	if (inFile.is_open())
	{
		while (getline(inFile, tmp))
		{
			pathList.push_back(tmp);
		}
	}

	inFile.close();
}

void readNameFromFile(string path)
{
	wfstream inFile;
	wstring tmp;

	inFile.open(path, ios::in);

	if (inFile.is_open())
	{
		while (getline(inFile, tmp))
		{
			nameList.push_back(tmp);
		}
	}

	inFile.close();
}

void loadRandomQuestion()
{
	//Reset game data
	remainingTime = 10;

	//Get random game type
	srand(time(0));
	int type = rand();
	int answerIndex; //The chosen country index to be answer
	int ans[3]; //3 others countries

	if (type % 2 == 0)
	{
		//Type 0
		//Show flags and guess country name

		//Get the chosen one
		answerIndex = rand() % NUMBER_OF_FLAG;
		
		//Question fragment
		//DestroyWindow(hQuestion);
		//hQuestion = CreateWindowEx(0, L"BUTTON", L"QUESTION", WS_CHILD | WS_VISIBLE | BS_BITMAP, defaultX, defaultY + 130, DEFAULT_ANSWER_WIDTH + 200, DEFAULT_ANSWER_HEIGHT + 100, g_hWnd, (HMENU)IDC_QUESTION, hInst, NULL);
		
		//Clear text and set bitmap
		SetWindowText(hQuestion, L" ");
		SendMessage(hQuestion, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)getImageAt(answerIndex,0));
		
		//Get 3 other countries
		for (int i = 0; i < 3; i++)
		{
			do 
			{
				ans[i] = rand() % NUMBER_OF_FLAG;
			} while (ans[i] == answerIndex);
		}
		
		//Get position of answer
		correctAnswerPos = rand() % 4;
		
		//Set answer
		int j = 0;
		for (int i = 0; i < 4; i++)
		{
			//Clear bitmap
			SendMessage(getAnswerWindowAt(i), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)NULL);

			//Set answer text
			if (correctAnswerPos == i)
			{
				SetWindowText(getAnswerWindowAt(correctAnswerPos), nameList[answerIndex].c_str());
			}
			else
			{
				SetWindowText(getAnswerWindowAt(i), nameList[ans[j]].c_str());
				j++;
			}
		}
	}
	else
	{
		//Type 1
		//Show names and guess flag
		answerIndex = rand() % 223;

		/*
		HFONT hFont = CreateFont(50, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

		//Question fragment
		DestroyWindow(hQuestion);
		hQuestion = CreateWindowEx(0, L"STATIC", L"QUESTION", WS_CHILD | WS_VISIBLE | SS_LEFT | ES_CENTER, defaultX, defaultY + 130, DEFAULT_ANSWER_WIDTH + 200, DEFAULT_ANSWER_HEIGHT + 100, g_hWnd, (HMENU)IDC_QUESTION, hInst, NULL);
		SendMessage(hQuestion, WM_SETFONT, WPARAM(hFont), TRUE);
		SetWindowText(hQuestion, nameList[answerIndex].c_str());
		*/

		//Clear bitmap
		SendMessage(hQuestion, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)NULL);
		
		//Set country name
		SetWindowText(hQuestion, nameList[answerIndex].c_str());

		//Get 3 other countries
		for (int i = 0; i < 3; i++)
		{
			do
			{
				ans[i] = rand() % NUMBER_OF_FLAG;
			} while (ans[i] == answerIndex);
		}

		//0,1,2,3 -> A,B,C,D
		correctAnswerPos = rand() % 4;

	
		//Clear answer text
		SetWindowText(hAnswerA, L" ");
		SetWindowText(hAnswerB, L" ");
		SetWindowText(hAnswerC, L" ");
		SetWindowText(hAnswerD, L" ");

		//Set answer bitmap
		int j = 0;
		for (int i = 0; i < 4; i++)
		{
			if (correctAnswerPos == i)
			{
				SendMessage(getAnswerWindowAt(i), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)getImageAt(answerIndex,1));
			}
			else
			{
				SendMessage(getAnswerWindowAt(i), BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)getImageAt(ans[j],1));
				j++;
			}
		}
	}
}

HBITMAP getImageAt(int position, int type)
{
	//Get current bitmap dir
	GetCurrentDirectory(MAX_BUFFER_SIZE, curPath);
	swprintf(flagImagePath, MAX_BUFFER_SIZE, L"%s\\%s", curPath, pathList[position].c_str());
	HBITMAP hBitmap;
	//Get bitmap
	if (type == 0)
	{
		hBitmap = (HBITMAP)LoadImage(NULL, (LPCWSTR)flagImagePath, IMAGE_BITMAP, DEFAULT_ANSWER_WIDTH + 200, DEFAULT_ANSWER_HEIGHT + 100, LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}
	else
	{
		hBitmap = (HBITMAP)LoadImage(NULL, (LPCWSTR)flagImagePath, IMAGE_BITMAP, DEFAULT_ANSWER_WIDTH, DEFAULT_ANSWER_HEIGHT, LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}
	return hBitmap;
}

HWND getAnswerWindowAt(int pos)
{
	switch (pos)
	{
	case 0:
		return hAnswerA;
		break;
	case 1:
		return hAnswerB;
		break;
	case 2:
		return hAnswerC;
		break;
	case 3:
		return hAnswerD;
		break;
	default:
		break;
	}
}

void CALLBACK tickTimerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	if (remainingTime <= 0)
	{
		KillTimer(hwnd, IDT_TIMER_SECOND);
		MessageBox(g_hWnd, L"Game over!", L"Guess the flag", MB_OK | MB_ICONERROR);
		isPlaying = false;
		//Clear bitmap
		SendMessage(hQuestion, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)NULL);

		//Set country name
		SetWindowText(hQuestion, L"PRESS TO PLAY!");
	}
	else
	{
		remainingTime--;
		SetWindowText(hClock, convertTimeToCountDown(remainingTime));
	}
}

//
WCHAR* convertTimeToCountDown(int remainTime)
{
	WCHAR* result = new WCHAR[6];

	int minutes = remainTime / 60;
	int second = remainTime % 60;
	if (minutes < 10)
	{
		if (second < 10)
		{
			wsprintf(result, L"0%d:0%d", minutes, second);
		}
		else
			wsprintf(result, L"0%d:%d", minutes, second);

	}
	else
	{
		if (second < 10)
		{
			wsprintf(result, L"%d:0%d", minutes, second);
		}
		else
			wsprintf(result, L"%d:%d", minutes, second);
	}


	return result;
}

void calcScore(int number)
{
	totalScore += number;
	WCHAR buff[20];
	wsprintf(buff, L"%d", totalScore);
	SetWindowText(hScore, buff);
}