#ifndef EXE5
#define EXE5
#include "exe4.h"

void checkFileOpen(FILE* fp);
BYTE makePosMask(char ch, int i);
bool isLetter(char ch);
void saveListToBinFile(char* file_name, chessPosList* pos_list);

#endif
