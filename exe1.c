#include "exe1.h"

chessPosArray*** validKnightMoves() {

	int ind;
	chessPosArray*** chessBoard;
	chessBoard = (chessPosArray***)malloc(BOARD_SIZE * sizeof(chessPosArray**));
	checkAllocationChessPosMat(chessBoard);

	for (ind = 0; ind < BOARD_SIZE; ind++) {

		chessBoard[ind] = (chessPosArray**)malloc(BOARD_SIZE * sizeof(chessPosArray*));
		checkAllocationChessPosArr(chessBoard[ind]);
	}

	fillBoard(chessBoard);

	return chessBoard;
}

void checkAllocationChessPosMat(chessPosArray*** resMat) {

	if (resMat == NULL) {
		printf("Memory Allocation Failure!");
		exit(1);
	}
}

void checkAllocationChessPosArr(chessPosArray** resArr) {

	if (resArr == NULL) {
		printf("Memory Allocation Failure!");
		exit(1);
	}
}

void fillBoard(chessPosArray*** board) {

	unsigned int row, col;

	for (row = 0; row < BOARD_SIZE; row++) {

		for (col = 0; col < BOARD_SIZE; col++) {

			board[row][col] = (chessPosArray*)malloc(sizeof(chessPosArray));
			checkAllocationCell(board[row][col]);

			fillCell(board[row][col], row, col);
		}
	}
}

void checkAllocationCell(chessPosArray* cell) {

	if (cell == NULL) {
		printf("Memory Allocation Failure!");
		exit(1);
	}
}

void fillCell(chessPosArray* cell, unsigned int row, unsigned int col) {

	chessPos* locationArr;
	locationArr = (chessPos*)malloc(KNIGHT_MAX_MOVE * sizeof(chessPos));
	checkAllocationLocationArr(locationArr);

	cell->size = fillLocationArr(locationArr, row, col);

	if (cell->size == 0) {
		free(locationArr);
		locationArr = NULL;
	}

	else if (cell->size < KNIGHT_MAX_MOVE) {

		locationArr = (chessPos*)realloc(locationArr, (cell->size) * sizeof(chessPos));
		checkAllocationLocationArr(locationArr);
	}

	cell->positions = locationArr;
}

void checkAllocationLocationArr(chessPos* arr) {

	if (arr == NULL) {
		printf("Memory Allocation Failure!");
		exit(1);
	}
}

unsigned int fillLocationArr(chessPos* arr, unsigned int row, unsigned int col) { /* test 2*/

	unsigned int logSize = 0;

	if (row >= 2 && col <= BOARD_SIZE - 2) { /* up-up-right */
		arr[logSize][0] = (row - 2) + 'A';
		arr[logSize][1] = ((col + 1) + 1) + '0';
		logSize++;
	}

	if (row >= 1 && col <= BOARD_SIZE - 3) { /* up-right-right */
		arr[logSize][0] = (row - 1) + 'A';
		arr[logSize][1] = ((col + 2) + 1) + '0';
		logSize++;
	}

	if (row <= BOARD_SIZE - 2 && col <= BOARD_SIZE - 3) { /* down-right-right */
		arr[logSize][0] = (row + 1) + 'A';
		arr[logSize][1] = ((col + 2) + 1) + '0';
		logSize++;
	}

	if (row <= BOARD_SIZE - 3 && col <= BOARD_SIZE - 2) { /* down-down-right */
		arr[logSize][0] = (row + 2) + 'A';
		arr[logSize][1] = ((col + 1) + 1) + '0';
		logSize++;
	}

	if (row <= BOARD_SIZE - 3 && col >= 1) { /* down-down-left */
		arr[logSize][0] = (row + 2) + 'A';
		arr[logSize][1] = ((col - 1) + 1) + '0';
		logSize++;
	}

	if (row <= BOARD_SIZE - 2 && col >= 2) { /* down-left-left */
		arr[logSize][0] = (row + 1) + 'A';
		arr[logSize][1] = ((col - 2) + 1) + '0';
		logSize++;
	}

	if (row >= 1 && col >= 2) { /* up-left-left */
		arr[logSize][0] = (row - 1) + 'A';
		arr[logSize][1] = ((col - 2) + 1) + '0';
		logSize++;
	}

	if (row >= 2 && col >= 1) { /* up-up-left */
		arr[logSize][0] = (row - 2) + 'A';
		arr[logSize][1] = ((col - 1) + 1) + '0';
		logSize++;
	}

	return logSize;
}