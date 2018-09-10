// Week1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1412477_Week1.h"
#include <commctrl.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
bool isNumber(WCHAR* c, int n);
float calcMoney(long long money, float rate, int month);

HWND txtAmountOfMoney, txtInterestRate, txtResult;

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
	LoadString(hInstance, IDC_MY1412477_WEEK1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1412477_WEEK1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MY1412477_WEEK1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MY1412477_WEEK1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 500, NULL, NULL, hInstance, NULL);

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
					  LOGFONT lf;
					  GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
					  HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
						  lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
						  lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
						  lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
						  lf.lfPitchAndFamily, lf.lfFaceName);

					  HWND hTemp;

					  hTemp = CreateWindowEx(0, L"BUTTON", L"CALCULATE", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 350, 500, 40, hWnd, (HMENU)IDC_CALC_BUTTON, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);

					  hTemp = CreateWindowEx(0, L"STATIC", L"Amount of Money", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 50, 100, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);

					  hTemp = CreateWindowEx(0, L"STATIC", L"Interest rate", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 150, 100, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);

					  txtAmountOfMoney = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 50, 150, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(txtAmountOfMoney, WM_SETFONT, WPARAM(hFont), TRUE);

					  txtInterestRate = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 150, 150, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(txtInterestRate, WM_SETFONT, WPARAM(hFont), TRUE);

					  hTemp = CreateWindowEx(0, L"STATIC", L"Result", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 250, 100, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);

					  txtResult = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 200, 250, 350, 60, hWnd, NULL, hInst, NULL);
					  SendMessage(txtResult, WM_SETFONT, WPARAM(hFont), TRUE);


					  EnableWindow(txtResult, false);
	}
		break;

	case WM_COMMAND:
	{
					   wmId = LOWORD(wParam);
					   wmEvent = HIWORD(wParam);

					   int txtInterestRateLen, txtAmountOfMoneyLen, txtResultLen;
					   float interestRate;
					   long long amountOfMoney;
					   WCHAR* buff1 = NULL;
					   WCHAR* buff2 = NULL;
					   WCHAR* buffResult = NULL;
					   int numbOfMonth = 12;

					   // Parse the menu selections:
					   switch (wmId)
					   {
					   case IDC_CALC_BUTTON:
						   
						   txtInterestRateLen = GetWindowTextLength(txtInterestRate);
						   txtAmountOfMoneyLen = GetWindowTextLength(txtAmountOfMoney);

						   if (txtAmountOfMoneyLen <= 0 || txtInterestRateLen <= 0)
						   {
							   MessageBox(hWnd, L"Amount of money and interest rate must not be empty!", L"Invalid input", MB_OK | MB_ICONWARNING);
							   break;
						   }

						   //txtResultLen = GetWindowTextLength(txtResult);

						   buff1 = new WCHAR[txtInterestRateLen + 1];
						   buff2 = new WCHAR[txtAmountOfMoneyLen + 1];

						   GetWindowText(txtInterestRate, buff1, txtInterestRateLen + 1);
						   GetWindowText(txtAmountOfMoney, buff2, txtAmountOfMoneyLen + 1);

						   if (!isNumber(buff1, txtInterestRateLen) || !isNumber(buff2, txtAmountOfMoneyLen))
						   {
							   MessageBox(hWnd, L"Amount of money and Interest rate must be a valid Integer of Float!", L"Invalid input", MB_OK | MB_ICONERROR);
							   break;
						   }

						   interestRate = _wtof(buff1);
						   amountOfMoney = _wtoi64(buff2);

						   if (amountOfMoney <= 0)
						   {
							   MessageBox(hWnd, L"Amount of money must greater than zero!", L"Invalid Amount of money", MB_OK | MB_ICONWARNING);
							   break;
						   }
						   else if (interestRate <= 0)
						   {
							   MessageBox(hWnd, L"Interest rate must greater than zero!", L"Invalid Interest rate", MB_OK | MB_ICONWARNING);
							   break;
						   }

						   buff1 = new WCHAR[255];


						   swprintf(buff1, 255, L" Amount of money that you have after %d months with interest rate %.5f is: \r\n -> %.5f$.", numbOfMonth, interestRate, calcMoney(amountOfMoney,interestRate,numbOfMonth));
						   SetWindowText(txtResult, buff1);

						   if (!buff1)
							   delete[] buff1;
						   if (!buff2)
							   delete[] buff2;

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


bool isNumber(WCHAR* c, int n)
{
	bool flag = false;
	for (int i = 0; i < n; i++)
	{
		if (!('0' <= c[i] && c[i] <= '9'))
		{
			if (c[i] == '.' && !flag)
			{
				flag = !flag;
			}
			else
				return false;
		}
	}
	return true;
}

float calcMoney(long long money, float rate, int month)
{
	for (int i = 0; i < month; i++)
	{
		money = money + money*rate;
	}

	return money;
}