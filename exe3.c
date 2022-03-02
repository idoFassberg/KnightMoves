#include "exe3.h"

pathTree findAllpossibleKnightpaths(chessPos* startingPosition) {

	pathTree res;
	chessPosArray*** pathOptionsMat;
	bool existMat[BOARD_SIZE][BOARD_SIZE];
	initializeExistMat(existMat); /* initialize all to FALSE */

	pathOptionsMat = validKnightMoves(); /* func from q1 */

	res.root = findAllpossibleKnightpathsHelper(existMat, pathOptionsMat, startingPosition);

	freePathOptionsMat(pathOptionsMat);

	return res;
}

void freePathOptionsMat(chessPosArray*** mat) {

	int i, j;

	for (i = 0; i < BOARD_SIZE; i++) {

		for (j = 0; j < BOARD_SIZE; j++)
			free(mat[i][j]->positions);
		
		free(mat[i]);
	}
	free(mat);
}

treeNode* findAllpossibleKnightpathsHelper(bool existMat[][BOARD_SIZE], chessPosArray*** pathOptionsMat, chessPos* startingPosition) {

	int col, row, i, size, rowE, colE;;
	chessPos* arr;
	treeNodeListCell* cell, * tail = NULL;

	treeNode* root = (treeNode*)malloc(sizeof(treeNode));
	checkTreeNodeAllocation(root);

	/* insert data to the new node */
	root->position[0] = startingPosition[0][0];
	root->position[1] = startingPosition[0][1];
	root->next_possible_positions = NULL;

	row = startingPosition[0][0] - 'A';
	col = (startingPosition[0][1] - '0') - 1; /* -1 for the differences between the way mat is built */

	existMat[row][col] = true; /* to know we allready been there */

	size = pathOptionsMat[row][col]->size; /* the numebr of the we can go to from current position */
	arr = pathOptionsMat[row][col]->positions; /* wich places can we go */

	for (i = 0; i < size; i++) {

		rowE = arr[i][0] - 'A';
		colE = arr[i][1] - '0' - 1;

		if (existMat[rowE][colE] == false) { /* false = new place we have not been to  */

			cell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
			treeNodeListCellAllocationCheck(cell);

			cell->next = NULL;

			if (root->next_possible_positions == NULL) /* cell for first child */
				root->next_possible_positions = cell;

			else
				tail->next = cell;

			tail = cell;
			cell->node = findAllpossibleKnightpathsHelper(existMat, pathOptionsMat, &arr[i]);

			existMat[rowE][colE] = false;
		}
	}

	return root;
}

void treeNodeListCellAllocationCheck(treeNodeListCell* cell) {

	if (cell == NULL) {

		printf("Memory Allocation Failure!");
		exit(1);
	}
}

void initializeExistMat(bool mat[][BOARD_SIZE]) {

	int i, j;

	for (i = 0; i < BOARD_SIZE; i++) {

		for (j = 0; j < BOARD_SIZE; j++)

			mat[i][j] = false;
	}
}

void checkTreeNodeAllocation(treeNode* node) {

	if (node == NULL) {

		printf("Memory Allocation Failure!");
		exit(1);
	}
}