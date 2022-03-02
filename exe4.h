#ifndef EXE4
#define EXE4

#include "exe3.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
void findKnightPathCoveringAllBoardHelper(treeNode* root, int* listLen, bool* flag, chessPosList* lst);
void insertNodeToEndList(chessPosList* lst, chessPosCell* curr);
void insertDataToEndList(chessPosList* lst, chessPos data);
void deleteFromList(chessPosList* lst, chessPosCell* node);
bool isEmptyList(chessPosList* lst);
chessPosCell* createNewChessPosCell(chessPos data, chessPosCell* next);
void makeEmptyList(chessPosList* lst);
void checkAllocationList(chessPosList* lst);
void myFree_chessPosList(chessPosList* lst);

#endif
