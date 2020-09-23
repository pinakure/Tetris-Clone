//
// Game.c: Game code
//
#include "Common.h"

T_Game Game[2];

void GameNew(int player)
{
	Game[player].Line = 0;
	Game[player].Level = 0;
	Game[player].Score = 0;
	Game[player].Status = GS_Playing;
	MapClear(player);	
}

int GameInit(void)
{
	int i;
	
	for(i=0; i<MAP_SIZE; i++)
	{
		Map1[i] = 0;
		Map2[i] = 0;
	}
	if(!PiecesInit())return 0;

	GameNew(PT_Player1);
	GameNew(PT_Player2);

	Game[PT_Player1].Status = GS_GameOver;
	Game[PT_Player2].Status = GS_GameOver;

	set_keyboard_rate(100, 100);

	return 1;
}

void GameDeinit(void)
{
	PiecesDeinit();
}


void GameDraw(void)
{
	PiecesDraw();
}

int GameTick(void)
{
	PiecesTick();
	return 0;
}