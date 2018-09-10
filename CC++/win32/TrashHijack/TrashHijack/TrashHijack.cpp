// TrashHijack.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TrashHijack.h"
#include <string>
#include <fstream>
#include <vector>
#include <locale>
#include <codecvt>
#include <windows.h>
#include <atlimage.h>
#include <gdiplusimaging.h>

using namespace std;

#define MAX_LOADSTRING 100
#define VK_CHAR_C	0x43

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND g_hWnd;

//
int defaultWidth = 1024, defaultHeight = 720;
bool isInstalled = false;
bool isActivated = false;
string fileName = "log.txt";
string buffer = "";
int deltaTime = 1000;
long long lastTimeStamp = 0;
TCHAR imageFolderName[255];
int numberOfImage = 0;
vector<wstring> textArray;
HHOOK hHook = NULL;
HINSTANCE hinstLib;


//
LRESULT CALLBACK KeyBoardHookProc(int nCode, WPARAM wParam, LPARAM lParam);
void _doInstallHook(HWND hWnd);
void _doRemoveHook(HWND hWnd);
bool isKeyPressed(int a);
void getChar(int vkCode);
void clipboardListener(HWND hWnd);
void WriteToFile(string path, vector<wstring>textarray);


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
	LoadString(hInstance, IDC_TRASHHIJACK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TRASHHIJACK));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRASHHIJACK));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TRASHHIJACK);
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
		g_hWnd = hWnd;
		_doInstallHook(hWnd);
		isInstalled = true;
		break;

	case WM_CLIPBOARDUPDATE:
		clipboardListener(g_hWnd);
		break;
	case WM_KEYDOWN:
		/*
		if (isKeyPressed(VK_LCONTROL) && isKeyPressed(VK_MENU) && isKeyPressed(VK_SHIFT))
		{
			if (!isInstalled)
			{
				_doInstallHook(hWnd);
				isInstalled = true;
			}
			else
			{
				_doRemoveHook(hWnd);

				ofstream outFile;
				outFile.open(fileName);
				outFile << buffer;
				outFile.close();

				isInstalled = false;
			}
		}
		*/
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
			RemoveClipboardFormatListener(hWnd);

			WriteToFile(fileName, textArray);

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


LRESULT CALLBACK KeyBoardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0) // không xử lý message 
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	// xử lý message
	
	switch (wParam)
	{
	/*
	case WM_CREATE:
		AddClipboardFormatListener(g_hWnd);
		break;
	case WM_CLIPBOARDUPDATE:
		clipboardListener(g_hWnd);
		break;
		*/
	case WM_KEYDOWN:
		if (isKeyPressed(VK_CONTROL) && isKeyPressed(VK_MENU) && isKeyPressed(VK_SHIFT) && isKeyPressed(VK_CHAR_C))
		{
			if (!isActivated)
			{
				isActivated = true;
				AddClipboardFormatListener(g_hWnd);
				MessageBox(g_hWnd, L"Hijacking activated!", L"Trash Hijack", MB_OK);
				//ShowWindow(g_hWnd, SW_MINIMIZE);
			}
			else
			{
				isActivated = false;
				//ShowWindow(g_hWnd, SW_SHOW);
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
	
	default:
	{
			   if (GetAsyncKeyState(VK_CAPITAL) < 0 || GetAsyncKeyState(VK_SHIFT) < 0)
			   {
				   buffer += char(vkCode);
			   }
			   else
			   {
				   char c = char(vkCode);
				   buffer += char(tolower(c));
			   }
	}

		break;
	}
}

void clipboardListener(HWND hWnd)
{
	if (OpenClipboard(hWnd))
	{
		if (IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
			LPCWSTR buffer = (LPCWSTR)GlobalLock(hClipboardData);
			textArray.push_back((WCHAR*)(buffer));
			MessageBox(0, (WCHAR*)(buffer), L"Data", 0);
			GlobalUnlock(hClipboardData);
		}
		else if (IsClipboardFormatAvailable(CF_BITMAP))
		{
			numberOfImage++;
			wsprintf(imageFolderName, L"%d.bmp", numberOfImage);
			HBITMAP hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
			//PBITMAPINFO pbi;

			BITMAP bitmap;
			GetObject(hBitmap, sizeof(BITMAP), &bitmap);

			HDC hdc = GetDC(hWnd); // Tạo DC ảo chứa bitmap
			HDC memDC = CreateCompatibleDC(hdc);
			SelectObject(memDC, hBitmap);
			CImage hinh;
			hinh.Attach(hBitmap);
			hinh.Save(imageFolderName, Gdiplus::ImageFormatBMP);

			BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, memDC, 0, 0, SRCCOPY);
			DeleteDC(memDC);
			ReleaseDC(hWnd, hdc);
		}

		CloseClipboard();
	}
}


void WriteToFile(string path, vector<wstring>textarray)
{
	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());
	wofstream f(path, ios::out);
	f.imbue(utf8_locale);

	for (int i = 0; i < textarray.size(); i++){
		f << textarray[i] << endl;
	}
	f.close();
}