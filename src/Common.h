//
//	Common.h: Gemz main header
//

#ifndef __COMMON_H
#define __COMMON_H

//
// System includes
//
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable: 4996)
#pragma warning(disable: 4312)
//#include <fmod.h>
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <setjmp.h>
#include <winalleg.h>
#include <windows.h>
#include <direct.h>

#define FPS		60
#define TimeDT	(1.0f / (float) FPS)

// SCR_WIDTH and SCR_HEIGHT are the virtual dimensions of the screen.
#define SCR_WIDTH	320
#define SCR_HEIGHT	240

#define SCR_DEPTH	VideoDepth
#define SCR_FULLSCREEN

#define SCR_SCALE	VideoScale

// When SCR_SCALE is defined, the actual screen size is multiplied by SCR_SCALE
#ifndef SCR_FULLSCREEN
#endif

// This define enables cheats, debug info and hacks to debug the code.
#define DEBUG

// If defined, the system will fill the settings file with junk.
#define JUNK_CFG

// Breakpoint.
#ifdef DEBUG
#define BREAK()	do { __asm int 3; } while(0)
#else
#define BREAK()
#endif


enum E_Options {
	OPT_Sound,
	OPT_Music,
	OPT_Physics,
	OPT_Powerups,
	OPT_Cheats,
	OPT_Fullscreen,
	OPT_VSync,
	OPT_VideoScale,
	OPT_TripleBuffer,
	OPT_ColorDepth,
	OPT_MAX
};

enum E_EngineModes {
	EM_Game,
	EM_Editor,
	EM_Menu,
	EM_PreTitle,

	// PUT NODRAW MODES DOWN HERE
	EM_NoDraw,
	EM_Exit,
	EM_Init,	
	EM_Deinit
};

extern int Options[];
extern const char GameDir[];

/*
==================
GetStaticChar1024
==================
	This function returns a static array of characters, 1024 chars
	long. This function only uses one buffer and is unsafe to call.
*/
char *GetStaticChar1024(void);

/*
=============
ChopString
=============
	This function returns a piece of string of the requested size.
*/
void ChopString(char *source, char *dest, int start, unsigned int len);

/*
==============
ValidFilename
==============
	This function returns 1 if fname is a valid filename. ext is a string
	with the expected file extension (in uppercase).

	Valid filenames:
		- Must have at least one letter before period
		- Must have only one period, and exactly 3 characters after it.
		- Can't be >= 64 characters, including extension.
		- Only contain:
			- Alphanumeric characters
			- Space (0x20, ' ')
			- One dot (for extension)
*/
int ValidFilename(char *fname, char *ext);

/*
===========
BlitSprite
===========
	Draws a sprite, masking full pink colors.
*/
void BlitSprite(BITMAP *bmp, int SX, int SY);

/*
===
va
===
	Returns a GetStaticChar1024() buffer filled with the
	printf-like args.
*/
char *va(char *fmt, ...);

/*
======
OnOff
======
	Returns "Enabled" if variable given is true, "Disabled" if false.
*/
char *OnOff(int variable);

int LoadOptions(void);
void NewOptions(void);
int SaveOptions(void);


//
// Game includes
//

#include "Win.h"				// Win32 code
#include "Map.h"				// Map code
#include "Sound.h"				// Sound code
#include "Video.h"				// Video code
#include "Game.h"				// Game code
#include "Hud.h"				// HUD Code
#include "Pieces.h"				// Pieces Code

#endif
