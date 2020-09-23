//
// Win.h: Win32 code
//
#include "Common.h"
#include "resource.h"

#define CLASS_NAME		L"Tetris"
#define WINDOW_TITLE	L"Tetris"

// TODO: fix minimize bug
#define WND_STYLE		(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU/* | WS_MINIMIZEBOX*/)

static HINSTANCE hAppInst;
static HWND hMainWnd;
static int Quit=1;

static BOOL CALLBACK AboutProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_CLOSE) {
		EndDialog(hDlg, 0);
		return 0;
	}

	if(uMsg == WM_COMMAND) {
		switch(wParam) {
			case IDOK:
				EndDialog(hDlg, 0);
				return 0;
		}
	}

	return 0;
}

LPCTSTR KT_D = L"D";
	
static void OptionsRestoreValues(HWND hDlg)
{
	SendDlgItemMessage(hDlg, ID_P1_ROTATE_LEFT, EM_SETLIMITTEXT, 1, 0);
	SendDlgItemMessage(hDlg, ID_P1_ROTATE_RIGHT, EM_SETLIMITTEXT, 1, 0);
	SendDlgItemMessage(hDlg, ID_P1_MOVE_LEFT, EM_SETLIMITTEXT, 1, 0);
	SendDlgItemMessage(hDlg, ID_P1_MOVE_RIGHT, EM_SETLIMITTEXT, 1, 0);
	SendDlgItemMessage(hDlg, ID_P1_DROP, EM_SETLIMITTEXT, 1, 0);
	
	//SendMessage(GetDlgItem(hDlg, ID_P1_DROP), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)KT_D);



	if(Options[OPT_Music] == 1) {
		SendDlgItemMessage(hDlg, ID_MUSIC_ENABLED, BM_SETCHECK, BST_CHECKED, 0);
		SendDlgItemMessage(hDlg, ID_MUSIC_DISABLED, BM_SETCHECK, BST_UNCHECKED, 0);
	} else {
		SendDlgItemMessage(hDlg, ID_MUSIC_ENABLED, BM_SETCHECK, BST_UNCHECKED, 0);
		SendDlgItemMessage(hDlg, ID_MUSIC_DISABLED, BM_SETCHECK, BST_CHECKED, 0);		
	}

	if(Options[OPT_Sound] == 1) {
		SendDlgItemMessage(hDlg, ID_SOUNDFX_ENABLED, BM_SETCHECK, BST_CHECKED, 0);		
		SendDlgItemMessage(hDlg, ID_SOUNDFX_DISABLED, BM_SETCHECK, BST_UNCHECKED, 0);		
	} else { 
		SendDlgItemMessage(hDlg, ID_SOUNDFX_ENABLED, BM_SETCHECK, BST_UNCHECKED, 0);		
		SendDlgItemMessage(hDlg, ID_SOUNDFX_DISABLED, BM_SETCHECK, BST_CHECKED, 0);		
	}
	//ID_SCALE:
	if(Options[OPT_VSync] == 1) {
		SendDlgItemMessage(hDlg, ID_VSYNC, BM_SETCHECK, BST_CHECKED, 0);
	} else {
		SendDlgItemMessage(hDlg, ID_VSYNC, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	if(Options[OPT_Fullscreen] == 1) {
		SendDlgItemMessage(hDlg, ID_FULLSCREEN, BM_SETCHECK, BST_CHECKED, 0);
	} else {
		SendDlgItemMessage(hDlg, ID_FULLSCREEN, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	if(Options[OPT_TripleBuffer]) {
		SendDlgItemMessage(hDlg, ID_TRIPLEBUFFER, BM_SETCHECK, BST_CHECKED, 0);
	} else {
		SendDlgItemMessage(hDlg, ID_TRIPLEBUFFER, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	//ID_FILTER:
}

static BOOL CALLBACK OptionsProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	OptionsRestoreValues(hDlg);
	
	if(uMsg == WM_KEYDOWN) {
		switch(wParam) {
			/* KEY BINDINGS */
			case ID_P1_ROTATE_LEFT:
				break;
				/*
				KeyMap[K_P1RotateLeft] = 0;
				KeyMap[K_P1RotateRight] = 0;
				KeyMap[K_P1MoveLeft] = 0;
				KeyMap[K_P1MoveRight] = 0;
				KeyMap[K_P1Drop] = 0;
				KeyMap[K_P2RotateLeft] = 0;
				KeyMap[K_P2RotateRight] = 0;
				KeyMap[K_P2MoveLeft] = 0;
				KeyMap[K_P2MoveRight] = 0;
				KeyMap[K_P2Drop] = 0;
				*/	

			case ID_P1_ROTATE_RIGHT:
			case ID_P1_MOVE_LEFT:
			case ID_P1_MOVE_RIGHT:
			case ID_P1_DROP:
			case ID_P2_ROTATE_LEFT:
			case ID_P2_ROTATE_RIGHT:
			case ID_P2_MOVE_LEFT:
			case ID_P2_MOVE_RIGHT:
			case ID_P2_DROP:
				break;			
		}		
		return 0;
	}

	if(uMsg == WM_CLOSE) {
		EndDialog(hDlg, 0);
		return 0;
	}
	if(uMsg == WM_COMMAND) {
		switch(wParam) {
			case IDOK:
				EndDialog(hDlg, 0);
				return 0;

			/* MUSIC */
			case ID_MUSIC_ENABLED:
				Options[OPT_Music] = 1;
				return 0;			
			case ID_MUSIC_DISABLED:
				Options[OPT_Music] = 0;
				return 0;

			/* SFX */			
			case ID_SOUNDFX_ENABLED:
				Options[OPT_Sound] = 1;
				return 0;			
			case ID_SOUNDFX_DISABLED:
				Options[OPT_Sound] = 0;
				return 0;
			
			/* VIDEO SCALE */
			case ID_SCALE:				
				Options[OPT_VideoScale] = SendDlgItemMessage(hDlg, ID_SCALE, BM_GETSTATE, 0, 0);
				SendDlgItemMessage(hDlg, ID_SCALEVALUE, BM_SETSTATE, Options[OPT_VideoScale], 0);
				return 0;
			/* VIDEO OPTIONS */
			case ID_VSYNC:			
				Options[OPT_VSync] ^= 1;				
				break;
			
			case ID_FULLSCREEN:
				SendDlgItemMessage(hDlg, ID_FULLSCREEN, BM_SETCHECK, BST_UNCHECKED, 0);
				return 0;

			case ID_TRIPLEBUFFER:
				SendDlgItemMessage(hDlg, ID_TRIPLEBUFFER, BM_SETCHECK, BST_UNCHECKED, 0);
				return 0;

			case ID_FILTER:
				SendDlgItemMessage(hDlg, ID_FILTER, BM_SETCHECK, BST_UNCHECKED, 0);				
				return 0;
			
		}
	}
	
	return 0;
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) {
		case WM_COMMAND:
			switch(wParam) {
				case ID_GAME_OPTIONS:
					DialogBoxParam(hAppInst,
						MAKEINTRESOURCE(ID_OPTIONS),
						hMainWnd,
						OptionsProc, 0);
					return 0;

				case ID_GAME_QUIT:
					Quit = 0;
					return 0;

				case ID_HELP_ABOUT:
					DialogBoxParam(hAppInst,
						MAKEINTRESOURCE(ID_ABOUT),
						hMainWnd,
						OptionsProc, 0);
					return 0;
			}

			return 0;

		case WM_CLOSE:
		case WM_QUIT:
		case WM_DESTROY:
			Quit = 0;
			return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

static void SwitchCb(void)
{
	ShowWindow(hMainWnd, SW_SHOW);
	InvalidateRect(hMainWnd, NULL, TRUE);
}

int WinInit(HINSTANCE hInst)
{
	WNDCLASS cls;
	RECT rc;

	hAppInst = hInst;

	memset(&cls, 0, sizeof(WNDCLASS));
	cls.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	cls.lpfnWndProc = WndProc;
	cls.hInstance = hInst;
	cls.lpszClassName = CLASS_NAME;
	
	// TODO: put icon, menu
	cls.hIcon = LoadIcon(hAppInst, MAKEINTRESOURCE(IDI_ICON1));
	cls.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	if(!RegisterClass(&cls)) {
		MessageBoxA(NULL, "Can't register window class", "Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	rc.left = 0;
	rc.top = 0;
	rc.right = SCR_WIDTH * Options[OPT_VideoScale];
	rc.bottom = SCR_HEIGHT * Options[OPT_VideoScale];
	AdjustWindowRect(&rc, WND_STYLE, TRUE);

	hMainWnd = CreateWindow(
		CLASS_NAME, WINDOW_TITLE, WND_STYLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, hAppInst, NULL);
	
	if(!hMainWnd) {
		UnregisterClass(CLASS_NAME, hAppInst);
		MessageBoxA(NULL, "Can't create window", "Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hMainWnd, SW_SHOW);
	win_set_window(hMainWnd);

	return 1;
}

int WinHandleMessages(void)
{
	MSG msg;

	while(PeekMessage(&msg, hMainWnd, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return Quit;
}

void WinDeinit(void)
{
	DestroyWindow(hMainWnd);
	UnregisterClass(CLASS_NAME, hAppInst);
}
