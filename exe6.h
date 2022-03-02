#ifndef EXE6
#define EXE6

#include "exe5.h"

int checkAndDisplayPathFromFile(char* file_name);
char makeCharFromMask(BYTE mask, int move, int ind);
chessPosList createListFromFile(FILE* fp);
bool isValidListMoves(chessPosList lst, chessPosArray*** mat);
bool isValidMove(chessPos pos, chessPos* arr, int size);
bool isCoveringAllBoard(chessPosList lst);

#endif
