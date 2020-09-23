//
// Video.h: Video code, header file
//
#ifndef __VIDEO_H
#define __VIDEO_H


// Main backbuffer: size is SCR_WIDTH*SCR_HEIGHT
#define VideoBuffer VideoPages[VideoCurrentPage]


enum E_Colors {
	C_Black,
	C_GrayD,
	C_Gray,
	C_GrayH,
	C_White,
	C_RedD,
	C_Red,
	C_RedH,
	C_YellowD,
	C_Yellow,
	C_YellowH,
	C_GreenD,
	C_Green,
	C_GreenH,
	C_CyanD,
	C_Cyan,
	C_CyanH,
	C_BlueD,
	C_Blue,
	C_BlueH,
	C_Pink,
	C_MAX
};



extern BITMAP *VideoPages[3];
extern int VideoCurrentPage;
extern int VideoScale, VideoDepth, VideoTripleBuffer;
extern int Colors[C_MAX];
extern FONT		*FontRed, 
				*FontBlue,
				*FontGreen,
				*FontWhite,
				*FontMono;
/*
==========
VideoInit
==========
	Initializes video system. Returns 0 on error.
*/
int VideoInit(void);

/*
============
VideoDeInit
============
	Deinitializes video system. 
*/
void VideoDeinit(void);

/*
================
VideoSwitchPage
================
	Switches current draw surface when using triple buffering.
*/
void VideoSwitchPage(void);

/*
===============
VideoDrawFrame
===============
	Draws the video buffer to screen when not using triple buffering.
*/
void VideoDrawFrame(void);

/*
=========
FontInit
=========
	Load font resources.
*/
int FontInit(void);

/*
===============
VideoDrawFrame
===============
	Unload font resources.
*/
void FontDeinit(void);
#endif