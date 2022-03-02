#include "exe6.h"

int checkAndDisplayPathFromFile(char* file_name) {

	chessPosArray*** validKnightMovesMat;
	chessPosList lst;
	FILE* fp = fopen(file_name, "rb");
	
	if (fp == NULL) /* check file open */
		return -1;
	
	lst = createListFromFile(fp);

	validKnightMovesMat = validKnightMoves();

	if (!isValidListMoves(lst, validKnightMovesMat)) {

		freePathOptionsMat(validKnightMovesMat);
		return 1; /* there is an invalid move */
	}

	freePathOptionsMat(validKnightMovesMat);

	display(&lst); /* func from question 2 */

	if (isCoveringAllBoard(lst))
		return 2; /* list of path is covering all chess board */
	else
		return 3; /* list of path is NOT covering all chess board */

	fclose(fp);
}

bool isCoveringAllBoard(chessPosList lst) {

	chessPosCell* curr = lst.head;
	int counter = 0;

	while (curr != NULL) {

		counter++;
		curr = curr->next;
	}

	if (counter == BOARD_SIZE * BOARD_SIZE)
		return true;
	else
		return false;
}

bool isValidListMoves(chessPosList lst, chessPosArray*** mat) {

	chessPosCell* curr = lst.head;
	int row, col;

	while (curr != NULL) {

		row = curr->position[0] - 'A';
		col = curr->position[1] - '1';

		if (curr->next != NULL) {

			if (!isValidMove(curr->next->position, mat[row][col]->positions, mat[row][col]->size))
				return false; /* move is NOT valid */
		}
		curr = curr->next;
	}
	return true; /* all moves are valid */
}

bool isValidMove(chessPos pos, chessPos* arr, int size) {

	int i;

	for (i = 0; i < size; i++) {

		if ((pos[0] == arr[i][0]) && (pos[1] == arr[i][1]))
			return true;
	}
	return false;
}

chessPosList createListFromFile(FILE* fp) {

	short int charCount = 0, numOfPositions, countDivide = 0, posCount = 0;
	chessPosList lst;
	chessPos pos;
	BYTE mask = 0, maskLeft, maskRight;
	makeEmptyList(&lst);
	int arr[8] = { 5,2,7,4,1,6,3,0 };

	fread(&numOfPositions, sizeof(short int), 1, fp);

	fread(&mask, sizeof(BYTE), 1, fp);

	while (posCount < numOfPositions) {

		if ((charCount + 1) % 3 == 0) { /* identify every divided chars in bytes */

			if (countDivide % 3 == 0) { /* divide two bits to the left byte and one to the right */

				maskLeft = mask << 1;
				fread(&mask, sizeof(BYTE), 1, fp);
				maskRight = mask >> 7;
				maskLeft |= maskRight;
				mask <<= 1;
				mask >>= 1;
			}

			else if (countDivide % 3 == 1) { /* divide one bit to the left byte and two to the right */

				maskLeft = mask << 2;
				fread(&mask, sizeof(BYTE), 1, fp);
				maskRight = mask >> 6;
				maskLeft |= maskRight;
				mask <<= 2;
				mask >>= 2;
			}

			else { /* no bits should divide */

				fread(&mask, sizeof(BYTE), 1, fp);
				charCount = countDivide = 0;
				continue;
			}

			pos[charCount % 2] = makeCharFromMask(maskLeft, 0, charCount);
			charCount++;
			countDivide++;
		}
		
		else {

			pos[charCount % 2] = makeCharFromMask(mask, arr[charCount % 8], charCount);
			mask <<= (8 - arr[charCount % 8]);
			mask >>= (8 - arr[charCount % 8]);
			charCount++;
		}

		if (charCount % 2 == 0) {

			insertDataToEndList(&lst, pos);
			posCount++;
		}
	}
	return lst;
}

char makeCharFromMask(BYTE mask, int move, int ind) { /* get a mask and return the right char */

	mask >>= move;

	if (ind % 2 == 0) /* in this case it's a char */
		mask = mask + 'A';

	else /* A number*/
		mask = mask + '1';

	return mask;
}