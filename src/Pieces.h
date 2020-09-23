//
// Pieces.h: Pieces code, header file
//
#ifndef __PIECES_H
#define __PIECES_H

#define PIECE_WIDTH		3
#define PIECE_HEIGHT	3
#define PIECE_SIZE		(PIECE_WIDTH*PIECE_HEIGHT)
#define PIECE_FPS		1.0f

enum E_KeyNames {
	K_P1RotateLeft,
	K_P1RotateRight,
	K_P1MoveLeft,
	K_P1MoveRight,
	K_P1Drop,
	K_P2RotateLeft,
	K_P2RotateRight,
	K_P2MoveLeft,
	K_P2MoveRight,
	K_P2Drop,
	K_MAX
};

int KeyMap[K_MAX];

enum E_PieceTypes {
	PT_Player1,
	PT_Player2,
	PT_Block1,
	PT_Block2,
	PT_Z,
	PT_L,
	PT_I,
	PT_T,
	PT_U,
	PT_V,
	PT_L2,
	PT_S,
	PT_MAX,
	PT_Next1,
	PT_Next2
};

typedef struct S_Piece {
	int Data[PIECE_SIZE];
	int X;
	int Y;
	int Type;
} T_Piece;

extern T_Piece Pieces[PT_MAX+10];
extern BITMAP *PieceGfx[48];

int PiecesInit(void);
void PiecesDraw(void);
void PiecesDeinit(void);
int PiecesTick(void);
void MapClear(int player);
void PutPiece(BITMAP *b, int i, int x, int y);
#endif