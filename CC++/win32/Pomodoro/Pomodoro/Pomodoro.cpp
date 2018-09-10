// Pomodoro.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Pomodoro.h"
#include <string>
#include <commctrl.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

using namespace std;

#define MAX_LOADSTRING 100

//
#define POMODORO_TIME 30 //Thoi gian, co the thay doi 1 lan va dung cho ca chuong trinh (tinh bang giay)
#define SHORT_BREAK 5
#define LONG_BREAK 10

#define DEFAULT_CONFIG_PATH L"D:\\config.ini"
#define DEFAULT_FRAGMENT_HEIGHT	320
#define DEFAULT_FRAGMENT_WIDTH	290

#define COORD_FIRSTLINE_X	50
#define COORD_FIRSTLINE_Y	50

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title pomodoroTimerProc text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void CALLBACK tickTimerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);
void CALLBACK pomodoroTimerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);
void CALLBACK shortBreakTimerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);
void CALLBACK longBreakTimerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);
WCHAR* convertTimeToCountDown(int remainTime);
void killAllTimer(HWND hWnd);
WCHAR* getStatusString();
void saveApplicationSettings(HWND hWnd);
void getApplicationSettings();
void getConfigPath();

//Declare variables
HWND setGoalInputField, setJobNameInputField, clockText, pomodoro, statusBar;
HWND hStartButton, hStopButton;
HWND hGoalStatic, hJobNameStatic;
int numberOfGoal;
int currPomodoro;
int remainTime;
WCHAR* strJobName;
wstring configPath;
int defaultWidth = 400, defaultHeight = 500;
int defaultX, defaultY;

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
	LoadString(hInstance, IDC_POMODORO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_POMODORO));
	

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POMODORO));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_POMODORO);
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

   getApplicationSettings();

   hWnd = CreateWindowEx(0, szWindowClass, szTitle,
	   WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, CW_USEDEFAULT, defaultWidth, defaultHeight, NULL, NULL, hInstance, NULL);

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

					  INITCOMMONCONTROLSEX icc;
					  icc.dwSize = sizeof(icc);
					  icc.dwICC = ICC_WIN95_CLASSES;
					  InitCommonControlsEx(&icc);

					  // Lấy font hệ thống
					  HFONT hFont = CreateFont(60, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Fixedsys");

					  RECT rect;
					  if (GetWindowRect(hWnd, &rect))
					  {
						  defaultWidth = rect.right - rect.left;
						  defaultHeight = rect.bottom - rect.top;
					  }
					  else
					  {
						  defaultWidth = 400;
						  defaultHeight = 500;
					  }

					  defaultX = (defaultWidth - DEFAULT_FRAGMENT_WIDTH) / 2 - 15;
					  defaultY = (defaultHeight - DEFAULT_FRAGMENT_HEIGHT) / 2 - 30;

					  clockText = CreateWindowEx(0, L"STATIC", L"00:00", WS_CHILD | WS_VISIBLE | SS_LEFT, defaultX + 60, defaultY + 50, 200, 60, hWnd, NULL, hInst, NULL);
					  SendMessage(clockText, WM_SETFONT, WPARAM(hFont), TRUE);


					  pomodoro = CreateWindowEx(0, L"STATIC", L"POMODORO TIME", WS_CHILD | WS_VISIBLE | SS_LEFT, defaultX + 50, defaultY, 400, 40, hWnd, NULL, hInst, NULL);
					  hFont = CreateFont(30, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
					  SendMessage(pomodoro, WM_SETFONT, WPARAM(hFont), TRUE);


					  hGoalStatic = CreateWindowEx(0, L"STATIC", L"Goal", WS_CHILD | WS_VISIBLE | SS_LEFT, defaultX, defaultY + 155, 100, 40, hWnd, NULL, hInst, NULL);
					  hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
					  SendMessage(hGoalStatic, WM_SETFONT, WPARAM(hFont), TRUE);

					  hJobNameStatic = CreateWindowEx(0, L"STATIC", L"Job", WS_CHILD | WS_VISIBLE | SS_LEFT, defaultX, defaultY + 205, 100, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hJobNameStatic, WM_SETFONT, WPARAM(hFont), TRUE);

					  setGoalInputField = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, defaultX + 70, defaultY + 150, 220, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(setGoalInputField, WM_SETFONT, WPARAM(hFont), TRUE);

					  setJobNameInputField = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, defaultX + 70, defaultY + 200, 220, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(setJobNameInputField, WM_SETFONT, WPARAM(hFont), TRUE);
					 

					  hStartButton = CreateWindowEx(0, L"BUTTON", L"START", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, defaultX, defaultY + 280, 130, 40, hWnd, (HMENU)IDC_START_BUTTON, hInst, NULL);
					  SendMessage(hStartButton, WM_SETFONT, WPARAM(hFont), TRUE);

					  hStopButton = CreateWindowEx(0, L"BUTTON", L"STOP", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, defaultX + 170, defaultY + 280, 130, 40, hWnd, (HMENU)IDC_STOP_BUTTON, hInst, NULL);
					  SendMessage(hStopButton, WM_SETFONT, WPARAM(hFont), TRUE);

					  //Status pomodoroTimerProc
					  statusBar = CreateWindowEx(0,
						  STATUSCLASSNAME,
						  L"0/0 Pomodoro",
						  WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 
						  0,defaultHeight,
						  500,20, 
						  hWnd, (HMENU)IDC_STATUSBAR,
						  hInst, NULL);
					  SendMessage(statusBar, WM_SETFONT, WPARAM(hFont), TRUE);



	}
	case WM_COMMAND:
	{
					   wmId = LOWORD(wParam);
					   wmEvent = HIWORD(wParam);

					   //
					   int setGoalLen, setJobNameLen;
					   WCHAR* buff1 = NULL;
					  


					   // Parse the menu selections:
					   switch (wmId)
					   {
					   case IDC_START_BUTTON:
						   setGoalLen = GetWindowTextLength(setGoalInputField);
						   setJobNameLen = GetWindowTextLength(setJobNameInputField);

						   buff1 = new WCHAR[setGoalLen + 1];
						   strJobName = new WCHAR[setJobNameLen + 1];

						   if (setJobNameLen <= 0 || setGoalLen <= 0)
						   {
							   MessageBox(hWnd, L"Job name or number of goal must not be empty!", L"Invalid input", MB_OK | MB_ICONERROR);
							   break;
						   }

						   GetWindowText(setGoalInputField, buff1, setGoalLen + 1);
						   GetWindowText(setJobNameInputField, strJobName, setJobNameLen + 1);

						   numberOfGoal = _wtoi(buff1);

						   if (numberOfGoal <= 0)
						   {
							   MessageBox(hWnd, L"Number of goal must greater than zero!", L"Invalid goal", MB_OK | MB_ICONWARNING);
							   break;
						   }

						   SetWindowText(pomodoro, strJobName);
						   SetWindowText(statusBar, getStatusString());

						   currPomodoro = 0;
						   remainTime = POMODORO_TIME;
						   SetTimer(hWnd, IDT_TIMER_SECOND, 1000, (TIMERPROC)tickTimerProc);
						   SetTimer(hWnd, IDT_TIMER_PODOMORO, POMODORO_TIME * 1000, (TIMERPROC)pomodoroTimerProc);

						   break;

					   case IDC_STOP_BUTTON:
						   killAllTimer(hWnd);
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
	}
		break;
	case WM_SIZE:
		RECT rect;
		if (GetWindowRect(hWnd, &rect))
		{
			defaultWidth = rect.right - rect.left;
			defaultHeight = rect.bottom - rect.top;
			
			defaultX = (defaultWidth - DEFAULT_FRAGMENT_WIDTH) / 2  - 15;
			defaultY = (defaultHeight - DEFAULT_FRAGMENT_HEIGHT) / 2 - 30;

			MoveWindow(statusBar, 0, defaultHeight, defaultWidth, 20, FALSE);
			MoveWindow(clockText, defaultX + 60, defaultY + 50, 200, 60, FALSE);
			MoveWindow(setGoalInputField, defaultX + 70, defaultY + 150, 220, 40, FALSE);
			MoveWindow(setJobNameInputField, defaultX + 70, defaultY + 200, 220, 40, FALSE);
			MoveWindow(pomodoro, defaultX + 50, defaultY, 400, 40, FALSE);

			MoveWindow(hStartButton, defaultX, defaultY + 280, 130, 40, FALSE);
			MoveWindow(hStopButton, defaultX + 170, defaultY + 280, 130, 40, FALSE);

			MoveWindow(hGoalStatic, defaultX, defaultY + 155, 100, 40, FALSE);
			MoveWindow(hJobNameStatic, defaultX, defaultY + 205, 100, 40, FALSE);
		}
		
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		killAllTimer(hWnd);
		saveApplicationSettings(hWnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void CALLBACK tickTimerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	remainTime--;
	
	SetWindowText(clockText, convertTimeToCountDown(remainTime));
}

void CALLBACK pomodoroTimerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	currPomodoro++;
	remainTime = 0;

	if (currPomodoro >= numberOfGoal)
	{
		killAllTimer(hwnd);
		SetWindowText(statusBar, getStatusString());
		SetWindowText(clockText, L"00:00");
		MessageBox(hwnd, L"You've reached your goal", L"Congratulations", MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		SetWindowText(statusBar, getStatusString());
		SetWindowText(clockText, L"00:00");

		if (currPomodoro % 4 == 0)
		{
			KillTimer(hwnd, IDT_TIMER_SECOND);
			KillTimer(hwnd, IDT_TIMER_PODOMORO);
			MessageBox(hwnd, L"You've done a pomodoro, take a long break!", L"Pomodoro", MB_OK | MB_ICONINFORMATION);
			SetTimer(hwnd, IDT_TIMER_LONGBREAK, LONG_BREAK * 1000, (TIMERPROC)longBreakTimerProc);
		}
		else
		{
			KillTimer(hwnd, IDT_TIMER_SECOND);
			KillTimer(hwnd, IDT_TIMER_PODOMORO);
			MessageBox(hwnd, L"Finish a pomodoro, let's break for 5 minutes", L"Pomodoro", MB_OK | MB_ICONINFORMATION);
			SetTimer(hwnd, IDT_TIMER_SHORTBREAK, SHORT_BREAK * 1000, (TIMERPROC)shortBreakTimerProc);
		}
	}
	
}

void CALLBACK shortBreakTimerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	KillTimer(hwnd, IDT_TIMER_SHORTBREAK);
	MessageBox(hwnd, L"Get back to work :D", L"Pomodoro", MB_OK | MB_ICONINFORMATION);

	remainTime = POMODORO_TIME;
	SetTimer(hwnd, IDT_TIMER_SECOND, 1000, (TIMERPROC)tickTimerProc);
	SetTimer(hwnd, IDT_TIMER_PODOMORO, POMODORO_TIME * 1000, (TIMERPROC)pomodoroTimerProc);
}

void CALLBACK longBreakTimerProc(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	KillTimer(hwnd, IDT_TIMER_LONGBREAK);
	MessageBox(hwnd, L"Back to work and Get shit done!", L"Pomodoro", MB_OK | MB_ICONINFORMATION);
	
	remainTime = POMODORO_TIME;
	SetTimer(hwnd, IDT_TIMER_SECOND, 1000, (TIMERPROC)tickTimerProc);
	SetTimer(hwnd, IDT_TIMER_PODOMORO, POMODORO_TIME * 1000, (TIMERPROC)pomodoroTimerProc);
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

	/*
	if (second < 10)
	{
		result[3] = '0';
		result[4] = second + '0';
	}
	else
	{
		result[3] = second / 10 + '0';
		result[4] = second % 10 + '0';
	}
		

	if (minutes < 10)
	{
		result[0] = '0';
		result[1] = minutes + '0';
	}
	else
	{
		result[0] = minutes / 10 + '0';
		result[1] = minutes % 10 + '0';
	}

	result[5] = '\0';
	return result;
	*/
}

void killAllTimer(HWND hWnd)
{
	KillTimer(hWnd, IDT_TIMER_LONGBREAK);
	KillTimer(hWnd, IDT_TIMER_SHORTBREAK);
	KillTimer(hWnd, IDT_TIMER_PODOMORO);
	KillTimer(hWnd, IDT_TIMER_SECOND);
}

WCHAR* getStatusString()
{
	WCHAR* res = new WCHAR[50];

	wsprintf(res, L"%d/%d Pomodoro", currPomodoro, numberOfGoal);

	return res;
	
	/*
	int tmp = numberOfGoal;
	int i = 2;

	res[0] = currPomodoro + '0';
	res[1] = '/';

	while (tmp != 0)
	{
		res[i] = tmp % 10 + '0';
		tmp /= 10;
		i++;
	}

	res[i++] = ' ';
	res[i++] = 'P';
	res[i++] = 'o';
	res[i++] = 'm';
	res[i++] = 'o';
	res[i++] = 'd';
	res[i++] = 'o';
	res[i++] = 'r';
	res[i++] = 'o';
	res[i] = '\0';

	return res;
	*/
}

void saveApplicationSettings(HWND hWnd)
{
	
	getConfigPath();
	RECT rect;
	if (GetWindowRect(hWnd, &rect))
	{
		defaultWidth = rect.right - rect.left;
		defaultHeight = rect.bottom - rect.top;
		WCHAR buff[50];
		wsprintf(buff, L"%d", defaultWidth);
		int i = WritePrivateProfileString(L"size", L"width", buff, configPath.c_str());
		wsprintf(buff, L"%d", defaultHeight);
		i = WritePrivateProfileString(L"size", L"height", buff, configPath.c_str());
	}
}

void getApplicationSettings()
{
	WCHAR buffer[255];
	getConfigPath();

	GetPrivateProfileString(L"size", L"width", L"400", buffer, 255, configPath.c_str());
	defaultWidth = _wtoi(buffer);

	GetPrivateProfileString(L"size", L"height", L"500", buffer, 255, configPath.c_str());
	defaultHeight = _wtoi(buffer);
}

void getConfigPath()
{
	WCHAR currDirPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currDirPath);
	wstring tmp(currDirPath);
	tmp += wstring(L"\\config.ini");
	configPath = tmp;
}