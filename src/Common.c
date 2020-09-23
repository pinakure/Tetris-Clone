/*
Common.c: M4GeekTech common routine kit 
*/

#include "Common.h"

char *GetStaticChar1024(void)
{
	static char str[1024];

	str[0] = 0;
	return str;
}

/* OPTION SAVELOAD FUNCTIONS */
int SaveOptions(void)
{
	FILE *fp;
	char *str;
	int i, len;

	str = GetStaticChar1024();
	strcpy(str, GameDir);
	strcat(str, "config.dat");

	fp = fopen(str, "wb");
	if(!fp) {
		alert("Can't open", str, NULL, "OK", NULL, 0, 0);
		return 0;
	}

	fwrite(Options, sizeof(int), OPT_MAX, fp);

#ifdef JUNK_CFG
	len = (rand() % 0xCAFE) + 0x1000;
	for(i=0; i<len; i++) {
		fputc(rand() % 0xFF, fp);
	}
#endif

	fclose(fp);
	return 1;
}

void NewOptions(void)
{
	Options[OPT_Music]		= 1;
	Options[OPT_Cheats]		= 0;
	Options[OPT_ColorDepth]	= 16;
	Options[OPT_Fullscreen] = 0;
	Options[OPT_Physics]    = 0;
	Options[OPT_Powerups]   = 1;
	Options[OPT_Sound]	    = 1;
	Options[OPT_TripleBuffer]=0;
	Options[OPT_VideoScale] = 1;
	Options[OPT_VSync]		= 0;	
}

int LoadOptions(void)
{
	FILE *fp;
	char *str;

	str = GetStaticChar1024();
	strcpy(str, GameDir);
	strcat(str, "config.dat");

	fp = fopen(str, "rb");
	if(!fp) {
		NewOptions();
		return 1;
	}
	
	fread(Options, sizeof(int), OPT_MAX, fp);
	
	fclose(fp);
	return 1;
}
/* END OF OPTION SAVELOAD FUNCTIONS */