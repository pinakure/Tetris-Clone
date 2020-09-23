//
// Pieces.c: Pieces code
//
#include "Common.h"

int KeyMap[K_MAX] = {	KEY_UP, 
						KEY_DOWN, 
						KEY_LEFT, 
						KEY_RIGHT,
						KEY_SPACE,
						KEY_W, 
						KEY_S, 
						KEY_A, 
						KEY_D,
						KEY_X };

static int PieceNew[2]  = {1, 1};
static float IncFrame[2]= {0, 0};
static int RotateNow[2] = {TRUE, TRUE};

static int PieceForceFall[2]= {0, 0};

const int Piece_b[PIECE_SIZE]= {  0,0,0,
				 				  0,1,0,
			 					  0,0,0};

const int Piece_B[PIECE_SIZE]= {	1,1,1,
									1,1,1,
									1,1,1};

const int Piece_L[PIECE_SIZE] = {	0,1,0,
									0,1,0,
									0,1,1};

const int Piece_L2[PIECE_SIZE] = {	0,1,0,
									0,1,0,
									1,1,0};

const int Piece_Z[PIECE_SIZE] = {	1,0,0,
									1,1,0,
									0,1,0};

const int Piece_S[PIECE_SIZE] = {	0,0,1,
									0,1,1,
									0,1,0};

const int Piece_I[PIECE_SIZE]= {	0,1,0,
									0,1,0,
									0,1,0};

const int Piece_T[PIECE_SIZE]= {	0,0,0,
									1,1,1,
									0,1,0};

const int Piece_U[PIECE_SIZE]= {	1,0,1,
									1,1,1,
									0,0,0};

const int Piece_V[PIECE_SIZE]= {	1,0,1,
									1,1,1,
									0,1,0};

T_Piece Pieces[PT_MAX+10];
BITMAP *PieceGfx[16*3];


int PiecesInit(void)
{
	char *str;	
	BITMAP *b;
	int i, r;

	srand(time(NULL));
	str = GetStaticChar1024();

	strcpy(str, GameDir);
	
	strcat(str, "gfx/blocks.bmp");
	
	b = load_bitmap(str, NULL);	
	
	if(!b) {		
		alert("Can't load", str, NULL, "OK", NULL, 0, 0);
		return 0;
	}

	for(r=0;r<3;r++) {
		for(i=0;i<16;i++) {
			PieceGfx[(r*16)+i]=create_bitmap(8, 8);
			blit(b, PieceGfx[(r*16)+i], i*8, r*8, 0, 0, 8, 8);
		}	
	}
	destroy_bitmap(b);

	//Proceed to create the pieces
	memcpy(Pieces[PT_Block1].Data, Piece_b, PIECE_SIZE*sizeof(int));
	memcpy(Pieces[PT_Block2].Data, Piece_B, PIECE_SIZE*sizeof(int));
	memcpy(Pieces[PT_Z].Data, Piece_Z, PIECE_SIZE*sizeof(int));
	memcpy(Pieces[PT_L].Data, Piece_L, PIECE_SIZE*sizeof(int));
	memcpy(Pieces[PT_I].Data, Piece_I, PIECE_SIZE*sizeof(int));
	memcpy(Pieces[PT_T].Data, Piece_T, PIECE_SIZE*sizeof(int));
	memcpy(Pieces[PT_U].Data, Piece_U, PIECE_SIZE*sizeof(int));
	memcpy(Pieces[PT_V].Data, Piece_V, PIECE_SIZE*sizeof(int));
	memcpy(Pieces[PT_L2].Data, Piece_L2, PIECE_SIZE*sizeof(int));
	memcpy(Pieces[PT_S].Data, Piece_S, PIECE_SIZE*sizeof(int));
	return 1;
}



void PiecesDeinit(void)
{
	int i;
	for(i=0;i<3*16;i++) {
		destroy_bitmap(PieceGfx[i]);
	}
}

