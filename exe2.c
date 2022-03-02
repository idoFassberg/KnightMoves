#include "exe2.h"

void display(chessPosList* lst) {

	int mat[BOARD_SIZE + 1][BOARD_SIZE + 1]; /* +1 for the numbers and letterss above board */

	buildBoard(mat);
	fillBoard2(lst, mat); /* gets the list and fill the matrix */
	printBoard(mat);
}

void buildBoard(int mat[][BOARD_SIZE + 1]) {

	/* initialize the matrix with spaces */
	int i, j;

	for (i = 0; i < BOARD_SIZE + 1; i++) {
		for (j = 0; j < BOARD_SIZE + 1; j++) {

			mat[i][j] = 0;
		}
	}
}

void fillBoard2(chessPosList* lst, int mat[][BOARD_SIZE + 1]) {

	chessPosCell* curr = lst->head;
	chessPosCell* prev = NULL;
	int LstInd = 1;

	while (curr != NULL) {

		if (mat[curr->position[0] - 'A' + 1][curr->position[1] - '1' + 1] == 0) {

			mat[curr->position[0] - 'A' + 1][curr->position[1] - '1' + 1] = LstInd;
			LstInd++;
		}

		else {

			removeFromLst(lst, curr, prev);
		}
		prev = curr;
		curr = curr->next;
	}
}

void removeFromLst(chessPosList* lst, chessPosCell* node, chessPosCell* prevNode) {

	if (lst->head == NULL)
		return;

	/* at least one node */
	else if (lst->head == lst->tail)

		lst->head = lst->tail = NULL;

	/* at least two nodes */
	else if (lst->head == node)

		lst->head = node->next;

	else if (lst->tail == node) {

		lst->tail = prevNode;
		prevNode->next = NULL;
	}

	else { /* remove from middle */

		prevNode->next = node->next;
	}

	free(node);
}

void printBoard(int mat[][BOARD_SIZE + 1]) {

	int i, j;

	system("cls");

	fillNumbers(mat); /* fill the cols numbers above the table */

	for (i = 0; i < BOARD_SIZE + 1; i++) {
		printPlusLine();

		printf("\n");

		for (j = 0; j < BOARD_SIZE + 1 ; j++)
			printf("|%3d  ", mat[i][j]);

		printf("|");
		printf("\n");
	}
	printPlusLine();
	printf("\n");

	fillLetters(mat); /* fill the rows letters beside the table*/
	gotoxy(0, 14);
}

void printPlusLine() {

	int i;

	for (i = 0; i < BOARD_SIZE + 1; i++)

		printf("+-----");

	printf("+");
}

void fillNumbers(int mat[][BOARD_SIZE + 1]) {

	int i;

	for (i = 1; i < BOARD_SIZE + 1; i++)
		mat[0][i] = i;
}

void fillLetters() {

	int i, w;

	gotoxy(3, 1);
	printf("%c", ' ');

	for (i = 3, w = 0; w < BOARD_SIZE; i += 2, w++) {

		gotoxy(3, i);
		printf("%c", w + 'A');
	}
}

void gotoxy(int y, int x) {
	printf("\x1b[%d;%df", x + 1, y + 1);
}