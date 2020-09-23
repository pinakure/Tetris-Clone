//
// Sound.h: Sound code, header file
//
#ifndef __SOUND_H
#define __SOUND_H

enum E_Sounds
{	
	SND_Mute,
	SND_Line,
	SND_Rotate,
	SND_Music,
	SND_LevelUp,
	SND_GameOver,
	SND_GameStart,
	SND_PieceDrop,
	SND_MAX
};

/*
========
SndInit
========
	Allocates all sounds. Returns 1 on success.
*/
int SndInit(void);

/*
==========
SndDeinit
==========
	Frees the sounds.
*/
void SndDeinit(void);

/*
=============
SndPlaySound
=============
	Starts playing the given sound.
*/
void SndPlaySound(enum E_Sound Sound);

/*
========
SndStop
========
	Stops a sound or bgm.
*/
void SndStop(enum E_Sound Sound);

/*
=============
SndSetVolume
=============
	Changes desired sound-s channel volume.
*/
void SndSetVolume(enum E_Sound Sound, float volume);

/*
=============
SndPlayMusic
=============
	Starts playing music.
*/
void SndPlayMusic(enum E_Sound Sound);

/*
==========
SndUpdate
==========
	Updates the sound system. Must be called once per frame.
*/
void SndUpdate(void);

#endif