static int GetBottom(int player)
{
	T_Piece *p;

	p = &Pieces[player];
	
	if(p ->Data[6] == 1)return 2;
	if(p ->Data[7] == 1)return 2;
	if(p ->Data[8] == 1)return 2;
	
	if(p ->Data[3] == 1)return 1;
	if(p ->Data[4] == 1)return 1;
	if(p ->Data[5] == 1)return 1;
	
	if(p ->Data[0] == 1)return 0;
	if(p ->Data[1] == 1)return 0;
	if(p ->Data[2] == 1)return 0;

	return 0;
}
static int GetTop(int player)
{
	T_Piece *p;

	p = &Pieces[player];
	
	if(p ->Data[0] == 1)return 0;
	if(p ->Data[1] == 1)return 0;
	if(p ->Data[2] == 1)return 0;

	if(p ->Data[3] == 1)return 1;
	if(p ->Data[4] == 1)return 1;
	if(p ->Data[5] == 1)return 1;

	if(p ->Data[6] == 1)return 2;
	if(p ->Data[7] == 1)return 2;
	if(p ->Data[8] == 1)return 2;

	return 0;
}
static int GetLeft(int player)
{
	T_Piece *p;

	p = &Pieces[player];
	
	if(p ->Data[0] == 1)return 0;
	if(p ->Data[3] == 1)return 0;
	if(p ->Data[6] == 1)return 0;
	
	if(p ->Data[1] == 1)return 1;
	if(p ->Data[4] == 1)return 1;
	if(p ->Data[7] == 1)return 1;
	
	if(p ->Data[2] == 1)return 2;
	if(p ->Data[5] == 1)return 2;
	if(p ->Data[8] == 1)return 2;

	return 0;
}
static int GetRight(int player)
{
	T_Piece *p;

	p = &Pieces[player];
	
	if(p ->Data[2] == 1)return 2;
	if(p ->Data[5] == 1)return 2;
	if(p ->Data[8] == 1)return 2;
	
	if(p ->Data[1] == 1)return 1;
	if(p ->Data[4] == 1)return 1;
	if(p ->Data[7] == 1)return 1;
	
	if(p ->Data[0] == 1)return 0;
	if(p ->Data[3] == 1)return 0;
	if(p ->Data[6] == 1)return 0;
	
	return 0;
}

static void PieceMove(int dir, int player)
{
	T_Piece *p;
	int x,y;

	p = &Pieces[player];

	switch(dir)
	{
		case -1:
			for(x=0; x<PIECE_WIDTH; x++) {
				for(y=0; y<PIECE_HEIGHT; y++) {
					if(MapTest(p->X+(x-1), p->Y+y, player)==1) {
						if(p->Data[(y*PIECE_HEIGHT)+x]==1) {
							return;
						}
					}
				}		
			}		
			
			if( ((p -> X)+GetLeft(player)) > 0 ){
				(p -> X)--;				
			}			
			break;
		case 1:
			for(x=PIECE_WIDTH-1; x>=0; x--) {
				for(y=0; y<PIECE_HEIGHT; y++) {
					if(MapTest(p->X+(x+1), p->Y+y, player)==1) {
						if(p->Data[(y*PIECE_HEIGHT)+x]==1) {
							return;
						}
					}
				}		
			}		
			
			if( ((p -> X)+GetRight(player)+1) < MAP_WIDTH ){
				(p -> X)++;
			}
			break;
	}
}

static void PieceRotate(int dir, int player)
{
	T_Piece *src;
	T_Piece dst;
	int i, ri;
	int wx, wy, rx, ry;
	
	src = &Pieces[player];
	
	
	switch(dir) {
		case -1:
			for(i=0; i<PIECE_SIZE; i++) {
				ri = (PIECE_SIZE-1) - i;

				ry = i / PIECE_WIDTH;
				rx = i % PIECE_WIDTH;
				
				wx = i / PIECE_WIDTH;
				wy = ri % PIECE_WIDTH;;
				dst.Data[(wy*PIECE_WIDTH)+wx] = src -> Data[(ry*PIECE_WIDTH)+rx];
			}	
			break;
		case 1:
			for(i=0; i<PIECE_SIZE; i++) {
				ri = (PIECE_SIZE-1) - i;

				ry = i / PIECE_WIDTH;
				rx = i % PIECE_WIDTH;
				
				wx = ri / PIECE_WIDTH;
				wy = i % PIECE_WIDTH;;
				dst.Data[(wy*PIECE_WIDTH)+wx] = src -> Data[(ry*PIECE_WIDTH)+rx];
			}
			break;
	}

	//Check the rotated piece doesn't collide with the map, if so, move it.	
	rx = src->X;
	ry = src->Y;

	for(i =0; i<PIECE_SIZE; i++) {
		if(dst.Data[i]==1)
		{
			if(i/PIECE_WIDTH == PIECE_HEIGHT-1){
				if(ry + (PIECE_HEIGHT-1) > MAP_HEIGHT-1){ry--;break;}
			}

			if(i%PIECE_WIDTH == PIECE_WIDTH-1){
				if(rx + (PIECE_WIDTH-1) > MAP_WIDTH-1){rx--;break;}				
			} 
			if(i%PIECE_WIDTH == 0){
				if(rx < 0){rx++;break;}				
			} 
		}
	}
	// Check the rotated piece doen't collide with another piece on the map
	for(i =0; i<PIECE_SIZE; i++) {		
		if(dst.Data[i])
		{
			if(MapTest(rx + (i%PIECE_WIDTH), ry + (i/PIECE_WIDTH), player)!=0) {
				return;
			}
		}
	}
	memcpy(src -> Data, dst.Data, PIECE_SIZE*sizeof(int));
	src->X = rx;
	src->Y = ry;	
}

