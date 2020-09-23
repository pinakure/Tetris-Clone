//
// Sound.c: Sound code
//
#include "Common.h"

#define MAX_CHANNELS	128
#define MAX_POLY		2

//static FMOD_SYSTEM *Sys;
//static FMOD_SOUND *Sounds[SND_MAX];
//static int Channel = 0;

static int LoadSound(char *fname, int idx)
{
	/*char *str;

	str = GetStaticChar1024();
	strcpy(str, GameDir);
	strcat(str, "sounds/");
	strcat(str, fname);

	if(FMOD_System_CreateSound(Sys, str, FMOD_DEFAULT, NULL, &Sounds[idx]) != FMOD_OK) {
		alert("Can't load", str, NULL, "OK", NULL, 0, 0);
		return 0;
	}
	*/
	return 1;
}

static void Free(void)
{
	/*int i;

	for(i=0; i<SND_MAX; i++) {
		if(Sounds[i]) {
			FMOD_Sound_Release(Sounds[i]);
			Sounds[i] = NULL;
		}
	}*/
}
/*
FMOD_DSP*			DSP_Echo;
FMOD_CHANNEL*		DSP_Chan;
FMOD_RESULT			DSP_Error;
	*/

int SndInit(void)
{
	/*int i;

	if(FMOD_System_Create(&Sys) != FMOD_OK) {
		alert("Can't initialize FMOD", NULL, NULL, "OK", NULL, 0, 0);
		return 0;
	}

	if(FMOD_System_Init(Sys, MAX_CHANNELS, FMOD_DEFAULT, NULL) != FMOD_OK) {
		FMOD_System_Release(Sys);
		alert("Can't initialize FMOD", NULL, NULL, "OK", NULL, 0, 0);
		return 0;
	}

	for(i=0; i<SND_MAX; i++) {
		Sounds[i] = NULL;
	}


#define Load(fname, idx) \
	if(!LoadSound(fname, idx)) { Free(); return 0; }

	// sound loading
	Load("silence.wav",		SND_Mute)
	Load("tetris.xm",		SND_Music)
	Load("levelup.wav",		SND_LevelUp)
	Load("rotate.wav",		SND_Rotate)
	Load("gover.wav",		SND_GameOver)
	Load("gstart.wav",		SND_GameStart)
	Load("line.wav",		SND_Line)
	Load("drop.wav",		SND_PieceDrop)
#undef Load

	
	// Add audio DSP's 
	FMOD_System_GetChannel(Sys, FMOD_CHANNEL_FREE, &DSP_Chan);
#ifdef DSP
		if(FMOD_System_CreateDSPByType(Sys, FMOD_DSP_TYPE_ECHO, &DSP_Echo) == FMOD_OK) {			
			//if(FMOD_Channel_AddDSP(DSP_Chan, DSP_Echo, 0) == FMOD_OK) {
			if(FMOD_System_AddDSP(Sys, DSP_Echo, NULL) == FMOD_OK) {
				FMOD_DSP_SetParameter(DSP_Echo, FMOD_DSP_ECHO_DECAYRATIO, 0.6f);
				FMOD_DSP_SetParameter(DSP_Echo, FMOD_DSP_ECHO_DELAY,      88.0f);
				FMOD_DSP_SetParameter(DSP_Echo, FMOD_DSP_ECHO_DRYMIX,     1.0f);
				FMOD_DSP_SetParameter(DSP_Echo, FMOD_DSP_ECHO_WETMIX,     0.5f);
			} else {
				alert("Can't add DSP", "to channel", NULL, "OK", NULL, 0, 0);
			}
		} else {
			alert("Can't create DSP", "DSP_ECHO", NULL, "OK", NULL, 0, 0);
		}
#endif
		*/
	return 1;
}

void SndDeinit(void)
{
	/*Free();
	FMOD_System_Release(Sys);*/
}

void SndPlayMusic(enum E_Sound Sound)
{
	/*
	if(Options[OPT_Music]) {
		switch(Sound) {
			case SND_Music:
				FMOD_System_PlaySound(Sys, SND_Music, Sounds[Sound], FALSE, NULL);	
				break;
		}
	}
	*/
}

void SndSetVolume(enum E_Sound Sound, float volume)
{
	/*
	FMOD_CHANNEL* channel;
	
	FMOD_System_GetChannel(Sys, SND_Music, &channel);
  
	FMOD_Channel_SetVolume(channel, volume);
	*/
}

void SndStop(enum E_Sound Sound)
{
	//FMOD_System_PlaySound(Sys, Sound, Sounds[SND_Mute], FALSE, NULL);	
}

void SndPlaySound(enum E_Sound Sound)
{
	/*
	if(Options[OPT_Sound]){
			switch(Sound)
		{
			//Non Trigerable sounds
			case SND_Music:
				break;
			case SND_LevelUp:
			case SND_Line:
			case SND_Rotate:
			case SND_GameOver:
			case SND_GameStart:
			case SND_PieceDrop:
				FMOD_System_PlaySound(Sys, Sound, Sounds[Sound], FALSE, NULL);
				break;		
		}	
	}
	*/
}

	


void SndUpdate(void)
{
	//FMOD_System_Update(Sys);
}
