#ifndef EXE1
#define EXE1

#include "general.h"

chessPosArray*** validKnightMoves();
void checkAllocationChessPosMat(chessPosArray*** resMat);
void checkAllocationChessPosArr(chessPosArray** resArr);
void fillBoard(chessPosArray*** board);
void checkAllocationCell(chessPosArray* cell);
void fillCell(chessPosArray* cell, unsigned int row, unsigned int col);
void checkAllocationLocationArr(chessPos* arr);
unsigned int fillLocationArr(chessPos* arr, unsigned int row, unsigned int col);

#endif