static void PieceSpawn(int player)
{
	static int r=0;
	//Get previously stored 'Next piece'
	memcpy(Pieces[player].Data, Pieces[PT_Next1+player].Data, PIECE_SIZE*sizeof(int));	
	
	Pieces[player].Type = Pieces[PT_Next1 + player].Type;

	while((rand()%5) > 0)
	{
		if(rand()%2)PieceRotate(1, player);
	}

	if(GetRight(player)-GetLeft(player) > 0)
	{
		Pieces[player].X = ( (Pieces[player].X + rand())%((MAP_WIDTH-1) - (GetRight(player)-GetLeft(player))));
	} else {
		Pieces[player].X = ( rand()%(MAP_WIDTH))-1;
	}
	Pieces[player].Y = -PIECE_HEIGHT;	
	
	//Set 'Next piece'
	r  = 2+((r+rand())%(PT_MAX-2));
	Pieces[PT_Next1 + player].Type = (rand()%3)*16;
	memcpy(Pieces[PT_Next1+player].Data, Pieces[r].Data, PIECE_SIZE*sizeof(int));	
	
	Game[player].Piecenew = 0;
}

static void PieceFall(int player)
{	
	T_Piece *p;
	int x,y;

	p = &Pieces[player];
	
	if( (p -> Y + GetBottom(player) ) <= 24)
	{
		// Check if there is stuff on the map below us before moving
		for(y=0; y<PIECE_HEIGHT; y++) {			
			for(x=0; x<PIECE_WIDTH; x++) {
				if(MapTest(p->X+x, p->Y+y+1, player)==1) {
					if(p->Data[(y*PIECE_HEIGHT)+x]==1) {
						if(!MapTransferPiece(player))
						{
							/*GameOver*/
							GameNew(player);
							SndPlaySound(SND_GameOver);
							Game[player].Status = GS_GameOver;
						} else {
							PieceSpawn(player);
						}
						
						return;
					}
				}
			}		
		}		
		p -> Y++;		
	} else {
		MapTransferPiece(player);
		PieceSpawn(player);
	}
}

void PieceDraw(int player)
{
	int x, y;
	T_Piece *pp;

	pp = &Pieces[player];

	switch(player) {
		case PT_Next1:
			for(y=0; y<PIECE_HEIGHT; y++) {
				for(x=0; x<PIECE_WIDTH; x++) {			
					if( (pp -> Data[(y*PIECE_WIDTH)+x]) > 0){
						blit(PieceGfx[2+Pieces[player].Type], VideoBuffer, 0, 0, 136+(x *8), (y *8),8, 8);						
					}
				}
			}
			break;
		case PT_Next2:
			for(y=0; y<PIECE_HEIGHT; y++) {
				for(x=0; x<PIECE_WIDTH; x++) {			
					if( (pp -> Data[(y*PIECE_WIDTH)+x]) > 0){
						blit(PieceGfx[3+Pieces[player].Type], VideoBuffer, 0, 0, 160+(x *8), (y *8),8, 8);						
					}
				}
			}
			break;
		case PT_Player1:
			for(y=0; y<PIECE_HEIGHT; y++) {
				for(x=0; x<PIECE_WIDTH; x++) {			
					if( (pp -> Data[(y*PIECE_WIDTH)+x]) > 0){
						if(pp->Y+y >= 0){
							blit(PieceGfx[2+Pieces[player].Type], VideoBuffer, 0, 0, 
														   8+(((pp -> X) + x )*8), 24+(((pp -> Y) + y )*8),
														   8, 8);
						}else PieceForceFall[player]=0;
					}
				}
			}
			break;
		case PT_Player2:
			for(y=0; y<PIECE_HEIGHT; y++) {
				for(x=0; x<PIECE_WIDTH; x++) {			
					if( (pp -> Data[(y*PIECE_WIDTH)+x]) > 0){
						if(pp->Y+y >= 0){
							blit(PieceGfx[3+Pieces[player].Type], VideoBuffer, 0, 0, 
														   192+(((pp -> X) + x )*8), 24+(((pp -> Y) + y )*8),
														   8, 8);
						}else PieceForceFall[player]=0;
					}
				}
			}
			break;
	}
	
}


