// main.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include "framework.h"
#include "resource.h"

#define MAX_LOADSTRING	100

// Global Variables:
HINSTANCE hInst;						// Current instance
WCHAR szTitle[MAX_LOADSTRING];			// Title bar text
WCHAR szWindowClass[MAX_LOADSTRING];	// Window name
HWND steamHwnd;							// Steam button handle
HWND originHwnd;						// Origin button handle
HWND battleNetHwnd;						// Battle.net button handle
HWND uplayHwnd;							// Uplay button handle
HWND bethesdaHwnd;						// Bethesda button handle
HWND gogHwnd;							// GOG button handle
HWND sbHwnd;							// Status Bar handle

// File location defaults:
std::filesystem::path steamPath		= "C:/Program Files (x86)/Steam/Steam.dll";
std::filesystem::path originPath	= "C:/Program Files (x86)/Origin/Origin.exe";
std::filesystem::path battleNetPath = "C:/Program Files (x86)/Battle.net/Battle.net Launcher.exe";
std::filesystem::path uplayPath		= "C:/Program Files (x86)/Ubisoft/Ubisoft Game Launcher/Uplay.exe";
std::filesystem::path bethesdaPath	= "C:/Program Files (x86)/Bethesda.net Launcher/BethesdaNetUpdater.exe";
std::filesystem::path gogPath		= "C:/Program Files (x86)/GOG Galaxy/GalaxyClient.exe";

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

	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 436, 500, nullptr, nullptr, hInstance, nullptr);

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
		// Create the buttons
		steamHwnd		= CreateWindow(L"button", L"Steam",		 WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,  10, 10, 50, 30, hWnd, (HMENU)IDC_STEAM,		hInst, NULL);
		originHwnd		= CreateWindow(L"button", L"Origin",	 WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,  70, 10, 50, 30, hWnd, (HMENU)IDC_ORIGIN,	hInst, NULL);
		battleNetHwnd	= CreateWindow(L"button", L"Battle.net", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 130, 10, 75, 30, hWnd, (HMENU)IDC_BATTLENET, hInst, NULL);
		uplayHwnd		= CreateWindow(L"button", L"Uplay",		 WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 215, 10, 50, 30, hWnd, (HMENU)IDC_UPLAY,		hInst, NULL);
		bethesdaHwnd	= CreateWindow(L"button", L"Bethesda",	 WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 275, 10, 75, 30, hWnd, (HMENU)IDC_BETHESDA,	hInst, NULL);
		gogHwnd			= CreateWindow(L"button", L"GOG",		 WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 360, 10, 50, 30, hWnd, (HMENU)IDC_GOG,		hInst, NULL);
		// Set all buttons to disabled until locations have been confirmed
		EnableWindow(steamHwnd, FALSE);
		EnableWindow(originHwnd, FALSE);
		EnableWindow(battleNetHwnd, FALSE);
		EnableWindow(uplayHwnd, FALSE);
		EnableWindow(bethesdaHwnd, FALSE);
		EnableWindow(gogHwnd, FALSE);

		// Create the status bar
		sbHwnd			= CreateWindow(STATUSCLASSNAME, NULL,	 WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,     0,  0,  0,  0, hWnd, (HMENU)IDC_STATUSBAR, hInst, NULL);
		// Send default text to the status bar
		SendMessage(sbHwnd, SB_SETTEXT, 0, (LPARAM)TEXT("File->Load to get install info..."));

		// TODO: Create the ListView

		break;

	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case IDC_STEAM:
				OutputDebugString(L"Steam pressed...\n");
				// This does nothing (for now)
				break;

			case IDC_ORIGIN:
				OutputDebugString(L"Origin pressed...\n");
				// This does nothing (for now)
				break;

			case IDC_BATTLENET:
				OutputDebugString(L"Battle.net pressed...\n");
				// This does nothing (for now)
				break;

			case IDC_UPLAY:
				OutputDebugString(L"Uplay pressed...\n");
				// This does nothing (for now)
				break;

			case IDC_BETHESDA:
				OutputDebugString(L"Bethesda pressed...\n");
				// This does nothing (for now)
				break;

			case IDC_GOG:
				OutputDebugString(L"GOG pressed...\n");
				// This does nothing (for now)
				break;

			case IDM_LOAD:
				OutputDebugString(L"Beginning process...\n");
				if (std::filesystem::exists(steamPath)) {
					EnableWindow(steamHwnd, TRUE);
					OutputDebugString(L"  Steam loaded\n");
				}
				if (std::filesystem::exists(originPath)) {
					EnableWindow(originHwnd, TRUE);
					OutputDebugString(L"  Origin loaded\n");
				}
				if (std::filesystem::exists(battleNetPath)) {
					EnableWindow(battleNetHwnd, TRUE);
					OutputDebugString(L"  Battle.net loaded\n");
				}
				if (std::filesystem::exists(uplayPath)) {
					EnableWindow(uplayHwnd, TRUE);
					OutputDebugString(L"  Uplay loaded\n");
				}
				if (std::filesystem::exists(bethesdaPath)) {
					EnableWindow(bethesdaHwnd, TRUE);
					OutputDebugString(L"  Bethesda loaded\n");
				}
				if (std::filesystem::exists(gogPath)) {
					EnableWindow(gogHwnd, TRUE);
					OutputDebugString(L"  GOG loaded\n");
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

	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 436;
		lpMMI->ptMinTrackSize.y = 500;
		lpMMI->ptMaxTrackSize.x = 436;
		lpMMI->ptMaxTrackSize.y = 500;
	}
	break;

	case WM_SIZE:
		SendMessage(sbHwnd, WM_SIZE, 0, 0);
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