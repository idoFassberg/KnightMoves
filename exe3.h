#ifndef EXE3
#define EXE3

#include "exe2.h"

pathTree findAllpossibleKnightpaths(chessPos* startingPosition);
treeNode* findAllpossibleKnightpathsHelper(bool existMat[][BOARD_SIZE], chessPosArray*** pathOptionsMat, chessPos* startingPosition);
void initializeExistMat(bool mat[][BOARD_SIZE]);
void checkTreeNodeAllocation(treeNode* node);
void treeNodeListCellAllocationCheck(treeNodeListCell* cell);
void freePathOptionsMat(chessPosArray*** mat);

#endif
