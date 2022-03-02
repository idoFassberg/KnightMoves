#include "exe7.h"

void mainMenu() {

	int choice, q6;
	bool isOneActivated, isTwoActivated, isThreeActivated, isFourActivated, isFiveActivated;
	isOneActivated = isTwoActivated = isThreeActivated = isFourActivated = isFiveActivated = false;
	char* fileName = NULL, * fileName2 = NULL;
	chessPos pos;
	pathTree tr;
	chessPosList* lst = NULL;
	tr.root = NULL;

	while (true) { /* work until user exit (option 6) */

		printMainOptions();

		scanf("%d", &choice);
		getchar();
		
		switch (choice) {

		case 1:
			optionOne(pos);
			isOneActivated = true;
			break;

		case 2:

			if (!isOneActivated) {

				printf("Position is missing\n");
				optionOne(pos);
				isOneActivated = true;
			}

			//func from q3
			tr = findAllpossibleKnightpaths(&pos);
			isTwoActivated = true;

			break;

		case 3:

			if (!isTwoActivated) { /* need to build a tree */

				if (!isOneActivated) {

					printf("Position is missing\n");
					optionOne(pos);
					isOneActivated = true;
				}

				//func from q3
				tr = findAllpossibleKnightpaths(&pos);
				isTwoActivated = true;
			}
			//func from q4
			lst = findKnightPathCoveringAllBoard(&tr);
			isThreeActivated = true;

			if (lst == NULL)
				printf("There is no path covering all board\n");

			break;

		case 4:

			printf("Please enter a new file name:\n");
			fileName = scanFileName();

			if (!isThreeActivated) {

				if (!isTwoActivated) { /* need to build a tree */

					if (!isOneActivated) {

						printf("Position is missing\n");
						optionOne(pos);
						isOneActivated = true;
					}

					//func from q3
					tr = findAllpossibleKnightpaths(&pos);
					isTwoActivated = true;
				}

				//func from q4
				lst = findKnightPathCoveringAllBoard(&tr);
				isThreeActivated = true;

				if (lst == NULL)
					printf("There is no path covering all board\n");
			}

			//func from q5
			saveListToBinFile(fileName, lst);

			break;

		case 5:

			printf("Please enter an existing file name:\n");
			fileName2 = scanFileName();

			/*func from q6 */
			q6 = checkAndDisplayPathFromFile(fileName2);
			printMessages(q6);

			break;

		case 6:
			freeAllAllocations(tr, lst, fileName, fileName2);
			exit(0);
			break;

		default:
			printf("Unvalid choice. Please try again!\n");
			break;
		}
	}
}

void freeAllAllocations(pathTree tr, chessPosList* lst, char* fileName, char* fileName2) {

	if (fileName != NULL)
		free(fileName);

	if (fileName2 != NULL)
		free(fileName2);

	if (lst != NULL)
		myFree_chessPosList(lst);

	if (tr.root != NULL)
		freeTree(&tr);
}

void freeTree(pathTree* tr){

	freeTreeHelper(tr->root);
}

void freeTreeHelper(treeNode* root){

	if (root == NULL)
		return;

	if (root->next_possible_positions == NULL) /* if the root doesn't have any sons*/
		free(root);

	else{  /* meaning the root has at least one son*/

		if (root->next_possible_positions->node != NULL)
			freeTreeHelper(root->next_possible_positions->node);

		if (root->next_possible_positions->next != NULL){ /* if the root has a brother*/

			if (root->next_possible_positions->next->node)
				freeTreeHelper(root->next_possible_positions->next->node); /* free brother */
		}
	}
}

void optionOne(chessPos pos) {

	int tmpNum;

	while (true) {

		printf("Please enter position. Upper letter between A - H and a number between 1 - 8:\n");
		scanf("%c%d", &pos[0], &tmpNum);
		pos[1] = tmpNum + '0';

		if (isValidInput(pos))
			break;

		else
			printf("Invalid Input. Please try again!\n");
	}
}

//void optionOne(chessPos pos) {
//
//	int tmpNum;
//	char ch;
//	while (true) {
//		//ch = getchar();
//		printf("Please enter position. Upper letter between A - H and a number between 1 - 8:\n");
//		
//		scanf("%c%c", &pos[0], &pos[1]);
//		ch = getchar();
//
//		if (ch != '\n')
//			printf("Invalid Input. Please try again!\n");
//		else {
//
//			if (isValidInput(pos))
//				break;
//			else
//				printf("Invalid Input. Please try again!\n");
//		}
//	}
//}

bool isValidInput(chessPos pos) {

	if (pos[0] >= 'A' && pos[0] <= 'H' && pos[1] >= '1' && pos[1] <= '8')
		return true;

	else
		return false;
}

char* scanFileName() {

	int sizeL = 0, sizeP = 1;
	bool endOfInput = false;
	char* res = (char*)malloc(sizeP * sizeof(char));
	checkAllocation(res);
	char ch;

	getchar();

	while (!endOfInput) {

		if (sizeL == sizeP) {

			sizeP *= 2;
			res = (char*)realloc(res, sizeP * sizeof(char));
			checkAllocation(res);
		}

		ch = getchar();

		if (ch == '\n') {
			endOfInput = true;
			continue;
		}

		res[sizeL] = ch;

		sizeL++;
	}

	res[sizeL] = '\0';

	if (sizeL < sizeP) {

		res = (char*)realloc(res, (sizeL + 1) * sizeof(char));
		checkAllocation(res);
	}

	return res;
}

void checkAllocation(char* str) {

	if (str == NULL) {

		printf("Memory Allocation Failure!");
		exit(1);
	}
}

void printMessages(int flag) {

	if (flag == 1)
		printf("The list does NOT contain a legal path for a knight.\n");

	else if (flag == 2)
		printf("The knight's path is covering all board.\n");

	else if (flag == 3)
		printf("The knight's path does NOT cover all board.\n");

	else /* flag == -1 */
		printf("The file does NOT exist\n");
}

void printMainOptions() {

	printf("1. Enter a knight's starting position\n");
	printf("2. Create all possible knight paths\n");
	printf("3. Find a knight path covering all board\n");
	printf("4. Save knight path covering all board to file\n");
	printf("5. Load and display path from file\n");
	printf("6. Exit\n");
}