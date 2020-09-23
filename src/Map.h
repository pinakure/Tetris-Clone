//
// MAP.h: MAP code, header file
//
#ifndef __MAP_H
#define __MAP_H

int MapInit(void);
void MapDraw(void);
void MapDeinit(void);
int MapTick(void);

int MapTest(int x, int y, int player);
int MapFindLines(int player);
void MapCut(int height, int player);
int MapTransferPiece(int player);
#endif