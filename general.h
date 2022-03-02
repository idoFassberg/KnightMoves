#ifndef GENERAL
#define GENERAL
/*___________________________________________________________________________________*/
#define BOARD_SIZE 5
#define KNIGHT_MAX_MOVE 8

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <conio.h>

/*___________________________________________________________________________________*/
typedef char chessPos[2];

typedef struct _chessPosArray {
	unsigned int size; /* numbers of options for positions */
	chessPos* positions;
}chessPosArray;

typedef struct _chessPosCell {

	chessPos position;
	struct _chessPosCell* next;

}chessPosCell;

typedef struct _chessPosList {

	chessPosCell* head;
	chessPosCell* tail;

}chessPosList;

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {

	chessPos position;
	treeNodeListCell* next_possible_positions;
}treeNode;

typedef struct _treeNodeListCell {

	treeNode* node;
	struct _treeNodeListCell* next;
}treeNodeListCell;

typedef struct _pathTree {

	treeNode* root;
}pathTree;

typedef unsigned char BYTE;
/*___________________________________________________________________________________*/
#endif
