// Week1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Week1.h"

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

HWND txtTotalBillCost, txtNumbOfGuest, txtResult;

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
	LoadString(hInstance, IDC_WEEK1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WEEK1));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WEEK1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WEEK1);
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

   hWnd = CreateWindowEx(0,szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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

					  hTemp = CreateWindowEx(0, L"STATIC", L"Total bill cost:", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 50, 100, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);

					  hTemp = CreateWindowEx(0, L"STATIC", L"Number of guest:", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 150, 100, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);

					  txtTotalBillCost = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 250, 50, 100, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(txtTotalBillCost, WM_SETFONT, WPARAM(hFont), TRUE);

					  txtNumbOfGuest = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 250, 150, 100, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(txtNumbOfGuest, 0, WPARAM(hFont), TRUE);

					  hTemp = CreateWindowEx(0, L"STATIC", L"Kết quả:", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 250, 100, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(hTemp, WM_SETFONT, WPARAM(hFont), TRUE);

					  txtResult = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 250, 250, 300, 40, hWnd, NULL, hInst, NULL);
					  SendMessage(txtResult, WM_SETFONT, WPARAM(hFont), TRUE);

		
					  EnableWindow(txtResult, false);
		}
		break;

		case WM_COMMAND:
		{
						   wmId = LOWORD(wParam);
						   wmEvent = HIWORD(wParam);

						   int txtNumbOfGuestLen, txtTotalBillCostLen, txtResultLen;
						   int numbOfGuest, totalBillCost;
						   WCHAR* buff1 = NULL;
						   WCHAR* buff2 = NULL;
						   WCHAR* buffResult = NULL;

						   // Parse the menu selections:
						   switch (wmId)
						   {
						   case IDC_CALC_BUTTON:

							   txtNumbOfGuestLen = GetWindowTextLength(txtNumbOfGuest);
							   txtTotalBillCostLen = GetWindowTextLength(txtTotalBillCost);

							   if (txtTotalBillCostLen <= 0 || txtNumbOfGuestLen <= 0)
							   {
								   MessageBox(hWnd, L"Total bill cost and number of guest must not be empty!", L"Invalid input", MB_OK | MB_ICONWARNING);
									break;
							   }

							   //txtResultLen = GetWindowTextLength(txtResult);

							   buff1 = new WCHAR[txtNumbOfGuestLen + 1];
							   buff2 = new WCHAR[txtTotalBillCostLen + 1];

							   GetWindowText(txtNumbOfGuest, buff1, txtNumbOfGuestLen + 1);
							   GetWindowText(txtTotalBillCost, buff2, txtTotalBillCostLen + 1);

							   if (!isNumber(buff1,txtNumbOfGuestLen) || !isNumber(buff2,txtTotalBillCostLen))
							   {
								   MessageBox(hWnd, L"Total bill cost and Number of guest must be a number!", L"Invalid input", MB_OK | MB_ICONERROR);
									break;
							   }

							   numbOfGuest = _wtoi(buff1);
							   totalBillCost = _wtoi(buff2);

							   if (totalBillCost <= 0)
							   {
								   MessageBox(hWnd, L"Total bill cost must greater than zero!", L"Invalid total bill cost", MB_OK | MB_ICONWARNING);
									break;
							   }
							   else if (numbOfGuest <= 0)
							   {
								   MessageBox(hWnd, L"Number of guest must greater than zero!", L"Invalid number of guest", MB_OK | MB_ICONWARNING);
								   break;
							   }

								   buff1 = new WCHAR[255];


							   swprintf(buff1, 255 ,L" Tips: %.2f. \r\n Each guest must pay: %.2f", totalBillCost*0.1, (totalBillCost*1.1 / numbOfGuest));
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
	for (int i = 0; i < n; i++)
	{
		if (!('0' <= c[i] && c[i] <= '9'))
		{
			return false;
		}
	}
	return true;
}