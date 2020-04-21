// main.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include "framework.h"
#include "GameLibrary.h"

#define MAX_LOADSTRING	100

// Global Variables:
HINSTANCE hInst;						// Current instance
WCHAR szTitle[MAX_LOADSTRING];			// Title bar text
WCHAR szWindowClass[MAX_LOADSTRING];	// Window name
HWND steamHandle;						// Steam button handle
//HWND originHandle;						// Origin button handle
//HWND battleNetHandle;					// Battle.net button handle
//HWND uplayHandle;						// Uplay button handle
//HWND bethesdaHandle;					// Bethesda button handle
//HWND gogHandle;							// GOG button handle

// Forward declarations of functions:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPWSTR lpCmdLine,
					  _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GAMELIBRARY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMELIBRARY));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
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
// FUNCTION: MyRegisterClass()
//
// PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEXW);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMELIBRARY));
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GAMELIBRARY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
// FUNCTION: InitInstance(HINSTANCE, int)
//
// PURPOSE: Saves instance handle and creates main window.
//
// COMMENTS:
//
//		In this function, we save the instance handle in a global variable and
//		create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	// HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
// FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
// PURPOSE: Processes messages for the main window.
//
// WM_COMMAND  - Process the application menu.
// WM_PAINT	   - Paint the main window.
// WM_DESTROY  - Post a quit message and return.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		steamHandle		= CreateWindow(L"button", L"Steam",		 WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,  10, 10, 50, 30, hWnd, (HMENU)IDC_STEAM,		hInst, NULL);
		/*originHandle	= CreateWindow(L"button", L"Origin",	 WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,  70, 10, 50, 30, hWnd, (HMENU)IDC_ORIGIN,	hInst, NULL);
		battleNetHandle	= CreateWindow(L"button", L"Battle.net", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 130, 10, 75, 30, hWnd, (HMENU)IDC_BATTLENET, hInst, NULL);
		uplayHandle		= CreateWindow(L"button", L"Uplay",		 WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 215, 10, 50, 30, hWnd, (HMENU)IDC_UPLAY,		hInst, NULL);
		bethesdaHandle	= CreateWindow(L"button", L"Bethesda",	 WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 275, 10, 75, 30, hWnd, (HMENU)IDC_BETHESDA,	hInst, NULL);
		gogHandle		= CreateWindow(L"button", L"GOG",		 WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 360, 10, 50, 30, hWnd, (HMENU)IDC_GOG,		hInst, NULL);*/
		EnableWindow(steamHandle, FALSE);
		break;

	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case IDC_STEAM:
				OutputDebugString(L"Steam pressed...\n");
				break;

			/*case IDC_ORIGIN:
				OutputDebugString(L"Origin pressed...\n");
				break;

			case IDC_BATTLENET:
				OutputDebugString(L"Battle.net pressed...\n");
				break;

			case IDC_UPLAY:
				OutputDebugString(L"Uplay pressed...\n");
				break;

			case IDC_BETHESDA:
				OutputDebugString(L"Bethesda pressed...\n");
				break;

			case IDC_GOG:
				OutputDebugString(L"GOG pressed...\n");
				break;*/

			case IDM_LOAD:
				OutputDebugString(L"Loading, but nothing to load.\n");
				EnableWindow(steamHandle, TRUE);
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
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			EndPaint(hWnd, &ps);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//
// FUNCTION: About(HWND, UINT, WPARAM, LPARAM)
//
// PURPOSE: Handles messages for the about box.
//
// WM_INITDIALOG  - Initial display of the box.
// WM_COMMAND     - Handles the buttons.
//
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