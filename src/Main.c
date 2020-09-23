#define VSYNC 1

#include "Common.h"	
#include <winalleg.h>
#include <windows.h>
#include <direct.h>

#ifdef DEBUG
const char GameDir[256]="./";
#else
const char GameDir[256]="./";
#endif

static void EngineTicker(void);
int SndInit(void);
void SndDeinit(void);

int				Options[OPT_MAX];
static int		EngineOldTick= 0;

static int Init(void)
{	
	install_keyboard();
	install_timer();
	
	if(!VideoInit()) {
		return 0;
	}

	if(!SndInit()){
		VideoDeinit();
		return 0;
	}

	if(!GameInit()) {
		SndDeinit();
		VideoDeinit();
		return 0;
	}
	
	if(!HUDInit()) {
		SndDeinit();
		GameDeinit();
		VideoDeinit();
		return 0;
	}
	install_int_ex(EngineTicker, BPS_TO_TIMER(FPS));
	return 1;
}

static void Deinit(void)
{
	remove_int(EngineTicker);
	SaveOptions();
	HUDDeinit();
	GameDeinit();
	VideoDeinit();
	SndDeinit();
}



/* TIMER FUNCTION */
static volatile 
unsigned int	EngineFrames = 0,
				EngineFPS	 = 1,
				EnginePeakFPS= 0,
				EngineDrive	 = 0,
				EngineTicks  = 1;

static void EngineTicker(void)
{
	EngineTicks++;

	if((EngineTicks%FPS)==0) {
		EngineFPS = EngineFrames;
		EngineFrames = 0;
		if(EngineFPS > EnginePeakFPS) EnginePeakFPS = EngineFPS;
	}
}
END_OF_STATIC_FUNCTION(EngineTicker);
/* END OF TIMER FUNCTION */


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	int Execute;

	LoadOptions();
	WinInit(hInst);

	allegro_init();
	
	Execute = Init();
	if(!Execute)return -1;

	SndPlayMusic(SND_Music);
	SndSetVolume(SND_Music, 0.2f);	
	while(Execute)
	{
		if(!WinHandleMessages()) {
			Execute = 0;
		}

		/* MAIN LOOP */
		
		if(EngineOldTick != EngineTicks)
		{
			/* LOGIC */
			EngineOldTick = EngineTicks;			
			
			if(key[KEY_ESC])Execute = 0;								
			
			GameTick();
			HUDTick();

			/*END OF LOGIC*/
		}

		/* DRAW */
		VideoSwitchPage();
		

		/*draw here*/
		HUDDraw();
		GameDraw();
		
		VideoDrawFrame();
		
		SndUpdate();
		EngineFrames++;

		if(Options[OPT_VSync]) {
			vsync();			
		}
	}		
	Deinit();

	WinDeinit();
	return 0;
}
