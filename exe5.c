#include "exe5.h"

void checkFileOpen(FILE* fp) {

	if (fp == NULL) {

		printf("File Open Failure!");
		exit(1);
	}
}

BYTE makePosMask(char ch, int i) { /* gets a char and return the "compressed" mask */

	BYTE mask;

	if (isLetter(ch))
		mask = ch - 'A';

	else /* A number */
		mask = ch - '1';

	mask <<= i;

	return mask;
}

bool isLetter(char ch) {

	if (ch >= 'A' && ch <= 'Z')
		return true;
	else
		return false;
}

void saveListToBinFile(char* file_name, chessPosList* pos_list) {

	FILE* fp;
	short int countPos = 0;
	chessPosCell* currCell = pos_list->head;
	BYTE mask = 0, tmpMask, tmpMaskRight, tmpMaskLeft;
	int charCount = 0, countDivide = 0;

	int arr[8] = { 5,2,7,4,1,6,3,0 }; /* to make the mask by the amount of shifting in bits */

	fp = fopen(file_name, "wb"); /* write in binary */
	checkFileOpen(fp);

	fwrite(&countPos, sizeof(short int), 1, fp); /* initialize to 0 and change to true value at the end */

	if (currCell != NULL) {
		mask = makePosMask(currCell->position[0], 5); /* first value */
		charCount++;
	}

	while (currCell != NULL) {

		if ((charCount + 1) % 3 == 0) { /* identify every divided chars in bytes */

			if (countDivide % 3 == 0) { /* divide two bits to the left byte and one to the right */

				tmpMask = makePosMask(currCell->position[0], 0);
				tmpMaskLeft = tmpMask >> 1;
				tmpMaskRight = tmpMask << 7;
			}

			else if (countDivide % 3 == 1) { /* divide one bit to the left byte and two to the right */

				tmpMask = makePosMask(currCell->position[1], 0);
				tmpMaskLeft = tmpMask >> 2;
				tmpMaskRight = tmpMask << 6;
			}

			else { /* no bits should divide */

				fwrite(&mask, sizeof(BYTE), 1, fp);
				countDivide = charCount = mask = 0; /* initialize */
				continue;
			}

			countDivide++;
			charCount++;
			mask |= tmpMaskLeft;

			fwrite(&mask, sizeof(BYTE), 1, fp); /* write full current byte to the file */

			mask = tmpMaskRight;
		}

		else {

			mask |= makePosMask(currCell->position[charCount % 2], arr[charCount % 8]);
			charCount++;
		}

		if (charCount % 2 == 0) { /* move to next positions after one chessPos = two chars */

			countPos++;
			currCell = currCell->next;
		}

	}

	fwrite(&mask, sizeof(BYTE), 1, fp);

	rewind(fp); /* start of file */
	fwrite(&countPos, sizeof(short int), 1, fp); /* true value of countPos*/


	fclose(fp); /* cehck!!! */
}