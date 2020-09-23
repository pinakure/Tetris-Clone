//
// Console.c: console code
//
#include "Common.h"

static PALETTE VideoPalette;

/* Exported variables */
BITMAP		*VideoPages[3];
int			VideoCurrentPage = 0,
			VideoScale = 0, 
			VideoDepth = 0, 
			VideoTripleBuffer = 0;
int			Colors[C_MAX];
FONT		*FontMono,
			*FontRed,
			*FontBlue,
			*FontGreen,
			*FontWhite;

int FontInit(void)
{
	char *str;
	str = GetStaticChar1024();

	strcpy(str, GameDir);
	strcat(str, "gfx/font.bmp");	
	FontMono = load_font(str, NULL, NULL);
	if(!FontMono) {		
		alert("Can't load", str, NULL, "OK", NULL, 0, 0);
		return 0;
	}
	return 1;
}

void FontDeinit(void)
{
	destroy_font(FontMono);
	destroy_font(FontBlue);		
	destroy_font(FontRed);
	destroy_font(FontGreen);
	destroy_font(FontWhite);
}

int VideoInit(void)
{
	BITMAP *ColorMap;
	char *str;
	int v=0;

	set_color_depth(Options[OPT_ColorDepth]);

	if(Options[OPT_TripleBuffer]) {
		if(Options[OPT_VideoScale] != 1) {
			Options[OPT_VideoScale] = 1;
		}

		if(!Options[OPT_Fullscreen]) {
			Options[OPT_Fullscreen] = 1;
		}

		if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, SCR_WIDTH, SCR_HEIGHT, 0, 0)) {
			v = 1;
			set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
			allegro_message("Can't setup video mode");
			return 0;
		}
				
		if(gfx_capabilities & GFX_CAN_TRIPLE_BUFFER) {
			VideoPages[0] = create_video_bitmap(SCR_WIDTH, SCR_HEIGHT);
			VideoPages[1] = create_video_bitmap(SCR_WIDTH, SCR_HEIGHT);
			VideoPages[2] = create_video_bitmap(SCR_WIDTH, SCR_HEIGHT);
			if(!VideoPages[0] || !VideoPages[1] || !VideoPages[2]) {
				set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
				allegro_message("Can't setup video mode");
				return 0;
			}

			VideoCurrentPage = 0;
			goto next;
		} else {
			Options[OPT_TripleBuffer] = 0;
		}
	}

	if(!v) {
		if(Options[OPT_Fullscreen]) {
			if(set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, SCR_WIDTH*Options[OPT_VideoScale], SCR_HEIGHT*Options[OPT_VideoScale], 0, 0)) {
				allegro_message("Can't setup video mode");
				return 0;
			}
		} else {
			if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCR_WIDTH*Options[OPT_VideoScale], SCR_HEIGHT*Options[OPT_VideoScale], 0, 0)) {
				allegro_message("Can't setup video mode");
				return 0;
			}
		}
	}

	VideoCurrentPage = 0;
	VideoPages[0] = create_bitmap(SCR_WIDTH, SCR_HEIGHT);
	if(!VideoPages[0]) {
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Can't setup video mode");
		return 0;
	}

next:;
	VideoScale = Options[OPT_VideoScale];
	VideoDepth = Options[OPT_ColorDepth];
	VideoTripleBuffer = Options[OPT_TripleBuffer];

	/*load color map*/
	str = GetStaticChar1024();

	strcpy(str, GameDir);
	strcat(str, "gfx/colormap.bmp");
	ColorMap = load_bitmap(str, VideoPalette);
	if(!ColorMap) {
		alert("Can't load", str, NULL, "OK", NULL, 0, 0);
		return 0;
	}
	destroy_bitmap(ColorMap);

	set_palette(VideoPalette); 	

	Colors[C_Black] = makecol(  0,   0,   0);
	Colors[C_GrayD] = makecol( 64,  64,  64);
	Colors[C_Gray ] = makecol(128, 128, 128);
	Colors[C_GrayH] = makecol(192, 192, 192);
	Colors[C_White] = makecol(255, 255, 255);
	Colors[C_RedD ] = makecol( 64,   0,   0);
	Colors[C_Red  ] = makecol(128,   0,   0);
	Colors[C_RedH ] = makecol(255,   0,   0);
	Colors[C_YellowD]=makecol( 64,  64,   0);
	Colors[C_Yellow]= makecol(128, 128,   0);
	Colors[C_YellowH]=makecol(255, 255,   0);
	Colors[C_GreenD]= makecol(  0,  64,   0);
	Colors[C_Green] = makecol(  0, 128,   0);
	Colors[C_GreenH]= makecol(  0, 255,   0);
	Colors[C_CyanD] = makecol(  0,  64, 255);
	Colors[C_Cyan ] = makecol(  0, 128, 255);
	Colors[C_CyanH] = makecol(  0, 255, 255);
	Colors[C_BlueD] = makecol(  0,   0,  64);
	Colors[C_Blue ] = makecol(  0,   0, 128);
	Colors[C_BlueH] = makecol(  0,   0, 255);
	Colors[C_Pink ] = makecol(255,   0, 255);
	
	if(!FontInit())
	{
		destroy_bitmap(VideoPages[0]);
		if(VideoTripleBuffer) {
			destroy_bitmap(VideoPages[1]);
			destroy_bitmap(VideoPages[2]);
		}	
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);	
		return 0;
	}
	return 1;
}

void VideoDeinit(void)
{	
	destroy_bitmap(VideoPages[0]);

	if(VideoTripleBuffer) {
		destroy_bitmap(VideoPages[1]);
		destroy_bitmap(VideoPages[2]);
	}

	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);	
}

/* TRIPLE BUFFERING FUNCTIONS */
void VideoSwitchPage(void)
{	
	//If triple buffer enabled, switch video page			
	if(VideoTripleBuffer) {
		if(!poll_scroll()) {
			request_video_bitmap(VideoBuffer);
			VideoCurrentPage = (VideoCurrentPage+1) % 3;
		}
	}

	// Whatever the triple buffer is enabled or not, clean the video surface
	if(VideoDepth == 8) {
		clear_to_color(VideoBuffer, 1);
	} else {
		clear_bitmap(VideoBuffer);
	}
}

void VideoDrawFrame(void)
{
	/*If not using Triple buffering, blit videobuffer to screen memory*/
	if(!VideoTripleBuffer)
	{			
		stretch_blit(VideoBuffer, screen,
			0, 0, SCR_WIDTH, SCR_HEIGHT,
			0, 0, VideoScale * SCR_WIDTH, VideoScale * SCR_HEIGHT);			
	}
}

