#ifndef EXE2
#define EXE2

#include "exe1.h"

void display(chessPosList* lst);
void buildBoard(int mat[][BOARD_SIZE + 1]);
void fillBoard2(chessPosList* lst, int mat[][BOARD_SIZE + 1]);
void removeFromLst(chessPosList* lst, chessPosCell* node, chessPosCell* prevNode);
void printBoard(int mat[][BOARD_SIZE + 1]);
void printPlusLine();
void fillNumbers(int mat[][BOARD_SIZE + 1]);
void fillLetters();
void gotoxy(int y, int x);
#endif
