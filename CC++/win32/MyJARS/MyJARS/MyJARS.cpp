// MyJARS.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MyJARS.h"
#include <commctrl.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
#define _CRT_NON_CONFORMING_SWPRINTFS

#define MAX_LOADSTRING 100

#define DEFAULT_STATIC_WIDTH 200
#define DEFALT_EDIT_WIDTH	360
#define RESULT_EDITBOX_WIDTH 320
#define DEFAULT_EDIT_HEIGHT 40

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND hTotalMoney, hEssentialSpending, hInvestmentMoney, hEducationMoney, hSavings, hEnjoymentMoney, hGiveAway;
HWND hBtnCalculate;
HWND hGiveAwayText;
long amountOfMoney;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK GiveAway(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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
	LoadString(hInstance, IDC_MYJARS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYJARS));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYJARS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MYJARS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMILE));

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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
	   GetSystemMetrics(SM_CXSCREEN)/2 - 680/2, GetSystemMetrics(SM_CYSCREEN)/2 - 600/2, 680, 600, NULL, NULL, hInstance, NULL);

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

					  HFONT hFont = CreateFont(60, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
					  HWND hTemp;


					  hTemp = CreateWindowEx(0, L"STATIC", L"JARS", WS_CHILD | WS_VISIBLE | SS_LEFT, 280, 20, DEFAULT_STATIC_WIDTH, 50, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);
					  

					  hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

					  //hTemp = CreateWindowEx(0, L"STATIC", L"Type your total money", WS_CHILD | WS_VISIBLE  | SS_LEFT, 100, 100, DEFAULT_STATIC_WIDTH, 40, hWnd, NULL, hInst, NULL);					  
					  //SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);

					  hTemp = CreateWindowEx(0, L"STATIC", L"Essential Spending", WS_CHILD | WS_VISIBLE | SS_LEFT, 100, 160, DEFAULT_STATIC_WIDTH, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);



					  hTemp = CreateWindowEx(0, L"STATIC", L"Investment", WS_CHILD | WS_VISIBLE | SS_LEFT, 100, 220, DEFAULT_STATIC_WIDTH, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);


					  hTemp = CreateWindowEx(0, L"STATIC", L"Education", WS_CHILD | WS_VISIBLE | SS_LEFT, 100, 280, DEFAULT_STATIC_WIDTH, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);


					  hTemp = CreateWindowEx(0, L"STATIC", L"Savings", WS_CHILD | WS_VISIBLE | SS_LEFT, 100, 340, DEFAULT_STATIC_WIDTH, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);

					  hTemp = CreateWindowEx(0, L"STATIC", L"Enjoyment Money", WS_CHILD | WS_VISIBLE | SS_LEFT, 100, 400, 200, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);

					  hGiveAwayText = CreateWindowEx(0, L"STATIC", L"Give away Money", WS_CHILD | SS_LEFT, 100, 460, 200, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hGiveAwayText, WM_SETFONT, WPARAM(hFont), TRUE);

						
					  //Edit Control
					  hTotalMoney = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 100, 100, DEFALT_EDIT_WIDTH, DEFAULT_EDIT_HEIGHT, hWnd, NULL, hInst, NULL);
					  SendMessage(hTotalMoney, WM_SETFONT, WPARAM(hFont), TRUE);
					  SendMessage(hTotalMoney, EM_SETCUEBANNER, TRUE, LPARAM(L"Input total amount of money..."));

					  hEssentialSpending = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 250, 160, RESULT_EDITBOX_WIDTH, DEFAULT_EDIT_HEIGHT, hWnd, NULL, hInst, NULL);
					  SendMessage(hEssentialSpending, WM_SETFONT, WPARAM(hFont), TRUE);


					  hInvestmentMoney = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 250, 220, RESULT_EDITBOX_WIDTH, DEFAULT_EDIT_HEIGHT, hWnd, NULL, hInst, NULL);
					  SendMessage(hInvestmentMoney, WM_SETFONT, WPARAM(hFont), TRUE);


					  hEducationMoney = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 250, 280, RESULT_EDITBOX_WIDTH, DEFAULT_EDIT_HEIGHT, hWnd, NULL, hInst, NULL);
					  SendMessage(hEducationMoney, WM_SETFONT, WPARAM(hFont), TRUE);

					  hSavings = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 250, 340, RESULT_EDITBOX_WIDTH, DEFAULT_EDIT_HEIGHT, hWnd, NULL, hInst, NULL);
					  SendMessage(hSavings, WM_SETFONT, WPARAM(hFont), TRUE);

					 

					  hEnjoymentMoney = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 250, 400, RESULT_EDITBOX_WIDTH, DEFAULT_EDIT_HEIGHT, hWnd, NULL, hInst, NULL);
					  SendMessage(hEnjoymentMoney, WM_SETFONT, WPARAM(hFont), TRUE);

					  

					  hGiveAway = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_BORDER | ES_READONLY, 250, 460, RESULT_EDITBOX_WIDTH, DEFAULT_EDIT_HEIGHT, hWnd, NULL, hInst, NULL);
					  SendMessage(hGiveAway, WM_SETFONT, WPARAM(hFont), TRUE);

					  hBtnCalculate = CreateWindowEx(0, L"BUTTON", L"CALCULATE", WS_CHILD | WS_BORDER | WS_VISIBLE | BS_PUSHBUTTON | ACS_CENTER | BS_BITMAP, 470, 100, 100, DEFAULT_EDIT_HEIGHT, hWnd, (HMENU)IDC_BUTTON, hInst, NULL);
					  hFont = CreateFont(20, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI"); 
					  SendMessage(hBtnCalculate, WM_SETFONT, WPARAM(hFont), TRUE);

	}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_BUTTON:
		{
						   int len = GetWindowTextLength(hTotalMoney);

						   if (len <= 1)
						   {
							   MessageBox(hWnd, L"Amount of Money must not be empty!", L"Invalid Input", MB_OK | MB_ICONERROR);
							   break;
						   }

						   WCHAR* buffer = new WCHAR[len + 1];
						   long result;

						   GetWindowText(hTotalMoney, buffer, len + 1);
						   amountOfMoney = _wtol(buffer);

						   if (amountOfMoney < 10)
						   {
							   MessageBox(hWnd, L"Amount of Money must be greater than 10", L"Invalid Input", MB_OK | MB_ICONWARNING);
							   break;
						   }

						   result = amountOfMoney * 55 / 100;
						   wsprintf(buffer, L"%d", result);
						   SetWindowText(hEssentialSpending, buffer);

						   result = amountOfMoney * 10 / 100;
						   wsprintf(buffer, L"%d", result);
						   SetWindowText(hInvestmentMoney, buffer);

						   wsprintf(buffer, L"%d", result);
						   SetWindowText(hEducationMoney, buffer);

						   wsprintf(buffer, L"%d", result);
						   SetWindowText(hSavings, buffer);

						   //Show dialog de nguoi dung lua chon
						   DialogBox(hInst, MAKEINTRESOURCE(IDD_GIVEAWAY), hWnd, GiveAway);

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


// Message handler for about box.
INT_PTR CALLBACK GiveAway(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//Xu ly
	WCHAR* buffer = new WCHAR[20];
	long result = amountOfMoney * 10 / 100;


	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			//Hide giveaway window
			ShowWindow(hGiveAway, SW_HIDE);
			ShowWindow(hGiveAwayText, SW_HIDE);

			//Calc and set money
			result = amountOfMoney * 15 / 100;
			wsprintf(buffer, L"%d", result);
			SetWindowText(hEnjoymentMoney, buffer);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDOK)
		{
			//Show give away window
			ShowWindow(hGiveAway, SW_SHOW);
			ShowWindow(hGiveAwayText, SW_SHOW);

			//Calc and set money
			result = amountOfMoney * 10 / 100;
			wsprintf(buffer, L"%d", result);
			SetWindowText(hEnjoymentMoney, buffer);

			result = amountOfMoney * 5 / 100;
			wsprintf(buffer, L"%d", result);
			SetWindowText(hGiveAway, buffer);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	case WM_CLOSE:
		//Hide giveaway window
		ShowWindow(hGiveAway, SW_HIDE);
		ShowWindow(hGiveAwayText, SW_HIDE);

		//Calc and set money
		result = amountOfMoney * 15 / 100;
		wsprintf(buffer, L"%d", result);
		SetWindowText(hEnjoymentMoney, buffer);

		EndDialog(hDlg, LOWORD(wParam));
		return (INT_PTR)TRUE;
		break;
	}
	return (INT_PTR)FALSE;
}
