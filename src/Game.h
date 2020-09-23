//
// Game.h: Game code, header file
//
#ifndef __GAME_H
#define __GAME_H

enum E_GameStatus {
	GS_GameOver,
	GS_Playing
};
typedef struct S_Game {
	int Score;
	int Line;
	int Status;
	int Level;
	int Piecenew;
} T_Game;

extern T_Game Game[2];

#define MAP_WIDTH		15
#define MAP_HEIGHT		26
#define MAP_SIZE		(MAP_WIDTH*MAP_HEIGHT)

int Map1[MAP_SIZE];
int Map2[MAP_SIZE];

int GameInit(void);
void GameDraw(void);
void GameDeinit(void);
int GameTick(void);
void GameNew(int player);
#endif