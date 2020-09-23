//
// Map.c: Map code
//
#include "Common.h"

int MapInit(void)
{

	return 1;
}

void MapDeinit(void)
{
}

int MapTransferPiece(int player)
{
	T_Piece *p;
	int x,y,c,f;
	int Line = FALSE;
	int OldLevel = 0;
	p = &Pieces[player];
	c = 0;
	Game[player].Score += 100;
	SndPlaySound(SND_PieceDrop);
			
	for(y=p->Y; y < p->Y + PIECE_HEIGHT; y++)
	{
		if(y >= 0) {
			for(x=p->X; x < p->X + PIECE_WIDTH; x++)
			{
				if(MapTest(x,y, player)==0){
					if(player == PT_Player1){
 						Map1[ (y*MAP_WIDTH)+x ] = p ->Data[c]*(1+(p->Type)/16);
					} else {
						Map2[ (y*MAP_WIDTH)+x ] = p ->Data[c]*(1+(p->Type)/16);
					}
				}
				c++;
			}
			f=MapFindLines(player);
			while(f!=-1)
			{
				MapCut(f, player);
				f=MapFindLines(player);				
				Game[player].Line++;
				OldLevel = Game[player].Level;
				Game[player].Level = Game[player].Line >> 3;
				if(Game[player].Level != OldLevel) {
					SndPlaySound(SND_LevelUp);
				}
				Game[player].Score += 1000;
				Line = TRUE;
			};
		} else {
			return 0;			
		}	
	}
	if(Line == TRUE){
		SndPlaySound(SND_Line);
	}
	return 1;
}


void MapCut(int height, int player)
{
	int x,y;

	switch(player) {
		case PT_Player1:
			for(y=height; y>=1; y--) {
				for(x=0; x<MAP_WIDTH; x++) {
					Map1[(y*MAP_WIDTH)+x] = Map1[((y-1)*MAP_WIDTH)+x] ;
				}
			}
			for(x=0; x<MAP_WIDTH; x++) {
				Map1[x] = 0;
			}
			break;
		case PT_Player2:
			for(y=height; y>=1; y--) {
				for(x=0; x<MAP_WIDTH; x++) {
					Map2[(y*MAP_WIDTH)+x] = Map1[((y-1)*MAP_WIDTH)+x] ;
				}
			}
			for(x=0; x<MAP_WIDTH; x++) {
				Map2[x] = 0;
			}
			break;

	}
}

int MapFindLines(int player)
{
	int x,y;
	int check;
	int *map;

	if(player == PT_Player1) {
		map = Map1;	
	} else {
		map = Map2;
	}	
	
	for(y=0;y<MAP_HEIGHT;y++) {
		check = 1;
		for(x=0;x<MAP_WIDTH;x++) {				
			if( map[(y*MAP_WIDTH)+x]==0) {
				check=0;
				break;
			}
		}
		if(check)
		{
			// TODO: Scroll down
			for(x=0;x<MAP_WIDTH;x++) {				
				map[(y*MAP_WIDTH)+x] = 0;
			}
			return y;
		}
	}
	return -1;
}



int MapTest(int x, int y, int player)
{
	switch(player){
		case 0:
			if(y<0)return 0;
			if(Map1[ (y*MAP_WIDTH)+x ]==0)return 0;	
			break;
		default:
			if(y<0)return 0;
			if(Map2[ (y*MAP_WIDTH)+x ]==0)return 0;	
			break;
	}
	return 1;
}


void MapClear(int player)
{
	int i;
	int *map;

	if(player == PT_Player1) {
		map = Map1;
	} else {
		map = Map2;
	}

	for(i=0; i<MAP_SIZE; i++) {
		map[i] = 0;
	}
	Game[player].Piecenew = 1; 
}


void MapDraw(void)
{
	int x,y, c;

	for(y=0; y<MAP_HEIGHT; y++) {
		for(x=0; x<MAP_WIDTH; x++) {
			c = Map1[(y*MAP_WIDTH)+x];
			if(c!=0) {
				c--;
				blit(PieceGfx[2+(c*16)], VideoBuffer, 0, 0, 8+(x*8), 24+(y*8), 8, 8);
			} else {
				blit(PieceGfx[0], VideoBuffer, 0, 0, 8+(x*8), 24+(y*8), 8, 8);
			}

			c = Map2[(y*MAP_WIDTH)+x];
			if(c!=0) {
				c--;
				blit(PieceGfx[3+(c*16)], VideoBuffer, 0, 0, 192+(x*8), 24+(y*8), 8, 8);
			} else {
				blit(PieceGfx[1], VideoBuffer, 0, 0, 192+(x*8), 24+(y*8), 8, 8);
			}
		}
	}

	if(Game[0].Status == GS_GameOver)
	{
		textprintf_centre_ex(VideoBuffer, font, 69, 108, Colors[C_RedH], -1, "Game Over");
		textprintf_centre_ex(VideoBuffer, font, 69, 126, Colors[C_RedH], -1, "Push 1 to start");
	}

	if(Game[1].Status == GS_GameOver)
	{
		textprintf_centre_ex(VideoBuffer, font, 253, 108, Colors[C_BlueH], -1, "Game Over");
		textprintf_centre_ex(VideoBuffer, font, 253, 126, Colors[C_BlueH], -1, "Push 2 to start");
	}
}

int MapTick(void)
{
	return 0;
}

