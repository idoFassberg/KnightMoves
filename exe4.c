#include "exe4.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
    chessPosList* lst;
    lst = (chessPosList*)malloc(sizeof(chessPosList));
    checkAllocationList(lst);
    makeEmptyList(lst);

    int listLen = 0;
    bool isFound = false;
    findKnightPathCoveringAllBoardHelper(path_tree->root, &listLen, &isFound, lst);


    if (listLen == (BOARD_SIZE * BOARD_SIZE))/* check if the list is in the right size */
        return lst;
    else
    {
        myFree_chessPosList(lst);/* if not in the right size - return null */
        return NULL;
    }

}

void findKnightPathCoveringAllBoardHelper(treeNode* root, int* listLen, bool* flag, chessPosList* lst)
{
    if (*flag == true) /* we want the function to just return from the rekorsia in this case */
    {
        *listLen = 0;
        return;
    }

    treeNodeListCell* curr;

    insertDataToEndList(lst, root->position);

    (*listLen) = (*listLen) + 1;

    curr = root->next_possible_positions;


    while ((curr != NULL) && (*flag == false))/* in case we didnt find the right path - keep search - call the rekorsia with next member*/
    {
        findKnightPathCoveringAllBoardHelper(curr->node, listLen, flag, lst);

        curr = curr->next;
    }

    if ((*flag == false))
    {
        if ((*listLen) == (BOARD_SIZE * BOARD_SIZE))/* check for the right path */
        {
            *flag = true;
            return;
        }
        else
        {
            (*listLen)--;
            deleteFromList(lst, lst->tail);/* delete the last member because its not the right path */
        }
    }

}

void deleteFromList(chessPosList* lst, chessPosCell* node)
{
    if (lst->head == NULL)/*case the list is empty*/
        return;
    else if (lst->head == lst->tail)/*case their is only 1 member*/
        lst->head = lst->tail = NULL;
    else if (lst->head == node)/*case we delete the list head*/
        lst->head = node->next;
    else if (lst->tail == node)/*case we delete the list tail*/
    {
        chessPosCell* curr = lst->head->next;
        chessPosCell* saver = lst->head;
        while (curr != NULL)
        {
            if (curr == node)
            {
                saver->next = NULL;
                lst->tail = saver;
            }
            saver = curr;
            curr = curr->next;
        }
    }
    else /*case we delete in the middle of the list*/
    {
        chessPosCell* curr = lst->head->next;
        chessPosCell* saver = lst->head;
        while (curr != NULL)
        {
            if (curr == node)
            {
                saver->next = curr->next;
            }
            saver = curr;
            curr = curr->next;
        }
    }


    free(node);
}

void insertDataToEndList(chessPosList* lst, chessPos data)
{
    chessPosCell* node;
    node = createNewChessPosCell(data, NULL);
    insertNodeToEndList(lst, node);
}

void insertNodeToEndList(chessPosList* lst, chessPosCell* curr)
{
    if (isEmptyList(lst) == true)
        lst->head = lst->tail = curr;
    else
    {
        lst->tail->next = curr;
        lst->tail = curr;
    }
    curr->next = NULL;
}

void myFree_chessPosList(chessPosList* lst)
{
    chessPosCell* curr, * temp;
    curr = lst->head;
    while (curr != NULL)
    {
        temp = curr->next;
        free(curr);
        curr = temp;
    }
    lst->head = NULL;
}

bool isEmptyList(chessPosList* lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;

}

chessPosCell* createNewChessPosCell(chessPos data, chessPosCell* next)
{
    chessPosCell* node;
    node = (chessPosCell*)malloc(sizeof(chessPosCell));
    if (node)
    {
        node->position[0] = data[0];
        node->position[1] = data[1];
        node->next = next;
        return node;
    }
    else
    {
        printf("Allocation failed");
        exit(1);
    }
    return node;
}

void makeEmptyList(chessPosList* lst)
{
    lst->head = lst->tail = NULL;
}

void checkAllocationList(chessPosList* lst)
{
    if (lst == NULL)
    {
        printf("List allocation failed\n");
        exit(1);
    }
}