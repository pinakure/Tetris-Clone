//
// Win.h: Win32 code
//
#ifndef __WIN_H
#define __WIN_H

/*
========
WinInit
========
	Initializes the Win32 GDI window, and binds Allegro to it.
	hInst: first parameter given to WinMain.
*/
int WinInit(HINSTANCE hInst);

/*
==================
WinHandleMessages
==================
	Handles all pending window messages.
	Returns 0 on window close.
*/
int WinHandleMessages(void);

/*
==========
WinDeinit
==========
	Closes the Win32 window.
*/
void WinDeinit(void);

void OptionsRestoreValues(HWND hDlg);
	
#endif