void PiecesDraw(void)
{
	MapDraw();
	PieceDraw(PT_Player1);
	PieceDraw(PT_Player2);
	PieceDraw(PT_Next1);
	PieceDraw(PT_Next2);	
}

static int Rotating[2];

static void HandleKey(int k)
{
	PieceForceFall[0] = 0;
	PieceForceFall[1] = 0;
	
	
	switch(k) {
		case KEY_1:
			if(Game[PT_Player1].Status == GS_GameOver){
				Game[PT_Player1].Status = GS_Playing;
				PieceNew[PT_Player1] = 1;
				SndPlaySound(SND_GameStart);
			}
			break;
		case KEY_UP:
			Rotating[PT_Player1] = TRUE;
			if(RotateNow[PT_Player1] == TRUE){
				SndPlaySound(SND_Rotate);
				PieceRotate(-1, PT_Player1);
				RotateNow[PT_Player1] = FALSE;
			}
			break;
		case KEY_DOWN:
			Rotating[PT_Player1] = TRUE;
			if(RotateNow[PT_Player1] == TRUE){
				SndPlaySound(SND_Rotate);
				PieceRotate(1, PT_Player1);
				RotateNow[PT_Player1] = FALSE;
			}
			break;	
	}
		 if(key[KEY_LEFT])PieceMove(-1, PT_Player1);
	else if(key[KEY_RIGHT])PieceMove(1, PT_Player1);
	
	switch(k) {
		case KEY_2:
			if(Game[PT_Player2].Status == GS_GameOver){
				Game[PT_Player2].Status = GS_Playing;
				PieceNew[PT_Player2] = 1;
				SndPlaySound(SND_GameStart);
			}
			break;
		case KEY_W:
			Rotating[PT_Player2] = TRUE;
			SndPlaySound(SND_Rotate);
			PieceRotate(-1, PT_Player2);
			break;
		case KEY_S:
			Rotating[PT_Player1] = TRUE;
			SndPlaySound(SND_Rotate);
			PieceRotate(1, PT_Player2);
			break;	
	}

		 if(key[KEY_A])PieceMove(-1, PT_Player2);
	else if(key[KEY_D])PieceMove(1, PT_Player2);
	
	
}

static float IncRotate[2];

static void PieceProcess(int player)
{
	IncRotate[player] -= TimeDT;		
	
	if(IncRotate[player] <= 0){
		RotateNow[player] = TRUE;
		IncRotate[player] = 1 / 2.0f;
	}

	if(Game[player].Status == GS_Playing) {
		IncFrame[player] -= TimeDT;	
		if(IncFrame[player] <= 0.0f) {
			IncFrame[player] = 1 / (( ( (float)Game[player].Level)+1.0f)*PIECE_FPS);
			if(!PieceForceFall[player]) {	
				PieceFall(player);
			}		
		}

		if(key[KEY_X])	{
			PieceForceFall[1] = 1;
		} else PieceForceFall[1] = 0;
		if(key[KEY_SPACE])	{
			PieceForceFall[0] = 1;
		} else PieceForceFall[0] = 0;

	
	
		if(PieceForceFall[player]) {
			PieceFall(player);
			if(Game[player].Status==GS_Playing)
			Game[player].Score++;
		}
		
		if(Game[player].Piecenew)
		{
			PieceSpawn(player);
			PieceSpawn(player);		
			PieceForceFall[player] = 0;
		}	
	}
}

int PiecesTick(void)
{
	PieceProcess(PT_Player1);
	PieceProcess(PT_Player2);

	Rotating[PT_Player1] = FALSE;
	Rotating[PT_Player2] = FALSE;
	if(keypressed())
	{
		HandleKey(readkey() >> 8);
	}
	return 0;
}