#ifndef EXE7
#define EXE7

#include "exe6.h"

void mainMenu();
void optionOne(chessPos pos);
bool isValidInput(chessPos pos);
char* scanFileName();
void checkAllocation(char* str);
void printMessages(int flag);
void printMainOptions();
void freeTree(pathTree* tr);
void freeTreeHelper(treeNode* root);
void freeAllAllocations(pathTree tr, chessPosList* lst, char* fileName, char* fileName2);

#endif